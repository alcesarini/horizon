/**
FILE NAME= hl_correlationTermStructure.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140602
*/
#ifndef _hl_interactionTermStructure_h_
#define _hl_interactionTermStructure_h_

#include <hl/mktData/hl_mktData.h>
#include <hl/math/interpolation/hl_interpolator.h>
#include <hl/underlyings/hl_underlying.h>

namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_Interactions
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InteractionTermStructureCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131213
\brief The term structure code
*/

class HL_InteractionTermStructureCode : public virtual HLMD::HL_MktDataCode
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

        HL_SER(objCodePtr1_);
        HL_SER(objCodePtr2_);


    }
    //@} Serialization -----------------------------------




public:


    /**
    Constructors & destructors
    */
    //@{

    HL_InteractionTermStructureCode();

    virtual ~HL_InteractionTermStructureCode();
    //@}


    /**
    Public class interface
    */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS(HL_ObjCodePtr, objCodePtr1);
    HL_CLASS_VAR_ACCESS_METHODS(HL_ObjCodePtr, objCodePtr2);


    virtual bool isCorrelation() const
    {
        HL_UNEXPECTED_FUNCTION_CALL;
    }

    bool isCovariance() const
    {
        return !isCorrelation();
    }


    //@}


protected:

    /**
    Implementations of base class methods
    */
    //@{
    HLSTRING objTypeImpl() const;


    void descriptionImpl(std::ostream & os) const;


    //@}


    /**
    Additional implementations
    */
    //@{
    /**
    Default initialization of the class vars.
    */
    void classDefaultInit();
    //@}

protected:


    /**
    Class variables
    */
    //@{
    /**
    Codes of the objects this class represents the interaction of.
    */
    HL_ObjCodePtr objCodePtr1_, objCodePtr2_;
    //@}

}
; // end class HL_InteractionTermStructureCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InteractionTermStructureCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_InteractionTermStructureCodePtr BSP<HLINTERACTIONS::HL_InteractionTermStructureCode>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InteractionTermStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131213
\brief Base class for correlation or covariance term structure between the fwds of two underlyings.

See comment to method get_interaction.
*/
class HL_InteractionTermStructure : public virtual HL_MktData
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

        HL_SERIALIZE_BASE_CLASS(HL_MktData);

        HL_SER(interactionTermStructureCode_);

    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_InteractionTermStructure();

    virtual ~HL_InteractionTermStructure();
    //@}


    /**
    Public class interface
    */
    //@{




    void set_HL_ObjCodePtr(const HL_ObjCodePtr & hl_ObjCodePtr);

    /**
    This method returns the interaction (i.e. correlation or covariance) between

    F_1(fixingDate, firstFwdMaturityTime) and F_2(fixingDate, secondFwdMaturityTime)

    for the evolution in the time interval [refDate, fixingDate], where

    - F_1(fixingDate, firstFwdMaturityTime) is the fwd of underlying_1 with maturity firstFwdMaturityTime observed at fixingDate

    - F_2(fixingDate, secondFwdMaturityTime) is the fwd of underlying_2 with maturity secondFwdMaturityTime observed at fixingDate

    We specify that the interaction is quoted as a 3-dimensional interpolation against the following 3 variables:

    1) fixingTime = yearFraction(refDate, fixingDate)

    2) deltaTime_1 = yearFraction(fixingDate, firstFwdMaturityTime)>0 (it must be >0)

    3) deltaTime_2 = yearFraction(fixingDate, secondFwdMaturityTime)>0 (it must be >0)


    Actually there's also another interface dealing with fixingTime instead of fixingDate (possibly more
    precise from the point of view of time measuring).
    */
    HLR get_interaction(const date & fixingDate,
                        const ptime & firstFwdMaturityTime,
                        const ptime & secondFwdMaturityTime) const
    {

        return get_interaction(ptime(fixingDate)/*fixingTime*/,
                               firstFwdMaturityTime,
                               secondFwdMaturityTime);

    } // end get_interaction



    virtual HLR get_interaction(const ptime & fixingTime,
                                const ptime & firstFwdMaturityTime,
                                const ptime & secondFwdMaturityTime) const;



    const HL_ObjCodePtr & get_objCodePtr1() const
    {
        return interactionTermStructureCode_->get_objCodePtr1();

    }

    const HL_ObjCodePtr & get_objCodePtr2() const
    {
        return interactionTermStructureCode_->get_objCodePtr2();

    }

    bool isCorrelation() const
    {
        return interactionTermStructureCode_->isCorrelation();
    }

    bool isCovariance() const
    {
        return interactionTermStructureCode_->isCovariance();
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


    HLR get_yf(const ptime& t_1, const ptime& t_2) const;


    HLR get_yf(const date& d_1, const date& d_2) const;

    virtual HLR get_interactionImpl(HLR fixingTime,
                                    HLR deltaTime_1,
                                    HLR deltaTime_2) const
    {
        HL_UNEXPECTED_FUNCTION_CALL;
    }


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


    HL_InteractionTermStructureCodePtr interactionTermStructureCode_;
    //@}

}
; // end class HL_InteractionTermStructure


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InteractionTermStructure: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_InteractionTermStructurePtr BSP<HLINTERACTIONS::HL_InteractionTermStructure>

//------------------------------------------------------------------------------------------------------

HL_InteractionTermStructurePtr get_InteractionTermStructurePtr(
        const HL_MktDataCollectorPtr & mktDataCollectorPtr, const HL_ObjCodePtr & objCodePtr);


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InteractionData
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 *
 * interactionMatrices.size()==fixingPeriods.size()
 * interactionMatrices[t].rows()==interactionMatrices[t].columns()==deltaPeriods.size() for all t
 *
 * interactionMatrices[t][m][n] holds the interaction in time interval [refDate, fixingDate_t]
 * with fixingDate_t = reDate+fixingPeriods[t] between
 * F_1(fixingDate_t, firstFwdMaturityTime_t_m) and F_2(fixingDate_t, secondFwdMaturityTime_t_n), with
 * firstFwdMaturityTime_t_m = fixingDate_t+deltaPeriods[m]
 * secondFwdMaturityTime_t_n =  fixingDate_t+deltaPeriods[n]
 *
 * Notice that F_1(fixingDate_t, firstFwdMaturityTime_t_m) and F_2(fixingDate_t, secondFwdMaturityTime_t_n)
 * are the fwds of underlying_1 and underlying_2 observed at fixingDate_t for respective maturities
 * firstFwdMaturityTime_t_m and secondFwdMaturityTime_t_n.
 *
*/
struct HL_InteractionData
{

    std::vector<HL_Period> fixingPeriods;
    std::vector<HL_Period> deltaPeriods;
    std::vector<MATRIX> interactionMatrices;



}; // end struct HL_InteractionData

//------------------------------------------------------------------------------------------------------


#define HL_InteractionDataPtr BSP<HLINTERACTIONS::HL_InteractionData>

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterpInteractionTermStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140305
\brief Implements HL_InteractionTermStructure through interpolation.
*/
class HL_InterpInteractionTermStructure : public virtual HL_InteractionTermStructure
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

        HL_SERIALIZE_BASE_CLASS(HL_InteractionTermStructure);
        HL_SER(interpolatorPtr_);






    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_InterpInteractionTermStructure();

    virtual ~HL_InterpInteractionTermStructure();
    //@}


    /**
    Public class interface
    */
    //@{


    void set_InteractionData(const HL_InteractionDataPtr & interactionDataPtr);


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


    void setInteractionPoints(const HL_InteractionDataPtr & interactionDataPtr);


    HLR get_interactionImpl(HLR fixingTime,
                            HLR deltaTime_1,
                            HLR deltaTime_2) const;

    //@}

protected:


    /**
    Class variables
    */
    //@{

    /**
     * Holds the points to be interpolated against (fixingTime, deltaTime_1, deltaTime_2)
     * */
    HL_InterpolatorPtr interpolatorPtr_;



    mutable VEC service_xVect_;
    VEC::const_iterator service_xVectBegin_, service_xVectEnd_;

    //@}

}
; // end class HL_InterpInteractionTermStructure


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterpInteractionTermStructure: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_InterpInteractionTermStructurePtr BSP<HLINTERACTIONS::HL_InterpInteractionTermStructure>

//------------------------------------------------------------------------------------------------------


HL_InterpInteractionTermStructurePtr HL_TEST_build_HL_InterpInteractionTermStructurePtr(
        const HL_ObjCodePtr & objCodePtr1,
        const HL_ObjCodePtr & objCodePtr2,
        const HL_MktDataCollectorPtr & mktDataCollectorPtr
        );

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class instantiateInteractionTermStructureCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



template <class T>
inline BSP<T> instantiateInteractionTermStructureCode(const HL_ObjCodePtr &objCodePtr1,
                                                      const HL_ObjCodePtr &objCodePtr2,
                                                      const HLSTRING & codeString)
{
    BSP<T> t(new T);

    t->set_sCode(codeString + "_"+ objCodePtr1->get_sCode() + "_" + objCodePtr2->get_sCode());

    t->set_objCodePtr1(objCodePtr1);
    t->set_objCodePtr2(objCodePtr2);
    return t;
} // end instantiateInteractionTermStructureCode




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CorrelationTermStructureCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_CorrelationTermStructureCodePtr BSP<HLINTERACTIONS::HL_CorrelationTermStructureCode>

//------------------------------------------------------------------------------------------------------


/**
\author A. Cesarini
\date 20140802
\brief CorrelationTermStructureCode
*/
class HL_CorrelationTermStructureCode : public virtual HL_InteractionTermStructureCode
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

        HL_SERIALIZE_BASE_CLASS(HL_InteractionTermStructureCode);

    }
    //@} Serialization -----------------------------------


    /**
    Constructors & destructors
    */
    //@{


    /**
     * Notice this constructor is protected since the creation of HL_CorrelationTermStructureCode
     * should always be accomplished using the static method instantiateInteractionTermStructureCode
    */
    HL_CorrelationTermStructureCode();

public:
    virtual ~HL_CorrelationTermStructureCode();
    //@}


    /**
    Public class interface
    */
    //@{
    bool isCorrelation() const
    {
        return true;
    }


    /**
     * This should be the unique way one creates an instance of HL_CorrelationTermStructureCode

    */
    friend BSP<HL_CorrelationTermStructureCode>
    instantiateInteractionTermStructureCode<HL_CorrelationTermStructureCode>(const HL_ObjCodePtr &objCodePtr1,
                                                                             const HL_ObjCodePtr &objCodePtr2,
                                                                             const HLSTRING & codeString);

    static HL_CorrelationTermStructureCodePtr instantiateCorrelationTermStructureCode(
            const HL_ObjCodePtr &objCodePtr1,
            const HL_ObjCodePtr &objCodePtr2 )
    {

        return instantiateInteractionTermStructureCode<HL_CorrelationTermStructureCode>(objCodePtr1,
                                                                                        objCodePtr2,
                                                                                        "Correlation");
    } // end instantiateCorrelationTermStructureCode


    //@}


protected:

    /**
    Implementations of base class methods
    */
    //@{
    HLSTRING objTypeImpl() const;
    //@}


    /**
    Additional implementations
    */
    //@{
    /**
    Default initialization of the class vars.
    */
    void classDefaultInit();
    //@}

protected:


    /**
    Class variables
    */
    //@{

    //@}

}
; // end class HL_CorrelationTermStructureCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CorrelationTermStructureCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CorrelationTermStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


typedef HL_InteractionTermStructure HL_CorrelationTermStructure;

//------------------------------------------------------------------------------------------------------

#define HL_CorrelationTermStructurePtr BSP<HLINTERACTIONS::HL_CorrelationTermStructure>


//------------------------------------------------------------------------------------------------------

inline HL_CorrelationTermStructurePtr get_CorrelationTermStructurePtr(
        const HL_MktDataCollectorPtr & mktDataCollectorPtr,
        const HL_CorrelationTermStructureCodePtr & correlationTermStructureCode)
{
    return get_InteractionTermStructurePtr(mktDataCollectorPtr, correlationTermStructureCode);

}




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CovarianceTermStructureCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_CovarianceTermStructureCodePtr BSP<HLINTERACTIONS::HL_CovarianceTermStructureCode>

//------------------------------------------------------------------------------------------------------


/**
\author A. Cesarini
\date 20140802
\brief CovarianceTermStructureCode
*/
class HL_CovarianceTermStructureCode : public virtual HL_InteractionTermStructureCode
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

        HL_SERIALIZE_BASE_CLASS(HL_InteractionTermStructureCode);

    }
    //@} Serialization -----------------------------------


    /**
    Constructors & destructors
    */
    //@{


    /**
     * Notice this constructor is protected since the creation of HL_CovarianceTermStructureCode
     * should always be accomplished using the static method instantiateInteractionTermStructureCode
    */
    HL_CovarianceTermStructureCode();

public:
    virtual ~HL_CovarianceTermStructureCode();
    //@}


    /**
    Public class interface
    */
    //@{
    bool isCorrelation() const
    {
        return false;
    }


    /**
     * This should be the unique way one creates an instance of HL_CovarianceTermStructureCode

    */
    friend BSP<HL_CovarianceTermStructureCode>
    instantiateInteractionTermStructureCode<HL_CovarianceTermStructureCode>(const HL_ObjCodePtr &objCodePtr1,
                                                                            const HL_ObjCodePtr &objCodePtr2,
                                                                            const HLSTRING & codeString);

    static HL_CovarianceTermStructureCodePtr instantiateCovarianceTermStructureCode(
            const HL_ObjCodePtr &objCodePtr1,
            const HL_ObjCodePtr &objCodePtr2 )
    {

        return instantiateInteractionTermStructureCode<HL_CovarianceTermStructureCode>(objCodePtr1,
                                                                                       objCodePtr2,
                                                                                       "Covariance");
    } // end instantiateCovarianceTermStructureCode


    //@}


protected:

    /**
    Implementations of base class methods
    */
    //@{
    HLSTRING objTypeImpl() const;
    //@}


    /**
    Additional implementations
    */
    //@{
    /**
    Default initialization of the class vars.
    */
    void classDefaultInit();
    //@}

protected:


    /**
    Class variables
    */
    //@{

    //@}

}
; // end class HL_CovarianceTermStructureCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CovarianceTermStructureCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CovarianceTermStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


typedef HL_InteractionTermStructure HL_CovarianceTermStructure;

//------------------------------------------------------------------------------------------------------

#define HL_CovarianceTermStructurePtr BSP<HLINTERACTIONS::HL_CovarianceTermStructure>


//------------------------------------------------------------------------------------------------------

inline HL_CovarianceTermStructurePtr get_CovarianceTermStructurePtr(
        const HL_MktDataCollectorPtr & mktDataCollectorPtr, const HL_ObjCodePtr & objCodePtr)
{
    return get_InteractionTermStructurePtr(mktDataCollectorPtr, objCodePtr);

}



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_DerivedCovarianceTermStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140802
\brief This class couples the vols of two underlyings and their correlations in order to define their covariance.

The constrcutor is protected since the class should be instantiated only through method getDerivedCovarianceTermStructure.
*/
class HL_DerivedCovarianceTermStructure : public virtual HL_CovarianceTermStructure
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

        HL_SERIALIZE_BASE_CLASS(HL_CovarianceTermStructure);


    }
    //@} Serialization -----------------------------------


    /**
    Constructors & destructors
    */
    //@{

    HL_DerivedCovarianceTermStructure();
public:
    virtual ~HL_DerivedCovarianceTermStructure();
    //@}


    /**
    Public class interface
    */
    //@{


    /**
     * objCodePtr1 and objCodePtr2 are the codes of the underlyings the returned covariance should be about.
     *
     * mktDataCollectorPtr is to be used to get both the two underlyings and also their CorrelationTermStructure
    */
    static HL_CovarianceTermStructurePtr getDerivedCovarianceTermStructure(
            const HL_ObjCodePtr & objCodePtr1,
            const HL_ObjCodePtr & objCodePtr2,
            const HL_MktDataCollectorPtr & mktDataCollectorPtr
            );


    HL_CLASS_VAR_ACCESS_METHODS(HL_UnderlyingPtr, underlying1);
    HL_CLASS_VAR_ACCESS_METHODS(HL_UnderlyingPtr, underlying2);
    HL_CLASS_VAR_ACCESS_METHODS_O(HL_CorrelationTermStructurePtr, correlationTermStructure12);
    void set_correlationTermStructure12(const HL_CorrelationTermStructurePtr& correlationTermStructure12);


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


    HLR get_interaction(const ptime & fixingTime,
                        const ptime & firstFwdMaturityTime,
                        const ptime & secondFwdMaturityTime) const;




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

    HL_UnderlyingPtr underlying1_;
    HL_UnderlyingPtr underlying2_;
    HL_CorrelationTermStructurePtr correlationTermStructure12_;


    //@}

}
; // end class HL_DerivedCovarianceTermStructure


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_DerivedCovarianceTermStructure: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_DerivedCovarianceTermStructurePtr BSP<HLINTERACTIONS::HL_DerivedCovarianceTermStructure>




} // end namespace HL_Interactions
} // end namespace HL_MarketData
} //end namespace HorizonLib


#endif // _hl_interactionTermStructure_h_
