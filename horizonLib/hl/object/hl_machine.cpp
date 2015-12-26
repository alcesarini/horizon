/**
FILE NAME= hl_machine.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131128
*/
#include <hl/object/hl_machine.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLOBJ::HL_MachineInput);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLOBJ::HL_MachineInputKey);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLOBJ::HL_MachineOutput);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLOBJ::HL_Machine);



namespace HorizonLib
{
namespace HL_Object
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MachineInput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_MachineInput::HL_MachineInput()
{
    classDefaultInit();

} // end HL_MachineInput

//------------------------------------------------------------------------------------------------------

HL_MachineInput::~HL_MachineInput()
{
} // end ~HL_MachineInput

//------------------------------------------------------------------------------------------------------

void HL_MachineInput::classDefaultInit()
{

} // end classDefaultInit



//------------------------------------------------------------------------------------------------------

void HL_MachineInput::descriptionImpl(std::ostream & os) const
{


    os << "HL_MachineInput:\n";

    Descriptable::descriptionImpl(os);

    //hl_fillDescriptionStream(hl_ObjCodePtr_);



} // end descriptionImpl



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MachineInput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MachineInputKey
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_MachineInputKey::HL_MachineInputKey()
{
    classDefaultInit();

} // end HL_MachineInputKey

//------------------------------------------------------------------------------------------------------

HL_MachineInputKey::~HL_MachineInputKey()
{
} // end ~HL_MachineInputKey

//------------------------------------------------------------------------------------------------------

void HL_MachineInputKey::classDefaultInit()
{

} // end classDefaultInit



//------------------------------------------------------------------------------------------------------

void HL_MachineInputKey::descriptionImpl(std::ostream & os) const
{


    os << "HL_MachineInputKey:\n";

    Descriptable::descriptionImpl(os);

    //hl_fillDescriptionStream(hl_ObjCodePtr_);



} // end descriptionImpl



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MachineInputKey:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MachineOutput
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_MachineOutput::HL_MachineOutput()
{
    classDefaultInit();

} // end HL_MachineOutput

//------------------------------------------------------------------------------------------------------

HL_MachineOutput::~HL_MachineOutput()
{
} // end ~HL_MachineOutput

//------------------------------------------------------------------------------------------------------

void HL_MachineOutput::classDefaultInit()
{

} // end classDefaultInit



//------------------------------------------------------------------------------------------------------

void HL_MachineOutput::descriptionImpl(std::ostream & os) const
{


    os << "HL_MachineOutput:\n";

    Descriptable::descriptionImpl(os);

    //hl_fillDescriptionStream(hl_ObjCodePtr_);



} // end descriptionImpl



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MachineOutput:: defines, typedefs, functions
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Machine
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



const HL_MachineOutputPtr & HL_Machine::doJob() const
{


    try{


        /*
        Actually not needed.
        */
        cleanDisposableData();

        /*
        Call buildInputKey(..) to finalize input by determining raw data the pricing depends on.
        This raw data shall then be used to decide if the very same heavy computation
        has already been performed or not, by emaining the outputs_ map.
        In the negative case, the heavy computation part has to be performed by calling method doJobImpl(..).
        Notice that to get raw data "inputKey" you may even use a market data descriptoir mechanism.
        In this way we are isolating both the data retriving part in a method of the machine and the heavy computation part.
        */
        HL_PNN(input_);

        input_->check();

        HL_MachineInputKeyPtr inputKey;

        buildInputKey(input_, inputKey);


        HL_PNN(machineDisposableData_.inputKey);

        bool alreadyExists;
        HL_MachineOutputPtr & output = HL_mapFind(outputs_, machineDisposableData_.inputKey, alreadyExists);

        if(!alreadyExists){

            output = doJobImpl();

        } // end  if(!alreadyExists)

        cleanDisposableData();

        return output;

    }catch(...){

        cleanDisposableData();
        throw;
    }

} // end doJob

//------------------------------------------------------------------------------------------------------

void HL_Machine::buildInputKey(const HL_MachineInputPtr & input,
                           HL_MachineInputKeyPtr & machineInputKey) const
{

    machineDisposableData_.inputKey = machineInputKey;

    HL_PNN(machineDisposableData_.inputKey);

} // end buildInputKey

//------------------------------------------------------------------------------------------------------


void HL_Machine::cleanDisposableData() const
{

    machineDisposableData_=MachineDisposableData();
} // end cleanDisposableData

} // end namespace HL_Object
} //end namespace HorizonLib
