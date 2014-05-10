/**
FILE NAME= hl_mathUtils.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131231
*/
#include <hl/math/hl_mathUtils.h>

namespace HorizonLib
{
namespace HL_Math
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// integerPower
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HLS integerPower(HLS x, HLS p)
{
    if (p == 0)
        return 1;

    if (p == 1)
        return x;

    int tmp = integerPower(x, p/2);
    if (p%2 == 0)
    {
        return tmp * tmp;
    }
    else
    {
        return x * tmp * tmp;
    }
} // end integerPower


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// hl_decimalToBase
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//		HL_Disposable<HLSTRING> hl_decimalToBase(HLI num, HLS base)
//		{
//
//			/*
//			bounds check for radix
//			*/
//			HL_SR(base>=2 && base<=62);
//
//
//			/*
//			if num is zero
//			*/
//			if (!num){
//				HLSTRING nullString("0");
//				HL_Disposable<HLSTRING> retDisp(nullString);
//				return retDisp;
//			}
//			char buf[66];  /* enough space for any 64-bit in base 2 */
//
//			/*
//			null terminate buf, and set i at end
//			*/
//			buf[65] = '\0';
//
//			HLI numSign = num>0 ? 1 : -1;
//
//			HLI effNum = numSign*num; /*>0*/
//
//			HLI i = 65;
//			/*
//			until effNum is 0
//			*/
//			while (effNum)
//			{
//				/*
//				go left 1 digit, divide by radix, and set digit to remainder
//				*/
//				buf[--i] = hl_baseDigits[effNum % base];
//				effNum /= base;
//			} // end while
//
//			if(numSign<0){
//				buf[--i] = '-';
//			}
//
//			/*
//			Copies up to the numm termination
//			*/
//			HLSTRING baseRepresentation(buf + i);
//
//
//			HL_Disposable<HLSTRING> retDisp(baseRepresentation);
//
//
//			return retDisp;
//
//
//		} // end decomalToBaseWhatever


} // end namespace HL_Math
} //end namespace HorizonLib
