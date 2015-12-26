/**
FILE NAME=hl_comparisonChecks.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140105
*/
#ifndef _hl_comparisonChecks_h_
#define _hl_comparisonChecks_h_


#include <hl/exceptions/hl_exceptions.h>

namespace HorizonLib
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// hl_equal_floats
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_DEFAULT_NB_EPSILON 42

//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20140105
\brief Floating point equality (42 is assumeed as in Quantlib 1.3).
*/
inline bool hl_equal_floats(HLR x, HLR y, HLS n)
{

    // Deals with +infinity and -infinity representations etc.
    if (x == y)
        return true;


    HLR diff = std::fabs(x-y), tolerance = n * HL_EPSILON;

    if (x * y == 0.0) // x or y = 0.0
        return diff < (tolerance * tolerance);

    bool eq = (diff <= tolerance*std::fabs(x)) || (diff <= tolerance*std::fabs(y));


    return eq;

} // end hl_equal_floats


//------------------------------------------------------------------------------------------------------

#define HL_REQ_FLOATS_RELATION(x, y, n, relation, requiredRelation, message) \
    HL_SRE(hl_equal_floats(x, y, n)==relation, \
    "x=" << x << ", y=" << y << ", (x-y)=" << (x-y) << ", HL_EPSILON=" << HL_EPSILON << ", n=" << n << \
    ", tolerance=n*HL_EPSILON*max(|x|,|y|)=" << (n*HL_EPSILON*std::max(std::fabs(x), std::fabs(y))) <<\
    ", x=" << #x << ", y=" << #y << ", (the required relation " << requiredRelation << " is violated), " << message);

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_REQ_EQUAL_FLOATS_N_E(x, y, n, message) HL_REQ_FLOATS_RELATION(x, y, n, true, "[x==y]", message)

//------------------------------------------------------------------------------------------------------

#define HL_REQ_EQUAL_FLOATS_N(x, y, n) HL_REQ_EQUAL_FLOATS_N_E(x, y, n, "")

//------------------------------------------------------------------------------------------------------

#define HL_REQ_EQUAL_FLOATS_E(x, y, message) HL_REQ_EQUAL_FLOATS_N_E(x, y, HL_DEFAULT_NB_EPSILON, message)

//------------------------------------------------------------------------------------------------------

#define HL_REQ_EQUAL_FLOATS(x, y) HL_REQ_EQUAL_FLOATS_E(x, y, "")

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_REQ_NOT_EQUAL_FLOATS_N_E(x, y, n, message) HL_REQ_FLOATS_RELATION(x, y, n, false, "[x!=y]", message)

//------------------------------------------------------------------------------------------------------

#define HL_REQ_NOT_EQUAL_FLOATS_N(x, y, n) HL_REQ_NOT_EQUAL_FLOATS_N_E(x, y, n, "")

//------------------------------------------------------------------------------------------------------

#define HL_REQ_NOT_EQUAL_FLOATS_E(x, y, message) HL_REQ_NOT_EQUAL_FLOATS_N_E(x, y, HL_DEFAULT_NB_EPSILON, message)

//------------------------------------------------------------------------------------------------------

#define HL_REQ_NOT_EQUAL_FLOATS(x, y) HL_REQ_NOT_EQUAL_FLOATS_E(x, y, "")






} //end namespace HorizonLib


#endif // _hl_comparisonChecks_h_
