/**
FILE NAME=hl_rootFinding.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20150721
*/
#ifndef _hl_rootFinding_h_
#define _hl_rootFinding_h_

#include <hl/math/hl_function.h>

namespace HorizonLib
{
namespace HL_Math
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RootFinderData
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140726
\brief This class specifies a system of data to discount cashflows without credit risk.

The idea is that one could have in principle more ways to risk-free discount cashflows, i.e.
this is a sort of pricing data detail for a pricing model.
In simple setups, one will have just one instance of this class.
*/

class HL_RootFinderData : public virtual HLSER::HL_Serializable, public virtual Descriptable
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
        HL_SER(init_a_);
        HL_SER(init_b_);
        HL_SER(maxFunctionInvocations_);
        HL_SER(digitTolerance_);


    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_RootFinderData();

    virtual ~HL_RootFinderData();
    //@}


    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(HLR, init_a);
    HL_CLASS_VAR_ACCESS_METHODS(HLR, init_b);
    HL_CLASS_VAR_ACCESS_METHODS(HLS, maxFunctionInvocations);
    HL_CLASS_VAR_ACCESS_METHODS(HLS, digitTolerance);


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


    HLR init_a_;
    HLR init_b_;
    HLS maxFunctionInvocations_;
    HLS digitTolerance_;



    //@}

}
; // end class HL_RootFinderData


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RootFinderData: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



#define HL_RootFinderDataPtr BSP<HLMA::HL_RootFinderData>





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_RootFindingResultType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
\brief The HL library period units.
*/
enum HL_RootFindingResultType
{
    HL_RootFindingResultType_InvalidMin=0,
    HL_RootFindingResultType_Found,
    HL_RootFindingResultType_MaxNbFunctionInvocationsReached,
    HL_RootFindingResultType_NotInitialyBracketed_a,
    HL_RootFindingResultType_NotInitialyBracketed_b,
    HL_RootFindingResultType_InvalidMax
}; // end enum HL_RootFindingResultType

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
        HL_RootFindingResultType,
        "HL_RootFindingResultType_InvalidMin",
        "HL_RootFindingResultType_Found",
        "HL_RootFindingResultType_MaxNbFunctionInvocationsReached",
        "HL_RootFindingResultType_NotInitialyBracketed_a",
        "HL_RootFindingResultType_NotInitialyBracketed_b",
        "HL_RootFindingResultType_InvalidMax"
        );



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RootFinder
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20150723
\brief To find the zero of a functor.

It looks in an interval [a,b], with a<=b or b>=a, assuming that the functor is monotone inside it.
If f(a)*f(b)>=0, the extremum that gives the result closer to 0 is chosen as result.
The relative precision of the bracketing interval will be the larget
between 2^{1-digitTolerance} and twice the machine epsilon (see class boost::math::tools::eps_tolerance<HLR>).


*/
class HL_RootFinder
{

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_RootFinder();

    virtual ~HL_RootFinder();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(HL_RootFinderDataPtr, rootFinderData);



    /**
    actualNbFunctionCalls: how many calls have been performed in the method.
    */
    void findSolution(
            const HL_RealFunctionPtr &realFunction,
            HLR & solution,
            HLS & actualNbFunctionCalls,
            HL_RootFindingResultType &rootFindingResultType) const;

    //@}


protected:


    /**
    We keep this wrapper in the base class, since it could be useful for many derived classes,
    in reason of the fact that std (and hence boost) usually want to use functor as objects in their
    algorithms.
    */
    class HL_RealFunctorWrapper
    {
    public:

        HL_RealFunctorWrapper(const HL_RealFunctionPtr & realFunction,
                              HLS &nbFunctionCalls)
            :
              realFunction_(realFunction),
              nbFunctionCalls_(nbFunctionCalls)
        {

            nbFunctionCalls_=0;

        }

        HLR operator()(HLR x) const
        {
            nbFunctionCalls_++;
            return realFunction_->operator ()(x);
        }


        HL_CLASS_VAR_ACCESS_METHODS_O(HLS, nbFunctionCalls);
    protected:

        HL_RealFunctionPtr realFunction_;
        HLS &nbFunctionCalls_;


    };

protected:

    /**
    Additional implementations
    */
    //@{
    /**
    Default initialization of the class vars.
    */
    void classDefaultInit();



    virtual void findSolutionImpl(
            const HL_RealFunctorWrapper & realFunctorWrapper,
            HLR a,
            HLR b,
            HLR & solution,
            HL_RootFindingResultType &rootFindingResultType) const=0;



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

    HL_RootFinderDataPtr rootFinderData_;



    //@}

}
; // end class HL_RootFinder


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RootFinder: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_RootFinderPtr BSP<HLMA::HL_RootFinder>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RootFinderToms748
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20150723
\brief Specialization of HL_RootFinder for toms748_solve (see http://www.boost.org)


*/
class HL_RootFinderToms748 : public HL_RootFinder
{

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_RootFinderToms748();

    virtual ~HL_RootFinderToms748();
    //@}


    /**
    Public class interface
    */
    //@{


    //@}


protected:



protected:

    /**
    Additional implementations
    */
    //@{
    /**
    Default initialization of the class vars.
    */
    void classDefaultInit();



    void findSolutionImpl(
            const HL_RealFunctorWrapper & realFunctorWrapper,
            HLR a,
            HLR b,
            HLR & solution,
            HL_RootFindingResultType &rootFindingResultType) const;



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
; // end class HL_RootFinderToms748


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RootFinderToms748: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_RootFinderToms748Ptr BSP<HLMA::HL_RootFinderToms748>

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_HL_RootFinder
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


void HL_TEST_HL_RootFinder();



} // end namespace HL_Math
} //end namespace HorizonLib


#endif // _hl_rootFinding_h_
