/**
 FILE NAME= hl_bidimCubicSpline.h
 LIB= HorizonLib
 ADDED BY= A. Cesarini
 DATE= 20140203
 */
#ifndef _hl_bidimCubicSpline_h_
#define _hl_bidimCubicSpline_h_

#include <hl/math/interpolation/hl_interpolator.h>

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

/**
 \author A. Cesarini
 \date 20140204
 \brief Controls for HL_2_D_CrossInterp.
 */
class HL_2_D_CrossInterpControls : public virtual HL_InterpControls
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

        HL_SER(interpControlsPtr_y_);
        HL_SER(interpControlsPtrVect_x_);

    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_2_D_CrossInterpControls();

    virtual ~HL_2_D_CrossInterpControls();
    //@}

    /**
     Public class interface
     */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(std::vector<HL_InterpControlsPtr>, interpControlsPtrVect_x);
    HL_CLASS_VAR_ACCESS_METHODS(HL_InterpControlsPtr, interpControlsPtr_y);


    virtual HL_InterpolatorType get_InterpolatorType() const
    {
        return HL_InterpolatorType_2_D_CrossInterp;

    }

    HLS nLocalityPoints(HLS dimIdx) const;

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

    /**
     * Check comment to HL_2_D_CrossInterp.
     * These HL_InterpControlsPtr is related to direction[0], i.e. x-direction
     * and is to be used to build I_j for j=0,...,(n_y-1) that are the x-direction interpolators
     *  introduced in the comment to HL_2_D_CrossInterp.
     * */
    std::vector<HL_InterpControlsPtr> interpControlsPtrVect_x_;
    /**
     * Check comment to HL_2_D_CrossInterp.
     * This interpolator is related to direction[1], i.e. y-direction, and is the one
     * that is used to to be the L(y) interpolator (check point 4 of comment to HL_2_D_CrossInterp)
     *
     *
     * */
    HL_InterpControlsPtr interpControlsPtr_y_;
    //@}

}
; // end class HL_2_D_CrossInterpControls

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_2_D_CrossInterpControls: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



#define HL_2_D_CrossInterpControlsPtr BSP<HLINTP::HL_2_D_CrossInterpControls>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_2_D_CrossInterp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20140203
 \brief Class to implement interpolation in 2 dimensions by combining 2 one-dimensional interpolations
 of any type (this is the meaning of "cross" here).

 We explain in detail the procedure for the case of 2 cubic interpolations.
 Other cases (for ex. linear x-cubic y) will be handled similarly.

 Suppose to give a bi-dimensional regular grid of points
 (x_i, y_j)
 for
 i=0,...,(n_x-1)
 j=0,...,(n_y-1)
 together with the corresponding function values: f(i, j).

 We assume that the x-direction is directions_[0], while y-direction is directions_[1].

 The class builds a set of n_y cubic interpolators: I_0,...,I_{n_y-1}.

 Each I_j is capable to interpolate along the x-direction for the fixed value y_j of the y-variable..

 Once the user asks for some f(x,y), the following procedure is applied:

 1) Localize y using dir_y = directions_[1]. Let j be the corresponding leftIdx (check HL_Direction class localization tool)
 2) Determine the minimum set of y-points (y_k for k\in J) around y, necessary to be a local interpolator around y.
 3) Compute F_k=f(x, y_{J_k}),  for k\in J
 4) Build an instance (L) of a local cubic interpolation out of {y_{J_k}, F_k}
 5) Use L to determine f(x,y)=L(y)

 Notice that:
 - the J set introduced above usually contains 4 elements for local cubic y-interpolation; in case
 of linear y-interpolator, the J set could contain just 2 points J={j, j+1}.
 In this respect, check the meaning of method HL_InterpControls::nLocalityPoints().
 - for the y-interpolation, one is forced to choose a local scheme (such as. e.g. HL_1_D_CubicInterpLocalParabolic)
 instead of a global one (such as e.g. spline) otherwise it could happen that the f(x,y) one computes through this class could
 depend on the number of points one uses in the J set (to avoid such inconvenient one would then be forced to use the maximum
 number of points in the J-set, i.e. n_y, with obvious consequent performance issues).

 */
class HL_2_D_CrossInterp : public virtual HL_Interpolator
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

        HL_SER(n_x_);
        HL_SER(n_y_);
        HL_SER(xInterps_);

        if(!isToStream())
        {
            set_yLocalInterpolationData();
        }

    }
    //@} Serialization -----------------------------------

public:

    /**
     Constructors & destructors
     */
    //@{
    HL_2_D_CrossInterp();

    virtual ~HL_2_D_CrossInterp();
    //@}

    /**
     Public class interface
     */
    //@{



    HLR operator()(const VEC::const_iterator & b, const VEC::const_iterator & e) const;


    void finalize();

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

    HL_InterpolatorPtr get_yInterpolator(HLR x, HLS start_yIdx, HLS end_yIdx) const;




    void set_yLocalInterpolationData();

    void set_xInterpolators();


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

    HLS n_x_, n_y_;
    /**
     * xInterps_[j]=I_j for j=0,...,(n_y-1) are the x-direction interpolators
     *  introduced in the comment to HL_2_D_CrossInterp
     * */
    std::vector<HL_InterpolatorPtr> xInterps_;

    BSP<HL_2_D_CrossInterpControls> bidimCrossInterpControls_;

    //@}
    /**
     Service class variables
     */
    //@{

    HL_DirectionPtr yDir_;

    HL_InterpControlsPtr serviceInterpControlsPtr_y_;

    HLS nLocalityPoints_y_;

    mutable VEC service_VEC_;


    //@}

}
; // end class HL_2_D_CrossInterp

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_2_D_CrossInterp: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



#define HL_2_D_CrossInterpPtr BSP<HLINTP::HL_2_D_CrossInterp>

//------------------------------------------------------------------------------------------------------

void HL_TEST_HL_2_D_CrossInterpAll();


}// end namespace HL_Interpolation
} // end namespace HL_Math
} //end namespace HorizonLib

#endif // _hl_bidimCubicSpline_h_
