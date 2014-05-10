/**
FILE NAME= hl_coreSerializableObj.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131206
*/
#ifndef _hl_coreSerializableObj_h_
#define _hl_coreSerializableObj_h_

#include <hl/basicFiles/hl_basicIncludes.h>



namespace HorizonLib
{
namespace HL_Serialization
{
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define	HL_FRIEND_SERIALIZATION_ACCESS friend class boost::serialization::access;

//------------------------------------------------------------------------------------------------------

#define HL_SERIALIZATION_CLASS_EXPORT_GUID(MyClass) BOOST_CLASS_EXPORT(MyClass)

//------------------------------------------------------------------------------------------------------

#define HL_SERIALIZE_BASE_CLASS(BaseClass) ar & boost::serialization::base_object<BaseClass>(*this);

//------------------------------------------------------------------------------------------------------

#define HL_SER(x) ar & x;



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// namespace defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

namespace HL_io = boost::iostreams;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CoreSerializableObj
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131206
\brief When one or more classes/primitive types are serialized, the result of the serialization can be stored
in one instance of this class. On the other hand, all the objs can be reconstructed by desrializing the instance
of the HL_CoreSerializableObj class (one or more times).
Finally, two instances A, B of the HL_CoreSerializableObj class could be compared and the comparison will give
a positive result if and only if the set of classes that have been used to create A and B were equal (at least
for what concerning the part of the classes related to serialization).
*/
class HL_CoreSerializableObj
{
public:

    typedef std::vector<char, boost::pool_allocator<char> > buffer_type;



    /**
    Constructors & destructors
    */
    //@{

    HL_CoreSerializableObj();

    virtual ~HL_CoreSerializableObj();
    //@}


    /**
    Public class interface
    */
    //@{
    /**
    To be called when one has finished to fill data inside the class and wants to start
    desrializing the dta already in to reconstruct objs.
    */
    void getReadyForDeserialization();

    boost::archive::binary_oarchive & oa() const
    {
        return *outputArchive_;
    }

    boost::archive::binary_iarchive & ia() const
    {
        return *inputArchive_;
    }
    //@}


private:



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

    //@}
private:

    /**
    Automatically called by classDefaultInit to be able to start filling the buffer with the data
    coming from the streaming of outside objects. The point of this automatically (and then mandatory function
    call on clqass constructing) is that before being of any help, this class has always to be filled with something.
    On the other hand, the functionis is private since we do not allow class reset and refill.
    */
    void resetBufferForOutput();

private:


    /**
    Class variables
    */
    //@{
    buffer_type buffer_;

    /**
    Output, i.e. to fill data inside this class (that is output to mean that the archive gets
    filled, i.e. it is an output target)
    */
    //@{
    BSP<HL_io::stream<HL_io::back_insert_device<buffer_type> > > output_stream_;
    BSP<boost::archive::binary_oarchive> outputArchive_;
    //@}
    /**
    Input, i.e. to get data outside from this class (that is input to mean that data is taken from the archive,
    i.e. it is a source (an input) of data)
    */
    //@{

    BSP<HL_io::basic_array_source<char> > source_;
    BSP<HL_io::stream<HL_io::basic_array_source <char> > > input_stream_;
    BSP<boost::archive::binary_iarchive> inputArchive_;


    //@}
    //@} Class variables

}
; // end class HL_CoreSerializableObj



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Serializable
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
 * \author A. Cesarini
 * \date 20140211
 * \brief Base class for all serializable objects.
 *
 */
class HL_Serializable
{


    /**
     -----------------------------------------------------
     Serialization
     */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS;

    template<class Archive>
    void save(Archive & ar, const unsigned int version) const
    {
        isToStream_=true;
    }

    template<class Archive>
    void load(Archive & ar, const unsigned int version)
    {
        isToStream_=false;

    }

    BOOST_SERIALIZATION_SPLIT_MEMBER();



    //@} Serialization -----------------------------------

public:


    /**
     * Constructors & destructors
    */
    //@{

    HL_Serializable();

    virtual ~HL_Serializable();
    //@}


    /**
     * Public class interface
    */
    //@{

    bool isToStream() const;

    //@}


protected:

    /**
     * Additional implementations
    */
    //@{
    /**
     * Default initialization of the class vars.
    */
    void classDefaultInit();
    //@}


    /**
     * Implementations of base class methods
    */
    //@{

    //@}


protected:


    /**
     * Class variables
    */
    //@{

    mutable boost::logic::tribool isToStream_;

    //@}

    /**
     * Service class variables
    */
    //@{

    //@}


}
; // end class HL_Serializable


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Serializable: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define HL_SER_BASE HL_SERIALIZE_BASE_CLASS(HLSER::HL_Serializable);

} // end namespace HL_Serialization
} //end namespace HorizonLib


#endif // _hl_coreSerializableObj_h_
