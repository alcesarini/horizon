/**
FILE NAME= hl_anagraphics.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140614
*/

#include <hl/instruments/anagraphics/hl_anagraphics.h>


HL_SERIALIZATION_CLASS_EXPORT_GUID(HLAN::HL_Anagraphics);

namespace HorizonLib
{
namespace HL_Instruments
{
namespace HL_Anagraphics
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Anagraphics
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_Anagraphics::HL_Anagraphics()
{

    classDefaultInit();



} // end HL_Anagraphics

//------------------------------------------------------------------------------------------------------

HL_Anagraphics::~HL_Anagraphics()
{} // end ~HL_Anagraphics


//------------------------------------------------------------------------------------------------------

void HL_Anagraphics::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_Anagraphics::descriptionImpl(std::ostream & os) const
{
    os << "HL_Anagraphics=" << anagraphicsTypeString() << ":\n";

    Descriptable::descriptionImpl(os);




} // end descriptionImpl

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Anagraphics: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------





} // end namespace HL_Anagraphics
} // end namespace HL_Instruments
} //end namespace HorizonLib
