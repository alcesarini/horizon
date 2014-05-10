/**
FILE NAME= hl_multiArray.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131228
*/
#include <hl/containers/hl_multiArray.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLCTRS::HL_RealMultiArray);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLCTRS::HL_RealSlicedMultiArray);


namespace HorizonLib
{
namespace HL_Containers
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MultiIndexHelper
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_MultiIndexHelper::HL_MultiIndexHelper()
{

    classDefaultInit();



} // end HL_MultiIndexHelper

//------------------------------------------------------------------------------------------------------

HL_MultiIndexHelper::~HL_MultiIndexHelper()
{} // end ~HL_MultiIndexHelper


//------------------------------------------------------------------------------------------------------

void HL_MultiIndexHelper::classDefaultInit()
{
    nDim_=0;
    nObjs_=0;
    powers_.clear();
    shape_.clear();

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_MultiIndexHelper::setShape(const ShapeType & shape)
{

    shape_=shape;
    nDim_ = shape_.size();

    HL_SR(nDim_>0);

    powers_ = std::vector<HLS>(nDim_);

    std::vector<HLS>::iterator powers_it=powers_.begin();

    nObjs_=1;

    BOOST_FOREACH(HLS shape_i, shape_)
    {

        (*powers_it) = nObjs_;

        nObjs_*=shape_i;

        ++powers_it;

    } // end for shape_i

} // end setShape

//------------------------------------------------------------------------------------------------------

HLS HL_MultiIndexHelper::linearIdx(const HLMIDX & multiIndex) const
{

    HL_SR(multiIndex.size()==nDim_);

    HLS linIdx=0;

    std::vector<HLS>::const_iterator powers_cIt=powers_.begin();

    BOOST_FOREACH(HLS m_i, multiIndex)
    {
        linIdx+=(m_i*(*powers_cIt));

        ++powers_cIt;
    } // end for m_i

    return linIdx;

} // end linearIdx

//------------------------------------------------------------------------------------------------------

void HL_MultiIndexHelper::descriptionImpl(std::ostream & os) const
{
    Descriptable::descriptionImpl(os);

    hl_fillDescriptionStream(nDim_);
    hl_fillDescriptionStream(nObjs_);

    HLI i=0;
    BOOST_FOREACH(HLS shape_i, shape_)
    {
        os << "shape[" << i << "]=" << shape_i << "\n";
        ++i;
    } // end for shape_i

} // end descriptionImpl




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MultiIndexHelper: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MultiArray: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



} // end namespace HL_Containers
} //end namespace HorizonLib
