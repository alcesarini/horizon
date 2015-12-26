/**
FILE NAME= hl_cashFlow.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140521
*/
#ifndef _hl_cashFlow_h_
#define _hl_cashFlow_h_

#include <hl/instruments/hl_baseIns.h>
#include <hl/instruments/hl_basket.h>
#include <hl/instruments/anagraphics/hl_scheduleAnagraphics.h>
#include <hl/dateTime/hl_dcc.h>


namespace HorizonLib
{
namespace HL_Instruments
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141028
\brief Some basic data defining any cashflow.
*/
class HL_CashFlowStructure :  public virtual HLSER::HL_Serializable, public virtual Descriptable
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

        HL_SER(payDate_);
        HL_SER(accrualPeriod_);
        HL_SER(notional_);
        HL_SER(payoffLeverage_);
        HL_SER(spread_);
        HL_SER(dccPtr_);
    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_CashFlowStructure();

    virtual ~HL_CashFlowStructure();
    //@}


    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(date, payDate);

    HL_CLASS_VAR_ACCESS_METHODS(HL_AccrualPeriodPtr, accrualPeriod);

    HL_CLASS_VAR_ACCESS_METHODS(HLR, notional);

    HL_CLASS_VAR_ACCESS_METHODS(HLR, payoffLeverage);

    HL_CLASS_VAR_ACCESS_METHODS(HLR, spread);

    HL_CLASS_VAR_ACCESS_METHODS(HL_DccPtr, dccPtr);


    const date & get_accrualStartDate() const
    {
        return accrualPeriod_->get_accrualStartDate();
    }


    const date & get_accrualEndDate() const
    {
        return accrualPeriod_->get_accrualEndDate();
    }


    HL_Order getOrder(const HL_CashFlowStructure & cashFlowStructure) const;

    void checkCashFlowStructure() const;


    /**
    To be used to get accruals
    */
    HLR tau(const date & d) const;

    HLR tau() const
    {
        return tau(get_accrualEndDate());
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


    date payDate_;

    HL_AccrualPeriodPtr accrualPeriod_;


    HLR notional_;

    HLR payoffLeverage_;

    HLR spread_;

    HL_DccPtr dccPtr_;

    //@}

}
; // end class HL_CashFlowStructure


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowStructure: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------





#define HL_CashFlowStructurePtr BSP<HLINS::HL_CashFlowStructure>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_CashFlowType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
\brief The HL library period units.
*/
enum HL_CashFlowType
{
    HL_CashFlowType_InvalidMin=0,
    HL_CashFlowType_Fixed,
    HL_CashFlowType_UnderlyingDelivery,
    HL_CashFlowType_Vanilla,
    HL_CashFlowType_InvalidMax
}; // end enum HL_CashFlowType

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
        HL_CashFlowType,
        "HL_CashFlowType_InvalidMin",
        "HL_CashFlowType_Fixed",
        "HL_CashFlowType_UnderlyingDelivery",
        "HL_CashFlowType_Vanilla",
        "HL_CashFlowType_InvalidMax"
        );


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140521
\brief The code of a cashflow
*/

class HL_CashFlowCode : public virtual HLINS::HL_InstrumentCode
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

        HL_SERIALIZE_BASE_CLASS(HLINS::HL_InstrumentCode);

    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_CashFlowCode();

    virtual ~HL_CashFlowCode();
    //@}


    /**
    Public class interface
    */
    //@{

    virtual HL_CashFlowType get_cashFlowType() const=0;



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
; // end class HL_CashFlowCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_CashFlowCodePtr BSP<HLINS::HL_CashFlowCode>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlow
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140521
\brief A cashflow, i.e. a single financial payment, i.e. a financial object.
*/
class HL_CashFlow : public virtual HLINS::HL_EnginedInstrument
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

        HL_SERIALIZE_BASE_CLASS(HLINS::HL_EnginedInstrument);

        HL_SER(cashFlowCode_);
        HL_SER(cashFlowStructure_);


    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_CashFlow();

    virtual ~HL_CashFlow();
    //@}



    /**
    Public implementations of base class methods
    */
    //@{

    void set_HL_ObjCodePtr(const HL_ObjCodePtr & hl_ObjCodePtr);


    HLS get_nbCashFlows() const
    {
        return 1;
    }

    const HL_CashFlow & get_cashFlow(HLS cashFlowIdx) const
    {

        return *this;
    }



    //@}


    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS_O(HL_CashFlowCodePtr, cashFlowCode);

    HL_CLASS_VAR_ACCESS_METHODS(HL_CashFlowStructurePtr, cashFlowStructure);

    HL_CashFlowType get_cashFlowType() const
    {
        return cashFlowCode_->get_cashFlowType();

    }

    const date & get_payDate() const
    {
        return cashFlowStructure_->get_payDate();
    }



    HL_Order getOrder(const HL_CashFlow & hl_CashFlow) const;



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


    HL_CashFlowCodePtr cashFlowCode_;

    HL_CashFlowStructurePtr cashFlowStructure_;



    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_CashFlow


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlow: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_DEFINE_ALL_ORDERING(HL_CashFlow);





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140914
\brief
*/
class HL_CashFlowPricingOutput : public virtual HLINS::HL_InstrumentOutput
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
        HL_SERIALIZE_BASE_CLASS(HLINS::HL_InstrumentOutput);

        HL_SER(cashFlowStructure_);
        HL_SER(payoff_);
        HL_SER(zcToPayDate_);
        HL_SER(isPayoffDeterministic_);



    }
    //@} Serialization -----------------------------------

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_CashFlowPricingOutput();

    virtual ~HL_CashFlowPricingOutput();
    //@}


    /**
    Public implementations of base class methods
    */
    //@{


    HLR get_dirtyPrice() const
    {
        HLR dirty = get_notional()*get_rate()*tau()*get_zcToPayDate();
        return dirty;
    }

    HLR get_accrued(const date& d) const;

    HLS get_nbCashFlowPricingOutputs() const
    {
        return 1;

    }


    const HL_CashFlowPricingOutput & get_CashFlowPricingOutput(HLS cashFlowPricingOutputIdx) const
    {

        HL_SRE(cashFlowPricingOutputIdx==0, "cashFlowPricingOutputIdx=" << cashFlowPricingOutputIdx);

        return *this;
    }





    //@}



    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(HL_CashFlowStructurePtr, cashFlowStructure);
    HL_CLASS_VAR_ACCESS_METHODS(HLR, payoff);
    HL_CLASS_VAR_ACCESS_METHODS(HLR, zcToPayDate);
    HL_CLASS_VAR_ACCESS_METHODS(bool, isPayoffDeterministic);


    HLR get_notional() const
    {
        return get_cashFlowStructure()->get_notional();
    }

    HLR get_payoffLeverage() const
    {
        return get_cashFlowStructure()->get_payoffLeverage();
    }

    HLR get_spread() const
    {
        return get_cashFlowStructure()->get_spread();
    }



    HLR get_rate() const
    {

        HLR r = get_payoffLeverage() * payoff_ + get_spread();
        return r;
    }

    HLR tau(const date & d) const
    {
        return cashFlowStructure_->tau(d);
    }

    HLR tau() const
    {
        return cashFlowStructure_->tau();
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

    HL_CashFlowStructurePtr cashFlowStructure_;

    /**
    By construction, it has to hold that:

    dirtyPrice = get_notional()*get_rate() * tau() * zcToPayDate_

    where remind that

    get_rate() = (payoffLeverage_ * payoff_ + spread_)

    tau() = tau(cashFlowStructure_->tau())

    Notice that the equation above implies that payoff_ = E^P[stochasticPayout|refDate],
    where E^P denotes expecation in the payDate-fwd measure of the "pricing ccy".
    */

    HLR payoff_;

    HLR zcToPayDate_;

    bool isPayoffDeterministic_;

    //@}

private:

    /**
    Private class variables
    */
    //@{


    //@}

}
; // end class HL_CashFlowPricingOutput

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



#define HL_CashFlowPricingOutputPtr BSP<HLINS::HL_CashFlowPricingOutput>





} // end namespace HL_Instruments
} //end namespace HorizonLib


#endif // _hl_cashFlow_h_
