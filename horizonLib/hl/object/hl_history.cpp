/**
FILE NAME= hl_history.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131221
*/


#include <hl/object/hl_history.h>



namespace HorizonLib
{
namespace HL_Object
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_DateRealHistory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_DateRealHistory::HL_DateRealHistory()
{
    classDefaultInit();

} // end HL_DateRealHistory

//------------------------------------------------------------------------------------------------------

HL_DateRealHistory::~HL_DateRealHistory()
{} // end ~HL_DateRealHistory

//------------------------------------------------------------------------------------------------------

void HL_DateRealHistory::classDefaultInit()
{
    expectedPositiveFixing_=false;
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------
void HL_DateRealHistory::descriptionImpl(std::ostream & os) const
{
    HL_BaseDateRealHistory::descriptionImpl(os);
    hl_fillDescriptionStream(expectedPositiveFixing_);
} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_DateRealHistory::ensureValidFixing(const HLSTRING & historyTag,
        const TimeType& time) const
{
    if(expectedPositiveFixing_)
        HL_SRE((*fixingPtr_)>0, "expected positive fixing, fixing=" << (*fixingPtr_) << errorString(historyTag, time));

} // end ensureValidFixing


int t()
{

    //HL_DateRealHistory h;

    //date t1;

    //HLR x = h.get_fixing("cciao", t1);

    return 5;
}


} // end namespace HL_Object
} //end namespace HorizonLib
