///////////////////////////////////////////////////////////////////////
// Simple proxy for DCS efm's so don't have to restart DCS every time
//
//
//
#ifndef __EFM_PROXY_CONFIG_H__
#define __EFM_PROXY_CONFIG_H__

#include "os.h"

#include <string>
#include <filesystem>

namespace Proxy
{

class Config
{
  const std::filesystem::path& m_modulePath;
  const std::filesystem::path m_filepath;

  // We load everything 

  bool ReadBoolean(const wchar_t* section, const wchar_t* key, bool defaultValue = false ) const;

public:
  enum class ConsoleLoggingModes
  {
    Both = 0,
    StdOut,
    StdErr
  };


  Config( const std::filesystem::path& modulePath );
  ~Config();


  // Returns the path to the efm/cockpit dll
  std::filesystem::path TargetDLL() const;

  // enabled or more for the console log
  bool LogConsole() const;
  ConsoleLoggingModes LogConsoleMode() const;

};



} // Proxy


#endif /* __EFM_PROXY_CONFIG_H__ */