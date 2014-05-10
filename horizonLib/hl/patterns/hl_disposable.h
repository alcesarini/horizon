/**
FILE NAME= hl_disposable.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131230
*/
#ifndef _hl_disposable_h_
#define _hl_disposable_h_

#include <hl/basicFiles/hl_basicIncludes.h>

namespace HorizonLib
{


	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	// class HL_Disposable
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------

	/**
	\author A. Cesarini
	\date 20131230
	\brief generic disposable object with move semantics (from QL 1.3).
	This class can be used for returning a value by copy. It relies
	on the returned object exposing a <tt>swap(T\&)</tt> method through
	which the copy constructor and assignment operator are implemented,
	thus resulting in actual move semantics. Typical use of this
	class is along the following lines:
	\code
	HL_Disposable<Foo> bar(Integer i) {
	Foo f(i*2);
	return f;
	}
	\endcode

	\warning In order to avoid copies in code such as shown above,
	the conversion from <tt>T</tt> to <tt>HL_Disposable\<T\></tt>
	is destructive, i.e., it does <b>not</b> preserve the
	state of the original object. Therefore, it is necessary
	for the developer to avoid code such as
	\code
	HL_Disposable<Foo> bar(Foo& f) {
	return f;
	}
	\endcode
	which would likely render the passed object unusable.
	The correct way to obtain the desired behavior would be:
	\code
	HL_Disposable<Foo> bar(Foo& f) {
	Foo temp = f;
	return temp;
	}
	\endcode
	*/
	template <class T>
	class HL_Disposable : public T 
	{
	public:
		HL_Disposable(T& t);
		HL_Disposable(const HL_Disposable<T>& t);
		HL_Disposable<T>& operator=(const HL_Disposable<T>& t);
	};


	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	// class HL_Disposable: inline definitions
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------

	template <class T>
	inline HL_Disposable<T>::HL_Disposable(T& t) 
	{
		this->swap(t);
	} // end HL_Disposable
	//------------------------------------------------------------------------------------------------------

	template <class T>
	inline HL_Disposable<T>::HL_Disposable(const HL_Disposable<T>& t) : T() 
	{
		this->swap(const_cast<HL_Disposable<T>&>(t));
	} // end HL_Disposable
	//------------------------------------------------------------------------------------------------------

	template <class T>
	inline HL_Disposable<T>& HL_Disposable<T>::operator=(const HL_Disposable<T>& t) 
	{
		this->swap(const_cast<HL_Disposable<T>&>(t));
		return *this;
	} // end operator=
	//------------------------------------------------------------------------------------------------------

} //end namespace HorizonLib


#endif // _hl_disposable_h_
