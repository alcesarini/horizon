/**
FILE NAME= hl_dateTime.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131213
*/
#include <hl/dateTime/hl_dateTime.h>

#include <hl/logging/hl_logging.h>




namespace HorizonLib
{
	namespace HL_DateTime
	{


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// act_yf
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------

#define HL_INVERSE_SECS_IN_ONE_YEAR 3.17097919837646e-8

		//------------------------------------------------------------------------------------------------------

		HLR act_yf(const time_period & tp)
		{

			time_duration td =tp.length();


			HLR yf = td.total_seconds()*HL_INVERSE_SECS_IN_ONE_YEAR;

			return yf;

		} // end act_yf


		//------------------------------------------------------------------------------------------------------

		HLR act_yf(const ptime & t_1, const ptime & t_2)
		{

			return act_yf(time_period(t_1, t_2));
		} // end act_yf


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// tests
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------

		void HL_TEST_dateTime()
		{




			HL_GET_LOGGER(false/*addTimer*/);



			date d1(2013, Dec, 13);

			HL_LOG(HLLOG::HL_severity_level_notification, "d1=" << d1); 

			date d1_Plus_2_Weeks  = d1 + weeks(2);

			HL_LOG(HLLOG::HL_severity_level_notification, "d1_Plus_2_Weeks=" << d1_Plus_2_Weeks); 

			date d1_Plus_2_Days  = d1 + days(2);

			HL_LOG(HLLOG::HL_severity_level_notification, "d1_Plus_2_Days=" << d1_Plus_2_Days); 



			date d1_Plus_2_months  = d1 + months(2);

			HL_LOG(HLLOG::HL_severity_level_notification, "d1_Plus_2_months=" << d1_Plus_2_months); 


			date d1_Plus_2_years  = d1 + years(2);

			HL_LOG(HLLOG::HL_severity_level_notification, "d1_Plus_2_years=" << d1_Plus_2_years); 


			date today = day_clock::local_day();

			HL_LOG(HLLOG::HL_severity_level_notification, "today=" << today); 

			// time 

			ptime local_time_second_Clock(second_clock::local_time());

			HL_LOG(HLLOG::HL_severity_level_notification, "local_time_second_Clock=" << local_time_second_Clock); 

			ptime local_time_microsecond_Clock(microsec_clock::local_time());

			HL_LOG(HLLOG::HL_severity_level_notification, "local_time_microsecond_Clock=" << local_time_microsecond_Clock); 


			ptime t_1(today, minutes(5));

			HL_LOG(HLLOG::HL_severity_level_notification, "t_1=" << t_1); 

			ptime t_2 = t_1 + days(3) + hours(1) + minutes(2);

			HL_LOG(HLLOG::HL_severity_level_notification, "t_2=" << t_2); 

			ptime t_3(today);

			HL_LOG(HLLOG::HL_severity_level_notification, "t_3=" << t_3); 


			time_period t_period_1_2(t_1, t_2);


			HL_LOG(HLLOG::HL_severity_level_notification, "t_period_1_2=" << t_period_1_2); 


			time_duration t_duration_1_2 = t_period_1_2.length();

			HL_LOG(HLLOG::HL_severity_level_notification, "t_duration_1_2=" << t_duration_1_2); 


			////iterate and print the week
			//day_iterator itr(weekstart);
			//while (itr <= weekend) {
			//	std::cout << (*itr) << std::endl;
			//	++itr;
			//}  
			////input streaming 
			//std::stringstream ss("2004-Jan-1");
			//ss >> d3;

			////date generator functions 
			//date d5 = next_weekday(d4, Sunday); //calculate Sunday following d4

			////US labor day is first Monday in Sept 
			//typedef nth_day_of_the_week_in_month nth_dow;
			//nth_dow labor_day(nth_dow::first,Monday, Sep); 
			////calculate a specific date for 2004 from functor 
			//date d6 = labor_day.get_date(2004); 

		} // end HL_TEST_dateTime
	} // end namespace HL_DateTime
} //end namespace HorizonLib
