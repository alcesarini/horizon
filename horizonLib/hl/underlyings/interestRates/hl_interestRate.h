/**
FILE NAME= hl_interestRate.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131214
*/
#ifndef _hl_interestRate_h_
#define _hl_interestRate_h_


#include <hl/underlyings/hl_underlying.h>
#include <hl/dateTime/hl_period.h>
#include <hl/dateTime/hl_dcc.h>

namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_Underlyings
{
namespace HL_InterestRates
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterestRateCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131210
\brief The ins code
*/

class HL_InterestRateCode : public virtual HL_UnderlyingCode
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

        HL_SERIALIZE_BASE_CLASS(HL_UnderlyingCode);

    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_InterestRateCode();

    virtual ~HL_InterestRateCode();
    //@}


    /**
    Public class interface
    */
    //@{

    //@}


protected:



    /**
    Additional implementations
    */
    //@{
    /**
    Default initialization of the class vars.
    */
    void classDefaultInit();
    //@}

    /**
    Implementations of base class methods
    */
    //@{
    HLSTRING objTypeImpl() const;
    //@}

protected:


    /**
    Class variables
    */
    //@{

    //@}

}
; // end class HL_InterestRateCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterestRateCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_InterestRateCodePtr BSP<HLINS::HL_InterestRateCode>





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterestRate
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131210
\brief Basic financial instrument.
*/
class HL_InterestRate : public virtual HL_Underlying
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

        HL_SERIALIZE_BASE_CLASS(HL_Underlying);

        HL_SER(tenor_);
        HL_SER(fixingDays_);


    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_InterestRate();

    virtual ~HL_InterestRate();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(HL_Period/*ClassVariableType*/, tenor/*classVariableName_no_underscore*/);

    HL_CLASS_VAR_ACCESS_METHODS(HLI/*ClassVariableType*/, fixingDays/*classVariableName_no_underscore*/);




    date fixingDate(const date & accrualStartDate) const;

    date accrualStartDate(const date & fixingDate) const;

    virtual date accrualEndDate(const date & accrualStartDate) const=0;

    bool isValidFixingDate(const date & fixingDate) const;

    //@}

protected:



    /**
    Additional implementations
    */
    //@{
    /**
    Default initialization of the class vars.
    */
    void classDefaultInit();

    //@}


    /**
    Implementations of base class methods
    */
    //@{
    void descriptionImpl(std::ostream & os) const;
    //@}

protected:


    /**
    Class variables
    */
    //@{
    /**
    The length of the interest rate (for ex.: 3m for eur3m, 5y for cms rate 5y).
    */
    HL_Period tenor_;

    /**
    accrualStartDate  = fixDate + fixingDays_ (usuallay fixingDays_=2 days).
    */
    HLI fixingDays_;


    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_InterestRate


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterestRateCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_InterestRatePtr BSP<HLINS::HL_InterestRate>


} // end namespace HL_InterestRates
} // end namespace HL_Underlyings
} // end namespace HL_MarketData
} //end namespace HorizonLib


#endif // _hl_interestRate_h_
