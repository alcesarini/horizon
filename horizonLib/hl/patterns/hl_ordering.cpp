/**
FILE NAME= hl_ordering.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131130
*/
#include <hl/patterns/hl_ordering.h>


namespace HorizonLib
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_ordering
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

struct A
{

    virtual ~A(){}

    virtual HL_Order getOrder(const A & a) const
    {
        HL_UNEXPECTED_FUNCTION_CALL;
    }


}
; // end struct A

//------------------------------------------------------------------------------------------------------


struct B : public virtual A
{

    HLI b;

    virtual HL_Order getOrder(const A & a) const
    {
        HL_DYN_C_PTR_CAST(const B*, casted, &a);

        //const B* casted = dynamic_cast<const B*>(&a);
        //HL_PNN(casted);

        if(b<casted->b)
            return HL_Order_1_Less_2;
        if(b>casted->b)
            return HL_Order_1_Greater_2;
        return HL_Order_1_Eq_2;
    }

}
; // end struct B

//------------------------------------------------------------------------------------------------------


struct C : public virtual B
{

    HLI c;

    virtual HL_Order getOrder(const A & a) const
    {

        HL_DYN_C_PTR_CAST(const C*, casted, &a);
        //const C* casted = dynamic_cast<const C*>(&a);
        //HL_PNN(casted);

        if(c<casted->c)
            return HL_Order_1_Less_2;
        if(c>casted->c)
            return HL_Order_1_Greater_2;

        return HL_Order_1_Eq_2;
    }

}
; // end struct C


//------------------------------------------------------------------------------------------------------

struct D : public virtual B
{

    HL_Order getOrder(const A & a) const
    {
        return HL_Order_InvalidMin;
    }

}
; // end struct D

//------------------------------------------------------------------------------------------------------

HL_DEFINE_ALL_ORDERING(A);

//------------------------------------------------------------------------------------------------------

void HL_TEST_ordering()
{

    HL_TRY
    {

        BSP<A> a(new A);
        BSP<B> b(new B);
        BSP<C> c(new C);

        BSP<A> d(new D);

        //HL_DYN_SHARED_PTR_CAST(C, dcSharedPtr, d);

        //HL_DYN_SHARED_PTR_CAST(B, dbSharedPtr, d);

        //HL_DYN_C_PTR_CAST(const C*, dcPtr, d.get());




        const std::type_info & t_A = typeid(A);
        const std::type_info & t_B = typeid(B);
        const std::type_info & t_C = typeid(C);


        BSP<A> Ab = boost::dynamic_pointer_cast<A>(b);
        BSP<A> Ac = boost::dynamic_pointer_cast<A>(c);


        if(t_A.before(t_B))
    {

        /*
        cannot compare share_ptr pf different types since boost comparison would apply instead of HL ones
        The 2 objects will be compared as A-types
        */
        HL_SR( (*a)<(*b));
            /*
            here a and b are of the same types (A) hence we can compare them as shared_ptrs
            */
            HL_SR( a<Ab);

        }
        else
        {

            HL_SR( (*a)>(*b));
            HL_SR( a>Ab);

        }

        if(t_A.before(t_C))
    {

        HL_SR( (*a)<(*c));
            HL_SR( a<Ac);

        }
        else
        {

            HL_SR( (*a)>(*c));
            HL_SR( a>Ac);

        }

        if(t_B.before(t_C))
    {

        HL_SR( (*b)<(*c));
            HL_SR( Ab<Ac);

        }
        else
        {

            HL_SR( (*b)>(*c));
            HL_SR( Ab>Ac);

        }

        BSP<B> bPrime(new B);
        BSP<A> AbPrime = boost::dynamic_pointer_cast<A>(bPrime);

        b->b=9;
        bPrime->b=10;
        /*
        comparison betweeb B-shared_ptrs is not defined, hence we dereference objs to call our comparison
        */
        if(b< bPrime)
        HLI x=8;

        HL_SR( (*b)< (*bPrime));
        /*
        comparison betweeb A-shared_ptrs is defined, hence we use it
        */
        HL_SR( Ab<AbPrime);

        bPrime->b=8;

        HL_SR(  (*b)> (*bPrime));
        HL_SR( Ab>AbPrime);

        bPrime->b=9;

        HL_SR(  (*b)== (*bPrime));
        HL_SR( Ab==AbPrime);


        //-----------


        BSP<C> cPrime(new C);
        BSP<A> AcPrime = boost::dynamic_pointer_cast<A>(cPrime);

        c->c=0;
        cPrime->c=10;

        HL_SR(  (*c)< (*cPrime));
        HL_SR( Ac<AcPrime);

        cPrime->c=-1;

        HL_SR(  (*c)> (*cPrime));
        HL_SR( Ac>AcPrime);

        cPrime->c=0;

        HL_SR(  (*c)== (*cPrime));
        HL_SR(  (*c)>= (*cPrime));
        HL_SR(  (*c)<= (*cPrime));

        HL_SR( Ac==AcPrime);
        HL_SR( Ac>=AcPrime);
        HL_SR( Ac<=AcPrime);

    }
    HL_CATCH;
} // end HL_TEST_ordering


//------------------------------------------------------------------------------------------------------

void HL_TEST_defines()
{

    HL_TRY
    {

        std::vector<HLR> vect(4, 0);
        vect[1] =1;
        vect[2] =2;
        vect[3] =3;

        HL_REQ_IS_ORDERED_L(vect);

        vect[2] =3;

        HL_REQ_IS_ORDERED_LE(vect);

        HL_REQ_IS_ORDERED_L(vect);
    }
    HL_CATCH;

    //------------------------------------------------------------------------------------------------------
    HL_TRY
    {

        std::vector<HLI> vect(4, 0);
        vect[1] =1;
        vect[2] =2;
        vect[3] =3;

        HL_REQ_RANGE_IS_ORDERED_L(vect.begin(), vect.end(), vect);

        vect[2] =3;

        HL_REQ_RANGE_IS_ORDERED_LE(vect.begin(), vect.end(), vect);

        HL_REQ_RANGE_IS_ORDERED_L(vect.begin(), vect.end(), vect);
    }
    HL_CATCH;

    //------------------------------------------------------------------------------------------------------
    HL_TRY
    {

        std::vector<HLR> vect(4, 3);
        vect[1] =2;
        vect[2] =1;
        vect[3] =0;

        HL_REQ_IS_ORDERED_G(vect);

        vect[2] =0;

        HL_REQ_IS_ORDERED_GE(vect);

        HL_REQ_IS_ORDERED_G(vect);
    }
    HL_CATCH;

    //------------------------------------------------------------------------------------------------------
    HL_TRY
    {

        std::vector<HLSTRING> vect(4, "z");
        vect[1] ="p";
        vect[2] ="g";
        vect[3] ="b";

        HL_REQ_RANGE_IS_ORDERED_G(vect.begin(), vect.end(), vect);

        vect[1] ="g";

        HL_REQ_RANGE_IS_ORDERED_GE(vect.begin(), vect.end(), vect);

        HL_REQ_RANGE_IS_ORDERED_G(vect.begin(), vect.end(), vect);
    }
    HL_CATCH;


} // end HL_TEST_defines

} //end namespace HorizonLib
