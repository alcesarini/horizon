/**
FILE NAME=hl_basicFunctions.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140308
*/
#ifndef _hl_basicFunctions_h_
#define _hl_basicFunctions_h_

#include <hl/math/hl_function.h>

namespace HorizonLib
{
namespace HL_Math
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Ln
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20131227
 \brief Base class for functions.
 */
class HL_Ln : public virtual HL_RealFunctor
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
        HL_SERIALIZE_BASE_CLASS(HL_RealFunctor);

    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_Ln();

    virtual ~HL_Ln();
    //@}

    /**
     Public class interface
     */
    //@{
    HLR operator()(const VEC::const_iterator & b, const VEC::const_iterator & e) const
    {
      return std::log(*b);
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
; // end class HL_Ln



} // end namespace HL_Math
} //end namespace HorizonLib


#endif // _hl_basicFunctions_h_
