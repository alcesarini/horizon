/**
FILE NAME= hl_modifier.cpp
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20150622
*/

#include <hl/patterns/hl_modifier.h>

HL_SERIALIZATION_CLASS_EXPORT_GUID(HL::HL_Modifier);
HL_SERIALIZATION_CLASS_EXPORT_GUID(HL::HL_ModifierCollection);


namespace HorizonLib
{


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Modifier
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_Modifier::HL_Modifier()
{

    classDefaultInit();



} // end HL_Modifier

//------------------------------------------------------------------------------------------------------

HL_Modifier::~HL_Modifier()
{
} // end ~HL_Modifier


//------------------------------------------------------------------------------------------------------

void HL_Modifier::classDefaultInit()
{

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_Modifier::descriptionImpl(std::ostream & os) const
{

    os << "HL_Modifier:\n";

    Descriptable::descriptionImpl(os);

    hl_fillDescriptionStream(vecSize());

} // end descriptionImpl


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_Modifier: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------




//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_ModifierCollection
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


HL_ModifierCollection::HL_ModifierCollection()
{

    classDefaultInit();



} // end HL_ModifierCollection

//------------------------------------------------------------------------------------------------------

HL_ModifierCollection::~HL_ModifierCollection()
{
} // end ~HL_ModifierCollection


//------------------------------------------------------------------------------------------------------

void HL_ModifierCollection::classDefaultInit()
{

    vecSize_=0;

} // end classDefaultInit

//------------------------------------------------------------------------------------------------------

void HL_ModifierCollection::descriptionImpl(std::ostream & os) const
{

    os << "HL_ModifierCollection:\n";

    HL_Modifier::descriptionImpl(os);

    hl_fillDescriptionStream(modifiers_);

} // end descriptionImpl

//------------------------------------------------------------------------------------------------------


void HL_ModifierCollection::set_modifiers(const std::vector<HL_ModifierPtr> & modifiers)
{

    modifiers_=modifiers;


    vecSize_=0;

    vecSizes_.resize(modifiers_.size());

    HLS i=0;
    BOOST_FOREACH(const HL_ModifierPtr & modifier, modifiers_)
    {

        HL_PNN(modifier);

        HLS vecSize = modifier->vecSize();
        vecSize_+=vecSize;
        vecSizes_[i]=vecSize;

        i++;

    } // end for modifier

} // end set_modifiers

//------------------------------------------------------------------------------------------------------

void HL_ModifierCollection::modify(const VEC::const_iterator & b, const VEC::const_iterator & e) const
{

    HL_SRE((e-b)==vecSize(), "(e-b)=" << (e-b) << ", vecSize()=" << vecSize());

    VEC::const_iterator cIt = b;

    std::vector<HLS>::const_iterator vecSize_cIt = vecSizes_.begin();

    BOOST_FOREACH(const HL_ModifierPtr & modifier, modifiers_)
    {

        VEC::const_iterator cItEnd = cIt + (*vecSize_cIt);

        modifier->modify(cIt, cItEnd);

        cItEnd = cIt;

    } // end for modifier


    //LAST(20150622);
    /*
    con questa nuova classe HL_ModifierPtr vai a considerare il bootstrap della curva come
    un oggetto da modificare (cioè il modifier modifica la curva, cioò modifica i nodi
    dell'interpolatore).
    a questo punto costruisci in generale l'azione di modificare un oggetto, poi una sequenza
    di azioni (magari annidate) ed il bootstrap srà un sottocaso di questo.

    da notare che i modifiers sono in geenrale streammabili, però non è detto all'atto
    pratico debbano per forza esserlo.. ovvero che sia utile che lo siano in pratica in tutti i casi..

    insomma avrai creato il concetto di modifica/calibrazione dei (parametri) di un modello...

    i parametri della curva da bootstrappare sono tali che se modifichi il parametro, l'effetto
    reale è la modifica di un nodo dell'oggetto (meramente matematico ovvero non parametrizzato)
    costituito dall'interpolatore.
    */
} // end modify


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// class HL_ModifierCollection: defines, utils
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



} //end namespace HorizonLib
