/**
FILE NAME= hl_enviromentInit.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131121
*/
#ifndef _hl_enviromentInit_h_
#define _hl_enviromentInit_h_


#include <hl/basicFiles/hl_workingIncludes.h>
#include <hl/logging/hl_logging.h>

namespace HorizonLib
{
	namespace HL_Enviroment
	{


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_EnviromentEntering
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------

		/**
		\author A. Cesarini
		\date 20131121
		\brief Class containing initializations to be called when loading the enviroment.
		*/

		class HL_EnviromentEntering
		{
		public:


			/**
			Constructors & destructors
			*/
			//@{

			HL_EnviromentEntering();

			virtual ~HL_EnviromentEntering();
			//@}


			/**
			Public class interface
			*/
			//@{

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

		}; // end class HL_EnviromentEntering




		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_EnviromentExit
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------

		/**
		\author A. Cesarini
		\date 20131121
		\brief Class containing initializations to be called when exiting the enviroment.
		*/

		class HL_EnviromentExit
		{
		public:


			/**
			Constructors & destructors
			*/
			//@{

			HL_EnviromentExit();

			virtual ~HL_EnviromentExit();
			//@}


			/**
			Public class interface
			*/
			//@{

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

		}; // end class HL_EnviromentExit







	} // end namespace HL_Enviroment
} //end namespace HorizonLib


#endif // _hl_enviromentInit_h_
