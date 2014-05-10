/**
FILE NAME= hl_mktDataCollector.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131226
*/
#include <hl/mktData/hl_mktDataCollector.h>
#include <hl/mktData/termStructures/hl_termStructure.h>

namespace HorizonLib
{
	namespace HL_MarketData
	{

		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_MktDataCollector
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		HL_MktDataCollector::HL_MktDataCollector()
		{

			classDefaultInit();



		} // end HL_MktDataCollector

		//------------------------------------------------------------------------------------------------------

		HL_MktDataCollector::~HL_MktDataCollector()
		{
		} // end ~HL_MktDataCollector


		//------------------------------------------------------------------------------------------------------

		void HL_MktDataCollector::classDefaultInit()
		{

		} // end classDefaultInit

		//------------------------------------------------------------------------------------------------------


		void HL_MktDataCollector::descriptionImpl(std::ostream & os) const
		{
			Descriptable::descriptionImpl(os);

			BOOST_FOREACH(const MktDataCollectionType::value_type & p, mktDataMap_)
			{
				os << "*****************************************************************************\n";
				os << p.second << "\n";
			} // end cIt

		} // end descriptionImpl



		//------------------------------------------------------------------------------------------------------

		void HL_MktDataCollector::set_refTime(const ptime &refTime)
		{


			refTime_=refTime;


		} // end set_refTime
		//------------------------------------------------------------------------------------------------------


		void HL_MktDataCollector::addMktData(const HL_MktDataPtr & mktDataPtr, const HL_MktDataCollectorPtr & mktDataCollectorPtr)
		{
			HL_PNN(mktDataPtr);

			mktDataPtr->set_mktDataCollectorWeakPtr(mktDataCollectorPtr);
		
		} // end addMktData
		

		struct Y
		{
		
			Y(int c)
			{}

			virtual void check(){}
		};

		//------------------------------------------------------------------------------------------------------

		void HL_TEST_HL_MktDataCollector_Serialize()
		{
		
		
			HL_MktDataCollectorPtr hl_MktDataCollectorPtr(new HL_MktDataCollector);
		
			HLSER::HL_CoreSerializableObj csObj;

			csObj.oa() << hl_MktDataCollectorPtr;

			HL_MktDataCollectorPtr hl_MktDataCollectorPtr_reconstructed(new HL_MktDataCollector);
			
			csObj.getReadyForDeserialization();
		

			csObj.ia() >> hl_MktDataCollectorPtr_reconstructed;

			BSP<Y> y = boost::make_shared<Y>(4);

			HL_TermStructureCodePtr termStructureCodePtr;// = boost::make_shared<HL_TermStructureCode>();

			HL_TermStructurePtr ts = get_TermStructurePtr(hl_MktDataCollectorPtr_reconstructed, termStructureCodePtr/* objCodePtr*/);


		} // end HL_TEST_HL_MktDataCollector_Serialize

	} // end namespace HL_MarketData
} //end namespace HorizonLib
