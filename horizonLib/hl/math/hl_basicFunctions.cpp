/**
FILE NAME= hl_basicFunctions.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140308
*/
#include <hl/math/hl_basicFunctions.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLMA::HL_Ln);


namespace HorizonLib
{
namespace HL_Math
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Ln
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_Ln::HL_Ln()
{

    classDefaultInit();



} // end HL_Ln

//------------------------------------------------------------------------------------------------------

HL_Ln::~HL_Ln()
{} // end ~HL_Ln


//------------------------------------------------------------------------------------------------------

void HL_Ln::classDefaultInit()
{
    nDim_=1;
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_Ln::descriptionImpl(std::ostream & os) const
{
    HL_Function::descriptionImpl(os);

    os << "Ln function";

} // end descriptionImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Ln: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

} // end namespace HL_Math
} //end namespace HorizonLib
