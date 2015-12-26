/**
FILE NAME= hl_interpolator.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131227
*/
#include <hl/math/interpolation/hl_interpolator.h>
#include <hl/math/hl_mathUtils.h>
#include <hl/math/interpolation/hl_multiLinearInterp.h>
#include <hl/math/interpolation/hl_cubicSpline.h>
#include <hl/math/interpolation/hl_bidimCubicSpline.h>


HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINTP::HL_InterpControls);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINTP::HL_Interpolator);





namespace HorizonLib
{
namespace HL_Math
{
namespace HL_Interpolation
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Direction
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



HL_Direction::HL_Direction()
{

    classDefaultInit();

} // end HL_Direction

//------------------------------------------------------------------------------------------------------

HL_Direction::~HL_Direction()
{} // end ~HL_Direction


//------------------------------------------------------------------------------------------------------

void HL_Direction::classDefaultInit()
{

    extrapolateLeft_=false;
    extrapolateRight_=false;

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_Direction::set_x(const VEC &x)
{
    x_=x;
    finalize();

} // end set_x

//------------------------------------------------------------------------------------------------------


void HL_Direction::finalize()
{
    HL_REQ_IS_ORDERED_L(x_);

    if(x_.size()==1)
    {

        // degenerate case (only one point)
        delta_x_.clear();

        HL_LocalizationSide & leftSide = localization_.localizationSides[HL_Localization::Left];
        HL_LocalizationSide & rightSide = localization_.localizationSides[HL_Localization::Right];

        leftSide.idx=0;
        rightSide.idx=0;
        leftSide.weight=1;
        rightSide.weight=0;

    }
    else if(x_.size()>1)
    {

        delta_x_.resize(x_.size()-1);

        VEC::iterator delta_x_it = delta_x_.begin();
        VEC::const_iterator x_cIt = x_.begin();
        VEC::const_iterator xNext_cIt = x_cIt;

        while((++xNext_cIt)!=x_.end())
        {

            *delta_x_it = *xNext_cIt - *x_cIt;
            x_cIt = xNext_cIt;
            ++delta_x_it;

        } // end while

    }
    else
    {

        HL_FAIL("expected x_.size()>0");
    }

} // end finalize



//------------------------------------------------------------------------------------------------------
/**
It should hold that x_.size()>0: this is not checked anyway.

Suppose x is such that x_[i]<x<=x[i+1] for i+1<x_.size(), then
localization_.leftIdx=i
localization_.rightIdx=i+1
localization_.leftWeight=(x_[i+1]-x)/(x_[i+1]-x_[i])
localization_.rightWeight=1-localization_.leftWeight

Similarly if x>x_.back(), the same holds with:
i ---> x_.size()-2
i+1 ---> x_.size()-1


Similarly if x<=x_.front(), the same holds with:
i ---> 0
i+1 ---> 1

If x_.size()=1, it always holds that
i ---> 0
i+1 ---> 0
localization_.leftWeight=1
localization_.rightWeight=0

*/
const HL_Direction::HL_Localization & HL_Direction::localize(HLR x) const
{

    if(x_.size()>1)
    {

        VEC::const_iterator rightIt = std::lower_bound(x_.begin(), x_.end(), x);


        if(rightIt==x_.begin())
        {
            ++rightIt;

        }
        else if(rightIt==x_.end())
        {
            --rightIt;

        }

        HL_LocalizationSide & leftSide = localization_.localizationSides[HL_Localization::Left];
        HL_LocalizationSide & rightSide = localization_.localizationSides[HL_Localization::Right];

        rightSide.idx=rightIt-x_.begin();
        leftSide.idx=rightSide.idx-1;

        HLR dx = delta_x_[leftSide.idx];

        leftSide.weight=(*rightIt - x)/dx;

        if(leftSide.weight>1 && !extrapolateLeft_)
        {
            leftSide.weight=1;
        }
        else if(leftSide.weight<0 && !extrapolateRight_)
        {
            leftSide.weight=0;
        }


        rightSide.weight=1-leftSide.weight;

    } // end if(x_.size()>1)

    return localization_;

} // end localize



//------------------------------------------------------------------------------------------------------

void HL_Direction::descriptionImpl(std::ostream & os) const
{
    Descriptable::descriptionImpl(os);

    hl_fillDescriptionStream(x_);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Direction: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterpControls
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_InterpControls::HL_InterpControls()
{

    classDefaultInit();



} // end HL_InterpControls

//------------------------------------------------------------------------------------------------------

HL_InterpControls::~HL_InterpControls()
{} // end ~HL_InterpControls


//------------------------------------------------------------------------------------------------------

void HL_InterpControls::classDefaultInit()
{} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_InterpControls::descriptionImpl(std::ostream & os) const
{
    Descriptable::descriptionImpl(os);

    HL_DESCRIBE_ENUM(os, get_InterpolatorType());



} // end descriptionImpl







//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Interpolator
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_Interpolator::HL_Interpolator()
{

    classDefaultInit();



} // end HL_Interpolator

//------------------------------------------------------------------------------------------------------

HL_Interpolator::~HL_Interpolator()
{} // end ~HL_Interpolator


//------------------------------------------------------------------------------------------------------

void HL_Interpolator::classDefaultInit()
{} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_Interpolator::set_interpControlsPtr(const HL_InterpControlsPtr &interpControlsPtr)
{

    interpControlsPtr_=interpControlsPtr;

    HL_PNN(interpControlsPtr_);


    domainDim_ = interpControlsPtr_->get_nDim();

    HL_SR(domainDim_>0);



} // end set_interpControlsPtr

//------------------------------------------------------------------------------------------------------


void HL_Interpolator::instantiateMultiArray()
{

    realMultiArrayPtr_.reset(new HLCTRS::HL_RealMultiArray);

    realMultiArrayPtr_->setShape(get_shape());

} // end instantiateMultiArray


//------------------------------------------------------------------------------------------------------

void HL_Interpolator::set_realMultiArrayPtr(const HL_RealMultiArrayPtr &realMultiArrayPtr)
{

    realMultiArrayPtr_=realMultiArrayPtr;

    HL_PNN(realMultiArrayPtr_);

    HLCTRS::HL_MultiIndexHelper::ShapeType requiredShape = get_shape();

    HL_SRE(realMultiArrayPtr_->get_shape()==requiredShape, hl_container_description(realMultiArrayPtr_->get_shape())
           << hl_container_description(requiredShape));

    finalize();


} // end set_realMultiArrayPtr


//------------------------------------------------------------------------------------------------------

HL_Disposable<HLCTRS::HL_MultiIndexHelper::ShapeType> HL_Interpolator::get_shape() const
{

    HLCTRS::HL_MultiIndexHelper::ShapeType shape(domainDim_);
    HLS i=0;
    BOOST_FOREACH(const HL_DirectionPtr & dir, get_directions())
    {
        shape[i] = dir->nbPoints();
        ++i;
    } // end for dir

    return shape;
} // end get_shape

//------------------------------------------------------------------------------------------------------

void HL_Interpolator::localize(const VEC::const_iterator & b, const VEC::const_iterator & e) const
{
    VEC::const_iterator it= b;

    BOOST_FOREACH(const HL_DirectionPtr & dir, get_directions())
    {
        dir->localize(*it);
        ++it;
    } // end for dir

} // end localize


//------------------------------------------------------------------------------------------------------

void HL_Interpolator::descriptionImpl(std::ostream & os) const
{
    os << "HL_Interpolator:\n";
    HL_RealFunction_n_1::descriptionImpl(os);
    hl_fillDescriptionStream(realMultiArrayPtr_);
} // end descriptionImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Interpolator: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_InterpolatorPtr interpolatorPtrFactory(const HL_InterpControlsPtr &interpControlsPtr,
        const HL_RealMultiArrayPtr &realMultiArrayPtr)
{

    HL_PNN(interpControlsPtr);


    HL_InterpolatorPtr interpolatorPtr;

    switch(interpControlsPtr->get_InterpolatorType())
    {
    case HL_InterpolatorType_n_D_Linear:
        interpolatorPtr.reset(new HL_n_D_MultiLinearInterp);
        break;
    case HL_InterpolatorType_1_D_CubicSpline:
        interpolatorPtr.reset(new HL_1_D_CubicSplineInterp);
        break;
    case HL_InterpolatorType_1_D_CubicLocalParabolic:
        interpolatorPtr.reset(new HL_1_D_CubicInterpLocalParabolic);
        break;
    case HL_InterpolatorType_2_D_CrossInterp:
        interpolatorPtr.reset(new HL_2_D_CrossInterp);
        break;
    default:
        HL_FAIL("invalid interpControlsPtr->get_InterpolatorType()=" << interpControlsPtr->get_InterpolatorType());
    } // end switch interpControlsPtr->get_InterpolatorType()

    interpolatorPtr->set_interpControlsPtr(interpControlsPtr);
    /*
     * Here we don't call instantiateMultiArray() since we use realMultiArrayPtr
     *  */
    interpolatorPtr->set_realMultiArrayPtr(realMultiArrayPtr);


    return interpolatorPtr;

} // end interpolatorPtrFactory


} // end namespace HL_Interpolation
} // end namespace HL_Math
} //end namespace HorizonLib
