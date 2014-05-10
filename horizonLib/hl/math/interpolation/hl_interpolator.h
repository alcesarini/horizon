/**
FILE NAME=hl_interpolator.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131227
*/
#ifndef _hl_interpolator_h_
#define _hl_interpolator_h_

#include <hl/math/hl_function.h>
#include <hl/containers/hl_multiArray.h>

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

/**
\author A. Cesarini
\date 20131228
\brief Describes the discretization of a direction in a grid of points.
*/
class HL_Direction : public virtual HLSER::HL_Serializable, public virtual Descriptable
{

    /**
    -----------------------------------------------------
    Serialization
    */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS;

    template<class Archive>
    void serialize(Archive &ar, const HLS version)
    {
        HL_SER_BASE;
        HL_SER(x_);
        HL_SER(delta_x_);
        HL_SER(extrapolateLeft_);
        HL_SER(extrapolateRight_);
        HL_SER(localization_);
    }
    //@} Serialization -----------------------------------

public:

    struct HL_LocalizationSide : public virtual HLSER::HL_Serializable
    {

        /**
        -----------------------------------------------------
        Serialization
        */
        //@{
        HL_FRIEND_SERIALIZATION_ACCESS;

        template<class Archive>
        void serialize(Archive &ar, const HLS version)
        {
            HL_SER_BASE;
            HL_SER(idx);
            HL_SER(weight);

        }
        //@} Serialization -----------------------------------


        HL_LocalizationSide()
            :
              idx(HL_NULL_INTEGER), weight(HL_NULL_REAL)
        {}

        HLS idx;
        HLR weight;


    }
    ; // end struct HL_LocalizationSide

    struct HL_Localization
    {

        enum SideType
        {
            Left=0,
            Right=1
        }; // end enum SideType


        /**
        -----------------------------------------------------
        Serialization
        */
        //@{
        HL_FRIEND_SERIALIZATION_ACCESS;

        template<class Archive>
        void serialize(Archive &ar, const HLS version)
        {
            HL_SER(localizationSides);

        }
        //@} Serialization -----------------------------------

        /**
        localizationSides[0] is the leftSide, localizationSides[1] is the rightSide
        */
        boost::array<HL_LocalizationSide, 2> localizationSides;
    }
    ; // end struct HL_Localization

    /**
    Constructors & destructors
    */
    //@{

    HL_Direction();

    virtual ~HL_Direction();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(HL_Localization, localization);
    HL_CLASS_VAR_ACCESS_METHODS(bool, extrapolateLeft);
    HL_CLASS_VAR_ACCESS_METHODS(bool, extrapolateRight);
    HL_CLASS_VAR_ACCESS_METHODS_O(VEC, delta_x);


    void set_x(const VEC &x);

    const VEC &get_x() const
    {
        return x_;
    }

    VEC &get_x()
    {
        return x_;
    }

    void finalize();

    HLR get_x(HLS pointIdx) const
    {
        return  get_x()[pointIdx];
    }

    HLS nbPoints() const
    {
        return x_.size();
    }

    HLR leftBorder() const
    {

        return get_x(0);
    }

    HLR rightBorder() const
    {

        return get_x(nbPoints()-1);
    }


    const HL_Localization & localize(HLR x) const;
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
    It must hold that x_[i]<x_[i+1]
    */
    VEC x_;
    VEC delta_x_;

    /**
    If this variable is false, it means that any intepolation method driven by this class
    should act as if the input point x was floored by x_[0].
    */
    bool extrapolateLeft_;
    /**
    If this variable is false, it means that any intepolation method driven by this class
    should act as if the input point x was capped by x_[x_.size()-1].
    */
    bool extrapolateRight_;

    mutable HL_Localization localization_;
    //@}

}
; // end class HL_Direction


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Direction: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_DirectionPtr BSP<HLINTP::HL_Direction>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_InterpolatorType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
\brief Check the classes that return each type as own interpolator type.
*/
enum HL_InterpolatorType
{
    HL_InterpolatorType_InvalidMin=0,
    HL_InterpolatorType_n_D_Linear,
    HL_InterpolatorType_1_D_CubicSpline,
    HL_InterpolatorType_1_D_CubicLocalParabolic,
    HL_InterpolatorType_2_D_CrossInterp,
    HL_InterpolatorType_InvalidMax
}; // end enum HL_InterpolatorType

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
        HL_InterpolatorType,
        "HL_InterpolatorType_InvalidMin",
        "HL_InterpolatorType_n_D_Linear",
        "HL_InterpolatorType_1_D_CubicSpline",
        "HL_InterpolatorType_1_D_CubicLocalParabolic",
        "HL_InterpolatorType_2_D_CrossInterp",
        "HL_InterpolatorType_InvalidMax"
        );




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterpControls
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20140203
 \brief Base class to provide data for to build instances of class HL_Interpolator.
 */
class HL_InterpControls : public virtual Descriptable
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
        HL_SER(directions_);
    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_InterpControls();

    virtual ~HL_InterpControls();
    //@}

    /**
     Public class interface
     */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(std::vector<HL_DirectionPtr>, directions);


    HLS get_nDim() const
    {

        return directions_.size();
    }

    virtual HL_InterpolatorType get_InterpolatorType() const=0;

    /**
     * Considering the dimIdx-th direction,
     * suppose that x_i <= x <= x_{i+1} and suppose that k=nLocalityPoints(dimIdx).
     * We then know that the interpolated values at x will depend only on the following points:
     * x_{i-k}, x_{i-k+1}, ..., x_i, x_{i+1},  x_{i+2}, ... x_{i+1+k-1},  x_{i+1+k}
     * In other words, the biggest k the less local is the interpolation applied to the dimIdx-th direction.
     * Notice that this method could return HL_MAX_INTEGER, meaning that the interpolation scheme is totally non-local.
     * */
    virtual HLS nLocalityPoints(HLS dimIdx) const=0;

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

    std::vector<HL_DirectionPtr> directions_;
    //@}

}
; // end class HL_InterpControls

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterpControls: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_InterpControlsPtr BSP<HLINTP::HL_InterpControls>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Interpolator
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131227
\brief Base class for interpolators.
*/
class HL_Interpolator : public virtual HL_Function
{

    /**
    -----------------------------------------------------
    Serialization
    */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS;

    template<class Archive>
    void serialize(Archive &ar, const HLS version)
    {
        HL_SERIALIZE_BASE_CLASS(HL_Function);
        HL_SER(interpControlsPtr_);
        HL_SER(realMultiArrayPtr_);


    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_Interpolator();

    virtual ~HL_Interpolator();
    //@}


    /**
    Public class interface
    */
    //@{



    HL_InterpolatorType get_InterpolatorType() const
    {

        return interpControlsPtr_->get_InterpolatorType();

    }

    HL_CLASS_VAR_ACCESS_METHODS_O(HL_InterpControlsPtr, interpControlsPtr);

    HL_CLASS_VAR_ACCESS_METHODS_O(HL_RealMultiArrayPtr, realMultiArrayPtr);


    void setPoint(const HLMIDX & multiIndex, HLR value)
    {

        updateComputationRefreshTab(multiIndex);
        (*realMultiArrayPtr_)[multiIndex]=value;
    }

    void set_interpControlsPtr(const HL_InterpControlsPtr &interpControlsPtr);


    /**
     * Call this method if you need to create room for data
     * */
    void instantiateMultiArray();

    /**
     * Call this method if you already have from outside and for some reason
     * an appropriate instance of realMultiArrayPtr_ to be directly
     * set into this class, avoiding data duplication.
     * */
    void set_realMultiArrayPtr(const HL_RealMultiArrayPtr &realMultiArrayPtr);

    /**
     * Automatically called at the end of method set_realMultiArrayPtr to get the class ready to work
     * or to be called by the user before using the interpolator.
     * */
    virtual void finalize()
    {}



    HLS get_nbPointsInDimension(HLS dimIdx) const
    {
        return realMultiArrayPtr_->get_nbPointsInDimension(dimIdx);
    }




    const std::vector<HL_DirectionPtr> & get_directions() const
    {

        return interpControlsPtr_->get_directions();
    }

    const HL_DirectionPtr & get_direction(HLS dimIdx) const
    {

        return get_directions()[dimIdx];
    }

    const HL_Direction::HL_Localization & get_localization(HLS dimIdx) const
    {

        return get_direction(dimIdx)->get_localization();
    }

    HLR getAbscissa(HLS dimIdx, HLS pointIdx) const
    {
        return  get_direction(dimIdx)->get_x()[pointIdx];
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



    HL_Disposable<HLCTRS::HL_MultiIndexHelper::ShapeType > get_shape() const;


    void localize(const VEC::const_iterator & b, const VEC::const_iterator & e) const;



    /**
     * The purpose of this method is to be called when setting points into realMultiArrayPtr_ in
     * order to keep track of what computations should be re-performed in reason of the newly
     * set points. The aim is to refresh (in method refreshComputations) just what strictly necessary in order to speed up of course.
     * Of course any derived class will implement this method differently.
     * */
    virtual void updateComputationRefreshTab(const HLMIDX & multiIndex)
    {

    }

    /**
     * Contains part of the actual math computations that the interpolator has to perform and in particular
     * the ones that should be refreshed once the geometry of the grid has been fixed and one changes only the
     * values of some the points inside realMultiArrayPtr_.
     * This methiod could in principle refresh only a part of the computations, i.e. only the ones that
     * whose results may have been affected by the points that have been changed.
     * */
    virtual void refreshComputations()
    {

    }

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

    HL_InterpControlsPtr interpControlsPtr_;

    HL_RealMultiArrayPtr realMultiArrayPtr_;



    //@}

    /**
    Service class variables
    */
    //@{


    //@}
}
; // end class HL_Interpolator


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Interpolator: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_InterpolatorPtr BSP<HLINTP::HL_Interpolator>

//------------------------------------------------------------------------------------------------------


/**
 * \author A. Cesarini
 * \date 20140208
 * \brief Utility method to instantiate classes deriving from HL_Interpolator, when
 * a realMultiArrayPtr is readily available.
 *
 *
 */
HL_InterpolatorPtr interpolatorPtrFactory(const HL_InterpControlsPtr &interpControlsPtr,
                                          const HL_RealMultiArrayPtr &realMultiArrayPtr);


} // end namespace HL_Interpolation
} // end namespace HL_Math
} //end namespace HorizonLib


#endif // _hl_interpolator_h_
