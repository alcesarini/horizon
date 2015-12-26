/**
 FILE NAME= hl_cubicSpline.cpp
 LIB= HorizonLib
 ADDED BY= A. Cesarini
 DATE= 20140111
 */
#include <hl/math/interpolation/hl_cubicSpline.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINTP::HL_1_D_CubicSplineInterpControls);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINTP::HL_1_D_CubicSplineInterp);

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINTP::HL_1_D_CubicInterpLocalParabolicControls);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINTP::HL_1_D_CubicInterpLocalParabolic);





namespace HorizonLib
{
namespace HL_Math
{
namespace HL_Interpolation
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_1_D_CubicInterp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_1_D_CubicInterp::HL_1_D_CubicInterp()
{

    classDefaultInit();

} // end HL_1_D_CubicInterp

//------------------------------------------------------------------------------------------------------

HL_1_D_CubicInterp::~HL_1_D_CubicInterp()
{} // end ~HL_1_D_CubicInterp

//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicInterp::classDefaultInit()
{

    applyMonotonicitConstraint_=false;
    serviceMultiIndex_=HLMIDX(1, 0);
    nPoints_=0;
    nPoints_minus_1_=0;
    nPoints_minus_2_=0;
    nPoints_minus_3_=0;



} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

HLR HL_1_D_CubicInterp::value_n_1(const VEC::const_iterator & b, const VEC::const_iterator & e)const
{

    localize(b, e);

    if(nonCubic())
        return nonCubicOperator();


    const HL_Direction::HL_LocalizationSide & locSideRight =
            dir()->get_localization().localizationSides[HL_Direction::HL_Localization::Right];

    HLS leftIdx = locSideRight.idx-1;

    HLR rightWeight = locSideRight.weight;

    HLR a_leftIdx = a_[leftIdx];
    HLR b_leftIdx = b_[leftIdx];
    HLR c_leftIdx = c_[leftIdx];


    HLR fValue= f(leftIdx) + rightWeight*(a_leftIdx + rightWeight*(b_leftIdx + rightWeight*c_leftIdx));

    return fValue;

} // end value_n_1
//------------------------------------------------------------------------------------------------------


void HL_1_D_CubicInterp::set_interpControlsPtr(const HL_InterpControlsPtr &interpControlsPtr)
{

    HL_Interpolator::set_interpControlsPtr(interpControlsPtr);

    preInit();

} // end set_interpControlsPtr


//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicInterp::preInit()
{
    HL_SRE(domainDim_==1, "cannot deal with domainDim_!=1, nDim_=" << domainDim_);

    HL_SRE(get_directions().size()==domainDim_, "get_directions().size()=" << get_directions().size());

    nPoints_ =dir()->nbPoints();

    HL_SRE(nPoints_>=1, "nPoints_=" << nPoints_);

    if(nonCubic())
    {
        /**
         * In case nPoints_=2 the class gets linear, in case nPoints_=1 the class gets constant
         *  */
        return;
    }
    nPoints_minus_1_=nPoints_-1;
    nPoints_minus_2_=nPoints_-2;
    nPoints_minus_3_=nPoints_-3;

    d_.resize(nPoints_);

    a_.resize(nPoints_minus_1_);
    b_.resize(nPoints_minus_1_);
    c_.resize(nPoints_minus_1_);

} // end preInit


//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicInterp::finalize()
{


    if(nonCubic())
    {
        /**
         * In case nPoints_=2 the class gets linear, in case nPoints_=1 the class gets constant
         *  */
        return;
    }


    computeIncrements();


    computeFirstDerivativeAtNodes();


    applyMonotonicitConstraint();


    computeCubicCoefficientsLoop();


} // end finalize


//------------------------------------------------------------------------------------------------------


void HL_1_D_CubicInterp::setPointAndPerformInterpolationComputations(HLS xIdx,
                                                                     HLR fEnd,
                                                                     HLR dEnd)
{

    HL_SRE(!applyMonotonicitConstraint_, "cannot handle applyMonotonicitConstraint_=true "
           << "during the bootstrapping of the interpolator.");


    f(xIdx)=fEnd;

    d_[xIdx] = dEnd;

    HL_SRE(xIdx<nPoints_, "xIdx=" << xIdx << ", nPoints_=" << nPoints_);

    if(nonCubic())
    {
        /**
         * In case nPoints_=2 the class gets linear, in case nPoints_=1 the class gets constant
         *  */
        return;
    }


    if(xIdx==0)
    {
        // do nothing more

    }else if(xIdx<nPoints_){

        HLS xIdxPrevious = xIdx-1;

        HLR & a = a_[xIdxPrevious];
        HLR & b = b_[xIdxPrevious];
        HLR & c = c_[xIdxPrevious];

        HLR dx = get_dx()[xIdxPrevious];

        HLR fStart =  f(xIdxPrevious);

        HLR S = (fEnd - fStart) / dx;

        HLR dStart = d_[xIdxPrevious];

        computeIntervalCubicCoefficientsImpl(
                    a,
                    b,
                    c,
                    dx,
                    S,
                    dStart,
                    dEnd
                    );


    }



} // end setPointAndPerformInterpolationComputations




//------------------------------------------------------------------------------------------------------

HLR HL_1_D_CubicInterp::nonCubicOperator() const
{
    HLR fValue;

    HLR f_0 = f(0);
    if(nPoints_==1)
    {
        fValue=f_0;
    }
    else if(nPoints_==2)
    {

        HLR f_1 = f(1);

        const HL_Direction::HL_LocalizationSide & locSideLeft =
                dir()->get_localization().localizationSides[HL_Direction::HL_Localization::Left];
        const HL_Direction::HL_LocalizationSide & locSideRight =
                dir()->get_localization().localizationSides[HL_Direction::HL_Localization::Right];


        fValue = f_0*locSideLeft.weight + f_1*locSideRight.weight;

    }
    else
    {
        HL_FAIL("expected nPoints_<3, nPoints_=" << nPoints_);
    }

    return fValue;


} // end nonCubicOperator

//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicInterp::computeIncrements()
{

    const VEC & dx = get_dx();

    HL_SR(dx.size()==nPoints_minus_1_);

    S_.resize(nPoints_minus_1_);

    HLS i = 0;
    HLR f_i = f(0);

    VEC::iterator S_it = S_.begin();

    BOOST_FOREACH(HLR dx_i, dx)
    {

        HLR f_i_plus_one = f(i + 1);

        HL_SRE(dx_i>0., "dx_i=" << dx_i << ", i=" << i);

        (*S_it) = (f_i_plus_one - f_i) / dx_i;

        f_i = f_i_plus_one;

        ++i;

        ++S_it;
    } // end for dx_i


} // end computeIncrements

//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicInterp::applyMonotonicitConstraint()
{

    if(!applyMonotonicitConstraint_)
        return;

    // Hyman monotonicity constrained filter

    const VEC & dx = get_dx();



    for (HLS i=0; i<nPoints_; ++i)
    {
        HLR d_i_corrected=HL_NAN;
        bool d_i_corrected_set=false;
        HLR & d_i = d_[i];

        HLI d_i_sign = d_i>0 ? 1 : -1;

        if (i==0)
        {

            if (d_i*S_[0]>0.0)
            {

                d_i_corrected = d_i_sign *std::min<HLR>(std::fabs(d_i), std::fabs(3.0*S_[0]));
                d_i_corrected_set=true;
            }


        }
        else if (i==nPoints_minus_1_)
        {

            if (d_i*S_[nPoints_minus_2_]>0.0)
            {
                d_i_corrected = d_i_sign * std::min<HLR>(std::fabs(d_i), std::fabs(3.0*S_[nPoints_minus_2_]));
                d_i_corrected_set=true;

            }

        }
        else
        {


            HLR dx_i = dx[i];
            HLR dx_im1 = dx[i-1];

            HLR S_i = S_[i];
            HLR S_im1 = S_[i-1];

            HLR pm=(S_im1*dx_i+S_i*dx_im1)/(dx_im1+dx_i);

            HLR pm_fabs = std::fabs(pm);

            HLR M = 3.0 * std::min(std::min(std::fabs(S_im1), std::fabs(S_i)), pm_fabs);

            if (i>1)
            {
                HLR dx_im2 = dx[i-2];
                HLR S_im2 = S_[i-2];

                if ((S_im1-S_im2)*(S_i-S_im1)>0.0)
                {

                    HLR pd=(S_im1*(2.0*dx_im1+dx_im2)
                            -S_im2*dx_im1)/
                            (dx_im2+dx_im1);

                    if (pm*pd>0.0 && pm*(S_im1-S_im2)>0.0)
                    {
                        M = std::max<HLR>(M, 1.5*std::min(pm_fabs,std::fabs(pd)));
                    }
                }
            } // end if (i>1)

            if (i<nPoints_minus_2_)
            {

                HLR dx_ip1 = dx[i+1];
                HLR S_ip1 = S_[i+1];


                if ((S_i-S_im1)*(S_ip1-S_i)>0.0)
                {

                    HLR pu=(S_i*(2.0*dx_i+dx_ip1)-S_ip1*dx_i)/
                            (dx_i+dx_ip1);

                    if (pm*pu>0.0 && -pm*(S_i-S_im1)>0.0)
                    {
                        M = std::max<HLR>(M, 1.5*std::min(pm_fabs,std::fabs(pu)));
                    }
                }
            } // end if (i<nPoints_minus_2_)


            if (d_i*pm>0.0)
            {
                d_i_corrected = d_i_sign *std::min(std::fabs(d_i), M);
                d_i_corrected_set=true;

            } // end if (d_i*pm>0.0)


        } // end if..else if...else...

        if (d_i_corrected_set && d_i_corrected!=d_i)
        {
            // Correction applied
            d_i = d_i_corrected;
        }
    } // end for i



} // end applyMonotonicitConstraint

//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicInterp::computeCubicCoefficientsLoop()
{



    const VEC & dx = get_dx();

    VEC::const_iterator d_cIt = d_.begin();

    HLR d_i = *d_cIt;

    VEC::const_iterator S_cIt = S_.begin();


    VEC::iterator a_it = a_.begin();
    VEC::iterator b_it = b_.begin();
    VEC::iterator c_it = c_.begin();


    // cubic coefficients
    BOOST_FOREACH(HLR dx_i, dx)
    {
        /*
         * Notice that in the value method (value_n_1) the following coefficients will be
         * multiplied by a weight instead of a dx, hence we have to normalize them accordingly.
         * */
        ++d_cIt;
        HLR d_ip1 =  *d_cIt;


        HLR S_i = *S_cIt;

        //        (*a_it) = d_i*dx_i;
        //        (*b_it) = (3.0*S_i - d_ip1 - 2.0*d_i)*dx_i;
        //        (*c_it) = (d_ip1 + d_i - 2.0*S_i)*dx_i;

        computeIntervalCubicCoefficientsImpl(
                    (*a_it) ,
                    (*b_it),
                    (*c_it),
                    dx_i,
                    S_i,
                    d_i /*dStart*/,
                    d_ip1 /*dEnd*/
                    );


        d_i = d_ip1;

        ++S_cIt;
        ++a_it;
        ++b_it;
        ++c_it;

    } // end for i

} // end computeCubicCoefficientsLoop


//------------------------------------------------------------------------------------------------------

/**
 * Related to interval [xStart, xEnd]
 * dStart is the derivative at xStart
 * dEnd is the derivative at xEnd
 * dx=xEnd-xStart
 * S= incremental ratio in [xStart, xEnd]
*/
void HL_1_D_CubicInterp::computeIntervalCubicCoefficientsImpl(
        HLR & a,
        HLR & b,
        HLR & c,
        HLR dx,
        HLR S,
        HLR dStart,
        HLR dEnd
        )
{

    a = dStart*dx;
    b = (3.0*S - dEnd - 2.0*dStart)*dx;
    c = (dEnd + dStart - 2.0*S)*dx;


} // end computeIntervalCubicCoefficientsImpl


//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicInterp::descriptionImpl(std::ostream & os) const
{
    os << "HL_1_D_CubicInterp:\n";
    HL_Interpolator::descriptionImpl(os);

} // end descriptionImpl

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_1_D_CubicInterp: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_1_D_CubicSplineInterpControls
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_1_D_CubicSplineInterpControls::HL_1_D_CubicSplineInterpControls()
{

    classDefaultInit();



} // end HL_1_D_CubicSplineInterpControls

//------------------------------------------------------------------------------------------------------

HL_1_D_CubicSplineInterpControls::~HL_1_D_CubicSplineInterpControls()
{} // end ~HL_1_D_CubicSplineInterpControls


//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicSplineInterpControls::classDefaultInit()
{
    leftBoundaryCondition_=HL_CubicSplineBoundaryCondition_InvalidMin;
    rightBoundaryCondition_=HL_CubicSplineBoundaryCondition_InvalidMin;
    leftValue_=0;
    rightValue_=0;

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicSplineInterpControls::descriptionImpl(std::ostream & os) const
{
    HL_InterpControls::descriptionImpl(os);

    HL_DESCRIBE_ENUM(os, leftBoundaryCondition_);
    HL_DESCRIBE_ENUM(os, rightBoundaryCondition_);
    hl_fillDescriptionStream(leftValue_);
    hl_fillDescriptionStream(rightValue_);



} // end descriptionImpl








//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_1_D_CubicSplineInterp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_1_D_CubicSplineInterp::HL_1_D_CubicSplineInterp()
{

    classDefaultInit();

} // end HL_1_D_CubicSplineInterp

//------------------------------------------------------------------------------------------------------

HL_1_D_CubicSplineInterp::~HL_1_D_CubicSplineInterp()
{} // end ~HL_1_D_CubicSplineInterp

//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicSplineInterp::classDefaultInit()
{} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicSplineInterp::computeFirstDerivativeAtNodes()
{


    HL_DYN_SHARED_PTR_CAST_OPERATION(HL_1_D_CubicSplineInterpControls /*OutPtrType*/,
                                     cubicSplineInterpControlsPtr_ /*outPtr*/,
                                     interpControlsPtr_ /*inPtr*/);


    L_.setDimension(nPoints_);

    rhs_.resize(nPoints_);

    setTridiagOpFirstRow();

    setTridiagOpMidRows();

    setTridiagOpLastRow();


    L_. solve(rhs_ /* rhs*/, d_ /*result*/);

} // end computeFirstDerivativeAtNodes


//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicSplineInterp::setTridiagOpFirstRow() const
{

    HLR & rhs_0 = rhs_[0];
    const VEC & dx = get_dx();

    switch(cubicSplineInterpControlsPtr_->get_leftBoundaryCondition())
    {
    case HL_CubicSplineBoundaryCondition_FirstDerivative:
        L_.setFirstRow(1. /*L_diag */, 0./*L_upper*/);
        rhs_0=cubicSplineInterpControlsPtr_->get_leftValue();
        break;
    case HL_CubicSplineBoundaryCondition_SecondDerivative:
        L_.setFirstRow(2.0 /*L_diag */, 1.0/*L_upper*/);
        rhs_0 = 3.0*S_[0] - cubicSplineInterpControlsPtr_->get_leftValue()*dx[0]*0.5;
        break;
    default:
        HL_FAIL("invalid cubicSplineInterpControlsPtr_->get_leftBoundaryCondition()="
                << cubicSplineInterpControlsPtr_->get_leftBoundaryCondition());
    } // end switch

} // end setTridiagOpFirstRow

//------------------------------------------------------------------------------------------------------


void HL_1_D_CubicSplineInterp::setTridiagOpMidRows() const
{
    const VEC & dx = get_dx();

    VEC::const_iterator dx_cIt = dx.begin();

    HLR dx_rm1 = *dx_cIt;

    VEC::const_iterator S_cIt = S_.begin();

    HLR S_rm1 = *S_cIt;


    for (HLS r = 1; r < nPoints_minus_1_; ++r)
    {
        ++dx_cIt;

        HLR dx_r = *dx_cIt;

        ++S_cIt;

        HLR S_r = *S_cIt;


        L_.setMidRow(r, dx_r/*L_lower*/, 2.0 * (dx_r + dx_rm1)/*L_diag*/, dx_rm1/*L_upper*/);

        rhs_[r] = 3.0 * (dx_r * S_rm1 + dx_rm1 * S_r);

        dx_rm1 =dx_r;

        S_rm1 = S_r;

    } // end for r

} // end setTridiagOpMidRows

//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicSplineInterp::setTridiagOpLastRow() const
{

    HLR & rhs_last = rhs_[nPoints_minus_1_];
    const VEC & dx = get_dx();

    switch(cubicSplineInterpControlsPtr_->get_rightBoundaryCondition())
    {
    case HL_CubicSplineBoundaryCondition_FirstDerivative:
        L_.setLastRow(0./*L_lower*/, 1./*L_diag*/);
        rhs_last=cubicSplineInterpControlsPtr_->get_rightValue();
        break;
    case HL_CubicSplineBoundaryCondition_SecondDerivative:
        L_.setLastRow(1.0/*L_lower*/, 2.0/*L_diag*/);
        rhs_last = 3.0*S_[nPoints_minus_2_] + cubicSplineInterpControlsPtr_->get_rightValue()*dx[nPoints_minus_2_]*0.5;
        break;
    default:
        HL_FAIL("invalid cubicSplineInterpControlsPtr_->get_rightBoundaryCondition()="
                << cubicSplineInterpControlsPtr_->get_rightBoundaryCondition());
    } // end switch

} // end setTridiagOpLastRow


//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicSplineInterp::descriptionImpl(std::ostream & os) const
{

    os << "HL_1_D_CubicSplineInterp:\n";
    HL_1_D_CubicInterp::descriptionImpl(os);

} // end descriptionImpl

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_1_D_CubicSplineInterp: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------







//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_1_D_CubicInterpLocalParabolicControls
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_1_D_CubicInterpLocalParabolicControls::HL_1_D_CubicInterpLocalParabolicControls()
{

    classDefaultInit();



} // end HL_1_D_CubicInterpLocalParabolicControls

//------------------------------------------------------------------------------------------------------

HL_1_D_CubicInterpLocalParabolicControls::~HL_1_D_CubicInterpLocalParabolicControls()
{} // end ~HL_1_D_CubicInterpLocalParabolicControls


//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicInterpLocalParabolicControls::classDefaultInit()
{} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicInterpLocalParabolicControls::descriptionImpl(std::ostream & os) const
{
    HL_InterpControls::descriptionImpl(os);


} // end descriptionImpl






//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_1_D_CubicInterpLocalParabolic
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_1_D_CubicInterpLocalParabolic::HL_1_D_CubicInterpLocalParabolic()
{

    classDefaultInit();

} // end HL_1_D_CubicInterpLocalParabolic

//------------------------------------------------------------------------------------------------------

HL_1_D_CubicInterpLocalParabolic::~HL_1_D_CubicInterpLocalParabolic()
{} // end ~HL_1_D_CubicInterpLocalParabolic

//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicInterpLocalParabolic::classDefaultInit()
{} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicInterpLocalParabolic::computeFirstDerivativeAtNodes()
{

    const VEC & dx = get_dx();


    VEC::const_iterator dx_cIt = dx.begin();

    HLR dx_rm1 = *dx_cIt;

    VEC::const_iterator S_cIt = S_.begin();

    HLR S_rm1 = *S_cIt;

    // intermediate points
    for (HLS r=1; r<(nPoints_minus_1_); ++r)
    {
        ++dx_cIt;

        HLR dx_r = *dx_cIt;

        ++S_cIt;

        HLR S_r = *S_cIt;


        d_[r] = (dx_rm1*S_r+dx_r*S_rm1)/(dx_r+dx_rm1);

        dx_rm1 =dx_r;

        S_rm1 = S_r;

    } // end for r


    HLR dx_0 = dx[0];
    HLR dx_1 = dx[1];

    // end points
    d_[0]    = ((2.0*dx_0+dx_1)*S_[0] - dx_0*S_[1]) / (dx_0+dx_1);

    HLR dx_nm2 = dx[nPoints_minus_2_];
    HLR dx_nm3 = dx[nPoints_minus_3_];

    d_[nPoints_minus_1_] =
            ((2.0*dx_nm2+dx_nm3)*S_[nPoints_minus_2_] - dx_nm2*S_[nPoints_minus_3_])
            /
            (dx_nm2+dx_nm3);


} // end computeFirstDerivativeAtNodes

//------------------------------------------------------------------------------------------------------

void HL_1_D_CubicInterpLocalParabolic::descriptionImpl(std::ostream & os) const
{
    os << "HL_1_D_CubicInterpLocalParabolic:\n";
    HL_1_D_CubicInterp::descriptionImpl(os);

} // end descriptionImpl

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_1_D_CubicInterpLocalParabolic: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TEST_F
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HLR HL_TEST_F::value(HLR x, HLR &valuePrime, HLR &valueSecond) const
{
    HLR f =a+x*(b+x*(c+x*d));

    valuePrime = b+x*(2*c+3*x*d);

    valueSecond = 2*c+6*x*d;

    return f;

} // end value

//------------------------------------------------------------------------------------------------------


HL_DirectionPtr HL_TEST_build_DirectionPtr(HLS n, HLR x_0, HLR dx)
{
    VEC v(n);

    HLS i=0;
    BOOST_FOREACH(HLR & x, v)
    {
        x = x_0+i*dx;

        ++i;
    } // end for x


    HL_DirectionPtr dir;
    dir.reset(new HL_Direction);
    dir->set_x(v);

    return dir;

} // end HL_TEST_build_DirectionPtr

//------------------------------------------------------------------------------------------------------


HL_InterpControlsPtr HL_TEST_1D_InterpControlsPtr(
        const HL_DirectionPtr & dir,
        HLR &a,
        HLR &b,
        const HL_TEST_F & F,
        /**
                                     * proportionalityFactor_F to be used to rescale F as one wants...
                                     * */
        HLR proportionalityFactor_F,
        HL_InterpolatorType interpolatorType,
        HL_CubicSplineBoundaryCondition leftBoundaryCondition,
        HL_CubicSplineBoundaryCondition rightBoundaryCondition,
        /**
                                     * Another output of the method
                                     * */
        BSP<HL_1_D_CubicInterp> &interpolatorPtr
        )
{

    interpolatorPtr.reset();

    a = dir->leftBorder();
    b = dir->rightBorder();


    HL_InterpControlsPtr interpControlsPtr;

    switch(interpolatorType)
    {
    case HL_InterpolatorType_1_D_CubicSpline:
    {
        interpolatorPtr.reset(new HL_1_D_CubicSplineInterp);


        HL_1_D_CubicSplineInterpControlsPtr hl_1_D_CubicSplineInterpControlsPtr(new HL_1_D_CubicSplineInterpControls);
        interpControlsPtr=hl_1_D_CubicSplineInterpControlsPtr;

        HLR value_a,valuePrime_a,valueSecond_a;
        value_a = F.value(a,valuePrime_a,valueSecond_a);

        value_a*=proportionalityFactor_F;
        valuePrime_a*=proportionalityFactor_F;
        valueSecond_a*=proportionalityFactor_F;


        hl_1_D_CubicSplineInterpControlsPtr->set_leftBoundaryCondition(leftBoundaryCondition);

        if(leftBoundaryCondition==HL_CubicSplineBoundaryCondition_FirstDerivative)
        {
            hl_1_D_CubicSplineInterpControlsPtr->set_leftValue(valuePrime_a);
        }
        else if(leftBoundaryCondition==HL_CubicSplineBoundaryCondition_SecondDerivative)
        {
            hl_1_D_CubicSplineInterpControlsPtr->set_leftValue(valueSecond_a);
        }
        else
        {
            HL_FAIL("invalid leftBoundaryCondition=" << leftBoundaryCondition);
        }


        HLR value_b,valuePrime_b,valueSecond_b;
        value_b = F.value(b,valuePrime_b,valueSecond_b);


        value_b*=proportionalityFactor_F;
        valuePrime_b*=proportionalityFactor_F;
        valueSecond_b*=proportionalityFactor_F;


        hl_1_D_CubicSplineInterpControlsPtr->set_rightBoundaryCondition(rightBoundaryCondition);

        if(rightBoundaryCondition==HL_CubicSplineBoundaryCondition_FirstDerivative)
        {
            hl_1_D_CubicSplineInterpControlsPtr->set_rightValue(valuePrime_b);
        }
        else if(rightBoundaryCondition==HL_CubicSplineBoundaryCondition_SecondDerivative)
        {
            hl_1_D_CubicSplineInterpControlsPtr->set_rightValue(valueSecond_b);
        }
        else
        {
            HL_FAIL("invalid rightBoundaryCondition=" << rightBoundaryCondition);
        }


        break;
    }
    case HL_InterpolatorType_1_D_CubicLocalParabolic:
    {

        interpolatorPtr.reset(new HL_1_D_CubicInterpLocalParabolic);

        HL_1_D_CubicInterpLocalParabolicControlsPtr hl_1_D_CubicInterpLocalParabolicControlsPtr(new HL_1_D_CubicInterpLocalParabolicControls);
        interpControlsPtr=hl_1_D_CubicInterpLocalParabolicControlsPtr;

        break;
    }
    default:
        HL_FAIL("invalid interpolatorType=" << interpolatorType);
    }
    ; // end switch(interpolatorType)

    std::vector<HL_DirectionPtr> directions(1);

    directions[0] = dir;

    interpControlsPtr->set_directions(directions);

    interpolatorPtr->set_interpControlsPtr(interpControlsPtr);

    interpolatorPtr->instantiateMultiArray();

    return interpControlsPtr;


} // end HL_TEST_1D_InterpControlsPtr


//------------------------------------------------------------------------------------------------------

void HL_TEST_HL_1_D_CubicInterpCheck(const HL_TEST_F & F,
                                     HLR a,
                                     HLR b,
                                     BSP<HL_1_D_CubicInterp> interpolatorPtr)
{

    HLSER::HL_CoreSerializableObj csObj;

    csObj.oa() << interpolatorPtr;
    csObj.getReadyForDeserialization();

    BSP<HL_1_D_CubicInterp> interpolatorPtr_R;
    csObj.ia() >> interpolatorPtr_R;


    HLS nCheckPoints =1000;


    HLR dxCheck = (b-a)/nCheckPoints;
    VEC xVect(1);
    for(HLS j=0;j<=nCheckPoints;++j)
    {
        HLR &x = xVect[0];

        x = a+dxCheck*j;

        x=std::min(x, b); // rounding

        HLR valuePrime,valueSecond;

        HLR value= F.value(x,valuePrime,valueSecond);

        HLR valueInterp = interpolatorPtr->value_n_1(xVect.begin(), xVect.end());

        HL_REQ_EQUAL_FLOATS_N(value, valueInterp, 1000);

        HLR valueInterp_R = interpolatorPtr_R->value_n_1(xVect.begin(), xVect.end());

        HL_REQ_EQUAL_FLOATS_N (valueInterp_R, valueInterp, 1);


    } // end for j


} // end HL_TEST_HL_1_D_CubicInterpCheck


//------------------------------------------------------------------------------------------------------

void HL_TEST_HL_1_D_CubicInterp(const HL_TEST_F & F,
                                HL_InterpolatorType interpolatorType,
                                HL_CubicSplineBoundaryCondition leftBoundaryCondition,
                                HL_CubicSplineBoundaryCondition rightBoundaryCondition,
                                HLS n=200)
{


    HL_DirectionPtr dir = HL_TEST_build_DirectionPtr(n, -10. /*x_0*/, 2.6/* dx*/);

    BSP<HL_1_D_CubicInterp> interpolatorPtr;


    HLR a, b;

    HL_InterpControlsPtr interpControlsPtr  = HL_TEST_1D_InterpControlsPtr(
                dir,
                a,
                b,
                F,
                /**
                                                                 * proportionalityFactor_F to be used to rescale F as one wants...
                                                                 * */
                1 /*HLR proportionalityFactor_F*/,
                interpolatorType,
                leftBoundaryCondition,
                rightBoundaryCondition,
                /**
                                                                 * Another output of the method
                                                                 * */
                interpolatorPtr
                );

    interpolatorPtr->set_applyMonotonicitConstraint(false);

    HLMIDX multiIndex(1, 0);


    HLS i=0;

    BOOST_FOREACH(HLR x, dir->get_x())
    {

        HLR valuePrime,valueSecond;

        HLR value = F.value(x,valuePrime,valueSecond);

        multiIndex[0]=i;

        interpolatorPtr->setPoint(multiIndex,value);


        ++i;
    } // end for x

    interpolatorPtr->finalize();


    HL_TEST_HL_1_D_CubicInterpCheck(F,
                                    a,
                                    b,
                                    interpolatorPtr);




} // end HL_TEST_HL_1_D_CubicInterp




//------------------------------------------------------------------------------------------------------

void HL_TEST_HL_1_D_CubicInterpBootstrap()
{

    HL_DirectionPtr dir = HL_TEST_build_DirectionPtr(50 /*n*/, -20. /*x_0*/, 4.6/* dx*/);


    HL_TEST_F F;

    F.a=-30;
    F.b=+32;
    F.c=-10.33;
    F.d=0.2; // impose the parabola

    HL_InterpolatorType interpolatorType = HL_InterpolatorType_1_D_CubicLocalParabolic;
    HL_CubicSplineBoundaryCondition leftBoundaryCondition =HL_CubicSplineBoundaryCondition_InvalidMin;
    HL_CubicSplineBoundaryCondition rightBoundaryCondition=HL_CubicSplineBoundaryCondition_InvalidMin;


    BSP<HL_1_D_CubicInterp> interpolatorPtr;


    HLR a, b;

    HL_InterpControlsPtr interpControlsPtr  = HL_TEST_1D_InterpControlsPtr(
                dir,
                a,
                b,
                F,
                /**
                                                                 * proportionalityFactor_F to be used to rescale F as one wants...
                                                                 * */
                1 /*HLR proportionalityFactor_F*/,
                interpolatorType,
                leftBoundaryCondition,
                rightBoundaryCondition,
                /**
                                                                 * Another output of the method
                                                                 * */
                interpolatorPtr
                );

    interpolatorPtr->set_applyMonotonicitConstraint(false);

    HLMIDX multiIndex(1, 0);


    HLS xIdx=0;

    BOOST_FOREACH(HLR x, dir->get_x())
    {

        HLR valuePrime,valueSecond;

        HLR value = F.value(x, valuePrime, valueSecond);



        interpolatorPtr->setPointAndPerformInterpolationComputations( xIdx,
                                                                      value /*fEnd*/,
                                                                      valuePrime /*dEnd*/);


        ++xIdx;
    } // end for x

    // no finalize needed
    // interpolatorPtr->finalize();

    HL_TEST_HL_1_D_CubicInterpCheck(F,
                                    a,
                                    b,
                                    interpolatorPtr);





} // end HL_TEST_HL_1_D_CubicInterpBootstrap


//------------------------------------------------------------------------------------------------------

void HL_TEST_HL_1_D_CubicInterpAll()
{

    HL_GET_LOGGER(false/*addTimer*/);



    /*
     * In the first set of tests, we fit a cubic with a cubic. So everything should work with no error (other than
     * the one due to machine limited precision).
     * */
    //************************************/
    {
        HL_TEST_F F;

        F.a=-3;
        F.b=+3;
        F.c=-1.33;
        F.d=.4;

        HL_InterpolatorType interpolatorType = HL_InterpolatorType_1_D_CubicSpline;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition =HL_CubicSplineBoundaryCondition_FirstDerivative;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition=HL_CubicSplineBoundaryCondition_FirstDerivative;


        HL_TEST_HL_1_D_CubicInterp(F, interpolatorType, leftBoundaryCondition, rightBoundaryCondition);
    }
    //************************************/

    {
        HL_TEST_F F;

        F.a=-3;
        F.b=+3;
        F.c=-1.33;
        F.d=.4;

        HL_InterpolatorType interpolatorType = HL_InterpolatorType_1_D_CubicSpline;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition =HL_CubicSplineBoundaryCondition_SecondDerivative;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition=HL_CubicSplineBoundaryCondition_FirstDerivative;


        HL_TEST_HL_1_D_CubicInterp(F, interpolatorType, leftBoundaryCondition, rightBoundaryCondition);
    }
    //************************************/
    {
        HL_TEST_F F;

        F.a=-3;
        F.b=+3;
        F.c=-1.33;
        F.d=.4;

        HL_InterpolatorType interpolatorType = HL_InterpolatorType_1_D_CubicSpline;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition =HL_CubicSplineBoundaryCondition_SecondDerivative;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition=HL_CubicSplineBoundaryCondition_SecondDerivative;


        HL_TEST_HL_1_D_CubicInterp(F, interpolatorType, leftBoundaryCondition, rightBoundaryCondition);
    }
    //************************************/
    {
        HL_TEST_F F;

        F.a=-30;
        F.b=+32;
        F.c=-10.33;
        F.d=4.3;

        HL_InterpolatorType interpolatorType = HL_InterpolatorType_1_D_CubicSpline;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition =HL_CubicSplineBoundaryCondition_SecondDerivative;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition=HL_CubicSplineBoundaryCondition_SecondDerivative;


        HL_TEST_HL_1_D_CubicInterp(F, interpolatorType, leftBoundaryCondition, rightBoundaryCondition);
    }
    /*
     * In the second set of tests, we fit a parabola with a parabola. So everything should work with no error (other than
     * the one due to machine limited precision).
     *
     *  */

    //************************************/
    {
        HL_TEST_F F;

        F.a=-30;
        F.b=+32;
        F.c=-10.33;
        F.d=0; // impose the parabola

        HL_InterpolatorType interpolatorType = HL_InterpolatorType_1_D_CubicLocalParabolic;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition =HL_CubicSplineBoundaryCondition_InvalidMin;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition=HL_CubicSplineBoundaryCondition_InvalidMin;


        HL_TEST_HL_1_D_CubicInterp(F, interpolatorType, leftBoundaryCondition, rightBoundaryCondition);
    }
    //************************************/
    {
        HL_TEST_F F;

        F.a=-30;
        F.b=+32;
        F.c=-10.33;
        F.d=0.01; // not imposing a parabola e get an error

        HL_InterpolatorType interpolatorType = HL_InterpolatorType_1_D_CubicLocalParabolic;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition =HL_CubicSplineBoundaryCondition_InvalidMin;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition=HL_CubicSplineBoundaryCondition_InvalidMin;


        try
        {
            HL_TEST_HL_1_D_CubicInterp(F, interpolatorType, leftBoundaryCondition, rightBoundaryCondition);
            HL_FAIL("expected to fail, shouldn't get here");
        }
        catch(...)
        {
            ;// should get here
        }
    }

    /*
     * Here we go with only 2 points, so we have to go linear if we want perfect match. No matter if we use
     * either HL_InterpolatorType_1_D_CubicSpline or HL_InterpolatorType_1_D_CubicLocalParabolic
     *  */
    //************************************/
    {
        HL_TEST_F F;

        F.a=-30;
        F.b=+32;
        F.c=0; // impose the linear
        F.d=0; // impose the linear

        HL_InterpolatorType interpolatorType = HL_InterpolatorType_1_D_CubicSpline;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition =HL_CubicSplineBoundaryCondition_FirstDerivative;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition=HL_CubicSplineBoundaryCondition_FirstDerivative;


        HL_TEST_HL_1_D_CubicInterp(F, interpolatorType, leftBoundaryCondition, rightBoundaryCondition, 2/*n*/);
    }
    //************************************/
    {
        HL_TEST_F F;

        F.a=-430;
        F.b=-32;
        F.c=0; // impose the linear
        F.d=0; // impose the linear

        HL_InterpolatorType interpolatorType = HL_InterpolatorType_1_D_CubicLocalParabolic;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition =HL_CubicSplineBoundaryCondition_InvalidMin;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition=HL_CubicSplineBoundaryCondition_InvalidMin;


        HL_TEST_HL_1_D_CubicInterp(F, interpolatorType, leftBoundaryCondition, rightBoundaryCondition, 2/*n*/);
    }
    //************************************/
    /*
     * Here we go with only 1 point, so we have to go constant if we want perfect match. No matter if we use
     * either HL_InterpolatorType_1_D_CubicSpline or HL_InterpolatorType_1_D_CubicLocalParabolic
     *  */
    {
        HL_TEST_F F;

        F.a=-30;
        F.b=0; // impose the flat
        F.c=0; // impose the flat
        F.d=0; // impose the flat

        HL_InterpolatorType interpolatorType = HL_InterpolatorType_1_D_CubicSpline;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition =HL_CubicSplineBoundaryCondition_FirstDerivative;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition=HL_CubicSplineBoundaryCondition_FirstDerivative;


        HL_TEST_HL_1_D_CubicInterp(F, interpolatorType, leftBoundaryCondition, rightBoundaryCondition, 1/*n*/);
    }
    //************************************/
    {
        HL_TEST_F F;

        F.a=-430;
        F.b=0; // impose the flat
        F.c=0; // impose the flat
        F.d=0; // impose the flat

        HL_InterpolatorType interpolatorType = HL_InterpolatorType_1_D_CubicLocalParabolic;
        HL_CubicSplineBoundaryCondition leftBoundaryCondition =HL_CubicSplineBoundaryCondition_InvalidMin;
        HL_CubicSplineBoundaryCondition rightBoundaryCondition=HL_CubicSplineBoundaryCondition_InvalidMin;


        HL_TEST_HL_1_D_CubicInterp(F, interpolatorType, leftBoundaryCondition, rightBoundaryCondition, 1/*n*/);
    }
    //************************************/


    HL_TEST_HL_1_D_CubicInterpBootstrap();

    //************************************/


    HL_SUCCESSFULL_TEST(HL_TEST_HL_1_D_CubicInterpAll);





} // end HL_TEST_HL_1_D_CubicInterpAll





} // end namespace HL_Interpolation
} // end namespace HL_Math
} //end namespace HorizonLib
