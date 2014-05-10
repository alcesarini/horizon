/**
FILE NAME= hl_coreSerializableObj.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131206
*/
#include <hl/serialization/hl_coreSerializableObj.h>
#include <hl/basicFiles/hl_workingIncludes.h>


namespace HorizonLib
{
namespace HL_Serialization
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CoreSerializableObj
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CoreSerializableObj::HL_CoreSerializableObj()
{
    classDefaultInit();

} // end HL_CoreSerializableObj

//------------------------------------------------------------------------------------------------------

HL_CoreSerializableObj::~HL_CoreSerializableObj()
{} // end ~HL_CoreSerializableObj

//------------------------------------------------------------------------------------------------------

void HL_CoreSerializableObj::classDefaultInit()
{
    resetBufferForOutput();
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_CoreSerializableObj::getReadyForDeserialization()
{
    /*
    Necessary operation to be sure to have all written into the buffer and nothing still in ram.
    So this flush has to be call before the following require.
    */
    output_stream_->flush();

    HL_SRE(!buffer_.empty(), "expected a non empty buffer_ when requesting to start deserializing");


    source_.reset(new HL_io::basic_array_source<char>(&buffer_[0],buffer_.size()));

    input_stream_.reset(new HL_io::stream<HL_io::basic_array_source <char> >(*source_));

    inputArchive_.reset(new boost::archive::binary_iarchive(*input_stream_));

} // end getReadyForDeserialization



//------------------------------------------------------------------------------------------------------

void HL_CoreSerializableObj::resetBufferForOutput()
{

    buffer_.clear();

    output_stream_.reset(new HL_io::stream<HL_io::back_insert_device<buffer_type> > (buffer_));

    outputArchive_.reset(new boost::archive::binary_oarchive(*output_stream_));

} // end resetBufferForOutput



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Serializable
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_Serializable::HL_Serializable()
{
    classDefaultInit();

} // end HL_Serializable

//------------------------------------------------------------------------------------------------------

HL_Serializable::~HL_Serializable()
{} // end ~HL_Serializable

//------------------------------------------------------------------------------------------------------

void HL_Serializable::classDefaultInit()
{
    isToStream_=boost::logic::indeterminate;


} // end classDefaultInit
//------------------------------------------------------------------------------------------------------

bool HL_Serializable::isToStream() const
{


    if (isToStream_)
    {
        return true;
    }
    else if (!isToStream_)
    {
        return false;
    }
    else
    {
        // isToStream_ is indeterminate
        HL_FAIL("expected isToStream_ not indeterminate");
    }

    return false;

} // end isToStream

} // end namespace HL_Serialization
} //end namespace HorizonLib

