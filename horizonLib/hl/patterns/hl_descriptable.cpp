/**
FILE NAME= hl_descriptable.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131218
*/
#include <hl/patterns/hl_descriptable.h>


namespace HorizonLib
{

	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	// class Descriptable
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------


	Descriptable::Descriptable()
	{
		classDefaultInit();

	} // end Descriptable

	//------------------------------------------------------------------------------------------------------

	Descriptable::~Descriptable()
	{
	} // end ~Descriptable

	//------------------------------------------------------------------------------------------------------

	void Descriptable::classDefaultInit()
	{

	} // end classDefaultInit



	//------------------------------------------------------------------------------------------------------

	HLSTRING Descriptable::description() const
	{

		std::stringstream ss;

		description(ss);

		return ss.str();

	} // end description

	//------------------------------------------------------------------------------------------------------

	void Descriptable::description(std::ostream & os) const
	{

		os << "\n DES START{* ptr=(" << this << ")\n"; // write the address

		descriptionImpl(os);

		os << "DES END ptr=(" << this << ") *}" << "\n"; // write the address

	} // end description

	//------------------------------------------------------------------------------------------------------

	void Descriptable::descriptionImpl(std::ostream & os) const
	{
		return;
	} // end descriptionImpl
	
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	// class Descriptable:: defines, typedefs, functions
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	

	std::ostream& operator<<(std::ostream& os, const Descriptable& descriptable)
	{
	
		descriptable.description(os);
	
		return os;
	} // end operator<<

	//------------------------------------------------------------------------------------------------------
	

	std::ostream& operator<<(std::ostream& os, const BSP<Descriptable>& descriptable)
	{
	
        if(!descriptable)
            return os << "null shared_ptr to obj deriving from Descriptable";
			
		return os << (*descriptable);

	} // end operator<<
} //end namespace HorizonLib
