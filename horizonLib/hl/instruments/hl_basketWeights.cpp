/**
FILE NAME= hl_basketComposition.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140523
*/


#include <hl/instruments/hl_basketWeights.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_BasketComposition);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_FwdStartBasketComposition);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_QuantBasketComposition);

namespace HorizonLib
{
namespace HL_Instruments
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_BasketRuleType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_BasketComposition
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_BasketComposition::HL_BasketComposition()
{

    classDefaultInit();



} // end HL_BasketComposition

//------------------------------------------------------------------------------------------------------

HL_BasketComposition::~HL_BasketComposition()
{
} // end ~HL_BasketComposition


//------------------------------------------------------------------------------------------------------

void HL_BasketComposition::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_BasketComposition::descriptionImpl(std::ostream & os) const
{

    os << "HL_BasketComposition:\n";

    Descriptable::descriptionImpl(os);

    hl_fillDescriptionStream(nbComponents_);
    hl_fillDescriptionStream(issueTime_);
    HL_DESCRIBE_ENUM(os, basketRuleType_);
    HL_DESCRIBE_ENUM(os, get_basketCompositionType());


} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

void HL_BasketComposition::checkBasketComposition() const
{


    HL_SR(nbComponents_);

    HL_SR(issueTime_!=ptime());


    HL_ENUM_CHECK(HL_BasketRuleType, basketRuleType_);




} // end checkBasketComposition



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FwdStartBasketComposition
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_FwdStartBasketComposition::HL_FwdStartBasketComposition()
{

    classDefaultInit();



} // end HL_FwdStartBasketComposition

//------------------------------------------------------------------------------------------------------

HL_FwdStartBasketComposition::~HL_FwdStartBasketComposition()
{
} // end ~HL_FwdStartBasketComposition


//------------------------------------------------------------------------------------------------------

void HL_FwdStartBasketComposition::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_FwdStartBasketComposition::descriptionImpl(std::ostream & os) const
{

    os << "HL_FwdStartBasketComposition:\n";

    HL_BasketComposition::descriptionImpl(os);

    hl_fillDescriptionStream(issueTimeWeights_);

} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_FwdStartBasketComposition::set_issueTimeWeights(const VEC & issueTimeWeights)
{

    issueTimeWeights_=issueTimeWeights;

    nbComponents_=issueTimeWeights_.size();

} // end set_issueTimeWeights

//------------------------------------------------------------------------------------------------------

void HL_FwdStartBasketComposition::checkBasketComposition() const
{

    HL_BasketComposition::checkBasketComposition();


    HLR sumWeights = std::accumulate(issueTimeWeights_.begin(), issueTimeWeights_.end(), 0.);

    HL_REQ_EQUAL_FLOATS(sumWeights, 1);




} // end checkBasketComposition




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_QuantBasketComposition
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_QuantBasketComposition::HL_QuantBasketComposition()
{

    classDefaultInit();



} // end HL_QuantBasketComposition

//------------------------------------------------------------------------------------------------------

HL_QuantBasketComposition::~HL_QuantBasketComposition()
{
} // end ~HL_QuantBasketComposition


//------------------------------------------------------------------------------------------------------

void HL_QuantBasketComposition::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_QuantBasketComposition::descriptionImpl(std::ostream & os) const
{

    os << "HL_QuantBasketComposition:\n";

    HL_BasketComposition::descriptionImpl(os);

    hl_fillDescriptionStream(issueTimeQuantities_);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_QuantBasketComposition::set_issueTimeQuantities(const VEC & issueTimeQuantities)
{

    issueTimeQuantities_=issueTimeQuantities;

    nbComponents_=issueTimeQuantities_.size();

} // end set_issueTimeQuantities

//------------------------------------------------------------------------------------------------------

void HL_QuantBasketComposition::checkBasketComposition() const
{

    HL_BasketComposition::checkBasketComposition();



} // end checkBasketComposition





} // end namespace HL_Instruments
} //end namespace HorizonLib
