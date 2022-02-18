///////////////////////////////////////////////////////////////////////
// Simple proxy for DCS efm's so don't have to restart DCS every time
//
//
//
#ifndef __EFM_PROXY_COMMON_H__
#define __EFM_PROXY_COMMON_H__

#include "os.h"

namespace Proxy
{

/// Used for debugging!
/// This goes to OutputDebugStringA()
void ToLog( const char* message, ... );

}

#endif /* __EFM_PROXY_COMMON_H__ */
