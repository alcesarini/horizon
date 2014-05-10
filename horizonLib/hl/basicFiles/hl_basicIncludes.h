/**
FILE NAME= hl_basicIncludes.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131117
 */
//#pragma warning(disable:4996)


#ifndef _hl_basicIncludes_h_
#define _hl_basicIncludes_h_


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
/*
 * Use pragmas to disable warnings from boost files.
 * We place this pragma here, since it is referred to a warning that is generated from template classes,
 * hence it is generated when we instantiates classes deriving from template boost classes.
 * Hence it is generated in our code: this is the reason why the pragma disabling the warning
 * is to be place here and applied to our whole library, differentlyh from
 * the pragma warning disabling we placed in file hl_boostIncludes.h, that concern
 * only boost code (hence we use #pragma GCC diagnostic push to save the diagnostic configuration
 * prtesent before entering the file and then restore the very same diagnostic configuration when
 * exiting the file).
 */
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
#pragma GCC diagnostic ignored "-Wunused-parameter" // disable diagnostic

#include <hl/basicFiles/hl_boostIncludes.h>


//#include <ql/quantlib.hpp>
//#include <iostream>


#include <hl/basicFiles/hl_auto_link.hpp>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// primitive types definition
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HLR double
#define HLF float
#define HLL long
#define HLI int
#define HLS unsigned HLI
#define HLSTRING std::string
#define HLMIDX std::vector<HLS>

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// namespaces definiton
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define QL QuantLib
#define HL HorizonLib
#define HLINS HL::HL_Instruments
#define HLCTRS HL::HL_Containers
#define HLENV HL::HL_Enviroment
#define HLLOG HL::HL_Logging
#define HLEXC HL::HL_Exceptions
#define HLOBJ HL::HL_Object
#define HLSER HL::HL_Serialization
#define HLMD HL::HL_MarketData
#define HLTS HLMD::HL_TermStructures
#define HLVOL HLMD::HL_VolSurfaces
#define HLDT HL::HL_DateTime
#define HLCAL HLDT::HL_Calendars
#define HLCCY HL::HL_Currencies
#define HLUND HLMD::HL_Underlyings
#define HLIR HLUND::HL_InterestRates
#define HLMA HL::HL_Math
#define HLINTP HLMA::HL_Interpolation
#define HLLA HLMA::HL_LinearAlgebra




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// numeri limits
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



// limits used as such (code taken from Quantlib 1.3)
#define HL_MIN_INTEGER         ((std::numeric_limits<HLI>::min)())
#define HL_MAX_INTEGER         ((std::numeric_limits<HLI>::max)())
#define HL_MIN_REAL           -((std::numeric_limits<HLR>::max)())
#define HL_MAX_REAL            ((std::numeric_limits<HLR>::max)())
#define HL_MIN_POSITIVE_REAL   ((std::numeric_limits<HLR>::min)())
#define HL_EPSILON             ((std::numeric_limits<HLR>::epsilon)())
// specific values---these should fit into any Integer or Real (code taken from Quantlib 1.3)
#define HL_NULL_INTEGER        ((std::numeric_limits<HLI>::max)())
#define HL_NULL_REAL           ((std::numeric_limits<HLF>::max)())

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Useful defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_DYN_PTR_CAST_OPERATION(outPtr, inPtr, dynCastingOperator, DynCastingOperatorArg) \
                outPtr = dynCastingOperator<DynCastingOperatorArg> (inPtr); \
                HL_SRE(outPtr, HLSTRING(#dynCastingOperator) + " unable to cast to type " + HLSTRING(#DynCastingOperatorArg));

//------------------------------------------------------------------------------------------------------

#define HL_DYN_C_PTR_CAST_OPERATION(OutPtrType, outPtr, inPtr) \
                HL_DYN_PTR_CAST_OPERATION(outPtr, inPtr, dynamic_cast, OutPtrType)

//------------------------------------------------------------------------------------------------------

#define HL_DYN_C_PTR_CAST(OutPtrType, outPtr, inPtr) \
		OutPtrType outPtr;\
		HL_DYN_C_PTR_CAST_OPERATION(OutPtrType, outPtr, inPtr)

//------------------------------------------------------------------------------------------------------


#define HL_DYN_SHARED_PTR_CAST_OPERATION(OutPtrType, outPtr, inPtr) \
                HL_DYN_PTR_CAST_OPERATION(outPtr, inPtr, boost::dynamic_pointer_cast, OutPtrType)


//------------------------------------------------------------------------------------------------------


#define HL_DYN_SHARED_PTR_CAST(OutPtrType, outPtr, inPtr) \
		BSP<OutPtrType> outPtr;\
		HL_DYN_SHARED_PTR_CAST_OPERATION(OutPtrType, outPtr, inPtr)


//------------------------------------------------------------------------------------------------------

#define HL_CLASS_VAR_ACCESS_METHODS_I(ClassVariableType, classVariableName_no_underscore) \
		void set_##classVariableName_no_underscore(const ClassVariableType & x)\
		{\
	classVariableName_no_underscore##_=x;\
		}

//------------------------------------------------------------------------------------------------------

#define HL_CLASS_VAR_ACCESS_METHODS_O(ClassVariableType, classVariableName_no_underscore) \
		const ClassVariableType & get_##classVariableName_no_underscore() const\
		{\
	return classVariableName_no_underscore##_;\
		}


//------------------------------------------------------------------------------------------------------
#define HL_CLASS_VAR_ACCESS_METHODS(ClassVariableType, classVariableName_no_underscore) \
		HL_CLASS_VAR_ACCESS_METHODS_I(ClassVariableType, classVariableName_no_underscore) \
		HL_CLASS_VAR_ACCESS_METHODS_O(ClassVariableType, classVariableName_no_underscore)


//------------------------------------------------------------------------------------------------------

#define HL_ENUM_CHECK(EnumTypeName, enumValue) \
		HL_SRE_ID(enumValue>EnumTypeName##_InvalidMin && enumValue<EnumTypeName##_InvalidMax,\
				HLSTRING(#enumValue) << "= " << enumValue);

//------------------------------------------------------------------------------------------------------

#define HL_ENUM_CHECK_LARGE(EnumTypeName, enumValue) \
		HL_SRE_ID(enumValue>=EnumTypeName##_InvalidMin && enumValue<=EnumTypeName##_InvalidMax,\
				HLSTRING(#enumValue) << "= " << enumValue);

//------------------------------------------------------------------------------------------------------

#define HL_SUCCESSFULL_TEST(testMethodName) \
    {\
    HL_GET_LOGGER(false/*addTimer*/);\
    HL_LOG(HLLOG::HL_severity_level_notification, "\n" << std::string(#testMethodName) <<  ": ok\n");\
    }




#endif // _hl_basicIncludes_h_
