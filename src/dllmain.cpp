#include "loader.h"
//#include "efm.h"

#include <memory>


// Must have one of these!
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ulReason, LPVOID lpReserved)
{
  switch (ulReason)
  {
    case DLL_PROCESS_ATTACH:
    {
      Proxy::Loader::Set( hModule );
    } break;

    case DLL_PROCESS_DETACH:
    {
    } break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    {
    } break;

  }
  return TRUE;
}