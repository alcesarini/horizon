/**
FILE NAME= hl_mktDataDescriptor.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20141229
*/
#include <hl/mktData/hl_mktDataDescriptor.h>


HL_SERIALIZATION_CLASS_EXPORT_GUID(HLMD::HL_RealData);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLMD::HL_Bi_Real_Data);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLMD::HL_Tri_Real_Data);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLMD::HL_TermStructure_Tracker_Data);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLMD::HL_VolSurface_Tracker_Data);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLMD::HL_MktDataTracker);



namespace HorizonLib
{
namespace HL_MarketData
{



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RealData
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_RealData::HL_RealData()
{

    classDefaultInit();



} // end HL_RealData

//------------------------------------------------------------------------------------------------------

HL_RealData::~HL_RealData()
{} // end ~HL_RealData


//------------------------------------------------------------------------------------------------------

void HL_RealData::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_RealData::descriptionImpl(std::ostream & os) const
{
    os << "HL_RealData:\n";

    Descriptable::descriptionImpl(os);

    hl_fillDescriptionStream(x_);



} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

HL_Order HL_RealData::getOrder(const HL_RealData & realData) const
{

    /*
    Set here some tolerance if needed
    */
    HL_PLAIN_ORDER_COMPARE(x_, realData.x_);


} // end getOrder

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RealData: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------








//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktDataTracker
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_MktDataTracker::HL_MktDataTracker()
{

    classDefaultInit();



} // end HL_MktDataTracker

//------------------------------------------------------------------------------------------------------

HL_MktDataTracker::~HL_MktDataTracker()
{} // end ~HL_MktDataTracker


//------------------------------------------------------------------------------------------------------

void HL_MktDataTracker::classDefaultInit()
{

    termStructure_Tracker_Data_.reset(new HL_TermStructure_Tracker_Data);
    volSurface_Tracker_Data_.reset(new HL_VolSurface_Tracker_Data);

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_MktDataTracker::descriptionImpl(std::ostream & os) const
{
    os << "HL_MktDataTracker:\n";

    Descriptable::descriptionImpl(os);


    hl_fillDescriptionStream(refTime_);
    hl_fillDescriptionStream(termStructure_Tracker_Data_);
    hl_fillDescriptionStream(volSurface_Tracker_Data_);


} // end descriptionImpl


//------------------------------------------------------------------------------------------------------


HL_Order HL_MktDataTracker::getOrder(const HL_MktDataTracker & mktDataTracker) const
{




    HL_SRE(refTime_!=ptime(), "forgot to set refTime_");

    HL_PLAIN_ORDER_COMPARE(refTime_, mktDataTracker.refTime_);
    HL_PLAIN_ORDER_COMPARE(termStructure_Tracker_Data_, mktDataTracker.termStructure_Tracker_Data_);
    HL_PLAIN_ORDER_COMPARE(volSurface_Tracker_Data_, mktDataTracker.volSurface_Tracker_Data_);



} // end getOrder

//------------------------------------------------------------------------------------------------------


void HL_MktDataTracker::addTermStructurePoint(const HL_TermStructureCodePtr & termStructureCode,
                                              HLR t,
                                              HLR value) const
{

    HL_TermStructure_Tracker_Data::MapXY & tsCodeVsBiRealMap =termStructure_Tracker_Data_->get_xy();


    HL_Bi_Real_Data & bi_Real_Data = tsCodeVsBiRealMap[termStructureCode];


    HL_Bi_Real_Data::MapXY & tVsValueMap = bi_Real_Data.get_xy();

    HL_RealData t_rd;
    t_rd.set_x(t);


    bool alreadyExists;
    HL_RealData & value_rd = HL_mapFind(tVsValueMap, t_rd, alreadyExists);

    if(alreadyExists){

        HL_RealData value_test_rd;
        value_test_rd.set_x(value);

        HL_SRE(value_test_rd==value_rd, "value_test_rd=" << value_test_rd
               << ", value_rd=" << value_rd);

    }else{

        value_rd.set_x(value);

    } // end if..else..




} // end addTermStructurePoint


//------------------------------------------------------------------------------------------------------


void HL_MktDataTracker::addVolSurfacePoint(const HL_VolSurfaceCodePtr & volSurfaceCode, HLR t, HLR k, HLR value) const
{

    HL_VolSurface_Tracker_Data::MapXY & volSurfaceCodeVsTriRealMap =volSurface_Tracker_Data_->get_xy();


    HL_Tri_Real_Data & tri_Real_Data = volSurfaceCodeVsTriRealMap[volSurfaceCode];


    HL_Tri_Real_Data::MapXY & tVskVsValueMap = tri_Real_Data.get_xy();

    HL_RealData t_rd;
    t_rd.set_x(t);


    HL_Bi_Real_Data::MapXY & kVsValueMap = tVskVsValueMap[t_rd].get_xy();


    HL_RealData k_rd;
    k_rd.set_x(k);


    bool alreadyExists;
    HL_RealData & value_rd = HL_mapFind(kVsValueMap, k_rd, alreadyExists);

    if(alreadyExists){

        HL_RealData value_test_rd;
        value_test_rd.set_x(value);

        HL_SRE(value_test_rd==value_rd, "value_test_rd=" << value_test_rd
               << ", value_rd=" << value_rd);

    }else{

        value_rd.set_x(value);

    } // end if..else..



} // end addVolSurfacePoint



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktDataTracker: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------






//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktDataTrackerContainer
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_MktDataTrackerContainer::HL_MktDataTrackerContainer()
{

    classDefaultInit();



} // end HL_MktDataTrackerContainer

//------------------------------------------------------------------------------------------------------

HL_MktDataTrackerContainer::~HL_MktDataTrackerContainer()
{} // end ~HL_MktDataTrackerContainer


//------------------------------------------------------------------------------------------------------

void HL_MktDataTrackerContainer::classDefaultInit()
{


} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_MktDataTrackerContainer::descriptionImpl(std::ostream & os) const
{
    os << "HL_MktDataTrackerContainer:\n";

    Descriptable::descriptionImpl(os);


    hl_fillDescriptionStream(refTime_);
    hl_fillDescriptionStream(mktDataTrackers_);


} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_MktDataTrackerContainer::addMktDataTracker(const HLSTRING & trackerKey)
{

    bool alreadyExists;
    HL_MktDataTrackerPtr & mktDataTracker = HL_mapFind(mktDataTrackers_, trackerKey, alreadyExists);

    HL_SRE(!alreadyExists, "trackerKey used twice: " << trackerKey);

    mktDataTracker.reset(new HL_MktDataTracker);

    mktDataTracker->set_refTime(refTime_);

} // end addMktDataTracker

//------------------------------------------------------------------------------------------------------

HL_MktDataTrackerPtr HL_MktDataTrackerContainer::popMktDataTracker(const HLSTRING & trackerKey)
{

    MAP_TRACKERS_TYPE::iterator it = mktDataTrackers_.find(trackerKey);


    HL_SRE(it!=mktDataTrackers_.end(), "trackerKey not found: " << trackerKey);

    HL_MktDataTrackerPtr mktDataTracker = it->second;

    // erase trackerKey and the corresponding object from mktDataTrackers_

    mktDataTrackers_.erase(it);

    return mktDataTracker;

} // end popMktDataTracker

//------------------------------------------------------------------------------------------------------

void HL_MktDataTrackerContainer::eraseMktDataTracker(const HLSTRING & trackerKey)
{

    HL_MktDataTrackerPtr mktDataTracker = popMktDataTracker(trackerKey);

} // end eraseMktDataTracker

//------------------------------------------------------------------------------------------------------

void HL_MktDataTrackerContainer::addTermStructurePoint(const HL_TermStructureCodePtr & termStructureCode,
                                                       HLR t,
                                                       HLR value) const
{


    BOOST_FOREACH(const MAP_TRACKERS_TYPE::value_type & mktDataTracker, mktDataTrackers_)
    {


        mktDataTracker.second->addTermStructurePoint(termStructureCode, t, value);


    } // end for mktDataTracker



} // end addTermStructurePoint

//------------------------------------------------------------------------------------------------------


void HL_MktDataTrackerContainer::addVolSurfacePoint(const HL_VolSurfaceCodePtr & volSurfaceCode, HLR t, HLR k, HLR value) const
{



    BOOST_FOREACH(const MAP_TRACKERS_TYPE::value_type & mktDataTracker, mktDataTrackers_)
    {


        mktDataTracker.second->addVolSurfacePoint(volSurfaceCode, t, k, value);


    } // end for mktDataTracker


} // end addVolSurfacePoint


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktDataTrackerContainer: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------











//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HL_TEST_HL_TermStructure_Tracker_Data
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



int HL_TEST_HL_TermStructure_Tracker_Data()
{

    {
        HL_Bi_Real_Data x, y;

        if(x<y && y>=x)
            return 3777;
    }

    {
        HL_Tri_Real_Data x, y;

        if(x<y && y>=x)
            return 3777;
    }

    {
        HL_TermStructure_Tracker_Data x, y;

        if(x<y && y>=x)
            return 3777;
    }

    {
        HL_VolSurface_Tracker_Data x, y;

        if(x<y && y>=x)
            return 3777;
    }


    {
        HL_MktDataTracker x, y;

        if(x<y && y>=x)
            return 3777;
    }



    return 5;

} // end HL_TEST_HL_TermStructure_Tracker_Data











} // end namespace HL_MarketData
} //end namespace HorizonLib
