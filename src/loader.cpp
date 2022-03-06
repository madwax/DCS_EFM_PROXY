///////////////////////////////////////////////////////////////////////
// Simple proxy for DCS efm's so don't have to restart DCS every time
//
// 
// 
#include "loader.h"

namespace Proxy
{

HMODULE Loader::s_hModule = nullptr;
std::filesystem::path Loader::s_moduleFilepath;

void Loader::Set( HMODULE hModule )
{
  Loader::s_hModule = hModule;

  constexpr DWORD MaxBuffSize = 1024;

  char tmpBuff[ MaxBuffSize ] = {};

  ::GetModuleFileNameA( Loader::s_hModule, tmpBuff, MaxBuffSize );

  Loader::s_moduleFilepath = std::filesystem::path( tmpBuff );
}


const std::filesystem::path& Loader::ModuleFilepath()
{
  return Loader::s_moduleFilepath;
}


Loader::Loader()
{
}


Loader::~Loader()
{
}


bool Loader::Load( const std::filesystem::path& filepath )
{
  this->m_hDLL = ::LoadLibraryA( filepath.string().c_str() );
  return ( this->m_hDLL != nullptr );
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

