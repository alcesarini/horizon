/**
FILE NAME= hl_mktInsFactory.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20141208
*/
#ifndef _hl_mktInsFactory_h_
#define _hl_mktInsFactory_h_

#include <hl/instruments/anagraphics/hl_mktInsAnagraphics.h>


namespace HorizonLib
{
namespace HL_Instruments
{
namespace HL_Anagraphics
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InsFactory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141227
\brief A factory to build a class HL_Instrument out of a class HL_Anagraphics.
*/
class HL_InsFactory
{
public:
    /**
    Constructors & destructors
    */
    //@{

    HL_InsFactory();

    virtual ~HL_InsFactory();
    //@}


    /**
    Public class interface
    */
    //@{


    // HL_CLASS_VAR_ACCESS_METHODS(HL_ScheduleAnagraphicsPtr, scheduleAnagraphics);


    HL_InstrumentPtr build_instrument(const HL_AnagraphicsPtr & anagraphics) const;



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


    virtual HL_InstrumentPtr build_instrument_impl(const HL_AnagraphicsPtr & anagraphics) const=0;

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



    //@}

}
; // end class HL_InsFactory


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InsFactory: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_InsFactoryPtr BSP<HLAN::HL_InsFactory>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_LegInsFactory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141208
\brief A factory to build a class HL_Instrument out of a class HL_LegAnagraphics.
*/
class HL_LegInsFactory : public HL_InsFactory
{
public:
    /**
    Constructors & destructors
    */
    //@{

    HL_LegInsFactory();

    virtual ~HL_LegInsFactory();
    //@}


    /**
    Public class interface
    */
    //@{


    // HL_CLASS_VAR_ACCESS_METHODS(HL_ScheduleAnagraphicsPtr, scheduleAnagraphics);


    HL_CalendarPtr get_calendar() const
    {
        return legAnagraphics_->get_calendar();
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


    HL_CashFlowStructurePtr build_cashFlowStructure(const HL_AccrualPeriodPtr & accrualPeriod) const;

    virtual void setDerivedLegAnagraphics() const=0;

    virtual HL_CashFlowPtr build_coupon(const HL_CashFlowStructurePtr &cashFlowStructure) const=0;



    HL_ObjCodePtr couponCodeBuildHelper(const HL_CashFlowStructurePtr &cashFlowStructure) const;

    virtual HL_CashFlowCodePtr instantiateCouponCodeImpl() const=0;

    //@}


    /**
    Implementations of base class methods
    */
    //@{

    HL_InstrumentPtr build_instrument_impl(const HL_AnagraphicsPtr & anagraphics) const;


    //@}

protected:


    /**
    Class variables
    */
    //@{



    mutable HL_LegAnagraphicsPtr legAnagraphics_;

    //@}

}
; // end class HL_LegInsFactory


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_LegInsFactory: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_LegInsFactoryPtr BSP<HLAN::HL_LegInsFactory>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedLegInsFactory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141208
\brief A factory to build a class HL_Instrument out of a class HL_LegAnagraphics.
*/
class HL_FixedLegInsFactory : public HL_LegInsFactory
{
public:
    /**
    Constructors & destructors
    */
    //@{

    HL_FixedLegInsFactory();

    virtual ~HL_FixedLegInsFactory();
    //@}


    /**
    Public class interface
    */
    //@{


    // HL_CLASS_VAR_ACCESS_METHODS(HL_ScheduleAnagraphicsPtr, scheduleAnagraphics);



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

    void setDerivedLegAnagraphics() const;


    virtual HL_CashFlowPtr build_coupon(const HL_CashFlowStructurePtr &cashFlowStructure) const;
    //@}


    /**
    Implementations of base class methods
    */
    //@{

    HL_CashFlowCodePtr instantiateCouponCodeImpl() const;

    //@}

protected:


    /**
    Class variables
    */
    //@{




    mutable HL_FixedLegAnagraphicsPtr fixedLegAnagraphics_;

    //@}

}
; // end class HL_FixedLegInsFactory


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FixedLegInsFactory: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_FixedLegInsFactoryPtr BSP<HLAN::HL_FixedLegInsFactory>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableLegInsFactory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141208
\brief A factory to build a class HL_Instrument out of a class HL_LegAnagraphics.
*/
class HL_VariableLegInsFactory : public HL_LegInsFactory
{
public:
    /**
    Constructors & destructors
    */
    //@{

    HL_VariableLegInsFactory();

    virtual ~HL_VariableLegInsFactory();
    //@}


    /**
    Public class interface
    */
    //@{


    // HL_CLASS_VAR_ACCESS_METHODS(HL_ScheduleAnagraphicsPtr, scheduleAnagraphics);



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

    void setDerivedLegAnagraphics() const;


    virtual HL_CashFlowPtr build_coupon(const HL_CashFlowStructurePtr &cashFlowStructure) const;
    //@}


    /**
    Implementations of base class methods
    */
    //@{

    HL_CashFlowCodePtr instantiateCouponCodeImpl() const;

    //@}

protected:


    /**
    Class variables
    */
    //@{




    mutable HL_UnderlyingDeliveryLegAnagraphicsPtr underlyingDeliveryLegAnagraphics_;

    //@}

}
; // end class HL_VariableLegInsFactory


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VariableLegInsFactory: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_VariableLegInsFactoryPtr BSP<HLAN::HL_VariableLegInsFactory>

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_UnderlyingDeliveryLegInsFactory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


typedef HL_VariableLegInsFactory HL_UnderlyingDeliveryLegInsFactory;


//------------------------------------------------------------------------------------------------------

#define HL_UnderlyingDeliveryLegInsFactoryPtr BSP<HLAN::HL_UnderlyingDeliveryLegInsFactory>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_SwapInsFactory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141227
\brief A factory to build a swap.
*/
class HL_SwapInsFactory : public HL_InsFactory
{
public:
    /**
    Constructors & destructors
    */
    //@{

    HL_SwapInsFactory();

    virtual ~HL_SwapInsFactory();
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

    HL_InstrumentPtr build_instrument_impl(const HL_AnagraphicsPtr & anagraphics) const;

    //@}

protected:


    /**
    Class variables
    */
    //@{





    //@}

}
; // end class HL_SwapInsFactory


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_SwapInsFactory: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_SwapInsFactoryPtr BSP<HLAN::HL_SwapInsFactory>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_InsFactoryPtr getInsFactory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
Utility to be used to instantiate the right HL_InsFactoryPtr when one has a anagraphics
of an unknown type.
*/
HL_InsFactoryPtr getInsFactory(const HL_AnagraphicsPtr & anagraphics);


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_InstrumentPtr buildIns
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
Utility to be used to instantiate HL_InstrumentPtr when one has a anagraphics
of an unknown type.
*/
HL_InstrumentPtr buildIns(const HL_AnagraphicsPtr & anagraphics);





} // end namespace HL_Anagraphics
} // end namespace HL_Instruments
} //end namespace HorizonLib


#endif // _hl_mktInsFactory_h_
