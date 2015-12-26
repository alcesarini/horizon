/**
FILE NAME= hl_pricingEngineFactory.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20150512
*/
#ifndef _hl_pricingEngineFactory_h_
#define _hl_pricingEngineFactory_h_


#include <hl/pricingEngines/hl_pricingEngine.h>
#include <hl/pricingEngines/hl_cashFlowPricingEngine.h>


namespace HorizonLib
{
namespace HL_PricingEngines
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineChoices
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20150528
\brief Class to be used in order to decide, for a particular pricing task, which HL_CashFlowPricingEngineType
is to be associated to which HL_CashFlowType.
In this class one value of HL_CashFlowPricingEngineType must be present at most once.

*/
class HL_PricingEngineChoices : public virtual HLSER::HL_Serializable, public virtual Descriptable
{

    typedef std::map<HLINS::HL_CashFlowType, HL_CashFlowPricingEngineType>  MapType;
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
        HL_SER(associations_);

    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_PricingEngineChoices();

    virtual ~HL_PricingEngineChoices();
    //@}


    /**
    Public class interface
    */
    //@{


    void setAssociation(HLINS::HL_CashFlowType cashFlowType,
                        HL_CashFlowPricingEngineType cashFlowPricingEngineType);

    HL_CashFlowPricingEngineType get_cashFlowPricingEngineType(HLINS::HL_CashFlowType cashFlowType) const;



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
    */

    /**
    associations_[x] = y
    means that HL_CashFlow of type x must be priced with HL_CashFlowPricingEngine of type y.
    */
    MapType associations_;
    //@}

}
; // end class HL_PricingEngineChoices


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineChoices: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_PricingEngineChoicesPtr BSP<HLPE::HL_PricingEngineChoices>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineData
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20150528
\brief Just a struct to conveniently collect pricinng engine data at an external interface level.

*/
class HL_PricingEngineData : public virtual HLSER::HL_Serializable, public virtual Descriptable
{

    typedef std::map<HLINS::HL_CashFlowType, HL_CashFlowPricingEngineType>  MapType;
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
        HL_SER(mktDataCollector_);
        HL_SER(riskFreeDiscounting_);
        HL_SER(pricingEngineChoices_);
    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_PricingEngineData();

    virtual ~HL_PricingEngineData();
    //@}


    /**
    Public class interface
    */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS(HL_MktDataCollectorPtr, mktDataCollector);
    HL_CLASS_VAR_ACCESS_METHODS(HL_RiskFreeDiscountingPtr, riskFreeDiscounting);
    HL_CLASS_VAR_ACCESS_METHODS(HL_PricingEngineChoicesPtr, pricingEngineChoices);



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
    */

    HL_MktDataCollectorPtr mktDataCollector_;
    HL_RiskFreeDiscountingPtr riskFreeDiscounting_;
    HL_PricingEngineChoicesPtr pricingEngineChoices_;
    //@}

}
; // end class HL_PricingEngineData


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_PricingEngineData: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_PricingEngineDataPtr BSP<HLPE::HL_PricingEngineData>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineFactory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20150528
\brief Just a struct to conveniently collect pricinng engine data at an external interface level.

*/
class HL_CashFlowPricingEngineFactory : public virtual HLSER::HL_Serializable, public virtual Descriptable
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
        HL_SER(pricingEngineData_);
    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_CashFlowPricingEngineFactory();

    virtual ~HL_CashFlowPricingEngineFactory();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(HL_PricingEngineDataPtr, pricingEngineData);



    HL_CashFlowPricingEnginePtr get_cashFlowPricingEngine(const HL_CashFlowPtr & cashFlow);


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


    HL_CashFlowPricingEngineInputPtr get_cashFlowPricingEngineInput(const HL_CashFlowPtr & cashFlow) const;

    HL_CashFlowPricingEnginePtr instantiate_cashFlowPricingEngine(HL_CashFlowPricingEngineType cashFlowPricingEngineType) const;

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
    */

    HL_PricingEngineDataPtr pricingEngineData_;
    //@}

}
; // end class HL_CashFlowPricingEngineFactory


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CashFlowPricingEngineFactory: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_CashFlowPricingEngineFactoryPtr BSP<HLPE::HL_CashFlowPricingEngineFactory>






//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// setPricingEngineIntoIns
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20150512
\brief Utility to instantiate a (suitable) pricing engine and to set it into the given instrument.
Notice that the pricing engine it is instantiated is the one of the mkt models (for ex. a black pricing
engine based on implied vol for a plain vanilla, etc..)
The nature of the instrument is not specified in this function.
*/
void setPricingEngineIntoIns(const HL_InstrumentPtr & instrument,
                             const HL_PricingEngineDataPtr & pricingEngineData
                             );

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// setPricingEngineIntoCashFlow
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20150512
\brief Utility to instantiate a (suitable) pricing engine and to set it into the given HL_CashFlow.
Notice that the pricing engine it is instantiated is the one of the mkt models (for ex. a black pricing
engine based on implied vol for a plain vanilla, etc..)
The input instrument is HL_CashFlow.
*/
void setPricingEngineIntoCashFlow(const HL_CashFlowPtr & cashFlow,
                                  const HL_PricingEngineDataPtr & pricingEngineData);





} // end namespace HL_PricingEngines
} //end namespace HorizonLib


#endif // _hl_pricingEngineFactory_h_
