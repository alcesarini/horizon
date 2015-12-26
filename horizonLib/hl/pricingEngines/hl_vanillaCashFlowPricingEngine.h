/**
FILE NAME= hl_vanillaCashFlowPricingEngine.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140920
*/
#ifndef _hl_vanillaCashFlowPricingEngine_h_
#define _hl_vanillaCashFlowPricingEngine_h_

#include <hl/pricingEngines/hl_cashFlowPricingEngine.h>
#include <hl/instruments/hl_vanillaCashFlow.h>

namespace HorizonLib
{
namespace HL_PricingEngines
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowPricingEngineInput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140920
\brief
*/
typedef HL_CashFlowPricingEngineInput HL_FixedCashFlowPricingEngineInput;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowPricingEngineInput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_FixedCashFlowPricingEngineInputPtr BSP<HLPE::HL_FixedCashFlowPricingEngineInput>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowPricingEngineInputKey
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141101
\brief
*/
typedef HL_CashFlowPricingEngineInputKey HL_FixedCashFlowPricingEngineInputKey;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowPricingEngineInputKey:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_FixedCashFlowPricingEngineInputKeyPtr BSP<HLPE::HL_FixedCashFlowPricingEngineInputKey>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowPricingEngineOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140914
\brief
*/
typedef HL_CashFlowPricingEngineOutput HL_FixedCashFlowPricingEngineOutput;


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowPricingEngineOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_FixedCashFlowPricingEngineOutputPtr BSP<HLPE::HL_FixedCashFlowPricingEngineOutput>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowPricingEngine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140902
\brief Basic pricing engine.
*/
class HL_FixedCashFlowPricingEngine : public virtual HL_CashFlowPricingEngine
{


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_FixedCashFlowPricingEngine();

    virtual ~HL_FixedCashFlowPricingEngine();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CashFlowPricingEngineType get_cashFlowPricingEngineType() const
    {
        return HL_CashFlowPricingEngineType_FixedCashFlow;
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

    void buildInputKey(const HL_MachineInputPtr & input,
                       HL_MachineInputKeyPtr & machineInputKey) const;


    virtual void instantiateCashFlowPricingOutput() const;

    virtual void fillCashFlowPricingOutput() const;

    virtual bool isPayoffDeterministic() const;

    /**
    Here's the core of the computation
    */
    virtual HLR computeCashFlowPayoff() const;

    virtual void instantiateCashFlowPricingEngineOutput() const;




    virtual void cleanDisposableData() const
    {
        fixedCashFlowPricingEngineDisposableData_=FixedCashFlowPricingEngineDisposableData();
    }

    //@}

protected:


    /**
    Class variables
    */
    //@{


    //@}


    struct FixedCashFlowPricingEngineDisposableData
    {

        FixedCashFlowPricingEngineDisposableData()
            :
              fixedCashFlow(NULL)
        {}
        //@{
        HL_FixedCashFlowPricingEngineInputPtr input;

        HL_FixedCashFlowPricingEngineInputKeyPtr inputKey;

        const HLINS::HL_FixedCashFlow* fixedCashFlow;

        HL_CashFlowPricingOutputPtr cashFlowPricingOutput;

        HL_CashFlowPricingEngineOutputPtr cashFlowPricingEngineOutput;


        //@}

    }; // end struct FixedCashFlowPricingEngineDisposableData

    mutable FixedCashFlowPricingEngineDisposableData fixedCashFlowPricingEngineDisposableData_;


}; // end class HL_FixedCashFlowPricingEngine


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowPricingEngine: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_FixedCashFlowPricingEnginePtr BSP<HLPE::HL_FixedCashFlowPricingEngine>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngineInput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141101
\brief
*/
typedef HL_CashFlowPricingEngineInput HL_VariableCashFlowPricingEngineInput;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngineInput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_VariableCashFlowPricingEngineInputPtr BSP<HLPE::HL_VariableCashFlowPricingEngineInput>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngineInputKey
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141030
\brief  Base engine for CashFlow.
*/
class HL_VariableCashFlowPricingEngineInputKey : public virtual HL_CashFlowPricingEngineInputKey
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
        HL_SER(fwds_);
        HL_SER(vols_);
        HL_SER(underlyingQuantities_);


    }
    //@} Serialization -----------------------------------

public:

    friend class HL_VariableCashFlowPricingEngine;

    /**
    Constructors & destructors
    */
    //@{

    HL_VariableCashFlowPricingEngineInputKey();

    virtual ~HL_VariableCashFlowPricingEngineInputKey();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(VEC, fwds);
    HL_CLASS_VAR_ACCESS_METHODS(VEC, vols);
    HL_CLASS_VAR_ACCESS_METHODS(VEC, underlyingQuantities);

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

    VEC fwds_;
    VEC vols_;


    VEC underlyingQuantities_;

    //@}

}
; // end class HL_VariableCashFlowPricingEngineInputKey

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngineInputKey:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_VariableCashFlowPricingEngineInputKeyPtr BSP<HLPE::HL_VariableCashFlowPricingEngineInputKey>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngineOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140914
\brief
*/
typedef HL_CashFlowPricingEngineOutput HL_VariableCashFlowPricingEngineOutput;


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngineOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_VariableCashFlowPricingEngineOutputPtr BSP<HLPE::HL_VariableCashFlowPricingEngineOutput>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141101
\brief Basic pricing engine.
*/
class HL_VariableCashFlowPricingEngine : public virtual HL_CashFlowPricingEngine
{


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_VariableCashFlowPricingEngine();

    virtual ~HL_VariableCashFlowPricingEngine();
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
    void descriptionImpl(std::ostream & os) const;

    void buildInputKey(const HL_MachineInputPtr & input,
                       HL_MachineInputKeyPtr & machineInputKey) const;


    virtual void instantiateCashFlowPricingOutput() const;

    virtual void fillCashFlowPricingOutput() const;

    virtual bool isPayoffDeterministic() const;

    /**
    Here's the core of the computation
    */
    virtual HLR computeCashFlowPayoff() const;

    virtual void instantiateCashFlowPricingEngineOutput() const;

    virtual void cleanDisposableData() const
    {

        variableCashFlowPricingEngineDisposableData_=VariableCashFlowPricingEngineDisposableData();
    }



    /**
    This time is to be provided even in the case in which the coupon depends on more
    than a single fixing time. For ex. if the coupon is asian it must be the final asian fixing.
    So this time is to be representive of the coupon fixing date
    */
    ptime get_nominalFixingTime() const
    {

        return variableCashFlowPricingEngineDisposableData_.variableCashFlow->get_nominalFixingTime();
    }

    //@}

    /**
    This method should be called by derived classes in order to set
    variableCashFlowPricingEngineDisposableData_.inputKey->nominalFixings_
    */
    void computeNominalFixings(bool extractAtmVol, HLR strikeToExtractVol=HL_NAN) const;


protected:


    /**
    Class variables
    */
    //@{


    //@}


    struct VariableCashFlowPricingEngineDisposableData
    {

        VariableCashFlowPricingEngineDisposableData()
            :
              variableCashFlow(NULL)
        {}

        //@{
        HL_VariableCashFlowPricingEngineInputPtr input;

        HL_VariableCashFlowPricingEngineInputKeyPtr inputKey;

        const HLINS::HL_VariableCashFlow * variableCashFlow;

        HL_VariableCashFlowPricingOutputPtr variableCashFlowPricingOutput;

        HL_VariableCashFlowPricingEngineOutputPtr variableCashFlowPricingEngineOutput;

        ptime nominalFixingTime;

        std::vector<HL_FixingStatePtr> nominalFixings;



        //@}

    }; // end struct VariableCashFlowPricingEngineDisposableData

    mutable VariableCashFlowPricingEngineDisposableData variableCashFlowPricingEngineDisposableData_;


}; // end class HL_VariableCashFlowPricingEngine


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingEngine: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_VariableCashFlowPricingEnginePtr BSP<HLPE::HL_VariableCashFlowPricingEngine>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingEngineInput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141102
\brief
*/
typedef HL_VariableCashFlowPricingEngineInput HL_VanillaCashFlowPricingEngineInput;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingEngineInput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_VanillaCashFlowPricingEngineInputPtr BSP<HLPE::HL_VanillaCashFlowPricingEngineInput>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingEngineInputKey
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141102
\brief
*/
typedef HL_VariableCashFlowPricingEngineInputKey HL_VanillaCashFlowPricingEngineInputKey;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingEngineInputKey:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_VanillaCashFlowPricingEngineInputKeyPtr BSP<HLPE::HL_VanillaCashFlowPricingEngineInputKey>






//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingEngineOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140914
\brief
*/
typedef HL_VariableCashFlowPricingEngineOutput HL_VanillaCashFlowPricingEngineOutput;


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingEngineOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_VanillaCashFlowPricingEngineOutputPtr BSP<HLPE::HL_VanillaCashFlowPricingEngineOutput>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingEngine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141102
\brief Basic pricing engine.
*/
class HL_VanillaCashFlowPricingEngine : public virtual HL_VariableCashFlowPricingEngine
{


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_VanillaCashFlowPricingEngine();

    virtual ~HL_VanillaCashFlowPricingEngine();
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
    void descriptionImpl(std::ostream & os) const;

    void buildInputKey(const HL_MachineInputPtr & input,
                       HL_MachineInputKeyPtr & machineInputKey) const;


    virtual void instantiateCashFlowPricingOutput() const;

    virtual void fillCashFlowPricingOutput() const;

    virtual bool isPayoffDeterministic() const;



    /**
    Here's the core of the computation
    */
    virtual HLR computeCashFlowPayoff() const;

    virtual void instantiateCashFlowPricingEngineOutput() const;

    virtual void cleanDisposableData() const
    {

        vanillaCashFlowPricingEngineDisposableData_=VanillaCashFlowPricingEngineDisposableData();
    }


    //@}

protected:


    /**
    Class variables
    */
    //@{


    //@}


    struct VanillaCashFlowPricingEngineDisposableData
    {
        VanillaCashFlowPricingEngineDisposableData()
            :
              vanillaCashFlow(NULL)
        {}

        //@{
        HL_VanillaCashFlowPricingEngineInputPtr input;

        HL_VanillaCashFlowPricingEngineInputKeyPtr inputKey;

        const HLINS::HL_VanillaCashFlow * vanillaCashFlow;

        HL_VanillaCashFlowPricingOutputPtr vanillaCashFlowPricingOutput;

        HL_VanillaCashFlowPricingEngineOutputPtr vanillaCashFlowPricingEngineOutput;

        //@}

    }; // end struct VanillaCashFlowPricingEngineDisposableData

    mutable VanillaCashFlowPricingEngineDisposableData vanillaCashFlowPricingEngineDisposableData_;


}; // end class HL_VanillaCashFlowPricingEngine


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowPricingEngine: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_VanillaCashFlowPricingEnginePtr BSP<HLPE::HL_VanillaCashFlowPricingEngine>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_AnalyticVanillaCashFlowPricingEngineInput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141109
\brief
*/
typedef HL_VanillaCashFlowPricingEngineInput HL_AnalyticVanillaCashFlowPricingEngineInput;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_AnalyticVanillaCashFlowPricingEngineInput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_AnalyticVanillaCashFlowPricingEngineInputPtr BSP<HLPE::HL_AnalyticVanillaCashFlowPricingEngineInput>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_AnalyticVanillaCashFlowPricingEngineInputKey
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141109
\brief
*/
typedef HL_VanillaCashFlowPricingEngineInputKey HL_AnalyticVanillaCashFlowPricingEngineInputKey;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_AnalyticVanillaCashFlowPricingEngineInputKey:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_AnalyticVanillaCashFlowPricingEngineInputKeyPtr BSP<HLPE::HL_AnalyticVanillaCashFlowPricingEngineInputKey>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_AnalyticVanillaCashFlowPricingEngineOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141109
\brief
*/
typedef HL_VanillaCashFlowPricingEngineOutput HL_AnalyticVanillaCashFlowPricingEngineOutput;


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_AnalyticVanillaCashFlowPricingEngineOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_AnalyticVanillaCashFlowPricingEngineOutputPtr BSP<HLPE::HL_AnalyticVanillaCashFlowPricingEngineOutput>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_AnalyticVanillaCashFlowPricingEngine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141109
\brief Engine to implement Black formulae (normal, shifted log-normal,..) for vanillas (exlucded
fwd start cases, asian cases, multi asset cases).
*/
class HL_AnalyticVanillaCashFlowPricingEngine : public virtual HL_VanillaCashFlowPricingEngine
{


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_AnalyticVanillaCashFlowPricingEngine();

    virtual ~HL_AnalyticVanillaCashFlowPricingEngine();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CashFlowPricingEngineType get_cashFlowPricingEngineType() const
    {
        return HL_CashFlowPricingEngineType_AnalyticVanilla;
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

    void buildInputKey(const HL_MachineInputPtr & input,
                       HL_MachineInputKeyPtr & machineInputKey) const;





    /**
    Here's the core of the computation
    */
    virtual HLR computeCashFlowPayoff() const;

    virtual void instantiateCashFlowPricingEngineOutput() const;





    virtual void cleanDisposableData() const
    {

        vanillaCashFlowPricingEngineDisposableData_=VanillaCashFlowPricingEngineDisposableData();
    }
    //@}

protected:


    /**
    Class variables
    */
    //@{


    //@}


    struct AnalyticVanillaCashFlowPricingEngineDisposableData
    {

        //@{
        HL_AnalyticVanillaCashFlowPricingEngineInputPtr input;

        HL_AnalyticVanillaCashFlowPricingEngineInputKeyPtr inputKey;

        HL_AnalyticVanillaCashFlowPricingEngineOutputPtr analyticVanillaCashFlowPricingEngineOutput;

        //@}

    }; // end struct AnalyticVanillaCashFlowPricingEngineDisposableData

    mutable AnalyticVanillaCashFlowPricingEngineDisposableData analyticVanillaCashFlowPricingEngineDisposableData_;


}; // end class HL_AnalyticVanillaCashFlowPricingEngine


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_AnalyticVanillaCashFlowPricingEngine: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_AnalyticVanillaCashFlowPricingEnginePtr BSP<HLPE::HL_AnalyticVanillaCashFlowPricingEngine>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowPricingEngineInput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141214
\brief
*/
typedef HL_VariableCashFlowPricingEngineInput HL_UnderlyingDeliveryCashFlowPricingEngineInput;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowPricingEngineInput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_UnderlyingDeliveryCashFlowPricingEngineInputPtr BSP<HLPE::HL_UnderlyingDeliveryCashFlowPricingEngineInput>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowPricingEngineInputKey
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141214
\brief
*/
typedef HL_VariableCashFlowPricingEngineInputKey HL_UnderlyingDeliveryCashFlowPricingEngineInputKey;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowPricingEngineInputKey:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_UnderlyingDeliveryCashFlowPricingEngineInputKeyPtr BSP<HLPE::HL_UnderlyingDeliveryCashFlowPricingEngineInputKey>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowPricingEngineOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140914
\brief
*/
typedef HL_VariableCashFlowPricingEngineOutput HL_UnderlyingDeliveryCashFlowPricingEngineOutput;


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowPricingEngineOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_UnderlyingDeliveryCashFlowPricingEngineOutputPtr BSP<HLPE::HL_UnderlyingDeliveryCashFlowPricingEngineOutput>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowPricingEngine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141214
\brief Basic pricing engine.
*/
class HL_UnderlyingDeliveryCashFlowPricingEngine : public virtual HL_VariableCashFlowPricingEngine
{


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_UnderlyingDeliveryCashFlowPricingEngine();

    virtual ~HL_UnderlyingDeliveryCashFlowPricingEngine();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CashFlowPricingEngineType get_cashFlowPricingEngineType() const
    {
        return HL_CashFlowPricingEngineType_UnderlyingDelivery;
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

    void buildInputKey(const HL_MachineInputPtr & input,
                       HL_MachineInputKeyPtr & machineInputKey) const;


    virtual void instantiateCashFlowPricingOutput() const;

    virtual void fillCashFlowPricingOutput() const;

    virtual bool isPayoffDeterministic() const;



    /**
    Here's the core of the computation
    */
    virtual HLR computeCashFlowPayoff() const;

    virtual void instantiateCashFlowPricingEngineOutput() const;

    virtual void cleanDisposableData() const
    {

        underlyingDeliveryCashFlowPricingEngineDisposableData_=UnderlyingDeliveryCashFlowPricingEngineDisposableData();
    }


    //@}

protected:


    /**
    Class variables
    */
    //@{


    //@}


    struct UnderlyingDeliveryCashFlowPricingEngineDisposableData
    {

        UnderlyingDeliveryCashFlowPricingEngineDisposableData()
            :
              underlyingDeliveryCashFlow(NULL)
        {}
        //@{
        HL_UnderlyingDeliveryCashFlowPricingEngineInputPtr input;

        HL_UnderlyingDeliveryCashFlowPricingEngineInputKeyPtr inputKey;

        const HLINS::HL_UnderlyingDeliveryCashFlow * underlyingDeliveryCashFlow;

        HL_UnderlyingDeliveryCashFlowPricingOutputPtr underlyingDeliveryCashFlowPricingOutput;

        HL_UnderlyingDeliveryCashFlowPricingEngineOutputPtr underlyingDeliveryCashFlowPricingEngineOutput;



        //@}

    }; // end struct UnderlyingDeliveryCashFlowPricingEngineDisposableData

    mutable UnderlyingDeliveryCashFlowPricingEngineDisposableData underlyingDeliveryCashFlowPricingEngineDisposableData_;


}; // end class HL_UnderlyingDeliveryCashFlowPricingEngine


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowPricingEngine: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_UnderlyingDeliveryCashFlowPricingEnginePtr BSP<HLPE::HL_UnderlyingDeliveryCashFlowPricingEngine>










} // end namespace HL_PricingEngines
} //end namespace HorizonLib


#endif // _hl_vanillaCashFlowPricingEngine_h_
