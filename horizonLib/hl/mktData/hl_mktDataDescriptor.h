/**
FILE NAME= hl_mktDataDescriptor.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20141229
*/
#ifndef _hl_mktDataDescriptor_h_
#define _hl_mktDataDescriptor_h_

#include <hl/mktData/hl_mktData.h>
#include <hl/mktData/termStructures/hl_termStructure.h>
#include <hl/mktData/volSurfaces/hl_volSurface.h>

namespace HorizonLib
{
namespace HL_MarketData
{





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RealData
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141229
\brief Base class to contain some anagraphics.
*/
class HL_RealData : public virtual HLSER::HL_Serializable, public virtual Descriptable
{

    /**
    -----------------------------------------------------
    Serialization
    */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS;

    template<class Archive>
    void serialize(Archive &ar, const HLS version)
    {

        HL_SER_BASE;

        HL_SER(x_);


    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_RealData();

    virtual ~HL_RealData();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS(HLR, x);


    HL_Order getOrder(const HL_RealData & realData) const;

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

    HLR x_;
    //@}

}
; // end class HL_RealData


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_RealData: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_RealDataPtr BSP<HLMD::HL_RealData>

//------------------------------------------------------------------------------------------------------

HL_DEFINE_ALL_ORDERING(HL_RealData);






//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_XY_Data
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141229
\brief Base class to contain a map x vs y.
*/
template<class X, class Y>
class HL_XY_Data : public virtual HLSER::HL_Serializable, public virtual Descriptable
{

    /**
    -----------------------------------------------------
    Serialization
    */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS;

    template<class Archive>
    void serialize(Archive &ar, const HLS version)
    {

        HL_SER_BASE;

        HL_SER(xy_);


    }
    //@} Serialization -----------------------------------

public:


    typedef std::map<X, Y> MapXY;
    /**
    Constructors & destructors
    */
    //@{

    HL_XY_Data();

    virtual ~HL_XY_Data();
    //@}


    /**
    Public class interface
    */
    //@{

    HL_CLASS_VAR_ACCESS_METHODS_O(MapXY, xy);

    MapXY & get_xy()
    {
        return xy_;
    }

    HL_Order getOrder(const HL_XY_Data & xyData) const;

    bool empty() const
    {
        return xy_.empty();
    }

    const Y & get_Y(const X & x) const
    {
        typename MapXY::const_iterator cIt = xy_.find(x);
        HL_SRE(cIt!=xy_.end(), "x key not found " << x);
        return cIt->second;
    }

    bool is_X_present(const X & x) const
    {
        typename MapXY::const_iterator cIt = xy_.find(x);
        bool present = cIt!=xy_.end();
        return present;
    }



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

    MapXY xy_;
    //@}

}
; // end class HL_XY_Data


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_XY_Data: inline implementations
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

template<class X, class Y>
inline HL_XY_Data<X, Y>::HL_XY_Data()
{

    classDefaultInit();



} // end HL_XY_Data

//------------------------------------------------------------------------------------------------------

template<class X, class Y>
inline HL_XY_Data<X, Y>::~HL_XY_Data()
{} // end ~HL_XY_Data


//------------------------------------------------------------------------------------------------------

template<class X, class Y>
inline void HL_XY_Data<X, Y>::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


template<class X, class Y>
inline void HL_XY_Data<X, Y>::descriptionImpl(std::ostream & os) const
{
    os << "HL_XY_Data:\n";

    Descriptable::descriptionImpl(os);


    //hl_fillDescriptionStream(xy_); // to be implemented if needed



} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

template<class X, class Y>
inline HL_Order HL_XY_Data<X, Y>::getOrder(const HL_XY_Data & xyData) const
{

    HL_PLAIN_ORDER_COMPARE(xy_, xyData.xy_);


} // end getOrder


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Bi_Real_Data
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141229
\brief HL_Bi_Real_Data can be used to track all the data like x vs. y, in
order, e.g., to implement some lazy behaviour.

Notice that it would be sufficient to implement the method HL_RealData::getOrder with some tolerance, in order
to take into account and appropriately neutralize machine rounding effects when trying to decide if some
input data has changed or not "to implemet the lazyness" of some procedure.
*/
typedef HL_XY_Data<HLMD::HL_RealData, HLMD::HL_RealData> HL_Bi_Real_Data;

//------------------------------------------------------------------------------------------------------

#define HL_Bi_Real_DataPtr BSP<HLMD::HL_Bi_Real_Data>

//------------------------------------------------------------------------------------------------------

HL_COMPARISON_MAP_CONTAINERS(HL_Bi_Real_Data::MapXY);

//------------------------------------------------------------------------------------------------------

HL_DEFINE_ALL_ORDERING(HL_Bi_Real_Data);


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Tri_Real_Data
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
/**
\author A. Cesarini
\date 20141229
\brief HL_Tri_Real_Data can be used to track all the data like z vs. x vs. y (for ex. maturity vs. strike vs. vol)
in order, e.g., to implement some lazy behaviour.

Notice that it would be sufficient to implement the method HL_RealData::getOrder with some tolerance, in order
to take into account and appropriately neutralize machine rounding effects when trying to decide if some
input data has changed or not "to implemet the lazyness" of some procedure.
*/
typedef HL_XY_Data<HL_RealData, HL_Bi_Real_Data> HL_Tri_Real_Data;

//------------------------------------------------------------------------------------------------------

#define HL_Tri_Real_DataPtr BSP<HLMD::HL_Tri_Real_Data>

//------------------------------------------------------------------------------------------------------

HL_COMPARISON_MAP_CONTAINERS(HL_Tri_Real_Data::MapXY);

//------------------------------------------------------------------------------------------------------

HL_DEFINE_ALL_ORDERING(HL_Tri_Real_Data);



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TermStructure_Tracker_Data
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
/**
\author A. Cesarini
\date 20141229
\brief HL_TermStructure_Tracker_Data can be used to track all the data retrived by a termstructure, in
order, e.g., to implement some lazy behaviour.

Notice that it would be sufficient to implement the method HL_RealData::getOrder with some tolerance, in order
to take into account and appropriately neutralize machine rounding effects when trying to decide if some
input data has changed or not "to implemet the lazyness" of some procedure.
*/
typedef HL_XY_Data<HL_TermStructureCodePtr, HL_Bi_Real_Data> HL_TermStructure_Tracker_Data;

//------------------------------------------------------------------------------------------------------

#define HL_TermStructure_Tracker_DataPtr BSP<HLMD::HL_TermStructure_Tracker_Data>

//------------------------------------------------------------------------------------------------------

HL_COMPARISON_MAP_CONTAINERS(HL_TermStructure_Tracker_Data::MapXY);

//------------------------------------------------------------------------------------------------------

HL_DEFINE_ALL_ORDERING(HL_TermStructure_Tracker_Data);




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_VolSurface_Tracker_Data
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
/**
\author A. Cesarini
\date 20141229
\brief HL_VolSurface_Tracker_Data can be used to track all the data retrived by a vol surface, in
order, e.g., to implement some lazy behaviour: maturity vs. strike vs. vol

Notice that it would be sufficient to implement the method HL_RealData::getOrder with some tolerance, in order
to take into account and appropriately neutralize machine rounding effects when trying to decide if some
input data has changed or not "to implemet the lazyness" of some procedure.
*/
typedef HL_XY_Data<HL_VolSurfaceCodePtr, HL_Tri_Real_Data> HL_VolSurface_Tracker_Data;

//------------------------------------------------------------------------------------------------------

#define HL_VolSurface_Tracker_DataPtr BSP<HLMD::HL_VolSurface_Tracker_Data>

//------------------------------------------------------------------------------------------------------

HL_COMPARISON_MAP_CONTAINERS(HL_VolSurface_Tracker_Data::MapXY);

//------------------------------------------------------------------------------------------------------

HL_DEFINE_ALL_ORDERING(HL_VolSurface_Tracker_Data);




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktDataTracker
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141229
\brief Base class to track market data changes in order, e.g., to implement some lazy behaviour.

Notice that it would be sufficient to implement the method HL_RealData::getOrder with some tolerance, in order
to take into account and appropriately neutralize machine rounding effects when trying to decide if some
input data has changed or not "to implemet the lazyness" of some procedure.
*/
class HL_MktDataTracker : public virtual HLSER::HL_Serializable, public virtual Descriptable
{

    /**
    -----------------------------------------------------
    Serialization
    */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS;

    template<class Archive>
    void serialize(Archive &ar, const HLS version)
    {

        HL_SER_BASE;


        HL_SER(refTime_);
        HL_SER(termStructure_Tracker_Data_);
        HL_SER(volSurface_Tracker_Data_);




    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_MktDataTracker();

    virtual ~HL_MktDataTracker();
    //@}


    /**
    Public class interface
    */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS(ptime, refTime);
    HL_CLASS_VAR_ACCESS_METHODS_O(HL_TermStructure_Tracker_DataPtr, termStructure_Tracker_Data);
    HL_CLASS_VAR_ACCESS_METHODS_O(HL_VolSurface_Tracker_DataPtr, volSurface_Tracker_Data);


    HL_Order getOrder(const HL_MktDataTracker & mktDataTracker) const;


    /**
    This is to add the data relative to a certian termStructure (determined by termStructureCode),
    concerning a certain time (t) and a certain value of the termStructure (usually the discount factor,
    but this could in principle depend on the details of the implementation).
    */
    void addTermStructurePoint(const HL_TermStructureCodePtr & termStructureCode, HLR t, HLR value) const;


    /**
    This is to add the data relative to a certian vol surface (determined by volSurfaceCode),
    concerning a certain time (t), a strike (k) and a certain value of the vol surface (usually the vol,
    but this could in principle depend on the details of the implementation).
    */
    void addVolSurfacePoint(const HL_VolSurfaceCodePtr & volSurfaceCode, HLR t, HLR k, HLR value) const;


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
    This is the first data to take into account when comparing mkt data.
    */
    ptime refTime_;

    HL_TermStructure_Tracker_DataPtr termStructure_Tracker_Data_;

    HL_VolSurface_Tracker_DataPtr volSurface_Tracker_Data_;

    //@}

}
; // end class HL_MktDataTracker


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktDataTracker: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_MktDataTrackerPtr BSP<HLMD::HL_MktDataTracker>


//------------------------------------------------------------------------------------------------------


HL_DEFINE_ALL_ORDERING(HL_MktDataTracker);


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktDataTrackerContainer
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20141230
\brief Contains a map of HL_MktDataTracker objects, indexed by a string key chosen by the class user.
We need more HL_MktDataTracker objects at the same time since one could want to monitor more
processes at the same time w.r.t. the mkt data they use.
*/
class HL_MktDataTrackerContainer : public virtual HLSER::HL_Serializable, public virtual Descriptable
{

    /**
    -----------------------------------------------------
    Serialization
    */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS;

    template<class Archive>
    void serialize(Archive &ar, const HLS version)
    {

        HL_SER_BASE;


        HL_SER(refTime_);
        HL_SER(mktDataTrackers_);




    }
    //@} Serialization -----------------------------------

public:

    typedef std::map<HLSTRING, HL_MktDataTrackerPtr> MAP_TRACKERS_TYPE;

    /**
    Constructors & destructors
    */
    //@{

    HL_MktDataTrackerContainer();

    virtual ~HL_MktDataTrackerContainer();
    //@}


    /**
    Public class interface
    */
    //@{


    HL_CLASS_VAR_ACCESS_METHODS(ptime, refTime);


    /**
    This is the method to be called when one wants to add a new tracker, i.e. when one wants
    to monitor the market data used by some task, e.g. in order to implement the lazyness of the
    computations of such task w.r.t. the data used by the task itself.

    The idea is like this:

    1) before starting the task call this method with a string tag identfying the task
    2) start collecting the mkt data necessary for the task
    (in the meanwhile the tracker will record such mkt data)
    3) decide if the task has already been performed before with the same mkt data or not.
    (if yes, you just don't need to perform it again, since you may already have the results cached somewhere)
    (if no, do the heavy computations of the task and possibly chache the results for later reuse.)
    */
    void addMktDataTracker(const HLSTRING & trackerKey);

    /**
    Returns the HL_MktDataTrackerPtr with the given trackerKey and removes it from  mktDataTrackers_.
    Throws if trackerKey is not found.
    */
    HL_MktDataTrackerPtr popMktDataTracker(const HLSTRING & trackerKey);

    /**
    Erase sthe HL_MktDataTrackerPtr with the given trackerKey from  mktDataTrackers_.
    Throws if trackerKey is not found.
    */
    void eraseMktDataTracker(const HLSTRING & trackerKey);

    void addTermStructurePoint(const HL_TermStructureCodePtr & termStructureCode, HLR t, HLR value) const;


    void addVolSurfacePoint(const HL_VolSurfaceCodePtr & volSurfaceCode, HLR t, HLR k, HLR value) const;


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
    This is the first data to take into account when comparing mkt data.
    */
    ptime refTime_;


    MAP_TRACKERS_TYPE mktDataTrackers_;


    //@}

}
; // end class HL_MktDataTrackerContainer


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktDataTrackerContainer: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_MktDataTrackerContainerPtr BSP<HLMD::HL_MktDataTrackerContainer>







} // end namespace HL_MarketData
} //end namespace HorizonLib


#endif // _hl_mktDataDescriptor_h_
