/**
FILE NAME= hl_commonDeclarations.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140601
*/
#ifndef _hl_commonDeclarations_h_
#define _hl_commonDeclarations_h_



/**
Contains some declaration that one would need to be seen from the whole library
*/

#include <hl/patterns/hl_ordering.h>
#include <hl/serialization/hl_coreSerializableObj.h>
#include <hl/dateTime/hl_dateTime.h>
#include <hl/patterns/hl_descriptable.h>
#include <hl/patterns/hl_disposable.h>
#include <hl/containers/hl_containerManip.h>
#include <hl/math/hl_comparisonChecks.h>


namespace HorizonLib
{




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_VanillaType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



enum HL_VanillaType
{
    HL_VanillaType_InvalidMin=-2,
    HL_Put=-1,
    HL_Call=+1,
    HL_VanillaType_InvalidMax=+2
}; // end enum HL_VanillaType

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
        HL_VanillaType,
        "HL_VanillaType_InvalidMin",
        "HL_Put",
        "HL_Call",
        "HL_VanillaType_InvalidMax"
        );



} //end namespace HorizonLib

#endif // _hl_commonDeclarations_h_
