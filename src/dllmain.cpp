

#include "common.h"


namespace Proxy
{

std::unique_ptr< Config > s_theConfig;
std::unique_ptr< Log > s_theLogger;
std::unique_ptr< Loader > s_theLoader;
std::unique_ptr< EFM > s_theEFMProxy;

}


// Must have one of these!
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulReason, LPVOID lpReserved)
{
  switch (ulReason)
  {
    case DLL_PROCESS_ATTACH:
    {
      Proxy::s_theLoader = std::make_unique< Proxy::Loader >( hModule );
      Proxy::s_theConfig = std::make_unique< Proxy::Config >( Proxy::s_theLoader->ModuleFilepath() );
      Proxy::s_theLogger = std::make_unique< Proxy::Log >( *Proxy::s_theConfig );

      // configure the logger
      Proxy::s_theLogger->Configure();

    } break;

    case DLL_PROCESS_DETACH:
    {
      Proxy::s_theLogger.reset();
      Proxy::s_theConfig.reset();
      Proxy::s_theLoader.reset();
    } break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    {
    } break;

  }
  return TRUE;
}