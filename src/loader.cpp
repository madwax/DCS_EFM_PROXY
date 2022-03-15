///////////////////////////////////////////////////////////////////////
// Simple proxy for DCS efm's so don't have to restart DCS every time
//
// 
// 
#include "loader.h"
#include "log.h"

namespace 
{
std::filesystem::path GetModuleFilepath( HMODULE hModule )
{
  constexpr DWORD MaxBuffSize = 1024;

  wchar_t tmpBuff[ MaxBuffSize ] = {};

  ::GetModuleFileNameW( hModule, tmpBuff, MaxBuffSize );

  return std::filesystem::path( tmpBuff );
}

}

namespace Proxy
{


Loader::Loader( HMODULE hModule ) 
  : m_hModule( hModule )
  , m_moduleFilepath( GetModuleFilepath( hModule ) )
{
}


Loader::~Loader()
{
  this->Unload();
}


const std::filesystem::path& Loader::ModuleFilepath() const
{
  return Loader::m_moduleFilepath;
}


bool Loader::Load( const std::filesystem::path& filepath )
{
  Proxy:ToLog( "Loading the file : %s", filepath.string().c_str() );

  this->m_hDLL = ::LoadLibraryW( filepath.wstring().c_str() );
  if( this->m_hDLL == nullptr )
  {
    Proxy::ToLog( "Failed to Load : %s", filepath.string().c_str() );
    return false;
  }
  return true;
}


void Loader::Unload()
{
  if( this->m_hDLL != nullptr )
  {
    ::FreeLibrary( this->m_hDLL );
    this->m_hDLL = nullptr;
  }
}


FARPROC Loader::GetProc( const char* exportName ) const
{
  if( this->m_hDLL == nullptr || exportName == nullptr )
  {
    return nullptr;
  }
  return static_cast<FARPROC>(::GetProcAddress( m_hDLL, exportName ) );
}


}

