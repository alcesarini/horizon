/**
FILE NAME= hl_exceptions.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131125
*/
#ifndef _hl_exceptions_h_
#define _hl_exceptions_h_


#include <hl/logging/hl_logging.h>

namespace HorizonLib
{
	namespace HL_Exceptions
	{



		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class Errinfo_HL_Exception
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------

		typedef boost::error_info<struct HL_Exception_tag, HLSTRING> Errinfo_HL_Exception;


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// HL_Exceptions defines
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------

		/** 
		The use of this function may be useful. By placing a break point during debugging one could be able to 
		detect the place from where the exception is thrown.
		*/
		inline void exceptionDebugEntryPoint()
		{
			return;		
		} // end exceptionDebugEntryPoint

		//------------------------------------------------------------------------------------------------------


#define HL_THROW(ExceptionClass, exceptionMessage) \
		{\
		std::stringstream ssException;\
		ssException << exceptionMessage;\
		BOOST_THROW_EXCEPTION(ExceptionClass() << \
		Errinfo_HL_Exception(ssException.str()));\
		}

		//------------------------ ------------------------------------------------------------------------------

#define HL_REQUIRE(ExceptionClass, condition, exceptionMessage) \
	if(!(condition)){ \
	exceptionDebugEntryPoint();\
	HL_THROW(ExceptionClass, exceptionMessage);\
	}


		//------------------------------------------------------------------------------------------------------

#define HL_EXPECTED_STRING(condition) ("[expected " + HLSTRING(#condition) + "] ")


		//------------------------------------------------------------------------------------------------------

#define HL_SRE_SERVICE(ExceptionClass, condition, exceptionMessage) \
	HL_REQUIRE(ExceptionClass, condition, HL_EXPECTED_STRING(condition) << exceptionMessage)

		//------------------------------------------------------------------------------------------------------

#define HL_SRE(condition, exceptionMessage) \
	HL_SRE_SERVICE(HL_IntermediateDataException, condition, exceptionMessage)

		//------------------------------------------------------------------------------------------------------

#define HL_SR(condition) HL_SRE(condition, "")


		//------------------------------------------------------------------------------------------------------

#define HL_SRE_ID(condition, exceptionMessage) \
	HL_SRE_SERVICE(HL_InputDataException, condition, exceptionMessage)

		//------------------------------------------------------------------------------------------------------

#define HL_SR_ID(condition) HL_SRE_ID(condition, "")
		

		//------------------------------------------------------------------------------------------------------

#define HL_PNN(pointer) \
	HL_REQUIRE(HL_LogicException, (pointer!=0), HL_EXPECTED_STRING(pointer) + " not null")

		//------------------------------------------------------------------------------------------------------

#define HL_FAIL(message) \
	HL_THROW(HL_LogicException, message)

		//------------------------------------------------------------------------------------------------------

#define HL_UNEXPECTED_FUNCTION_CALL \
	HL_THROW(HL_LogicException, "unexpected function call")

		//------------------------------------------------------------------------------------------------------

#define HL_EXCEPTION_HEADER(exceptionHeader) std::stringstream ssExc; \
	ssExc << "\n***HL_EXC***: " << exceptionHeader << "\n";

		//------------------------------------------------------------------------------------------------------

#define HL_OUTPUT_EXCEPTION_DIAGNOSTIC(e) ssExc << "\nOutput from diagnostic_information():\n";\
	ssExc << boost::diagnostic_information(e);

		//------------------------------------------------------------------------------------------------------

#define HL_WRITE_EXCEPTION HLSTRING excString = ssExc.str();\
	HL_GET_LOGGER(false/*addTimer*/);\
	HL_LOG(HLLOG::HL_severity_level_critical, excString);\
	std::cerr << excString;

		//------------------------------------------------------------------------------------------------------

#define HL_TRY try

		//------------------------------------------------------------------------------------------------------

#define HL_CATCH catch(HL_Exception & e)\
		{\
		HL_EXCEPTION_HEADER("Caught HL_Exception")\
		if( HLSTRING const * info = boost::get_error_info<Errinfo_HL_Exception>(e) ){\
		ssExc << "Errinfo_HL_Exception= " << *info << "\n";\
		}\
		HL_OUTPUT_EXCEPTION_DIAGNOSTIC(e)\
		HL_WRITE_EXCEPTION\
		}catch(std::exception & e)\
		{\
		HL_EXCEPTION_HEADER("nCaught std::exception")\
		HL_OUTPUT_EXCEPTION_DIAGNOSTIC(e)\
		HL_WRITE_EXCEPTION\
		}catch(boost::exception & e)\
		{\
		HL_EXCEPTION_HEADER("nCaught boost::exception")\
		HL_OUTPUT_EXCEPTION_DIAGNOSTIC(e)\
		HL_WRITE_EXCEPTION\
		}catch(...)\
		{\
		HL_EXCEPTION_HEADER("nCaught unexpected exception")\
		ssExc << boost::current_exception_diagnostic_information();\
		HL_WRITE_EXCEPTION\
		}





		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_Exception
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------

		typedef boost::error_info<struct HL_Exception_tag, HLSTRING> Errinfo_HL_Exception;

		//------------------------------------------------------------------------------------------------------

		/**
		\author A. Cesarini
		\date 20131125
		\brief Base for all exception objects we throw. 
		See "\boost_1_54_0\libs\exception\example\example_io.cpp"
		*/

		class HL_Exception : public virtual std::exception,	public virtual boost::exception
		{
		public:


			/**
			Constructors & destructors
			*/
			//@{

			HL_Exception();

			virtual ~HL_Exception() throw()
			{
			}

		public:

			//@}


			/**
			Public class interface
			*/
			//@{
			char const * what() const throw()
			{
				return "HL_Exception: ";
			}
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

		}; // end class HL_Exception


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_LogicException
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		/**
		\author A. Cesarini
		\date 20131125
		\brief Base for all exception objects that denote an ill conditioned way the program is working.
		See "\boost_1_54_0\libs\exception\example\example_io.cpp"
		*/

		class HL_LogicException : public virtual HL_Exception
		{
		public:


			/**
			Constructors & destructors
			*/
			//@{

			HL_LogicException();


			virtual ~HL_LogicException() throw()
			{
			}

		public:

			//@}


			/**
			Public class interface
			*/
			//@{
			char const * what() const throw()
			{
				return "<<<HL_LogicException>>>";
			}
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

		}; // end class HL_LogicException



		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_InputDataException
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		/**
		\author A. Cesarini
		\date 20131125
		\brief Base for all exception objects that denote an ill conditioned way the program is working, concerning the 
		raw input data the program has received.
		See "\boost_1_54_0\libs\exception\example\example_io.cpp"
		*/

		class HL_InputDataException : public virtual HL_Exception
		{
		public:


			/**
			Constructors & destructors
			*/
			//@{

			HL_InputDataException();


			virtual ~HL_InputDataException() throw()
			{
			}

		public:

			//@}


			/**
			Public class interface
			*/
			//@{
			char const * what() const throw()
			{
				return "HL_InputDataException: ";
			}
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

		}; // end class HL_InputDataException


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_IntermediateDataException
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------

		/**
		\author A. Cesarini
		\date 20131125
		\brief Base for all exception objects that denote an ill conditioned way the program is working, concerning the 
		intermediate data the program has produced nduring its processing algorithm.
		Notice the we derived "protected-virtual" and not "publidc-virtual", since boost example made like that.
		See "\boost_1_54_0\libs\exception\example\example_io.cpp"
		*/

		class HL_IntermediateDataException : public virtual HL_Exception
		{
		public:


			/**
			Constructors & destructors
			*/
			//@{

			HL_IntermediateDataException();

			virtual ~HL_IntermediateDataException() throw()
			{
			}

		public:

			//@}


			/**
			Public class interface
			*/
			//@{
			char const * what() const throw()
			{
				return "HL_IntermediateDataException: ";
			}
			//@}


		protected:

			/**
			Implementations of base class methods
			*/
			//@{

			//@}


			/**
			Additional implementations
			*/
			//@{
			/**
			Default initialization of the class vars.
			*/
			void classDefaultInit();
			//@}

		protected:


			/**
			Class variables
			*/
			//@{

			//@}

		}; // end class HL_IntermediateDataException


		void exceptionExample();



	} // end namespace HL_Exceptions
} //end namespace HorizonLib

namespace HorizonLib
{
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	// usings
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------

	using namespace HL_Exceptions;


} //end namespace HorizonLib

#endif // _hl_exceptions_h_
