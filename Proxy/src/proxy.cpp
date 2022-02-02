#include "proxy.h"

// RHC - Turns out Windows now has safe string functions!?? I'm showing my age!
#include <strsafe.h>


#define MAX_LOG_REPORT_SIZE 1024

static char strFilePathOfProxy[ MAX_PROXY_FILEPATH ];
static char strLogBuffer[ MAX_LOG_REPORT_SIZE ];

// The current realEFM 
static EFM* pEFM = NULL;

void ToLog( const char* message, ... )
{
  va_list args;
  va_start( args, message );
  ::StringCbVPrintfA( strLogBuffer, MAX_LOG_REPORT_SIZE, message, args );
  va_end( args );

  ::OutputDebugStringA( strLogBuffer );
}

// Must have one of these!
BOOL APIENTRY DllMain( HMODULE hModule, DWORD ulReason, LPVOID lpReserved )
{
  switch( ulReason )
  {
    case DLL_PROCESS_ATTACH:
    {
      // Alway zero the mem!
      ::ZeroMemory( strFilePathOfProxy, MAX_PROXY_FILEPATH );  
      ::GetModuleFileNameA( hModule, strFilePathOfProxy, MAX_PROXY_FILEPATH );

      ToLog( "=====================================================\n" );
      ToLog( "==== The Proxy EFM is : %s", strFilePathOfProxy );
      ToLog( "=====================================================\n" );
    } break;

    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
    {
    } break;
  }
  return TRUE;
}


static EFM* Get() 
{
  if( pEFM == NULL )
  {
    // need to tell someone that there is a problem!
    ToLog( "=====================================================\n" );
    ToLog( "==             DCS EMF PROXY ERRROR                ==\n" );
    ToLog( "=====================================================\n" );
    ToLog( "======= HAVING TO CREATE Real EFM out of Sync =======\n" );
    ToLog( "=====================================================\n" );

    pEFM = new EFM();
    if( pEFM->Load( strFilePathOfProxy ) == false )
    {
      ToLog( "Failed to load the real EFM!!!!!\n" );
      ::DebugBreak();
    }
    else
    {
      ToLog( "The Real EFM Is Loaded!" );
    }
  }
  return pEFM;
}


void ed_fm_set_plugin_data_install_path( const char* path )
{
  if( pEFM != NULL )
  {
    ToLog( "=====================================================\n" );
    ToLog( "==             DCS EMF PROXY ERRROR                ==\n" );
    ToLog( "=====================================================\n" );
    ToLog( "=====  Already have existing real EFM loaded   ======\n" );
    ToLog( "=====================================================\n" );

    delete pEFM;
    pEFM = NULL;
  }

  
  pEFM = new EFM();
  if( pEFM->Load( strFilePathOfProxy ) == false )
  {
    ToLog( "======  ERROR  Failed create/load the real EFM  ====\n" );
    ::DebugBreak();
  }
  else
  {
    ToLog( "=====================================================\n" );
    ToLog( "====                Loaded Real EFM              ====\n" );
    ToLog( " The Install Path : %s\n", path );
    pEFM->set_plugin_data_install_path( path );


  }
}


void ed_fm_release()
{
  if( pEFM == NULL )
  {
    ToLog( "=====================================================\n" );
    ToLog( "==             DCS EMF PROXY ERRROR                ==\n" );
    ToLog( "=====================================================\n" );
    ToLog( "======             NO EFM ON RELEASE           ======\n" );
    ToLog( "=====================================================\n" );
  }
  else
  {
    pEFM->release();
    delete pEFM;
    pEFM = NULL;

    ToLog( "=====================================================\n" );
    ToLog( "====             Released Real EFM               ====\n" );
    ToLog( "=====================================================\n" );
  }
}

void ed_fm_cold_start()
{
  Get()->cold_start();
}

void ed_fm_hot_start()
{
  Get()->hot_start();
}

void ed_fm_hot_start_in_air()
{
  Get()->hot_start_in_air();
}

void ed_fm_add_local_force( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  Get()->add_local_force( x, y, z, pos_x, pos_y, pos_z );
}

void ed_fm_add_global_force( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  Get()->add_global_force( x, y, z, pos_x, pos_y, pos_z );
}

bool ed_fm_add_local_force_component( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  return Get()->add_local_force_component( x, y, z, pos_x, pos_y, pos_z );
}

bool ed_fm_add_global_force_component( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  return Get()->add_global_force_component( x, y, z, pos_x, pos_y, pos_z );
}

void ed_fm_add_local_moment( double& x, double& y, double& z )
{
  Get()->add_local_moment( x, y, z );
}

void ed_fm_add_global_moment( double& x, double& y, double& z )
{
  Get()->add_global_moment( x, y, z );
}

bool ed_fm_add_local_moment_component( double& x, double& y, double& z )
{
  return Get()->add_local_moment_component( x, y, z );
}

bool ed_fm_add_global_moment_component( double& x, double& y, double& z )
{
  return Get()->add_global_moment_component( x, y, z );
}

void ed_fm_simulate( double dt )
{
  Get()->simulate( dt );
}

void ed_fm_set_surface( double h, double h_obj, unsigned surface_type, double normal_x, double normal_y, double normal_z )
{
  Get()->set_surface( h, h_obj, surface_type, normal_x, normal_y, normal_z );
}

void ed_fm_set_atmosphere( double h, double t, double a, double ro, double p, double wind_vx, double wind_vy, double wind_vz )
{
  Get()->set_atmosphere( h, t, a, ro, p, wind_vx, wind_vy, wind_vz );
}

void ed_fm_wind_vector_field_update_request( wind_vector_field& in_out )
{
  Get()->wind_vector_field_update_request( in_out );
}

void ed_fm_wind_vector_field_done()
{
  Get()->wind_vector_field_done();
}

void ed_fm_set_current_mass_state( double mass, double center_of_mass_x, double center_of_mass_y, double center_of_mass_z, double moment_of_inertia_x, double moment_of_inertia_y, double moment_of_inertia_z )
{
  Get()->set_current_mass_state( mass, center_of_mass_x, center_of_mass_y, center_of_mass_z, moment_of_inertia_x, moment_of_inertia_y, moment_of_inertia_z );
}

void ed_fm_set_current_state( double ax, double ay, double az, double vx, double vy, double vz, double px, double py, double pz, double omegadotx, double omegadoty, double omegadotz, double omegax, double omegay, double omegaz, double quaternion_x, double quaternion_y, double quaternion_z, double quaternion_w )
{
  Get()->set_current_state( ax, ay, az, vx, vy, vz, px, py, pz, omegadotx, omegadoty, omegadotz, omegax, omegay, omegaz, quaternion_x, quaternion_y, quaternion_z, quaternion_w );
}

void ed_fm_set_current_state_body_axis( double ax, double ay, double az, double vx, double vy, double vz, double wind_vx, double wind_vy, double wind_vz, double omegadotx, double omegadoty, double omegadotz, double omegax, double omegay, double omegaz, double yaw, double pitch, double roll, double common_angle_of_attack, double common_angle_of_slide )
{
  Get()->set_current_state_body_axis( ax, ay, az, vx, vy, vz, wind_vx, wind_vy, wind_vz, omegadotx, omegadoty, omegadotz, omegax, omegay, omegaz, yaw, pitch, roll, common_angle_of_attack, common_angle_of_slide );
}

void ed_fm_set_command( int command, float value )
{
  Get()->set_command( command, value );
}

bool ed_fm_change_mass( double& delta_mass, double& delta_mass_pos_x, double& delta_mass_pos_y, double& delta_mass_pos_z, double& delta_mass_moment_of_inertia_x, double& delta_mass_moment_of_inertia_y, double& delta_mass_moment_of_inertia_z )
{
  return Get()->change_mass( delta_mass, delta_mass_pos_x, delta_mass_pos_y, delta_mass_pos_z, delta_mass_moment_of_inertia_x, delta_mass_moment_of_inertia_y, delta_mass_moment_of_inertia_z );
}

void ed_fm_set_internal_fuel( double fuel )
{
  Get()->set_internal_fuel( fuel );
}

double ed_fm_get_internal_fuel()
{
  return Get()->get_internal_fuel();
}

void ed_fm_set_external_fuel( int station, double fuel, double x, double y, double z )
{
  Get()->set_external_fuel( station, fuel, x, y, z );
}

double ed_fm_get_external_fuel()
{
  return Get()->get_external_fuel();
}

void ed_fm_refueling_add_fuel( double fuel )
{
  Get()->refueling_add_fuel( fuel );
}

void ed_fm_set_draw_args( EdDrawArgument* array, size_t size )
{
  Get()->set_draw_args( array, size );
}

void ed_fm_set_fc3_cockpit_draw_args( EdDrawArgument* array, size_t size )
{
  Get()->set_fc3_cockpit_draw_args( array, size );
}

double ed_fm_get_shake_amplitude()
{
  return Get()->get_shake_amplitude();
}

void ed_fm_configure( const char* cfg_path )
{
  Get()->configure( cfg_path );
}

double ed_fm_get_param( unsigned param_enum )
{
  return Get()->get_param( param_enum );
}

// targets! <<<
bool ed_fm_make_balance( double& ax, double& ay, double& az, double& vx, double& vy, double& vz, double& omegadotx, double& omegadoty, double& omegadotz, double& omegax, double& omegay, double& omegaz, double& yaw, double& pitch, double& roll )
{
  return Get()->make_balance( ax, ay, az, vx, vy, vz, omegadotx, omegadoty, omegadotz, omegax, omegay, omegaz, yaw, pitch, roll );
}

bool ed_fm_enable_debug_info()
{
  return Get()->enable_debug_info();
}

size_t ed_fm_debug_watch( int level, char* buffer, size_t maxlen )
{
  return Get()->debug_watch( level, buffer, maxlen );
}


void ed_fm_on_planned_failure( const char* name )
{
  Get()->on_planned_failure( name );
}

void ed_fm_on_damage( int element, double element_integrity_factor )
{
  Get()->on_damage( element, element_integrity_factor );
}

void ed_fm_repair()
{
  Get()->repair();
}

bool ed_fm_need_to_be_repaired()
{
  return Get()->need_to_be_repaired();  
}

void ed_fm_set_immortal( bool value )
{
  Get()->set_immortal( value );
}

void ed_fm_unlimited_fuel( bool value )
{
  Get()->unlimited_fuel( value );
}

void ed_fm_set_easy_flight( bool value )
{
  Get()->set_easy_flight( value );
}

void ed_fm_set_property_numeric( const char* property_name, float value )
{
  Get()->set_property_numeric( property_name, value );
}

void ed_fm_set_property_string( const char* property_name, const char* value )
{
  Get()->set_property_string( property_name, value );
}

bool ed_fm_pop_simulation_event( ed_fm_simulation_event& out )
{
  return Get()->pop_simulation_event( out );
}

bool ed_fm_push_simulation_event( const ed_fm_simulation_event& in )
{
  return Get()->push_simulation_event( in );
}

void ed_fm_suspension_feedback( int idx, const ed_fm_suspension_info* info )
{
  Get()->suspension_feedback( idx, info );
}

bool ed_fm_LERX_vortex_update( unsigned idx, LERX_vortex& out )
{
  return Get()->LERX_vortex_update( idx, out );
}

