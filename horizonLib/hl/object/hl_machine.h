/**
FILE NAME= hl_machine.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131128
*/
#ifndef _hl_machine_h_
#define _hl_machine_h_


#include <hl/object/hl_object.h>


namespace HorizonLib
{
namespace HL_Object
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MachineInput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140902
\brief See comment to HL_Machine.
*/
class HL_MachineInput : public virtual HLSER::HL_Serializable, public virtual Descriptable
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


    }
    //@} Serialization -----------------------------------

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_MachineInput();

    virtual ~HL_MachineInput();
    //@}


    /**
    Public class interface
    */
    //@{

    virtual void check() const
    {

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


    //@}

private:

    /**
    Private class variables
    */
    //@{


    //@}

}
; // end class HL_MachineInput

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MachineInput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_MachineInputPtr BSP<HLOBJ::HL_MachineInput>

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MachineInputKey
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140920
\brief  See comment to HL_Machine.
*/
class HL_MachineInputKey : public virtual HLSER::HL_Serializable, public virtual Descriptable
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


    }
    //@} Serialization -----------------------------------

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_MachineInputKey();

    virtual ~HL_MachineInputKey();
    //@}


    /**
    Public class interface
    */
    //@{
    /**
     * To have ordering defined
    */
    virtual HL_Order getOrder(const HL_MachineInputKey & machineInputKey) const=0;

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


    //@}

private:

    /**
    Private class variables
    */
    //@{


    //@}

}
; // end class HL_MachineInputKey

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MachineInputKey:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_MachineInputKeyPtr BSP<HLOBJ::HL_MachineInputKey>

//------------------------------------------------------------------------------------------------------

HL_DEFINE_ALL_ORDERING(HL_MachineInputKey);



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MachineOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140902
\brief See comment to HL_Machine.
*/
class HL_MachineOutput : public virtual HLSER::HL_Serializable, public virtual Descriptable
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


    }
    //@} Serialization -----------------------------------

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_MachineOutput();

    virtual ~HL_MachineOutput();
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
    void descriptionImpl(std::ostream & os) const;
    //@}

protected:


    /**
    Class variables
    */
    //@{


    //@}

private:

    /**
    Private class variables
    */
    //@{


    //@}

}
; // end class HL_MachineOutput

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MachineOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_MachineOutputPtr BSP<HLOBJ::HL_MachineOutput>




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Machine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 * \author A. Cesarini
 *  \date 20131128
 * \brief
 * The purpose of this class is to transform one instance of HL_MachineInput-data (let's name it "I") in one
 * instance of HL_MachineOuputdata (let's name it "O").
 * Notice that I is the unique data that is used to produce O.
 * Notice that HL_MachineInput must NOT have an ordering defined, but the HL_Machine is able to build
 * an instance of HL_MachineInputKey, say "i", out of I, that should have an ordering defined, and that is used to lazily
 * store a map of output results against input conditions.
 *
 * FINANCIAL_EXAMPLE: suppose that we have to compute a d-date swap rate (O) from a discount curve
 * having HL_ObjCode "X_code".
 * Then, in practice the swap rate will be computed from the discount factors of the curve.
 * Suppose then that we are sure, within the execution enviroment we are interested in, that the discount factors of
 * the "X_code" curve will never change.
 * In this case, it will hence be sufficinet to get i=X_code, even if the swap rate has been in practice constructed
 * using the discount factors (i.e. the number that are the actual input of the math formula yield to the swap rate).
 * In other words, since we know for some external reasons that rates are fixed, we only have to remind which
 * curve gave rise to the swap rate (and not the actual values of its discounts).
 * In this example, we will then recognize as I=whole discount curve (instance of HL_MachineInputPtr), while
 * i=X_code (instance of HL_MachineInputKey).
*/
class HL_Machine : public virtual Descriptable
{
public:


    /**
            \name Constructors & destructors
            */
    //@{

    HL_Machine(){}

    virtual ~HL_Machine(){}
    //@}


    /**
            \name Public class interface
            */
    //@{

    /**
    Referring to the class comment, this method produces O.
    This is then the possibly computation-intensive method.
    */
    const HL_MachineOutputPtr & doJob() const;


    /**
    The method doJob() will work by taking this input class as input.
    The user could set it any number of times, or perhaps the user could set it once
    but change it any number of times he/she wants, since the object pointed by input_
    is not pointed as a const object.
    */
    HL_CLASS_VAR_ACCESS_METHODS(HL_MachineInputPtr, input);

    /**
            Resets all the track record of past jobs.
            */
    void resetOutputs()
    {
        outputs_.clear();
    }
    //@}


protected:



    /**
     * \name Additional implementations
    */
    //@{
    /**
     * Default initialization of the class vars.
    */
    void classDefaultInit(){}


    virtual void buildInputKey(const HL_MachineInputPtr & input,
                               HL_MachineInputKeyPtr & machineInputKey) const;


    virtual HL_MachineOutputPtr doJobImpl() const=0;


    virtual void cleanDisposableData() const;

    //@}


    /**
     * \name Implementations of base class methods
    */
    //@{
    void descriptionImpl(std::ostream & os) const
    {
        os << "HL_Machine\n";
    }

    //@}

protected:


    /**
    \name Class variables
    */
    //@{
    /**
     * The work of the machine has produced these outputs, associated to the corresponding inputs
     * in the sense explained in the class comment.
     * This stored data will be used to avoid redoing jobs when asking for the HL_MachineInputPtr-instances
     * that have already been processed in the past.
    */
    mutable std::map<HL_MachineInputKeyPtr, HL_MachineOutputPtr> outputs_;




    //@}

protected:

    /**
    Disposable to mean that this variable are temporary, i.e. destroyed after computations
    have been completed.
    Every derived class of HL_Machine has its own disposable data in order to
    have derived-type shared ptrs to input and input key classes and also according to its need
    of temporary variables to accomplish its tasks.
    Derived-type shared ptrs are useful since they have the right interface to access input and
    inputKey data that are specific to the computations that the intermediate class
    is supposed to perform.
    */
    struct MachineDisposableData
    {

        //@{


        HL_MachineInputKeyPtr inputKey;
        //@}

    }; // end struct MachineDisposableData

    mutable MachineDisposableData machineDisposableData_;


    HL_MachineInputPtr input_;

}; // end class HL_Machine



} // end namespace HL_Object
} //end namespace HorizonLib


#endif // _hl_machine_h_
