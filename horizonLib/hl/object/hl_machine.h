/**
FILE NAME= hl_machine.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131128
*/
#ifndef _hl_machine_h_
#define _hl_machine_h_


#include <hl/object/hl_object.h>


namespace HorizonLib
{
	namespace HL_Object
	{


		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------
		// class HL_Machine
		//------------------------------------------------------------------------------------------------------
		//------------------------------------------------------------------------------------------------------

		/**
		\author A. Cesarini
		\date 20131128
		\brief The purpose of this class is to transform one instance of MachineInputType-data (let's name it "I") in one 
		instance of MachineOutputTypedata (let's name it "O"). 
		
		Notice that I is generally not the unique data that
		is used to produce O, but nonetheless I is supposed to uniquely determine the conditions under which O has 
		been produced. Notice that MachineInputType must have an ordering defined.
		FINANCIAL_EXAMPLE: suppose that we have to compute a d-date swap rate (O) from a discount curve having HL_ObjCode "X_code".
		Then, in practice the swap rate will be computed from the discount factors of the curve.
		Suppose then that we are sure, within the execution enviroment we are interested in, that the discount factors of
		the "X_code" curve will never change.
		In this case, it will hence be sufficinet to get I=X_code, even if the swap rate has been in practice constructed 
		using the discount factors (i.e. the number that are the actual input of the math formula yield to the swap rate).
		In other words, since we know for some external reasons that rates are fixed, we only have to remind which 
		curve gave rise to the swap rate (and not the actual values of its discounts).
		*/
		template <class MachineInputType, class MachineOutputType>
		class HL_Machine
		{
		public:

			typedef MachineInputType InputType;
			typedef MachineOutputType OutputType;


			/**
			\name Constructors & destructors
			*/
			//@{

			HL_Machine(){}

			virtual ~HL_Machine(){}
			//@}


			/**
			\name Public class interface
			*/
			//@{

			/** 
			Referring to the class comment, this method produces O.
			This is then the possibly computation-intensive method.
			*/
			virtual void doJob() const=0;

			/** 
			Resets all the track record of past jobs.
			*/
			void resetOutputs()
			{
				outputs_.clear();
			}
			//@}


		protected:



			/**
			\name Additional implementations
			*/
			//@{
			/**
			Default initialization of the class vars.
			*/
			void classDefaultInit(){}

			//@}
						
			
			/**
			\name Implementations of base class methods
			*/
			//@{

			//@}

		protected:


			/**
			\name Class variables
			*/
			//@{
			/** 
			The work of the machine has produced these outputs, associated to the corresponding inputs
			in the sense explained in the class comment.

			This stored data will be used to avoid redoing jobs when asking for the InputType-instances
			that have already been processed in the past.
			*/
			std::map<InputType, OutputType> outputs_;
			//@}

		}; // end class HL_Machine



	} // end namespace HL_Object
} //end namespace HorizonLib


#endif // _hl_machine_h_
