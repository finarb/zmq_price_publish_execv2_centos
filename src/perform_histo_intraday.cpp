
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

using namespace std;
using namespace FeedOS;
using namespace FeedOS::Types;

void perform_histo_intraday_extended(FeedOS::API::Connection & connection, int argc, char * argv[])
{
	FEEDOS_SCOPER (User, "perform_histo_intraday_extended");

	if (argc != 4)
	{
		std::cerr <<"? CODE BEGIN_DATE END_DATE" << std::endl;
		return;
	}
	char const * instr_code_str = argv[1];

    FeedOS::PolymorphicInstrumentCode instr_code;
	if (!instr_code.read_from_string (instr_code_str))
	{
		std::cerr << "syntax error while reading PolymorphicInstrumentCode: " << instr_code_str << std::endl;
		return;
	}

	Timestamp begin_date;
	if (!begin_date.set_from_string(argv[2]))
	{
		// can be "null" => today 00:00
		std::cerr << "syntax error while reading BEGIN_DATE" << std::endl;
		return;
	}

	Timestamp end_date;
	if (!end_date.set_from_string(argv[3]))
	{
		// can be "null" => now
		std::cerr << "syntax error while reading END_DATE" << std::endl;
		return;
	}

	// Store index values mapping in a map to ease intraday points display
	std::map<unsigned int, ListOfQuotationContextFlag> trade_condition_map;
	{
		FeedOS::ListOfTradeConditionsDictionaryEntry dictionary;
		ReturnCode const rc_dico = API_REFERENTIAL_GetTradeConditionsDictionary(connection, dictionary);
		if (RC_OK != rc_dico)
		{
			std::cerr << "error on GetTradeConditionsDictionary request: " << error_string(rc_dico) << std::endl;
			return;
		}

		for (FeedOS::ListOfTradeConditionsDictionaryEntry::const_iterator current = dictionary.begin(), end = dictionary.end(); end != current; ++current)
		{
			trade_condition_map.insert(std::make_pair(current->getIndex(),current->getValue()));
		}
	}

	// result: internal code of the target instrument
	FOSInstrumentCode result_internal_code;
	// result: the data
	FeedOS::Types::ListOfIntradayHistoryPointExtended result_data;

	// synchronous request
	ReturnCode const rc = API_QUOTATION_GetHistoryIntradayExtended
			(connection,
			// outputs
			result_internal_code,
			result_data,
			// inputs
			instr_code,
			begin_date,
			end_date
			);

	if (rc != RC_OK)
	{
		std::cerr << "get_histo_intraday_extended error, rc="<< error_string(rc) << std::endl;
	}
	else
	{
		std::cerr << "get_histo_intraday_extended ok" << std::endl;
		dump_histo_intraday_extended(result_data, trade_condition_map);
	}
}

void perform_histo_intraday_extended_N_ticks(FeedOS::API::Connection & connection, int argc, char * argv[])
{
	FEEDOS_SCOPER (User, "perform_histo_intraday_extended_N_ticks");

	if (argc != 4)
	{
		std::cerr <<"? CODE DATETIME NB_TICKS" << std::endl;
		return;
	}
	char const * instr_code_str = argv[1];

	FeedOS::PolymorphicInstrumentCode instr_code;
	if (!instr_code.read_from_string (instr_code_str))
	{
		std::cerr << "syntax error while reading PolymorphicInstrumentCode: " << instr_code_str << std::endl;
		return;
	}

	Timestamp date;
	if (!date.set_from_string(argv[2]))
	{
		// can be "null" => today 00:00
		std::cerr << "syntax error while reading DATE" << std::endl;
		return;
	}

	/* if nb_ticks is :
		> 0: returns at most 'nb_ticks' trades after the specified date (included)
		< 0: returns at most 'nb_ticks' trades before the specified date (excluded)
	*/
	int nb_ticks = atoi(argv[3]);

	// Store index values mapping in a map to ease intraday points display
	std::map<unsigned int, ListOfQuotationContextFlag> trade_condition_map;
	{
		FeedOS::ListOfTradeConditionsDictionaryEntry dictionary;
		ReturnCode const rc_dico = API_REFERENTIAL_GetTradeConditionsDictionary(connection, dictionary);
		if (RC_OK != rc_dico)
		{
			std::cerr << "error on GetTradeConditionsDictionary request: " << error_string(rc_dico) << std::endl;
			return;
		}

		for (FeedOS::ListOfTradeConditionsDictionaryEntry::const_iterator current = dictionary.begin(), end = dictionary.end(); end != current; ++current)
		{
			trade_condition_map.insert(std::make_pair(current->getIndex(),current->getValue()));
		}
	}

	// result: internal code of the target instrument
	FOSInstrumentCode result_internal_code;
	// result: the data
	FeedOS::Types::ListOfIntradayHistoryPointExtended result_data;

	// synchronous request
	ReturnCode const rc = API_QUOTATION_GetHistoryIntradayExtendedNTicks
		(connection,
		// outputs
		result_internal_code,
		result_data,
		// inputs
		instr_code,
		date,
		nb_ticks
		);

	if (rc != RC_OK)
	{
		std::cerr << "get_histo_intraday_extended_N_ticks error, rc="<< error_string(rc) << std::endl;
	}
	else
	{
		std::cerr << "get_histo_intraday_extended_N_ticks ok" << std::endl;
		dump_histo_intraday_extended(result_data, trade_condition_map);
	}
}
