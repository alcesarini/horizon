/**
FILE NAME= hl_volSurface.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131227
*/
#include <hl/mktData/volSurfaces/hl_volSurface.h>
#include <hl/mktData/hl_mktDataCollector.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLVOL::HL_VolSurface);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLVOL::HL_VolSurfaceCode);

namespace HorizonLib
{
	namespace HL_MarketData
	{
		namespace HL_VolSurfaces
		{

			//------------------------------------------------------------------------------------------------------
			//------------------------------------------------------------------------------------------------------
			// class HL_VolSurfaceCode
			//------------------------------------------------------------------------------------------------------
			//------------------------------------------------------------------------------------------------------


			HL_VolSurfaceCode::HL_VolSurfaceCode()
			{
				classDefaultInit();

			} // end HL_VolSurfaceCode

			//------------------------------------------------------------------------------------------------------

			HL_VolSurfaceCode::~HL_VolSurfaceCode()
			{
			} // end ~HL_VolSurfaceCode

			//------------------------------------------------------------------------------------------------------

			void HL_VolSurfaceCode::classDefaultInit()
			{

			} // end classDefaultInit

			//------------------------------------------------------------------------------------------------------

			HLSTRING HL_VolSurfaceCode::objTypeImpl() const
			{
				return "HL_VolSurfaceCode";
			} // end objTypeImpl


			//------------------------------------------------------------------------------------------------------
			//------------------------------------------------------------------------------------------------------
			// class HL_VolSurface
			//------------------------------------------------------------------------------------------------------
			//------------------------------------------------------------------------------------------------------


			HL_VolSurface::HL_VolSurface()
			{

				classDefaultInit();



			} // end HL_VolSurface

			//------------------------------------------------------------------------------------------------------

			HL_VolSurface::~HL_VolSurface()
			{
			} // end ~HL_VolSurface
						
			
			//------------------------------------------------------------------------------------------------------

			void HL_VolSurface::classDefaultInit()
			{

			} // end classDefaultInit

			//------------------------------------------------------------------------------------------------------


			void HL_VolSurface::descriptionImpl(std::ostream & os) const
			{
				HL_MktData::descriptionImpl(os);
			
			} // end descriptionImpl



			//------------------------------------------------------------------------------------------------------

			HLR HL_VolSurface::vol(const ptime &t, HLR k) const
			{

				HLR yf = HLDT::act_yf(get_refTime(), t);

				return 0;

			} // end vol

			//------------------------------------------------------------------------------------------------------
			//------------------------------------------------------------------------------------------------------
			// class HL_VolSurface: defines, utils
			//------------------------------------------------------------------------------------------------------
			//------------------------------------------------------------------------------------------------------

			
			HL_VolSurfacePtr get_VolSurfacePtr(const HL_MktDataCollectorPtr & mktDataCollectorPtr, const HL_ObjCodePtr & objCodePtr)
			{

				return get_mktData<HL_VolSurfacePtr>(mktDataCollectorPtr, objCodePtr);
				
			} // end get_VolSurfacePtr


			//------------------------------------------------------------------------------------------------------

			void HL_TEST_HL_VolSurface()
			{
				HL_MktDataCollectorPtr mktDataCollectorPtr;

				HL_VolSurfaceCodePtr code;

				ptime t;
				HLR k=0;
				HL_VolSurfacePtr vol = get_VolSurfacePtr(mktDataCollectorPtr, code);
				HLR v1 = vol->vol(t, k);
			
				date d;

				HLR v2 = vol->vol(d, k);


			} // end HL_TEST_HL_VolSurface

		} // end namespace HL_VolSurfaces
	} // end namespace HL_MarketData
} //end namespace HorizonLib