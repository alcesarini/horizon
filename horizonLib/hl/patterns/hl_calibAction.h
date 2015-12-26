/**
FILE NAME= hl_calibAction.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20150627
*/
#ifndef _hl_calibAction_h_
#define _hl_calibAction_h_

#include <hl/patterns/hl_baseAction.h>
#include <hl/patterns/hl_modifier.h>
#include <hl/math/hl_function.h>
#include <hl/math/rootFinding/hl_rootFinding.h>

namespace HorizonLib
{




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CalibAction (fwd declaration)
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

class HL_CalibAction;

//------------------------------------------------------------------------------------------------------

#define HL_CalibActionPtr BSP<HL::HL_CalibAction>

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// enum HL_TargetFunctionType
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



enum HL_TargetFunctionType
{
    HL_TargetFunctionType_InvalidMin=0,
    HL_TargetFunctionType_Fit,
    HL_TargetFunctionType_Solve,
    HL_TargetFunctionType_InvalidMax
}; // end enum HL_TargetFunctionType

//------------------------------------------------------------------------------------------------------

HL_ENUM_DESCRIPTION(
        HL_TargetFunctionType,
        "HL_TargetFunctionType_InvalidMin",
        "HL_TargetFunctionType_Fit",
        "HL_TargetFunctionType_Solve",
        "HL_TargetFunctionType_InvalidMax"
        );




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TargetFunction
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20131227
 \brief Specialization of HL_RealFunction_n_1 to be used by classes HL_CalibAction.
 */
class HL_TargetFunction : public virtual HLMA::HL_RealFunction_n_1
{

    /**
     -----------------------------------------------------
     Serialization
     */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS
    ;

    template<class Archive>
    void
    serialize(Archive &ar, const HLS version)
    {
        HL_SERIALIZE_BASE_CLASS(HL_TargetFunction);

        HL_SER(modifier_);
    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_TargetFunction();

    virtual ~HL_TargetFunction();
    //@}

    /**
     Public class interface
     */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS_O(HL_ModifierPtr, modifier);
    void set_modifier(const HL_ModifierPtr & modifier);


    HL_CLASS_VAR_ACCESS_METHODS(HL_CalibActionPtr, nestedAction);



    HLR value_n_1(const VEC::const_iterator & b, const VEC::const_iterator & e) const;

    virtual HL_TargetFunctionType get_targetFunctionType() const=0;

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


    virtual HLR computeTargetValue(const VEC::const_iterator & b, const VEC::const_iterator & e) const=0;

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


    HL_ModifierPtr modifier_;


    /**
    The nested action to be performed right after calling modifier_->modify(b, e)
    and before calling computeTargetValue (see method value_n_1(..)).
    */
    HL_CalibActionPtr nestedAction_;

    //@}

}
; // end class HL_TargetFunction

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TargetFunction: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_TargetFunctionPtr BSP<HL::HL_TargetFunction>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CalibAction
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20150627
 \brief Calibration action base class.

 This class is a base class representing a calibration action, i.e. the modification of an object
 according to a specific instance of class HL_Modifier (targetFunction_->get_modifier()) finalized
 to achieve some mathematical condition
 related to a specific mathematical function (targetFunction_), namely its minimization or
 equality to zero (in the HL_TargetFunctionType_Fit/HL_TargetFunctionType_Solve cases respectively).


 */
class HL_CalibAction : public virtual HL_Action
{

    /**
     -----------------------------------------------------
     Serialization
     */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS
    ;

    template<class Archive>
    void
    serialize(Archive &ar, const HLS version)
    {


        HL_SERIALIZE_BASE_CLASS(HL_Action);

        HL_SER(targetFunction_);

    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_CalibAction();

    virtual ~HL_CalibAction();
    //@}

    /**
     Public class interface
     */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS(HL_TargetFunctionPtr, targetFunction);


    /**
    This is the gate to modify the object this class exists for.
    */
    void go() const;

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

    virtual void goImpl() const=0;

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


    HL_TargetFunctionPtr targetFunction_;



    //@}

}
; // end class HL_CalibAction

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CalibAction: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_CalibActionPtr BSP<HL::HL_CalibAction>







//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CalibActionSolve
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20150627
 \brief Specialization of HL_CalibAction for the case of solving
 targetFunction_ to zero (i.e. "Brenting", i.e. HL_TargetFunctionType_Solve).

 */
class HL_CalibActionSolve : public virtual HL_CalibAction
{

    /**
     -----------------------------------------------------
     Serialization
     */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS
    ;

    template<class Archive>
    void
    serialize(Archive &ar, const HLS version)
    {
        HL_SERIALIZE_BASE_CLASS(HL_CalibAction);



    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_CalibActionSolve();

    virtual ~HL_CalibActionSolve();
    //@}

    /**
     Public class interface
     */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS(HL_RootFinderDataPtr, rootFinderData);

    HL_CLASS_VAR_ACCESS_METHODS(HL_RootFinderPtr, rootFinder);


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

    void goImpl() const;

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


     HL_RootFinderDataPtr rootFinderData_;

     HL_RootFinderPtr rootFinder_;

    //@}

}
; // end class HL_CalibActionSolve

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CalibActionSolve: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_CalibActionSolvePtr BSP<HL::HL_CalibActionSolve>



} //end namespace HorizonLib


#endif // _hl_calibAction_h_
