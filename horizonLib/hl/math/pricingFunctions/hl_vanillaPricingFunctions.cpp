/**
FILE NAME= hl_vanillaPricingFunctions.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140601
*/
#include <hl/math/pricingFunctions/hl_vanillaPricingFunctions.h>


namespace HorizonLib
{
namespace HL_Math
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// function hl_undiscBS
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HLR hl_undiscBS(HLR F, HLR K, HLR stdDev, HL_VanillaType vanillaType)
{

    HL_SRE(F>=0., "F=" << F);
    HL_SRE(stdDev>=0., "stdDev=" << stdDev);

    HL_ENUM_CHECK(HL_VanillaType, vanillaType);

    HLR bs;

    if(stdDev==0. || K<=0. || F==0.){

        HLR intrinsic = vanillaType*(F-K);
        bs = std::max(intrinsic, 0.);

    }else{

        /*
        default mean=0, default stdDev=1
        */
        boost::math::normal normDensity;

        HLR halfStdDev =  0.5*stdDev;

        HLR d_1 = std::log(F/K)/stdDev + halfStdDev;

        HLR d_2 = d_1 - halfStdDev;

        bs = vanillaType*  (  F * cdf(normDensity, (vanillaType*d_1)) - K * cdf(normDensity, (vanillaType*d_2)) ) ;


    } // end if..else..

    return bs;

} // end hl_undiscBS

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// function hl_undiscShiftedBS
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HLR hl_undiscShiftedBS(HLR F, HLR K, HLR shift, HLR stdDev, HL_VanillaType vanillaType)
{

    return hl_undiscBS(F, K-shift, stdDev, vanillaType);


} // end hl_undiscShiftedBS




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// function hl_undiscNormalBS
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HLR hl_undiscNormalBS(HLR F, HLR K, HLR stdDev, HL_VanillaType vanillaType)
{

    HL_SRE(stdDev>=0., "stdDev=" << stdDev);
    HL_ENUM_CHECK(HL_VanillaType, vanillaType);

    HLR nbs;

    if(stdDev==0.){

        HLR intrinsic = vanillaType*(F-K);
        nbs = std::max(intrinsic, 0.);

    }else{

        /*
        default mean=0, default stdDev=1
        */
        boost::math::normal normDensity;


        HLR delta = F-K;

        HLR zStar = -delta/stdDev;

        nbs = stdDev * pdf(normDensity, zStar) + vanillaType * delta * cdf(normDensity, -vanillaType*zStar);


    } // end if..else..

    return nbs;

} // end hl_undiscNormalBS


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// function hl_undiscGenericBS
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HLR hl_undiscGenericBS(HLR F,
                       HLR K,
                       HLR stdDev,
                       HLVOL::HL_ImpliedVolModelTypeType impliedVolModelTypeType,
                       HL_VanillaType vanillaType)
{

    switch(impliedVolModelTypeType)
    {
    case HLVOL::HL_ImpliedVolModelTypeType_LogNormal:

        return hl_undiscBS(F, K, stdDev, vanillaType);

    case HLVOL::HL_ImpliedVolModelTypeType_ShiftedLogNormal:

        return hl_undiscShiftedBS(F, K, HL_NAN /*shift, the vol is not ready */, stdDev, vanillaType);

    case HLVOL::HL_ImpliedVolModelTypeType_Normal:

        return hl_undiscNormalBS(F, K, stdDev, vanillaType);

    default:
        HL_FAIL("invalid impliedVolModelTypeType=" << getEnumString(impliedVolModelTypeType));

    } // end switch impliedVolModelTypeType


    return HL_NAN;

} // end hl_undiscGenericBS



} // end namespace HL_Math
} //end namespace HorizonLib
