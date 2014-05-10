/**
FILE NAME= baseIns.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131109
*/


#include <hl/instruments/hl_baseIns.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_Instrument);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_InstrumentCode);

namespace HorizonLib
{
	namespace HL_Instruments
	{


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_InstrumentCode
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		HL_InstrumentCode::HL_InstrumentCode()
		{
			classDefaultInit();

		} // end HL_InstrumentCode

		//------------------------------------------------------------------------------------------------------

		HL_InstrumentCode::~HL_InstrumentCode()
		{
		} // end ~HL_InstrumentCode

		//------------------------------------------------------------------------------------------------------

		void HL_InstrumentCode::classDefaultInit()
		{

		} // end classDefaultInit
		//------------------------------------------------------------------------------------------------------

		HLSTRING HL_InstrumentCode::objTypeImpl() const
		{
			return "HL_InstrumentCode";
		} // end objTypeImpl


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_Instrument
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		HL_Instrument::HL_Instrument()
		{

			classDefaultInit();

			

		} // end HL_Instrument

		//------------------------------------------------------------------------------------------------------

		HL_Instrument::~HL_Instrument()
		{
		} // end ~HL_Instrument


		//------------------------------------------------------------------------------------------------------

		void HL_Instrument::classDefaultInit()
		{

		} // end classDefaultInit
					
		
		//------------------------------------------------------------------------------------------------------

		void HL_Instrument::descriptionImpl(std::ostream & os) const
		{
			HLOBJ::HL_FinObj::descriptionImpl(os);
			
		} // end descriptionImpl

	} // end namespace HL_Instruments
} //end namespace HorizonLib
