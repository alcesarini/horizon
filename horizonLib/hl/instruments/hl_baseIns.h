/**
FILE NAME= hl_baseIns.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131109
*/
#ifndef _hl_baseIns_h_
#define _hl_baseIns_h_


#include <hl/object/hl_machine.h>



namespace HorizonLib
{
namespace HL_PricingEngines
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngine (fwd declaration)
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20150518
\brief Basic pricing engine.
*/


class HL_PricingEngine;

//------------------------------------------------------------------------------------------------------

#define HL_PricingEnginePtr BSP<HLPE::HL_PricingEngine>

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineOutput (fwd declaration)
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

class HL_PricingEngineOutput;

//------------------------------------------------------------------------------------------------------

#define HL_PricingEngineOutputPtr BSP<HLPE::HL_PricingEngineOutput>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineInput (fwd declaration)
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

class HL_PricingEngineInput;

//------------------------------------------------------------------------------------------------------

#define HL_PricingEngineInputPtr BSP<HLPE::HL_PricingEngineInput>


} // end namespace HL_PricingEngines
} //end namespace HorizonLib


namespace HorizonLib
{
namespace HL_Instruments
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingOutput (fwd declaration)
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

class HL_CashFlowPricingOutput;

//------------------------------------------------------------------------------------------------------


#define HL_CashFlowPricingOutputPtr BSP<HLINS::HL_CashFlowPricingOutput>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InstrumentOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140914
\brief
*/
class HL_InstrumentOutput : public virtual HLOBJ::HL_MachineOutput
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


    }
    //@} Serialization -----------------------------------

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_InstrumentOutput();

    virtual ~HL_InstrumentOutput();
    //@}


    /**
    Public class interface
    */
    //@{

    virtual HLR get_dirtyPrice() const;

    virtual HLR get_accrued(const date& d) const;


    virtual HLS get_nbCashFlowPricingOutputs() const=0;

    virtual const HL_CashFlowPricingOutput & get_CashFlowPricingOutput(HLS cashFlowPricingOutputIdx) const=0;



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
; // end class HL_InstrumentOutput

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InstrumentOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_InstrumentOutputPtr BSP<HLINS::HL_InstrumentOutput>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InstrumentCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131210
\brief The ins code
*/

class HL_InstrumentCode : public virtual HLOBJ::HL_FinObjCode
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

        HL_SERIALIZE_BASE_CLASS(HLOBJ::HL_FinObjCode);

    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_InstrumentCode();

    virtual ~HL_InstrumentCode();
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
; // end class HL_InstrumentCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InstrumentCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_InstrumentCodePtr BSP<HLINS::HL_InstrumentCode>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlow (fwd declaration)
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
A HL_CashFlow is an instrument with the restriction of the single payment. A is basically a collection of HL_CashFlow.
*/
class HL_CashFlow;


//------------------------------------------------------------------------------------------------------


#define HL_CashFlowPtr BSP<HLINS::HL_CashFlow>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Instrument
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131110
\brief Basic financial instrument.
*/
class HL_Instrument : public virtual HLOBJ::HL_FinObj
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

        HL_SERIALIZE_BASE_CLASS(HLOBJ::HL_FinObj);

        HL_SER(instrumentCode_);

    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_Instrument();

    virtual ~HL_Instrument();
    //@}


    /**
    Public class interface
    */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS_O(HL_InstrumentCodePtr, instrumentCode);


    virtual HLS get_nbCashFlows() const=0;

    virtual const HL_CashFlow & get_cashFlow(HLS cashFlowIdx) const=0;


    void set_HL_ObjCodePtr(const HL_ObjCodePtr & hl_ObjCodePtr);


    virtual HL_InstrumentOutputPtr get_instrumentOutput() const=0;


    /**
    Short cut to get just the dirty price.
    */
    HLR get_dirtyPrice() const
    {
        return get_instrumentOutput()->get_dirtyPrice();
    }


    /**
    In case the class stores/precache any computation data, this method
    should totally discard it.
    Notice that if the class has an HL_Machine attached in order to deal with its
    computations, then this method should trigger the discard of all the
    computation data of the HL_Machine.
    */
    virtual void purgeAllComputations() const{}


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
    Not to be serialized, since it corresponds to HL_Obj::hl_ObjCodePtr_
    */
    HL_InstrumentCodePtr instrumentCode_;


    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_Instrument


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Instrument: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_InstrumentPtr BSP<HLINS::HL_Instrument>






//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowCollectionInstrument
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140921
\brief Collection of HL_CashFlow classes.

This class shouldn't be derived any more. It is designed to host any instrument as a sum of
HL_CashFlow, i.e. as a sum of instrument with only one payout.
*/
class HL_CashFlowCollectionInstrument : public virtual HL_Instrument
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

        HL_SERIALIZE_BASE_CLASS(HL_Instrument);


        HL_SER(cashFlows_);


    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_CashFlowCollectionInstrument();

    virtual ~HL_CashFlowCollectionInstrument();
    //@}


    /**
    Public implementations of base class methods
    */
    //@{

    HLS get_nbCashFlows() const
    {

        return cashFlows_.size();
    }

    const HL_CashFlow & get_cashFlow(HLS cashFlowIdx) const
    {
        HL_SR(cashFlowIdx<cashFlows_.size());
        return *cashFlows_[cashFlowIdx];
    }



    HL_InstrumentOutputPtr get_instrumentOutput() const;


    void purgeAllComputations() const;

    //@}


    /**
    Public class interface
    */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS_O(std::vector<HL_CashFlowPtr>/*ClassVariableType*/, cashFlows/*classVariableName_no_underscore*/);

    void set_cashFlows(const std::vector<HL_CashFlowPtr> & cashFlows);

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
    An instrument is basically a set of cashflows.
    They're kept sorted with their own ordering.
    */
    std::vector<HL_CashFlowPtr> cashFlows_;
    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_CashFlowCollectionInstrument


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowCollectionInstrument: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_CashFlowCollectionInstrumentPtr BSP<HLINS::HL_CashFlowCollectionInstrument>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowCollectionInstrumentOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140921
\brief Collection of HL_InstrumentOutput classes.

This class shouldn't be derived any more. It is designed to host any HL_InstrumentOutput as a sum of
HL_CashFlowPricingOutput, i.e. as a sum of HL_InstrumentOutput with only one payout.
*/
class HL_CashFlowCollectionInstrumentOutput : public virtual HL_InstrumentOutput
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
        HL_SERIALIZE_BASE_CLASS(HL_InstrumentOutput);

        HL_SER(cashFlowPricingOutputs_);

    }
    //@} Serialization -----------------------------------

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_CashFlowCollectionInstrumentOutput();

    virtual ~HL_CashFlowCollectionInstrumentOutput();
    //@}


    /**
    Public implementations of base class methods
    */
    //@{

    HLS get_nbCashFlowPricingOutputs() const
    {
        return cashFlowPricingOutputs_.size();

    }

    const HL_CashFlowPricingOutput & get_CashFlowPricingOutput(HLS cashFlowPricingOutputIdx) const
    {
        HL_SR(cashFlowPricingOutputIdx<cashFlowPricingOutputs_.size());
        return *cashFlowPricingOutputs_[cashFlowPricingOutputIdx];

    }

    HL_CLASS_VAR_ACCESS_METHODS_I(std::vector<HL_CashFlowPricingOutputPtr>, cashFlowPricingOutputs);


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


    std::vector<HL_CashFlowPricingOutputPtr> cashFlowPricingOutputs_;

    //@}

}
; // end class HL_CashFlowCollectionInstrumentOutput

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowCollectionInstrumentOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_CashFlowCollectionInstrumentOutputPtr BSP<HLINS::HL_CashFlowCollectionInstrumentOutput>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_EnginedInstrument
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20151014
\brief Basic financial instrument to be price using a pricing engine.
*/
class HL_EnginedInstrument : public virtual HL_Instrument
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

        HL_SERIALIZE_BASE_CLASS(HL_Instrument);


    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_EnginedInstrument();

    virtual ~HL_EnginedInstrument();
    //@}


    /**
    Public class interface
    */
    //@{



    HL_CLASS_VAR_ACCESS_METHODS(HL_PricingEnginePtr, pricingEngine);




    HL_InstrumentOutputPtr get_instrumentOutput() const;

    /**
    Remind that when calling this method, the input of the pricing engine pricingEngine_
    that is supposed to accomplish the task of computing the instrument price and results
    has already been set, including the instrument itself that is set
    into the engine's input as a c-pointer link.
    Notice that the engine's input could vary during time (the input is in the engine but
    this does not mean it is fixed..), and similarly also the instrument anagraphics
    could (at least in principle) vary.
    Notice that nevertheless this, the engine is a HL_Machine, so it is "lazy".
    */
    HL_PricingEngineOutputPtr get_pricingEngineOutput() const;



    void purgeAllComputations() const;

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
    To get the price (not serialized).
    It's useful to have the pricing engine attached to the instrument.
    Notice that the pricing engine owns the instrument by mean of a weak ptr and so
    no shared_ptr auto-containing loop issue is present.
    */
    HL_PricingEnginePtr pricingEngine_;
    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_EnginedInstrument


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_EnginedInstrument: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_EnginedInstrumentPtr BSP<HLINS::HL_EnginedInstrument>





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Utility Methods
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// mergeInstruments
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



HL_InstrumentPtr mergeInstruments(const std::vector<HL_InstrumentPtr> & instruments);


} // end namespace HL_Instruments
} //end namespace HorizonLib


#endif // _hl_baseIns_h_
