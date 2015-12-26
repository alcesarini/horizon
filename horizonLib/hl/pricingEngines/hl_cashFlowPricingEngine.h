/**
FILE NAME= hl_cashFlowPricingEngine.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20141030
*/
#ifndef _hl_cashFlowPricingEngine_h_
#define _hl_cashFlowPricingEngine_h_

#include <hl/pricingEngines/hl_pricingEngine.h>
#include <hl/instruments/hl_cashFlow.h>

namespace HorizonLib
{
namespace HL_PricingEngines
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineInput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141030
\brief
*/
typedef HL_PricingEngineInput HL_CashFlowPricingEngineInput;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineInput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_CashFlowPricingEngineInputPtr BSP<HLPE::HL_CashFlowPricingEngineInput>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineInputKey
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141030
\brief  Base engine for CashFlow.
*/
class HL_CashFlowPricingEngineInputKey : public virtual HL_PricingEngineInputKey
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
        HL_SERIALIZE_BASE_CLASS(HL_PricingEngineInputKey);
        HL_SER(zcToPayDate_);



    }
    //@} Serialization -----------------------------------

public:

    friend class HL_CashFlowPricingEngine;

    /**
    Constructors & destructors
    */
    //@{

    HL_CashFlowPricingEngineInputKey();

    virtual ~HL_CashFlowPricingEngineInputKey();
    //@}


    /**
    Public class interface
    */
    //@{


    /**
     * To have ordering defined
    */
    virtual HL_Order getOrder(const HL_MachineInputKey & machineInputKey) const;


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

    /**
    Zc of discountinf TS to CashFLow payDate.
    */
    HLR zcToPayDate_;

    //@}

}
; // end class HL_CashFlowPricingEngineInputKey

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineInputKey:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_CashFlowPricingEngineInputKeyPtr BSP<HLPE::HL_CashFlowPricingEngineInputKey>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141030
\brief
*/
typedef HL_PricingEngineOutput HL_CashFlowPricingEngineOutput;


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_CashFlowPricingEngineOutputPtr BSP<HLPE::HL_CashFlowPricingEngineOutput>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_CashFlowPricingEngineType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
\brief The only concrete HL_CashFlowPricingEngine types. Search for this types to find out
which cashlow pricing engines you may actually instantiate and completely use.
*/
enum HL_CashFlowPricingEngineType
{
    HL_CashFlowPricingEngineType_InvalidMin=0,
    HL_CashFlowPricingEngineType_FixedCashFlow,
    HL_CashFlowPricingEngineType_UnderlyingDelivery,
    HL_CashFlowPricingEngineType_AnalyticVanilla,
    HL_CashFlowPricingEngineType_InvalidMax
}; // end enum HL_CashFlowPricingEngineType



//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
        HL_CashFlowPricingEngineType,
        "HL_CashFlowPricingEngineType_InvalidMin",
        "HL_CashFlowPricingEngineType_FixedCashFlow",
        "HL_CashFlowPricingEngineType_UnderlyingDelivery",
        "HL_CashFlowPricingEngineType_AnalyticVanilla",
        "HL_CashFlowPricingEngineType_InvalidMax"
        );





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141030
\brief Basic pricing engine for a HL_CashFlow..
*/
class HL_CashFlowPricingEngine : public virtual HL_PricingEngine
{


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_CashFlowPricingEngine();

    virtual ~HL_CashFlowPricingEngine();
    //@}


    /**
    Public class interface
    */
    //@{

    // HL_CLASS_VAR_ACCESS_METHODS_O(std::vector<HL_CashFlowPtr>/*ClassVariableType*/, cashFlows/*classVariableName_no_underscore*/);


    virtual HL_CashFlowPricingEngineType get_cashFlowPricingEngineType() const=0;

    /**
    Specifies which kind of chasflows this engine can take care of (i.e. can price).
    */
    const std::set<HLINS::HL_CashFlowType> & get_allowedCashFlowTypes() const;

    /**
    Ensures that the current egine can manage the given cashFlowType.
    */
    void ensureCashFlowTypeAllowed(HLINS::HL_CashFlowType cashFlowType) const;


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
    Builds and returns the fwd-measure associated to the HL_CashFlow payDate and to
    the class HL_PricingEngineInput::riskFreeDiscounting_.
    */
    HL_FwdMeasurePtr getRiskFreeDiscountingFwdMeasure() const;

    //@}


    /**
    Implementations of base class methods
    */
    //@{
    void descriptionImpl(std::ostream & os) const;

    void buildInputKey(const HL_MachineInputPtr & input,
                       HL_MachineInputKeyPtr & machineInputKey) const;

    HL_PricingEngineOutputPtr performEngineComputations() const;


    virtual void instantiateCashFlowPricingOutput() const=0;

    virtual void fillCashFlowPricingOutput() const;

    virtual bool isPayoffDeterministic() const=0;

    /**
    Here's the core of the computation.

    Should compute HL_CashFlowPricingOutput::payoff_, so check the comment there to
    understand the meaning of this method.
    */
    virtual HLR computeCashFlowPayoff() const=0;

    virtual void instantiateCashFlowPricingEngineOutput() const=0;

    virtual void cleanDisposableData() const
    {

        cashFlowPricingEngineDisposableData_=CashFlowPricingEngineDisposableData();
    }


    //@}

protected:


    /**
    Class variables
    */
    //@{


    //@}


    struct CashFlowPricingEngineDisposableData
    {

        CashFlowPricingEngineDisposableData()
            :
              cashFlow(NULL)
        {}
        //@{
        HL_CashFlowPricingEngineInputPtr input;

        HL_CashFlowPricingEngineInputKeyPtr inputKey;

        const HLINS::HL_CashFlow * cashFlow;

        HL_CashFlowStructurePtr cashFlowStructure;

        HL_CashFlowPricingOutputPtr cashFlowPricingOutput;

        HL_CashFlowPricingEngineOutputPtr cashFlowPricingEngineOutput;
        //@}

    }; // end struct CashFlowPricingEngineDisposableData

    mutable CashFlowPricingEngineDisposableData cashFlowPricingEngineDisposableData_;


}; // end class HL_CashFlowPricingEngine


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngine: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_CashFlowPricingEnginePtr BSP<HLPE::HL_CashFlowPricingEngine>







//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineAssociation
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20150524
\brief It's a map that says which HL_CashFlowPricingEngineType can be associated to
which HL_CashFlowType.
*/
class HL_CashFlowPricingEngineAssociation : public virtual Descriptable
{


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_CashFlowPricingEngineAssociation();

    virtual ~HL_CashFlowPricingEngineAssociation();
    //@}


    /**
    Public class interface
    */
    //@{

    // HL_CLASS_VAR_ACCESS_METHODS_O(std::vector<HL_CashFlowPtr>/*ClassVariableType*/, cashFlows/*classVariableName_no_underscore*/);

    /**
    What cashFlowPricingEngineType can price?
    */
    const std::set<HLINS::HL_CashFlowType> &
    get_allowedCashFlowTypes(HL_CashFlowPricingEngineType cashFlowPricingEngineType) const;


    /**
    What cashFlowType can be priced with?
    */
    std::set<HL_CashFlowPricingEngineType>
    get_allowedCashFlowPricingEngineTypes(HLINS::HL_CashFlowType cashFlowType) const;



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


    /**
    This states for each concrete HL_CashFlowPricingEngine (i.e. for each HL_CashFlowPricingEngineType)
    which kind of HL_CashFlow (i.e. of HL_CashFlowType) could be manged by the engine.
    */
    std::map<HL_CashFlowPricingEngineType, std::set<HLINS::HL_CashFlowType> > associations_;

}; // end class HL_CashFlowPricingEngineAssociation


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineAssociation: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_CashFlowPricingEngineAssociationPtr BSP<HLPE::HL_CashFlowPricingEngineAssociation>


//------------------------------------------------------------------------------------------------------

/**
Returns the unique static instance of HL_CashFlowPricingEngineAssociation to know the
right association cashFlowPricingEngineType vs. cashFlowType in a unique way for the whole HL library world.
*/
HL_CashFlowPricingEngineAssociationPtr get_cashFlowPricingEngineStaticAssociation();

//------------------------------------------------------------------------------------------------------

/**
Ensure that cashFlowPricingEngineType is good to price cashFlowType
*/
void ensureCashFlowPricingEngineAllowed(HL_CashFlowPricingEngineType cashFlowPricingEngineType,
                                        HLINS::HL_CashFlowType cashFlowType);


} // end namespace HL_PricingEngines
} //end namespace HorizonLib


#endif // _hl_cashFlowPricingEngine_h_
