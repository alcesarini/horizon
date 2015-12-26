/**
FILE NAME= hl_period.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131218
*/
#ifndef _hl_period_h_
#define _hl_period_h_

#include <hl/basicFiles/hl_commonDeclarations.h>

namespace HorizonLib
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_PeriodUnit
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
\brief The HL library period units.
*/
enum HL_PeriodUnit
{
    HL_PeriodUnit_InvalidMin=0,
    HL_PeriodUnit_Days,
    HL_PeriodUnit_Weeks,
    HL_PeriodUnit_Months,
    HL_PeriodUnit_Years,
    HL_PeriodUnit_InvalidMax
}; // end enum HL_PeriodUnit

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
        HL_PeriodUnit,
        "HL_PeriodUnit_InvalidMin",
        "d",
        "w",
        "m",
        "y",
        "HL_PeriodUnit_InvalidMax"
        );

namespace HL_DateTime
{

//------------------------------------------------------------------------------------------------------

void HL_TEST_period_duration();

//------------------------------------------------------------------------------------------------------

void HL_TEST_writing_enum_descriptions();

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Period
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

typedef boost::variant<boost::gregorian::days,
boost::gregorian::weeks,
boost::gregorian::months,
boost::gregorian::years> HL_PeriodVariant;

//------------------------------------------------------------------------------------------------------

typedef boost::variant<boost::gregorian::day_iterator,
boost::gregorian::week_iterator,
boost::gregorian::month_iterator,
boost::gregorian::year_iterator> HL_PeriodIteratorVariant;

//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131218
\brief The HL library period.
*/

class HL_Period : public virtual HLSER::HL_Serializable
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

        HL_SER(nbUnits_);
        HL_SER(periodUnit_);
    }
    //@} Serialization -----------------------------------

    friend std::ostream& operator<<(std::ostream& os, const HL_Period& period);

    friend date operator+(const date & d, const HL_Period& period);




public:


    /**
    Constructors & destructors
    */
    //@{

    HL_Period(HLL nbUnits=0, HL_PeriodUnit hl_PeriodUnit=HL_PeriodUnit_InvalidMin);


    virtual ~HL_Period();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_Order getOrder(const HL_Period & period) const;

    HL_CLASS_VAR_ACCESS_METHODS(long, nbUnits);

    HL_CLASS_VAR_ACCESS_METHODS(HL_PeriodUnit, periodUnit);

    bool empty() const;
    //@}


protected:

    /**
    Additional implementations
    */
    //@{

    HL_PeriodVariant getPeriodVariant() const;

    HL_PeriodIteratorVariant getPeriodIteratorVariant(const date & d) const;

    //@}


    /**
    Implementations of base class methods
    */
    //@{

    //@}


protected:


    /**
    Class variables
    */
    //@{
    /**
    The period will be nbUnits_x hl_PeriodUnit()
    */
    HLL nbUnits_;
    HL_PeriodUnit periodUnit_;
    //@}



}
; // end class HL_Period

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Period:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_DEFINE_ALL_ORDERING(HL_Period);

//------------------------------------------------------------------------------------------------------

std::ostream& operator<<(std::ostream& os, const HL_Period& period);

//------------------------------------------------------------------------------------------------------

date operator+(const date & d, const HL_Period& period);

//------------------------------------------------------------------------------------------------------

HL_Period operator*(HLL i, const HL_Period& period);
//------------------------------------------------------------------------------------------------------

inline HL_Period operator*(const HL_Period& period, HLL i)
{
    return i*period;
}
//------------------------------------------------------------------------------------------------------

inline HL_Period operator-(const HL_Period& period)
{
    return -1*period;
}

} // end namespace HL_DateTime

//------------------------------------------------------------------------------------------------------


using HL_DateTime::HL_Period;


} //end namespace HorizonLib


#endif // _hl_period_h_
