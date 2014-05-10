/**
FILE NAME= auto link
LIB= HorizonLib
ADDED BY= A. Cesarini
DATE= 20131117
*/
#ifndef _horizonLib_autolink_hpp_
#define _horizonLib_autolink_hpp_

//
//#include <boost/config.hpp>
//
//// select toolset:
//#if (_MSC_VER < 1310)
//#  error "unsupported Microsoft compiler"
//#elif (_MSC_VER == 1310)
//#  define HL_LIB_TOOLSET "vc71"
//#elif (_MSC_VER == 1400)
//#  define HL_LIB_TOOLSET "vc80"
//#elif (_MSC_VER == 1500)
//#  define HL_LIB_TOOLSET "vc90"
//#elif (_MSC_VER == 1600)
//#  define HL_LIB_TOOLSET "vc100"
//#elif (_MSC_VER == 1700)
//#  define HL_LIB_TOOLSET "vc110"
//#else
//#  error "unknown Microsoft compiler"
//#endif
//
//#ifdef _M_X64
//#  define HL_LIB_PLATFORM "-x64"
//#else
//#  define HL_LIB_PLATFORM
//#endif
//
///*** libraries to be linked ***/
//
//// select thread opt:
//#ifdef _MT
//#  define HL_LIB_THREAD_OPT "-mt"
//#else
//#  define HL_LIB_THREAD_OPT
//#endif
//
//// select linkage opt:
//#ifdef _DLL
//#  if defined(_DEBUG)
//#    define HL_LIB_RT_OPT "-gd"
//#  else
//#    define HL_LIB_RT_OPT
//#  endif
//#else
//#  if defined(_DEBUG)
//#    define HL_LIB_RT_OPT "-sgd"
//#  else
//#    define HL_LIB_RT_OPT "-s"
//#  endif
//#endif
//
//#define HL_LIB_NAME "HorizonLib-" HL_LIB_TOOLSET HL_LIB_PLATFORM HL_LIB_THREAD_OPT HL_LIB_RT_OPT ".lib"
//
//#pragma comment(lib, HL_LIB_NAME)
//#ifdef BOOST_LIB_DIAGNOSTIC
//#  pragma message("Will (need to) link to lib file: " HL_LIB_NAME)
//#endif

#endif // _horizonLib_autolink_hpp_
