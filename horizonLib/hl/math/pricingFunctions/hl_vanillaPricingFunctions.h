/**
FILE NAME=hl_vanillaPricingFunctions.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140601
*/
#ifndef _hl_vanillaPricingFunctions_h_
#define _hl_vanillaPricingFunctions_h_

#include <hl/math/hl_function.h>
#include <hl/mktData/volSurfaces/hl_volSurface.h>

namespace HorizonLib
{
namespace HL_Math
{







//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// function hl_undiscBS
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140601
\brief BS formula

\[
E[ (vanillaType * (S-K))^+] = vanillaType * [(F * N(vanillaType*d_1) - K * N(vanillaType*d_2)] \\

d_1 = ln(F/K)/stdDev + 0.5*stdDev \\

d_2 = d_1 - 0.5*stdDev
\]

where S is a log-normal with mean F and given stdDev, N is umulative std normal.

\param K: the strike can also be negative
\param F: fwd: it must be >=0
*/
HLR hl_undiscBS(HLR F, HLR K, HLR stdDev, HL_VanillaType vanillaType);


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// function hl_undiscShiftedBS
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140601
\brief BS formula with a shift

Let Y = S +shift, where S is a log-normal with mean F and given stdDev.

Then
\[
E[ (vanillaType * (Y-K))^+] = E[ (vanillaType * (S-(K-shift))^+] = \\
=hl_undiscBS(F, (K-shift), stdDev, vanillaType)
\]

*/
HLR hl_undiscShiftedBS(HLR F, HLR K, HLR shift, HLR stdDev, HL_VanillaType vanillaType);



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// function hl_undiscNormalBS
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140601
\brief Normal BS formula

\doc_tag 20140601-NBS

\[
E[ (vanillaType * (S-K))^+]\]
where S is a normal with mean F and given stdDev.

\param K: the strike can also be negative


*/
HLR hl_undiscNormalBS(HLR F, HLR K, HLR stdDev, HL_VanillaType vanillaType);


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// function hl_undiscGenericBS
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141123
\brief Checks impliedVolModelTypeType and uses the right BS formula.

\[
E[ (vanillaType * (S-K))^+]\]
where S is an underlying with mean F and given stdDev.

\param K: the strike can also be negative

*/
HLR hl_undiscGenericBS(HLR F,
                       HLR K,
                       HLR stdDev,
                       HLVOL::HL_ImpliedVolModelTypeType impliedVolModelTypeType,
                       HL_VanillaType vanillaType);





} // end namespace HL_Math
} //end namespace HorizonLib


#endif // _hl_vanillaPricingFunctions_h_
