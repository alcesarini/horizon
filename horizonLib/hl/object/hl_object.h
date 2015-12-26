/**
FILE NAME= hl_object.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131126
*/
#ifndef _hl_object_h_
#define _hl_object_h_


#include <hl/currencies/hl_ccyCode.h>

namespace HorizonLib
{
namespace HL_Object
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Obj
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131126
\brief This class is the base for external entities that are codified by a name, a type,....
*/
class HL_Obj : public virtual HLSER::HL_Serializable, public virtual Descriptable
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

        HL_SER(hl_ObjCodePtr_);


    }
    //@} Serialization -----------------------------------

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_Obj();

    virtual ~HL_Obj();
    //@}


    /**
    Public class interface
    */
    //@{
    /**
    Notice this is not virtual
    */
    HLSTRING objType() const;

   const HLSTRING & sCode() const
   {

       return hl_ObjCodePtr_->get_sCode();
   }


    virtual void set_HL_ObjCodePtr(const HL_ObjCodePtr & hl_ObjCodePtr);

    const HL_ObjCodePtr & hl_ObjCodePtr() const
    {
        return hl_ObjCodePtr_;
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
    HL_ObjCodePtr hl_ObjCodePtr_;


    //@}

private:

    /**
    Private class variables
    */
    //@{


    //@}

}
; // end class HL_Obj

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Obj:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_ObjPtr BSP<HLOBJ::HL_Obj>


//------------------------------------------------------------------------------------------------------

#define HL_SRE_SERVICE_OBJ(ExceptionClass, condition, exceptionMessage)\
    HL_SRE_SERVICE(ExceptionClass, condition, exceptionMessage << ", objType()=" << objType() << ", ObjCode=" << hl_ObjCodePtr())

//------------------------------------------------------------------------------------------------------

#define HL_SRE_OBJ(condition, exceptionMessage) \
    HL_SRE_SERVICE_OBJ(HL_IntermediateDataException, condition, exceptionMessage)

//------------------------------------------------------------------------------------------------------

#define HL_SRE_ID_OBJ(condition, exceptionMessage) \
    HL_SRE_SERVICE_OBJ(HL_InputDataException, condition, exceptionMessage)


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FinObjCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131214
\brief The base-code for financial objs.
*/

class HL_FinObjCode : public virtual HLOBJ::HL_ObjCode
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

        HL_SERIALIZE_BASE_CLASS(HLOBJ::HL_ObjCode);
        HL_SER(ccyCode_);
    }
    //@} Serialization -----------------------------------


public:


    /**
    Constructors & destructors
    */
    //@{

    HL_FinObjCode();

    virtual ~HL_FinObjCode();
    //@}


    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(HL_CcyCodePtr, ccyCode);
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


    void descriptionImpl(std::ostream & os) const;

    //@}



protected:


    /**
    Class variables
    */
    //@{

    HL_CcyCodePtr ccyCode_;
    //@}

}
; // end class HL_FinObjCode


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FinObjCode: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_FinObjCodePtr BSP<HLOBJ::HL_FinObjCode>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FinObj
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131126
\brief Specializations of HL_Obj for financial objects
FINANCIAL_EXAMPLE: a discount curve, a call option, a stock, an euribor rate, etc.. will all
be represented by classes deriving from HL_FinObj
*/
class HL_FinObj : public virtual HL_Obj
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
        HL_SERIALIZE_BASE_CLASS(HLOBJ::HL_Obj);


    }
    //@} Serialization -----------------------------------

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_FinObj();

    virtual ~HL_FinObj();
    //@}


    /**
    Public class interface
    */
    //@{



    void set_HL_ObjCodePtr(const HL_ObjCodePtr & hl_ObjCodePtr);


    const HL_CcyCodePtr & hl_CcyCode() const
    {
        return finObjCode_->get_ccyCode();
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

    /**
    A down-casted link to HL_Obj::hl_ObjCodePtr_
    */
    HL_FinObjCodePtr finObjCode_;

    //@}

private:

    /**
    Private class variables
    */
    //@{



    //@}

}
; // end class HL_FinObj

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_FinObj:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_FinObjPtr BSP<HLOBJ::HL_FinObj>




} // end namespace HL_Object
} //end namespace HorizonLib


#endif // _hl_object_h_
