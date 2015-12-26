/**
 FILE NAME= hl_bidimCubicSpline.cpp
 LIB= HorizonLib
 ADDED BY= A. Cesarini
 DATE= 20140203
 */
#include <hl/math/interpolation/hl_bidimCubicSpline.h>
#include <hl/math/interpolation/hl_cubicSpline.h> /* included just for HL_TEST_HL_2_D_CrossInterp*/

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINTP::HL_2_D_CrossInterp);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINTP::HL_2_D_CrossInterpControls);



namespace HorizonLib
{
namespace HL_Math
{
namespace HL_Interpolation
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_2_D_CrossInterpControls
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_2_D_CrossInterpControls::HL_2_D_CrossInterpControls()
{

    classDefaultInit();



} // end HL_2_D_CrossInterpControls

//------------------------------------------------------------------------------------------------------

HL_2_D_CrossInterpControls::~HL_2_D_CrossInterpControls()
{} // end ~HL_2_D_CrossInterpControls


//------------------------------------------------------------------------------------------------------

void HL_2_D_CrossInterpControls::classDefaultInit()
{} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_2_D_CrossInterpControls::descriptionImpl(std::ostream & os) const
{
    HL_InterpControls::descriptionImpl(os);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

HLS HL_2_D_CrossInterpControls::nLocalityPoints(HLS dimIdx) const
{
    /*
     * Ask to each direction
     * */
    if(dimIdx==0)
    {
        HL_FAIL("function cannot be implemented since nLocalityPoints(0 /*dimIdx*/) changes for different y_i");
    }
    else if(dimIdx==1)
    {
        return interpControlsPtr_y_->nLocalityPoints(0/*dimIdx*/);
    }

    HL_FAIL("expected dimIdx=0 or 1, dimIdx=" << dimIdx);

    return 0;

} // end nLocalityPoints





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_2_D_CrossInterp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_2_D_CrossInterp::HL_2_D_CrossInterp()
{

    classDefaultInit();

} // end HL_2_D_CrossInterp

//------------------------------------------------------------------------------------------------------

HL_2_D_CrossInterp::~HL_2_D_CrossInterp()
{} // end ~HL_2_D_CrossInterp

//------------------------------------------------------------------------------------------------------

void HL_2_D_CrossInterp::classDefaultInit()
{

    n_x_ = 0;
    n_y_ = 0;
    nLocalityPoints_y_=0;
    service_VEC_=VEC(1, 0);

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

HLR HL_2_D_CrossInterp::value_n_1(const VEC::const_iterator & b, const VEC::const_iterator & e)const
{

    HL_SR((e-b)==2);

    HLR x = *b;
    HLR y = *(b+1);

    const HL_Direction::HL_Localization & yLoc = yDir_->localize(y);

    HLS yIdxLeft = yLoc.localizationSides[HL_Direction::HL_Localization::Left].idx;

    HLS start_yIdx = (yIdxLeft>=nLocalityPoints_y_) ? (yIdxLeft-nLocalityPoints_y_) : 0;

    HLS end_yIdx = yIdxLeft+1+nLocalityPoints_y_;

    end_yIdx = (end_yIdx<n_y_) ? end_yIdx : (n_y_-1);


    HL_InterpolatorPtr yInterpolator = get_yInterpolator(x, start_yIdx, end_yIdx);

    service_VEC_[0]=y;

    HLR fValue=yInterpolator->value_n_1(service_VEC_.begin()/*b*/, service_VEC_.end()/*e*/);

    return fValue;

} // end value_n_1


//------------------------------------------------------------------------------------------------------

void HL_2_D_CrossInterp::finalize()
{
    HL_SRE(domainDim_==2, "cannot deal with domainDim_!=2, domainDim_=" << domainDim_);

    HL_SRE(get_directions().size()==domainDim_, "get_directions().size()=" << get_directions().size());


    n_x_ = get_nbPointsInDimension(0);

    n_y_ = get_nbPointsInDimension(1);


    set_yLocalInterpolationData();

    set_xInterpolators();



} // end finalize

//------------------------------------------------------------------------------------------------------

HL_InterpolatorPtr HL_2_D_CrossInterp::get_yInterpolator(HLR x, HLS start_yIdx, HLS end_yIdx) const
{

    std::vector<HL_DirectionPtr> yLocalDirVect(1);

    HL_DirectionPtr &yLocalDir=yLocalDirVect.front();

    yLocalDir.reset(new HL_Direction);

    VEC & v_yLocal = yLocalDir->get_x();

    HLS n_yLocalPoints = (end_yIdx-start_yIdx+1);

    v_yLocal.resize(n_yLocalPoints);

    HLCTRS::HL_MultiIndexHelper::ShapeType shape(1, n_yLocalPoints);

    HL_RealMultiArrayPtr realMultiArrayPtr(new HLCTRS::HL_RealMultiArray);

    realMultiArrayPtr->setShape(shape);

    HLMIDX multiIndex(1, 0);


    HLS &i=multiIndex[0];
    i=0;

    std::vector<HL_InterpolatorPtr>::const_iterator xInterps_cIt= xInterps_.begin()+start_yIdx;

    service_VEC_[0]=x;



    BOOST_FOREACH(HLR & y_i, v_yLocal)
    {
        y_i =yDir_->get_x(i+start_yIdx);

        HLR f_x_y_i = (*xInterps_cIt)->value_n_1(service_VEC_.begin()/*b*/, service_VEC_.end()/*e*/);

        realMultiArrayPtr->operator[](multiIndex) = f_x_y_i;


        ++i;
        ++xInterps_cIt;
    } // end for v_y_i

    yLocalDir->finalize();

    serviceInterpControlsPtr_y_->set_directions(yLocalDirVect);

    return interpolatorPtrFactory(serviceInterpControlsPtr_y_ /*interpControlsPtr*/, realMultiArrayPtr);

} // end get_yInterpolator




//------------------------------------------------------------------------------------------------------

void HL_2_D_CrossInterp::set_yLocalInterpolationData()
{

    HL_DYN_SHARED_PTR_CAST_OPERATION(HL_2_D_CrossInterpControls/*OutPtrType*/,
                                     bidimCrossInterpControls_/*outPtr*/,
                                     interpControlsPtr_/*inPtr*/);


    yDir_ = get_direction(1/*y*/);

    serviceInterpControlsPtr_y_ = bidimCrossInterpControls_->get_interpControlsPtr_y();

    HL_PNN(serviceInterpControlsPtr_y_);

    nLocalityPoints_y_=bidimCrossInterpControls_->nLocalityPoints(1/* dimIdx*/);



} // end set_yLocalInterpolationData

//------------------------------------------------------------------------------------------------------

void HL_2_D_CrossInterp::set_xInterpolators()
{
    xInterps_.resize(n_y_);

    const std::vector<HL_InterpControlsPtr> &interpControlsPtrVect_x = bidimCrossInterpControls_->get_interpControlsPtrVect_x();

    HL_SR(interpControlsPtrVect_x.size()==n_y_);



    HLS j=0;
    BOOST_FOREACH(HL_InterpolatorPtr & xInterps_j, xInterps_)
    {

        const HL_InterpControlsPtr & interpControlsPtr_x_j = interpControlsPtrVect_x[j];

        HL_SR(interpControlsPtr_x_j->get_directions().size()==1);

        HL_SR(get_direction(0/*x*/)->get_x()==interpControlsPtr_x_j->get_directions()[0]->get_x());


        BSP<HLCTRS::HL_SlicedMultiArray<HLR> > slicedMultiArray_j(new HLCTRS::HL_SlicedMultiArray<HLR>);

        std::map<HLS, HLS> fixedCoords_j;

        fixedCoords_j[1]=j;/* i.e. y-value is fixed to the one corresponding to y_j=this.getAbscissa(1 for y-dim, j for pointIdx)*/


        slicedMultiArray_j->set_inputMultiArray(realMultiArrayPtr_/*inputMultiArray*/, fixedCoords_j);

        xInterps_j= interpolatorPtrFactory(interpControlsPtr_x_j, slicedMultiArray_j);

        ++j;

    } // end for interpControlsPtr_j

} // end set_xInterpolators

//------------------------------------------------------------------------------------------------------

void HL_2_D_CrossInterp::descriptionImpl(std::ostream & os) const
{

    os << "HL_2_D_CrossInterp:\n";
    HL_Interpolator::descriptionImpl(os);




} // end descriptionImpl

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_2_D_CrossInterp: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


void HL_TEST_HL_2_D_CrossInterp(const HL_TEST_F & F_x,
                                const HL_TEST_F & F_y,
                                HLS n_x,
                                HLS n_y,
                                HL_InterpolatorType interpolatorType_x,
                                HL_CubicSplineBoundaryCondition leftBoundaryCondition_x,
                                HL_CubicSplineBoundaryCondition rightBoundaryCondition_x
                               )
{
    std::vector<HL_DirectionPtr> directions(2);

    HL_DirectionPtr & dir_x = directions[0];

    dir_x= HL_TEST_build_DirectionPtr(n_x, -30. /*x_0*/, .6/* dx*/);


    HL_DirectionPtr & dir_y = directions[1];

    dir_y= HL_TEST_build_DirectionPtr(n_y, 34. /*x_0*/, 2.1/* dx*/);


    HL_2_D_CrossInterpControlsPtr hl_2_D_CrossInterpControlsPtr(new HL_2_D_CrossInterpControls);

    /*
     * This specifies the bidimensional grid
     * */
    hl_2_D_CrossInterpControlsPtr->set_directions(directions);

    /*
     * This is to build L(y), see comment to HL_2_D_CrossInterpControlsPtr::interpControlsPtr_y_
     *  */
    HL_1_D_CubicInterpLocalParabolicControlsPtr interpControlsPtr_y(new HL_1_D_CubicInterpLocalParabolicControls);

    hl_2_D_CrossInterpControlsPtr->set_interpControlsPtr_y(interpControlsPtr_y);

    /*
     * Now we have to specifiy the vector HL_2_D_CrossInterpControls::interpControlsPtrVect_x_
     * */
    std::vector<HL_InterpControlsPtr> interpControlsPtrVect_x(n_y);

    HLS i_y=0;

    BOOST_FOREACH(HL_InterpControlsPtr & interpControlsPtr_x, interpControlsPtrVect_x)
    {

        HLR y_i = dir_y->get_x(i_y);

        HLR F_y_prime_i, F_y_second_i;

        HLR F_y_i = F_y.value(y_i, F_y_prime_i, F_y_second_i);

        HLR proportionalityFactor_F_i = F_y_i;

        HLR a,b;

        BSP<HL_1_D_CubicInterp> interpolatorPtr_x;
        interpControlsPtr_x = HL_TEST_1D_InterpControlsPtr(
                                  dir_x,
                                  a,
                                  b,
                                  F_x,
                                  /**
                                   * proportionalityFactor_F to be used to rescale F as one wants...
                                   * */
                                  proportionalityFactor_F_i,
                                  interpolatorType_x,
                                  leftBoundaryCondition_x,
                                  rightBoundaryCondition_x,
                                  /**
                                   * Another output of the method
                                   * */
                                  interpolatorPtr_x
                              );

        ++i_y;
    } // end for interpControlsPtr_x


    hl_2_D_CrossInterpControlsPtr->set_interpControlsPtrVect_x(interpControlsPtrVect_x);

    HL_2_D_CrossInterpPtr hl_2_D_CrossInterpPtr(new HL_2_D_CrossInterp);

    hl_2_D_CrossInterpPtr->set_interpControlsPtr(hl_2_D_CrossInterpControlsPtr);

    hl_2_D_CrossInterpPtr->instantiateMultiArray();

    HLMIDX multiIndex(2, 0);

    i_y=0;
    BOOST_FOREACH(HLR y_i, dir_y->get_x())
    {
        multiIndex[1]=i_y;

        HLR F_y_prime_i, F_y_second_i;

        HLR F_y_i = F_y.value(y_i, F_y_prime_i, F_y_second_i);

        HLS j_x=0;

        BOOST_FOREACH(HLR x_j, dir_x->get_x())
        {
            multiIndex[0]=j_x;

            HLR F_x_prime_j, F_x_second_j;

            HLR F_x_j = F_x.value(x_j, F_x_prime_j, F_x_second_j);

            HLR F_xy_i_j = F_y_i*F_x_j;

            hl_2_D_CrossInterpPtr->setPoint(multiIndex, F_xy_i_j/* value*/);


            ++j_x;
        } // end for x

        ++i_y;
    } // end for y_i


    hl_2_D_CrossInterpPtr->finalize();



    HLSER::HL_CoreSerializableObj csObj;

    csObj.oa() << hl_2_D_CrossInterpPtr;
    csObj.getReadyForDeserialization();

    HL_2_D_CrossInterpPtr hl_2_D_CrossInterpPtr_R;
    csObj.ia() >> hl_2_D_CrossInterpPtr_R;



    HLR nCheck=400;

    HLR xStart = dir_x->leftBorder();
    HLR xEnd = dir_x->rightBorder();
    HLR dx = (xEnd-xStart)/nCheck;

    HLR yStart = dir_y->leftBorder();
    HLR yEnd = dir_y->rightBorder();
    HLR dy = (yEnd-yStart)/nCheck;

    VEC xVect(2);

    for(HLS i=0;i<nCheck;++i)
    {
        HLR y_i = yStart+dy*i;
        HLR F_y_prime_i, F_y_second_i;
        HLR F_y_i = F_y.value(y_i, F_y_prime_i, F_y_second_i);

        xVect[1]=y_i;

        for(HLS j=0;j<nCheck;++j)
        {
            HLR x_j = xStart+j*dx;

            xVect[0]=x_j;

            HLR F_x_prime_j, F_x_second_j;

            HLR F_x_j = F_x.value(x_j, F_x_prime_j, F_x_second_j);

            HLR F_xy_i_j = F_y_i*F_x_j;

            HLR F_xy_i_j_interp = hl_2_D_CrossInterpPtr_R->value_n_1(xVect.begin(), xVect.end());


            HL_REQ_EQUAL_FLOATS_N(F_xy_i_j, F_xy_i_j_interp, 1000);

        } // end for j

    } // end for i


} // end HL_TEST_HL_2_D_CrossInterp

//------------------------------------------------------------------------------------------------------

void HL_TEST_HL_2_D_CrossInterpAll()
{

    HLS n_x=25;
    HLS n_y=40;


    //************************************/
    {
        HL_TEST_F F_x;

        F_x.a=-3;
        F_x.b=+3;
        F_x.c=-.33;
        F_x.d=.04;

        HL_InterpolatorType interpolatorType_x = HL_InterpolatorType_1_D_CubicSpline;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition_x = HL_CubicSplineBoundaryCondition_FirstDerivative;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition_x = HL_CubicSplineBoundaryCondition_FirstDerivative;

        /*
         * The y-direction is exact only if we use a parabola (at most) since the y-direction interpolator
         * built insider method HL_TEST_HL_2_D_CrossInterp will be parabolic
         *
         * */
        HL_TEST_F F_y;

        F_y.a=-2.3;
        F_y.b=+1;
        F_y.c=.33;
        /*
         * zero to get a parabola... the cubic would be to much to have perfect match between exact and interpolated results.
         */
        F_y.d=0.00;

        HL_TEST_HL_2_D_CrossInterp(F_x,
                                   F_y,
                                   n_x,
                                   n_y,
                                   interpolatorType_x,
                                   leftBoundaryCondition_x,
                                   rightBoundaryCondition_x
                                  );


    }

    //************************************/
    {
        HL_TEST_F F_x;

        F_x.a=-3;
        F_x.b=+3;
        F_x.c=-.33;
        F_x.d=.04;

        HL_InterpolatorType interpolatorType_x = HL_InterpolatorType_1_D_CubicSpline;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition_x = HL_CubicSplineBoundaryCondition_SecondDerivative;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition_x = HL_CubicSplineBoundaryCondition_SecondDerivative;

        /*
         * The y-direction is exact only if we use a parabola (at most) since the y-direction interpolator
         * built insider method HL_TEST_HL_2_D_CrossInterp will be parabolic
         *
         * */
        HL_TEST_F F_y;

        F_y.a=-2.3;
        F_y.b=+1;
        F_y.c=4.33;
        /*
         * zero to get a parabola... the cubic would be to much to have perfect match between exact and interpolated results.
         */
        F_y.d=0.00;

        HL_TEST_HL_2_D_CrossInterp(F_x,
                                   F_y,
                                   n_x,
                                   n_y,
                                   interpolatorType_x,
                                   leftBoundaryCondition_x,
                                   rightBoundaryCondition_x
                                  );


    }

    //************************************/
    n_x=50;
    n_y=2;
    /*
     * Here we have to set F_y.c=0 otherwise the match won't be perfect since the y-dir interpolation will be linear and hence
     * one cannot perfectly match a parabola (case F_y.c!=0) with a straight line.
     *  */
    {
        HL_TEST_F F_x;

        F_x.a=-3;
        F_x.b=+3;
        F_x.c=-.33;
        F_x.d=.04;

        HL_InterpolatorType interpolatorType_x = HL_InterpolatorType_1_D_CubicSpline;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition_x = HL_CubicSplineBoundaryCondition_SecondDerivative;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition_x = HL_CubicSplineBoundaryCondition_SecondDerivative;


        HL_TEST_F F_y;

        F_y.a=-2.3;
        F_y.b=+1;
        F_y.c=0;
        F_y.d=0;

        HL_TEST_HL_2_D_CrossInterp(F_x,
                                   F_y,
                                   n_x,
                                   n_y,
                                   interpolatorType_x,
                                   leftBoundaryCondition_x,
                                   rightBoundaryCondition_x
                                  );


    }


    //************************************/
    n_x=50;
    n_y=1;
    /*
     * Here we have to set F_y to be constant otherwise the match won't be perfect since the y-dir interpolation will be constant and hence
     * one cannot perfectly match with a constant something that is not constant.
     *  */
    {
        HL_TEST_F F_x;

        F_x.a=-3;
        F_x.b=+3;
        F_x.c=-.33;
        F_x.d=.04;

        HL_InterpolatorType interpolatorType_x = HL_InterpolatorType_1_D_CubicSpline;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition_x = HL_CubicSplineBoundaryCondition_SecondDerivative;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition_x = HL_CubicSplineBoundaryCondition_SecondDerivative;


        HL_TEST_F F_y;

        F_y.a=-2.3;
        F_y.b=0;
        F_y.c=0;
        F_y.d=0.00;

        HL_TEST_HL_2_D_CrossInterp(F_x,
                                   F_y,
                                   n_x,
                                   n_y,
                                   interpolatorType_x,
                                   leftBoundaryCondition_x,
                                   rightBoundaryCondition_x
                                  );


    }
    //************************************/
    n_x=2;
    n_y=10;
    /*
     * Now we do similar tests both for n_x=1,2
     *  */
    {
        HL_TEST_F F_x;

        F_x.a=-3;
        F_x.b=+3;
        F_x.c=0;
        F_x.d=0;

        HL_InterpolatorType interpolatorType_x = HL_InterpolatorType_1_D_CubicSpline;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition_x = HL_CubicSplineBoundaryCondition_SecondDerivative;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition_x = HL_CubicSplineBoundaryCondition_SecondDerivative;

        /*
         * The y-direction is exact only if we use a parabola (at most) since the y-direction interpolator
         * built insider method HL_TEST_HL_2_D_CrossInterp will be parabolic
         *
         * */
        HL_TEST_F F_y;

        F_y.a=-2.3;
        F_y.b=+1;
        F_y.c=.7;
        /*
         * zero to get a parabola... the cubic would be to much to have perfect match between exact and interpolated results.
         */
        F_y.d=0.00;

        HL_TEST_HL_2_D_CrossInterp(F_x,
                                   F_y,
                                   n_x,
                                   n_y,
                                   interpolatorType_x,
                                   leftBoundaryCondition_x,
                                   rightBoundaryCondition_x
                                  );


    }
    //************************************/
    n_x=1;
    n_y=10;
    /*
     * Now we do similar tests both for n_x=1,2
     *  */
    {
        HL_TEST_F F_x;

        F_x.a=-3;
        F_x.b=0;
        F_x.c=0;
        F_x.d=0;

        HL_InterpolatorType interpolatorType_x = HL_InterpolatorType_1_D_CubicSpline;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition_x = HL_CubicSplineBoundaryCondition_SecondDerivative;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition_x = HL_CubicSplineBoundaryCondition_SecondDerivative;

        /*
         * The y-direction is exact only if we use a parabola (at most) since the y-direction interpolator
         * built insider method HL_TEST_HL_2_D_CrossInterp will be parabolic
         *
         * */
        HL_TEST_F F_y;

        F_y.a=-2.3;
        F_y.b=+1;
        F_y.c=.7;
        /*
         * zero to get a parabola... the cubic would be to much to have perfect match between exact and interpolated results.
         */
        F_y.d=0.00;

        HL_TEST_HL_2_D_CrossInterp(F_x,
                                   F_y,
                                   n_x,
                                   n_y,
                                   interpolatorType_x,
                                   leftBoundaryCondition_x,
                                   rightBoundaryCondition_x
                                  );


    }
    //************************************/
    n_x=2;
    n_y=2;
    /*
     * Few points both in x-dir and y-dir
     *  */
    {
        HL_TEST_F F_x;

        F_x.a=-3;
        F_x.b=1;
        F_x.c=0;
        F_x.d=0;

        HL_InterpolatorType interpolatorType_x = HL_InterpolatorType_1_D_CubicSpline;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition_x = HL_CubicSplineBoundaryCondition_SecondDerivative;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition_x = HL_CubicSplineBoundaryCondition_SecondDerivative;


        HL_TEST_F F_y;

        F_y.a=-2.3;
        F_y.b=+1;
        F_y.c=0;
        F_y.d=0.00;

        HL_TEST_HL_2_D_CrossInterp(F_x,
                                   F_y,
                                   n_x,
                                   n_y,
                                   interpolatorType_x,
                                   leftBoundaryCondition_x,
                                   rightBoundaryCondition_x
                                  );


    }



    HL_SUCCESSFULL_TEST(HL_TEST_HL_2_D_CrossInterpAll);


} // end HL_TEST_HL_2_D_CrossInterpAll


} // end namespace HL_Interpolation
} // end namespace HL_Math
} //end namespace HorizonLib
