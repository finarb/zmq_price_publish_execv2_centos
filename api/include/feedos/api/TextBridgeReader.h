
/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2007      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_TEXT_BRIDGE_READER_H
#define FEEDOS_TEXT_BRIDGE_READER_H

#include "TextBridgeInterface.h"
#include <string>
#include <fstream>
#include <map>

namespace FeedOS {

	namespace TextBridge {

		class Reader
		{
			typedef Reader	Me;
		public:
			Reader (	Interface & target, 
						bool should_ignore_unknown_tokens,
						bool should_accept_any_protocol_version
					);

			virtual ~Reader ();

			// return false in case of error
			bool enable_logging (std::string const & filename, bool sync_write = false);

			// call this to begin a new "session"
			void reset_state();

			bool decode_raw_data (void const * p, unsigned int l);
			bool decode_raw_stream (std::istream & s);

			unsigned int get_counter_nb_bytes_read() const { return m_counter_nb_bytes_read; }
			unsigned int get_counter_nb_msg_read() const { return m_counter_nb_msg_read; }
			unsigned int get_counter_error_EOD () const { return m_counter_decoding_error_EOD; }
			unsigned int get_counter_error_UNKNOWN_CMD() const { return m_counter_decoding_error_UNKNOWN_CMD; }
			unsigned int get_counter_error_CMD_EXECUTION() const { return m_counter_execution_error; }

		protected:
			// expects a "full cmd" (that is a CMD_TOKEN [+ARGS])
			bool decode_full_cmd (char const * p, unsigned int l);
			bool decode_cmd (std::string const & cmd_token, char const * args_p, unsigned int args_len);

		private:
			Interface &	m_target;
			bool		m_should_ignore_unknown_tokens;
			bool		m_should_accept_any_protocol_version;

			bool			m_logging_enabled;
			bool			m_logging_sync_write;
			std::string		m_log_filename;
			std::ofstream	m_log_file;

			std::string	m_current_buffer;
			std::string m_current_cmd_token;
			char const * m_current_cmd_token_descr;

			typedef bool (Me::*decode_cmd_token_cb) (char const * args_p, unsigned int args_len, char const expected_arguments[]);
			typedef std::pair<decode_cmd_token_cb,char const*> CB_and_description;
			typedef std::map<std::string, CB_and_description> MapOfDecodeDB;
			MapOfDecodeDB	m_map_of_decoder_cb;

			unsigned int	m_counter_nb_bytes_read;
			unsigned int	m_counter_nb_msg_read;
			unsigned int	m_counter_decoding_error_EOD;
			unsigned int	m_counter_decoding_error_UNKNOWN_CMD;
			unsigned int	m_counter_execution_error;

			bool log_decoding_error (char const*err_str) const;

			inline double		decode_args_price	(char const * & args_p) const;
			inline double		decode_args_double	(char const * & args_p) const;
			inline long int		decode_args_long	(char const * & args_p) const;
			inline unsigned int	decode_args_uint	(char const * & args_p) const;
			inline bool			decode_args_bool	(char const * & args_p) const;
			inline bool			decode_args_word	(char const * & args_p, char * word_p, unsigned int word_max_len) const;
			inline char			decode_args_char	(char const * & args_p) const;

#			define FEEDOS_BRIDGE_INTERFACE_CMD(CMD, NAME, ARGS) bool decode_cmd_token_##NAME (char const * args_p, unsigned int args_len, char const expected_arguments[]);
#			include "TextBridgeInterface_cmd.hpp"

		};

	}
}

#endif
