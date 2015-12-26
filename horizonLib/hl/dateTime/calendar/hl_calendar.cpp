/**
FILE NAME= hl_calendar.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131216
*/
#include <hl/dateTime/calendar/hl_calendar.h>


HL_SERIALIZATION_CLASS_EXPORT_GUID(HLCAL::HL_Calendar);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLCAL::HL_CalendarCode);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLCAL::HL_FakeCalendar);

namespace HorizonLib
{
namespace HL_DateTime
{
namespace HL_Calendars
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CalendarCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CalendarCode::HL_CalendarCode()
{
    classDefaultInit();

} // end HL_CalendarCode

//------------------------------------------------------------------------------------------------------

HL_CalendarCode::~HL_CalendarCode()
{
} // end ~HL_CalendarCode

//------------------------------------------------------------------------------------------------------

void HL_CalendarCode::classDefaultInit()
{

} // end classDefaultInit
//------------------------------------------------------------------------------------------------------

HLSTRING HL_CalendarCode::objTypeImpl() const
{
    return "HL_CalendarCode";
} // end objTypeImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Calendar
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_Calendar::HL_Calendar()
{

    classDefaultInit();



} // end HL_Calendar

//------------------------------------------------------------------------------------------------------

HL_Calendar::~HL_Calendar()
{
} // end ~HL_Calendar


//------------------------------------------------------------------------------------------------------

void HL_Calendar::classDefaultInit()
{

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

bool HL_Calendar::isHoliday(const date & d) const
{

    HL_SR(isValidDate(d));

    return isHolidayImpl(d);

} // end isHoliday


//------------------------------------------------------------------------------------------------------

bool HL_Calendar::isLastBusinessDayOfMonth(const date & d) const
{

    HL_SR(isValidDate(d));

    date nextBusinessDay = adjust(d+days(1), HL_BusinessDayConvention_Following);

    bool eom = (d.month()!=nextBusinessDay.month());
    return eom;

} // end isLastBusinessDayOfMonth


//------------------------------------------------------------------------------------------------------

date HL_Calendar::advance(const date & d,
                          const HL_Period& hl_Period,
                          HL_BusinessDayConvention hl_BusinessDayConvention,
                          bool send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth
                          ) const
{
    HL_SR(isValidDate(d));

    HL_PeriodUnit periodUnit = hl_Period.get_periodUnit();
    HL_ENUM_CHECK(HL_PeriodUnit, periodUnit);

    HLL nbUnits = hl_Period.get_nbUnits();

    date adv_d;

    if(nbUnits==0){
        adv_d = adjust(d, hl_BusinessDayConvention);
        return adv_d;
    }


    switch(periodUnit)
    {
    case HL_PeriodUnit_Days:
    {
        int step = (nbUnits>0) ? 1 : -1;

        day_iterator d_itr(d, step);

        while(nbUnits!=0)
        {
            ++d_itr;

            if(!isHoliday(*d_itr))
                nbUnits-=step;

        } // end while(nbUnits!=0)
        adv_d = (*d_itr);
    }
        return adv_d;
    case HL_PeriodUnit_Weeks:
        adv_d = d + hl_Period;
        break;
    case HL_PeriodUnit_Months:
    case HL_PeriodUnit_Years:
        adv_d = d + hl_Period;

        if(send_LastBusinessDayOfMonth_In_LastBusinessDayOfMonth && isLastBusinessDayOfMonth(d)){
            return lastBusinessDayOfMonth(adv_d);
        }
        break;
    default:
        HL_FAIL("invalid hl_Period.get_periodUnit()=" << hl_Period.get_periodUnit());
    } // end switch(periodUnit_)

    adv_d = adjust(adv_d, hl_BusinessDayConvention);

    return adv_d;

} // end advance

//------------------------------------------------------------------------------------------------------


date HL_Calendar::lastBusinessDayOfMonth(const date & d) const
{
    date endOfMonth =  d.end_of_month();
    endOfMonth = adjust(endOfMonth, HL_BusinessDayConvention_Preceding);

    return endOfMonth;
} // end lastBusinessDayOfMonth

//------------------------------------------------------------------------------------------------------

date HL_Calendar::adjust(const date & d, HL_BusinessDayConvention hl_bdc) const
{
    HL_SR(isValidDate(d));

    if (hl_bdc==HL_BusinessDayConvention_Unadjusted)
        return d;

    bool isModifiedConvention=false;
    HL_BusinessDayConvention modified_bdc=HL_BusinessDayConvention_InvalidMin;
    int step;

    switch(hl_bdc)
    {
    case HL_BusinessDayConvention_ModifiedFollowing:
        isModifiedConvention=true;
        modified_bdc=HL_BusinessDayConvention_Preceding;
    case HL_BusinessDayConvention_Following:
        step=1;
        break;
    case HL_BusinessDayConvention_ModifiedPreceding:
        isModifiedConvention=true;
        modified_bdc=HL_BusinessDayConvention_Following;
    case HL_BusinessDayConvention_Preceding:
        step=-1;
        break;
    default:
        HL_FAIL("invalid hl_bdc=" << hl_bdc);
    } // end switch(hl_bdc)


    day_iterator d_itr(d, step);

    while(isHoliday(*d_itr))
    {
        ++d_itr;
    } // end while d_itr


    date d_adj(*d_itr);

    if(isModifiedConvention && d_adj.month()!=d.month())
        return adjust(d, modified_bdc);

    return d_adj;


} // end adjust

//------------------------------------------------------------------------------------------------------

bool HL_Calendar::isValidDate(const date & d) const
{
    return (d!=date(not_a_date_time));
} // end isValidDate


//------------------------------------------------------------------------------------------------------

void HL_Calendar::descriptionImpl(std::ostream & os) const
{
    HLOBJ::HL_Obj::descriptionImpl(os);

} // end descriptionImpl



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FakeCalendar
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_FakeCalendar::HL_FakeCalendar()
{

    classDefaultInit();



} // end HL_FakeCalendar

//------------------------------------------------------------------------------------------------------

HL_FakeCalendar::~HL_FakeCalendar()
{
} // end ~HL_FakeCalendar


//------------------------------------------------------------------------------------------------------

void HL_FakeCalendar::classDefaultInit()
{

} // end classDefaultInit



//------------------------------------------------------------------------------------------------------

void HL_FakeCalendar::descriptionImpl(std::ostream & os) const
{
    HLOBJ::HL_Obj::descriptionImpl(os);

} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

bool HL_FakeCalendar::isHolidayImpl(const date & d) const
{

    tm d_tm = to_tm(d);

    return d_tm.tm_wday==6 /*Saturday */|| d_tm.tm_wday==0 /*Sunday*/;

} // end isHolidayImpl



} // end namespace HL_Calendars
} // end namespace HL_DateTime
} //end namespace HorizonLib
