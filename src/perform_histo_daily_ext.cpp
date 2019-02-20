
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

using namespace FeedOS;
using namespace FeedOS::Types;

/** \cond refguide
 * This sample demonstrates how to use the \c GetHistoryDailyExt request to
 * download daily and session historical data. This request also lets users
 * choose to apply corporate action adjustment factors if necessary. It makes
 * use of a synchronous call.
 *
 * Users have first to set input parameters as needed: list of instrument codes,
 * begin and end date, whether they want daily, session or both points, and
 * which adjustment factor to apply.
 *
 * Then, containers for the returned values have to be created: a list of
 * internal codes corresponding to the input codes, and the actual requested
 * data.
 * \snippet perform_histo_daily_ext.cpp snippet_returned_data
 *
 * The request can now be sent.
 * \snippet perform_histo_daily_ext.cpp snippet_request
 *
 * If request response is \c RC_OK, data are valid:
 * \snippet perform_histo_daily_ext.cpp snippet_response
 *
 * \endcond
 */
void perform_histo_daily_ext(API::Connection & connection, int argc, char * argv[])
{
	FEEDOS_SCOPER(User, "perform_histo_daily_ext");

	if (argc != 6) {
		std::cerr << "Usage: instr_code begin_date end_date point_type adj_factor_types" << std::endl;
		std::cerr << "       point_type: Daily, Session, DailyAndSession" << std::endl;
		std::cerr << "       adj_factor_types: None, All" << std::endl;
		return;
	}

    PolymorphicInstrumentCode instr_code;
	if (!instr_code.read_from_string(argv[1]))
	{
		std::cerr << "invalid instrument code" << std::endl;
		return;
	}

	YMD_Date begin_date;
	{
		Timestamp t;
		if (!t.set_from_string(argv[2]))
		{	// could be "null" => "beginning of time"
			std::cerr << "syntax error while reading begin_date" << std::endl;
			return;
		}
		int y,m,d;
		t.get(y,m,d);
		begin_date = YMD_Date (static_cast<uint16> (y), static_cast<uint8> (m), static_cast<uint8> (d));
	}

	YMD_Date end_date;
	{
		Timestamp t;
		if (!t.set_from_string(argv[3]))
		{   // could be "null" => "today"
			std::cerr << "syntax error while reading end_date" << std::endl;
			return;
		}
		int y,m,d;
		t.get(y,m,d);
		end_date = YMD_Date (static_cast<uint16> (y), static_cast<uint8> (m), static_cast<uint8> (d));
	}

	DailyExtPointType point_type;
	{
		if (argv[4] == std::string("Daily"))
		{
			point_type = DailyExtPointType_DailyOnly;
		}
		else if (argv[4] == std::string("Session"))
		{
			point_type = DailyExtPointType_SessionOnly;
		}
		else if (argv[4] == std::string("DailyAndSession"))
		{
			point_type = DailyExtPointType_DailyAndSession;
		}
		else
		{
			std::cerr << "syntax error while reading point_type" << std::endl;
			return;
		}
	}

	AdjustmentFactorEventTypeMask adj_factor_types;
	{
		if (argv[5] == std::string("None"))
		{
			adj_factor_types = AdjustmentFactorEventTypeMask_NoAdjustment;
		}
		else if (argv[5] == std::string("All"))
		{
			adj_factor_types = AdjustmentFactorEventTypeMask_All;
		}
		// You might want to handle other values for adjustment factor types
		else
		{
			std::cerr << "syntax error while reading adj_factor_types" << std::endl;
			return;
		}
	}

	//![snippet_returned_data]
	FOSInstrumentCode internal_code;
	ListOfDailyHistoryPointExt result_data;
	//![snippet_returned_data]

	//![snippet_request]
	ReturnCode const rc = API_QUOTATION_GetHistoryDailyExt(
			connection,
			internal_code,
			result_data,
			instr_code,
			begin_date,
			end_date,
			point_type,
			adj_factor_types
			);
	//![snippet_request]

	//![snippet_response]
	if (rc != RC_OK)
	{
		std::cerr << "get_histo_daily_ext error, rc=" << error_string(rc)
				<< std::endl;
	}
	else
	{
		std::cerr << "get_histo_daily_ext ok" << std::endl;
		dump_histo_daily_ext(result_data);
	}
	//![snippet_response]
}
