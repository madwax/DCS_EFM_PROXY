///////////////////////////////////////////////////////////////////////
// Simple proxy for DCS efm's so don't have to restart DCS every time
//
//
//
#include "config.h"
#include "os.h"


namespace Proxy
{

Config::Config( const std::filesystem::path& modulePath )
  : m_modulePath( modulePath )
  , m_filepath( modulePath.parent_path() / std::filesystem::path( "efm.proxy.ini" ) )
{
}


Config::~Config()
{
}


bool Config::ReadBoolean(const wchar_t* section, const wchar_t* key, bool defaultValue ) const
{
  constexpr DWORD ValueBufferSize = 24;
  wchar_t valueBuffer[ ValueBufferSize ] = {};

  const DWORD used = ::GetPrivateProfileStringW( section
    , key
    , ( defaultValue ) ? L"true" : L"false" 
    , valueBuffer
    , ValueBufferSize
    , m_filepath.wstring().c_str()
  );

  if( wcscmp( valueBuffer, L"true" ) == 0 || wcscmp( valueBuffer, L"True" ) == 0 || wcscmp( valueBuffer, L"TRUE" ) == 0 || wcscmp( valueBuffer, L"1" ) == 0 )
  {
    return true;
  }
  return false;
}


std::filesystem::path Config::TargetDLL() const
{
  // workout the default 
  std::filesystem::path defaultDLL = m_modulePath.stem().wstring() + L".real.dll";

  constexpr DWORD ValueBufferSize = 1024;
  wchar_t valueBuffer[ ValueBufferSize ] = {};

  const DWORD used = ::GetPrivateProfileStringW( L"General"
    , L"target"
    , defaultDLL.wstring().c_str()
    , valueBuffer
    , ValueBufferSize
    , m_filepath.wstring().c_str()
  );

  std::filesystem::path target;

  if( used == 0 )
  {
    target = defaultDLL;
  }
  else
  {
    target = valueBuffer;
  }

  // The user might want the dll anywere they want
  if( target.is_absolute() )
  {
    return target;
  }

  // it's relative
  std::filesystem::path result = std::filesystem::canonical( m_modulePath.parent_path() / target );
  return result;
}


bool Config::LogConsole() const
{
  return this->ReadBoolean( L"Log", L"console", false );
}


Config::ConsoleLoggingModes Config::LogConsoleMode() const
{
  constexpr DWORD ValueBufferSize = 48;
  wchar_t valueBuffer[ ValueBufferSize ] = {};

  const DWORD used = ::GetPrivateProfileStringW( L"Log"
    , L"mode"
    , L"both"
    , valueBuffer
    , ValueBufferSize
    , m_filepath.wstring().c_str()
  );

  if( wcscmp( valueBuffer, L"out" ) == 0 || wcscmp( valueBuffer, L"Out" ) == 0 || wcscmp( valueBuffer, L"OUT" ) == 0 )
  {
    return Config::ConsoleLoggingModes::StdOut;
  }

  if( wcscmp( valueBuffer, L"err" ) == 0 || wcscmp( valueBuffer, L"Err" ) == 0 || wcscmp( valueBuffer, L"ERR" ) == 0 )
  {
    return Config::ConsoleLoggingModes::StdErr;
  }

  return Config::ConsoleLoggingModes::Both;  
}



}
