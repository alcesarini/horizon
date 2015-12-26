/**
FILE NAME= hl_rootFinding.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20150721
*/
#include <hl/math/rootFinding/hl_rootFinding.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLMA::HL_RootFinderData);

namespace HorizonLib
{
namespace HL_Math
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RootFinderData
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_RootFinderData::HL_RootFinderData()
{
    classDefaultInit();

} // end HL_RootFinderData

//------------------------------------------------------------------------------------------------------

HL_RootFinderData::~HL_RootFinderData()
{} // end ~HL_RootFinderData

//------------------------------------------------------------------------------------------------------

void HL_RootFinderData::classDefaultInit()
{


    init_a_=HL_NAN;
    init_b_=HL_NAN;

    maxFunctionInvocations_=HL_NULL_INTEGER;
    digitTolerance_=HL_NULL_INTEGER;



} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_RootFinderData::descriptionImpl(std::ostream & os) const
{

    Descriptable::descriptionImpl(os);
    os << "HL_RootFinderData:\n";
    hl_fillDescriptionStream(init_a_);
    hl_fillDescriptionStream(init_b_);
    hl_fillDescriptionStream(maxFunctionInvocations_);
    hl_fillDescriptionStream(digitTolerance_);


} // end descriptionImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RootFinder
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_RootFinder::HL_RootFinder()
{

    classDefaultInit();



} // end HL_RootFinder

//------------------------------------------------------------------------------------------------------

HL_RootFinder::~HL_RootFinder()
{} // end ~HL_RootFinder


//------------------------------------------------------------------------------------------------------

void HL_RootFinder::classDefaultInit()
{




} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_RootFinder::findSolution(
        const HL_RealFunctionPtr &realFunction,
        HLR & solution,
        HLS & actualNbFunctionCalls,
        HL_RootFindingResultType &rootFindingResultType) const
{


    HL_PNN(rootFinderData_);

    HL_PNN(realFunction);

    HL_SR(realFunction->get_domainDim()==1);

    HL_SR(realFunction->get_coDomainDim()==1);

    HL_RealFunctorWrapper realFunctorWrapper(realFunction, actualNbFunctionCalls);

    HLR a = rootFinderData_->get_init_a();

    HLR b = rootFinderData_->get_init_b();

    if(a>b)
        HL_SwapVars(a, b);

    HLR f_a = realFunctorWrapper(a);

    if(f_a==0){

        solution = a;
        rootFindingResultType = HL_RootFindingResultType_Found;

        return;
    } // end if(f_a==0)


    HLR f_b = realFunctorWrapper(b);

    if(f_b==0){

        solution = b;
        rootFindingResultType = HL_RootFindingResultType_Found;
        return;

    } // if(f_b==0)


    if(f_a * f_b>0)
    {
        if(std::fabs(f_a)>=std::fabs(f_b)){

            solution = b;
            rootFindingResultType = HL_RootFindingResultType_NotInitialyBracketed_b;

        }else{

            solution = a;
            rootFindingResultType = HL_RootFindingResultType_NotInitialyBracketed_a;
        }
        return;

    } // end  if(f_a * f_b>0)



    findSolutionImpl(
                realFunctorWrapper,
                a,
                b,
                solution,
                rootFindingResultType);



} // end findSolution


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RootFinder: defines, utils
//-----------------------------------------------------b-------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RootFinderToms748
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_RootFinderToms748::HL_RootFinderToms748()
{

    classDefaultInit();



} // end HL_RootFinderToms748

//------------------------------------------------------------------------------------------------------

HL_RootFinderToms748::~HL_RootFinderToms748()
{} // end ~HL_RootFinderToms748


//------------------------------------------------------------------------------------------------------

void HL_RootFinderToms748::classDefaultInit()
{

} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_RootFinderToms748::findSolutionImpl(
        const HL_RealFunctorWrapper & realFunctorWrapper,
        HLR a,
        HLR b,
        HLR & solution,
        HL_RootFindingResultType &rootFindingResultType) const
{



    boost::uintmax_t max_iter=rootFinderData_->get_maxFunctionInvocations();

    boost::math::tools::eps_tolerance<HLR> tol(rootFinderData_->get_digitTolerance());


    std::pair<HLR, HLR> bracket =
            boost::math::tools::toms748_solve(
                realFunctorWrapper/*f*/,
                a /*a*/,
                b/*b*/,
                tol,
                max_iter);


    if(max_iter<rootFinderData_->get_maxFunctionInvocations()){

        rootFindingResultType = HL_RootFindingResultType_Found;

    }else{
        rootFindingResultType = HL_RootFindingResultType_MaxNbFunctionInvocationsReached;

    }

    /*
    We do not perform more complicated best guesess since the bracket could already be very close
    to the machine precision, hence computations would be dangerous and also useless given the fact
    that the required precision has probably already been reached.
    */
    solution = 0.5*(bracket.first+bracket.second);



} // end findSolutionImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RootFinderToms748: defines, utils
//-----------------------------------------------------b-------------------------------------------------
//------------------------------------------------------------------------------------------------------



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_HL_RootFinder
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TEST_RootFinderFunction
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20131227
 \brief Specialization of HL_RealFunction for domainDim_=1, coDomainDim_=1.
 */
class HL_TEST_RootFinderFunction : public virtual HL_RealFunctor
{
public:
    /**
     Constructors & destructors
     */
    //@{

    HL_TEST_RootFinderFunction(HLR y)
        :
          y_(y)
    {

    }

    //@}

    /**
     Public class interface
     */
    //@{


    HLR operator()(HLR x) const
    {

        return x*x-y_;
    }

    //@}

protected:

    HLR y_;

}
; // end class HL_TEST_RootFinderFunction



//------------------------------------------------------------------------------------------------------


void HL_TEST_HL_RootFinder_y(HLR init_a, HLR init_b, HLS maxFunctionInvocations, HLS digitTolerance, HLR y)
{


    HL_RootFinderPtr rootFinder(new HL_RootFinderToms748);


    HL_RootFinderDataPtr rootFinderData(new HL_RootFinderData);

    rootFinderData->set_init_a(init_a);

    rootFinderData->set_init_b(init_b);

    rootFinderData->set_maxFunctionInvocations(maxFunctionInvocations);

    rootFinderData->set_digitTolerance(digitTolerance);

    rootFinder->set_rootFinderData(rootFinderData);

    HLR solution = HL_NAN;

    HL_RootFindingResultType rootFindingResultType=HL_RootFindingResultType_InvalidMin;

    HL_RealFunctionPtr realFunction(new HL_TEST_RootFinderFunction(y));

    HLS actualNbFunctionCalls=0;

    rootFinder->findSolution(realFunction, solution, actualNbFunctionCalls, rootFindingResultType);


    HL_GET_LOGGER(false/*addTimer*/);


    HL_LOG(HLLOG::HL_severity_level_notification,
           "\n" <<
           "-------------------------------" << "\n" <<
           "solution=" << solution << "\n" <<
           ", actualNbFunctionCalls=" << actualNbFunctionCalls << "\n" <<
           ", rootFindingResultType=" << getEnumString(rootFindingResultType) << "\n" <<
           ", init_a=" << init_a << "\n" <<
           ", init_b=" << init_b << "\n" <<
           ", maxFunctionInvocations=" << maxFunctionInvocations << "\n" <<
           ", digitTolerance=" << digitTolerance << "\n" <<
           "-------------------------------"
           );



} // end HL_TEST_HL_RootFinder_y

//------------------------------------------------------------------------------------------------------

void HL_TEST_HL_RootFinder()
{
    HL_TEST_HL_RootFinder_y(2./* init_a*/, 4. /*init_b*/, 1000 /*maxFunctionInvocations*/, 8 /*digitTolerance*/, 9.2 /*y*/);

    HL_TEST_HL_RootFinder_y(2./* init_a*/, 4. /*init_b*/, 1000 /*maxFunctionInvocations*/, 16 /*digitTolerance*/, 9.2 /*y*/);

    HL_TEST_HL_RootFinder_y(2./* init_a*/, 4. /*init_b*/, 1000 /*maxFunctionInvocations*/, 32 /*digitTolerance*/, 9.2 /*y*/);

    HL_TEST_HL_RootFinder_y(4./* init_a*/, 2. /*init_b*/, 1000 /*maxFunctionInvocations*/, 32 /*digitTolerance*/, 9.2 /*y*/);

    HL_TEST_HL_RootFinder_y(4./* init_a*/, 5. /*init_b*/, 1000 /*maxFunctionInvocations*/, 32 /*digitTolerance*/, 9.2 /*y*/);

    HL_TEST_HL_RootFinder_y(1./* init_a*/, 2. /*init_b*/, 1000 /*maxFunctionInvocations*/, 32 /*digitTolerance*/, 9.2 /*y*/);

    HL_TEST_HL_RootFinder_y(2./* init_a*/, 4. /*init_b*/, 4 /*maxFunctionInvocations*/, 32 /*digitTolerance*/, 9.2 /*y*/);


} // end HL_TEST_HL_RootFinder


} // end namespace HL_Math
} //end namespace HorizonLib
