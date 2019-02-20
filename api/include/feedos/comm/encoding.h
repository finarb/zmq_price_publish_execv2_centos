
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2005-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_COMM_ENCODING_H
#define FEEDOS_COMM_ENCODING_H

#ifndef FEEDOS_BASE_NETWORK_H
#  include "../base/network.h"
#endif

#ifndef FEEDOS_COMM_TYPES_H
#  include "types.h"
#endif

namespace FeedOS {

	namespace Encoding {

		// internal stuff
		typedef uint32		LargeListSizeType;
		typedef uint8		SmallListSizeType;

		// types used to binary-encode predefined types (see types.h errors.h)
		typedef	uint32	Enum_t				;
		typedef uint16	ReturnCode_t		;
	}


	class DataEncoder;
	class DataDecoder;
	void Encode_FOSInteger(DataEncoder & e, FOSInteger const & v);
	void Decode_FOSInteger(DataDecoder & d, FOSInteger & v);


	class EncodedBuffer
	{
	public:
		inline EncodedBuffer () {}
		inline virtual ~EncodedBuffer () {}
		inline EncodedBuffer (EncodedBuffer const & s) : m_buffer (s.m_buffer) {}
		inline EncodedBuffer (std::string const & s) : m_buffer (s) {}
		inline EncodedBuffer (void const * p, unsigned int n) : m_buffer ((char const*)p, n) {}

		inline std::string const &	get_buffer  () const	{ return m_buffer; }
		inline std::string &		get_buffer  ()			{ return m_buffer; }

		virtual void dump (std::ostream & os) const { dump_hexa_and_ascii (os, m_buffer.c_str(), (unsigned int)m_buffer.size()); }

		static void dump_hexa_and_ascii (std::ostream & os, void const * p, unsigned int n);
	private:
		std::string	m_buffer;
	};




	class DataEncoder
	{
		std::string & m_buffer;
		DataEncoder const & operator= (DataEncoder const & m);
	public:
		inline DataEncoder (DataEncoder const & v) : m_buffer (v.m_buffer) {}
		inline DataEncoder (EncodedBuffer & b) : m_buffer (b.get_buffer()) {}

		inline void clear() { m_buffer.clear(); }


		//
		// basic types (see base/base.h)
		//
#define FEEDOS_DataEncoder_APPEND_BASIC(T)	\
		inline void encode_##T(T v) { v=hton_##T(v); m_buffer.append ((char const *)&v,sizeof(T)); }	\
		inline void encode (T const & v) { encode_##T(v); }

		FEEDOS_DataEncoder_APPEND_BASIC(uint64)
		FEEDOS_DataEncoder_APPEND_BASIC(uint32)
		FEEDOS_DataEncoder_APPEND_BASIC(uint16)
		FEEDOS_DataEncoder_APPEND_BASIC(uint8)
		FEEDOS_DataEncoder_APPEND_BASIC(int64)
		FEEDOS_DataEncoder_APPEND_BASIC(int32)
		FEEDOS_DataEncoder_APPEND_BASIC(int16)
		FEEDOS_DataEncoder_APPEND_BASIC(int8)
		FEEDOS_DataEncoder_APPEND_BASIC(float64)
		FEEDOS_DataEncoder_APPEND_BASIC(char)

#undef	FEEDOS_DataEncoder_APPEND_BASIC

		// bool
		inline void encode_bool(bool v)	{ encode_uint8(static_cast<uint8> (v?1:0)); }

		// Timestamp
		void encode_Timestamp(Timestamp const & v);


		//
		// complex types (see types.h)
		//
#define FEEDOS_DataEncoder_APPEND_TYPE(T)	\
		inline void encode_##T(T const & v) { encode ((Encoding::T##_t) v); }

		FEEDOS_DataEncoder_APPEND_TYPE(Enum)
		FEEDOS_DataEncoder_APPEND_TYPE(ReturnCode)

#undef FEEDOS_DataEncoder_APPEND_TYPE



		template<typename T>
		void encode_Enum (T const & v) { encode ((Encoding::Enum_t)v); }


		//
		// variable-length strings
		//
		void encode_String	(std::string const & s);


		//
		// all-around integer
		//
		void encode_FOSInteger (FOSInteger const & v) { Encode_FOSInteger (*this, v); }


		//
		// lists of objects
		//
		inline void encode_count_long_list	(unsigned int n) { encode((Encoding::LargeListSizeType)n); }



		// raw stuff
		inline void encode_binary	(void const * p, unsigned int n)	{ m_buffer.append ((char const*)p, n); }
		inline void encode_binary	(std::string const & s)				{ m_buffer.append (s); }
	};




	class DataDecoder
	{
		inline DataDecoder (DataDecoder const & /*v*/) : m_buffer (0), m_cursor(0) {}
	public:
		inline DataDecoder () : m_buffer (0), m_cursor(0) {}

		inline DataDecoder (EncodedBuffer const & b) { attach_to_buffer (b);}
		inline DataDecoder (std::string const & b) { attach_to_string (b);}
		// no copy constructor nor operator=  (on purpose)

		inline void attach_to_string (std::string const & b)
		{ 
			m_buffer=&b;
			m_reset_offset=0;
			reset_cursor();
		}

		inline void attach_to_buffer (EncodedBuffer const & b)
		{ 
			attach_to_string (b.get_buffer());
		}

		//
		// basic types (see base/base.h)
		//
#define FEEDOS_DataDecoder_DECODE_BASIC(T)	\
		inline void peek_##T(T & v) const	{ check_underflow ("peek_"#T, sizeof(T)); v=ntoh_##T(*(T const *)m_cursor); }	\
		inline void decode_##T (T & v)		{ check_underflow ("decode_"#T,  sizeof(T)); v=ntoh_##T(*(T const *)m_cursor); skip_bytes(sizeof(T)); }	\
		inline void peek(T & v) const	{ peek_##T(v); }			\
		inline void decode (T & v)		{ decode_##T (v); }			\
		inline T peek_##T() const		{ T v; peek (v); return v; }	\
		inline T decode_##T ()			{ T v; decode (v); return v; }

		FEEDOS_DataDecoder_DECODE_BASIC(uint64)
		FEEDOS_DataDecoder_DECODE_BASIC(uint32)
		FEEDOS_DataDecoder_DECODE_BASIC(uint16)
		FEEDOS_DataDecoder_DECODE_BASIC(uint8)
		FEEDOS_DataDecoder_DECODE_BASIC(int64)
		FEEDOS_DataDecoder_DECODE_BASIC(int32)
		FEEDOS_DataDecoder_DECODE_BASIC(int16)
		FEEDOS_DataDecoder_DECODE_BASIC(int8)
		FEEDOS_DataDecoder_DECODE_BASIC(float64)
		FEEDOS_DataDecoder_DECODE_BASIC(char)

#undef	FEEDOS_DataDecoder_DECODE_BASIC

		// bool
		inline bool decode_bool() { return (0!=decode_uint8()); }
		inline void decode_bool(bool & v) { v=decode_bool(); }

		// Timestamp
		void decode_Timestamp(Timestamp & v);


		//
		// complex types (see types.h)
		//
#define FEEDOS_DataDecoder_DECODE_TYPE(T)	\
	inline void decode_##T(T & v) { Encoding::T##_t t;	decode(t); v=T(t); }

		FEEDOS_DataDecoder_DECODE_TYPE(Enum)
		FEEDOS_DataDecoder_DECODE_TYPE(ReturnCode)

#undef FEEDOS_DataDecoder_DECODE_TYPE


		template<typename T>
		void decode_Enum (T & v) { Encoding::Enum_t t; decode (t); v=(T)t; }



		//
		// variable-length strings
		//
		void					decode_String	(std::string & s);
		inline std::string		decode_String	() { std::string s; decode_String(s); return s; }



		//
		// all-around integer
		//
		void decode_FOSInteger (FOSInteger & v) { Decode_FOSInteger(*this,v); }
		inline FOSInteger decode_FOSInteger () { FOSInteger v; Decode_FOSInteger(*this,v); return v; }



		//
		// lists of objects
		//
		unsigned int decode_count_long_list	();


		// raw stuff
		inline std::string	decode_binary (unsigned int l) 
		{
			check_underflow ("decode_binary", l); 
			char const *p=(char const *)m_cursor; 
			skip_bytes(l);
			return std::string (p, l);
		}
		inline void			decode_binary	(std::string & s, unsigned int l)
		{
			check_underflow ("decode_binary", l);
			s.assign ((char const *)m_cursor, l); 
			skip_bytes(l); 
		}
		inline void			decode_binary	(void * p, unsigned int n) 
		{
			check_underflow ("decode_binary", n);
			memcpy ((char *) p, (char const *)m_cursor, n);
			skip_bytes(n);
		}

		inline unsigned int	get_buffer_remaining_bytes () const { return m_buffer_remaining_bytes; }
	
	protected:

		inline void			reset_cursor ()
		{
			m_buffer_remaining_bytes = (unsigned int)m_buffer->size() - m_reset_offset;
			m_cursor=(unsigned char const *)m_buffer->data() + m_reset_offset; 

		}

		inline void			set_reset_offset (unsigned int offset) { m_reset_offset = offset; }
		inline void			set_reset_offset () { m_reset_offset = (unsigned int)(m_cursor-(unsigned char const *)m_buffer->data()); }

	private:
		std::string const *		m_buffer;
		unsigned int			m_buffer_remaining_bytes;
		unsigned char const *	m_cursor;
		unsigned int			m_reset_offset;

#if FEEDOS_ENABLE_PARANOID_CHECKS
		inline void check_underflow (char const * where, unsigned int nb_to_read) const { if (nb_to_read > m_buffer_remaining_bytes) log_underflow(where, nb_to_read); }
#else
		inline void check_underflow (char const * /*where*/, unsigned int /*nb_to_read*/) const {}
#endif
	public:
		void log_underflow (char const * where, unsigned int nb_to_read) const;
		void log_protocol_error (char const * where) const;

		inline void const *	cursor () const { return m_cursor; }
		inline void			skip_bytes (unsigned int l) { m_buffer_remaining_bytes-=l; m_cursor+=l; }
	};



}



inline std::ostream & operator<< (std::ostream & os, FeedOS::EncodedBuffer const & b)
{
	b.dump(os);
	return os;
}

// to be moved somewhere else.
void dump_utctimestamps_encoding_capabilities(std::ostream &);


#endif
