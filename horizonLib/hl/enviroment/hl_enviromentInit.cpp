/**
FILE NAME= hl_enviromentInit.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131121
*/
#include <hl/enviroment/hl_enviromentInit.h>


namespace HorizonLib
{
	namespace HL_Enviroment
	{



		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_EnviromentEntering
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		HL_EnviromentEntering::HL_EnviromentEntering()
		{
			classDefaultInit();

		} // end HL_EnviromentEntering

		//------------------------------------------------------------------------------------------------------

		HL_EnviromentEntering::~HL_EnviromentEntering()
		{
		} // end ~HL_EnviromentEntering

		//------------------------------------------------------------------------------------------------------

		void HL_EnviromentEntering::classDefaultInit()
		{
			HLLOG::HL_Log::initializeLogging();

		} // end classDefaultInit



		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_EnviromentExit
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		HL_EnviromentExit::HL_EnviromentExit()
		{
			classDefaultInit();

		} // end HL_EnviromentExit

		//------------------------------------------------------------------------------------------------------

		HL_EnviromentExit::~HL_EnviromentExit()
		{
		} // end ~HL_EnviromentExit

		//------------------------------------------------------------------------------------------------------

		void HL_EnviromentExit::classDefaultInit()
		{

			boost::singleton_pool<boost::pool_allocator_tag, sizeof(char)>::release_memory();

		} // end classDefaultInit


	} // end namespace HL_Enviroment
} //end namespace HorizonLib
