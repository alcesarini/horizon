/**
FILE NAME= hl_descriptable.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131218
*/
#ifndef _hl_descriptable_h_
#define _hl_descriptable_h_

#include <hl/basicFiles/hl_basicIncludes.h>
#include <hl/exceptions/hl_exceptions.h>


namespace HorizonLib
{


	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	// class Descriptable
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------

	/**
	\author A. Cesarini
	\date 20131216
	\brief Base class for classes that implement a method "description"
	*/

	class Descriptable
	{
	public:


		/**
		Constructors & destructors
		*/
		//@{

		Descriptable();

		virtual ~Descriptable();
		//@}


		/**
		Public class interface
		*/
		//@{
		/** 
		Interface to directly get a string from description(std::ostream & os ).
		*/
		HLSTRING description() const;

		//@}


	protected:

		friend std::ostream& operator<<(std::ostream& os, const Descriptable& descriptable);

		friend std::ostream& operator<<(std::ostream& os, const BSP<Descriptable>& descriptable);
		/**
		Additional implementations
		*/
		//@{
		/**
		Default initialization of the class vars.
		*/
		void classDefaultInit();


		/** 
		Meant to be a "human-readble" description of the object.
		Derived classes should add their own part of the description to the one of the base class in 
		a pyramid scheme.

		This method is not virtual the *impl is.
		*/
		void description(std::ostream & os) const;

		virtual void descriptionImpl(std::ostream & os) const;
		//@}

		/**
		Implementations of base class methods
		*/
		//@{

		//@}

	protected:


		/**
		Class variables
		*/
		//@{

		//@}

	}; // end class Descriptable



	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------
	// class Descriptable:: defines, typedefs, functions
	//------------------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------------------


	std::ostream& operator<<(std::ostream& os, const Descriptable& descriptable);

	//------------------------------------------------------------------------------------------------------

	std::ostream& operator<<(std::ostream& os, const BSP<Descriptable>& descriptable);

	//------------------------------------------------------------------------------------------------------

#define HL_DES_START "[* "
#define HL_DES_END " *]"

	//------------------------------------------------------------------------------------------------------

	inline void hl_fillDescriptionStreamHeaderService(std::ostream & os, const HLSTRING & dataNameString)
	{
		os << HL_DES_START << dataNameString << ": "; 

	} // end hl_fillDescriptionStreamHeaderService

	//------------------------------------------------------------------------------------------------------

#define hl_fillDescriptionStreamHeader(dataName) hl_fillDescriptionStreamHeaderService(os, HLSTRING(#dataName))

	//------------------------------------------------------------------------------------------------------

#define hl_fillDescriptionStreamCloser() os << HL_DES_END << "\n"; 

	//------------------------------------------------------------------------------------------------------

#define hl_fillDescriptionStream(data) \
	hl_fillDescriptionStreamHeader(data); \
	os << data;\
	hl_fillDescriptionStreamCloser();


	//------------------------------------------------------------------------------------------------------

#define HL_GET_ENUM_STRING(EnumTypeName, ...) \
	static HLSTRING descrs_##EnumTypeName [] = {__VA_ARGS__};\
	inline HLSTRING getEnumString(EnumTypeName enumValue)\
	{\
	HL_ENUM_CHECK_LARGE(EnumTypeName, enumValue);\
	HLI idx = (enumValue - EnumTypeName##_InvalidMin);\
	HLI enumSize = sizeof(descrs_##EnumTypeName) / sizeof(HLSTRING);\
	HL_SRE(enumSize==(EnumTypeName##_InvalidMax - EnumTypeName##_InvalidMin +1), "enumSize=" << enumSize)\
	HL_SRE(idx<enumSize, "idx=" << idx << ", enumSize=" << enumSize);\
	return (descrs_##EnumTypeName[idx]);\
	}

	//------------------------------------------------------------------------------------------------------

#define HL_ENUM_DESCRIPTION(EnumTypeName, ...) \
	HL_GET_ENUM_STRING(EnumTypeName, __VA_ARGS__)\
	inline void enumDescription(std::ostream & os, EnumTypeName enumValue, const HLSTRING & varName)\
	{\
	hl_fillDescriptionStreamHeaderService(os, varName);\
	os << getEnumString(enumValue);\
	hl_fillDescriptionStreamCloser();\
	}
	//------------------------------------------------------------------------------------------------------

#define HL_DESCRIBE_ENUM(os, enumVariable) enumDescription(os, enumVariable, HLSTRING(#enumVariable));

	//------------------------------------------------------------------------------------------------------

} //end namespace HorizonLib


#endif // _hl_descriptable_h_
