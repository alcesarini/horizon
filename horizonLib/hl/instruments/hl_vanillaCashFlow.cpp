/**
FILE NAME= hl_vanillaCashFlow.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140523
*/


#include <hl/instruments/hl_vanillaCashFlow.h>



HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_FixedCashFlow);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_FixedCashFlowCode);


HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_VariableCashFlow);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_VariableCashFlowCode);


HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_FixingState);


HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_UnderlyingDeliveryCashFlow);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_UnderlyingDeliveryCashFlowCode);



HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_VanillaCashFlow);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_VanillaCashFlowCode);


namespace HorizonLib
{
namespace HL_Instruments
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlowCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_FixedCashFlowCode::HL_FixedCashFlowCode()
{
    classDefaultInit();

} // end HL_FixedCashFlowCode

//------------------------------------------------------------------------------------------------------

HL_FixedCashFlowCode::~HL_FixedCashFlowCode()
{
} // end ~HL_FixedCashFlowCode

//------------------------------------------------------------------------------------------------------

void HL_FixedCashFlowCode::classDefaultInit()
{

} // end classDefaultInit
//------------------------------------------------------------------------------------------------------

HLSTRING HL_FixedCashFlowCode::objTypeImpl() const
{
    return "HL_FixedCashFlowCode";
} // end objTypeImpl





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedCashFlow
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_FixedCashFlow::HL_FixedCashFlow()
{

    classDefaultInit();



} // end HL_FixedCashFlow

//------------------------------------------------------------------------------------------------------

HL_FixedCashFlow::~HL_FixedCashFlow()
{
} // end ~HL_FixedCashFlow


//------------------------------------------------------------------------------------------------------

void HL_FixedCashFlow::classDefaultInit()
{
    fixedRate_=0.;

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_FixedCashFlow::descriptionImpl(std::ostream & os) const
{


    HL_CashFlow::descriptionImpl(os);

    hl_fillDescriptionStream(fixedRate_);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_VariableCashFlowCode::HL_VariableCashFlowCode()
{
    classDefaultInit();

} // end HL_VariableCashFlowCode

//------------------------------------------------------------------------------------------------------

HL_VariableCashFlowCode::~HL_VariableCashFlowCode()
{
} // end ~HL_VariableCashFlowCode

//------------------------------------------------------------------------------------------------------

void HL_VariableCashFlowCode::classDefaultInit()
{

} // end classDefaultInit
//------------------------------------------------------------------------------------------------------

HLSTRING HL_VariableCashFlowCode::objTypeImpl() const
{
    return "HL_VariableCashFlowCode";
} // end objTypeImpl





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlow
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_VariableCashFlow::HL_VariableCashFlow()
{

    classDefaultInit();



} // end HL_VariableCashFlow

//------------------------------------------------------------------------------------------------------

HL_VariableCashFlow::~HL_VariableCashFlow()
{
} // end ~HL_VariableCashFlow


//------------------------------------------------------------------------------------------------------

void HL_VariableCashFlow::classDefaultInit()
{


} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_VariableCashFlow::descriptionImpl(std::ostream & os) const
{


    HL_CashFlow::descriptionImpl(os);
    hl_fillDescriptionStream(basketPtr_);
    hl_fillDescriptionStream(nominalFixingTime_);
    hl_fillDescriptionStream(basketComposition_);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_VariableCashFlow::checkCashFlow() const
{

    HL_CashFlow::checkCashFlow();

    HL_PNN(basketPtr_);
    HL_SR(nominalFixingTime_!=ptime());

    HL_PNN(basketComposition_);


    HL_SR(basketComposition_->get_nbComponents()==basketPtr_->nbComponents());



} // end checkCashFlow



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixingState
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_FixingState::HL_FixingState()
{

    classDefaultInit();



} // end HL_FixingState

//------------------------------------------------------------------------------------------------------

HL_FixingState::~HL_FixingState()
{
} // end ~HL_FixingState


//------------------------------------------------------------------------------------------------------

void HL_FixingState::classDefaultInit()
{

    fwdValue_ = HL_NAN;

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_FixingState::descriptionImpl(std::ostream & os) const
{

    os << "HL_FixingState:\n";

    Descriptable::descriptionImpl(os);

    hl_fillDescriptionStream(fixingTime_);
    hl_fillDescriptionStream(fwdValue_);
    hl_fillDescriptionStream(fixingDescription_);
    hl_fillDescriptionStream(volState_);


} // end descriptionImpl



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_VariableCashFlowPricingOutput::HL_VariableCashFlowPricingOutput()
{
    classDefaultInit();

} // end HL_CashFlowPricingOutput

//------------------------------------------------------------------------------------------------------

HL_VariableCashFlowPricingOutput::~HL_VariableCashFlowPricingOutput()
{
} // end ~HL_VariableCashFlowPricingOutput

//------------------------------------------------------------------------------------------------------

void HL_VariableCashFlowPricingOutput::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_VariableCashFlowPricingOutput::descriptionImpl(std::ostream & os) const
{


    os << "HL_VariableCashFlowPricingOutput:\n";

    HL_CashFlowPricingOutput::descriptionImpl(os);

    hl_fillDescriptionStream(nominalFixings_);


} // end descriptionImpl



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableCashFlowPricingOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlowCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_UnderlyingDeliveryCashFlowCode::HL_UnderlyingDeliveryCashFlowCode()
{
    classDefaultInit();

} // end HL_UnderlyingDeliveryCashFlowCode

//------------------------------------------------------------------------------------------------------

HL_UnderlyingDeliveryCashFlowCode::~HL_UnderlyingDeliveryCashFlowCode()
{
} // end ~HL_UnderlyingDeliveryCashFlowCode

//------------------------------------------------------------------------------------------------------

void HL_UnderlyingDeliveryCashFlowCode::classDefaultInit()
{

} // end classDefaultInit
//------------------------------------------------------------------------------------------------------

HLSTRING HL_UnderlyingDeliveryCashFlowCode::objTypeImpl() const
{
    return "HL_UnderlyingDeliveryCashFlowCode";
} // end objTypeImpl





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryCashFlow
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_UnderlyingDeliveryCashFlow::HL_UnderlyingDeliveryCashFlow()
{

    classDefaultInit();



} // end HL_UnderlyingDeliveryCashFlow

//------------------------------------------------------------------------------------------------------

HL_UnderlyingDeliveryCashFlow::~HL_UnderlyingDeliveryCashFlow()
{
} // end ~HL_UnderlyingDeliveryCashFlow


//------------------------------------------------------------------------------------------------------

void HL_UnderlyingDeliveryCashFlow::classDefaultInit()
{


} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_UnderlyingDeliveryCashFlow::descriptionImpl(std::ostream & os) const
{


    HL_VariableCashFlow::descriptionImpl(os);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_UnderlyingDeliveryCashFlow::checkCashFlow() const
{

    HL_VariableCashFlow::checkCashFlow();



} // end checkCashFlow



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlowCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_VanillaCashFlowCode::HL_VanillaCashFlowCode()
{
    classDefaultInit();

} // end HL_VanillaCashFlowCode

//------------------------------------------------------------------------------------------------------

HL_VanillaCashFlowCode::~HL_VanillaCashFlowCode()
{
} // end ~HL_VanillaCashFlowCode

//------------------------------------------------------------------------------------------------------

void HL_VanillaCashFlowCode::classDefaultInit()
{



} // end classDefaultInit
//------------------------------------------------------------------------------------------------------

HLSTRING HL_VanillaCashFlowCode::objTypeImpl() const
{
    return "HL_VanillaCashFlowCode";
} // end objTypeImpl





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VanillaCashFlow
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_VanillaCashFlow::HL_VanillaCashFlow()
{

    classDefaultInit();



} // end HL_VanillaCashFlow

//------------------------------------------------------------------------------------------------------

HL_VanillaCashFlow::~HL_VanillaCashFlow()
{
} // end ~HL_VanillaCashFlow


//------------------------------------------------------------------------------------------------------

void HL_VanillaCashFlow::classDefaultInit()
{

    strike_=HL_NAN;

    vanillaType_=HL_VanillaType_InvalidMin;

    isDigital_=false;

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_VanillaCashFlow::descriptionImpl(std::ostream & os) const
{


    HL_VariableCashFlow::descriptionImpl(os);

    hl_fillDescriptionStream(strike_);
    HL_DESCRIBE_ENUM(os, vanillaType_);
    hl_fillDescriptionStream(isDigital_);



} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_VanillaCashFlow::checkCashFlow() const
{

    HL_VariableCashFlow::checkCashFlow();


    HL_ENUM_CHECK(HL_VanillaType, vanillaType_);


} // end checkCashFlow




} // end namespace HL_Instruments
} //end namespace HorizonLib
