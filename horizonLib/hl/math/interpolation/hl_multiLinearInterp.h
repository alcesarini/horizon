/**
FILE NAME= hl_multiLinearInterp.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131227
*/
#ifndef _hl_multiLinearInterp_h_
#define _hl_multiLinearInterp_h_

#include <hl/math/interpolation/hl_interpolator.h>


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

/**
 \author A. Cesarini
 \date 20140204
 \brief Controls for HL_n_D_MultiLinearInterp.
 */
class HL_n_D_MultiLinearInterpControls : public virtual HL_InterpControls
{

    /**
     -----------------------------------------------------
     Serialization
     */
    //@{
    HL_FRIEND_SERIALIZATION_ACCESS
    ;

    template<class Archive>
    void
    serialize(Archive &ar, const HLS version)
    {
        HL_SERIALIZE_BASE_CLASS(HL_InterpControls);


    }
    //@} Serialization -----------------------------------

public:
    /**
     Constructors & destructors
     */
    //@{
    HL_n_D_MultiLinearInterpControls();

    virtual ~HL_n_D_MultiLinearInterpControls();
    //@}

    /**
     Public class interface
     */
    //@{

    virtual HL_InterpolatorType get_InterpolatorType() const
    {
        return HL_InterpolatorType_n_D_Linear;

    }

    HLS nLocalityPoints(HLS dimIdx) const
    {
       /*
        * Linear methods are local
        * */
      return 0;
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

    //@}

}
; // end class HL_n_D_MultiLinearInterpControls

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_n_D_MultiLinearInterp
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131227
\brief Multilinear interpolator on a regular interpolation grid.
*/
class HL_n_D_MultiLinearInterp : public virtual HL_Interpolator
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

        HL_SERIALIZE_BASE_CLASS(HL_Interpolator);

    }
    //@} Serialization -----------------------------------

public:


    /**
    Constructors & destructors
    */
    //@{

    HL_n_D_MultiLinearInterp();

    virtual ~HL_n_D_MultiLinearInterp();
    //@}


    /**
    Public class interface
    */
    //@{


    HLR operator()(const VEC::const_iterator & b, const VEC::const_iterator & e) const;
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

    void scanNeighbours(HLMIDX neighbour, HLR weight) const;


    //@}

protected:

    /**
    Class variables
    */
    //@{


    //@}


    /**
    Service class variables
    */
    //@{




    mutable HLR weightedValue_;
    //@}


}
; // end class HL_n_D_MultiLinearInterp


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_n_D_MultiLinearInterp: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



void HL_TEST_HL_n_D_MultiLinearInterp();


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class Prova
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



/**
\author autore
\date 20140106

\brief breve. breve1

dettagli
*/
class Prova
{
public:

    /**
    questo enum
    */
    enum ENUM
    {
        /**
        valore 1
        */
        V_1,
        /**
        valore 2
        */
        V_2
    };

    /**
    costruttore. cos.

    dett costr
    */
    Prova()
    {}



    /**
    f. f.

    dett f
    */
    void f()
    {}


    void g();


protected:



    /**
    \name gruppo. g.

    dett. g.
    */
    //@{
    /**
    a. a.

    d.a.
    */
    HLS a;

    /**
    r. r.

    d.r.
    */
    HLR r;
    //@}
};


} // end namespace HL_Interpolation
} // end namespace HL_Math
} //end namespace HorizonLib


#endif // _hl_multiLinearInterp_h_
