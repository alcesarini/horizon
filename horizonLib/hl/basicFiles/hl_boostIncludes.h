/**
FILE NAME= hl_boostIncludes.h
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131121
*/
#ifndef _hl_boostIncludes_h_
#define _hl_boostIncludes_h_

#define BOOST_SYSTEM_NO_DEPRECATED

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//Use pragmas to disable warnings from boost files
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#pragma GCC diagnostic push // remember previous diagnostic info
#pragma GCC diagnostic ignored "-Wall" // disable diagnostic
#pragma GCC diagnostic ignored "-Wextra" // disable diagnostic
#pragma GCC diagnostic ignored "-Wunused-local-typedefs" // disable diagnostic
#pragma GCC diagnostic ignored "-Wunused-variable" // disable diagnostic





//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//BOOST INCLUDES (must go before anything other, for some reason actually not understood)
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------



#include <boost/config.hpp>
#include <boost/limits.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/variant.hpp>
#include <boost/pool/pool_alloc.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/attributes/timer.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/support/date_time.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

#include <boost/exception/all.hpp>
#include <boost/foreach.hpp>

#include <boost/logic/tribool.hpp>

/* 
To eliminate this warning when including the following bunch of serialization-related files
*/
//#pragma warning(disable:4244)

#include <boost/serialization/export.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/iostreams/stream_buffer.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/back_inserter.hpp>


/*
serialization
*/
#include <boost/serialization/utility.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/weak_ptr.hpp>
#include <boost/date_time/posix_time/time_serialize.hpp>


#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

/* 
Set the warning level to default value.
*/
//#pragma warning(default:4244)

/* 
UBLAS includes
*/
#include <boost/numeric/ublas/vector.hpp>

/* 
random
*/
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/math/tools/roots.hpp>

/*
math
*/

/*
probability distributions
*/
#include <boost/math/distributions/normal.hpp>



//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// BOOST UBLAS defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

#define VEC boost::numeric::ublas::vector<HLR>

#define MATRIX boost::numeric::ublas::matrix<HLR>


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// BOOST generic defines
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------


#define BSP boost::shared_ptr
#define BWP boost::weak_ptr

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// BOOST using
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

using namespace boost::gregorian;
using namespace boost::posix_time;

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
//Use pragmas to disable warnings from boost files
//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------

/*
 * restore the previous diagnostic setup, taken by the push pragma before entering the file
 * */
#pragma GCC diagnostic pop

#endif // _hl_boostIncludes_h_ 
