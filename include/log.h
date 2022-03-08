///////////////////////////////////////////////////////////////////////
// Simple proxy for DCS efm's so don't have to restart DCS every time
//
//
//
#ifndef __EFM_PROXY_LOGGER_H__
#define __EFM_PROXY_LOGGER_H__

#include "os.h"
#include "config.h"


namespace Proxy
{

/// Used for debugging!
/// This goes to OutputDebugStringA()
void ToLog( const char* message, ... );

class Log
{
  const Config& m_theConfig;

  bool m_useOutputDebug = true;
  // if we do the console window
  bool m_consoleEnabled = false;
  
  // Runtime Console support
  //@{
  bool m_consoleWindowAlloced = false;
  FILE* m_hConsoleStdOutRedirect = nullptr;
  FILE* m_hConsoleStdErrRedirect = nullptr;
  
  Config::ConsoleLoggingModes m_consoleMode = Config::ConsoleLoggingModes::Both;

  //@}
  void CreateConsoleWindow();
  void ReleaseConsoleWindow();

  void ConfigureConsole();


public:
  Log( const Config& theConfig );
  ~Log();

  // read the config object and do what is need
  void Configure();

  void StdOut( const char* strMessage, ... );
  void StdErr( const char* strMessage, ... );

  void StdOutArg( const char* strMessage, va_list& args );
  void StdErrArg( const char* strMessage, va_list& args );

};

}



#endif /* __EFM_PROXY_LOGGER_H__ */
