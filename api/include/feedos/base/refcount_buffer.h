
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_REF_COUNT_BUFFER_H
#define FEEDOS_BASE_REF_COUNT_BUFFER_H

#ifndef FEEDOS_COMPAT_INCLUDE
#	include "lock.h"
#endif

#include <string>
#include <iostream>
#include <cstring>

namespace FeedOS
{
	class refcount_buffer
	{
	private:
		class shared_buffer
		{
			void operator=(shared_buffer const &);	// dummy stuff
			shared_buffer (shared_buffer const &);	// dummy stuff

			// data members
			mutable	LockedCounter	m_count;
			void *					m_ptr;
			size_t					m_allocated_length;
			size_t					m_valid_length;

			void log_error_destructor() const;
			void log_error_nonconst() const;

			inline void assign (void const * p, size_t l)
			{
				resize (l);
				std::memcpy (m_ptr, p, l);
			}

		public:
			inline shared_buffer () : m_count (1), m_ptr(0), m_allocated_length(0), m_valid_length(0) {}
			inline shared_buffer (void const * p, size_t l) : m_count (1), m_ptr(0) { assign (p,l); }

			inline ~shared_buffer ()
			{
#ifdef _DEBUG
				if (m_count!=0) {
					log_error_destructor();
				}
#endif			
				clear();
			}

			inline unsigned int		get_count() const { return m_count; }
			inline void				inc_count() const { ++m_count; }
			inline void				dec_count() const 
			{
				if (--m_count==0) {
					delete this;
				}
			}

			inline size_t	capacity() const { return m_allocated_length; }
			inline size_t	size () const { return m_valid_length; }
			inline void		get_read_access (void const * & p, size_t & l) const { p=m_ptr; l=m_valid_length; }
			inline void		get_write_access (void * & p, size_t & l)
			{
#ifdef _DEBUG
				if (1!=m_count) {
					log_error_nonconst();
				}
#endif
				p=m_ptr; 
				l=m_valid_length;
			}

			inline void * resize (size_t l)
			{
				if (0==m_ptr) {
					m_ptr = new char [m_allocated_length=l];						
				} else {
					if (m_allocated_length < l) {
						char * old_ptr = (char *)m_ptr;
						m_ptr = new char [m_allocated_length=l];
						std::memcpy (m_ptr, old_ptr, m_valid_length);
						delete[] old_ptr;
					}
				}
				m_valid_length=l;
				return m_ptr;
			}

			inline void * reset (size_t l)
			{
				if (0==m_ptr) {
					m_ptr = new char [m_allocated_length=l];						
				} else {
					if (m_allocated_length < l) {
						delete[] (char*)m_ptr;
						m_ptr = new char [m_allocated_length=l];
					}
				}
				m_valid_length=l;
				return m_ptr;
			}

			inline void clear()
			{
				if (0!=m_ptr) {
					delete[] (char*)m_ptr;
					m_ptr=0;
					m_allocated_length=m_valid_length=0;
				}
			}

			bool operator== (const shared_buffer & s) const
			{
				return m_ptr==s.m_ptr;
			}

		};	// class shared_buffer

		shared_buffer *		m_ptr;

		inline void do_copy_on_write()
		{
			if (0==m_ptr) {
				// allocate a new string to write to
				m_ptr=new shared_buffer;
			} else if (m_ptr->get_count()>1) {
				// make a copy 
				void const * p;
				size_t l;
				m_ptr->get_read_access (p,l);
				shared_buffer * old_ptr = m_ptr;
				m_ptr=new shared_buffer (p,l);
				old_ptr->dec_count();
			} else {
				// refcount==1, can safely write to the string
			}
		}

		inline void do_release_shared_buffer()
		{
			if (m_ptr) {
				m_ptr->dec_count();
				m_ptr=0;
			}
		}

	public:

		inline size_t	capacity() const
		{
			return (m_ptr) ? m_ptr->capacity() : 0;
		}

		inline size_t	size () const 
		{
			return (m_ptr) ? m_ptr->size() : 0;
		}

		inline void	get_read_access (void const * & p, size_t & l) const 
		{
			if (m_ptr) {
				return m_ptr->get_read_access(p,l);
			} else {
				p=0; l=0; 
			}
		}

		inline void	get_write_access (void * & p, size_t & l)
		{
			if (m_ptr) {
				do_copy_on_write();
				return m_ptr->get_write_access(p,l);
			} else {
				p=0; l=0; 
			}
		}

		inline ~refcount_buffer()
		{
			do_release_shared_buffer();	// smart pointer "auto-deallocate"
		}

		// optimized "operation on twin"
		inline refcount_buffer (refcount_buffer const & s)
			: m_ptr (s.m_ptr)
		{
			if (m_ptr) {
				m_ptr->inc_count();	// buffer sharing
			}
		}

		// constructors (same as std::string)
		inline refcount_buffer () : m_ptr(0) {}
		inline refcount_buffer (void const * p, size_t l) : m_ptr(new shared_buffer (p,l)) {}
		inline refcount_buffer (std::string const & s) : m_ptr(new shared_buffer (s.data(), s.length())) {}

		// optimized
		bool empty() const
		{
			if (!m_ptr)
				return true;
			void const * p;
			size_t l;
			m_ptr->get_read_access (p,l);
			return 0==l;
		}

		bool operator== (const refcount_buffer & s) const
		{
			if (m_ptr==s.m_ptr) return true;
			if (!m_ptr || !s.m_ptr) return false;
            return *m_ptr == *s.m_ptr;
		}

		refcount_buffer & operator= (const refcount_buffer & s) 	 
		{
			assign(s);
			return *this;
		}

		// optimized "operation on twin"
		void assign (const refcount_buffer & s)
		{
			if (m_ptr!=s.m_ptr) {
				do_release_shared_buffer();
				if (0!=s.m_ptr) {
					s.m_ptr->inc_count();	// buffer sharing
					m_ptr=s.m_ptr;
				}
			}
		}

		// assign (copy) a buffer
		void assign (void const * p, size_t l)
		{
			do_release_shared_buffer();
			m_ptr = new shared_buffer (p,l);
		}

		// resize the buffer (keeps current data)
		void * resize (size_t n)
		{
			do_copy_on_write();
			return m_ptr->resize(n); 
		}

		// resize the buffer (trash current data)
		void * reset (size_t n)
		{
			do_copy_on_write();
			return m_ptr->reset(n); 
		}

		// optimized "operation on twin"
		void swap (refcount_buffer & s) 	 
		{
			std::swap (m_ptr, s.m_ptr);
		}

		// optimized
		void clear()
		{
			do_release_shared_buffer();
		}

	};

}


std::ostream & operator<< (std::ostream & os, FeedOS::refcount_buffer const & b);


#endif
