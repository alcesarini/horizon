/**
FILE NAME= hl_logging.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131121
*/
#include <hl/logging/hl_logging.h>


namespace HorizonLib
{
	namespace HL_Logging
	{



		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_Log
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		HL_Log::HL_Log()
		{
			classDefaultInit();

		} // end HL_Log

		//------------------------------------------------------------------------------------------------------

		HL_Log::~HL_Log()
		{
		} // end ~HL_Log

		//------------------------------------------------------------------------------------------------------

		void HL_Log::classDefaultInit()
		{

		} // end classDefaultInit

		//------------------------------------------------------------------------------------------------------

		void HL_Log::initializeLogging()
		{

			/*
			Code taken from the following example:
			.\boost_1_54_0\libs\log\example\basic_usage\main.cpp


			*          Copyright Andrey Semashev 2007 - 2013.
			* Distributed under the Boost Software License, Version 1.0.
			*    (See accompanying file LICENSE_1_0.txt or copy at
			*          http://www.boost.org/LICENSE_1_0.txt)
			*/
			/*!
			* \file   main.cpp
			* \author Andrey Semashev
			* \date   11.11.2007
			*
			* \brief  An example of basic library usage. See the library tutorial for expanded
			*         comments on this code. It may also be worthwhile reading the Wiki requirements page:
			*         http://www.crystalclearsoftware.com/cgi-bin/boost_wiki/wiki.pl?Boost.Logging
			*/

			// The first thing we have to do to get using the library is
			// to set up the logging sinks - i.e. where the logs will be written to.
			HL_logging::add_console_log(std::clog, HL_keywords::format = "%TimeStamp%: %Message%");

			// One can also use lambda expressions to setup filters and formatters
			HL_logging::add_file_log
                (
				"HL_LOG_FILE.log",
                HL_keywords::filter = HL_expr::attr< HL_severity_level >("Severity") >= HL_severity_level_normal,
				HL_keywords::format = HL_expr::stream
				<< HL_expr::format_date_time< boost::posix_time::ptime >("TimeStamp", "%Y-%m-%d, %H:%M:%S.%f")
				<< " [" << HL_expr::format_date_time< HL_attrs::timer::value_type >(HL_UP_TIME, "%O:%M:%S")
				<< "] [" << HL_expr::format_named_scope("Scope", HL_keywords::format = "%n (%f:%l)")
				<< "] <" << HL_expr::attr< HL_severity_level >("Severity")
				<< "> " << HL_expr::message);

			// Also let's add some commonly used attributes, like timestamp and record counter.
			HL_logging::add_common_attributes();
			HL_logging::core::get()->add_thread_attribute("Scope", HL_attrs::named_scope());



		} // end initializeLogging




	} // end namespace HL_Logging
} //end namespace HorizonLib
