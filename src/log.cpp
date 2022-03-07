///////////////////////////////////////////////////////////////////////
// Simple proxy for DCS efm's so don't have to restart DCS every time
//
// 
//
#include "common.h"

#include "os.h"

#include <strsafe.h>

namespace Proxy
{

void ToLog( const char* strMessage, ... )
{
  va_list args;
  va_start( args, strMessage );
  s_theLogger->StdOutArg( strMessage, args );
  va_end( args );
}


Log::Log( const Config& theConfig )
  : m_theConfig( theConfig )
{
}


void Log::Configure()
{
  this->StdOut( "=== Doing a Logging System Reconfigure ===" );

  this->m_consoleEnabled = this->m_theConfig.LogConsole();
  if( this->m_consoleEnabled )
  {
    this->StdOut( "ConsoleEnabled = true" );
  }
  else
  {
    this->StdOut( "ConsoleEnabled = false" );
  }

  switch( this->m_theConfig.LogConsoleMode() )
  {
    case Config::ConsoleLoggingModes::Both:
    {
      this->StdOut( "Console Mode = both" );
    } break;

    case Config::ConsoleLoggingModes::StdOut:
    {
      this->StdOut( "Console Mode = Out" );
    } break;
  
    case Config::ConsoleLoggingModes::StdErr:
    {
      this->StdOut( "Console Mode = Err" );
    } break;

    default:
    {
      this->StdOut( "Console Mode = Unknown" );
    } break;
  }

}


void Log::StdOut( const char* strMessage, ... )
{
  va_list args;
  va_start( args, strMessage );
  this->StdOutArg( strMessage, args );
  va_end( args );
}


void Log::StdOutArg( const char* strMessage, va_list& args )
{
  if( m_useOutputDebug )
  {
    constexpr size_t MaxLogReportStringSize = 1024;
    char strLogBuffer[ MaxLogReportStringSize ] = {};

    ::StringCbVPrintfA( strLogBuffer, MaxLogReportStringSize, strMessage, args );
    ::OutputDebugStringA( strLogBuffer );
  }
  else
  {
    std::vfprintf( stdout, strMessage, args );
  }
}


void Log::StdErr( const char* strMessage, ... )
{
  va_list args;
  va_start( args, strMessage );
  this->StdOut( strMessage, args );
  va_end( args );
}


void Log::StdErrArg( const char* strMessage, va_list& args )
{
  if( m_useOutputDebug )
  {
    constexpr size_t MaxLogReportStringSize = 1024;
    char strLogBuffer[ MaxLogReportStringSize ] = {};

    ::StringCbVPrintfA( strLogBuffer, MaxLogReportStringSize, strMessage, args );
    ::OutputDebugStringA( strLogBuffer );
  }
  else
  {
    std::vfprintf( stderr, strMessage, args );
  }
}


}
