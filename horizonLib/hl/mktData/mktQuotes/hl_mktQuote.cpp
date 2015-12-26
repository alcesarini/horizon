/**
FILE NAME= hl_mktQuote.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140607
*/

#include <hl/mktData/mktQuotes/hl_mktQuote.h>


HL_SERIALIZATION_CLASS_EXPORT_GUID(HLMQS::HL_MktQuote);

namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_MktQuotes
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktQuote
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_MktQuote::HL_MktQuote()
{

    classDefaultInit();



} // end HL_MktQuote

//------------------------------------------------------------------------------------------------------

HL_MktQuote::~HL_MktQuote()
{} // end ~HL_MktQuote


//------------------------------------------------------------------------------------------------------

void HL_MktQuote::classDefaultInit()
{
    value_=HL_NULL_REAL;

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_MktQuote::descriptionImpl(std::ostream & os) const
{
    os << "HL_MktQuote=" << mktQuoteType() << ":\n";

    Descriptable::descriptionImpl(os);

    hl_fillDescriptionStream(value_);
    hl_fillDescriptionStream(quotationTime_);
    hl_fillDescriptionStream(anagraphicsPtr_);



} // end descriptionImpl

//------------------------------------------------------------------------------------------------------


void HL_MktQuote::checkMktQuote() const
{


    HL_SR(value_!=HL_NULL_REAL);

    HL_SR(quotationTime_!=ptime());
    HL_PNN(anagraphicsPtr_);

    anagraphicsPtr_->checkAnagraphics();

}

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktQuote: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------





} // end namespace HL_MktQuotes
} // end namespace HL_MarketData
} //end namespace HorizonLib
