/**
FILE NAME=he_test.cpp
LIB= HorizonExtern
ADDED BY= A. Cesarini
DATE= 20151212
*/

#include <hl/test/hl_test.h>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// ext_HE_TEST_INT_EXTERN_LINK
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
extern "C"
{

extern void ext_HE_TEST_INT_EXTERN_LINK(int * pInt)
{

    HorizonLib::HL_Test::HL_TEST_get_int_nb((*pInt));




} // end ext_HE_TEST_INT_EXTERN_LINK


}

namespace HorizonExtern
{



} //end namespace HorizonExtern

