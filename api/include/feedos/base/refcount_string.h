
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_REF_COUNT_STRING_H
#define FEEDOS_BASE_REF_COUNT_STRING_H

#ifndef FEEDOS_BASE_BASE_H
#  include "base.h"  //FEEDOS_STLEXT_NAMESPACE
#endif


#ifndef FEEDOS_COMPAT_INCLUDE
#	include "lock.h"
#endif

#include <string>
#include <iostream>

#if defined TARGET_PLATFORM_WIN32//Oliver-Nov07
#	define FEEDOS_DISABLE_REFCOUNT_STRING	0
#else
#	define FEEDOS_DISABLE_REFCOUNT_STRING	1
#endif

#if FEEDOS_DISABLE_REFCOUNT_STRING

namespace FeedOS
{
	class refcount_string : public std::string
	{
	public:
		inline refcount_string (refcount_string const & s) :
			std::string(s)
		{
		}

		inline std::string const &	const_str() const	{ return *this; }
		inline std::string &		nonconst_str()		{ return *this; }

		// constructors (same as std::string)
		typedef char	charT;	// TODO make this a template parameter (along with "traits" and "Alloc")
		inline refcount_string () { }
		inline /*explicit*/ refcount_string (std::string const & s, size_type pos = 0, size_type n = npos) : std::string(s, pos, n) {}
		inline /*explicit*/ refcount_string (charT const *s) : std::string(s) {}
		inline /*explicit*/ refcount_string (charT const *s, size_type n) : std::string(s,n) {}
		inline /*explicit*/ refcount_string (size_type n, charT c) : std::string(n,c) {}
		template <class InputIterator>
		inline /*explicit*/ refcount_string (InputIterator first, InputIterator last) : std::string(first,last) {}

#ifdef FEEDOS_COMPAT_INCLUDE
		struct hash
		{
			inline size_t operator() (FeedOS::refcount_string const & s) const { return s.get_hash(); }
		};

		inline size_t get_hash() const
		{
			FEEDOS_STLEXT_NAMESPACE::hash<std::string> h;
			return h(const_str());
		}
#endif
		//TODO Oliver-Nov07: constructors must be explicit,
		// and therefore, the following functions must be implemented
		// refcount_string & operator= (const refcount_string & s)
		// refcount_string & operator= (const std::string & s)
		// refcount_string & operator= (const charT* s)
		// refcount_string & operator= (charT c)
	};
}

#else

namespace FeedOS
{

	class refcount_string
	{
	private:
		class shared_string
		{
			void operator=(shared_string const &);	// dummy stuff
			shared_string (shared_string const &);	// dummy stuff

			// data members
			mutable	LockedCounter	m_count;
					std::string		m_str;

			void log_error_destructor() const;
			void log_error_nonconst() const;

		public:
			typedef std::string::size_type size_type;

			inline shared_string () : m_count (1) {}
			inline explicit shared_string (std::string const & s, size_type pos = 0, size_type n = npos) : m_count (1), m_str (s,pos,n) {}
			inline explicit shared_string (char const * s) : m_count (1), m_str(s) {}
			inline explicit shared_string (char const * s, size_type n) : m_count (1), m_str(s,n) {}
			inline explicit shared_string (size_type n, char c) : m_count (1), m_str(n,c) {}
			template <class InputIterator>
			inline explicit shared_string (InputIterator first, InputIterator last) : m_count (1), m_str(first,last) {}

			inline ~shared_string ()
			{
#ifdef _DEBUG
				if (m_count!=0) {
					log_error_destructor();
				}
#endif			
			}

			inline unsigned int		get_count() const { return m_count; }
			inline void inc_count() const { ++m_count; }
			inline void dec_count() const 
			{
				if (--m_count==0) {
					delete this;
				}
			}
			inline std::string const &	const_str() const { return m_str; }
			inline std::string &		nonconst_str()
			{
#ifdef _DEBUG
				if (1!=m_count) {
					log_error_nonconst();
				}
#endif
				return m_str; 
			}
		};

		// data member
		shared_string	* m_ptr;

		// global member for "empty value"
		static std::string const s_empty_string;

		void log_error_global_empty_string() const;

		inline void do_copy_on_write()
		{
			if (0==m_ptr) {
				// allocate a new string to write to
				m_ptr=new shared_string;
			} else if (m_ptr->get_count()>1) {
				// make a copy 
				shared_string * old_ptr = m_ptr;
                m_ptr=new shared_string (old_ptr->const_str());
				old_ptr->dec_count();
			} else {
				// refcount==1, can safely write to the string
			}
		}

		inline void do_release_shared()
		{
			if (m_ptr) {
				m_ptr->dec_count();
			}
		}

	public:
		inline std::string const & const_str() const
		{
			if (m_ptr) {
				return m_ptr->const_str();
			} else {
#ifdef _DEBUG
				if (!s_empty_string.empty()) {
					log_error_global_empty_string();
				}
#endif
				return s_empty_string; 
			}
		}

		inline std::string & nonconst_str()
		{
			do_copy_on_write();
			return m_ptr->nonconst_str();
		}

		// zut alors : global operators == and < does not work when called from STL
		inline bool operator== (FeedOS::refcount_string const & s) const
		{
			if (s.m_ptr==m_ptr) {
				return true;
			} else {
	            return s.const_str() == const_str();
			}
		}

		inline bool operator< (FeedOS::refcount_string const & s) const
		{
			return const_str() < s.const_str();
		}


#ifdef FEEDOS_COMPAT_INCLUDE
		inline size_t get_hash() const
		{
			if (0==m_ptr) {
				return 0;
			} else {
				FEEDOS_STLEXT_NAMESPACE::hash<std::string> h;
				return h(const_str());
			}
		}

		struct hash
		{
			inline size_t operator() (FeedOS::refcount_string const & s) const { return s.get_hash(); }
		};
#endif

		typedef char	charT;	// TODO make this a template parameter (along with "traits" and "Alloc")

		typedef std::string::value_type				value_type				; 
		typedef std::string::pointer 				pointer 				; 
		typedef std::string::reference 				reference 				; 
		typedef std::string::const_reference 		const_reference 		; 	
		typedef std::string::size_type 				size_type 				; 
		typedef std::string::difference_type 		difference_type 		; 	
		typedef std::string::iterator 				iterator 				; 
		typedef std::string::const_iterator 		const_iterator 			; 
		typedef std::string::reverse_iterator 		reverse_iterator 		; 	
		typedef std::string::const_reverse_iterator	const_reverse_iterator	; 
		static const size_type npos = ~(size_t)0;//std::string::npos;

		inline ~refcount_string()
		{
			do_release_shared();	// smart pointer "auto-deallocate"
		}

		// optimized "operation on twin"
		inline /*explicit*/ refcount_string (refcount_string const & s) :
			m_ptr (s.m_ptr)
		{
			m_ptr->inc_count();	// buffer sharing
		}

		// constructors (same as std::string)
		inline /*explicit*/ refcount_string () : m_ptr(0) {}
		inline explicit refcount_string (std::string const & s, size_type pos = 0, size_type n = npos) : m_ptr(new shared_string (s, pos, n)) {}
		inline explicit refcount_string (charT const *s) : m_ptr(new shared_string (s)) {}
		inline explicit refcount_string (charT const *s, size_type n) : m_ptr(new shared_string (s,n)) {}
		inline explicit refcount_string (size_type n, charT c) : m_ptr(new shared_string (n,c)) {}
		template <class InputIterator>
		inline explicit refcount_string (InputIterator first, InputIterator last) : m_ptr(new shared_string (first,last)) {}

		iterator begin()								{ do_copy_on_write(); return m_ptr->nonconst_str().begin(); }
		iterator end() 									{ do_copy_on_write(); return m_ptr->nonconst_str().end(); }						
		const_iterator begin() const					{ return const_str().begin(); }		
		const_iterator end() const 						{ return const_str().end(); }						
		reverse_iterator rbegin() 						{ do_copy_on_write(); return m_ptr->nonconst_str().rbegin(); }				
		reverse_iterator rend() 						{ do_copy_on_write(); return m_ptr->nonconst_str().rend(); }				
		const_reverse_iterator rbegin() const			{ return const_str().rbegin(); }	 	
		const_reverse_iterator rend() const  			{ return const_str().rend(); }		
		size_type size() const 	 						{ return const_str().size(); }						
		size_type length() const 	 					{ return const_str().length(); }					
		size_type max_size() const  					{ return const_str().max_size(); }						
		size_type capacity() const 	 					{ return const_str().capacity(); }					

		// optimized
		bool empty() const
		{
			return m_ptr?(const_str().empty()):true; 
		}

		reference operator[](size_type n)				{ do_copy_on_write(); return m_ptr->nonconst_str()[n]; }
		const_reference operator[](size_type n) const 	{ return const_str()[n]; }

#if 0
		// least safe version : re-casting into char* exposes the shared buffer)
		const charT* c_str() const 					 	{ return const_str().c_str(); }		
		const charT* data() const 					 	{ return const_str().data(); }	
#elif 0
		// safer version : doing on-the-fly casting of c_str() into char* calls copy_on_write()
		class _nonconst_cast_checker
		{
			refcount_string const & m_s;
		public:
			_nonconst_cast_checker (refcount_string const & s) : m_s (s) {}

			// TODO: make it work
			operator char const *	() const	{ return													m_s		.const_str()	.c_str(); }
			operator char *			()			{ return (refcount_string::charT *)	(((refcount_string &)	m_s)	.nonconst_str()	.c_str()); }
		};

		// TODO: have 2 intermediate classes: one for C_STR(), one for DATA()
		_nonconst_cast_checker	c_str() const 					 	{ return _nonconst_cast_checker(*this); }		
		_nonconst_cast_checker	data() const 					 	{ return _nonconst_cast_checker(*this); }	
#else
		// most conservative version (casting this into char[const]* calls copy_on_write()
		const charT* c_str() const 					 	{ return ((refcount_string *)this)->nonconst_str().c_str(); }		
		const charT* data() const 					 	{ return ((refcount_string *)this)->nonconst_str().data(); }	
#endif
		operator std::string const &	() const	{ return const_str(); }
		operator std::string &			()			{ do_copy_on_write(); return m_ptr->nonconst_str(); }


		// optimized "operation on twin"
		refcount_string & operator= (const refcount_string & s) 	 
		{
			if (m_ptr!=s.m_ptr) {
				do_release_shared();
				if (0==s.m_ptr) {
					m_ptr=0;
				} else {
					m_ptr=s.m_ptr;
					m_ptr->inc_count();	// buffer sharing
				}
			}
			return *this;
		}

		refcount_string & operator= (const std::string & s) 	 
		{
			do_release_shared();
			m_ptr = new shared_string (s);
			return *this;
		}

		refcount_string & operator= (const charT* s)
		{
			do_release_shared();
			m_ptr = new shared_string (s);
			return *this;
		}

		refcount_string & operator= (charT c) 
		{
			do_release_shared();
			m_ptr = new shared_string (1,c);
			return *this;
		}

		void reserve (size_t n)			{ do_copy_on_write(); m_ptr->nonconst_str().reserve(n); }

		// optimized "operation on twin"
		void swap (refcount_string & s) 	 
		{
			std::swap (m_ptr, s.m_ptr);
		}

		void swap (std::string & s) 					{ do_copy_on_write(); m_ptr->nonconst_str().swap(s); }

		iterator insert(iterator pos, const charT & x) 	{ do_copy_on_write(); return m_ptr->nonconst_str().insert(pos,x); }

		template <class InputIterator>
		void insert(iterator pos, InputIterator f, InputIterator l)			 { do_copy_on_write(); m_ptr->nonconst_str().insert(pos,f,l); }

		void insert(iterator pos, size_type n, const charT & x)				{ do_copy_on_write(); m_ptr->nonconst_str().insert(pos,n,x); }

		refcount_string& insert(size_type pos, const std::string & s)		{ do_copy_on_write(); m_ptr->nonconst_str().insert(pos,s); return *this; }

		refcount_string& insert(size_type pos, 
							const std::string& s, 
							size_type pos1, size_type n)					{ do_copy_on_write(); m_ptr->nonconst_str().insert(pos,s,pos1,n); return *this; }

		refcount_string& insert(size_type pos, const charT* s) 				{ do_copy_on_write(); m_ptr->nonconst_str().insert(pos,s); return *this; }
		refcount_string& insert(size_type pos, const charT* s, size_type n) { do_copy_on_write(); m_ptr->nonconst_str().insert(pos,s,n); return *this; }	
		refcount_string& insert(size_type pos, size_type n, charT c)		{ do_copy_on_write(); m_ptr->nonconst_str().insert(pos,n,c); return *this; }
		refcount_string& append(const std::string& s) 						{ do_copy_on_write(); m_ptr->nonconst_str().append(s); return *this; }

		refcount_string& append(const std::string& s, 
							size_type pos, size_type n)						{ do_copy_on_write(); m_ptr->nonconst_str().append(s,pos,n); return *this; }

		refcount_string& append(const charT* s) 							{ do_copy_on_write(); m_ptr->nonconst_str().append(s); return *this; }
		refcount_string& append(const charT* s, size_type n) 				{ do_copy_on_write(); m_ptr->nonconst_str().append(s,n); return *this; }
		refcount_string& append(size_type n, charT c) 						{ do_copy_on_write(); m_ptr->nonconst_str().append(n,c); return *this; }

		template <class InputIterator>
		refcount_string& append(InputIterator first, InputIterator last)	{ do_copy_on_write(); m_ptr->nonconst_str().append(first,last); return *this; }

		void push_back(charT c) 											{ do_copy_on_write(); m_ptr->nonconst_str().push_back(c); }
		refcount_string& operator+=(const std::string& s) 					{ do_copy_on_write(); m_ptr->nonconst_str() += s; return *this; }
		refcount_string& operator+=(const charT* s) 	 					{ do_copy_on_write(); m_ptr->nonconst_str() += s; return *this; }
		refcount_string& operator+=(charT c) 	 							{ do_copy_on_write(); m_ptr->nonconst_str() += c; return *this; }
		iterator erase(iterator p) 	 										{ do_copy_on_write(); return m_ptr->nonconst_str().erase (p); }
		iterator erase(iterator first, iterator last) 						{ do_copy_on_write(); return m_ptr->nonconst_str().erase (first,last); }
		refcount_string& erase(size_type pos = 0, size_type n = npos) 		{ do_copy_on_write(); m_ptr->nonconst_str().erase (pos,n); return *this; }

		// optimized
		void clear()
		{
			if (0==m_ptr) {
				// nothing to do
			} else if (m_ptr->get_count()==1) {
				// refcount==1, can safely write to the string
				m_ptr->nonconst_str().clear();
			} else {
				// detach from shared_string
				m_ptr->dec_count();
				m_ptr=0;
			}
		}

		void resize(size_type n, charT c = charT())  				{ do_copy_on_write(); m_ptr->nonconst_str().resize (n,c); }

		// optimized "operation on twin"
		refcount_string& assign(const refcount_string& s)			{ return this->operator=(s); }

		refcount_string& assign(const std::string& s)				{ return this->operator=(s); }

		 
		refcount_string& assign(const std::string& s, 
							size_type pos, size_type n)				{ do_copy_on_write(); m_ptr->nonconst_str().assign(s,pos,n); return *this; }

		refcount_string& assign(const charT* s, size_type n) 		{ do_copy_on_write(); m_ptr->nonconst_str().assign(s,n); return *this; }
		refcount_string& assign(const charT* s) 					{ do_copy_on_write(); m_ptr->nonconst_str().assign(s); return *this; }
		refcount_string& assign(size_type n, charT c) 				{ do_copy_on_write(); m_ptr->nonconst_str().assign(n,c); return *this; }

		template <class InputIterator>
		refcount_string& assign(InputIterator first, InputIterator last)
																	{ do_copy_on_write(); m_ptr->nonconst_str().assign(first,last); return *this; }

		refcount_string& replace(size_type pos, size_type n, 
							const std::string& s)					{ do_copy_on_write(); m_ptr->nonconst_str().replace(pos,n,s); return *this; }

		refcount_string& replace(size_type pos, size_type n, 
							const std::string& s, 
							size_type pos1, size_type n1)			{ do_copy_on_write(); m_ptr->nonconst_str().replace(pos,n,s,pos1,n1); return *this; }

		refcount_string& replace(size_type pos, size_type n, 
							const charT* s, size_type n1)			{ do_copy_on_write(); m_ptr->nonconst_str().replace(pos,n,s,n1); return *this; }

		refcount_string& replace(size_type pos, size_type n, 
							const charT* s)							{ do_copy_on_write(); m_ptr->nonconst_str().replace(pos,n,s); return *this; }

		refcount_string& replace(size_type pos, size_type n, 
							size_type n1, charT c)					{ do_copy_on_write(); m_ptr->nonconst_str().replace(pos,n,n1,c); return *this; }

		refcount_string& replace(iterator first, iterator last, 
							const std::string& s)					{ do_copy_on_write(); m_ptr->nonconst_str().replace(first,last,s); return *this; }

		refcount_string& replace(iterator first, iterator last, 
							const charT* s, size_type n)			{ do_copy_on_write(); m_ptr->nonconst_str().replace(first,last,s,n); return *this; }

		refcount_string& replace(iterator first, iterator last, 
							const charT* s)							{ do_copy_on_write(); m_ptr->nonconst_str().replace(first,last,s); return *this; }

		refcount_string& replace(iterator first, iterator last, 
							size_type n, charT c)					{ do_copy_on_write(); m_ptr->nonconst_str().replace(first,last,n,c); return *this; }

		template <class InputIterator>
		refcount_string& replace(iterator first, iterator last, 
							InputIterator f, InputIterator l)		{ do_copy_on_write(); m_ptr->nonconst_str().replace(first,last,f,l); return *this; }

		size_type copy(charT* buf, size_type n, size_type pos = 0) const					{ return const_str().copy(buf,n,pos); }		
		size_type find(const std::string& s, size_type pos = 0) const 						{ return const_str().find(s,pos); }	
		size_type find(const charT* s, size_type pos, size_type n) const 					{ return const_str().find(s,pos,n); }	
		size_type find(const charT* s, size_type pos = 0) const 							{ return const_str().find(s,pos); }	
		size_type find(charT c, size_type pos = 0) const 									{ return const_str().find(c,pos); }	
		size_type rfind(const std::string& s, size_type pos = npos) const					{ return const_str().rfind(s,pos); } 	
		size_type rfind(const charT* s, size_type pos, size_type n) const 					{ return const_str().rfind(s,pos,n); }	
		size_type rfind(const charT* s, size_type pos = npos) const 						{ return const_str().rfind(s,pos); }	
		size_type rfind(charT c, size_type pos = npos) const 								{ return const_str().rfind(c,pos); }	
		size_type find_first_of(const std::string& s, size_type pos = 0) const 				{ return const_str().find_first_of(s,pos); }	
		size_type find_first_of(const charT* s, size_type pos, size_type n) const			{ return const_str().find_first_of(s,pos,n); }
		size_type find_first_of(const charT* s, size_type pos = 0) const 					{ return const_str().find_first_of(s,pos); }
		size_type find_first_of(charT c, size_type pos = 0) const 							{ return const_str().find_first_of(c,pos); }
		size_type find_first_not_of(const std::string& s, size_type pos = 0) const 			{ return const_str().find_first_not_of(s,pos); }
		size_type find_first_not_of(const charT* s, size_type pos, size_type n) const 		{ return const_str().find_first_not_of(s,pos,n); }	
		size_type find_first_not_of(const charT* s, size_type pos = 0) const 				{ return const_str().find_first_not_of(s,pos); }
		size_type find_first_not_of(charT c, size_type pos = 0) const 						{ return const_str().find_first_not_of(c,pos); }	
		size_type find_last_of(const std::string& s, size_type pos = npos) const 			{ return const_str().find_last_of(s,pos); }
		size_type find_last_of(const charT* s, size_type pos, size_type n) const 			{ return const_str().find_last_of(s,pos,n); }
		size_type find_last_of(const charT* s, size_type pos = npos) const 					{ return const_str().find_last_of(s,pos); }
		size_type find_last_of(charT c, size_type pos = npos) const 						{ return const_str().find_last_of(c,pos); }
		size_type find_last_not_of(const std::string& s, size_type pos = npos) const 		{ return const_str().find_last_not_of(s,pos); }
		size_type find_last_not_of(const charT* s, size_type pos, size_type n) const 		{ return const_str().find_last_not_of(s,pos,n); }
		size_type find_last_not_of(const charT* s, size_type pos = npos) const 				{ return const_str().find_last_not_of(s,pos); }
		size_type find_last_not_of(charT c, size_type pos = npos) const 					{ return const_str().find_last_not_of(c,pos); }
		std::string substr(size_type pos = 0, size_type n = npos) const 					{ return const_str().substr(pos,n); }
		int compare(const std::string& s) const 											{ return const_str().compare(s); }
		int compare(size_type pos, size_type n, const std::string& s) const					{ return const_str().compare(pos,n,s); }
		int compare(size_type pos, size_type n, const std::string& s, size_type pos1, size_type n1) const
																							{ return const_str().compare(pos,n,s,pos1,n1); }
		int compare(const charT* s) const 													{ return const_str().compare(s); }								
		int compare(size_type pos, size_type n, const charT* s, size_type len = npos) const	{ return const_str().compare(pos,n,s,len); }

	};

}

// optimized
inline FeedOS::refcount_string
operator+(const FeedOS::refcount_string& s1,
          const FeedOS::refcount_string& s2)
{
	if (s1.empty()) {
		if (s2.empty()) {
			return FeedOS::refcount_string();
		} else {
			return s2;
		}
	} else {
		if (s2.empty()) {
			return s1;
		} else {
			return FeedOS::refcount_string (s1.const_str() + s2.const_str());
		}
	}
}


// optimized
template <class traits, class Alloc>
inline FeedOS::refcount_string
operator+(const FeedOS::refcount_string& s1,
		  const std::basic_string<FeedOS::refcount_string::charT, traits, Alloc>& s2)
{
	if (s1.empty()) {
		if (s2.empty()) {
			return FeedOS::refcount_string();
		} else {
			return s2;
		}
	} else {
		if (s2.empty()) {
			return s1;
		} else {
			return FeedOS::refcount_string (s1.const_str() + s2);
		}
	}
}

// optimized
template <class traits, class Alloc>
inline FeedOS::refcount_string
operator+(const std::basic_string<FeedOS::refcount_string::charT, traits, Alloc>& s1,
          const FeedOS::refcount_string& s2)
{
	if (s1.empty()) {
		if (s2.empty()) {
			return FeedOS::refcount_string();
		} else {
			return s2;
		}
	} else {
		if (s2.empty()) {
			return s1;
		} else {
			return FeedOS::refcount_string (s1 +  s2.const_str());
		}
	}
}

// optimized
inline FeedOS::refcount_string
operator+(const FeedOS::refcount_string::charT* s1,
          const FeedOS::refcount_string& s2)
{
	if (s2.empty()) {
		return FeedOS::refcount_string (s1);
	} else {
		return FeedOS::refcount_string (s1 + s2.const_str());
	}
}

// optimized
inline FeedOS::refcount_string
operator+(const FeedOS::refcount_string& s1,
		  const FeedOS::refcount_string::charT* s2)
{
	if (s1.empty()) {
		return FeedOS::refcount_string (s2);
	} else {
		return FeedOS::refcount_string (s1.const_str() + s2);
	}
}

// optimized
inline FeedOS::refcount_string
operator+(FeedOS::refcount_string::charT c,
          const FeedOS::refcount_string& s2)
{
	if (s2.empty()) {
		return FeedOS::refcount_string (1,c);
	} else {
		return FeedOS::refcount_string (c + s2.const_str());
	}
}

// optimized
inline FeedOS::refcount_string
operator+(const FeedOS::refcount_string& s1,
		  FeedOS::refcount_string::charT c)
{
	if (s1.empty()) {
		return FeedOS::refcount_string (1,c);
	} else {
		return FeedOS::refcount_string (s1.const_str() + c);
	}
}



// optimized
template <class traits, class Alloc>
bool operator==(	const std::basic_string<FeedOS::refcount_string::charT, traits, Alloc>& s1,
					const FeedOS::refcount_string & s2)
{
	if (s2.empty()) {
		return s1.empty();
	} else {
		if (s1.empty()) {
			return false;
		} else {
			return s2.const_str() == s1;
		}
	}
}

template <class traits, class Alloc>
bool operator!=(	const std::basic_string<FeedOS::refcount_string::charT, traits, Alloc>& s1,
					const FeedOS::refcount_string & s2)
{
	return ! (s1 == s2);
}

// optimized
template <class traits, class Alloc>
bool operator==(	const FeedOS::refcount_string & s2,
					const std::basic_string<FeedOS::refcount_string::charT, traits, Alloc> & s1)
{
	if (s2.empty()) {
		return s1.empty();
	} else {
		if (s1.empty()) {
			return false;
		} else {
			return s2.const_str() == s1;
		}
	}
}

template <class traits, class Alloc>
bool operator!=(	const FeedOS::refcount_string & s2,
					const std::basic_string<FeedOS::refcount_string::charT, traits, Alloc> & s1)
{
	return ! (s1 == s2);
}

/*
// optimized
inline bool operator==(	const FeedOS::refcount_string & s2,
						const FeedOS::refcount_string & s1)
{
	return s2.operator== (s1);
}
*/

inline bool operator!=(	const FeedOS::refcount_string & s2,
						const FeedOS::refcount_string & s1)
{
	return ! (s1 == s2);
}


inline bool operator==(	const FeedOS::refcount_string::charT * s1, 
						const FeedOS::refcount_string & s2)
{
	return s1 == s2.const_str();
}

inline bool operator!=(	const FeedOS::refcount_string::charT * s1, 
						const FeedOS::refcount_string & s2)
{
	return ! (s1 == s2);
}

inline bool operator==(	const FeedOS::refcount_string & s1,
						const FeedOS::refcount_string::charT * s2)
{
	return s1.const_str() == s2;
}

inline bool operator!=(	const FeedOS::refcount_string & s1,
						const FeedOS::refcount_string::charT * s2)
{
	return ! (s1 == s2);
}

/*
inline bool operator<(	const FeedOS::refcount_string & s1,
						 const FeedOS::refcount_string & s2)
{
	return s1.const_str() < s2.const_str();
}
*/

template <class traits, class Alloc>
bool operator<(std::basic_string<FeedOS::refcount_string::charT, traits, Alloc>& s1,
               const FeedOS::refcount_string & s2)
{
	return s1 < s2.const_str();
}

template <class traits, class Alloc>
bool operator<(const FeedOS::refcount_string & s1,
			   std::basic_string<FeedOS::refcount_string::charT, traits, Alloc>& s2)
{
	return s1.const_str() < s2;
}

inline bool operator<(const FeedOS::refcount_string::charT * s1,
               const FeedOS::refcount_string & s2)
{
	return s1 < s2.const_str();
}

inline bool operator<(const FeedOS::refcount_string & s1,
			   const FeedOS::refcount_string::charT * s2)
{
	return s1.const_str() < s2;
}

template <class traits, class Alloc>
void swap(std::basic_string<FeedOS::refcount_string::charT, traits, Alloc>& s1,
          FeedOS::refcount_string & s2)
{
	s1.swap(s2.nonconst_str());
}

template <class traits, class Alloc>
void swap(FeedOS::refcount_string & s1,
		  std::basic_string<FeedOS::refcount_string::charT, traits, Alloc>& s2)
{
	s2.swap(s1.nonconst_str());
}

template <class traits>
std::basic_istream<FeedOS::refcount_string::charT, traits>&
operator>>(std::basic_istream<FeedOS::refcount_string::charT, traits>& is,
           FeedOS::refcount_string & s)
{
	return is >> (s.nonconst_str());
}

// optimized
template <class traits>
std::basic_ostream<FeedOS::refcount_string::charT, traits>&
operator<<(std::basic_ostream<FeedOS::refcount_string::charT, traits>& os,
           const FeedOS::refcount_string & s)
{
	if (!s.empty()) {
		os << s.const_str();
	}
	return os;
}


template <class traits, class Alloc>
std::basic_istream<FeedOS::refcount_string::charT, traits>&
getline(std::basic_istream<FeedOS::refcount_string::charT, traits>& is,
        FeedOS::refcount_string & s,
        FeedOS::refcount_string::charT delim)
{
	return std::getline (is, s.nonconst_str(), delim);
}


template <class traits, class Alloc>
std::basic_istream<FeedOS::refcount_string::charT, traits>&
getline(std::basic_istream<FeedOS::refcount_string::charT, traits>& is,
        FeedOS::refcount_string & s)
{
	return std::getline (is, s.nonconst_str());
}

#endif


#endif
