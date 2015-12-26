/**
 FILE NAME=hl_function.h
 LIB= HorizonLib
 ADDED BY= A. Cesarini
 DATE= 20131227
 */
#ifndef _hl_function_h_
#define _hl_function_h_

#include <hl/basicFiles/hl_workingIncludes.h>

namespace HorizonLib
{
namespace HL_Math
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RealFunction
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20131227
 \brief Base class for functions.
 */
class HL_RealFunction : public virtual HLSER::HL_Serializable, public virtual Descriptable
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
        HL_SER(domainDim_);
        HL_SER(coDomainDim_);

    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_RealFunction();

    virtual ~HL_RealFunction();
    //@}

    /**
     Public class interface
     */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS_O(HLS/*ClassVariableType*/, domainDim/*classVariableName_no_underscore*/);
    HL_CLASS_VAR_ACCESS_METHODS_O(HLS/*ClassVariableType*/, coDomainDim/*classVariableName_no_underscore*/);

    //virtual HLR operator()(const VEC::const_iterator & b, const VEC::const_iterator & e) const=0;

    /**
    Returns an iterator to the beginning of the result range.

    This is he onlòy interface that must be implemented for sure.
    */
    virtual const VEC::const_iterator & value_n_m(const VEC::const_iterator & b, const VEC::const_iterator & e) const=0;

    /**
    This interface is present but it could be forbidden (this is useful)
    */
    virtual HLR value_n_1(const VEC::const_iterator & b, const VEC::const_iterator & e) const
    {
        HL_UNEXPECTED_FUNCTION_CALL;
    }
    /**
    This interface is present but it could be forbidden (this is useful)
    */
    virtual const VEC::const_iterator &  value_1_m(HLR x) const
    {

        HL_UNEXPECTED_FUNCTION_CALL;

    }
    /**
    This interface is present but it could be forbidden (this is useful)
    */
    virtual HLR operator()(HLR x) const
    {
        HL_UNEXPECTED_FUNCTION_CALL;

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
    HLS domainDim_;

    HLS coDomainDim_;

    //@}

}
; // end class HL_RealFunction

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RealFunction: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_RealFunctionPtr BSP<HLMA::HL_RealFunction>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RealFunction_n_1
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20131227
 \brief Specialization of HL_RealFunction for domainDim_>=1, coDomainDim_=1.
 */
class HL_RealFunction_n_1 : public virtual HL_RealFunction
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
        HL_SERIALIZE_BASE_CLASS(HL_RealFunction);

    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_RealFunction_n_1();

    virtual ~HL_RealFunction_n_1();
    //@}

    /**
     Public class interface
     */
    //@{


    /**
    Returns an iterator to the beginning of the result range.
    */
    const VEC::const_iterator & value_n_m(const VEC::const_iterator & b, const VEC::const_iterator & e) const
    {
        service_y_vec_[0] = value_n_1(b, e);
        return service_y_vec_cBegin_;

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
    mutable VEC service_y_vec_;

    mutable VEC::const_iterator service_y_vec_cBegin_;

    //@}

}
; // end class HL_RealFunction_n_1

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RealFunction_n_1: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RealFunction_1_m
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20131227
 \brief Specialization of HL_RealFunction for domainDim_=1, coDomainDim_>=1.
 */
class HL_RealFunction_1_m : public virtual HL_RealFunction
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
        HL_SERIALIZE_BASE_CLASS(HL_RealFunction);

    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_RealFunction_1_m();

    virtual ~HL_RealFunction_1_m();
    //@}

    /**
     Public class interface
     */
    //@{


    /**
    Returns an iterator to the beginning of the result range.
    */
    const VEC::const_iterator & value_n_m(const VEC::const_iterator & b, const VEC::const_iterator & e) const
    {

        return value_1_m(*b);
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

}
; // end class HL_RealFunction_1_m

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RealFunction_1_m: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RealFunctor
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20131227
 \brief Specialization of HL_RealFunction for domainDim_=1, coDomainDim_=1.
 */
class HL_RealFunctor : public virtual HL_RealFunction_n_1, public virtual HL_RealFunction_1_m
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
        HL_SERIALIZE_BASE_CLASS(HL_RealFunction); // not of the two bases

    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_RealFunctor();

    virtual ~HL_RealFunctor();
    //@}

    /**
     Public class interface
     */
    //@{


    /**
    Returns an iterator to the beginning of the result range.
    */
    const VEC::const_iterator & value_n_m(const VEC::const_iterator & b, const VEC::const_iterator & e) const
    {
        return HL_RealFunction_n_1::value_n_m(b, e);

    }


    HLR value_n_1(const VEC::const_iterator & b, const VEC::const_iterator & e) const
    {
        return (*this)(*b);
    }


    const VEC::const_iterator & value_1_m(HLR x) const
    {
        service_x_vec_[0]=x;
        return value_n_m(service_x_vec_.begin(), service_x_vec_.end());
    }

    virtual HLR operator()(HLR x) const=0;

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
     mutable VEC service_x_vec_;
    //@}

}
; // end class HL_RealFunctor

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RealFunctor: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_RealFunctorPtr BSP<HLMA::HL_RealFunctor>






}// end namespace HL_Math
} //end namespace HorizonLib

#endif // _hl_function_h_
