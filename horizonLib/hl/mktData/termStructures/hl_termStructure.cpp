/**
FILE NAME= hl_termStructure.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131213
*/
#include <hl/mktData/termStructures/hl_termStructure.h>
#include <hl/mktData/hl_mktDataCollector.h>
#include <hl/math/interpolation/hl_multiLinearInterp.h>
#include <hl/math/interpolation/hl_cubicSpline.h>


HL_SERIALIZATION_CLASS_EXPORT_GUID(HLTS::HL_TermStructure);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLTS::HL_TermStructureCode);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLTS::HL_InterpTermStructure);

namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_TermStructures
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TermStructureCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_TermStructureCode::HL_TermStructureCode()
{
    classDefaultInit();

} // end HL_TermStructureCode

//------------------------------------------------------------------------------------------------------

HL_TermStructureCode::~HL_TermStructureCode()
{} // end ~HL_TermStructureCode

//------------------------------------------------------------------------------------------------------

void HL_TermStructureCode::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

HLSTRING HL_TermStructureCode::objTypeImpl() const
{
    return "HL_TermStructureCode";
} // end objTypeImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TermStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_TermStructure::HL_TermStructure()
{

    classDefaultInit();



} // end HL_TermStructure

//------------------------------------------------------------------------------------------------------

HL_TermStructure::~HL_TermStructure()
{} // end ~HL_TermStructure


//------------------------------------------------------------------------------------------------------

void HL_TermStructure::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_TermStructure::descriptionImpl(std::ostream & os) const
{
    HL_MktData::descriptionImpl(os);



} // end descriptionImpl

//------------------------------------------------------------------------------------------------------


void HL_TermStructure::set_HL_ObjCodePtr(const HL_ObjCodePtr & hl_ObjCodePtr)
{

    HL_MktData::set_HL_ObjCodePtr(hl_ObjCodePtr);


    HL_DYN_SHARED_PTR_CAST_OPERATION(HLTS::HL_TermStructureCode, termStructureCode_ /*outPtr*/, hl_ObjCodePtr_ /*inPtr*/);



} // end set_HL_ObjCodePtr


//------------------------------------------------------------------------------------------------------


HLR HL_TermStructure::df(const ptime &t) const
{

    HLR yf = get_yf(t);
    HLR discount = df(yf);

    /*
    do the mkt data tracking
    */
    const HL_MktDataTrackerContainerPtr & mktDataTrackerContainerPtr=
            get_mktDataCollector()->get_mktDataTrackerContainerPtr();

    mktDataTrackerContainerPtr->addTermStructurePoint(termStructureCode_, yf, discount/* value*/);

    return discount;

} // end df



//------------------------------------------------------------------------------------------------------


HLR HL_TermStructure::df(HLR t) const
{

    HL_UNEXPECTED_FUNCTION_CALL;

    return HL_NAN;

} // end df


//------------------------------------------------------------------------------------------------------


HLR HL_TermStructure::get_yf(const ptime &t) const
{

    HLR yf = HLDT::act_yf(get_refTime(), t);
    return yf;


} // end get_yf




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TermStructure: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_TermStructurePtr get_TermStructurePtr(const HL_MktDataCollectorPtr & mktDataCollectorPtr, const HL_ObjCodePtr & objCodePtr)
{

    return get_mktData<HL_TermStructurePtr>(mktDataCollectorPtr, objCodePtr);

} // end get_TermStructurePtr




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterpTermStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_InterpTermStructure::HL_InterpTermStructure()
{

    classDefaultInit();



} // end HL_InterpTermStructure

//------------------------------------------------------------------------------------------------------

HL_InterpTermStructure::~HL_InterpTermStructure()
{} // end ~HL_InterpTermStructure


//------------------------------------------------------------------------------------------------------

void HL_InterpTermStructure::classDefaultInit()
{

    HL_ENUM_DEFAULT_INIT(HL_DiscountFactorInterpVariableType, discountFactorInterpVariableType_);
    HL_ENUM_DEFAULT_INIT(HLINTP::HL_InterpolatorType, discountFactorInterpType_);


    nbNodes_=0;

    tVec_=VEC(1, 0);

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_InterpTermStructure::descriptionImpl(std::ostream & os) const
{
    HL_TermStructure::descriptionImpl(os);

    HL_DESCRIBE_ENUM(os, discountFactorInterpVariableType_);
    HL_DESCRIBE_ENUM(os, discountFactorInterpType_);
    hl_fillDescriptionStream(interpolatorPtr_);
    //hl_fillDescriptionStream(nodeDates_);
    hl_fillDescriptionStream(nodeTimes_);
    hl_fillDescriptionStream(nbNodes_);



} // end descriptionImpl
//------------------------------------------------------------------------------------------------------

void HL_InterpTermStructure::setNodeDates(const std::vector<date> & nodeDates)
{


    HLS nbNodes =  nodeDates.size();

    const date & refDate = get_refDate();

    HL_SR(nodeDates.front()==refDate);

    VEC nodeTimes(nbNodes);

    for(HLS i=0;i<nbNodes;i++)
    {

        const date & currentDate = nodeDates[i];

        HL_SRE(i==0 || currentDate>nodeDates[i-1], "i=" << i << ", currentDate=" << currentDate);

        HLR yf = get_yf(ptime(currentDate));

        nodeTimes[i] = yf;

    } // end for v_y_i

    setNodeTimes(nodeTimes);


} // end setNodeDates

//------------------------------------------------------------------------------------------------------

void HL_InterpTermStructure::setNodeTimes(const VEC & nodeTimes)
{

    nodeTimes_=nodeTimes;

    nbNodes_ =  nodeTimes.size();

    HL_SR(nbNodes_);

    HL_REQ_RANGE_IS_ORDERED_L(nodeTimes_.begin(), nodeTimes_.end(), nodeTimes_);

    setInterpolator();

} // end setNodeTimes


//------------------------------------------------------------------------------------------------------


void HL_InterpTermStructure::setNodeDiscount(HLS nodeIdx, HLR nodeDiscount)
{

    HLR nodeValue = getInterpolationVariable(nodeDiscount, nodeIdx);

    setNodeValue(nodeIdx, nodeValue);

    if(nodeIdx==1 && discountFactorInterpVariableType_==HL_DiscountFactorInterpVariableType_Rate){
        // Needed since otherwise we cannot define the rate for t=0
        setNodeValue(nodeIdx-1, nodeValue);
    }


} // end setNodeDiscount



//------------------------------------------------------------------------------------------------------

HLR HL_InterpTermStructure::getInterpolationVariable(HLR nodeDiscount, HLS nodeIdx)
{

    HL_SRE(nodeDiscount>0., "nodeDiscount=" << nodeDiscount << ", nodeIdx=" << nodeIdx);

    HL_SR(nodeIdx<nbNodes_);


    HLR interpVariable;

    switch(discountFactorInterpVariableType_)
    {
    case HL_DiscountFactorInterpVariableType_Discount:
        interpVariable = nodeDiscount;
        break;
    case HL_DiscountFactorInterpVariableType_RateTime:
        interpVariable = std::log(nodeDiscount);
        break;
    case HL_DiscountFactorInterpVariableType_Rate:
    {
        HLR t = nodeTimes_[nodeIdx];
        if(t>0)
            interpVariable =  std::log(nodeDiscount) / t;
        else
            interpVariable =HL_NAN;


    }
        break;
    default:
        HL_FAIL("invalid discountFactorInterpVariableType_=" << discountFactorInterpVariableType_);

    } // end switch discountFactorInterpVariableType_

    return interpVariable;

} // end getInterpolationVariable

//------------------------------------------------------------------------------------------------------


HLR HL_InterpTermStructure::df(HLR t) const
{

    (*tVec_.begin())=t;

    HLR interpVariable= interpolatorPtr_->value_n_1(tVec_.begin(), tVec_.end());

    HLR df_t = getDiscountFactorFromInterpolationVariable(interpVariable, t);

    return df_t;

} // end df


//------------------------------------------------------------------------------------------------------

void HL_InterpTermStructure::setNodeValue(HLS nodeIdx, HLR nodeValue)
{

    interpolatorPtr_->setPoint(HLMIDX(1, nodeIdx), nodeValue);

} // end setNodeValue

//------------------------------------------------------------------------------------------------------

HLR HL_InterpTermStructure::getNodeValue(HLS nodeIdx) const
{

    return interpolatorPtr_->getPoint(HLMIDX(1, nodeIdx));

} // end getNodeValue

//------------------------------------------------------------------------------------------------------

HLR HL_InterpTermStructure::getDiscountFactorFromInterpolationVariable(HLR interpVariable, HLR t) const
{


    HLR df_t;

    switch(discountFactorInterpVariableType_)
    {
    case HL_DiscountFactorInterpVariableType_Discount:
        df_t = interpVariable;
        break;
    case HL_DiscountFactorInterpVariableType_RateTime:
        df_t = std::exp(interpVariable);
        break;
    case HL_DiscountFactorInterpVariableType_Rate:
        df_t = std::exp(interpVariable * t);
        break;
    default:
        HL_FAIL("invalid discountFactorInterpVariableType_=" << discountFactorInterpVariableType_);

    } // end switch discountFactorInterpVariableType_

    return df_t;


} // end getDiscountFactorFromInterpolationVariable

//------------------------------------------------------------------------------------------------------

void HL_InterpTermStructure::setInterpolator()
{


    std::vector<HL_DirectionPtr> directions(1);

    HL_DirectionPtr & dir = directions.front();

    dir.reset(new HLINTP::HL_Direction);
    dir->set_x(nodeTimes_);

    dir->set_extrapolateLeft(false);
    dir->set_extrapolateLeft(false);

    HL_InterpControlsPtr interpControlsBasePtr;

    switch(discountFactorInterpType_)
    {
    case HLINTP::HL_InterpolatorType_n_D_Linear:
    {
        HL_InterpControlsPtr interpControlsPtr(new HLINTP::HL_n_D_MultiLinearInterpControls);
        interpControlsPtr->set_directions(directions);

        interpControlsBasePtr=interpControlsPtr;
        interpolatorPtr_.reset(new HLINTP::HL_n_D_MultiLinearInterp);

    }
        break;
    case HLINTP::HL_InterpolatorType_1_D_CubicSpline:
    {
        HL_1_D_CubicSplineInterpControlsPtr interpControlsPtr(new HLINTP::HL_1_D_CubicSplineInterpControls);

        interpControlsPtr->set_directions(directions);

        interpControlsPtr->set_leftBoundaryCondition(HLINTP::HL_CubicSplineBoundaryCondition_SecondDerivative);
        interpControlsPtr->set_rightBoundaryCondition(HLINTP::HL_CubicSplineBoundaryCondition_SecondDerivative);
        interpControlsPtr->set_leftValue(0);
        interpControlsPtr->set_rightValue(0);

        interpControlsBasePtr=interpControlsPtr;
        interpolatorPtr_.reset(new HLINTP::HL_1_D_CubicSplineInterp);


    }
        break;
    case HLINTP::HL_InterpolatorType_1_D_CubicLocalParabolic:
    {

        HL_1_D_CubicInterpLocalParabolicControlsPtr interpControlsPtr(new HLINTP::HL_1_D_CubicInterpLocalParabolicControls);
        interpControlsPtr->set_directions(directions);

        interpControlsBasePtr=interpControlsPtr;
        interpolatorPtr_.reset(new HLINTP::HL_1_D_CubicInterpLocalParabolic);


    }
        break;
    default:
        HL_FAIL("invalid discountFactorInterpType_=" << discountFactorInterpType_);

    } // end switch discountFactorInterpType_

    interpolatorPtr_->set_interpControlsPtr(interpControlsBasePtr);

    interpolatorPtr_->instantiateMultiArray();


} // end setInterpolator




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterpTermStructure: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




} // end namespace HL_TermStructures
} // end namespace HL_MarketData
} //end namespace HorizonLib
