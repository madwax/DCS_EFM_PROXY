///////////////////////////////////////////////////////////////////////
// Simple proxy for DCS efm's so don't have to restart DCS every time
//
// 
//
#include "common.h"

#include "os.h"

#include <strsafe.h>


namespace 
{

void WhichStd( const Proxy::Config::ConsoleLoggingModes& mode, bool& stdOut, bool& stdErr )
{
  switch( mode )
  {
    case Proxy::Config::ConsoleLoggingModes::Both:
    {
      stdOut = true;
      stdErr = true;
    } break;

    case Proxy::Config::ConsoleLoggingModes::StdOut:
    {
      stdOut = true;
      stdErr = false;
    } break;

    case Proxy::Config::ConsoleLoggingModes::StdErr:
    {
      stdOut = false;
      stdErr = true;
    } break;

    default:
    {
      stdOut = false;
      stdErr = false;
    } break;
  }
}

}

namespace Proxy
{

void ToLog( const char* strMessage, ... )
{
  va_list args;
  va_start( args, strMessage );
  s_theLogger->StdOutArg( strMessage, args );
  va_end( args );
  s_theLogger->StdOut( "\n" );
}

Log::Log( const Config& theConfig )
  : m_theConfig( theConfig )
{
}

Log::~Log()
{
  this->ReleaseConsoleWindow();
}

void Log::ReleaseConsoleWindow()
{

  if( this->m_consoleWindowAlloced )
  {
    if( this->m_hConsoleStdOutRedirect != nullptr )
    {
      fclose( this->m_hConsoleStdOutRedirect );
      this->m_hConsoleStdOutRedirect = nullptr;
    }

    if( this->m_hConsoleStdErrRedirect != nullptr )
    {
      fclose( this->m_hConsoleStdErrRedirect );
      this->m_hConsoleStdErrRedirect = nullptr;
    }

    ::FreeConsole();

    m_consoleWindowAlloced = false;
  }
}

void Log::ConfigureConsole()
{
  const bool isToCreate = this->m_theConfig.LogConsole();
  if( isToCreate != this->m_consoleEnabled )
  {
    if( isToCreate )
    {
      if( AllocConsole() )
      {
        m_consoleWindowAlloced = true;

        bool stdOut, stdErr;

        WhichStd( this->m_theConfig.LogConsoleMode(), stdOut, stdErr );

        if( stdOut )
        {
          this->m_hConsoleStdOutRedirect = freopen("CONOUT$", "w", stdout);
        }
        if( stdErr )
        {
          this->m_hConsoleStdErrRedirect = freopen("CONOUT$", "w", stderr);
        }

        ::SetConsoleTitleW( L"DCS EFM Proxy Console Window" );
        m_useOutputDebug = false;
      }
      else
      {
        m_consoleWindowAlloced = false;
        ::OutputDebugStringA( "[ERRER] EFM Proxy Failed AllocConsole!!!!" );
      }
    }
    else
    {
      if( !isToCreate )
      {
        // switch back to OutputDebugString
        m_useOutputDebug = true;
      }

      if( m_consoleWindowAlloced )
      {
        this->ReleaseConsoleWindow();
      }
      else
      {
        fprintf( stdout, "Just reconfigured This is a stdout test for the console\n" );
        fprintf( stderr, "Just reconfigured This is a stderr test for the console\n" );
      }
    }
    this->m_consoleEnabled = isToCreate;
  }
}

void Log::Configure()
{
  // config the console stuff
  this->ConfigureConsole();

  this->StdOut( "Testing configure stdout\n" );
  this->StdErr( "Testing configure stderr\n" );
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
  this->StdErrArg( strMessage, args );
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
