/**
FILE NAME= hl_ccyCode.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131210
*/


#include <hl/currencies/hl_ccyCode.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLCCY::HL_CcyCode);

namespace HorizonLib
{
	namespace HL_Currencies
	{

		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_CcyCode
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		HL_CcyCode::HL_CcyCode()
		{
			classDefaultInit();

		} // end HL_CcyCode

		//------------------------------------------------------------------------------------------------------

		HL_CcyCode::~HL_CcyCode()
		{
		} // end ~HL_CcyCode

		//------------------------------------------------------------------------------------------------------

		void HL_CcyCode::classDefaultInit()
		{

		} // end classDefaultInit
		//------------------------------------------------------------------------------------------------------

		HLSTRING HL_CcyCode::objTypeImpl() const
		{
			return "HL_CcyCode";
		} // end objTypeImpl

	} // end namespace HL_Currencies
} //end namespace HorizonLib
