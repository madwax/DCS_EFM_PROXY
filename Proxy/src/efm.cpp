#include "efm.h"

#include <strsafe.h>


EFM::EFM()
{
  this->m_hEFM = NULL;

  this->m_add_local_force = NULL;
  this->m_add_global_force = NULL;
  this->m_add_local_force_component = NULL;
  this->m_add_global_force_component = NULL;
  this->m_add_local_moment = NULL;
  this->m_add_global_moment = NULL;
  this->m_add_local_moment_component = NULL;
  this->m_add_global_moment_component = NULL;
  this->m_simulate = NULL;
  this->m_set_surface = NULL;
  this->m_set_atmosphere = NULL;
  this->m_wind_vector_field_update_request = NULL;
  this->m_wind_vector_field_done = NULL;
  this->m_set_current_mass_state = NULL;
  this->m_set_current_state = NULL;
  this->m_set_current_state_body_axis = NULL;
  this->m_set_command = NULL;
  this->m_change_mass = NULL;
  this->m_set_internal_fuel = NULL;
  this->m_get_internal_fuel = NULL;
  this->m_set_external_fuel = NULL;
  this->m_get_external_fuel = NULL;
  this->m_refueling_add_fuel = NULL;
  this->m_set_draw_args = NULL;
  this->m_set_fc3_cockpit_draw_args = NULL;
  this->m_get_shake_amplitude = NULL;
  this->m_configure = NULL;
  this->m_release = NULL;
  this->m_get_param = NULL;
  this->m_cold_start = NULL;
  this->m_hot_start = NULL;
  this->m_hot_start_in_air = NULL;
  this->m_make_balance = NULL;
  this->m_enable_debug_info = NULL;
  this->m_debug_watch = NULL;
  this->m_set_plugin_data_install_path = NULL;
  this->m_on_planned_failure = NULL;
  this->m_on_damage = NULL;
  this->m_repair = NULL;
  this->m_need_to_be_repaired = NULL;
  this->m_set_immortal = NULL;
  this->m_unlimited_fuel = NULL;
  this->m_set_easy_flight = NULL;
  this->m_set_property_numeric = NULL;
  this->m_set_property_string = NULL;
  this->m_pop_simulation_event = NULL;
  this->m_push_simulation_event = NULL;
  this->m_suspension_feedback = NULL;
  this->m_LERX_vortex_update = NULL;
}

EFM::~EFM()
{
  if( this->m_hEFM != NULL )
  {
    ::FreeLibrary( this->m_hEFM );
    this->m_hEFM = NULL;
  }
}


FARPROC EFM::GetProc( const char* name )
{
  FARPROC ret = ::GetProcAddress( this->m_hEFM, name );
  if( ret == NULL )
  {
    ToLog( " - Failed to Load %s\n", name );
  }
  else
  {
    ToLog( " - Loaded %s\n", name );
  }
  return ret;
}


bool EFM::Load( const char* proxyEFMFilePath )
{
#define MAX_REAL_EFM_PATH ( MAX_PROXY_FILEPATH + MAX_PROXY_FILEPATH )

  char toLoadDll[ MAX_REAL_EFM_PATH ];
  ::ZeroMemory( toLoadDll, MAX_REAL_EFM_PATH );

  size_t sz = 0;
  ( void )::StringCchLengthA( proxyEFMFilePath, MAX_PROXY_FILEPATH, &sz );

  // HACK but we have the room ;)
  // should move to win32 funcs as well!
  ::memcpy( toLoadDll, proxyEFMFilePath, sz );
  ::strcpy( ( toLoadDll + ( sz - 4 ) ), ".real.dll" );

  ToLog( "The Real EFM will be : %s\n", toLoadDll );

  this->m_hEFM = ::LoadLibraryA( toLoadDll );
  if( this->m_hEFM == NULL )
  {
    const DWORD lastError = ::GetLastError();
 
    ToLog("=======================================================\n");
    ToLog("===== BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD BAD =====\n");
    ToLog("=======================================================\n");
    ToLog("===== Failed to load real EFM dll path: %s\n");
    ToLog("===== Win32 Error: %lu\n", lastError);
    ToLog("=======================================================\n");
    return false;
  }

  ToLog("=======================================================\n");
  ToLog("===== Loaded real EFM dll from path: %s\n");
  ToLog("=======================================================\n");

  this->m_add_local_force = ( PFN_FORCE_SOURCE )this->GetProc( "ed_fm_add_local_force" );
  this->m_add_global_force = ( PFN_FORCE_SOURCE )this->GetProc( "ed_fm_add_global_force" );
  this->m_add_local_force_component = ( PFN_FORCE_COMPONENT_SOURCE )this->GetProc( "ed_fm_add_local_force_component" );
  this->m_add_global_force_component = ( PFN_FORCE_COMPONENT_SOURCE )this->GetProc( "ed_fm_add_global_force_component" );
  this->m_add_local_moment = ( PFN_MOMENT_SOURCE )this->GetProc( "ed_fm_add_local_moment" );
  this->m_add_global_moment = ( PFN_MOMENT_SOURCE )this->GetProc( "ed_fm_add_global_moment" );
  this->m_add_local_moment_component = ( PFN_MOMENT_COMPONENT_SOURCE )this->GetProc( "ed_fm_add_local_moment_component" );
  this->m_add_global_moment_component = ( PFN_MOMENT_COMPONENT_SOURCE )this->GetProc( "ed_fm_add_global_moment_component" );
  this->m_simulate = ( PFN_SIMULATE )this->GetProc( "ed_fm_simulate" );
  this->m_set_surface = ( PFN_SET_SURFACE )this->GetProc( "ed_fm_set_surface" );
  this->m_set_atmosphere = ( PFN_SET_ATMOSPHERE )this->GetProc( "ed_fm_set_atmosphere" );
  this->m_wind_vector_field_update_request = ( PFN_WIND_VECTOR_FIELD_UPDATE_REQUEST )this->GetProc( "ed_fm_wind_vector_field_update_request" );
  this->m_wind_vector_field_done = ( PFN_WIND_VECTOR_FIELD_DONE )this->GetProc( "ed_fm_wind_vector_field_done" );
  this->m_set_current_mass_state = ( PFN_CURRENT_MASS_STATE )this->GetProc( "ed_fm_set_current_mass_state" );
  this->m_set_current_state = ( PFN_CURRENT_STATE )this->GetProc( "ed_fm_set_current_state" );
  this->m_set_current_state_body_axis = ( PFN_CURRENT_STATE_BODY_AXIS )this->GetProc( "ed_fm_set_current_state_body_axis" );
  this->m_set_command = ( PFN_SET_COMMAND )this->GetProc( "ed_fm_set_command" );
  this->m_change_mass = ( PFN_CHANGE_MASS )this->GetProc( "ed_fm_change_mass" );
  this->m_set_internal_fuel = ( PFN_SET_INTERNAL_FUEL )this->GetProc( "ed_fm_set_internal_fuel" );
  this->m_get_internal_fuel = ( PFN_GET_INTERNAL_FUEL )this->GetProc( "ed_fm_get_internal_fuel" );
  this->m_set_external_fuel = ( PFN_SET_EXTERNAL_FUEL )this->GetProc( "ed_fm_set_external_fuel" );
  this->m_get_external_fuel = ( PFN_GET_EXTERNAL_FUEL )this->GetProc( "ed_fm_get_external_fuel" );
  this->m_refueling_add_fuel = ( PFN_REFUELING_ADD_FUEL )this->GetProc( "ed_fm_refueling_add_fuel" );
  this->m_set_draw_args = ( PFN_SET_DRAW_ARGS )this->GetProc( "ed_fm_set_draw_args" );
  this->m_set_draw_args_v2 = ( PFN_SET_DRAW_ARGS_V2 )this->GetProc( "ed_fm_set_draw_args_v2" );
  this->m_set_fc3_cockpit_draw_args = ( PFN_SET_DRAW_ARGS )this->GetProc( "ed_fm_set_fc3_cockpit_draw_args" );
  this->m_set_fc3_cockpit_draw_args_v2 = ( PFN_SET_DRAW_ARGS_V2 )this->GetProc( "ed_fm_set_fc3_cockpit_draw_args_v2" );
  this->m_get_shake_amplitude = ( PFN_GET_SHAKE_AMPLITUDE )this->GetProc( "ed_fm_get_shake_amplitude" );
  this->m_configure = ( PFN_CONFIGURE )this->GetProc( "ed_fm_configure" );
  this->m_release = ( PFN_FM_RELEASE )this->GetProc( "ed_fm_release" );
  this->m_get_param = ( PFN_GET_PARAM )this->GetProc( "ed_fm_get_param" );
  this->m_cold_start = ( PFN_COLD_START )this->GetProc( "ed_fm_cold_start" );
  this->m_hot_start = ( PFN_HOT_START )this->GetProc( "ed_fm_hot_start" );
  this->m_hot_start_in_air = ( PFN_HOT_START_IN_AIR )this->GetProc( "ed_fm_hot_start_in_air" );
  this->m_make_balance = ( PFN_MAKE_BALANCE )this->GetProc( "ed_fm_make_balance" );
  this->m_enable_debug_info = ( PFN_ENABLE_DEBUG_INFO )this->GetProc( "ed_fm_enable_debug_info" );
  this->m_debug_watch = ( PFN_DEBUG_WATCH )this->GetProc( "ed_fm_debug_watch" );
  this->m_set_plugin_data_install_path = ( PFN_SET_PLUGIN_DATA_INSTALL_PATH )this->GetProc( "ed_fm_set_plugin_data_install_path" );
  this->m_on_planned_failure = ( PFN_ON_PLANNED_FAILURE )this->GetProc( "ed_fm_on_planned_failure" );
  this->m_on_damage = ( PFN_ON_DAMAGE )this->GetProc( "ed_fm_on_damage" );
  this->m_repair = ( PFN_REPAIR )this->GetProc( "ed_fm_repair" );
  this->m_need_to_be_repaired = ( PFN_NEED_TO_BE_REPAIRED )this->GetProc( "ed_fm_need_to_be_repaired" );
  this->m_set_immortal = ( PFN_FM_SET_IMMORTAL )this->GetProc( "ed_fm_set_immortal" );
  this->m_unlimited_fuel = ( PFN_FM_SET_UNLIMITED_FUEL )this->GetProc( "ed_fm_unlimited_fuel" );
  this->m_set_easy_flight = ( PFN_FM_SET_EASY_FLIGHT )this->GetProc( "ed_fm_set_easy_flight" );
  this->m_set_property_numeric = ( PFN_FM_SET_PROPERTY_NUMERIC )this->GetProc( "ed_fm_set_property_numeric" );
  this->m_set_property_string = ( PFN_FM_SET_PROPERTY_STRING )this->GetProc( "ed_fm_set_property_string" );
  this->m_pop_simulation_event = ( PFN_FM_POP_SIMULATION_EVENT )this->GetProc( "ed_fm_pop_simulation_event" );
  this->m_push_simulation_event = ( PFN_FM_PUSH_SIMULATION_EVENT )this->GetProc( "ed_fm_push_simulation_event" );
  this->m_suspension_feedback = ( PFN_FM_SUSPENSION_FEEDBACK )this->GetProc( "ed_fm_suspension_feedback" );
  this->m_LERX_vortex_update = ( PFN_FM_LERX_VORTEX_UPDATE )this->GetProc( "ed_fm_LERX_vortex_update" );

  return true;
}

void EFM::add_local_force( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  if( this->m_add_local_force != NULL )
  {
    ( *( this->m_add_local_force ) )( x, y, z, pos_x, pos_y, pos_z );
  }
}

void EFM::add_global_force( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  if( this->m_add_global_force != NULL )
  {
    ( *( this->m_add_global_force ) )( x, y, z, pos_x, pos_y, pos_z );
  }
}

bool EFM::add_local_force_component( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  if( this->m_add_local_force_component != NULL )
  {
    return ( *( this->m_add_local_force_component ) )( x, y, z, pos_x, pos_y, pos_z );
  }
  return false;
}

bool EFM::add_global_force_component( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  if( this->m_add_global_force_component != NULL )
  {
    return ( *( this->m_add_global_force_component ) )( x, y, z, pos_x, pos_y, pos_z );
  }
  return false;
}

void EFM::add_local_moment( double& x, double& y, double& z )
{
  if( this->m_add_local_moment != NULL )
  {
    ( *( this->m_add_local_moment ) )( x, y, z );
  }
}

void EFM::add_global_moment( double& x, double& y, double& z )
{
  if( this->m_add_global_moment != NULL )
  {
    ( *( this->m_add_global_moment ) )( x, y, z );
  }
}

bool EFM::add_local_moment_component( double& x, double& y, double& z )
{
  if( this->m_add_local_moment_component != NULL )
  {
    return ( *( this->m_add_local_moment_component ) )( x, y, z );
  }
  return false;
}

bool EFM::add_global_moment_component( double& x, double& y, double& z )
{
  if( this->m_add_global_moment_component != NULL )
  {
    return ( *( this->m_add_global_moment_component ) )( x, y, z );
  }
  return false;
}

void EFM::simulate( double dt )
{
  if( this->m_simulate != NULL )
  {
    ( *( this->m_simulate ) )( dt );
  }
}

void EFM::set_surface( double h, double h_obj, unsigned surface_type, double normal_x, double normal_y, double normal_z )
{
  if( this->m_set_surface != NULL )
  {
    ( *( this->m_set_surface ) )( h, h_obj, surface_type, normal_x, normal_y, normal_z );
  }
}

void EFM::set_atmosphere( double h, double t, double a, double ro, double p, double wind_vx, double wind_vy, double wind_vz )
{
  if( this->m_set_atmosphere != NULL )
  {
    ( *( this->m_set_atmosphere ) )( h, t, a, ro, p, wind_vx, wind_vy, wind_vz );
  }
}

void EFM::wind_vector_field_update_request( wind_vector_field& in_out )
{
  if( this->m_wind_vector_field_update_request != NULL )
  {
    ( *( this->m_wind_vector_field_update_request ) )( in_out );
  }
}

void EFM::wind_vector_field_done()
{
  if( this->m_wind_vector_field_done != NULL )
  {
    ( *( this->m_wind_vector_field_done ) )( );
  }
}

void EFM::set_current_mass_state( double mass, double center_of_mass_x, double center_of_mass_y, double center_of_mass_z, double moment_of_inertia_x, double moment_of_inertia_y, double moment_of_inertia_z )
{
  if( this->m_set_current_mass_state != NULL )
  {
    ( *( this->m_set_current_mass_state ) )( mass, center_of_mass_x, center_of_mass_y, center_of_mass_z, moment_of_inertia_x, moment_of_inertia_y, moment_of_inertia_z );
  }
}

void EFM::set_current_state( double ax, double ay, double az, double vx, double vy, double vz, double px, double py, double pz, double omegadotx, double omegadoty, double omegadotz, double omegax, double omegay, double omegaz, double quaternion_x, double quaternion_y, double quaternion_z, double quaternion_w )
{
  if( this->m_set_current_state != NULL )
  {
    ( *( this->m_set_current_state ) )( ax, ay, az, vx, vy, vz, px, py, pz, omegadotx, omegadoty, omegadotz, omegax, omegay, omegaz, quaternion_x, quaternion_y, quaternion_z, quaternion_w );
  }
}

void EFM::set_current_state_body_axis( double ax, double ay, double az, double vx, double vy, double vz, double wind_vx, double wind_vy, double wind_vz, double omegadotx, double omegadoty, double omegadotz, double omegax, double omegay, double omegaz, double yaw, double pitch, double roll, double common_angle_of_attack, double common_angle_of_slide )
{
  if( this->m_set_current_state_body_axis != NULL )
  {
    ( *( this->m_set_current_state_body_axis ) )( ax, ay, az, vx, vy, vz, wind_vx, wind_vy, wind_vz, omegadotx, omegadoty, omegadotz, omegax, omegay, omegaz, yaw, pitch, roll, common_angle_of_attack, common_angle_of_slide );
  }
}

void EFM::set_command( int command, float value )
{
  if( this->m_set_command != NULL )
  {
    ( *( this->m_set_command ) )( command, value );
  }
}

bool EFM::change_mass( double& delta_mass, double& delta_mass_pos_x, double& delta_mass_pos_y, double& delta_mass_pos_z, double& delta_mass_moment_of_inertia_x, double& delta_mass_moment_of_inertia_y, double& delta_mass_moment_of_inertia_z )
{
  if( this->m_change_mass != NULL )
  {
    return ( *( this->m_change_mass ) )( delta_mass, delta_mass_pos_x, delta_mass_pos_y, delta_mass_pos_z, delta_mass_moment_of_inertia_x, delta_mass_moment_of_inertia_y, delta_mass_moment_of_inertia_z );
  }
  return false;
}

void EFM::set_internal_fuel( double fuel )
{
  if( this->m_set_internal_fuel != NULL )
  {
    ( *( this->m_set_internal_fuel ) )( fuel );
  }
}

double EFM::get_internal_fuel()
{
  if( this->m_get_internal_fuel != NULL )
  {
    return ( *( this->m_get_internal_fuel ) )( );
  }
  return 0.0;
}

void EFM::set_external_fuel( int station, double fuel, double x, double y, double z )
{
  if( this->m_set_external_fuel != NULL )
  {
    ( *( this->m_set_external_fuel ) )( station, fuel, x, y, z );
  }
}

double EFM::get_external_fuel()
{
  if( this->m_get_external_fuel != NULL )
  {
    return ( *( this->m_get_external_fuel ) )( );
  }
  return 0.0;
}

void EFM::refueling_add_fuel( double fuel )
{
  if( this->m_refueling_add_fuel != NULL )
  {
    ( *( this->m_refueling_add_fuel ) )( fuel );
  }
}

void EFM::set_draw_args( EdDrawArgument* array, size_t size )
{
  if( this->m_set_draw_args != NULL )
  {
    ( *( this->m_set_draw_args ) )( array, size );
  }
}

void EFM::set_draw_args_v2( float* array, size_t size )
{
  if( this->m_set_draw_args_v2 != NULL )
  {
    ( *( this->m_set_draw_args_v2 ) )( array, size );
  }
}

void EFM::set_fc3_cockpit_draw_args( EdDrawArgument* array, size_t size )
{
  if( this->m_set_fc3_cockpit_draw_args != NULL )
  {
    ( *( this->m_set_fc3_cockpit_draw_args ) )( array, size );
  }
}

void EFM::set_fc3_cockpit_draw_args_v2( float* array, size_t size )
{
  if( this->m_set_fc3_cockpit_draw_args_v2 != NULL )
  {
    ( *( this->m_set_fc3_cockpit_draw_args_v2 ) )( array, size );
  }
}

double EFM::get_shake_amplitude()
{
  if( this->m_get_shake_amplitude != NULL )
  {
    return ( *( this->m_get_shake_amplitude ) )( );
  }
  return 0.0;
}

void EFM::configure( const char* cfg_path )
{
  if( this->m_configure != NULL )
  {
    ( *( this->m_configure ) )( cfg_path );
  }
}

void EFM::release()
{
  if( this->m_release != NULL )
  {
    ( *( this->m_release ) )( );
  }
}

double EFM::get_param( unsigned param_enum )
{
  if( this->m_get_param != NULL )
  {
    return ( *( this->m_get_param ) )( param_enum );
  }
  return 0.0;
}

void EFM::cold_start()
{
  if( this->m_cold_start != NULL )
  {
    ( *( this->m_cold_start ) )( );
  }
}

void EFM::hot_start()
{
  if( this->m_hot_start != NULL )
  {
    ( *( this->m_hot_start ) )( );
  }
}

void EFM::hot_start_in_air()
{
  if( this->m_hot_start_in_air != NULL )
  {
    ( *( this->m_hot_start_in_air ) )( );
  }
}

bool EFM::make_balance( double& ax, double& ay, double& az, double& vx, double& vy, double& vz, double& omegadotx, double& omegadoty, double& omegadotz, double& omegax, double& omegay, double& omegaz, double& yaw, double& pitch, double& roll )
{
  if( this->m_make_balance != NULL )
  {
    return ( *( this->m_make_balance ) )( ax, ay, az, vx, vy, vz, omegadotx, omegadoty, omegadotz, omegax, omegay, omegaz, yaw, pitch, roll );
  }
  return false;
}

bool EFM::enable_debug_info()
{
  if( this->m_enable_debug_info != NULL )
  {
    return ( *( this->m_enable_debug_info ) )( );
  }
  return false;
}

size_t EFM::debug_watch( int level, char* buffer, size_t maxlen )
{
  if( this->m_debug_watch != NULL )
  {
    return ( *( this->m_debug_watch ) )( level, buffer, maxlen );
  }
  return 0;
}

void EFM::set_plugin_data_install_path( const char* path )
{
  if( this->m_set_plugin_data_install_path != NULL )
  {
    ( *( this->m_set_plugin_data_install_path ) )( path );
  }
}

void EFM::on_planned_failure( const char* name )
{
  if( this->m_on_planned_failure != NULL )
  {
    ( *( this->m_on_planned_failure ) )( name );
  }
}

void EFM::on_damage( int element, double element_integrity_factor )
{
  if( this->m_on_damage != NULL )
  {
    ( *( this->m_on_damage ) )( element, element_integrity_factor );
  }
}

void EFM::repair()
{
  if( this->m_repair != NULL )
  {
    ( *( this->m_repair ) )( );
  }
}

bool EFM::need_to_be_repaired()
{
  if( this->m_need_to_be_repaired != NULL )
  {
    return ( *( this->m_need_to_be_repaired ) )( );
  }
  return false;
}

void EFM::set_immortal( bool value )
{
  if( this->m_set_immortal != NULL )
  {
    ( *( this->m_set_immortal ) )( value );
  }
}

void EFM::unlimited_fuel( bool value )
{
  if( this->m_unlimited_fuel != NULL )
  {
    ( *( this->m_unlimited_fuel ) )( value );
  }
}

void EFM::set_easy_flight( bool value )
{
  if( this->m_set_easy_flight != NULL )
  {
    ( *( this->m_set_easy_flight ) )( value );
  }
}

void EFM::set_property_numeric( const char* property_name, float value )
{
  if( this->m_set_property_numeric != NULL )
  {
    ( *( this->m_set_property_numeric ) )( property_name, value );
  }
}

void EFM::set_property_string( const char* property_name, const char* value )
{
  if( this->m_set_property_string != NULL )
  {
    ( *( this->m_set_property_string ) )( property_name, value );
  }
}

bool EFM::pop_simulation_event( ed_fm_simulation_event& out )
{
  if( this->m_pop_simulation_event != NULL )
  {
    return ( *( this->m_pop_simulation_event ) )( out );
  }
  return false;
}

bool EFM::push_simulation_event( const ed_fm_simulation_event& in )
{
  if( this->m_push_simulation_event != NULL )
  {
    return ( *( this->m_push_simulation_event ) )( in );
  }
  return false;
}

void EFM::suspension_feedback( int idx, const ed_fm_suspension_info* info )
{
  if( this->m_suspension_feedback != NULL )
  {
    ( *( this->m_suspension_feedback ) )( idx, info );
  }
}

bool EFM::LERX_vortex_update( unsigned idx, LERX_vortex& out )
{
  if( this->m_LERX_vortex_update != NULL )
  {
    return ( *( this->m_LERX_vortex_update ) )( idx, out );
  }
  return false;
}

