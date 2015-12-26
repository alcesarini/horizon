/**
 FILE NAME= hl_cubicSpline.h
 LIB= HorizonLib
 ADDED BY= A. Cesarini
 DATE= 20140111
 */
#ifndef _hl_cubicSpline_h_
#define _hl_cubicSpline_h_

#include <hl/math/interpolation/hl_interpolator.h>
#include <hl/math/linearAlgebra/hl_tridiagonalOperator.h>


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

/**
 \author A. Cesarini
 \date 20131227
 \brief Base class for cubic interpolation methods.
 \warning Notice that this class and its derived classes should be streamed only after
 completely computed and refreshed.
 */
class HL_1_D_CubicInterp : public virtual HL_Interpolator
{

    /**
     -----------------------------------------------------
     Serialization
     */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS
    ;

    template<class Archive>
    void serialize(Archive &ar, const HLS version)
    {

        HL_SERIALIZE_BASE_CLASS(HL_Interpolator);

        HL_SER(applyMonotonicitConstraint_);
        HL_SER(S_);
        HL_SER(d_);
        HL_SER(nPoints_);
        HL_SER(nPoints_minus_1_);
        HL_SER(nPoints_minus_2_);
        HL_SER(nPoints_minus_3_);
        HL_SER(a_);
        HL_SER(b_);
        HL_SER(c_);


    }
    //@} Serialization -----------------------------------

public:

    /**
     Constructors & destructors
     */
    //@{
    HL_1_D_CubicInterp();

    virtual ~HL_1_D_CubicInterp();
    //@}

    /**
     Public class interface
     */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(bool/*ClassVariableType*/, applyMonotonicitConstraint/*classVariableName_no_underscore*/);


    HLR value_n_1(const VEC::const_iterator & b, const VEC::const_iterator & e) const;


    void set_interpControlsPtr(const HL_InterpControlsPtr &interpControlsPtr);


    void finalize();


    /**
     * 0<=xIdx<nPoints_
     * fEnd is supposed to be set into f(xEnd), where xEnd=get_x(xIdx)
     * dEnd is supposed to be the derivative of the interpolating function at xEnd.
     * Notice that xEnd is the end of the interval [get_x(xIdx-1), get_x(xIdx)] (at least if xIdx>0,...)
    */
    void setPointAndPerformInterpolationComputations(HLS xIdx,
                                                     HLR fEnd,
                                                     HLR dEnd);

    //@}

protected:
    /**
     Additional implementations
     */
    //@{
    /**
     Default initialization of the class vars.
     */
    void classDefaultInit();



    void preInit();


    HLR nonCubicOperator() const;


    const HL_DirectionPtr & dir() const
    {
        return get_direction(0);
    }

    const VEC & get_x() const
    {
        return dir()->get_x();
    }

    const VEC & get_dx() const
    {
        return dir()->get_delta_x();
    }

    HLR f(HLS idx) const
    {
        serviceMultiIndex_[0]=idx;
        return realMultiArrayPtr_->operator[](serviceMultiIndex_);
    }

    HLR & f(HLS idx)
    {
        serviceMultiIndex_[0]=idx;
        return realMultiArrayPtr_->operator[](serviceMultiIndex_);
    }

    bool nonCubic() const
    {

        return nPoints_<3;
    }

    void computeIncrements();

    virtual void computeFirstDerivativeAtNodes()=0;

    void applyMonotonicitConstraint();

    void computeCubicCoefficientsLoop();


    void computeIntervalCubicCoefficientsImpl(
            HLR & a,
            HLR & b,
            HLR & c,
            HLR dx,
            HLR S,
            HLR dStart,
            HLR dEnd
            );

    //@}

    /**
     Implementations of base class methods
     */
    //@{


    void descriptionImpl(std::ostream & os) const;

    //@}

protected:

    /**
     Class variables
     */
    //@{

    bool applyMonotonicitConstraint_;
    //@}
    /**
     Service class variables
     */
    //@{

    mutable HLMIDX serviceMultiIndex_;


    mutable VEC S_;
    /**
     First derivative
     */
    mutable VEC d_;


    mutable HLS nPoints_, nPoints_minus_1_, nPoints_minus_2_, nPoints_minus_3_;


    mutable VEC a_, b_, c_;


    //@}

}
; // end class HL_1_D_CubicInterp

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_1_D_CubicInterp: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_CubicSplineBoundaryCondition
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \brief The HL library period units.
 */
enum HL_CubicSplineBoundaryCondition
{
    HL_CubicSplineBoundaryCondition_InvalidMin = 0,
    /**
     * Match value of end-slope
     * */
    HL_CubicSplineBoundaryCondition_FirstDerivative,
    /**
     * Match value of second derivative at end
     * */
    HL_CubicSplineBoundaryCondition_SecondDerivative,
    HL_CubicSplineBoundaryCondition_InvalidMax
}
;
// end enum HL_CubicSplineBoundaryCondition

HL_ENUM_DESCRIPTION(HL_CubicSplineBoundaryCondition,
                    "HL_CubicSplineBoundaryCondition_InvalidMin", "HL_CubicSplineBoundaryCondition_FirstDerivative", "HL_CubicSplineBoundaryCondition_SecondDerivative", "HL_CubicSplineBoundaryCondition_InvalidMax");





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_1_D_CubicSplineInterpControls
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20131227
 \brief Controls for HL_1_D_CubicSplineInterp.
 */
class HL_1_D_CubicSplineInterpControls : public virtual HL_InterpControls
{

    /**
     -----------------------------------------------------
     Serialization
     */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS
    ;

    template<class Archive>
    void
    serialize(Archive &ar, const HLS version)
    {

        HL_SERIALIZE_BASE_CLASS(HL_InterpControls);

        HL_SER(leftBoundaryCondition_);
        HL_SER(rightBoundaryCondition_);
        HL_SER(leftValue_);
        HL_SER(rightValue_);

    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_1_D_CubicSplineInterpControls();

    virtual ~HL_1_D_CubicSplineInterpControls();
    //@}

    /**
     Public class interface
     */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(HL_CubicSplineBoundaryCondition/*ClassVariableType*/, leftBoundaryCondition/*classVariableName_no_underscore*/);
    HL_CLASS_VAR_ACCESS_METHODS(HL_CubicSplineBoundaryCondition/*ClassVariableType*/, rightBoundaryCondition/*classVariableName_no_underscore*/);
    HL_CLASS_VAR_ACCESS_METHODS(HLR/*ClassVariableType*/, leftValue/*classVariableName_no_underscore*/);
    HL_CLASS_VAR_ACCESS_METHODS(HLR/*ClassVariableType*/, rightValue/*classVariableName_no_underscore*/);

    virtual HL_InterpolatorType get_InterpolatorType() const
    {
        return HL_InterpolatorType_1_D_CubicSpline;

    }

    HLS nLocalityPoints(HLS dimIdx) const
    {
        /*
         * Cubic spline is not local at all
         * */
        return HL_MAX_INTEGER;
    }



    //@}

protected:

    /**
     Additional implementations
     */
    //@{
    /**
     Default initialization of the class vars.
     */
    void classDefaultInit();

    //@}

    /**
     Implementations of base class methods
     */
    //@{
    void descriptionImpl(std::ostream & os) const;



    //@}

protected:

    /**
     Class variables
     */
    //@{

    HL_CubicSplineBoundaryCondition leftBoundaryCondition_, rightBoundaryCondition_;
    HLR leftValue_, rightValue_;
    //@}

}
; // end class HL_1_D_CubicSplineInterpControls




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_1_D_CubicSplineInterpControls: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_1_D_CubicSplineInterpControlsPtr BSP<HLINTP::HL_1_D_CubicSplineInterpControls>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_1_D_CubicSplineInterp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20131227
 \brief Specilization of HL_1_D_CubicInterp for the case of the cubic spline method.
 */
class HL_1_D_CubicSplineInterp : public virtual HL_1_D_CubicInterp
{

    /**
     -----------------------------------------------------
     Serialization
     */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS
    ;

    template<class Archive>
    void serialize(Archive &ar, const HLS version)
    {

        HL_SERIALIZE_BASE_CLASS(HL_1_D_CubicInterp);

    }
    //@} Serialization -----------------------------------

public:


    /**
     Constructors & destructors
     */
    //@{
    HL_1_D_CubicSplineInterp();

    virtual ~HL_1_D_CubicSplineInterp();
    //@}

    /**
     Public class interface
     */
    //@{

    //@}

protected:
    /**
     Additional implementations
     */
    //@{
    /**
     Default initialization of the class vars.
     */
    void classDefaultInit();


    //@}

    /**
     Implementations of base class methods
     */
    //@{

    void computeFirstDerivativeAtNodes();


    void setTridiagOpFirstRow() const;

    void setTridiagOpMidRows() const;

    void setTridiagOpLastRow() const;



    void descriptionImpl(std::ostream & os) const;

    //@}

protected:

    /**
     Class variables
     */
    //@{


    mutable HL_1_D_CubicSplineInterpControlsPtr cubicSplineInterpControlsPtr_;
    //@}

    /**
     Service class variables
     */
    //@{

    mutable HLLA::HL_TridiagonalOperator L_;
    mutable VEC rhs_;
    //@}





}
; // end class HL_1_D_CubicSplineInterp

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

/**
 \author A. Cesarini
 \date 20140203
 \brief Controls for HL_1_D_CubicInterpLocalParabolic.
 */
class HL_1_D_CubicInterpLocalParabolicControls : public virtual HL_InterpControls
{

    /**
     -----------------------------------------------------
     Serialization
     */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS
    ;

    template<class Archive>
    void
    serialize(Archive &ar, const HLS version)
    {
        HL_SERIALIZE_BASE_CLASS(HL_InterpControls);


    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_1_D_CubicInterpLocalParabolicControls();

    virtual ~HL_1_D_CubicInterpLocalParabolicControls();
    //@}

    /**
     Public class interface
     */
    //@{

    virtual HL_InterpolatorType get_InterpolatorType() const
    {
        return HL_InterpolatorType_1_D_CubicLocalParabolic;

    }

    HLS nLocalityPoints(HLS dimIdx) const
    {
        /*
         * Parabolic method is almost local
         * */
        return 1;
    }
    //@}

protected:

    /**
     Additional implementations
     */
    //@{
    /**
     Default initialization of the class vars.
     */
    void classDefaultInit();

    //@}

    /**
     Implementations of base class methods
     */
    //@{
    void descriptionImpl(std::ostream & os) const;



    //@}

protected:

    /**
     Class variables
     */
    //@{

    //@}

}
; // end class HL_1_D_CubicInterpLocalParabolicControls


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_1_D_CubicInterpLocalParabolicControls: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



#define HL_1_D_CubicInterpLocalParabolicControlsPtr BSP<HLINTP::HL_1_D_CubicInterpLocalParabolicControls>





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_1_D_CubicInterpLocalParabolic
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20131227
 \brief Specilization of HL_1_D_CubicInterp for the case of the cubic spline method.
 */
class HL_1_D_CubicInterpLocalParabolic : public virtual HL_1_D_CubicInterp
{

    /**
     -----------------------------------------------------
     Serialization
     */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS
    ;

    template<class Archive>
    void serialize(Archive &ar, const HLS version)
    {

        HL_SERIALIZE_BASE_CLASS(HL_1_D_CubicInterp);

    }
    //@} Serialization -----------------------------------

public:

    /**
     Constructors & destructors
     */
    //@{
    HL_1_D_CubicInterpLocalParabolic();

    virtual ~HL_1_D_CubicInterpLocalParabolic();
    //@}

    /**
     Public class interface
     */
    //@{

    //@}

protected:
    /**
     Additional implementations
     */
    //@{
    /**
     Default initialization of the class vars.
     */
    void classDefaultInit();


    //@}

    /**
     Implementations of base class methods
     */
    //@{

    void computeFirstDerivativeAtNodes();


    void descriptionImpl(std::ostream & os) const;




    //@}

protected:

    /**
     Class variables
     */
    //@{
    //@}
    /**
     Service class variables
     */
    //@{
    //@}
}
; // end class HL_1_D_CubicInterpLocalParabolic

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_1_D_CubicInterpLocalParabolic: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


void HL_TEST_HL_1_D_CubicInterpAll();

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TEST_F
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

class HL_TEST_F
{
public:

    HLR value(HLR x, HLR &valuePrime, HLR &valueSecond) const;

public:

    HLR a, b, c, d;

}
; // end HL_TEST_F
//------------------------------------------------------------------------------------------------------

HL_DirectionPtr HL_TEST_build_DirectionPtr(HLS n, HLR x_0, HLR dx);

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
        );
//------------------------------------------------------------------------------------------------------


}// end namespace HL_Interpolation
} // end namespace HL_Math
} //end namespace HorizonLib

#endif // _hl_cubicSpline_h_
