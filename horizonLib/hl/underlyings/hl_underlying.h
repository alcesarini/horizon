/**
FILE NAME= hl_underlying.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131214
*/
#ifndef _hl_underlying_h_
#define _hl_underlying_h_


#include <hl/mktData/hl_mktData.h>
#include <hl/dateTime/calendar/hl_calendar.h>
#include <hl/object/hl_history.h>
#include <hl/mktData/volSurfaces/hl_volSurface.h>
#include <hl/math/probMeasures/hl_probMeasure.h>

namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_Underlyings
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131210
\brief The ins code
*/

class HL_UnderlyingCode : public virtual HLMD::HL_MktDataCode
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

        HL_SERIALIZE_BASE_CLASS(HLMD::HL_MktDataCode);

    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_UnderlyingCode();

    virtual ~HL_UnderlyingCode();
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
; // end class HL_UnderlyingCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_UnderlyingCodePtr BSP<HLUND::HL_UnderlyingCode>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Underlying
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131216
\brief Basic financial instrument.
*/
class HL_Underlying : public virtual HLMD::HL_MktData
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

        HL_SERIALIZE_BASE_CLASS(HLMD::HL_MktData);
        HL_SER(calendar_);
        HL_SER(hl_TimeRealHistoryPtr_);
        HL_SER(impliedVolSurfaceCode_);


    }
    //@} Serialization -----------------------------------


public:
    /**
    Constructors & destructors
    */
    //@{

    HL_Underlying();

    virtual ~HL_Underlying();
    //@}


    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(HL_CalendarPtr/*ClassVariableType*/, calendar/*classVariableName_no_underscore*/);

    HL_CLASS_VAR_ACCESS_METHODS(HL_TimeRealHistoryPtr/*ClassVariableType*/, hl_TimeRealHistoryPtr/*classVariableName_no_underscore*/);

    HL_CLASS_VAR_ACCESS_METHODS(HL_VolSurfaceCodePtr, impliedVolSurfaceCode);

    /**
    \param  historyTag is the tag of the history that will be used for past fixings
    */
    HL_ExpectationPtr expectation(const date & fixingDate,
                                  const HL_MeasurePtr & measure=HL_MeasurePtr(),
                                  const HLSTRING & historyTag=HLSTRING())
    {

        return expectation(ptime(fixingDate),
                           measure,
                           historyTag);
    }

    HL_ExpectationPtr expectation(const ptime & fixingTime,
                                  const HL_MeasurePtr & measure=HL_MeasurePtr(),
                                  const HLSTRING & historyTag=HLSTRING()) const;


    HL_ExpectationPtr quotingMeasureExpectation(const date & fixingDate,
                                                const HLSTRING & historyTag=HLSTRING()) const
    {

        return quotingMeasureExpectation(ptime(fixingDate), historyTag);
    }

    /**
     * This is the expectation in the quoting measure of impliedVolSurface_, i.e. the
     * expectation quoted by the market.
    */
    HL_ExpectationPtr quotingMeasureExpectation(const ptime & fixingTime,
                                                const HLSTRING & historyTag=HLSTRING()) const;

    HLR get_spot() const
    {

        HLR spot = quotingMeasureExpectation(get_refTime())->get_value();
        return spot;
    }

    HL_VolSurfacePtr get_impliedVolSurface() const;

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


    HL_ExpectationPtr getServiceExpectation(bool & pastFixingFound,
                                            const ptime & fixingTime,
                                            const HL_MeasurePtr & measure,
                                            const HLSTRING & historyTag=HLSTRING()) const;



    HLR forecastExpectation(const ptime & fixingTime, const HL_MeasurePtr & measure) const;

    virtual HLR forecastQuotingMeasureExpectationImpl(const ptime & fixingTime) const=0;

    virtual HL_MeasurePtr get_quotingMeasure(const ptime & fixingTime) const=0;



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
    HL_CalendarPtr calendar_;

    HL_TimeRealHistoryPtr hl_TimeRealHistoryPtr_;




    /**
    The implied vol of the underlying quoted by the mkt (notice that
    the vol can be expressed as normal vol, log-normal vol, shifted log-normal, etc..)
    according to its internal variable.
    */
    HL_VolSurfaceCodePtr impliedVolSurfaceCode_;
    //@}

private:
    /**
    Private class variables
    */
    //@{


    //@}
}
; // end class HL_Underlying


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_UnderlyingPtr BSP<HLUND::HL_Underlying>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//  defaultHistoryTag()
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HLSTRING defaultHistoryTag();


} // end namespace HL_Underlyings
} // end namespace HL_MarketData
} //end namespace HorizonLib


#endif // _hl_underlying_h_
