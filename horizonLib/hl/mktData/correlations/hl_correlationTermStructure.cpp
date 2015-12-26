/**
FILE NAME= hl_correlationTermStructure.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140602
*/

#include <hl/mktData/correlations/hl_correlationTermStructure.h>
#include <hl/mktData/hl_mktDataCollector.h>
#include <hl/math/interpolation/hl_multiLinearInterp.h>
#include <hl/dateTime/hl_dateTime.h>


HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINTERACTIONS::HL_InteractionTermStructure);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINTERACTIONS::HL_InteractionTermStructureCode);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINTERACTIONS::HL_InterpInteractionTermStructure);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINTERACTIONS::HL_CorrelationTermStructureCode);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINTERACTIONS::HL_CovarianceTermStructureCode);

namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_Interactions
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InteractionTermStructureCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_InteractionTermStructureCode::HL_InteractionTermStructureCode()
{
    classDefaultInit();

} // end HL_InteractionTermStructureCode

//------------------------------------------------------------------------------------------------------

HL_InteractionTermStructureCode::~HL_InteractionTermStructureCode()
{} // end ~HL_InteractionTermStructureCode

//------------------------------------------------------------------------------------------------------

void HL_InteractionTermStructureCode::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

HLSTRING HL_InteractionTermStructureCode::objTypeImpl() const
{
    HL_UNEXPECTED_FUNCTION_CALL;
} // end objTypeImpl



//------------------------------------------------------------------------------------------------------


void HL_InteractionTermStructureCode::descriptionImpl(std::ostream & os) const
{
    HLMD::HL_MktDataCode::descriptionImpl(os);



    /*
     * There is  no need to write if the class is a correlation or a covariance since this is
     * written in the very base HL_ObjCode::descriptionImpl through method objTypeImpl()
     * that is implemented in the most derived class.
    */
    hl_fillDescriptionStream(objCodePtr1_);
    hl_fillDescriptionStream(objCodePtr2_);



} // end descriptionImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InteractionTermStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_InteractionTermStructure::HL_InteractionTermStructure()
{

    classDefaultInit();



} // end HL_InteractionTermStructure

//------------------------------------------------------------------------------------------------------

HL_InteractionTermStructure::~HL_InteractionTermStructure()
{} // end ~HL_InteractionTermStructure


//------------------------------------------------------------------------------------------------------

void HL_InteractionTermStructure::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_InteractionTermStructure::descriptionImpl(std::ostream & os) const
{
    HL_MktData::descriptionImpl(os);



} // end descriptionImpl

//------------------------------------------------------------------------------------------------------



void HL_InteractionTermStructure::set_HL_ObjCodePtr(const HL_ObjCodePtr & hl_ObjCodePtr)
{

    HL_MktData::set_HL_ObjCodePtr(hl_ObjCodePtr);


    interactionTermStructureCode_ =
            boost::dynamic_pointer_cast<HL_InteractionTermStructureCode>(hl_ObjCodePtr);

    HL_PNN(interactionTermStructureCode_);


} // end set_HL_ObjCodePtr


//------------------------------------------------------------------------------------------------------




HLR HL_InteractionTermStructure::get_interaction(const ptime & fixingTime,
                                                 const ptime & firstFwdMaturityTime,
                                                 const ptime & secondFwdMaturityTime) const
{

    HL_SRE(fixingTime>=get_refTime(), "fixingTime=" << fixingTime << ", get_refTime()=" << get_refTime());

    HL_SRE(firstFwdMaturityTime>=fixingTime, "fixingTime=" << fixingTime << ",firstFwdMaturityTime=" << firstFwdMaturityTime);

    HL_SRE(secondFwdMaturityTime>=fixingTime, "fixingTime=" << fixingTime << ",secondFwdMaturityTime=" << secondFwdMaturityTime);

    HLR fixingTimeShift = get_yf(get_refTime(), fixingTime);

    HLR deltaTime_1 = get_yf(fixingTime, firstFwdMaturityTime);

    HLR deltaTime_2 = get_yf(fixingTime, secondFwdMaturityTime);

    return get_interactionImpl(fixingTimeShift, deltaTime_1, deltaTime_2);


} // end get_interaction



//------------------------------------------------------------------------------------------------------

HLR HL_InteractionTermStructure::get_yf(const ptime& t_1, const ptime& t_2) const
{

    HLR yf =HLDT::act_yf(t_1, t_2);
    return yf;

} // end get_yf

//------------------------------------------------------------------------------------------------------

HLR HL_InteractionTermStructure::get_yf(const date& d_1, const date& d_2) const
{
    HLR yf =HLDT::act_yf(d_1, d_2);
    return yf;

} // end get_yf



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InteractionTermStructure: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_InteractionTermStructurePtr get_InteractionTermStructurePtr(const HL_MktDataCollectorPtr & mktDataCollectorPtr,
                                                               const HL_ObjCodePtr & objCodePtr)
{

    return get_mktData<HL_InteractionTermStructurePtr>(mktDataCollectorPtr, objCodePtr);

} // end get_TermStructurePtr




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterpInteractionTermStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_InterpInteractionTermStructure::HL_InterpInteractionTermStructure()
{

    classDefaultInit();



} // end HL_InterpInteractionTermStructure

//------------------------------------------------------------------------------------------------------

HL_InterpInteractionTermStructure::~HL_InterpInteractionTermStructure()
{} // end ~HL_InterpInteractionTermStructure


//------------------------------------------------------------------------------------------------------

void HL_InterpInteractionTermStructure::classDefaultInit()
{
    service_xVect_.resize(3);

    service_xVectBegin_= service_xVect_.begin();

    service_xVectEnd_ = service_xVect_.end();

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_InterpInteractionTermStructure::descriptionImpl(std::ostream & os) const
{
    HL_InteractionTermStructure::descriptionImpl(os);


    hl_fillDescriptionStream(interpolatorPtr_);


} // end descriptionImpl


//------------------------------------------------------------------------------------------------------

void HL_InterpInteractionTermStructure::set_InteractionData(const HL_InteractionDataPtr & interactionDataPtr)
{
    HL_PNN(interactionDataPtr);

    HLS nbFixingPeriods = interactionDataPtr->fixingPeriods.size();


    HL_SR(nbFixingPeriods);

    HL_SR(nbFixingPeriods==interactionDataPtr->interactionMatrices.size());


    HLS nbDeltaPeriods = interactionDataPtr->deltaPeriods.size();

    HL_SR(nbDeltaPeriods);


    VEC fixingTimes(nbFixingPeriods);

    VEC deltaTimes(nbDeltaPeriods, 0.);

    const date & refDate = get_refDate();

    for(HLS t=0;t<nbFixingPeriods;t++)
    {

        const HL_Period & period_t = interactionDataPtr->fixingPeriods[t];

        date fixingDate_t = refDate + period_t;

        HLR fixingTime_t = get_yf(refDate, fixingDate_t);

        fixingTimes[t] = fixingTime_t;

        const MATRIX & rho_t = interactionDataPtr->interactionMatrices[t];

        HL_SR(rho_t.size1()==nbDeltaPeriods && rho_t.size2()==nbDeltaPeriods);


        for(HLS i=0;i<nbDeltaPeriods;i++)
        {

            const HL_Period & deltaPeriod_i = interactionDataPtr->deltaPeriods[i];

            date endDate_t_i = fixingDate_t + deltaPeriod_i;

            HLR deltaTime_t_i = get_yf(fixingDate_t, endDate_t_i);

            deltaTimes[i] += deltaTime_t_i;


            if(get_objCodePtr1()==get_objCodePtr2() && interactionTermStructureCode_->isCorrelation()){

                HL_SRE(rho_t(i, i)==1.,
                       "case get_objCodePtr1()==get_objCodePtr2() && isCorrelation()==true, get_objCodePtr1()="
                       << get_objCodePtr1()->get_sCode()
                       << ", rho_t(i, i)=" << rho_t(i, i) << ", i=" << i);
            } // end if

        } //end for i


    } // end for t

    /*
    In this way we compute an average delta time w.r.t. all fixingDates
    */
    deltaTimes/=nbFixingPeriods;


    std::vector<HL_DirectionPtr> directions(3);
    HLS dirIdx =0;
    HL_DirectionPtr& dir_fixingTime = directions[dirIdx++];
    dir_fixingTime.reset(new HLINTP::HL_Direction);
    dir_fixingTime->set_x(fixingTimes);
    dir_fixingTime->set_extrapolateLeft(false);
    dir_fixingTime->set_extrapolateRight(false);

    HL_DirectionPtr& dir_deltaTime1 = directions[dirIdx++];
    dir_deltaTime1.reset(new HLINTP::HL_Direction);
    dir_deltaTime1->set_x(deltaTimes);
    dir_deltaTime1->set_extrapolateLeft(false);
    dir_deltaTime1->set_extrapolateRight(false);


    HL_DirectionPtr& dir_deltaTime2 = directions[dirIdx++];
    dir_deltaTime2.reset(new HLINTP::HL_Direction);
    dir_deltaTime2->set_x(deltaTimes);
    dir_deltaTime2->set_extrapolateLeft(false);
    dir_deltaTime2->set_extrapolateRight(false);




    HL_InterpControlsPtr interpControlsPtr(new HLINTP::HL_n_D_MultiLinearInterpControls);


    interpControlsPtr->set_directions(directions);

    interpolatorPtr_.reset(new HLINTP::HL_n_D_MultiLinearInterp);


    interpolatorPtr_->set_interpControlsPtr(interpControlsPtr);


    interpolatorPtr_->instantiateMultiArray();


    setInteractionPoints(interactionDataPtr);


} // end set_InteractionData

//------------------------------------------------------------------------------------------------------


void HL_InterpInteractionTermStructure::setInteractionPoints(const HL_InteractionDataPtr & interactionDataPtr)
{
    HLS nbFixingPeriods = interactionDataPtr->fixingPeriods.size();


    HLS nbDeltaPeriods = interactionDataPtr->deltaPeriods.size();

    HLMIDX multiIndex(3);


    for(HLS t=0;t<nbFixingPeriods;t++)
    {

        multiIndex[0]=t;

        const MATRIX & rho_t = interactionDataPtr->interactionMatrices[t];

        for(HLS i_1=0;i_1<nbDeltaPeriods;i_1++)
        {

            multiIndex[1]=i_1;

            for(HLS i_2=0;i_2<nbDeltaPeriods;i_2++)
            {
                multiIndex[2]=i_2;


                HLR rho_12 = rho_t(i_1, i_2);


                interpolatorPtr_->setPoint(multiIndex, rho_12/* value*/);


            } //end for i_2


        } //end for i_1


    } // end for t


} // end setInteractionPoints


//------------------------------------------------------------------------------------------------------

HLR HL_InterpInteractionTermStructure::get_interactionImpl(HLR fixingTime,
                                                           HLR deltaTime_1,
                                                           HLR deltaTime_2) const
{

    service_xVect_[0] = fixingTime;
    service_xVect_[1] = deltaTime_1;
    service_xVect_[2] = deltaTime_2;


    HLR rho = interpolatorPtr_->value_n_1(service_xVectBegin_, service_xVectEnd_);

    return rho;

} // end get_interactionImpl

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_InterpInteractionTermStructure: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



HL_InterpInteractionTermStructurePtr HL_TEST_build_HL_InterpInteractionTermStructurePtr(
        const HL_ObjCodePtr & objCodePtr1,
        const HL_ObjCodePtr & objCodePtr2,
        const HL_MktDataCollectorPtr & mktDataCollectorPtr
        )
{
    HL_InterpInteractionTermStructurePtr interpInteractionTermStructure(
                new HLINTERACTIONS::HL_InterpInteractionTermStructure);


    HL_InteractionDataPtr interactionData(new HLINTERACTIONS::HL_InteractionData);



    std::vector<HL_Period> &fixingPeriods = interactionData->fixingPeriods;

    fixingPeriods.push_back(HL_Period(1, HL_PeriodUnit_Years));
    fixingPeriods.push_back(HL_Period(5, HL_PeriodUnit_Years));
    fixingPeriods.push_back(HL_Period(7, HL_PeriodUnit_Years));


    std::vector<HL_Period> &deltaPeriods = interactionData->deltaPeriods;

    deltaPeriods.push_back(HL_Period(0, HL_PeriodUnit_Years));
    deltaPeriods.push_back(HL_Period(1, HL_PeriodUnit_Years));


    std::vector<MATRIX> &interactionMatrices = interactionData->interactionMatrices;



    MATRIX rho(deltaPeriods.size(), deltaPeriods.size());

    rho(0, 0)=1;
    rho(1, 1)=1;
    rho(0, 1)=0.5;
    rho(1, 0)=rho(0, 1);

    interactionMatrices.push_back(rho);

    rho(0, 1)=0.6;
    rho(1, 0)=rho(0, 1);

    interactionMatrices.push_back(rho);

    rho(0, 1)=0.7;
    rho(1, 0)=rho(0, 1);

    interactionMatrices.push_back(rho);

    interpInteractionTermStructure->set_mktDataCollectorWeakPtr(mktDataCollectorPtr);


    HL_CorrelationTermStructureCodePtr correlationTermStructureCode12 =
            HL_CorrelationTermStructureCode::instantiateCorrelationTermStructureCode(objCodePtr1, objCodePtr2);


    interpInteractionTermStructure->set_HL_ObjCodePtr(correlationTermStructureCode12);

    interpInteractionTermStructure->set_InteractionData(interactionData);





    HLMD::HL_MktDataCollector::addMktData(correlationTermStructureCode12 /*objCodePtr*/,
                                    interpInteractionTermStructure /*mktDataPtr*/,
                                    mktDataCollectorPtr,
                                    false /*allowOverwritingExistingData*/);



    return interpInteractionTermStructure;

} // end HL_TEST_build_HL_InterpInteractionTermStructurePtr



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CorrelationTermStructureCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CorrelationTermStructureCode::HL_CorrelationTermStructureCode()
{
    classDefaultInit();

} // end HL_CorrelationTermStructureCode

//------------------------------------------------------------------------------------------------------

HL_CorrelationTermStructureCode::~HL_CorrelationTermStructureCode()
{} // end ~HL_CorrelationTermStructureCode

//------------------------------------------------------------------------------------------------------

void HL_CorrelationTermStructureCode::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

HLSTRING HL_CorrelationTermStructureCode::objTypeImpl() const
{
    return "HL_CorrelationTermStructureCode";
} // end objTypeImpl





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_CovarianceTermStructureCode
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_CovarianceTermStructureCode::HL_CovarianceTermStructureCode()
{
    classDefaultInit();

} // end HL_CovarianceTermStructureCode

//------------------------------------------------------------------------------------------------------

HL_CovarianceTermStructureCode::~HL_CovarianceTermStructureCode()
{} // end ~HL_CovarianceTermStructureCode

//------------------------------------------------------------------------------------------------------

void HL_CovarianceTermStructureCode::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

HLSTRING HL_CovarianceTermStructureCode::objTypeImpl() const
{
    return "HL_CovarianceTermStructureCode";
} // end objTypeImpl




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_DerivedCovarianceTermStructure
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_DerivedCovarianceTermStructure::HL_DerivedCovarianceTermStructure()
{

    classDefaultInit();



} // end HL_DerivedCovarianceTermStructure

//------------------------------------------------------------------------------------------------------

HL_DerivedCovarianceTermStructure::~HL_DerivedCovarianceTermStructure()
{} // end ~HL_DerivedCovarianceTermStructure


//------------------------------------------------------------------------------------------------------

void HL_DerivedCovarianceTermStructure::classDefaultInit()
{
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------


void HL_DerivedCovarianceTermStructure::descriptionImpl(std::ostream & os) const
{
    HL_MktData::descriptionImpl(os);



} // end descriptionImpl

//------------------------------------------------------------------------------------------------------


HL_CovarianceTermStructurePtr HL_DerivedCovarianceTermStructure::getDerivedCovarianceTermStructure(
        const HL_ObjCodePtr & objCodePtr1,
        const HL_ObjCodePtr & objCodePtr2,
        const HL_MktDataCollectorPtr & mktDataCollectorPtr
        )
{

    HL_DerivedCovarianceTermStructurePtr derivedCovarianceTermStructure(new HL_DerivedCovarianceTermStructure);

    HL_CovarianceTermStructureCodePtr derivedCovarianceTermStructureCode =
            HL_CovarianceTermStructureCode::instantiateCovarianceTermStructureCode(
                objCodePtr1,
                objCodePtr2 );

    derivedCovarianceTermStructure->set_HL_ObjCodePtr(derivedCovarianceTermStructureCode);


    HL_CorrelationTermStructureCodePtr correlationTermStructureCode12 =
            HL_CorrelationTermStructureCode::instantiateCorrelationTermStructureCode(objCodePtr1, objCodePtr2);


    HL_CorrelationTermStructurePtr correlationTermStructure12 =
            get_CorrelationTermStructurePtr(mktDataCollectorPtr, correlationTermStructureCode12);


    derivedCovarianceTermStructure->set_correlationTermStructure12(correlationTermStructure12);



    HL_UnderlyingPtr underlying1 = get_mktData<HL_UnderlyingPtr>(mktDataCollectorPtr, objCodePtr1);

    derivedCovarianceTermStructure->set_underlying1(underlying1);


    HL_UnderlyingPtr underlying2 = get_mktData<HL_UnderlyingPtr>(mktDataCollectorPtr, objCodePtr2);

    derivedCovarianceTermStructure->set_underlying2(underlying2);


    derivedCovarianceTermStructure->set_mktDataCollectorWeakPtr(mktDataCollectorPtr);

    return derivedCovarianceTermStructure;


} // end setDerivedCovarianceTermStructureData

//------------------------------------------------------------------------------------------------------


void HL_DerivedCovarianceTermStructure::set_correlationTermStructure12(
        const HL_CorrelationTermStructurePtr& correlationTermStructure12)
{

    correlationTermStructure12_=correlationTermStructure12;
    HL_SR(correlationTermStructure12_->isCorrelation());

} // end set_correlationTermStructure12

//------------------------------------------------------------------------------------------------------

HLR HL_DerivedCovarianceTermStructure::get_interaction(const ptime & fixingTime,
                                                       const ptime & firstFwdMaturityTime,
                                                       const ptime & secondFwdMaturityTime) const
{

    HLR corr12 = correlationTermStructure12_->get_interaction(fixingTime,
                                                              firstFwdMaturityTime,
                                                              secondFwdMaturityTime);


    /*
     * Remind that, being F(t, firstFwdMaturityTime) = E[S(firstFwdMaturityTime)|t] for firstFwdMaturityTime>=t,
     *  it holds that
     *
     * E[F(fixingTime, firstFwdMaturityTime)|refDate] = E[E[S(firstFwdMaturityTime)|fixingTime]|refDate]=
     * =E[S(firstFwdMaturityTime)|refDate] = F(refDate, firstFwdMaturityTime)
     * that is exactly our fwd1 here below.
     *
     * A similiar comment applies to fwd2 next below.
    */
    HLR fwd1 = underlying1_->quotingMeasureExpectation(firstFwdMaturityTime)->get_value();

    HLR vol1 = underlying1_->get_impliedVolSurface()->vol(fixingTime, fwd1, firstFwdMaturityTime)->get_vol();

    HLR fwd2 = underlying2_->quotingMeasureExpectation(secondFwdMaturityTime)->get_value();

    HLR vol2 = underlying2_->get_impliedVolSurface()->vol(fixingTime, fwd2, secondFwdMaturityTime)->get_vol();


    HLR t = get_yf(get_refTime(), fixingTime);

    HLR cov = corr12*vol1*vol2*t;

    return cov;

} // end get_interactionImpl



} // end namespace HL_Interactions
} // end namespace HL_MarketData
} //end namespace HorizonLib
