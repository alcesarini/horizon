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
// class HL_Function
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20131227
 \brief Base class for functions.
 */
class HL_Function : public virtual HLSER::HL_Serializable, public virtual Descriptable
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
        HL_SER(nDim_);
    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_Function();

    virtual ~HL_Function();
    //@}

    /**
     Public class interface
     */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS_O(HLS/*ClassVariableType*/, nDim/*classVariableName_no_underscore*/)
    ;

    virtual HLR operator()(const VEC::const_iterator & b, const VEC::const_iterator & e) const=0;
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
    HLS nDim_;
    //@}

}
; // end class HL_Function

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Function: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

}// end namespace HL_Math
} //end namespace HorizonLib

#endif // _hl_function_h_
