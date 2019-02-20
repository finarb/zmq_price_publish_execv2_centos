
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2009      **/
/**                                **/
/************************************/

#ifndef FEEDOS_FRAMEWORK_REFERENTIAL_PRICE_INCREMENT_TABLE_H
#define FEEDOS_FRAMEWORK_REFERENTIAL_PRICE_INCREMENT_TABLE_H

#ifndef FEEDOS_COMPAT_INCLUDE
#	ifndef FEEDOS_API_API_H
#		include "../api/api.h"
#	endif
#endif

#include <map>
#include <set>

namespace FeedOS {

	class ReferentialPriceIncrementTable
	{
		ReferentialPriceIncrementTable const & operator=(ReferentialPriceIncrementTable const &);
	public:
		ReferentialPriceIncrementTable ();

		// load a set of values
		ReferentialPriceIncrementTable (Types::VariableIncrementPriceBandTable const & data);

		// get list of price bands
		Types::VariableIncrementPriceBandTable const & get_data() const { return m_data; }

		// load a new set of values
		void load (Types::VariableIncrementPriceBandTable const & data);

		// print all values (uses market_value2name() to convert values)
		void print_content (std::ostream & os) const;

		// return false in case of error (cannot compute any tick size)
		// up/down tick_size is 0 when no order can be placed in this direction
		bool get_price_increments (float64 base_price, float64 & upper_tick_size, float64 & lower_tick_size) const;

	private:
		Types::VariableIncrementPriceBandTable			m_data;
	};


	class ReferentialPriceIncrementTables
	{
		ReferentialPriceIncrementTables const & operator=(ReferentialPriceIncrementTables const &);
	public:
		ReferentialPriceIncrementTables ();

		// load a set of values
		ReferentialPriceIncrementTables (Types::ListOfVariableIncrementPriceBandTable const & data);

		// get list of price bands
		Types::VariableIncrementPriceBandTable const & get_data(uint32 table_id) const;

		// load a new set of values
		void load (Types::ListOfVariableIncrementPriceBandTable const & data, bool merge_with_existing_tables=true);

		// print all values (uses market_value2name() to convert values)
		void print_content (std::ostream & os) const;

		// return false in case of error (cannot compute any tick size)
		// up/down tick_size is 0 when no order can be placed in this direction
		bool get_price_increments (unsigned int table_id, float64 base_price, float64 & upper_tick_size, float64 & lower_tick_size) const;

	private:
		typedef std::map <unsigned int, ReferentialPriceIncrementTable> MapOfVarTickSizeTable;
		MapOfVarTickSizeTable	m_table_map;
	};

}


#endif
