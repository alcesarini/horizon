/**
FILE NAME= hl_mktData.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131214
*/
#include <hl/mktData/hl_mktData.h>
#include <hl/mktData/hl_mktDataCollector.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLMD::HL_MktData);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLMD::HL_MktDataCode);

namespace HorizonLib
{
	namespace HL_MarketData
	{


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_MktDataCode
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		HL_MktDataCode::HL_MktDataCode()
		{
			classDefaultInit();

		} // end HL_MktDataCode

		//------------------------------------------------------------------------------------------------------

		HL_MktDataCode::~HL_MktDataCode()
		{
		} // end ~HL_MktDataCode

		//------------------------------------------------------------------------------------------------------

		void HL_MktDataCode::classDefaultInit()
		{

		} // end classDefaultInit
		//------------------------------------------------------------------------------------------------------

		HLSTRING HL_MktDataCode::objTypeImpl() const
		{
			return "HL_MktDataCode";
		} // end objTypeImpl


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_MktData
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		HL_MktData::HL_MktData()
		{

			classDefaultInit();



		} // end HL_MktData

		//------------------------------------------------------------------------------------------------------

		HL_MktData::~HL_MktData()
		{
		} // end ~HL_MktData


		//------------------------------------------------------------------------------------------------------

		void HL_MktData::classDefaultInit()
		{

		} // end classDefaultInit

		//------------------------------------------------------------------------------------------------------


		void HL_MktData::set_mktDataCollectorWeakPtr(const HL_MktDataCollectorPtr & mktDataCollectorPtr)
		{
		
            if(mktDataCollectorWeakPtr_.expired()==false){
                HL_SRE(mktDataCollectorPtr.get()==mktDataCollectorWeakPtr_.lock().get(),
                       "HL_MktDataCollector alreay set but it is another instance (this is an ambiguos situation, "
                       << "you need to check the code.");
            }


            HL_PNN(mktDataCollectorPtr);
		
			mktDataCollectorWeakPtr_=mktDataCollectorPtr;

		} // end set_mktDataCollectorWeakPtr


		//------------------------------------------------------------------------------------------------------

		HL_MktDataCollectorPtr HL_MktData::get_mktDataCollector() const
		{
			return mktDataCollectorWeakPtr_.lock();
		} // end mktDataCollector


		//------------------------------------------------------------------------------------------------------

		const ptime &HL_MktData::get_refTime() const
		{
			return get_mktDataCollector()->get_refTime();
		} // end refTime

		//------------------------------------------------------------------------------------------------------

		date HL_MktData::get_refDate() const
		{
			return get_mktDataCollector()->get_refDate();
		} // end refDate

		//------------------------------------------------------------------------------------------------------


		void HL_MktData::descriptionImpl(std::ostream & os) const
		{
			HLOBJ::HL_FinObj::descriptionImpl(os);

		} // end descriptionImpl





	} // end namespace HL_MarketData
} //end namespace HorizonLib
