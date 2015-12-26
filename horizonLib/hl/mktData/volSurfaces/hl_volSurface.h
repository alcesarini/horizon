/**
FILE NAME= hl_volSurface.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131227
*/
#ifndef _hl_volSurface_h_
#define _hl_volSurface_h_

#include <hl/mktData/hl_mktData.h>
#include <hl/math/probMeasures/hl_probMeasure.h>

namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_VolSurfaces
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_ImpliedVolModelTypeType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
\brief To specify the model the implied vol refers to.
*/
enum HL_ImpliedVolModelTypeType
{
    HL_ImpliedVolModelTypeType_InvalidMin=0,
    /**
     * The classic non-shifted log-normal vol for BS model
     * */
    HL_ImpliedVolModelTypeType_LogNormal,
    /**
     * Shifted log-normal BS model
     * */
    HL_ImpliedVolModelTypeType_ShiftedLogNormal,
    /**
     * The underlying model follows a normal distribution.
     * */
    HL_ImpliedVolModelTypeType_Normal,
    HL_ImpliedVolModelTypeType_InvalidMax
}; // end enum HL_ImpliedVolModelTypeType

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
        HL_ImpliedVolModelTypeType,
        "HL_ImpliedVolModelTypeType_InvalidMin",
        "HL_ImpliedVolModelTypeType_LogNormal",
        "HL_ImpliedVolModelTypeType_ShiftedLogNormal",
        "HL_ImpliedVolModelTypeType_Normal",
        "HL_ImpliedVolModelTypeType_InvalidMax"
        );



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VolState
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141123
\brief The output of a call to HL_VolSurface.
*/
class HL_VolState :  public virtual HLSER::HL_Serializable, public virtual Descriptable
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
        HL_SER(vol_);
        HL_SER(stdDev_);
        HL_SER(timeFactor_);
        HL_SER(sqrtTimeFactor_);
        HL_SER(impliedVolModelTypeType_);

    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_VolState();

    virtual ~HL_VolState();
    //@}


    /**
    Public class interface
    */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS_O(HLR, vol);
    HL_CLASS_VAR_ACCESS_METHODS_O(HLR, stdDev);
    HL_CLASS_VAR_ACCESS_METHODS_O(HLR, timeFactor);
    HL_CLASS_VAR_ACCESS_METHODS_O(HLR, sqrtTimeFactor);
    HL_CLASS_VAR_ACCESS_METHODS_O(HL_ImpliedVolModelTypeType, impliedVolModelTypeType);



    void set_volState(HLR vol, HLR timeFactor, HL_ImpliedVolModelTypeType impliedVolModelTypeType);



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


    HLR vol_;

    HLR stdDev_;

    HLR timeFactor_;

    HLR sqrtTimeFactor_;

    HL_ImpliedVolModelTypeType impliedVolModelTypeType_;
    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_VolState


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VolState: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



#define HL_VolStatePtr BSP<HLVOL::HL_VolState>





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VolSurfaceCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131213
\brief The vol surface code
*/

class HL_VolSurfaceCode : public virtual HL_MktDataCode
{
public:


    /**
    Constructors & destructors
    */
    //@{

    HL_VolSurfaceCode();

    virtual ~HL_VolSurfaceCode();
    //@}


    /**
    Public class interface
    */
    //@{

    //@}


protected:

    /**
    Implementations of base class methods
    */
    //@{
    HLSTRING objTypeImpl() const;
    //@}


    /**
    Additional implementations
    */
    //@{
    /**
    Default initialization of the class vars.
    */
    void classDefaultInit();
    //@}

protected:


    /**
    Class variables
    */
    //@{

    //@}

}
; // end class HL_VolSurfaceCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VolSurfaceCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_VolSurfaceCodePtr BSP<HLVOL::HL_VolSurfaceCode>





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VolSurface
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131213
\brief Base class for all vol surfaces, allowing to deal with a correction w.r.t. different fwd maturities.
Check comment to the vol(..) method.
*/
class HL_VolSurface : public virtual HL_MktData
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

        HL_SERIALIZE_BASE_CLASS(HL_MktData);

        HL_SER(impliedVolModelTypeType_);
        HL_SER(riskFreeDiscounting_);



    }
    //@} Serialization -----------------------------------

public:



    /**
    Constructors & destructors
    */
    //@{

    HL_VolSurface();

    virtual ~HL_VolSurface();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(HL_ImpliedVolModelTypeType, impliedVolModelTypeType);
    HL_CLASS_VAR_ACCESS_METHODS(HL_RiskFreeDiscountingPtr, riskFreeDiscounting);



    /**
    Implied vol in time interval [get_refTime(), t] for a vanilla option having strike equal to k
    whose payout is

    [sign*(F(t, fwdMaturityDate)-k)]^+

    where F(t, fwdMaturityDate) = E[S(fwdMaturityDate)|F_t]

    Notice that we add an additional variable, namely fwdMaturityDate, w.r.t. standard
    get_vol methods. This is so since we want to have the possibility to model not
    only the vol of an underlying, but the vol of the fwd process of un underlying for
    any fwd maturity.
    If such additional degree of freedom is not nedeed, simply use a derivation of this
    class that ignores it.
    */
    HL_VolStatePtr vol(const ptime &t, HLR k, const ptime & fwdMaturityTime) const;

    HL_VolStatePtr vol(const date &d, HLR k, const ptime & fwdMaturityTime) const
    {

        return vol(ptime(d), k, fwdMaturityTime);

    }



    void set_HL_ObjCodePtr(const HL_ObjCodePtr & hl_ObjCodePtr);


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

    /**
    The ultimate source of the data
    */
    virtual HLR volImpl(HLR yf, HLR k, HLR fwd_yf) const=0;

    HLR get_yf(const ptime &t) const;

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

    HL_ImpliedVolModelTypeType impliedVolModelTypeType_;

    /**
     * This is the pricing measure in which the implied volatility surfcae should be used.
     *
    */
    HL_RiskFreeDiscountingPtr riskFreeDiscounting_;


    HL_VolSurfaceCodePtr volSurfaceCode_;


    //@}

}
; // end class HL_VolSurface


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VolSurface: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_VolSurfacePtr BSP<HLVOL::HL_VolSurface>

//------------------------------------------------------------------------------------------------------

HL_VolSurfacePtr get_VolSurfacePtr(const HL_MktDataCollectorPtr & mktDataCollectorPtr, const HL_ObjCodePtr & objCodePtr);



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FlatVolSurface
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131213
\brief Specializes HL_VolSurface for flat vol.
*/
class HL_FlatVolSurface : public virtual HL_VolSurface
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

        HL_SERIALIZE_BASE_CLASS(HL_MktData);

        HL_SER(flatVol_);



    }
    //@} Serialization -----------------------------------

public:



    /**
    Constructors & destructors
    */
    //@{

    HL_FlatVolSurface();

    virtual ~HL_FlatVolSurface();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(HLR, flatVol);

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


    /**
    The ultimate source of the data
    */
    HLR volImpl(HLR yf, HLR k, HLR fwd_yf) const
    {
        return flatVol_;
    }
    //@}

protected:


    /**
    Class variables
    */
    //@{


    HLR flatVol_;

    //@}

}
; // end class HL_FlatVolSurface


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FlatVolSurface: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_FlatVolSurfacePtr BSP<HLVOL::HL_FlatVolSurface>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_HL_VolSurfaceCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_VolSurfaceCodePtr HL_TEST_get_HL_VolSurfaceCode(const HL_FinObjCodePtr & finObjCode);


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_HL_VolSurface
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_VolSurfacePtr HL_TEST_get_HL_VolSurface(const HL_VolSurfaceCodePtr &volSurfaceCode,
                                           const HL_RiskFreeDiscountingPtr &riskFreeDiscounting,
                                           HLR flatVolValue);




} // end namespace HL_VolSurfaces
} // end namespace HL_MarketData
} //end namespace HorizonLib


#endif // _hl_volSurface_h_
