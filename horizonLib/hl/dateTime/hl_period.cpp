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



			HL_Period hl_Period_days(3, HL_PeriodUnit_Days);
			HL_Period hl_Period_weeks(4, HL_PeriodUnit_Weeks);
			HL_Period hl_Period_months(5, HL_PeriodUnit_Months);
			HL_Period hl_Period_years(6, HL_PeriodUnit_Years);


			std::stringstream ss;

			ss << hl_Period_days << "\n";
			ss << hl_Period_weeks << "\n";
			ss << hl_Period_months << "\n";
			ss << hl_Period_years << "\n";

			ss << "--------------------------------------\n";


			date d(2013, Jan, 1);

			date d1 = d + hl_Period_days;
			date d2 = d + hl_Period_weeks;
			date d3 = d + hl_Period_months;
			date d4 = d + hl_Period_years;

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
		void hl_PeriodServiceTransform(const HL_Period & hl_Period,
			HLL & nbUnits, 
			HL_PeriodUnit& hl_PeriodUnit
			)
		{

			nbUnits= hl_Period.get_nbUnits();

			switch(hl_Period.get_hl_PeriodUnit())
			{
			case HL_PeriodUnit_Days:
				hl_PeriodUnit=HL_PeriodUnit_Days;
			case HL_PeriodUnit_Weeks:
				nbUnits*=7;
				break;
			case HL_PeriodUnit_Months:
				hl_PeriodUnit=HL_PeriodUnit_Months;
			case HL_PeriodUnit_Years:
				nbUnits*=12;
				break;
			default:
				HL_FAIL("invalid hl_Period.get_hl_PeriodUnit()=" << hl_Period.get_hl_PeriodUnit());
			} // end switch(hl_PeriodUnit_)

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


		HL_Period::HL_Period(HLL nbUnits, HL_PeriodUnit hl_PeriodUnit)
			:
		nbUnits_(nbUnits),
			hl_PeriodUnit_(hl_PeriodUnit)
		{
			HL_ENUM_CHECK_LARGE(HL_PeriodUnit, hl_PeriodUnit_);
		} // end HL_Period

		//------------------------------------------------------------------------------------------------------

		HL_Period::~HL_Period()
		{
		} // end ~HL_Period

		//------------------------------------------------------------------------------------------------------

		HL_Order HL_Period::getOrder(const HL_Period & hl_Period) const
		{
			//------------------------------------------------------------------------------------------------------
			HLL nbUnitsThis; 
			HL_PeriodUnit hl_PeriodUnitThis;

			hl_PeriodServiceTransform(*this/*hl_Period*/,
				nbUnitsThis/* nbUnits*/, 
				hl_PeriodUnitThis/* hl_PeriodUnit*/
				);

			//------------------------------------------------------------------------------------------------------
			HLL nbUnitsOther; 
			HL_PeriodUnit hl_PeriodUnitOther;

			hl_PeriodServiceTransform(hl_Period,
				nbUnitsOther/* nbUnits*/, 
				hl_PeriodUnitOther/* hl_PeriodUnit*/
				);
			//------------------------------------------------------------------------------------------------------
			HL_SRE(hl_PeriodUnitThis==hl_PeriodUnitOther, "the two instances of HL_Period are not comparable: " 
				<< "(*this)= " << (*this) << ", hl_Period=" << hl_Period << " (able to compare "
				<< "only Days/Days, Days/Weeks, Months/Months, Months/Years)");

			return plainOrder(nbUnitsThis, nbUnitsOther);


		} // end getOrder

		//------------------------------------------------------------------------------------------------------

		HL_PeriodVariant HL_Period::getPeriodVariant() const
		{
			switch(hl_PeriodUnit_)
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
			} // end switch(hl_PeriodUnit_)

			HL_FAIL("invalid hl_PeriodUnit_=" << hl_PeriodUnit_);

		} // end getPeriodVariant

		//------------------------------------------------------------------------------------------------------

		HL_PeriodIteratorVariant HL_Period::getPeriodIteratorVariant(const date & d) const
		{
			switch(hl_PeriodUnit_)
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
			} // end switch(hl_PeriodUnit_)

			HL_FAIL("invalid hl_PeriodUnit_=" << hl_PeriodUnit_);

		} // end getPeriodIteratorVariant

		//------------------------------------------------------------------------------------------------------

		std::ostream& operator<<(std::ostream& os, const HL_Period& hl_Period)
		{

			//HL_PeriodVariant hl_PeriodVariant=hl_Period.getPeriodVariant();

			//boost::apply_visitor(HL_Period_descr_visitor(os), hl_PeriodVariant);


			return os << hl_Period.get_nbUnits() << getEnumString(hl_Period.get_hl_PeriodUnit()); 
		} // end operator<<


		//------------------------------------------------------------------------------------------------------



		date operator+(const date & d, const HL_Period& hl_Period)
		{

			HL_PeriodIteratorVariant hl_PeriodIteratorVariant_d = hl_Period.getPeriodIteratorVariant(d);

			return boost::apply_visitor(HL_Period_DateIncrement_Visitor(), hl_PeriodIteratorVariant_d);

		} // end operator+()

	} // end namespace HL_DateTime
} //end namespace HorizonLib
