/**
FILE NAME= hl_tridiagonalOperator.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140111
*/
#include <hl/math/linearAlgebra/hl_tridiagonalOperator.h>


namespace HorizonLib
{
namespace HL_Math
{
namespace HL_LinearAlgebra
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TridiagonalOperator
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_TridiagonalOperator::HL_TridiagonalOperator()
{

    classDefaultInit();



} // end HL_TridiagonalOperator

//------------------------------------------------------------------------------------------------------

HL_TridiagonalOperator::~HL_TridiagonalOperator()
{} // end ~HL_TridiagonalOperator


//------------------------------------------------------------------------------------------------------

void HL_TridiagonalOperator::classDefaultInit()
{
    n_=0;
} // end classDefaultInit


//------------------------------------------------------------------------------------------------------

void HL_TridiagonalOperator::setDimension(HLS n)
{
    n_=n;

    HL_SR(n_>0);

    diagonal_.resize(n_);
    lowerDiagonal_.resize(n_-1);
    upperDiagonal_.resize(n_-1);
    temp_.resize(n_);

} // end setDimension

//------------------------------------------------------------------------------------------------------

void HL_TridiagonalOperator::setFirstRow(HLR L_diag, HLR L_upper)
{

    HL_SR(n_>1);

    diagonal_[0]=L_diag;
    upperDiagonal_[0]=L_upper;

} // end setFirstRow

//------------------------------------------------------------------------------------------------------

void HL_TridiagonalOperator::setMidRow(HLS r, HLR L_lower, HLR L_diag, HLR L_upper)
{

    HL_SR(n_>1);
    HL_SRE(r>0 && r<n_, "r=" << r << ", n_=" << n_);

    lowerDiagonal_[r-1]=L_lower;
    diagonal_[r]=L_diag;
    upperDiagonal_[r]=L_upper;

} // end setMidRow

//------------------------------------------------------------------------------------------------------

void HL_TridiagonalOperator::setLastRow(HLR L_lower, HLR L_diag)
{

    HL_SR(n_>1);

    lowerDiagonal_[n_-2]=L_lower;
    diagonal_[n_-1]=L_diag;

} // end setLastRow

//------------------------------------------------------------------------------------------------------

HL_Disposable<VEC> HL_TridiagonalOperator::solve(const VEC& rhs) const
{

    VEC result(n_);
    solve(rhs, result);

    return result;

} // end solve

//------------------------------------------------------------------------------------------------------

void HL_TridiagonalOperator::solve(const VEC& rhs, VEC& result) const
{

    HL_SR(n_>0);

    HL_SRE(n_==diagonal_.size() &&
           (n_-1)==lowerDiagonal_.size() &&
           (n_-1)==upperDiagonal_.size() &&
           n_==result.size() &&
           n_==rhs.size(),
           "n_=" << n_ << ", diagonal_.size()=" << diagonal_.size() <<
           ", lowerDiagonal_.size()=" << lowerDiagonal_.size() << ", upperDiagonal_.size()=" << upperDiagonal_.size() <<
           ", result.size()=" << result.size() << ", rhs.size()=" << rhs.size());

    HLR bet = diagonal_[0];

    HL_REQ_NOT_EQUAL_FLOATS_E(bet, 0., "row=" << 0);

    result[0] = rhs[0]/bet;

    if(n_==1)
        return;

    for (HLS r=1; r<=n_-1; ++r)
    {
        temp_[r] = upperDiagonal_[r-1]/bet;

        bet = diagonal_[r]-lowerDiagonal_[r-1]*temp_[r];

        HL_REQ_NOT_EQUAL_FLOATS_E(bet, 0., "row=" << r);

        result[r] = (rhs[r] - lowerDiagonal_[r-1]*result[r-1])/bet;

    } // end for r

    for (HLS r=n_-2; r>0; --r)
        result[r] -= temp_[r+1]*result[r+1];

    result[0] -= temp_[1]*result[1];

} // end solve


//------------------------------------------------------------------------------------------------------

void HL_TridiagonalOperator::descriptionImpl(std::ostream & os) const
{
    Descriptable::descriptionImpl(os);

} // end descriptionImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TridiagonalOperator: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


void HL_TEST_HL_TridiagonalOperator()
{


    HLS n=30;

    HL_TridiagonalOperator to;

    to.setDimension(n);


    to.setFirstRow(190. /*L_diag*/, 78. /*L_upper*/);

    for(HLS r=1;r<n-1;++r)
    {

        to.setMidRow(r, .7/*L_lower*/, 5./*L_diag*/, 2./*L_upper*/);


    } // end for r

    to.setLastRow(1./* L_lower*/, 3./* L_diag*/);


    // produces randomness out of thin air
    boost::random::mt19937 rng;
    // see pseudo-random number generators
    boost::random::uniform_int_distribution<> cent(1, 10000);
    // distribution that maps to 1..10000
    // see random number distributions

    const VEC &diagonal= to.get_diagonal();
    const VEC &lowerDiagonal = to.get_lowerDiagonal();
    const VEC &upperDiagonal = to.get_upperDiagonal();



    for(HLS trial=0;trial<100;++trial)
    {
        VEC x(n);


        BOOST_FOREACH(HLR &x_r, x)
        {
            x_r = cent(rng);

        } // end for x_r

        // y = L*x
        VEC y(n);

        for(HLS r=0;r<n;r++)
        {
            HLR &y_r = y[r];

            y_r = diagonal[r]*x[r];

            if(r<n-1)
            {
                y_r+= upperDiagonal[r]*x[r+1];
            }


            if(r>0)
            {
                y_r+= lowerDiagonal[r-1]*x[r-1];
            }


        } // end for r

        HLS r=0;

        VEC xReconstructed = to.solve(y);


        BOOST_FOREACH(HLR x_r, x)
        {

            HL_REQ_EQUAL_FLOATS_N(x_r, xReconstructed[r], 1000);

            r++;
        } // end for x_r


    } // end for trial

    HL_SUCCESSFULL_TEST(HL_TEST_HL_TridiagonalOperator);



} // end HL_TEST_HL_TridiagonalOperator

} // end namespace HL_LinearAlgebra
} // end namespace HL_Math
} //end namespace HorizonLib
