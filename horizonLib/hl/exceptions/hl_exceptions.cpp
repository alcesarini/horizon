/**
FILE NAME= hl_exceptions.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131109
*/
#include <hl/exceptions/hl_exceptions.h>


namespace HorizonLib
{
	namespace HL_Exceptions
	{


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_Exception
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		HL_Exception::HL_Exception()
		{
			classDefaultInit();

		} // end HL_Exception


		//------------------------------------------------------------------------------------------------------

		void HL_Exception::classDefaultInit()
		{

		} // end classDefaultInit


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_LogicException
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		HL_LogicException::HL_LogicException()
		{
			classDefaultInit();

		} // end HL_LogicException


		//------------------------------------------------------------------------------------------------------

		void HL_LogicException::classDefaultInit()
		{

		} // end classDefaultInit


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_InputDataException
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		HL_InputDataException::HL_InputDataException()
		{
			classDefaultInit();

		} // end HL_InputDataException


		//------------------------------------------------------------------------------------------------------

		void HL_InputDataException::classDefaultInit()
		{

		} // end classDefaultInit



		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_IntermediateDataException
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------


		HL_IntermediateDataException::HL_IntermediateDataException()
		{
			classDefaultInit();

		} // end HL_IntermediateDataException


		//------------------------------------------------------------------------------------------------------

		void HL_IntermediateDataException::classDefaultInit()
		{

		} // end classDefaultInit

		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_IntermediateDataException
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------



		//------------------------------------------------------------------------------------------------------

		void exceptionExample()
		{


			HLI c=5;

			HL_TRY
			{
				BSP<HL_Exception> bbbbb;

				HL_PNN(bbbbb);

				HL_SR(c<2);

				HL_SRE_ID(c<2, "--------------------------------------");

				HL_SRE(c<2, "vediamo se funziona INT");

			}
			HL_CATCH;







			//try{
			//	try
			//	{

			//		BOOST_THROW_EXCEPTION(HL_InputDataException() <<
			//			boost::errinfo_errno    (errno) <<
			//			errinfo_HL_InputDataException("ciao"));


			//	}catch(boost::exception & x)
			//	{
			//		x <<
			//			errinfo_HL_IntermediateDataException("BBBB errinfo_HL_IntermediateDataException");


			//		throw;
			//	}

			//}catch(boost::exception & x)
			//{
			//	if( HLSTRING const * info = boost::get_error_info<errinfo_HL_InputDataException>(x) )
			//		std::cerr << "HL_InputDataException: " << *info << "\n";
			//	if( HLSTRING const * info = boost::get_error_info<errinfo_HL_IntermediateDataException>(x) )
			//		std::cerr << "HL_IntermediateDataException: " << *info << "\n";
			//	if( HLI const * err = boost::get_error_info<boost::errinfo_errno>(x) )
			//		std::cerr << "errinfo_errno: " << *err << "\n";

			//	std::cerr << "\nOutput from diagnostic_information():\n";
			//	std::cerr << diagnostic_information(x);
			//}catch(... )
			//{
			//	std::cerr << "\nCaught unexpected exception!\n";
			//	std::cerr << boost::current_exception_diagnostic_information();
			//}



		}



	} // end namespace HL_Exceptions
} //end namespace HorizonLib
