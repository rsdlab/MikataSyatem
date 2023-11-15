// -*- C++ -*-
/*!
 *
 * THIS FILE IS GENERATED AUTOMATICALLY!! DO NOT EDIT!!
 *
 * @file ManipulatorCommonInterface_CommonSkel.h 
 * @brief ManipulatorCommonInterface_Common server skeleton header wrapper code
 * @date Tue Nov 14 22:26:45 2023 
 *
 */

#ifndef MANIPULATORCOMMONINTERFACE_COMMONSKEL_H
#define MANIPULATORCOMMONINTERFACE_COMMONSKEL_H


#include <rtm/config_rtc.h>
#undef PACKAGE_BUGREPORT
#undef PACKAGE_NAME
#undef PACKAGE_STRING
#undef PACKAGE_TARNAME
#undef PACKAGE_VERSION

#if   defined ORB_IS_TAO
#  include "ManipulatorCommonInterface_CommonC.h"
#  include "ManipulatorCommonInterface_CommonS.h"
#elif defined ORB_IS_OMNIORB
#  if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#    ifdef USE_stub_in_nt_dll
#        undef USE_stub_in_nt_dll
#    endif
#    ifdef OpenRTM_IMPORT_SYMBOL
#        define USE_stub_in_nt_dll
#    endif
#  endif
#  include "ManipulatorCommonInterface_Common.hh"
//#  include "ManipulatorCommonInterface_CommonUtil.h"
#elif defined ORB_IS_MICO
#  include "ManipulatorCommonInterface_Common.h"
#elif defined ORB_IS_ORBIT2
#  include "/ManipulatorCommonInterface_Common-cpp-stubs.h"
#  include "/ManipulatorCommonInterface_Common-cpp-skels.h"
#elif defined ORB_IS_RTORB
#  include "ManipulatorCommonInterface_Common.h"
#elif defined ORB_IS_ORBEXPRESS
#  include "ManipulatorCommonInterface_Common.h"
#else
#  error "NO ORB defined"
#endif

#endif // MANIPULATORCOMMONINTERFACE_COMMONSKEL_H
