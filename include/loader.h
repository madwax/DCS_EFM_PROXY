///////////////////////////////////////////////////////////////////////
// Simple proxy for DCS efm's so don't have to restart DCS every time
//
//
//
#ifndef __EFM_PROXY_LOADER_H__
#define __EFM_PROXY_LOADER_H__

#include "os.h"

#include <string>
#include <filesystem>

namespace Proxy
{

// Super-simple dll loader and exports grabber
class Loader
{
  static HMODULE s_hModule;
  static std::filesystem::path s_moduleFilepath;

  HMODULE m_hDLL = nullptr;

  // The filepath of this dll
  std::filesystem::path m_dllFilepath;

public:
  // Call this on process attach in DLL main
  static void Set( HMODULE hModule );
  static const std::filesystem::path& ModuleFilepath();
  
  Loader();
  Loader( const Loader& ) = delete;
  Loader( Loader&& ) = delete;
  virtual ~Loader();

  void operator = ( const Loader& ) = delete;
  void operator = ( Loader&& ) = delete;

  // Loads the DLL. 
  bool Load( const std::filesystem::path& filepath );

  // Unload the DLL
  void Unload();

  // Get an export function
  FARPROC GetProc( const char* exportName ) const;
};

}

#endif /* __EFM_PROXY_LOADER_H__ */