
/**********************************************/
/** FeedOS sample client code               **/
/**                                         **/
/** performing a snapshot of quotation data **/
/** on several instruments at once          **/
/**                                         **/
/** QuantHouse 2005                         **/
/*********************************************/

#include <feedos/zmqpp/tools.h>

#include <feedos/api/api.h>
#include <feedos/framework/InstrumentReferentialData.h>
#include <feedos/framework/InstrumentQuotationData.h>
#include <feedos/framework/market_tools.h>

using namespace std;
using namespace FeedOS;
using namespace FeedOS::Types;

static void do_print_value (	char const * tag_name,
								float64 some_price,
								float64 factor,
								std::string const & price_currency,
								std::string const & fractional_price
							)
{
	double const price_value = some_price * factor;
	std::cout << "  monetary value of "<< tag_name << " = "<< price_value << ' ' << price_currency <<std::endl;
	if ( !fractional_price.empty() )
	{
		std::cout << "  fractional price=" << fractional_price << std::endl;
	}
}


void perform_price_instruments (FeedOS::API::Connection & connection, int argc, char * argv[]) 
{
	if (argc<2) {
		cerr <<"? CODES..."<<endl;
		return;
	}

	// read list of instrument codes
	FeedOS::Types::ListOfPolymorphicInstrumentCode	codes;
	if (!extract_codes (codes, argc, argv))	// read them from command-line arguments
		return;

	ReturnCode rc;

	// retrieve a few fundamental characteristics ("referential" data)
	FeedOS::Types::ListOfReferentialTagNumber requested_referential_tags;
	requested_referential_tags.push_back (FeedOS::TAG_PriceCurrency);
	requested_referential_tags.push_back (FeedOS::TAG_Factor);
	requested_referential_tags.push_back (FeedOS::TAG_MARKET_CME_DisplayPriceNbOfDecimal);
	requested_referential_tags.push_back (FeedOS::TAG_MARKET_CME_DisplayPricePrimaryDenominator);
	requested_referential_tags.push_back (FeedOS::TAG_MARKET_CME_DisplayPriceSecondaryDenominator);

	FeedOS::Types::ListOfInstrumentCharacteristics result_referential_data;
	rc = API_REFERENTIAL_GetInstruments
					(
						connection,
						// outputs
						result_referential_data,
						// inputs
						codes,
						requested_referential_tags
					);
	if (rc != RC_OK) {
		cerr << "referential_get error, rc="<< error_string(rc) <<endl;
		return;
	}

	// retrieve Last Price
	FeedOS::Types::ListOfQuotationTagNumber requested_quotation_tags;
	requested_quotation_tags.push_back (FeedOS::TAG_LastPrice);

	FeedOS::Types::ListOfInstrumentStatusL1	result_quotation_data;
	rc = API_QUOTATION_SnapshotInstrumentsL1 
					(
						connection, 
						// outputs
						result_quotation_data,
						// inputs
						codes, 
						requested_quotation_tags
						// use default values for remaining input params
					);
	if (rc != RC_OK) {
		cerr << "quotation_snapshot error, rc="<< error_string(rc) <<endl;
		return;
	}

	// pretty-print prices of each instrument
	FeedOS::InstrumentReferentialData	ref_data;
	FeedOS::InstrumentQuotationData		quot_data;
	for (	unsigned int i=0;
			i < codes.size();
			++i)
	{
		FeedOS::PolymorphicInstrumentCode const & code = codes[i];
		std::cout << "\ninstrument: "<<code<<std::endl;

		FeedOS::Types::InstrumentCharacteristics const & characteristics = result_referential_data[i];
		ref_data	.reset(characteristics.getCode());
		ref_data	.load (characteristics.getAttributes());
		FeedOS::Types::InstrumentStatusL1 const & status = result_quotation_data[i];
		quot_data	.reset(status.getCode());
		quot_data	.load (status.getValues());

		float64 factor;
		if (ref_data.get_Factor (factor))
		{
			std::cout << "  Factor="<< factor <<std::endl;
		}
		else
		{
			std::cout << "  no tag Factor" << std::endl;
			// no Factor: assume 1
			factor=1;
		}
		
		std::string price_currency;
		if (ref_data.get_PriceCurrency (price_currency))
		{
			std::cout << "  PriceCurrency="<<price_currency<<std::endl;
		}
		else
		{
			price_currency = "(unknown currency)";
		}

		unsigned int displayPrice_primaryDenominator = 0;
		displayPrice_primaryDenominator = ref_data.get_tag_uint32( FeedOS::TAG_MARKET_CME_DisplayPricePrimaryDenominator );
		if ( displayPrice_primaryDenominator )
		{
			std::cout << "  Display price primary denominator=" << displayPrice_primaryDenominator << std::endl;
		}
		else
		{
			std::cout << "  no tag TAG_MARKET_CME_DisplayPricePrimaryDenominator" << std::endl;
		}
		
		unsigned int displayPrice_secondaryDenominator = 0;
		displayPrice_secondaryDenominator = ref_data.get_tag_uint32( FeedOS::TAG_MARKET_CME_DisplayPriceSecondaryDenominator );
		if ( displayPrice_secondaryDenominator )
		{
			std::cout << "  Display price secondary denominator (numerator)=" << displayPrice_secondaryDenominator << std::endl;
		}
		else
		{
			std::cout << "  no tag TAG_MARKET_CME_DisplayPriceSecondaryDenominator" << std::endl;
		}

		unsigned int displayPrice_nbDecimal = 0;
		displayPrice_nbDecimal = ref_data.get_tag_uint32( FeedOS::TAG_MARKET_CME_DisplayPriceNbOfDecimal );
		if ( displayPrice_nbDecimal )
		{
			std::cout << "  Display price nb decimal=" << displayPrice_nbDecimal << std::endl;
		}
		else
		{
			std::cout << "  no tag TAG_MARKET_CME_DisplayPriceNbOfDecimal" << std::endl;
		}

		float64 last_price = 0;
		if (quot_data.get_LastPrice (last_price))
		{
			std::cout << "  LastPrice="<< last_price <<std::endl;
		}
		else
		{
			std::cout << "  no tag LastPrice"<<std::endl;
			continue;
		}
		
		std::string fractional_display_price;
		if ( !FeedOS::convert_CME_decimal_to_fractional_display_price(displayPrice_primaryDenominator, displayPrice_secondaryDenominator, displayPrice_nbDecimal, last_price, fractional_display_price) )
		{
			fractional_display_price = "[N/A]";
		}

		// could also print LastTradePrice, PreviousDailyClosingPrice, best Bid/Ask, etc
		do_print_value ("LastPrice", last_price, factor, price_currency, fractional_display_price);
	}
}
