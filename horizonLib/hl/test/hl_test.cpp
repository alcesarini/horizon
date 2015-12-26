/**
FILE NAME= hl_test.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20151212
*/


#include <hl/test/hl_test.h>



namespace HorizonLib
{
namespace HL_Test
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_FIRST_EXTERN_LINK
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


//std::string HL_TEST_FIRST_EXTERN_LINK_get_sample_string()
//{

//    return "hello, this comes from horizonLib!!";

//} // end HL_TEST_FIRST_EXTERN_LINK_get_sample_string

//------------------------------------------------------------------------------------------------------

void HL_TEST_get_int_nb(int & y)
{
    VEC x(3);
    x[0]=1.1;
    x[1]=4.1;
    x[2]=5.1;

    int a=0;
    for(HLS i=0;i<x.size();i++)
        a += (HLI)(x[i]);

    //HL_SR(a==10);

    y += a;
} // end HL_TEST_get_int_nb

} // end namespace HL_Test
} //end namespace HorizonLib
