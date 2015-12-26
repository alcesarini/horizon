/**
FILE NAME= hl_vanillaCashFlow.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140523
*/
#ifndef _hl_vanillaCashFlow_h_
#define _hl_vanillaCashFlow_h_


#include <hl/instruments/hl_cashFlow.h>



namespace HorizonLib
{
namespace HL_Instruments
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140523
\brief The code of a fixed cashflow
*/

class HL_FixedCashFlowCode : public virtual HL_CashFlowCode
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

        HL_SERIALIZE_BASE_CLASS(HL_CashFlowCode);

    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_FixedCashFlowCode();

    virtual ~HL_FixedCashFlowCode();
    //@}


    /**
    Public class interface
    */
    //@{

    //@}




    /**
    Public implementations of base class methods
    */
    //@{


    HL_CashFlowType get_cashFlowType() const
    {
        return HL_CashFlowType_Fixed;

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
    HLSTRING objTypeImpl() const;


    //@}

protected:


    /**
    Class variables
    */
    //@{

    //@}

}
; // end class HL_FixedCashFlowCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_FixedCashFlowCodePtr BSP<HLINS::HL_FixedCashFlowCode>





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlow
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140523
\brief FixedCashFlow.
*/
class HL_FixedCashFlow : public virtual HL_CashFlow
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

        HL_SERIALIZE_BASE_CLASS(HL_CashFlow);

        HL_SER(fixedRate_);

    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_FixedCashFlow();

    virtual ~HL_FixedCashFlow();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(HLR, fixedRate);


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


    HLR fixedRate_;

    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_FixedCashFlow


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlow: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




#define HL_FixedCashFlowPtr BSP<HLINS::HL_FixedCashFlow>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141101
\brief The code of a cashflow delivering the underlying.
*/

class HL_VariableCashFlowCode : public virtual HL_CashFlowCode
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

        HL_SERIALIZE_BASE_CLASS(HL_CashFlowCode);

    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_VariableCashFlowCode();

    virtual ~HL_VariableCashFlowCode();
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
    HLSTRING objTypeImpl() const;
    //@}

protected:


    /**
    Class variables
    */
    //@{

    //@}

}
; // end class HL_VariableCashFlowCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_VariableCashFlowCodePtr BSP<HLINS::HL_VariableCashFlowCode>





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlow
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140523
\brief Pays the basket underlying with no modification whatsoever.
*/
class HL_VariableCashFlow : public virtual HL_CashFlow
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

        HL_SERIALIZE_BASE_CLASS(HL_CashFlow);

        HL_SER(basketPtr_);
        HL_SER(nominalFixingTime_);

    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_VariableCashFlow();

    virtual ~HL_VariableCashFlow();
    //@}


    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(HL_BasketPtr, basketPtr);

    HL_CLASS_VAR_ACCESS_METHODS(ptime, nominalFixingTime);


    HL_CLASS_VAR_ACCESS_METHODS(HL_BasketCompositionPtr, basketComposition);



    virtual void checkCashFlow() const;


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
    The cash flow can be computed only observing these basketPtr_.
    */
    HL_BasketPtr basketPtr_;



    /**
    The time the cashflow should become deterministic.
    Notice that we work with times and not simply dates.
    */
    ptime nominalFixingTime_;


    HL_BasketCompositionPtr basketComposition_;
    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_VariableCashFlow


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlow: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




#define HL_VariableCashFlowPtr BSP<HLINS::HL_VariableCashFlow>





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixingState
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141111
\brief To define describe the fixing of an underlying at a date.
*/
class HL_FixingState :  public virtual HLSER::HL_Serializable, public virtual Descriptable
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
        HL_SER(fixingTime_);
        HL_SER(fwdValue_);
        HL_SER(fixingDescription_);
        HL_SER(volState_);


    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_FixingState();

    virtual ~HL_FixingState();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(ptime, fixingTime);

    HL_CLASS_VAR_ACCESS_METHODS(HLR, fwdValue);

    HL_CLASS_VAR_ACCESS_METHODS(HLSTRING, fixingDescription);

    HL_CLASS_VAR_ACCESS_METHODS(HL_VolStatePtr, volState);



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
    The date this fixing refers to.
    */

    ptime fixingTime_;

    /**
    The fwd estimation to fixingDate_ (in the quoting measure of the underlying).
    */
    HLR fwdValue_;



    /**
    What is this fixing? An informative string.
    */
    HLSTRING fixingDescription_;


    /**
    The estimation of the implied vol (in the quoting measure of the underlying).
    We do not further specify the exact defintion of such vol, since it will depended
    on the class that generates this class, i.e. from the context.
    Notice that this class could be used as additional informative output for
    the user of the pricing models.
    */
    HL_VolStatePtr volState_;


    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_FixingState


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixingState: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



#define HL_FixingStatePtr BSP<HLINS::HL_FixingState>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141101
\brief
*/
class HL_VariableCashFlowPricingOutput : public virtual HLINS::HL_CashFlowPricingOutput
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
        HL_SERIALIZE_BASE_CLASS(HLINS::HL_CashFlowPricingOutput);

        HL_SER(nominalFixings_);


    }
    //@} Serialization -----------------------------------

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_VariableCashFlowPricingOutput();

    virtual ~HL_VariableCashFlowPricingOutput();
    //@}


    /**
    Public implementations of base class methods
    */
    //@{



    //@}



    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(std::vector<HL_FixingStatePtr>, nominalFixings);


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


    std::vector<HL_FixingStatePtr> nominalFixings_;



    //@}

private:

    /**
    Private class variables
    */
    //@{




    //@}

}
; // end class HL_VariableCashFlowPricingOutput

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



#define HL_VariableCashFlowPricingOutputPtr BSP<HLINS::HL_VariableCashFlowPricingOutput>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140523
\brief The code of a cashflow delivering the underlying.
*/

class HL_UnderlyingDeliveryCashFlowCode : public virtual HL_VariableCashFlowCode
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

        HL_SERIALIZE_BASE_CLASS(HL_VariableCashFlowCode);

    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_UnderlyingDeliveryCashFlowCode();

    virtual ~HL_UnderlyingDeliveryCashFlowCode();
    //@}


    /**
    Public class interface
    */
    //@{

    //@}



    /**
    Public implementations of base class methods
    */
    //@{


    HL_CashFlowType get_cashFlowType() const
    {
        return HL_CashFlowType_UnderlyingDelivery;

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
    HLSTRING objTypeImpl() const;
    //@}

protected:


    /**
    Class variables
    */
    //@{

    //@}

}
; // end class HL_UnderlyingDeliveryCashFlowCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_UnderlyingDeliveryCashFlowCodePtr BSP<HLINS::HL_UnderlyingDeliveryCashFlowCode>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

typedef HL_VariableCashFlowPricingOutput HL_UnderlyingDeliveryCashFlowPricingOutput;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



#define HL_UnderlyingDeliveryCashFlowPricingOutputPtr BSP<HLINS::HL_UnderlyingDeliveryCashFlowPricingOutput>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlow
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140523
\brief Pays the basket underlying with no modification whatsoever.
*/
class HL_UnderlyingDeliveryCashFlow : public virtual HL_VariableCashFlow
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

        HL_SERIALIZE_BASE_CLASS(HL_VariableCashFlow);


    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_UnderlyingDeliveryCashFlow();

    virtual ~HL_UnderlyingDeliveryCashFlow();
    //@}


    /**
    Public class interface
    */
    //@{


    virtual void checkCashFlow() const;


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

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_UnderlyingDeliveryCashFlow


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlow: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




#define HL_UnderlyingDeliveryCashFlowPtr BSP<HLINS::HL_UnderlyingDeliveryCashFlow>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140523
\brief The code of a cashflow of type HL_VanillaCashFlow.
*/

class HL_VanillaCashFlowCode : public virtual HL_VariableCashFlowCode
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

        HL_SERIALIZE_BASE_CLASS(HL_VariableCashFlowCode);

    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_VanillaCashFlowCode();

    virtual ~HL_VanillaCashFlowCode();
    //@}


    /**
    Public class interface
    */
    //@{

    //@}


    /**
    Public implementations of base class methods
    */
    //@{


    HL_CashFlowType get_cashFlowType() const
    {
        return HL_CashFlowType_Vanilla;

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
    HLSTRING objTypeImpl() const;
    //@}

protected:


    /**
    Class variables
    */
    //@{

    //@}

}
; // end class HL_VanillaCashFlowCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_VanillaCashFlowCodePtr BSP<HLINS::HL_VanillaCashFlowCode>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

typedef HL_VariableCashFlowPricingOutput HL_VanillaCashFlowPricingOutput;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



#define HL_VanillaCashFlowPricingOutputPtr BSP<HLINS::HL_VanillaCashFlowPricingOutput>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlow
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140523
\brief Pays a vanilla on the basket underlying.
*/
class HL_VanillaCashFlow : public virtual HL_VariableCashFlow
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

        HL_SERIALIZE_BASE_CLASS(HL_VariableCashFlow);

        HL_SER(strike_);
        HL_SER(vanillaType_);
        HL_SER(isDigital_);


    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_VanillaCashFlow();

    virtual ~HL_VanillaCashFlow();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(HLR, strike);
    HL_CLASS_VAR_ACCESS_METHODS(HL_VanillaType, vanillaType);
    HL_CLASS_VAR_ACCESS_METHODS(bool, isDigital);


    virtual void checkCashFlow() const;


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

    HLR strike_;

    HL_VanillaType vanillaType_;

    bool isDigital_;



    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_VanillaCashFlow


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlow: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




#define HL_VanillaCashFlowPtr BSP<HLINS::HL_VanillaCashFlow>




} // end namespace HL_Instruments
} //end namespace HorizonLib


#endif // _hl_vanillaCashFlow_h_
