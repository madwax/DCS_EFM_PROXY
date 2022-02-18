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

void ToLog( const char* message, ... )
{
  constexpr size_t MaxLogReportStringSize = 1024;

  char strLogBuffer[ MaxLogReportStringSize ] = {};

  va_list args;
  va_start( args, message );
  ::StringCbVPrintfA( strLogBuffer, MaxLogReportStringSize, message, args );
  va_end( args );

  ::OutputDebugStringA( strLogBuffer );
}

}
