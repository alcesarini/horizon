/**
FILE NAME=he_test.h
LIB= HorizonExtern
ADDED BY= A. Cesarini
DATE= 20151212
*/
#ifndef _he_test_h_
#define _he_test_h_


#include <boost/python.hpp>

#include <he/basicFiles/he_defines.h>

#include <hl/test/hl_test.h>

struct World
{
    void set(std::string msg);
    std::string greet();
    std::string msg;
};



namespace HorizonExtern
{





} //end namespace HorizonExtern


#endif // _he_test_h_
