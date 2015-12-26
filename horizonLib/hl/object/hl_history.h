/**
FILE NAME= hl_history.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131221
*/
#ifndef _hl_history_h_
#define _hl_history_h_


#include <hl/object/hl_object.h>



namespace HorizonLib
{
namespace HL_Object
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_History
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131216
\brief History of fixings.
*/
template <class TIME_TYPE, class FIXING_TYPE>
class HL_History : public virtual HLSER::HL_Serializable, public Descriptable
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

        HL_SER(hl_ObjCodePtr_);
        HL_SER(histories_);
        HL_SER(refTime_);


    }
    //@} Serialization -----------------------------------


public:

    typedef TIME_TYPE TimeType;
    typedef FIXING_TYPE FixingType;
    typedef typename std::map<TimeType, FixingType> HistType;
    /**
    The string is a tag to recognize one history from another.
    */
    typedef typename std::map<HLSTRING, HistType> HistoryCollectionType;

    /**
    Constructors & destructors
    */
    //@{

    HL_History()
    {
        classDefaultInit();
    }

    virtual ~HL_History()
    {}
    //@}


    /**
    Public class interface
    */
    //@{



    HL_CLASS_VAR_ACCESS_METHODS(HL_ObjCodePtr/*ClassVariableType*/, hl_ObjCodePtr/*classVariableName_no_underscore*/);

    HL_CLASS_VAR_ACCESS_METHODS(HistoryCollectionType/*ClassVariableType*/, histories/*classVariableName_no_underscore*/);

    HL_CLASS_VAR_ACCESS_METHODS(TimeType, refTime);


    /**
    If the return ptr is null, it means that the fixing is not found.
    The method throws an exception if the fixing is not present and time<refTime.
    If instead time==refTime, the fixing is returned (i.e. a non null pointer is returned) if present,
    otherwise a null pointer is returned.
    If time>refTime, a null pointer is returned.

    The behaviour just described above should be general for all types of underlyings and historical fixings.
    Hence it has been placed in this very base class and "hard-coded" into getFixingPtr method.

    Notice also that we completely ignore if fixings are present for times > refTime (we do not check to avoid such
    ocurrences for performance reasons, but in any case they are not expected to (i.e. should not) occur
    in normal class usage).
    */
    const FixingType * getFixingPtr(const HLSTRING & historyTag,
                                    const TimeType& time,
                                    bool allowEmptyStrictlyPastFixing=false
                                    ) const
    {

        fixingPtr_=NULL;

        if(time>refTime_)
            return fixingPtr_;

        bool exactlyAtRefTime = (time==refTime_);

        typename HistoryCollectionType::const_iterator coll_cIt = histories_.find(historyTag);

        if(coll_cIt==histories_.end())
        {
            HL_SRE(allowEmptyStrictlyPastFixing || exactlyAtRefTime, "history tag not found: " << errorString(historyTag, time));
            return fixingPtr_;
        }

        const HistType & hist = coll_cIt->second;

        typename HistType::const_iterator hist_cIt = hist.find(time);

        if(hist_cIt==hist.end())
        {
            HL_SRE(allowEmptyStrictlyPastFixing || exactlyAtRefTime, "time not found: "  << errorString(historyTag, time));
            return fixingPtr_;
        }

        fixingPtr_ = &(hist_cIt->second);

        /*
        Should be implemented in derived classes acording to the actual type of fixingPtr_
        */
        ensureValidFixing(historyTag, time);

        return fixingPtr_;
    } // end getFixingPtr


    void storeFixing(const HLSTRING & historyTag,
                     const TimeType& time,
                     const FixingType & newFixingValue)
    {

        const FixingType * alreadyStoredFixingValue = getFixingPtr(historyTag, time, true/*allowEmptyStrictlyPastFixing*/);


        HL_SRE(alreadyStoredFixingValue==NULL,
               "Fixing already stored, historyTag=" << historyTag << ", time=" << time <<
               ", newFixingValue=" << newFixingValue << ", alreadyStoreFixingValue=" << alreadyStoredFixingValue);


        histories_[historyTag][time]=newFixingValue;



    } // end storeFixing

    //@}


protected:




    /**
    Additional implementations
    */
    //@{
    /**
    Default initialization of the class vars.
    */
    void classDefaultInit()
    {
        fixingPtr_=NULL;
    }





    //@}


    /**
    Implementations of base class methods
    */
    //@{
    void descriptionImpl(std::ostream & os) const
    {
        Descriptable::descriptionImpl(os);

        hl_fillDescriptionStream(hl_ObjCodePtr_);

        os << "Stored history tags:\n";
        BOOST_FOREACH(const typename HistoryCollectionType::value_type & p, histories_)
        {
            os << p.first << "\n";
        } // end cIt
    } // end descriptionImpl

    /**
    Should check the value of fixingPtr_
    */
    virtual void ensureValidFixing(const HLSTRING & historyTag,
                                   const TimeType& time) const
    {
        HL_UNEXPECTED_FUNCTION_CALL;
    }


    HLSTRING errorString(const HLSTRING & historyTag, const TimeType& time) const
    {
        std::stringstream ss;
        ss << " [historyTag=" << historyTag << ", time=" << time <<
              "] for the following HL_History object: " << (*this);
        return ss.str();
    }

    //@}
protected:


    /**
    Class variables
    */
    //@{
    /**
    The code of the object the History refers to
    */
    HL_ObjCodePtr hl_ObjCodePtr_;

    HistoryCollectionType histories_;

    TimeType refTime_;

    /**
    Service ptr
    */
    mutable const FixingType * fixingPtr_;

    //@}

private:
    /**
    Private class variables
    */
    //@{

    //@}
}
; // end class HL_History


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_History: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


typedef HL_History<ptime, HLR> HL_BaseTimeRealHistory;



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TimeRealHistory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131222
\brief History: time vs double
*/

class HL_TimeRealHistory : public HL_BaseTimeRealHistory
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


        HL_SERIALIZE_BASE_CLASS(HL_BaseTimeRealHistory);

        HL_SER(expectedPositiveFixing_);


    }
    //@} Serialization -----------------------------------
public:


    /**
    Constructors & destructors
    */
    //@{

    HL_TimeRealHistory();

    virtual ~HL_TimeRealHistory();
    //@}


    /**
    Public class interface
    */
    //@{
    HL_CLASS_VAR_ACCESS_METHODS(bool/*ClassVariableType*/, expectedPositiveFixing/*classVariableName_no_underscore*/);

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


    void ensureValidFixing(const HLSTRING & historyTag,
                           const TimeType& time) const;
    //@}


protected:


    /**
    Class variables
    */
    //@{
    bool expectedPositiveFixing_;
    //@}

}
; // end class HL_TimeRealHistory



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_TimeRealHistory: defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_TimeRealHistoryPtr BSP<HLOBJ::HL_TimeRealHistory>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// HLTEST_get_HL_TimeRealHistory
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

HL_TimeRealHistoryPtr HLTEST_get_HL_TimeRealHistory(const HL_ObjCodePtr & objCode,
                                                    const date & refDate,
                                                    const HLSTRING & historyTag,
                                                    const std::vector<HLR> & fixingValues);






} // end namespace HL_Object
} //end namespace HorizonLib


#endif // _hl_history_h_
