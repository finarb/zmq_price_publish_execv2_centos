
/************************************/
/** FeedOS                         **/
/**                                **/
/** copyright QuantHouse 2007      **/
/** Author: Denery Fenouil         **/
/************************************/

#ifndef FEEDOS_TEXT_BRIDGE_WRITER_H
#define FEEDOS_TEXT_BRIDGE_WRITER_H

#include "TextBridgeInterface.h"
#include <iostream>

namespace FeedOS {

	namespace TextBridge {

		class Writer
			: public Interface
		{
			typedef Writer	Me;
		public:
			Writer (std::ostream & output);

#			define FEEDOS_BRIDGE_INTERFACE_CMD(CMD, NAME, ARGS) virtual void bridge_cmd_##NAME ARGS;
#			include "TextBridgeInterface_cmd.hpp"

		protected:

			inline void push_price (double price);

			void push_blank () { m_output << char_TOKEN_SEPARATOR; }

			template <typename T>
			void push (T v) { m_output << v; }

			template <typename T>
			void push_and_blank (T v) { m_output << v << char_TOKEN_SEPARATOR; }

			inline void push_endl () { m_output << char_LINE_SEPARATOR; }

		private:
			std::ostream &		m_output;
		};

	}
}

#endif
