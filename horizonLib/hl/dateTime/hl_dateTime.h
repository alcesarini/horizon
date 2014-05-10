/**
FILE NAME= hl_dateTime.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131213
*/
#ifndef _hl_dateTime_h_
#define _hl_dateTime_h_

#include <hl/basicFiles/hl_basicIncludes.h>


namespace HorizonLib
{
	namespace HL_DateTime
	{

		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// act_yf
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		/** 
		Unique method to convert a time_period to a year fraction.
		FINANCIAL_EXAMPLE: Notice that here we take as input a time_period and NOT a date_period.
		Converting a date_period to a year fraction will be instead a matter for coupon calculation, or similar
		financial stuff and this will be done with appropriate day counting classes. 
		act_yf is instead an actual physical time lapse.
		*/
		HLR act_yf(const time_period & tp);

		//------------------------------------------------------------------------------------------------------

		HLR act_yf(const ptime & t_1, const ptime & t_2);


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// tests
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------

		void HL_TEST_dateTime();


	} // end namespace HL_DateTime
} //end namespace HorizonLib


#endif // _hl_dateTime_h_
