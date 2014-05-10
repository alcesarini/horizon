/**
FILE NAME= hl_logging.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131121
*/
#ifndef _hl_logging_h_
#define _hl_logging_h_


#include <hl/basicFiles/hl_basicIncludes.h>

namespace HorizonLib
{
	namespace HL_Logging
	{

		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// namespace defines
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------

#define HL_logging boost::log
#define HL_sinks boost::log::sinks
#define HL_attrs boost::log::attributes
#define HL_src boost::log::sources
#define HL_expr boost::log::expressions
#define HL_keywords boost::log::keywords

		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// enum HL_severity_level
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		/**
		Here we define our application severity levels
		*/
		enum HL_severity_level
		{
			HL_severity_level_normal,
			HL_severity_level_notification,
			HL_severity_level_warning,
			HL_severity_level_error,
			HL_severity_level_critical
		}; // end enum HL_severity_level

		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_Log: formatting
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------

		// The formatting logic for the severity level
		template< typename CharT, typename TraitsT >
		inline std::basic_ostream< CharT, TraitsT >& operator<< (
			std::basic_ostream< CharT, TraitsT >& strm, HL_severity_level lvl)
		{
			static const char* const str[] =
			{
				"normal",
				"notification",
				"warning",
				"error",
				"critical"
			};
			if (static_cast< std::size_t >(lvl) < (sizeof(str) / sizeof(*str)))
				strm << str[lvl];
			else
				strm << static_cast< HLI >(lvl);
			return strm;

		} // end operator<<


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// HL_Log defines
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


#define HL_UP_TIME "Uptime"


		//------------------------------------------------------------------------------------------------------
		/**
		Call HL_GET_LOGGER to get the logger and then call HL_LOG as many times as needed
		*/
#define HL_GET_LOGGER(addTimer) \
	HL_src::severity_logger< HLLOG::HL_severity_level > hl_slg; \
	if (addTimer) { \
	hl_slg.add_attribute(HL_UP_TIME, HL_attrs::timer()); \
	} \
	BOOST_LOG_FUNCTION(); 

		//------------------------------------------------------------------------------------------------------
		/**
		Call HL_LOG after having called HL_GET_LOGGER
		*/
#define HL_LOG(hl_severity_level, logMessage) \
	BOOST_LOG_SEV(hl_slg, hl_severity_level) << "HL_Log: " << logMessage;



		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_Log
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------

		/**
		\author A. Cesarini
		\date 20131121
		\brief The logger interface.
		*/

		class HL_Log
		{
		public:


			/**
			Constructors & destructors
			*/
			//@{

			HL_Log();

			virtual ~HL_Log();
			//@}


			/**
			Public class interface
			*/
			//@{
			/** 
			To be called when entering the enviroment to in initialize the logger.
			*/
			static void initializeLogging();
			//@}


		protected:



			/**
			Additional implementations
			*/
			//@{
			/**
			Default initialization of the class vars.
			*/
			void classDefaultInit();
			//@}

			/**
			Implementations of base class methods
			*/
			//@{

			//@}

		protected:


			/**
			Class variables
			*/
			//@{

			//@}

		}; // end class HL_Log





	} // end namespace HL_Logging
} //end namespace HorizonLib


#endif // _hl_logging_h_
