/**
FILE NAME= hl_history.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131221
*/


#include <hl/object/hl_history.h>
#include <hl/dateTime/calendar/hl_calendar.h>


HL_SERIALIZATION_CLASS_EXPORT_GUID(HLOBJ::HL_TimeRealHistory);

namespace HorizonLib
{
namespace HL_Object
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TimeRealHistory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_TimeRealHistory::HL_TimeRealHistory()
{
    classDefaultInit();

} // end HL_TimeRealHistory

//------------------------------------------------------------------------------------------------------

HL_TimeRealHistory::~HL_TimeRealHistory()
{} // end ~HL_TimeRealHistory

//------------------------------------------------------------------------------------------------------

void HL_TimeRealHistory::classDefaultInit()
{
    expectedPositiveFixing_=false;
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------
void HL_TimeRealHistory::descriptionImpl(std::ostream & os) const
{
    HL_BaseTimeRealHistory::descriptionImpl(os);
    hl_fillDescriptionStream(expectedPositiveFixing_);
} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_TimeRealHistory::ensureValidFixing(const HLSTRING & historyTag, const TimeType& time) const
{
    if(expectedPositiveFixing_)
        HL_SRE((*fixingPtr_)>0, "expected positive fixing, fixing=" << (*fixingPtr_) << errorString(historyTag, time));

} // end ensureValidFixing



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HLTEST_get_HL_TimeRealHistory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_TimeRealHistoryPtr HLTEST_get_HL_TimeRealHistory(const HL_ObjCodePtr & objCode,
                                                    const date & refDate,
                                                    const HLSTRING & historyTag,
                                                    const std::vector<HLR> & fixingValues)
{
    HL_TimeRealHistoryPtr dateRealHistory(new HLOBJ::HL_TimeRealHistory);


    dateRealHistory->set_hl_ObjCodePtr(objCode);


    dateRealHistory->set_expectedPositiveFixing(true);


    dateRealHistory->set_refTime(ptime(refDate));


    HL_CalendarPtr iborFakeCalendar(new HLCAL::HL_FakeCalendar);

    date d = refDate;

    BOOST_FOREACH(HLR fix, fixingValues)
    {
        d = iborFakeCalendar->advance(d,
                                      HL_Period(-1, HL_PeriodUnit_Days),
                                      HL_BusinessDayConvention_Preceding,
                                      false /*send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth*/);




        dateRealHistory->storeFixing(historyTag,
                                     ptime(d) /*time*/,
                                     fix /* newFixingValue*/);

    } // end for fix





    return dateRealHistory;

} // end HLTEST_get_HL_TimeRealHistoryeo


} // end namespace HL_Object
} //end namespace HorizonLib
