/**
FILE NAME= hl_period.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131218
*/
#include <hl/dateTime/hl_period.h>


namespace HorizonLib
{
namespace HL_DateTime
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_PeriodUnit
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



void HL_TEST_period_duration()
{



    HL_Period period_days(3, HL_PeriodUnit_Days);
    HL_Period period_weeks(4, HL_PeriodUnit_Weeks);
    HL_Period period_months(5, HL_PeriodUnit_Months);
    HL_Period period_years(6, HL_PeriodUnit_Years);


    std::stringstream ss;

    ss << period_days << "\n";
    ss << period_weeks << "\n";
    ss << period_months << "\n";
    ss << period_years << "\n";

    ss << "--------------------------------------\n";


    date d(2013, Jan, 1);

    date d1 = d + period_days;
    date d2 = d + period_weeks;
    date d3 = d + period_months;
    date d4 = d + period_years;

    ss << "d= " << d << "\n";
    ss << "d1= " << d1 << "\n";
    ss << "d2= " << d2 << "\n";
    ss << "d3= " << d3 << "\n";
    ss << "d4= " << d4 << "\n";

    HL_GET_LOGGER(false);

    HL_LOG(HLLOG::HL_severity_level_notification, ss.str());

} // end HL_TEST_period_duration

//------------------------------------------------------------------------------------------------------


void HL_TEST_writing_enum_descriptions()
{
    std::stringstream ss;

    for(HLI i=HL_PeriodUnit_InvalidMin;i<=HL_PeriodUnit_InvalidMax;++i)
    {

        HL_PeriodUnit pu_i =(HL_PeriodUnit)i;

        HL_DESCRIBE_ENUM(ss, pu_i);

    } // end for i

    HL_GET_LOGGER(false /*addTimer*/);


    HL_LOG(HLLOG::HL_severity_level_notification, ss.str());


} // end HL_TEST_writing_enum_descriptions


//------------------------------------------------------------------------------------------------------
void hl_PeriodServiceTransform(const HL_Period & period,
                               HLL & nbUnits,
                               HL_PeriodUnit& periodUnit
                               )
{

    nbUnits= period.get_nbUnits();

    switch(period.get_periodUnit())
    {
    case HL_PeriodUnit_Days:
        periodUnit=HL_PeriodUnit_Days;
    case HL_PeriodUnit_Weeks:
        nbUnits*=7;
        break;
    case HL_PeriodUnit_Months:
        periodUnit=HL_PeriodUnit_Months;
    case HL_PeriodUnit_Years:
        nbUnits*=12;
        break;
    default:
        HL_FAIL("invalid period.get_periodUnit()=" << period.get_periodUnit());
    } // end switch(periodUnit_)

} // end hl_PeriodServiceTransform

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Period_descr_visitor
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

//class HL_Period_descr_visitor: public boost::static_visitor<>
//{
//public:

//	HL_Period_descr_visitor(std::ostream& os)
//		:
//	os_(os)
//	{}

//
//	void operator()(boost::gregorian::days & t) const
//	{
//		os_ << t;
//	}
//	void operator()(boost::gregorian::weeks & t) const
//	{
//		os_ << t;
//	}
//	void operator()(boost::gregorian::months & t) const
//	{
//		os_ << t.number_of_months() << "m";
//	}
//	void operator()(boost::gregorian::years & t) const
//	{
//		os_ << t.number_of_years() << "y";
//	}

//protected:
//	std::ostream& os_;
//}; // end HL_Period_descr_visitor


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Period_DateIncrement_Visitor
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

class HL_Period_DateIncrement_Visitor: public boost::static_visitor<date>
{
public:


    template <class T>
    date operator()(T & t) const
    {
        ++t;

        return *t;
    }

}; // end HL_Period_DateIncrement_Visitor


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Period
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_Period::HL_Period(HLL nbUnits, HL_PeriodUnit periodUnit)
    :
      nbUnits_(nbUnits),
      periodUnit_(periodUnit)
{
    HL_ENUM_CHECK_LARGE(HL_PeriodUnit, periodUnit_);
} // end HL_Period

//------------------------------------------------------------------------------------------------------

HL_Period::~HL_Period()
{
} // end ~HL_Period

//------------------------------------------------------------------------------------------------------

HL_Order HL_Period::getOrder(const HL_Period & period) const
{
    //------------------------------------------------------------------------------------------------------
    HLL nbUnitsThis;
    HL_PeriodUnit periodUnitThis;

    hl_PeriodServiceTransform(*this/*period*/,
                              nbUnitsThis/* nbUnits*/,
                              periodUnitThis/* periodUnit*/
                              );

    //------------------------------------------------------------------------------------------------------
    HLL nbUnitsOther;
    HL_PeriodUnit periodUnitOther;

    hl_PeriodServiceTransform(period,
                              nbUnitsOther/* nbUnits*/,
                              periodUnitOther/* periodUnit*/
                              );
    //------------------------------------------------------------------------------------------------------
    HL_SRE(periodUnitThis==periodUnitOther, "the two instances of HL_Period are not comparable: "
           << "(*this)= " << (*this) << ", period=" << period << " (able to compare "
           << "only Days/Days, Days/Weeks, Months/Months, Months/Years)");

    return plainOrder(nbUnitsThis, nbUnitsOther);


} // end getOrder

//------------------------------------------------------------------------------------------------------


bool HL_Period::empty() const
{
    return periodUnit_==HL_PeriodUnit_InvalidMin && nbUnits_==0;

} // end empty


//------------------------------------------------------------------------------------------------------

HL_PeriodVariant HL_Period::getPeriodVariant() const
{
    switch(periodUnit_)
    {
    case HL_PeriodUnit_Days:
        return boost::gregorian::days(nbUnits_);
    case HL_PeriodUnit_Weeks:
        return boost::gregorian::weeks(nbUnits_);
    case HL_PeriodUnit_Months:
        return boost::gregorian::months(nbUnits_);
    case HL_PeriodUnit_Years:
        return boost::gregorian::years(nbUnits_);
    default:
        ;
    } // end switch(periodUnit_)

    HL_FAIL("invalid periodUnit_=" << periodUnit_);

} // end getPeriodVariant

//------------------------------------------------------------------------------------------------------

HL_PeriodIteratorVariant HL_Period::getPeriodIteratorVariant(const date & d) const
{
    switch(periodUnit_)
    {
    case HL_PeriodUnit_Days:
        return boost::gregorian::day_iterator(d, nbUnits_);
    case HL_PeriodUnit_Weeks:
        return boost::gregorian::week_iterator(d, nbUnits_);
    case HL_PeriodUnit_Months:
        return boost::gregorian::month_iterator(d, nbUnits_);
    case HL_PeriodUnit_Years:
        return boost::gregorian::year_iterator(d, nbUnits_);
    default:
        ;
    } // end switch(periodUnit_)

    HL_FAIL("invalid periodUnit_=" << periodUnit_);

} // end getPeriodIteratorVariant

//------------------------------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const HL_Period& period)
{

    //HL_PeriodVariant hl_PeriodVariant=period.getPeriodVariant();

    //boost::apply_visitor(HL_Period_descr_visitor(os), hl_PeriodVariant);


    return os << period.get_nbUnits() << getEnumString(period.get_periodUnit());
} // end operator<<


//------------------------------------------------------------------------------------------------------



date operator+(const date & d, const HL_Period& period)
{

    HL_PeriodIteratorVariant hl_PeriodIteratorVariant_d = period.getPeriodIteratorVariant(d);

    return boost::apply_visitor(HL_Period_DateIncrement_Visitor(), hl_PeriodIteratorVariant_d);

} // end operator+()

//------------------------------------------------------------------------------------------------------

HL_Period operator*(HLL i, const HL_Period& period)
{

    HL_Period p(i*period.get_nbUnits(), period.get_periodUnit());

    return p;


} // end operator*



} // end namespace HL_DateTime
} //end namespace HorizonLib
