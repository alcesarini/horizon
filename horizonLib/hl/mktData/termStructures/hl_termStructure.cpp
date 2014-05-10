/**
FILE NAME= hl_termStructure.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131213
*/
#include <hl/mktData/termStructures/hl_termStructure.h>
#include <hl/mktData/hl_mktDataCollector.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLTS::HL_TermStructure);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLTS::HL_TermStructureCode);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLTS::HL_InterpTermStructure);

namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_TermStructures
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TermStructureCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_TermStructureCode::HL_TermStructureCode()
{
    classDefaultInit();

} // end HL_TermStructureCode

//------------------------------------------------------------------------------------------------------

HL_TermStructureCode::~HL_TermStructureCode()
{} // end ~HL_TermStructureCode

//------------------------------------------------------------------------------------------------------

void HL_TermStructureCode::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

HLSTRING HL_TermStructureCode::objTypeImpl() const
{
    return "HL_TermStructureCode";
} // end objTypeImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TermStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_TermStructure::HL_TermStructure()
{

    classDefaultInit();



} // end HL_TermStructure

//------------------------------------------------------------------------------------------------------

HL_TermStructure::~HL_TermStructure()
{} // end ~HL_TermStructure


//------------------------------------------------------------------------------------------------------

void HL_TermStructure::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_TermStructure::descriptionImpl(std::ostream & os) const
{
    HL_MktData::descriptionImpl(os);

} // end descriptionImpl



//------------------------------------------------------------------------------------------------------


HLR HL_TermStructure::df(const ptime &t) const
{

    HLR yf = HLDT::act_yf(get_refTime(), t);

    HLR df = dfImpl(yf);
    return df;

} // end df

//------------------------------------------------------------------------------------------------------


HLR HL_TermStructure::dfImpl(HLR t) const
{

  HL_FAIL("not implemented");

  return HL_NULL_REAL;

} // end dfImpl



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TermStructure: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_TermStructurePtr get_TermStructurePtr(const HL_MktDataCollectorPtr & mktDataCollectorPtr, const HL_ObjCodePtr & objCodePtr)
{

    return get_mktData<HL_TermStructurePtr>(mktDataCollectorPtr, objCodePtr);

} // end get_TermStructurePtr




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterpTermStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_InterpTermStructure::HL_InterpTermStructure()
{

    classDefaultInit();



} // end HL_InterpTermStructure

//------------------------------------------------------------------------------------------------------

HL_InterpTermStructure::~HL_InterpTermStructure()
{} // end ~HL_InterpTermStructure


//------------------------------------------------------------------------------------------------------

void HL_InterpTermStructure::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_InterpTermStructure::descriptionImpl(std::ostream & os) const
{
  HL_TermStructure::descriptionImpl(os);

} // end descriptionImpl



//------------------------------------------------------------------------------------------------------


HLR HL_InterpTermStructure::dfImpl(HLR t) const
{

  HL_FAIL("not implemented");

  return HL_NULL_REAL;

} // end dfImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterpTermStructure: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




} // end namespace HL_TermStructures
} // end namespace HL_MarketData
} //end namespace HorizonLib
