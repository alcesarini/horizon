/**
FILE NAME= hl_modifier.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20150622
*/
#ifndef _hl_modifier_h_
#define _hl_modifier_h_

#include <hl/basicFiles/hl_workingIncludes.h>

namespace HorizonLib
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Modifier
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20150622
 \brief This class is a base class representing an interface to be used in order to modify an object.

 Such class should be always used to modify an object, i.e. for example a model while calibrating.
 Derived classes will specialize the interaction with the object.

 */
class HL_Modifier : public virtual HLSER::HL_Serializable, public virtual Descriptable
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
    HL_Modifier();

    virtual ~HL_Modifier();
    //@}

    /**
     Public class interface
     */
    //@{


    /**
    This is the gate to modify the object this class exists for.
    */
    virtual void modify(const VEC::const_iterator & b, const VEC::const_iterator & e) const=0;

    /**
    The expected size (i.e. e-b) of the range to be passed to method modify(..).
    */
    virtual HLS vecSize() const=0;
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
; // end class HL_Modifier

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Modifier: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_ModifierPtr BSP<HL::HL_Modifier>

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_ModifierCollection
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 \author A. Cesarini
 \date 20150622
 \brief Just adds up a certain number of modifiers.

 */
class HL_ModifierCollection : public virtual HL_Modifier
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
        HL_SERIALIZE_BASE_CLASS(HL_Modifier);

        HL_SER(vecSize_);
        HL_SER(vecSizes_);

    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_ModifierCollection();

    virtual ~HL_ModifierCollection();
    //@}

    /**
     Public class interface
     */
    //@{

    void set_modifiers(const std::vector<HL_ModifierPtr> & modifiers);


    /**
    This is the gate to modify the object this class exists for.
    */
    void modify(const VEC::const_iterator & b, const VEC::const_iterator & e) const;


    HL_CLASS_VAR_ACCESS_METHODS_O(std::vector<HL_ModifierPtr>, modifiers);



    HLS vecSize() const
    {
        return vecSize_;
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


    HLS vecSize_;

    std::vector<HLS> vecSizes_;

    std::vector<HL_ModifierPtr> modifiers_;

    //@}

}
; // end class HL_ModifierCollection

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_ModifierCollection: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



} //end namespace HorizonLib


#endif // _hl_modifier_h_
