/**
FILE NAME= hl_basket.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140523
*/


#include <hl/instruments/hl_basket.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_Basket);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINS::HL_BasketCode);

namespace HorizonLib
{
namespace HL_Instruments
{





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_BasketCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_BasketCode::HL_BasketCode()
{
    classDefaultInit();

} // end HL_BasketCode

//------------------------------------------------------------------------------------------------------

HL_BasketCode::~HL_BasketCode()
{
} // end ~HL_BasketCode

//------------------------------------------------------------------------------------------------------

void HL_BasketCode::classDefaultInit()
{

} // end classDefaultInit
//------------------------------------------------------------------------------------------------------

HLSTRING HL_BasketCode::objTypeImpl() const
{
    return "HL_BasketCode";
} // end objTypeImpl




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Basket
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_Basket::HL_Basket()
{

    classDefaultInit();



} // end HL_Basket

//------------------------------------------------------------------------------------------------------

HL_Basket::~HL_Basket()
{
} // end ~HL_Basket


//------------------------------------------------------------------------------------------------------

void HL_Basket::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_Basket::descriptionImpl(std::ostream & os) const
{
    HLOBJ::HL_FinObj::descriptionImpl(os);

    hl_fillDescriptionStream(basketCodePtr_);
    hl_fillDescriptionStream(underlyingCodes_);
    hl_fillDescriptionStream(underlyingHistoryTags_);


} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

HL_Order HL_Basket::getOrder(const HL_Basket & hl_Basket) const
{


    HL_Order basketCodePtrOrder= plainOrder(basketCodePtr_, hl_Basket.basketCodePtr_);


    return basketCodePtrOrder;



} // end getOrder

//------------------------------------------------------------------------------------------------------

void HL_Basket::checkBasket() const
{

    HL_PNN(basketCodePtr_);
    HL_SR(underlyingCodes_.size());
    HL_SR(underlyingCodes_.size()==underlyingHistoryTags_.size());



} // end checkBasket



} // end namespace HL_Instruments
} //end namespace HorizonLib
