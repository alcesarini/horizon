/**
FILE NAME= hl_iborIndex.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131216
*/
#ifndef _hl_iborIndex_h_
#define _hl_iborIndex_h_


#include <hl/underlyings/interestRates/hl_interestRate.h>


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
// class HL_IborIndexCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131210
\brief The ins code
*/

class HL_IborIndexCode : public virtual HL_InterestRateCode
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

        HL_SERIALIZE_BASE_CLASS(HL_InterestRateCode);

    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_IborIndexCode();

    virtual ~HL_IborIndexCode();
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
; // end class HL_IborIndexCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IborIndexCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_IborIndexCodePtr BSP<HLINS::HL_IborIndexCode>

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IborIndex
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131210
\brief Basic financial instrument.
*/
class HL_IborIndex : public virtual HL_InterestRate
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

        HL_SERIALIZE_BASE_CLASS(HL_InterestRate);

        HL_SER(accrualEndDateBDC_);
        HL_SER(accrualEndDatePreserveLastBusinessDayOfMonth_);
        HL_SER(dcc_);


    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_IborIndex();

    virtual ~HL_IborIndex();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(HL_BusinessDayConvention/*ClassVariableType*/, accrualEndDateBDC/*classVariableName_no_underscore*/);
    HL_CLASS_VAR_ACCESS_METHODS(bool/*ClassVariableType*/, accrualEndDatePreserveLastBusinessDayOfMonth/*classVariableName_no_underscore*/);
    HL_CLASS_VAR_ACCESS_METHODS(HL_DccPtr/*ClassVariableType*/, dcc/*classVariableName_no_underscore*/);


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


    date accrualEndDate(const date & accrualStartDate) const;


    void descriptionImpl(std::ostream & os) const;

    HLR forecastedExpectation(const date & fixingDate, const HL_MeasurePtr & hl_MeasurePtr) const;
    //@}
protected:


    /**
    Class variables
    */
    //@{
    HL_BusinessDayConvention accrualEndDateBDC_;
    bool accrualEndDatePreserveLastBusinessDayOfMonth_;

    HL_DccPtr dcc_;
    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_IborIndex


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_IborIndexCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_IborIndexPtr BSP<HLINS::HL_IborIndex>


} // end namespace HL_InterestRates
} // end namespace HL_Underlyings
} // end namespace HL_MarketData
} //end namespace HorizonLib


#endif // _hl_iborIndex_h_
