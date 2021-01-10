///////////////////////////////////////////////////////////////////////
// Simple proxy for DCS efm's so don't have to restart DCS every time
//
//
#ifndef __EFM_PROXY_COMMON_H__
#define __EFM_PROXY_COMMON_H__

/// For Windows support
#include <SDKDDKVer.h>
// Always!
#define WIN32_LEAN_AND_MEAN   
#include <windows.h>

#define EXPORT_ED_FM_PHYSICS_IMP extern "C" __declspec(dllexport)

/// Now for DCS headers.  These are the ones shipped with your install copy.  See the API folder!
#include "FM/wHumanCustomPhysicsAPI_ImplementationDeclare.h"


/// Used for debugging!
/// This goes to OutputDebugStringA()
void ToLog( const char* message, ... );


#endif /* __EFM_PROXY_COMMON_H__ */
