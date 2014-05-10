/**
FILE NAME= hl_objectCode.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131208
*/
#include <hl/object/hl_objectCode.h>



namespace HorizonLib
{
	namespace HL_Object
	{


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_ObjCode
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		HL_ObjCode::HL_ObjCode()
		{
			classDefaultInit();

		} // end HL_ObjCode

		//------------------------------------------------------------------------------------------------------

		HL_ObjCode::~HL_ObjCode()
		{
		} // end ~HL_ObjCode
			
		
		//------------------------------------------------------------------------------------------------------

		void HL_ObjCode::classDefaultInit()
		{
			nCode_=HL_NULL_INTEGER;

		} // end classDefaultInit
		


		//------------------------------------------------------------------------------------------------------

		HLSTRING HL_ObjCode::objType() const
		{
			return objTypeImpl();

		} // end objType

		//------------------------------------------------------------------------------------------------------

		HL_Order HL_ObjCode::getOrder(const HL_ObjCode & hl_ObjCode) const
		{

			HL_PLAIN_ORDER_COMPARE(nCode_, hl_ObjCode.nCode_);

			HL_PLAIN_ORDER_COMPARE(sCode_, hl_ObjCode.sCode_);

			return HL_Order_1_Eq_2;

		} // end getOrder


		//------------------------------------------------------------------------------------------------------
		
		void HL_ObjCode::descriptionImpl(std::ostream & os) const
		{
		
			os << "HL_ObjCode= " << objType() << ":\n";
			Descriptable::descriptionImpl(os);
			hl_fillDescriptionStream(nCode_);
			hl_fillDescriptionStream(sCode_);

		} // end descriptionImpl







	} // end namespace HL_Object
} //end namespace HorizonLib