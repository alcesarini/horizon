/**
FILE NAME= hl_baseAction.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20151105
*/
#ifndef _hl_baseAction_h_
#define _hl_baseAction_h_

#include <hl/basicFiles/hl_workingIncludes.h>


namespace HorizonLib
{







//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Action
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20150627
 \brief Base class for actions with no result caching (differently from HL_Machine)
 */
class HL_Action : public virtual HLSER::HL_Serializable, public virtual Descriptable
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
        HL_SER_BASE;


    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_Action();

    virtual ~HL_Action();
    //@}

    /**
     Public class interface
     */
    //@{




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




    //@}

}
; // end class HL_Action

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Action: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_ActionPtr BSP<HL::HL_Action>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_ActionSequence
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20150627
 \brief Just adds up a certain number of Actions.

 */
class HL_ActionSequence : public virtual HL_Action
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

        HL_SER(actions_);

    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_ActionSequence();

    virtual ~HL_ActionSequence();
    //@}

    /**
     Public class interface
     */
    //@{




    HL_CLASS_VAR_ACCESS_METHODS(std::vector<HL_ActionPtr>, actions);


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


    std::vector<HL_ActionPtr> actions_;

    //@}

}
; // end class HL_ActionSequence

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_ActionSequence: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_ActionSequencePtr BSP<HL::HL_ActionSequence>



} //end namespace HorizonLib


#endif // _hl_baseAction_h_
