
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_ENCODING_FUNCTIONS_H
#define FEEDOS_COMM_ENCODING_FUNCTIONS_H

#ifndef FEEDOS_API_GENERATED_TYPES_H
#  include "generated_types.h"
#endif

#ifndef FEEDOS_COMM_ENCODING_H
#  include "../comm/encoding.h"
#endif

#ifndef FEEDOS_COMM_EXCEPTIONS_H
#  include "../comm/exceptions.h"
#endif

namespace FeedOS {

#define FEEDOS_MAKE_ENCODER_BASIC_TYPE(TYPE)		\
	inline void Encode_##TYPE (DataEncoder & e, TYPE const & v)	{ e.encode_##TYPE (v); }	\
	inline void Decode_##TYPE (DataDecoder & d, TYPE & v)		{ d.decode_##TYPE (v); }

#define FEEDOS_MAKE_ENCODER_TYPE_CAST(TYPE,ALIAS)	\
	inline void Encode_##TYPE (DataEncoder & e, TYPE const & v)	{ e.encode ((ALIAS) v); }	\
	inline void Decode_##TYPE (DataDecoder & d, TYPE & v)		{ d.decode ((ALIAS&)v); }

#define FEEDOS_DECLARE_ENCODER(TYPE)		\
	void Encode_##TYPE		(DataEncoder & e, TYPE const & v);	\
	void Decode_##TYPE		(DataDecoder & d, TYPE & v);


	FEEDOS_MAKE_ENCODER_BASIC_TYPE	(uint32)		
	FEEDOS_MAKE_ENCODER_BASIC_TYPE	(uint16)		
	FEEDOS_MAKE_ENCODER_BASIC_TYPE	(uint8)
	FEEDOS_MAKE_ENCODER_BASIC_TYPE	(int64)	
	FEEDOS_MAKE_ENCODER_BASIC_TYPE	(int32)		
	FEEDOS_MAKE_ENCODER_BASIC_TYPE	(int16)		
	FEEDOS_MAKE_ENCODER_BASIC_TYPE	(int8)		
	FEEDOS_MAKE_ENCODER_BASIC_TYPE	(float64)		
	FEEDOS_MAKE_ENCODER_BASIC_TYPE	(bool)		
	FEEDOS_MAKE_ENCODER_BASIC_TYPE	(char)		
	FEEDOS_MAKE_ENCODER_BASIC_TYPE	(ReturnCode)	
	FEEDOS_MAKE_ENCODER_BASIC_TYPE	(String)		
	FEEDOS_MAKE_ENCODER_BASIC_TYPE	(Timestamp)
	FEEDOS_MAKE_ENCODER_BASIC_TYPE	(Enum)		

	template<typename T> void Decode_Enum	(DataDecoder & d, T & v)		{ d.decode_Enum (v); }
	template<typename T> void Encode_Enum	(DataEncoder & e, T const & v)	{ e.encode_Enum (v); }

	FEEDOS_MAKE_ENCODER_TYPE_CAST (FOSMarketId,			FOSLowLevelMarketId)

	inline void Encode_FOSInstrumentCode (DataEncoder & e, FOSInstrumentCode const & v)
	{
		if (v.get_numeric() & INSTRUMENT_CODE_RESERVED_MASK)
		{
			throw Exception ("Invalid instrument code: " + v.to_str());
		}
		e.encode ((FOSLowLevelInstrumentCode) v);
	}
	inline void Decode_FOSInstrumentCode (DataDecoder & d, FOSInstrumentCode & v)		{ d.decode ((FOSLowLevelInstrumentCode&)v); }

	FEEDOS_DECLARE_ENCODER	(Any);
	FEEDOS_DECLARE_ENCODER	(PolymorphicInstrumentCode);
	FEEDOS_DECLARE_ENCODER	(BinaryBuffer);
	FEEDOS_DECLARE_ENCODER	(FOSPrice);
	FEEDOS_DECLARE_ENCODER	(FOSInteger);


#undef FEEDOS_MAKE_ENCODER_BASIC_TYPE
#undef FEEDOS_MAKE_ENCODER_TYPE_CAST
#undef FEEDOS_MAKE_ENCODER_DECLARE_PROTO

}



#endif
