/**
FILE NAME= hl_volSurface.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131227
*/
#include <hl/mktData/volSurfaces/hl_volSurface.h>
#include <hl/mktData/hl_mktDataCollector.h>
#include <hl/underlyings/interestRates/hl_iborIndex.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLVOL::HL_VolState);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLVOL::HL_VolSurface);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLVOL::HL_VolSurfaceCode);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLVOL::HL_FlatVolSurface);


namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_VolSurfaces
{





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VolState
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_VolState::HL_VolState()
{

    classDefaultInit();



} // end HL_VolState

//------------------------------------------------------------------------------------------------------

HL_VolState::~HL_VolState()
{
} // end ~HL_VolState


//------------------------------------------------------------------------------------------------------

void HL_VolState::classDefaultInit()
{

    vol_=HL_NAN;

    stdDev_=HL_NAN;

    timeFactor_=HL_NAN;

    sqrtTimeFactor_=HL_NAN;

    impliedVolModelTypeType_= HL_ImpliedVolModelTypeType_InvalidMin;


} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_VolState::descriptionImpl(std::ostream & os) const
{

    os << "HL_VolState:\n";

    Descriptable::descriptionImpl(os);


    hl_fillDescriptionStream(vol_);
    hl_fillDescriptionStream(stdDev_);
    hl_fillDescriptionStream(timeFactor_);
    hl_fillDescriptionStream(sqrtTimeFactor_);
    HL_DESCRIBE_ENUM(os, impliedVolModelTypeType_);


} // end descriptionImpl


//------------------------------------------------------------------------------------------------------


void HL_VolState::set_volState(HLR vol, HLR timeFactor, HL_ImpliedVolModelTypeType impliedVolModelTypeType)
{

    vol_=vol;

    timeFactor_=timeFactor;

    sqrtTimeFactor_=std::sqrt(timeFactor_);

    stdDev_=vol_*sqrtTimeFactor_;


    impliedVolModelTypeType_=impliedVolModelTypeType;

} // end set_volState



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VolSurfaceCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_VolSurfaceCode::HL_VolSurfaceCode()
{
    classDefaultInit();

} // end HL_VolSurfaceCode

//------------------------------------------------------------------------------------------------------

HL_VolSurfaceCode::~HL_VolSurfaceCode()
{
} // end ~HL_VolSurfaceCode

//------------------------------------------------------------------------------------------------------

void HL_VolSurfaceCode::classDefaultInit()
{

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

HLSTRING HL_VolSurfaceCode::objTypeImpl() const
{
    return "HL_VolSurfaceCode";
} // end objTypeImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VolSurface
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_VolSurface::HL_VolSurface()
{

    classDefaultInit();



} // end HL_VolSurface

//------------------------------------------------------------------------------------------------------

HL_VolSurface::~HL_VolSurface()
{
} // end ~HL_VolSurface


//------------------------------------------------------------------------------------------------------

void HL_VolSurface::classDefaultInit()
{

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_VolSurface::descriptionImpl(std::ostream & os) const
{
    HL_MktData::descriptionImpl(os);

    HL_DESCRIBE_ENUM(os, impliedVolModelTypeType_);

    hl_fillDescriptionStream(riskFreeDiscounting_);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------


void HL_VolSurface::set_HL_ObjCodePtr(const HL_ObjCodePtr & hl_ObjCodePtr)
{

    HL_MktData::set_HL_ObjCodePtr(hl_ObjCodePtr);


    HL_DYN_SHARED_PTR_CAST(HLVOL::HL_VolSurfaceCode, volSurfaceCode_ /*outPtr*/, hl_ObjCodePtr_ /*inPtr*/);



} // end set_HL_ObjCodePtr



//------------------------------------------------------------------------------------------------------

HL_VolStatePtr HL_VolSurface::vol(const ptime &t, HLR k, const ptime & fwdMaturityTime) const
{

    HL_VolStatePtr volState(new HL_VolState);


    if(t>get_refTime())
    {


        HLR yf = HLDT::act_yf(get_refTime(), t);

        HLR fwd_yf = HLDT::act_yf(get_refTime(), fwdMaturityTime);


        HLR vol = volImpl(yf, k, fwd_yf);


        /*
        do the mkt data tracking
        */
        const HL_MktDataTrackerContainerPtr & mktDataTrackerContainerPtr=
                get_mktDataCollector()->get_mktDataTrackerContainerPtr();

        mktDataTrackerContainerPtr->addVolSurfacePoint(volSurfaceCode_, yf/* t*/, k, vol/* value*/);


        volState->set_volState(vol, yf, get_impliedVolModelTypeType());

    } // end  if(t>get_refTime())

    return volState;

} // end vol


//------------------------------------------------------------------------------------------------------

HLR HL_VolSurface::get_yf(const ptime &t) const
{

    HLR dt = HLDT::act_yf(get_refTime(), t);

    return dt>0 ? dt : 0;

} // end get_yf



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VolSurface: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_VolSurfacePtr get_VolSurfacePtr(const HL_MktDataCollectorPtr & mktDataCollectorPtr, const HL_ObjCodePtr & objCodePtr)
{

    return get_mktData<HL_VolSurfacePtr>(mktDataCollectorPtr, objCodePtr);

} // end get_VolSurfacePtr


//------------------------------------------------------------------------------------------------------

void HL_TEST_HL_VolSurface()
{
    HL_MktDataCollectorPtr mktDataCollectorPtr;

    HL_VolSurfaceCodePtr code;

    ptime t;
    HLR k=0;
    HL_VolSurfacePtr vol = get_VolSurfacePtr(mktDataCollectorPtr, code);
    HLR v1 = vol->vol(t, k, t)->get_vol();

//    date d;

//    HLR v2 = vol->vol(d, k, date());


} // end HL_TEST_HL_VolSurface








//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FlatVolSurface
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_FlatVolSurface::HL_FlatVolSurface()
{

    classDefaultInit();



} // end HL_FlatVolSurface

//------------------------------------------------------------------------------------------------------

HL_FlatVolSurface::~HL_FlatVolSurface()
{
} // end ~HL_FlatVolSurface


//------------------------------------------------------------------------------------------------------

void HL_FlatVolSurface::classDefaultInit()
{

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_FlatVolSurface::descriptionImpl(std::ostream & os) const
{
    HL_VolSurface::descriptionImpl(os);

    hl_fillDescriptionStream(flatVol_);


} // end descriptionImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FlatVolSurface: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_HL_VolSurfaceCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_VolSurfaceCodePtr HL_TEST_get_HL_VolSurfaceCode(const HL_FinObjCodePtr & finObjCode)
{
    HL_VolSurfaceCodePtr volSurfaceCode(new HLVOL::HL_VolSurfaceCode);

    volSurfaceCode->set_sCode(finObjCode->get_sCode() + "_TEST_VOL");

    volSurfaceCode->set_ccyCode(finObjCode->get_ccyCode());

    return volSurfaceCode;

} // end HL_TEST_get_HL_VolSurfaceCode

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_HL_VolSurface
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_VolSurfacePtr HL_TEST_get_HL_VolSurface(const HL_VolSurfaceCodePtr &volSurfaceCode,
                                           const HL_RiskFreeDiscountingPtr &riskFreeDiscounting,
                                           HLR flatVolValue)
{



    HL_FlatVolSurfacePtr volSurface(new HLVOL::HL_FlatVolSurface);

    volSurface->set_HL_ObjCodePtr(volSurfaceCode);

    volSurface->set_flatVol(flatVolValue);

    volSurface->set_impliedVolModelTypeType(HL_ImpliedVolModelTypeType_Normal);


    volSurface->set_riskFreeDiscounting(riskFreeDiscounting);

    return volSurface;

} // end HL_TEST_get_HL_VolSurface






} // end namespace HL_VolSurfaces
} // end namespace HL_MarketData
} //end namespace HorizonLib
