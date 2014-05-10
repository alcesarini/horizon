/**
FILE NAME= hl_test_serialization.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131206
*/
#ifndef _hl_test_serialization_h_
#define _hl_test_serialization_h_


#include <hl/object/hl_object.h>

namespace HorizonLib
{
namespace HL_Serialization
{


//------------------------------------------------------------------------------------------------------



class HL_TEST_Obj_A : public virtual HLOBJ::HL_Obj
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
        HL_SER(a_string_);
    }
    //@} Serialization -----------------------------------

public:

    HL_TEST_Obj_A()
    {}

protected:

    HLSTRING objTypeImpl() const
    {
        return "HL_TEST_Obj_A";
    }

public:


    HLSTRING a_string_;

}
; // end HL_TEST_Obj_A


//------------------------------------------------------------------------------------------------------


class HL_TEST_Obj_B : public virtual HL_TEST_Obj_A
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

        HL_SERIALIZE_BASE_CLASS(HL_TEST_Obj_A);
        HL_SER(b_int_);

    }
    //@} Serialization -----------------------------------

public:

    HL_TEST_Obj_B()
    {}

protected:

    HLSTRING objTypeImpl() const
    {
        return "HL_TEST_Obj_B";
    }

public:
    HLI b_int_;


}
;  // end class HL_TEST_Obj_B

//------------------------------------------------------------------------------------------------------


void HL_TEST_HL_Obj_serialization();


} // end namespace HL_Serialization
} //end namespace HorizonLib


#endif // _hl_test_serialization_h_
