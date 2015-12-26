/**
FILE NAME= hl_multiLinearInterp.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131227
*/
#include <hl/math/interpolation/hl_multiLinearInterp.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINTP::HL_n_D_MultiLinearInterpControls);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HLINTP::HL_n_D_MultiLinearInterp);

namespace HorizonLib
{
namespace HL_Math
{
namespace HL_Interpolation
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_n_D_MultiLinearInterpControls
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_n_D_MultiLinearInterpControls::HL_n_D_MultiLinearInterpControls()
{

    classDefaultInit();



} // end HL_n_D_MultiLinearInterpControls

//------------------------------------------------------------------------------------------------------

HL_n_D_MultiLinearInterpControls::~HL_n_D_MultiLinearInterpControls()
{} // end ~HL_n_D_MultiLinearInterpControls


//------------------------------------------------------------------------------------------------------

void HL_n_D_MultiLinearInterpControls::classDefaultInit()
{} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_n_D_MultiLinearInterpControls::descriptionImpl(std::ostream & os) const
{
    HL_InterpControls::descriptionImpl(os);


} // end descriptionImpl





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_n_D_MultiLinearInterp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_n_D_MultiLinearInterp::HL_n_D_MultiLinearInterp()
{

    classDefaultInit();



} // end HL_n_D_MultiLinearInterp

//------------------------------------------------------------------------------------------------------

HL_n_D_MultiLinearInterp::~HL_n_D_MultiLinearInterp()
{} // end ~HL_n_D_MultiLinearInterp


//------------------------------------------------------------------------------------------------------

void HL_n_D_MultiLinearInterp::classDefaultInit()
{
    weightedValue_=HL_NAN;
} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

HLR HL_n_D_MultiLinearInterp::value_n_1(const VEC::const_iterator & b, const VEC::const_iterator & e) const
{

    localize(b, e);

    weightedValue_=0;

    HLMIDX neighbour;
    scanNeighbours(neighbour, 1/*weight*/);


    return weightedValue_;
} // end value_n_1

//------------------------------------------------------------------------------------------------------

void HL_n_D_MultiLinearInterp::descriptionImpl(std::ostream & os) const
{
    HL_Interpolator::descriptionImpl(os);

} // end descriptionImpl

//------------------------------------------------------------------------------------------------------

void HL_n_D_MultiLinearInterp::scanNeighbours(HLMIDX neighbour, HLR weight) const
{
    HLS dimIdx = neighbour.size();

    if(dimIdx==domainDim_)
    {

        /* end of scan, we have to add the contribution of the neighbour-point */

        weightedValue_+= weight*realMultiArrayPtr_->operator[](neighbour);
        return;
    }

    neighbour.push_back(0/* dummy value*/);


    const HL_Direction::HL_Localization & loc = get_localization(dimIdx);


    /*
    Left-right loop on dimension
    */
    BOOST_FOREACH(const HL_Direction::HL_LocalizationSide & locSide, loc.localizationSides)
    {

        HLR nextWeight = locSide.weight*weight;

        if(nextWeight==0.)
            continue; // no contribution will be added by zero weight neighbours

        neighbour.back()=locSide.idx;

        scanNeighbours(neighbour, nextWeight);

    } // end for i



} // end scanNeighbours




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_n_D_MultiLinearInterp: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

VEC HL_TEST_getPoint(const std::vector<VEC> &vs, const VEC &w, const HLMIDX & multiIndexCheck)
{

    HL_SR(vs.size()==w.size() && vs.size()==multiIndexCheck.size());
    VEC v(vs.size());

    HLS i=0;

    BOOST_FOREACH(HLR w_i, w)
    {
        HLS idx = multiIndexCheck[i];

        HL_SR(idx+1 < vs[i].size());

        HLR v_i= vs[i][idx]*(1-w_i)+vs[i][idx+1]*w_i;
        v[i] = v_i;
        ++i;
    }

    return v;
} // end HL_TEST_getPoint

//------------------------------------------------------------------------------------------------------


HLR HL_TEST_getEffectiveWeight(
    const std::vector<HL_DirectionPtr> & directions,
    const HLMIDX &multiIndex,
    const HLMIDX &multiIndexCheck,
    const VEC &multiIndexCheckWeight)
{

    HL_SR(multiIndex.size()==multiIndexCheck.size() && multiIndex.size()==multiIndexCheckWeight.size());

    HLR weight=1;

    HLS i=0;
    BOOST_FOREACH(HLS m_i, multiIndex)
    {
        HLS mc_i = multiIndexCheck[i];

        HLR w_i = multiIndexCheckWeight[i];

        if(!directions[i]->get_extrapolateLeft())
            w_i=std::min(1., w_i);

        if(!directions[i]->get_extrapolateRight())
            w_i=std::max(0., w_i);


        if(mc_i==m_i)
            weight*=(1-w_i);
        else if(mc_i+1==m_i)
            weight*=w_i;
        else
            return 0;

        ++i;
    }

    return weight;

} // end HL_TEST_getEffectiveWeight

//------------------------------------------------------------------------------------------------------

void HL_TEST_HL_n_D_MultiLinearInterp()
{

    std::vector<HL_DirectionPtr> directions(4);

    HLS dirIdx =0;
    HLS i;
    //------------------------------------------------------------------------------------------------------


    VEC v_x(4);
    i=0;
    v_x[i++]=0.;
    v_x[i++]=1.;
    v_x[i++]=2.;
    v_x[i++]=3.;


    HL_DirectionPtr& dir_x = directions[dirIdx++];
    dir_x.reset(new HL_Direction);
    dir_x->set_x(v_x);

    //------------------------------------------------------------------------------------------------------

    VEC v_y(3);
    i=0;
    v_y[i++]=10.;
    v_y[i++]=20.;
    v_y[i++]=30.;

    HL_DirectionPtr& dir_y = directions[dirIdx++];
    dir_y.reset(new HL_Direction);
    dir_y->set_x(v_y);

    //------------------------------------------------------------------------------------------------------

    VEC v_z(3);
    i=0;
    v_z[i++]=-100.;
    v_z[i++]=-50.;
    v_z[i++]=0.;

    HL_DirectionPtr& dir_z = directions[dirIdx++];
    dir_z.reset(new HL_Direction);
    dir_z->set_x(v_z);
    dir_z->set_extrapolateLeft(true);
    dir_z->set_extrapolateRight(true);

    //------------------------------------------------------------------------------------------------------


    VEC v_t(5);
    i=0;
    v_t[i++]=0.1;
    v_t[i++]=0.2;
    v_t[i++]=0.3;
    v_t[i++]=0.4;
    v_t[i++]=0.5;

    HL_DirectionPtr& dir_t = directions[dirIdx++];
    dir_t.reset(new HL_Direction);
    dir_t->set_x(v_t);

    //------------------------------------------------------------------------------------------------------

    std::vector<VEC> vs(4);

    vs[0] = v_x;
    vs[1] = v_y;
    vs[2] = v_z;
    vs[3] = v_t;




    HL_InterpControlsPtr interpControlsPtr(new HL_n_D_MultiLinearInterpControls);

    interpControlsPtr->set_directions(directions);

    HL_n_D_MultiLinearInterp m;

    m.set_interpControlsPtr(interpControlsPtr);


    m.instantiateMultiArray();

    //------------------------------------------------------------------------------------------------------



    // produces randomness out of thin air
    boost::random::mt19937 rng;
    // see pseudo-random number generators
    boost::random::uniform_int_distribution<> cent(1, 10000);
    // distribution that maps to 1..10000
    // see random number distributions


    std::vector<HLMIDX> multiIndexChecks;
    std::vector<VEC> multiIndexCheckWeights;

    //------------------------------------------------------------------------------------------------------
    // Single check point
    multiIndexChecks.push_back(HLMIDX(4));
    i=0;
    multiIndexChecks.back()[i++] = 2;
    multiIndexChecks.back()[i++] = 1;
    multiIndexChecks.back()[i++] = 0;
    multiIndexChecks.back()[i++] = 3;

    multiIndexCheckWeights.push_back(VEC(4));
    i=0;
    multiIndexCheckWeights.back()[i++] = 1.;
    multiIndexCheckWeights.back()[i++] = 0;
    multiIndexCheckWeights.back()[i++] = 0.;
    multiIndexCheckWeights.back()[i++] = 1.;
    //------------------------------------------------------------------------------------------------------
    // Single check point
    multiIndexChecks.push_back(HLMIDX(4));
    i=0;
    multiIndexChecks.back()[i++] = 1;
    multiIndexChecks.back()[i++] = 1;
    multiIndexChecks.back()[i++] = 1;
    multiIndexChecks.back()[i++] = 2;

    multiIndexCheckWeights.push_back(VEC(4));
    i=0;
    multiIndexCheckWeights.back()[i++] = .3;
    multiIndexCheckWeights.back()[i++] = 0.44;
    multiIndexCheckWeights.back()[i++] = 0.12;
    multiIndexCheckWeights.back()[i++] = .945;
    //------------------------------------------------------------------------------------------------------
    // Single check point
    multiIndexChecks.push_back(HLMIDX(4));
    i=0;
    multiIndexChecks.back()[i++] = 1;
    multiIndexChecks.back()[i++] = 0; // left border
    multiIndexChecks.back()[i++] = 1; // right border
    multiIndexChecks.back()[i++] = 2;

    multiIndexCheckWeights.push_back(VEC(4));
    i=0;
    multiIndexCheckWeights.back()[i++] = .3;
    multiIndexCheckWeights.back()[i++] = -0.44; // left border (extrapolate=false)
    multiIndexCheckWeights.back()[i++] = 1.12; // right border (extrapolate=true)
    multiIndexCheckWeights.back()[i++] = .945;
    //------------------------------------------------------------------------------------------------------
    // Single check point
    multiIndexChecks.push_back(HLMIDX(4));
    i=0;
    multiIndexChecks.back()[i++] = 1;
    multiIndexChecks.back()[i++] = 0; // left border
    multiIndexChecks.back()[i++] = 1; // right border
    multiIndexChecks.back()[i++] = 2;

    multiIndexCheckWeights.push_back(VEC(4));
    i=0;
    multiIndexCheckWeights.back()[i++] = .3;
    multiIndexCheckWeights.back()[i++] = 0; // left border, equal to previous since extrapolate=false
    multiIndexCheckWeights.back()[i++] = 1.12; // right border (extrapolate=true)
    multiIndexCheckWeights.back()[i++] = .945;
    //------------------------------------------------------------------------------------------------------
    // Single check point
    multiIndexChecks.push_back(HLMIDX(4));
    i=0;
    multiIndexChecks.back()[i++] = 1;
    multiIndexChecks.back()[i++] = 0; // left border
    multiIndexChecks.back()[i++] = 1; // right border
    multiIndexChecks.back()[i++] = 2;

    multiIndexCheckWeights.push_back(VEC(4));
    i=0;
    multiIndexCheckWeights.back()[i++] = .3;
    multiIndexCheckWeights.back()[i++] = -0.44; // left border (extrapolate=false)
    multiIndexCheckWeights.back()[i++] = 1; // right border, different to previous since extrapolate=true
    multiIndexCheckWeights.back()[i++] = .945;
    //------------------------------------------------------------------------------------------------------
    // Single check point
    multiIndexChecks.push_back(HLMIDX(4));
    i=0;
    multiIndexChecks.back()[i++] = 1;
    multiIndexChecks.back()[i++] = 0; // left border
    multiIndexChecks.back()[i++] = 1; // right border
    multiIndexChecks.back()[i++] = 2;

    multiIndexCheckWeights.push_back(VEC(4));
    i=0;
    multiIndexCheckWeights.back()[i++] = .3;
    multiIndexCheckWeights.back()[i++] = -0.44; // left border (extrapolate=false)
    multiIndexCheckWeights.back()[i++] = 1.06; // right border, different to previous since extrapolate=true
    multiIndexCheckWeights.back()[i++] = .945;
    //------------------------------------------------------------------------------------------------------


    HLMIDX multiIndex(4, 0);

    HLS & ix = multiIndex[0];
    HLS & iy = multiIndex[1];
    HLS & iz = multiIndex[2];
    HLS & it = multiIndex[3];

    VEC checkValues(multiIndexChecks.size(), 0);

    ix=0;
    BOOST_FOREACH(HLR x, v_x)
    {
        iy=0;
        BOOST_FOREACH(HLR y, v_y)
        {
            iz=0;
            BOOST_FOREACH(HLR z, v_z)
            {
                it=0;
                BOOST_FOREACH(HLR t, v_t)
                {

                    HLR r = cent(rng);

                    m.setPoint(multiIndex, r);

                    i=0;
                    BOOST_FOREACH(HLR & checkValue_i, checkValues)
                    {
                        HLR ew_i = HL_TEST_getEffectiveWeight(
                                       directions,
                                       multiIndex,
                                       multiIndexChecks[i],
                                       multiIndexCheckWeights[i]);

                        checkValue_i+= (ew_i*r);

                        ++i;
                    } // end checkValue


                    ++it;
                } // end for t
                ++iz;
            } // end for z
            ++iy;
        } // end for y
        ++ix;
    } // end for x

    HLSER::HL_CoreSerializableObj csObj;

    csObj.oa() << m;
    csObj.getReadyForDeserialization();
    HL_n_D_MultiLinearInterp m_1;
    csObj.ia() >> m_1;




    i=0;
    BOOST_FOREACH(HLR checkValue_i, checkValues)
    {

        VEC checkPoint_i = HL_TEST_getPoint(vs, multiIndexCheckWeights[i], multiIndexChecks[i]);


        HLR checkValueFromInterp_m = m.value_n_1(checkPoint_i.begin(), checkPoint_i.end());

        HLR checkValueFromInterp_m1 = m_1.value_n_1(checkPoint_i.begin(), checkPoint_i.end());

        HL_REQ_EQUAL_FLOATS_N(checkValue_i, checkValueFromInterp_m, 1000);
        HL_REQ_EQUAL_FLOATS_N(checkValue_i, checkValueFromInterp_m1, 1000);

        //        HL_LOG(HLLOG::HL_severity_level_notification, "\n------------------------------------------------\n");
        //
        //
        //
        //        HL_LOG(HLLOG::HL_severity_level_notification,
        //               "\nmultiIndexChecks=" << hl_container_description(multiIndexChecks[i])
        //               << "\nmultiIndexCheckWeights=" << hl_container_description(multiIndexCheckWeights[i])
        //               << "\ncheckValue_i=" << checkValue_i);

        ++i;
    } // end checkValue


    HL_SUCCESSFULL_TEST(HL_TEST_HL_n_D_MultiLinearInterp);




} // end HL_TEST_HL_n_D_MultiLinearInterp


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class Prova
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



/**
g. g.

dett g
*/
void Prova::g()
{}





} // end namespace HL_Interpolation
} // end namespace HL_Math
} //end namespace HorizonLib
