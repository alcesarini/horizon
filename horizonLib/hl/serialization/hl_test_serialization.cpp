/**
FILE NAME= hl_test_serialization.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131206
*/
#include <hl/serialization/hl_test_serialization.h>

/*
Necessary in this position, if within the software design 
these classes will be serialized only through base class pointers.
Notice that it is necessary just once.
*/
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLSER::HL_TEST_Obj_A);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLSER::HL_TEST_Obj_B);

namespace HorizonLib
{
namespace HL_Serialization
{



std::vector<char/*, boost::pool_allocator<char>*/> allo(HLI nb)
{

    std::vector<char/*, boost::pool_allocator<char>*/> v(nb);

    return v;
}

//------------------------------------------------------------------------------------------------------

void HL_TEST_HL_Obj_serialization()
{

    std::cout << "start memory alloc test??" << std::endl;
    std::getchar();

    HL_GET_LOGGER(true/*addTimer*/);

    HL_LOG(HLLOG::HL_severity_level_notification, "STD VECTOR ALLOC start");


    std::vector<std::vector<char/*, boost::pool_allocator<char>*/> > vs;

    for(HLI i=0;i<15000000;i++)
    {

        HLR x = std::sin(i*1.);

        HLI nb = (HLI) (x*20);

        if(nb<=0)
            nb = -nb+1;

        vs.push_back(allo(nb));





    } // end x


    std::cout << "end memory alloc test??" << std::endl;
    std::getchar();

    HL_LOG(HLLOG::HL_severity_level_normal, "STD VECTOR ALLOC end");



    return;


    BSP<HLOBJ::HL_Obj> b(new HL_TEST_Obj_B);

    HL_DYN_SHARED_PTR_CAST(HL_TEST_Obj_B, bCasted, b);

    bCasted->b_int_=76;

    bCasted->a_string_="prova";


    BSP<HLOBJ::HL_Obj> a(new HL_TEST_Obj_A);

    HL_DYN_SHARED_PTR_CAST(HL_TEST_Obj_A, aCasted, a);

    aCasted->a_string_="pipo";

    std::vector<HLR> xVect(3000);

    HLI i=0;
    BOOST_FOREACH(HLR & x, xVect)
    {
        x=i*2.5;
        i++;
    } // end x


    HL_TEST_Obj_A aObject;
    aObject.a_string_="pipo2";


    HL_TEST_Obj_B bObject;
    bObject.a_string_="pipo3";
    bObject.b_int_=111;

    HLR doubleTest = 34342.545454;

    //----------------------------------------------


    HLSER::HL_CoreSerializableObj csObj;

    csObj.oa() << b;
    csObj.oa() << a;
    csObj.oa() << xVect;
    csObj.oa() << aObject;
    csObj.oa() << bObject;
    csObj.oa() << doubleTest;


    csObj.getReadyForDeserialization();

    BSP<HLOBJ::HL_Obj> bReconstructed;
    BSP<HLOBJ::HL_Obj> aReconstructed;
    std::vector<HLR> xVectReconstructed;
    HL_TEST_Obj_A aObjectReconstructed;
    HL_TEST_Obj_B bObjectReconstructed;
    HLR doubleTestReconstructed;

    csObj.ia() >> bReconstructed;
    csObj.ia() >> aReconstructed;
    csObj.ia() >> xVectReconstructed;
    csObj.ia() >> aObjectReconstructed;
    csObj.ia() >> bObjectReconstructed;
    csObj.ia() >> doubleTestReconstructed;

    //----------

    HL_DYN_SHARED_PTR_CAST(HL_TEST_Obj_B, bReconstructedCasted, bReconstructed);

    HL_SR(bReconstructedCasted->b_int_==bCasted->b_int_ &&
          bReconstructedCasted->a_string_==bCasted->a_string_);

    //----------

    HL_DYN_SHARED_PTR_CAST(HL_TEST_Obj_A, aReconstructedCasted, aReconstructed);

    HL_SR(aCasted->a_string_==aReconstructedCasted->a_string_);


    //----------
    i=0;
    BOOST_FOREACH(HLR x, xVect)
    {

        HL_SR(x==xVectReconstructed[i] );

        i++;


    } // end x


    //----------


    HL_SR(aObject.a_string_==aObjectReconstructed.a_string_);

    //----------

    HL_SR(bObject.b_int_==bObjectReconstructed.b_int_ &&
          bObject.a_string_==bObjectReconstructed.a_string_);

    //----------
    HL_SR(doubleTest==doubleTestReconstructed);

    //----------

    /*
    Ok, getting here means the tests was successful.
    */


} // end HL_TEST_HL_Obj_serialization


} // end namespace HL_Serialization
} //end namespace HorizonLib

