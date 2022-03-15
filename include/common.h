///////////////////////////////////////////////////////////////////////
// Simple proxy for DCS efm's so don't have to restart DCS every time
//
//
//
#ifndef __EFM_PROXY_COMMON_H__
#define __EFM_PROXY_COMMON_H__

#include "config.h"
#include "log.h"
#include "loader.h"
#include "efm.h"
#include "proxy.h"

namespace Proxy
{

extern std::unique_ptr< Config > s_theConfig;
extern std::unique_ptr< Log > s_theLogger;
extern std::unique_ptr< Loader > s_theLoader;
extern std::unique_ptr< EFM > s_theEFMProxy;

}

#endif /* __EFM_PROXY_COMMON_H__ */
