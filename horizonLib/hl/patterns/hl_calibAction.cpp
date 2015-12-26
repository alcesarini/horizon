/**
FILE NAME= hl_calibAction.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20150627
*/

#include <hl/patterns/hl_calibAction.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HL::HL_TargetFunction);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HL::HL_CalibAction);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HL::HL_CalibActionSolve);


namespace HorizonLib
{





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TargetFunction
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_TargetFunction::HL_TargetFunction()
{

    classDefaultInit();



} // end HL_TargetFunction

//------------------------------------------------------------------------------------------------------

HL_TargetFunction::~HL_TargetFunction()
{
} // end ~HL_TargetFunction


//------------------------------------------------------------------------------------------------------

void HL_TargetFunction::classDefaultInit()
{

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_TargetFunction::descriptionImpl(std::ostream & os) const
{

    os << "HL_TargetFunction:\n";

    HL_RealFunction_n_1::descriptionImpl(os);


    hl_fillDescriptionStream(modifier_);

    HL_DESCRIBE_ENUM(os, get_targetFunctionType());

    hl_fillDescriptionStream(nestedAction_);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_TargetFunction::set_modifier(const HL_ModifierPtr & modifier)
{
    modifier_=modifier;
    HL_PNN(modifier_);
    domainDim_ = modifier_->vecSize();

} // end set_modifier


//------------------------------------------------------------------------------------------------------

HLR HL_TargetFunction::value_n_1(const VEC::const_iterator & b, const VEC::const_iterator & e) const
{

    modifier_->modify(b, e);


    if(nestedAction_)
        nestedAction_->go();


    return computeTargetValue(b, e);

} // end value_n_1



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TargetFunction: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CalibAction
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CalibAction::HL_CalibAction()
{

    classDefaultInit();



} // end HL_CalibAction

//------------------------------------------------------------------------------------------------------

HL_CalibAction::~HL_CalibAction()
{
} // end ~HL_CalibAction


//------------------------------------------------------------------------------------------------------

void HL_CalibAction::classDefaultInit()
{

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_CalibAction::descriptionImpl(std::ostream & os) const
{

    os << "HL_CalibAction:\n";

    Descriptable::descriptionImpl(os);

    if(targetFunction_){
        hl_fillDescriptionStream(targetFunction_);
    }else{
        os << "null targetFunction_";
    }

} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

void HL_CalibAction::go() const
{


    goImpl();

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CalibAction: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CalibActionSolve
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CalibActionSolve::HL_CalibActionSolve()
{

    classDefaultInit();



} // end HL_CalibActionSolve

//------------------------------------------------------------------------------------------------------

HL_CalibActionSolve::~HL_CalibActionSolve()
{
} // end ~HL_CalibActionSolve


//------------------------------------------------------------------------------------------------------

void HL_CalibActionSolve::classDefaultInit()
{


} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_CalibActionSolve::descriptionImpl(std::ostream & os) const
{

    os << "HL_CalibActionSolve:\n";

    HL_CalibAction::descriptionImpl(os);


} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

void HL_CalibActionSolve::goImpl() const
{

    HL_PNN(targetFunction_);

    HL_SR(targetFunction_->get_targetFunctionType()==HL_TargetFunctionType_Solve);

    /*
    Otherwise a solve would not be possible.
    */
    HL_SR(targetFunction_->get_domainDim()==1);


    HL_PNN(rootFinderData_);

    HL_PNN(rootFinder_);

    rootFinder_->set_rootFinderData(rootFinderData_);


    HLS actualNbFunctionCalls=0;
    HLR solution;
    HLMA::HL_RootFindingResultType rootFindingResultType;

    rootFinder_->findSolution(targetFunction_,
                              solution,
                              actualNbFunctionCalls,
                              rootFindingResultType);


    /* Final call to be sure the solution is actually set and used */
    targetFunction_->operator ()(solution);

} // end modify


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CalibActionSolve: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




} //end namespace HorizonLib
