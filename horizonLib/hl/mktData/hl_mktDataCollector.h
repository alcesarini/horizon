/**
FILE NAME= hl_mktDataCollector.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131226
*/
#ifndef _hl_mktDataCollector_h_
#define _hl_mktDataCollector_h_

#include <hl/mktData/hl_mktData.h>



namespace HorizonLib
{
namespace HL_MarketData
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktDataCollector
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131226
\brief The complete set of mkt data, all contained in this class, and also synchronous, i.e.
all associatyed to the exact same time instant (that is HL_MktDataCollector::refTime_).
*/
class HL_MktDataCollector : public virtual HLSER::HL_Serializable, public virtual Descriptable
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
        HL_SER(mktDataMap_);



    }
    //@} Serialization -----------------------------------

public:


    typedef std::map<HL_ObjCodePtr, HL_MktDataPtr> MktDataCollectionType;


    /**
    Constructors & destructors
    */
    //@{

    HL_MktDataCollector();

    virtual ~HL_MktDataCollector();
    //@}


    /**
    Public class interface
    */
    //@{

    template<class MktDataTypePtr>
    MktDataTypePtr get_mktData(const HL_ObjCodePtr & objCodePtr) const
    {

        HL_PNN(objCodePtr);

        MktDataCollectionType::const_iterator cIt = mktDataMap_.find(objCodePtr);

        HL_SRE(cIt!=mktDataMap_.end(), ", missing objCodePtr=" << objCodePtr);

        HL_DYN_SHARED_PTR_CAST(typename MktDataTypePtr::element_type, outMktData, cIt->second);

        return outMktData;

    } // end get_mktData


    void set_refTime(const ptime &refTime);


    const ptime &get_refTime() const
    {
        return refTime_;
    }

    date get_refDate() const
    {
        return get_refTime().date();
    }

    /**
    This method should be the only way to add elements to mktDataMap_, apart
    when serializing. This method ensures that the HL_MktData::mktDataCollectorWeakPtr_
    will be properly set in such a way that each instance of HL_MktData will have a link
    to the (unique) HL_MktDataCollector instance it is hosted in.
    */
    static void addMktData(const HL_MktDataPtr & mktDataPtr, const HL_MktDataCollectorPtr & mktDataCollectorPtr);

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



    //@}

private:

    /**
    Private class variables
    */
    //@{
    /**
    This is the date/time at which this object has been created.
    */
    MktDataCollectionType mktDataMap_;
    ptime refTime_;
    //@}

}
; // end class HL_MktDataCollector


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktDataCollector: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

template <class MktDataTypePtr>
inline MktDataTypePtr get_mktData(const HL_MktDataCollectorPtr & mktDataCollectorPtr, const HL_ObjCodePtr & objCodePtr)
{
    HL_PNN(mktDataCollectorPtr);
    return mktDataCollectorPtr->get_mktData<MktDataTypePtr>(objCodePtr);
} // end get_mktData



} // end namespace HL_MarketData
} //end namespace HorizonLib


#endif // _hl_mktDataCollector_h_
