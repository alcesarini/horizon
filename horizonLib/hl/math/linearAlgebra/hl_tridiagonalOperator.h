/**
FILE NAME= hl_tridiagonalOperator.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140111
*/
#ifndef _hl_tridiagonalOperator_h_
#define _hl_tridiagonalOperator_h_

#include <hl/math/hl_mathUtils.h>


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

/**
\author A. Cesarini

\date 20131227

\brief Solves L*x=y, where L is a tridiagonal matrix.

Inspired by QuantLib 1.3 implementation (ql/methods/finitedifferences/tridiagonaloperator.hpp).

A tridiagonal matrix is defined by the condition: $L[i][i+j]=0 \mbox{if} j>1 \mbox{or} j<-1$.

*/
class HL_TridiagonalOperator : public virtual Descriptable
{
public:


    /**
    Constructors & destructors
    */
    //@{

    HL_TridiagonalOperator();

    virtual ~HL_TridiagonalOperator();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(VEC/*ClassVariableType*/, diagonal/*classVariableName_no_underscore*/);
    HL_CLASS_VAR_ACCESS_METHODS(VEC/*ClassVariableType*/, lowerDiagonal/*classVariableName_no_underscore*/);
    HL_CLASS_VAR_ACCESS_METHODS(VEC/*ClassVariableType*/, upperDiagonal/*classVariableName_no_underscore*/);

    /**
    To specify n_ once for all
    */
    void setDimension(HLS n);

    /**
    Sets the first L's row:
    L_diag = L[0][0]
    L_upper = L_[0][1]
    */
    void setFirstRow(HLR L_diag, HLR L_upper);

    /**
    Sets the r-th mid L's row (0<r<n_-1):

    L_lower = L[r][r-1]
    L_diag = L[r][r]
    L_upper = L_[r][r+1]
    */
    void setMidRow(HLS r, HLR L_lower, HLR L_diag, HLR L_upper);

    /**
    Sets the last L's row:
    L_lower = L[n_-1][n_-2]
    L_diag = L[n_-1][n_-1]
    */
    void setLastRow(HLR L_lower, HLR L_diag);

    HL_Disposable<VEC> solve(const VEC& rhs) const;


    void solve(const VEC& rhs, VEC& result) const;

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
    /**
    L is a n_ x n_ matrix
    */
    HLS n_;
    /**
    diagonal_.size()=n_
    lowerDiagonal_.size()=upperDiagonal_.size()=n_-1
    lowerDiagonal_[i]=L[i+1][i], i=0,...,n_-2
    upperDiagonal_[i]=L[i][i+1], i=0,...,n_-2
    */
    VEC diagonal_, lowerDiagonal_, upperDiagonal_;

    //@}


    /**
    Service class variables
    */
    //@{



    mutable VEC temp_;

    //@}


}
; // end class HL_TridiagonalOperator


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TridiagonalOperator: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


/**
Tests that HL_TridiagonalOperator behaves correctly.
*/
void HL_TEST_HL_TridiagonalOperator();


} // end namespace HL_LinearAlgebra
} // end namespace HL_Math
} //end namespace HorizonLib


#endif // _hl_tridiagonalOperator_h_
