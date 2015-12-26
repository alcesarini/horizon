/**
FILE NAME= hl_mktQuote.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20140607
*/
#ifndef _hl_mktQuote_h_
#define _hl_mktQuote_h_

#include <hl/mktData/hl_mktData.h>
#include <hl/instruments/anagraphics/hl_anagraphics.h>

namespace HorizonLib
{
namespace HL_MarketData
{
namespace HL_MktQuotes
{




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktQuote
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/**
\author A. Cesarini
\date 20131213
\brief Base class for all mkt instrument quotation data (for ex. the 5y eur 6m swap par
rate should be represented by one instance of this class).

See comment to method get_correlation.
*/
class HL_MktQuote : public virtual HLSER::HL_Serializable, public virtual Descriptable
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
        HL_SER(value_);
        HL_SER(quotationTime_);
        HL_SER(anagraphicsPtr_);



    }
    //@} Serialization -----------------------------------

public:
    /**
    Constructors & destructors
    */
    //@{

    HL_MktQuote();

    virtual ~HL_MktQuote();
    //@}


    /**
    Public class interface
    */
    //@{



    HL_CLASS_VAR_ACCESS_METHODS(HLR, value);
    HL_CLASS_VAR_ACCESS_METHODS(ptime, quotationTime);
    HL_CLASS_VAR_ACCESS_METHODS(HL_AnagraphicsPtr, anagraphicsPtr);


    /**
    Unique tag for the mkt quote type.
    */
    HLSTRING mktQuoteType() const
    {
        return "mktQuote for " + anagraphicsPtr_->anagraphicsTypeString();
    }


    void checkMktQuote() const;
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
    The mktQuote is determined by a unique value (for ex. the mktQuote could
    represent a mktSwap contract andf the quote its par.
    */
    HLR value_;

    /**
     * The mktQuote is updated to some precise time specified by this class variable.
    */
    ptime quotationTime_;




    /**
    The quotation is referred to the instrument represented by this anagraphics.
    */
    HL_AnagraphicsPtr anagraphicsPtr_;
    //@}

}
; // end class HL_MktQuote


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_MktQuote: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define HL_MktQuotePtr BSP<HLMQS::HL_MktQuote>





} // end namespace HL_MktQuotes
} // end namespace HL_MarketData
} //end namespace HorizonLib


#endif // _hl_mktQuote_h_
