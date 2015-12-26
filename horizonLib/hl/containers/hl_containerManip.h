/**
FILE NAME=hl_containerManip.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131230
*/
#ifndef _hl_containerManip_h_
#define _hl_containerManip_h_

#include <hl/basicFiles/hl_basicIncludes.h>



namespace HorizonLib
{

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Pair: operator<<
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


template <class KEYTYPE, class OBJTYPE>
inline std::ostream & operator<<(std::ostream & os, const std::pair<KEYTYPE, OBJTYPE> & p)
{

    os << "\n{";
    os << "1st=" << p.first << ", 2nd=" << p.second << "\n";
    os << "}";

    return os;

} // end operator<<

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Container: operator<<
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


template <class Container>
inline std::ostream & hl_container_description(std::ostream & os, const Container & container)
{

    os << "\n{";
    typename Container::const_iterator cIt = container.begin();

    if(cIt!=container.end()){
        while(true)
        {
            os << *cIt;
            ++cIt;
            if(cIt==container.end())
                break;
            os << ", ";
        } // end while
    } // end if

    os << "}";

    return os;

} // end hl_container_description

//------------------------------------------------------------------------------------------------------

#define HL_CONTAINER_DESCRIPTION(ContainerType) \
    template <class T>\
    inline std::ostream & operator<<(std::ostream & os, const ContainerType<T> & container)\
{\
    return hl_container_description(os, container);\
}

//------------------------------------------------------------------------------------------------------

HL_CONTAINER_DESCRIPTION(std::vector);

//------------------------------------------------------------------------------------------------------

HL_CONTAINER_DESCRIPTION(std::set);

//------------------------------------------------------------------------------------------------------

HL_CONTAINER_DESCRIPTION(boost::numeric::ublas::vector);

//------------------------------------------------------------------------------------------------------

template <class KEYTYPE, class OBJTYPE>
inline std::ostream & operator<<(std::ostream & os, const std::map<KEYTYPE, OBJTYPE> & container)
{
    return hl_container_description(os, container);
}


//------------------------------------------------------------------------------------------------------

template <class Container>
inline HLSTRING hl_container_description(const Container & container)
{

    std::stringstream ss;
    ss << container;

    return ss.str();
} // end hl_container_description







} //end namespace HorizonLib


#endif // _hl_containerManip_h_
