/**
FILE NAME= hl_mktInsAnagraphics.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20141207
*/
#ifndef _hl_mktInsAnagraphics_h_
#define _hl_mktInsAnagraphics_h_

#include <hl/instruments/anagraphics/hl_anagraphics.h>
#include <hl/instruments/anagraphics/hl_scheduleAnagraphics.h>
#include <hl/instruments/hl_cashFlow.h>

namespace HorizonLib
{
namespace HL_Instruments
{
namespace HL_Anagraphics
{






//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_LegAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141207
\brief A leg in a short amount of data.
*/
class HL_LegAnagraphics : public virtual HL_Anagraphics
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

        HL_SERIALIZE_BASE_CLASS(HL_Anagraphics);

        HL_SER(ccyCode_);
        HL_SER(scheduleAnagraphics_);
        HL_SER(accrualDcc_);
        HL_SER(payDateSettlementDays_);
        HL_SER(payDateBusinessDayConvention_);

    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_LegAnagraphics();

    virtual ~HL_LegAnagraphics();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(HL_CcyCodePtr, ccyCode);
    HL_CLASS_VAR_ACCESS_METHODS(HL_ScheduleAnagraphicsPtr, scheduleAnagraphics);
    HL_CLASS_VAR_ACCESS_METHODS(HL_DccPtr, accrualDcc);
    HL_CLASS_VAR_ACCESS_METHODS(HLI, payDateSettlementDays);
    HL_CLASS_VAR_ACCESS_METHODS(HL_BusinessDayConvention, payDateBusinessDayConvention);






    virtual HLINS::HL_CashFlowType get_cashFlowType() const=0;


    virtual void checkAnagraphics() const;

    HL_CalendarPtr get_calendar() const
    {
        return scheduleAnagraphics_->get_calendar();
    }

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

    HL_CcyCodePtr ccyCode_;

    HL_ScheduleAnagraphicsPtr scheduleAnagraphics_;


    HL_DccPtr accrualDcc_;

    /**
    The pay date is offset by this nb of days w.r.t. the accrual end date
    of the coupon and according to the calendar specified in scheduleAnagraphics_.
    */
    HLI payDateSettlementDays_;

    /**
    To be used in association to payDateSettlementDays_
    */
    HL_BusinessDayConvention payDateBusinessDayConvention_;


    //@}

}
; // end class HL_LegAnagraphics


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_LegAnagraphics: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_LegAnagraphicsPtr BSP<HLAN::HL_LegAnagraphics>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedLegAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141207
\brief A fixed leg in a short amount of data.
*/
class HL_FixedLegAnagraphics : public virtual HL_LegAnagraphics
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

        HL_SERIALIZE_BASE_CLASS(HL_LegAnagraphics);

        HL_SER(fixedRate_);



    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_FixedLegAnagraphics();

    virtual ~HL_FixedLegAnagraphics();
    //@}


    /**
    Public class interface
    */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS(HLR, fixedRate);





    /**
    Unique tag for the mkt quote type.
    */
    HL_AnagraphicsType anagraphicsType() const
    {

        return HL_AnagraphicsType_FixedLegAnagraphics;
    }




    HLINS::HL_CashFlowType get_cashFlowType() const
    {
        return HLINS::HL_CashFlowType_Fixed;
    }

    virtual void checkAnagraphics() const;

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

    HLR fixedRate_;



    //@}

}
; // end class HL_FixedLegAnagraphics


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedLegAnagraphics: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_FixedLegAnagraphicsPtr BSP<HLAN::HL_FixedLegAnagraphics>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableLegAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141207
\brief A fixed leg in a short amount of data.
*/
class HL_VariableLegAnagraphics : public virtual HL_LegAnagraphics
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

        HL_SERIALIZE_BASE_CLASS(HL_LegAnagraphics);

        HL_SER(basketComposition_);
        HL_SER(basket_);
        HL_SER(fixingSettlementDays_);
        HL_SER(fixingBusinessDayConvention_);


    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_VariableLegAnagraphics();

    virtual ~HL_VariableLegAnagraphics();
    //@}


    /**
    Public class interface
    */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS(HL_BasketCompositionPtr, basketComposition);


    HL_CLASS_VAR_ACCESS_METHODS(HL_BasketPtr, basket);

    HL_CLASS_VAR_ACCESS_METHODS(HLI, fixingSettlementDays);
    HL_CLASS_VAR_ACCESS_METHODS(HL_BusinessDayConvention, fixingBusinessDayConvention);


    /**
    Unique tag for the mkt quote type.
    */
    HL_AnagraphicsType anagraphicsType() const
    {

        return HL_AnagraphicsType_UnderlyingDeliveryLegAnagraphics;
    }


    HLINS::HL_CashFlowType get_cashFlowType() const
    {
        return HLINS::HL_CashFlowType_UnderlyingDelivery;
    }

    void checkAnagraphics() const;

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

    HL_BasketCompositionPtr basketComposition_;

    HL_BasketPtr basket_;



    /**
    The fix date is offset by this nb of days w.r.t. the accrual start date
    of the coupon and according to the calendar specified in scheduleAnagraphics_.
    */
    HLI fixingSettlementDays_;

    /**
    To be used in association to payDateSettlementDays_
    */
    HL_BusinessDayConvention fixingBusinessDayConvention_;



    //@}

}
; // end class HL_VariableLegAnagraphics


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableLegAnagraphics: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_VariableLegAnagraphicsPtr BSP<HLAN::HL_VariableLegAnagraphics>

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryLegAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

typedef HL_VariableLegAnagraphics HL_UnderlyingDeliveryLegAnagraphics;

//------------------------------------------------------------------------------------------------------

#define HL_UnderlyingDeliveryLegAnagraphicsPtr BSP<HLAN::HL_UnderlyingDeliveryLegAnagraphics>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_SwapAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141207
\brief A swap in a short amount of data.
*/
class HL_SwapAnagraphics : public virtual HL_Anagraphics
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

        HL_SERIALIZE_BASE_CLASS(HL_Anagraphics);

        HL_SER(receiveLegAnagraphics_);
        HL_SER(payLegAnagraphics_);



    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_SwapAnagraphics();

    virtual ~HL_SwapAnagraphics();
    //@}


    /**
    Public class interface
    */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS(HL_LegAnagraphicsPtr, receiveLegAnagraphics);
    HL_CLASS_VAR_ACCESS_METHODS(HL_LegAnagraphicsPtr, payLegAnagraphics);


    /**
    Unique tag for the mkt quote type.
    */
    HL_AnagraphicsType anagraphicsType() const
    {

        return HL_AnagraphicsType_SwapAnagraphics;
    }


    void checkAnagraphics() const;

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

    HL_LegAnagraphicsPtr receiveLegAnagraphics_;
    HL_LegAnagraphicsPtr payLegAnagraphics_;



    //@}

}
; // end class HL_SwapAnagraphics


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_SwapAnagraphics: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_SwapAnagraphicsPtr BSP<HLAN::HL_SwapAnagraphics>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_HL_FixedLegAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_FixedLegAnagraphicsPtr HL_TEST_get_HL_FixedLegAnagraphics(
        const HL_CcyCodePtr& ccyCode,
        const date & spotDate,
        const HL_Period & scheduleLength,
        const HL_Period & couponFrequency,
        HLR fixedRate);



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_HL_UnderlyingDeliveryLegAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_UnderlyingDeliveryLegAnagraphicsPtr HL_TEST_get_HL_UnderlyingDeliveryLegAnagraphics(
        const HL_CcyCodePtr& ccyCode,
        const date & spotDate,
        const HL_Period & scheduleLength,
        const HL_Period & couponFrequency,
        const HL_BasketCompositionPtr & basketComposition,
        const HL_BasketPtr & basket
        );


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_get_Basket_Ibor
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_BasketPtr HL_TEST_get_Basket_Ibor(HLS nbMonths);



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_HL_get_SwapAnagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_SwapAnagraphicsPtr HL_TEST_HL_get_SwapAnagraphics(const date & spotDate,
                                                     const HL_Period & scheduleLength,
                                                     const HL_Period & fixedCouponFrequency,
                                                     HLR fixedRate,
                                                     const HL_Period & floatCouponFrequency,
                                                     HLS iborNbMonths);




} // end namespace HL_Anagraphics
} // end namespace HL_Instruments
} //end namespace HorizonLib


#endif // _hl_mktInsAnagraphics_h_
