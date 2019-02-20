
/************************************/
/** FeedOS C++ Client API          **/
/**                                **/
/** copyright QuantHouse 2003-2007 **/
/**                                **/
/************************************/

#ifndef FEEDOS_BASE_SMART_PTR_H
#define FEEDOS_BASE_SMART_PTR_H

#ifndef FEEDOS_BASE_LOCK_H
#  include "lock.h"
#endif

namespace FeedOS {

	/** a ref-counting, auto-dealloc generic pointer class */
	template <class T>
	class smart_ptr
	{
		class control_block {
		public:
			inline control_block (T* ptr) : m_count (1), m_ptr (ptr) {}
			inline void	inc_ref()		{ ++m_count; }
			inline void	dec_ref()		{ if (0==--m_count) { delete m_ptr;	delete this; } }
			inline T*	ptr() const 	{ return m_ptr; }
		private:
			LockedCounter m_count;
			T* m_ptr;
		} * m_control_block;
	public:
		/// build a smart pointer from a C++ pointer
		inline explicit smart_ptr (T* ptr) : m_control_block (ptr?new control_block (ptr):NULL) {}

		/// copy constructor
		inline smart_ptr (smart_ptr<T> const & p)	{ if ((m_control_block = p.m_control_block)) m_control_block->inc_ref(); }

		/// default constructor
		inline smart_ptr () : m_control_block (NULL) {}

		/// "exchange assignment"
		inline void swap (smart_ptr<T> & p)
		{ 
			class control_block * temp = m_control_block;
			m_control_block = p.m_control_block;
			p.m_control_block = temp;
		}

		/// assignement
		inline smart_ptr<T> const & operator= (smart_ptr<T> const & p)
		{
			if (m_control_block != p.m_control_block) {
				if (m_control_block)						m_control_block->dec_ref();
				if ((m_control_block = p.m_control_block))	m_control_block->inc_ref();
			}
			return *this;
		}

		/// destructor: decrement reference, and dealloc if needed
		/** @warning for performance reasons, destructor is NOT virtual */
		inline ~smart_ptr ()	{ if (m_control_block) m_control_block->dec_ref(); }

	public:

		/** @name comparison */
		//@{
		inline bool operator== (smart_ptr<T> const & p) const	{ return (m_control_block == p.m_control_block); }	// { return ptr() == pt);	}
		inline bool operator!= (smart_ptr<T> const & p) const	{ return (m_control_block != p.m_control_block); }	// { return ptr() != pt);	}
		inline bool operator<  (smart_ptr<T> const & p) const	{ return (m_control_block  < p.m_control_block); }	// { return ptr()  < pt);	}

		inline bool is_null () const { return 0==m_control_block; }

		/// this allows to use a smart_ptr as a conditional expression : if (my_smart_ptr) {...}
		inline operator bool	() const { return 0!=m_control_block; }
		inline bool operator!	() const { return 0==m_control_block; }

		//@}

		/** @name dereferencing */
		//@{
		inline T *	ptr () const	{ return  (m_control_block == NULL) ? NULL : m_control_block->ptr(); }
		inline operator T *	() const	{ return  ptr (); }
		inline T *	operator->	() const	{ return  m_control_block->ptr(); }
		inline T &	operator*	() const	{ return *m_control_block->ptr(); }
		//@}

	};



	class reference_counter
	{
	public:
		inline virtual ~reference_counter () {}
		inline reference_counter () : m_reference_count (0) {}
		inline unsigned int	inc_reference_counter()	const	{ return ++m_reference_count; }
		inline unsigned int	dec_reference_counter()	const	{ return --m_reference_count; }
		virtual void pre_destructor () {}	// called by smart_ptr2 BEFORE delete
	private:
		mutable LockedCounter m_reference_count;
	};


	/** a ref-counting, auto-dealloc generic pointer class. Parameter Type should inherit from reference_counter */
	template <class T>
	class smart_ptr2
	{
	public:

		/// build a smart pointer from a C++ pointer
		inline explicit smart_ptr2 (T* ptr)	{ if ((m_ptr=ptr)) m_ptr->inc_reference_counter(); }

		/// copy constructor
		inline smart_ptr2 (smart_ptr2<T> const & p)	{ if ((m_ptr=p.m_ptr)) m_ptr->inc_reference_counter(); }

		/// default constructor
		inline smart_ptr2 () : m_ptr (NULL) {}

		/// "exchange assignment"
		inline void swap (smart_ptr2<T> & p)
		{ 
			T * temp = m_ptr;
			m_ptr = p.m_ptr;
			p.m_ptr = temp;
		}

		/// assignement
		inline smart_ptr2<T> const & operator= (T * p)
		{
			if (m_ptr != p) {
				dec_ref_and_delete_if_needed();
				if ((m_ptr=p))	m_ptr->inc_reference_counter();
			}
			return *this;
		}
		inline smart_ptr2<T> const & operator= (smart_ptr2<T> const & p)
		{
			return operator= (p.m_ptr);
		}


		/// destructor: decrement reference, and dealloc if needed
		/** @warning for performance reasons, destructor is NOT virtual */
		inline ~smart_ptr2 ()	{ dec_ref_and_delete_if_needed(); }

	public:

		/** @name comparison */
		//@{
		inline bool operator== (smart_ptr2<T> const & p) const	{ return (m_ptr == p.m_ptr); }
		inline bool operator!= (smart_ptr2<T> const & p) const	{ return (m_ptr != p.m_ptr); }
		inline bool operator<  (smart_ptr2<T> const & p) const	{ return (m_ptr  < p.m_ptr); }

		inline bool is_null () const { return 0==m_ptr; }

		/// this allows to use a smart_ptr2 as a conditional expression : if (my_smart_ptr) {...}
		inline operator bool	() const { return 0!=m_ptr; }
		inline bool operator!	() const { return 0==m_ptr; }

		//@}

		/** @name dereferencing */
		//@{
		inline T *	ptr () const			{ return  m_ptr; }
		inline operator T *	() const		{ return  m_ptr; }
		inline T *	operator->	() const	{ return  m_ptr; }
		inline T &	operator*	() const	{ return *m_ptr; }
		//@}

	private:

		void dec_ref_and_delete_if_needed()
		{
			if (m_ptr && (0==m_ptr->dec_reference_counter())) {
				m_ptr->pre_destructor();
				delete m_ptr;
			}
		}

		T * m_ptr;
	};


}

#endif
