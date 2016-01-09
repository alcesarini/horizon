/**
FILE NAME=he_test.cpp
LIB= HorizonExtern
ADDED BY= A. Cesarini
DATE= 20151212
*/


#include <he/test/he_test.h>



void World::set(std::string msg)
{
    this->msg = msg;
}

std::string World::greet()
{
    int x =1;

    HorizonLib::HL_Test::HL_TEST_get_int_nb(x);

    std::stringstream ss;

    ss << msg << "_ippoo_" << x;

    std::cout << "sono qui" << "\n";


    HL_GET_LOGGER(false/*addTimer*/);


    HL_LOG(HLLOG::HL_severity_level_notification, "ciao");

    return ss.str();
}




using namespace boost::python;

BOOST_PYTHON_MODULE(libhorizonExtern)
{

    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    // World
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------

    class_<World>("World")
            .def("greet", &World::greet)
            .def("set", &World::set)
            ;

    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    // HorizonLib::HL_Test::HL_A
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------

    class_<HorizonLib::HL_Test::HL_A, BSP<HorizonLib::HL_Test::HL_A> >("HL_A",init<>())
            .def("create",&HorizonLib::HL_Test::HL_A::create )
            .staticmethod("create")
            .def("hello",&HorizonLib::HL_Test::HL_A::hello)
            .def_readwrite("hl_c", &HorizonLib::HL_Test::HL_A::hl_c);

    //------------------------------------------------------------------------------------------------------


    boost::python::register_ptr_to_python< BSP<HorizonLib::HL_Test::HL_A> >();


    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    // HorizonLib::HL_Test::HL_B
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------


    class_<HorizonLib::HL_Test::HL_B, BSP<HorizonLib::HL_Test::HL_B> >("HL_B",init<HLR>())
            .def("create",&HorizonLib::HL_Test::HL_B::create )
            .staticmethod("create")
            .def("hello_b",&HorizonLib::HL_Test::HL_B::hello_b)
            .def("set_hl_a",&HorizonLib::HL_Test::HL_B::set_hl_a)
            .def("set_extraString_b",&HorizonLib::HL_Test::HL_B::set_extraString_b)
            .def("set_hl_c",&HorizonLib::HL_Test::HL_B::set_hl_c)
            ;

    //------------------------------------------------------------------------------------------------------


    boost::python::register_ptr_to_python< BSP<HorizonLib::HL_Test::HL_B> >();



    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------
    // HorizonLib::HL_Test::HL_C
    //------------------------------------------------------------------------------------------------------
    //------------------------------------------------------------------------------------------------------

    class_<HorizonLib::HL_Test::HL_C, BSP<HorizonLib::HL_Test::HL_C> >("HL_C",init<>())
            .def("create",&HorizonLib::HL_Test::HL_C::create )
            .staticmethod("create")
            .def("hello_c",&HorizonLib::HL_Test::HL_C::hello_c);

    //------------------------------------------------------------------------------------------------------


    boost::python::register_ptr_to_python< BSP<HorizonLib::HL_Test::HL_C> >();



} // end BOOST_PYTHON_MODULE


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

