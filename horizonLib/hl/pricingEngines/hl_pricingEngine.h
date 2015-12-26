/**
FILE NAME= hl_pricingEngine.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140902
*/
#ifndef _hl_pricingEngine_h_
#define _hl_pricingEngine_h_


#include <hl/object/hl_machine.h>
#include <hl/mktData/hl_mktDataCollector.h>
#include <hl/instruments/hl_baseIns.h>
#include <hl/math/probMeasures/hl_probMeasure.h>

namespace HorizonLib
{
namespace HL_PricingEngines
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineInput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140902
\brief The input to be given to a HL_PricingEngine.

Actually, there's no a particular need to serialize it, but nonetheless it could be.
*/
class HL_PricingEngineInput : public virtual HLOBJ::HL_MachineInput
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
        HL_SERIALIZE_BASE_CLASS(HLOBJ::HL_MachineInput);
        HL_SER(mktDataCollector_);
        HL_SER(riskFreeDiscounting_);

    }
    //@} Serialization -----------------------------------

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_PricingEngineInput();

    virtual ~HL_PricingEngineInput();
    //@}


    /**
    Public class interface
    */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS(HL_MktDataCollectorPtr, mktDataCollector);


    void set_instrumentPtr(const HLINS::HL_Instrument * instrumentPtr)
    {
        instrumentPtr_=instrumentPtr;
    }

    const HLINS::HL_Instrument * get_instrumentPtr() const
    {
        HL_PNN(instrumentPtr_);

        return instrumentPtr_;
    }

    HL_CLASS_VAR_ACCESS_METHODS(HL_RiskFreeDiscountingPtr, riskFreeDiscounting);


    virtual void check() const;

    const HL_TermStructureCodePtr & get_riskFreeDiscountingTermStructureCode() const
    {

        return riskFreeDiscounting_->get_riskFreeDiscountingTermStructureCode();
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

private:

    /**
    Private class variables
    */
    //@{

    HL_MktDataCollectorPtr mktDataCollector_;

    /**
    What to price (not to be serialized)
    */
    const HLINS::HL_Instrument* instrumentPtr_;

    /**
    How to discount. The ccy of  riskFreeDiscounting_->get_ccyCode() must coincide
    with the ccy of instrument_. This is checked in method checkPricingEngineInput().
    */
    HL_RiskFreeDiscountingPtr riskFreeDiscounting_;

    //@}

}
; // end class HL_PricingEngineInput

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineInput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------






//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineInputKey
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140927
\brief  See comment to HL_Machine.
*/
class HL_PricingEngineInputKey : public virtual HLOBJ::HL_MachineInputKey
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
        HL_SERIALIZE_BASE_CLASS(HLOBJ::HL_MachineInputKey);
        HL_SER(refDate_);
        HL_SER(instrumentCode_);
        HL_SER(riskFreeDiscounting_);



    }
    //@} Serialization -----------------------------------

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_PricingEngineInputKey();

    virtual ~HL_PricingEngineInputKey();
    //@}


    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(date, refDate);
    HL_CLASS_VAR_ACCESS_METHODS(HL_InstrumentCodePtr, instrumentCode);
    HL_CLASS_VAR_ACCESS_METHODS(HL_RiskFreeDiscountingPtr, riskFreeDiscounting);


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
    If the refDate (i.e. the computation date) changes the Input is considred to have changed (notice
    that we do not use refTime, but refDate, since if the time changes it is not sure that the input
    is to be considred changed too).

    Notice that refDate is the refDate of the MktDataCollector with which the computation has been accomplished.
    */
    date refDate_;

    HL_InstrumentCodePtr instrumentCode_;
    HL_RiskFreeDiscountingPtr riskFreeDiscounting_;

    //@}

}
; // end class HL_PricingEngineInputKey

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineInputKey:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_PricingEngineInputKeyPtr BSP<HLPE::HL_PricingEngineInputKey>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140914
\brief
*/
class HL_PricingEngineOutput : public virtual HLOBJ::HL_MachineOutput
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
        HL_SERIALIZE_BASE_CLASS(HLOBJ::HL_MachineOutput);
        HL_SER(refTime_);
        HL_SER(instrumentOutput_);

    }
    //@} Serialization -----------------------------------

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_PricingEngineOutput();

    virtual ~HL_PricingEngineOutput();
    //@}


    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(ptime, refTime);

    HL_CLASS_VAR_ACCESS_METHODS(HL_InstrumentOutputPtr, instrumentOutput);


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
    refTime_ is the refTime_ of the MktDataCollector with which the computation has been accomplished.
    */
    ptime refTime_;

    HL_InstrumentOutputPtr instrumentOutput_;



    //@}

}
; // end class HL_PricingEngineOutput

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------








//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140902
\brief Basic pricing engine.
*/
class HL_PricingEngine : public virtual HLOBJ::HL_Machine
{


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_PricingEngine();

    virtual ~HL_PricingEngine();
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



    virtual HL_PricingEngineOutputPtr performEngineComputations() const=0;


    HL_MachineOutputPtr doJobImpl() const;


    virtual void cleanDisposableData() const
    {

        pricingEngineDisposableData_=PricingEngineDisposableData();
    }



    date get_refDate() const
    {

        return pricingEngineDisposableData_.input->get_mktDataCollector()->get_refDate();
    }

    const ptime& get_refTime() const
    {

        return pricingEngineDisposableData_.input->get_mktDataCollector()->get_refTime();
    }


    //@}

protected:


    /**
    Class variables
    */
    //@{


    //@}

    struct PricingEngineDisposableData
    {

        //@{
        HL_PricingEngineInputPtr input;

        HL_PricingEngineInputKeyPtr inputKey;
        //@}

    }; // end struct PricingEngineDisposableData

    mutable PricingEngineDisposableData pricingEngineDisposableData_;


}
; // end class HL_PricingEngine


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngine: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




} // end namespace HL_PricingEngines
} //end namespace HorizonLib


#endif // _hl_pricingEngine_h_
