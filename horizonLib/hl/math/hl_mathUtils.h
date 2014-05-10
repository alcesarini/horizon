/**
FILE NAME=hl_mathUtils.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131231
*/
#ifndef _hl_mathUtils_h_
#define _hl_mathUtils_h_

#include <hl/basicFiles/hl_workingIncludes.h>


namespace HorizonLib
{
namespace HL_Math
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// integerPower
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
Returns x^p
*/
HLS integerPower(HLS x, HLS p);

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// hl_decimalToBase
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//static char hl_baseDigits[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";


//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140104
\brief Returns the string representation of the inpuy num (to be expressed in base 10) to the new base base.
*/
//		HL_Disposable<HLSTRING> hl_decimalToBase(HLI num, HLS base);



} // end namespace HL_Math
} //end namespace HorizonLib


#endif // _hl_mathUtils_h_
