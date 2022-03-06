#include "common.h"
#include "efm.h"


namespace Proxy
{


EFM::EFM()
{
  Reset();
}


EFM::~EFM()
{
  Reset();
}


std::filesystem::path EFM::ConfigFilepath() const
{
  std::filesystem::path configFilepath = Loader::ModuleFilepath().parent_path() / std::filesystem::path("efm.proxy.ini");
  return configFilepath;
}


void EFM::Reset()
{
  this->m_add_local_force = nullptr;
  this->m_add_global_force = nullptr;
  this->m_add_local_force_component = nullptr;
  this->m_add_global_force_component = nullptr;
  this->m_add_local_moment = nullptr;
  this->m_add_global_moment = nullptr;
  this->m_add_local_moment_component = nullptr;
  this->m_add_global_moment_component = nullptr;
  this->m_simulate = nullptr;
  this->m_set_surface = nullptr;
  this->m_set_atmosphere = nullptr;
  this->m_wind_vector_field_update_request = nullptr;
  this->m_wind_vector_field_done = nullptr;
  this->m_set_current_mass_state = nullptr;
  this->m_set_current_state = nullptr;
  this->m_set_current_state_body_axis = nullptr;
  this->m_set_command = nullptr;
  this->m_change_mass = nullptr;
  this->m_set_internal_fuel = nullptr;
  this->m_get_internal_fuel = nullptr;
  this->m_set_external_fuel = nullptr;
  this->m_get_external_fuel = nullptr;
  this->m_refueling_add_fuel = nullptr;
  this->m_set_draw_args_v2 = nullptr;
  this->m_set_fc3_cockpit_draw_args_v2 = nullptr;
  this->m_set_draw_args = nullptr;
  this->m_set_fc3_cockpit_draw_args = nullptr;
  this->m_get_shake_amplitude = nullptr;
  this->m_configure = nullptr;
  this->m_release = nullptr;
  this->m_get_param = nullptr;
  this->m_cold_start = nullptr;
  this->m_hot_start = nullptr;
  this->m_hot_start_in_air = nullptr;
  this->m_make_balance = nullptr;
  this->m_enable_debug_info = nullptr;
  this->m_debug_watch = nullptr;
  this->m_set_plugin_data_install_path = nullptr;
  this->m_on_planned_failure = nullptr;
  this->m_on_damage = nullptr;
  this->m_repair = nullptr;
  this->m_need_to_be_repaired = nullptr;
  this->m_set_immortal = nullptr;
  this->m_unlimited_fuel = nullptr;
  this->m_set_easy_flight = nullptr;
  this->m_set_property_numeric = nullptr;
  this->m_set_property_string = nullptr;
  this->m_pop_simulation_event = nullptr;
  this->m_push_simulation_event = nullptr;
  this->m_suspension_feedback = nullptr;
  this->m_LERX_vortex_update = nullptr;
}


bool EFM::LoadExports()
{
  Reset();

  this->m_add_local_force = reinterpret_cast< PFN_FORCE_SOURCE >( this->m_theLoader.GetProc( "ed_fm_add_local_force" ) );
  this->m_add_global_force = reinterpret_cast< PFN_FORCE_SOURCE >( this->m_theLoader.GetProc( "ed_fm_add_global_force" ) );
  this->m_add_local_force_component = reinterpret_cast< PFN_FORCE_COMPONENT_SOURCE >( this->m_theLoader.GetProc( "ed_fm_add_local_force_component" ) );
  this->m_add_global_force_component = reinterpret_cast< PFN_FORCE_COMPONENT_SOURCE >( this->m_theLoader.GetProc( "ed_fm_add_global_force_component" ) );
  this->m_add_local_moment = reinterpret_cast< PFN_MOMENT_SOURCE >( this->m_theLoader.GetProc( "ed_fm_add_local_moment" ) );
  this->m_add_global_moment = reinterpret_cast< PFN_MOMENT_SOURCE >( this->m_theLoader.GetProc( "ed_fm_add_global_moment" ) );
  this->m_add_local_moment_component = reinterpret_cast< PFN_MOMENT_COMPONENT_SOURCE >( this->m_theLoader.GetProc( "ed_fm_add_local_moment_component" ) );
  this->m_add_global_moment_component = reinterpret_cast< PFN_MOMENT_COMPONENT_SOURCE >( this->m_theLoader.GetProc( "ed_fm_add_global_moment_component" ) );
  this->m_simulate = reinterpret_cast< PFN_SIMULATE >( this->m_theLoader.GetProc( "ed_fm_simulate" ) );
  this->m_set_surface = reinterpret_cast< PFN_SET_SURFACE >( this->m_theLoader.GetProc( "ed_fm_set_surface" ) );
  this->m_set_atmosphere = reinterpret_cast< PFN_SET_ATMOSPHERE >( this->m_theLoader.GetProc( "ed_fm_set_atmosphere" ) );
  this->m_wind_vector_field_update_request = reinterpret_cast< PFN_WIND_VECTOR_FIELD_UPDATE_REQUEST >( this->m_theLoader.GetProc( "ed_fm_wind_vector_field_update_request" ) );
  this->m_wind_vector_field_done = reinterpret_cast< PFN_WIND_VECTOR_FIELD_DONE >( this->m_theLoader.GetProc( "ed_fm_wind_vector_field_done" ) );
  this->m_set_current_mass_state = reinterpret_cast< PFN_CURRENT_MASS_STATE >( this->m_theLoader.GetProc( "ed_fm_set_current_mass_state" ) );
  this->m_set_current_state = reinterpret_cast< PFN_CURRENT_STATE >( this->m_theLoader.GetProc( "ed_fm_set_current_state" ) );
  this->m_set_current_state_body_axis = reinterpret_cast< PFN_CURRENT_STATE_BODY_AXIS >( this->m_theLoader.GetProc( "ed_fm_set_current_state_body_axis" ) );
  this->m_set_command = reinterpret_cast< PFN_SET_COMMAND >( this->m_theLoader.GetProc( "ed_fm_set_command" ) );
  this->m_change_mass = reinterpret_cast< PFN_CHANGE_MASS >( this->m_theLoader.GetProc( "ed_fm_change_mass" ) );
  this->m_set_internal_fuel = reinterpret_cast< PFN_SET_INTERNAL_FUEL >( this->m_theLoader.GetProc( "ed_fm_set_internal_fuel" ) );
  this->m_get_internal_fuel = reinterpret_cast< PFN_GET_INTERNAL_FUEL >( this->m_theLoader.GetProc( "ed_fm_get_internal_fuel" ) );
  this->m_set_external_fuel = reinterpret_cast< PFN_SET_EXTERNAL_FUEL >( this->m_theLoader.GetProc( "ed_fm_set_external_fuel" ) );
  this->m_get_external_fuel = reinterpret_cast< PFN_GET_EXTERNAL_FUEL >( this->m_theLoader.GetProc( "ed_fm_get_external_fuel" ) );
  this->m_refueling_add_fuel = reinterpret_cast< PFN_REFUELING_ADD_FUEL >( this->m_theLoader.GetProc( "ed_fm_refueling_add_fuel" ) );
  this->m_set_draw_args_v2 = reinterpret_cast< PFN_SET_DRAW_ARGS_V2 >( this->m_theLoader.GetProc( "ed_fm_set_draw_args_v2" ) );
  this->m_set_fc3_cockpit_draw_args_v2 = reinterpret_cast< PFN_SET_DRAW_ARGS_V2 >( this->m_theLoader.GetProc( "ed_fm_set_fc3_cockpit_draw_args_v2" ) );
  this->m_set_draw_args = reinterpret_cast< PFN_SET_DRAW_ARGS >( this->m_theLoader.GetProc( "ed_fm_set_draw_args" ) );
  this->m_set_fc3_cockpit_draw_args = reinterpret_cast< PFN_SET_DRAW_ARGS >( this->m_theLoader.GetProc( "ed_fm_set_fc3_cockpit_draw_args" ) );
  this->m_get_shake_amplitude = reinterpret_cast< PFN_GET_SHAKE_AMPLITUDE >( this->m_theLoader.GetProc( "ed_fm_get_shake_amplitude" ) );
  this->m_configure = reinterpret_cast< PFN_CONFIGURE >( this->m_theLoader.GetProc( "ed_fm_configure" ) );
  this->m_release = reinterpret_cast< PFN_FM_RELEASE >( this->m_theLoader.GetProc( "ed_fm_release" ) );
  this->m_get_param = reinterpret_cast< PFN_GET_PARAM >( this->m_theLoader.GetProc( "ed_fm_get_param" ) );
  this->m_cold_start = reinterpret_cast< PFN_COLD_START >( this->m_theLoader.GetProc( "ed_fm_cold_start" ) );
  this->m_hot_start = reinterpret_cast< PFN_HOT_START >( this->m_theLoader.GetProc( "ed_fm_hot_start" ) );
  this->m_hot_start_in_air = reinterpret_cast< PFN_HOT_START_IN_AIR >( this->m_theLoader.GetProc( "ed_fm_hot_start_in_air" ) );
  this->m_make_balance = reinterpret_cast< PFN_MAKE_BALANCE >( this->m_theLoader.GetProc( "ed_fm_make_balance" ) );
  this->m_enable_debug_info = reinterpret_cast< PFN_ENABLE_DEBUG_INFO >( this->m_theLoader.GetProc( "ed_fm_enable_debug_info" ) );
  this->m_debug_watch = reinterpret_cast< PFN_DEBUG_WATCH >( this->m_theLoader.GetProc( "ed_fm_debug_watch" ) );
  this->m_set_plugin_data_install_path = reinterpret_cast< PFN_SET_PLUGIN_DATA_INSTALL_PATH >( this->m_theLoader.GetProc( "ed_fm_set_plugin_data_install_path" ) );
  this->m_on_planned_failure = reinterpret_cast< PFN_ON_PLANNED_FAILURE >( this->m_theLoader.GetProc( "ed_fm_on_planned_failure" ) );
  this->m_on_damage = reinterpret_cast< PFN_ON_DAMAGE >( this->m_theLoader.GetProc( "ed_fm_on_damage" ) );
  this->m_repair = reinterpret_cast< PFN_REPAIR >( this->m_theLoader.GetProc( "ed_fm_repair" ) );
  this->m_need_to_be_repaired = reinterpret_cast< PFN_NEED_TO_BE_REPAIRED >( this->m_theLoader.GetProc( "ed_fm_need_to_be_repaired" ) );
  this->m_set_immortal = reinterpret_cast< PFN_FM_SET_IMMORTAL >( this->m_theLoader.GetProc( "ed_fm_set_immortal" ) );
  this->m_unlimited_fuel = reinterpret_cast< PFN_FM_SET_UNLIMITED_FUEL >( this->m_theLoader.GetProc( "ed_fm_unlimited_fuel" ) ); 
  this->m_set_easy_flight = reinterpret_cast< PFN_FM_SET_EASY_FLIGHT >( this->m_theLoader.GetProc( "ed_fm_set_easy_flight" ) );
  this->m_set_property_numeric = reinterpret_cast< PFN_FM_SET_PROPERTY_NUMERIC >( this->m_theLoader.GetProc( "ed_fm_set_property_numeric" ) );
  this->m_set_property_string = reinterpret_cast< PFN_FM_SET_PROPERTY_STRING >( this->m_theLoader.GetProc( "ed_fm_set_property_string" ) );
  this->m_pop_simulation_event = reinterpret_cast< PFN_FM_POP_SIMULATION_EVENT >( this->m_theLoader.GetProc( "ed_fm_pop_simulation_event" ) );
  this->m_push_simulation_event = reinterpret_cast< PFN_FM_PUSH_SIMULATION_EVENT >( this->m_theLoader.GetProc( "ed_fm_push_simulation_event" ) );
  this->m_suspension_feedback = reinterpret_cast< PFN_FM_SUSPENSION_FEEDBACK >( this->m_theLoader.GetProc( "ed_fm_suspension_feedback" ) );
  this->m_LERX_vortex_update = reinterpret_cast< PFN_FM_LERX_VORTEX_UPDATE >( this->m_theLoader.GetProc( "ed_fm_LERX_vortex_update" ) );

  return true;
}


bool EFM::Load( const std::filesystem::path& filepath )
{
  if( m_theLoader.Load( filepath.string().c_str() ) == false )
  {
    Proxy::ToLog("EFM Proxy : Failed to load %s", filepath.string().c_str() );
    return false;
  }

  if( this->LoadExports() == false )
  {
    Proxy::ToLog("EFM Proxy : Failed to load %s exports", filepath.string().c_str() );
    return false;  
  }

  return true;
}


std::filesystem::path EFM::TargetDLL()
{
  const std::filesystem::path configFilepath = this->ConfigFilepath();
  //Proxy::ToLog( "Looking for config file : '%s'", configFilepath.string().c_str() );
  // workout the default 
  std::filesystem::path defaultDLL = Loader::ModuleFilepath().stem().string() + std::string( ".real.dll" );
  //ToLog( "EFM Proxy : Default plugin to load : %s", defaultDLL.string().c_str() );

  constexpr DWORD ValueBufferSize = 1024;
  char valueBuffer[ ValueBufferSize ] = {};

  const DWORD used = ::GetPrivateProfileStringA( "General"
    , "target"
    , defaultDLL.string().c_str()
    , valueBuffer
    , ValueBufferSize
    , configFilepath.string().c_str()
  );

  std::filesystem::path target;

  if( used == 0 )
  {
    ToLog( "EFM Proxy : Failed to read from config file, using default TargetDLL" );
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
  std::filesystem::path result = std::filesystem::canonical( Loader::ModuleFilepath().parent_path() / target );
  return result;
}


bool EFM::Load()
{
  // If we have a config defined then read the target in it else use the default which is proxyname.real.dll
  std::filesystem::path targetDllFilepath = this->TargetDLL();
  return this->Load( targetDllFilepath );
}


void EFM::add_local_force( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  if( this->m_add_local_force != nullptr )
  {
    ( *( this->m_add_local_force ) )( x, y, z, pos_x, pos_y, pos_z );
  }
}


void EFM::add_global_force( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  if( this->m_add_global_force != nullptr )
  {
    ( *( this->m_add_global_force ) )( x, y, z, pos_x, pos_y, pos_z );
  }
}


bool EFM::add_local_force_component( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  if( this->m_add_local_force_component != nullptr )
  {
    return ( *( this->m_add_local_force_component ) )( x, y, z, pos_x, pos_y, pos_z );
  }
  return false;
}


bool EFM::add_global_force_component( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  if( this->m_add_global_force_component != nullptr )
  {
    return ( *( this->m_add_global_force_component ) )( x, y, z, pos_x, pos_y, pos_z );
  }
  return false;
}


void EFM::add_local_moment( double& x, double& y, double& z )
{
  if( this->m_add_local_moment != nullptr )
  {
    ( *( this->m_add_local_moment ) )( x, y, z );
  }
}


void EFM::add_global_moment( double& x, double& y, double& z )
{
  if( this->m_add_global_moment != nullptr )
  {
    ( *( this->m_add_global_moment ) )( x, y, z );
  }
}


bool EFM::add_local_moment_component( double& x, double& y, double& z )
{
  if( this->m_add_local_moment_component != nullptr )
  {
    return ( *( this->m_add_local_moment_component ) )( x, y, z );
  }
  return false;
}


bool EFM::add_global_moment_component( double& x, double& y, double& z )
{
  if( this->m_add_global_moment_component != nullptr )
  {
    return ( *( this->m_add_global_moment_component ) )( x, y, z );
  }
  return false;
}


void EFM::simulate( double dt )
{
  if( this->m_simulate != nullptr )
  {
    ( *( this->m_simulate ) )( dt );
  }
}


void EFM::set_surface( double h, double h_obj, unsigned surface_type, double normal_x, double normal_y, double normal_z )
{
  if( this->m_set_surface != nullptr )
  {
    ( *( this->m_set_surface ) )( h, h_obj, surface_type, normal_x, normal_y, normal_z );
  }
}


void EFM::set_atmosphere( double h, double t, double a, double ro, double p, double wind_vx, double wind_vy, double wind_vz )
{
  if( this->m_set_atmosphere != nullptr )
  {
    ( *( this->m_set_atmosphere ) )( h, t, a, ro, p, wind_vx, wind_vy, wind_vz );
  }
}


void EFM::wind_vector_field_update_request( wind_vector_field& in_out )
{
  if( this->m_wind_vector_field_update_request != nullptr )
  {
    ( *( this->m_wind_vector_field_update_request ) )( in_out );
  }
}


void EFM::wind_vector_field_done()
{
  if( this->m_wind_vector_field_done != nullptr )
  {
    ( *( this->m_wind_vector_field_done ) )( );
  }
}


void EFM::set_current_mass_state( double mass, double center_of_mass_x, double center_of_mass_y, double center_of_mass_z, double moment_of_inertia_x, double moment_of_inertia_y, double moment_of_inertia_z )
{
  if( this->m_set_current_mass_state != nullptr )
  {
    ( *( this->m_set_current_mass_state ) )( mass, center_of_mass_x, center_of_mass_y, center_of_mass_z, moment_of_inertia_x, moment_of_inertia_y, moment_of_inertia_z );
  }
}


void EFM::set_current_state( double ax, double ay, double az, double vx, double vy, double vz, double px, double py, double pz, double omegadotx, double omegadoty, double omegadotz, double omegax, double omegay, double omegaz, double quaternion_x, double quaternion_y, double quaternion_z, double quaternion_w )
{
  if( this->m_set_current_state != nullptr )
  {
    ( *( this->m_set_current_state ) )( ax, ay, az, vx, vy, vz, px, py, pz, omegadotx, omegadoty, omegadotz, omegax, omegay, omegaz, quaternion_x, quaternion_y, quaternion_z, quaternion_w );
  }
}


void EFM::set_current_state_body_axis( double ax, double ay, double az, double vx, double vy, double vz, double wind_vx, double wind_vy, double wind_vz, double omegadotx, double omegadoty, double omegadotz, double omegax, double omegay, double omegaz, double yaw, double pitch, double roll, double common_angle_of_attack, double common_angle_of_slide )
{
  if( this->m_set_current_state_body_axis != nullptr )
  {
    ( *( this->m_set_current_state_body_axis ) )( ax, ay, az, vx, vy, vz, wind_vx, wind_vy, wind_vz, omegadotx, omegadoty, omegadotz, omegax, omegay, omegaz, yaw, pitch, roll, common_angle_of_attack, common_angle_of_slide );
  }
}


void EFM::set_command( int command, float value )
{
  if( this->m_set_command != nullptr )
  {
    ( *( this->m_set_command ) )( command, value );
  }
}


bool EFM::change_mass( double& delta_mass, double& delta_mass_pos_x, double& delta_mass_pos_y, double& delta_mass_pos_z, double& delta_mass_moment_of_inertia_x, double& delta_mass_moment_of_inertia_y, double& delta_mass_moment_of_inertia_z )
{
  if( this->m_change_mass != nullptr )
  {
    return ( *( this->m_change_mass ) )( delta_mass, delta_mass_pos_x, delta_mass_pos_y, delta_mass_pos_z, delta_mass_moment_of_inertia_x, delta_mass_moment_of_inertia_y, delta_mass_moment_of_inertia_z );
  }
  return false;
}


void EFM::set_internal_fuel( double fuel )
{
  if( this->m_set_internal_fuel != nullptr )
  {
    ( *( this->m_set_internal_fuel ) )( fuel );
  }
}


double EFM::get_internal_fuel()
{
  if( this->m_get_internal_fuel != nullptr )
  {
    return ( *( this->m_get_internal_fuel ) )( );
  }
  return 0.0;
}


void EFM::set_external_fuel( int station, double fuel, double x, double y, double z )
{
  if( this->m_set_external_fuel != nullptr )
  {
    ( *( this->m_set_external_fuel ) )( station, fuel, x, y, z );
  }
}


double EFM::get_external_fuel()
{
  if( this->m_get_external_fuel != nullptr )
  {
    return ( *( this->m_get_external_fuel ) )( );
  }
  return 0.0;
}


void EFM::refueling_add_fuel( double fuel )
{
  if( this->m_refueling_add_fuel != nullptr )
  {
    ( *( this->m_refueling_add_fuel ) )( fuel );
  }
}


void EFM::set_draw_args_v2( float* array, size_t size )
{
  if( this->m_set_draw_args_v2 != nullptr )
  {
    ( *( this->m_set_draw_args_v2 ) )( array, size );  
  }
}


void EFM::set_fc3_cockpit_draw_args_v2( float* array, size_t size )
{
  if( this->m_set_fc3_cockpit_draw_args_v2 != nullptr )
  {
    ( *( this->m_set_fc3_cockpit_draw_args_v2 ) )( array, size );  
  }
}


void EFM::set_draw_args( EdDrawArgument* array, size_t size )
{
  if( this->m_set_draw_args != nullptr )
  {
    ( *( this->m_set_draw_args ) )( array, size );
  }
}


void EFM::set_fc3_cockpit_draw_args( EdDrawArgument* array, size_t size )
{
  if( this->m_set_fc3_cockpit_draw_args != nullptr )
  {
    ( *( this->m_set_fc3_cockpit_draw_args ) )( array, size );
  }
}


double EFM::get_shake_amplitude()
{
  if( this->m_get_shake_amplitude != nullptr )
  {
    return ( *( this->m_get_shake_amplitude ) )( );
  }
  return 0.0;
}


double EFM::get_param( unsigned param_enum )
{
  if( this->m_get_param != nullptr )
  {
    return ( *( this->m_get_param ) )( param_enum );
  }
  return 0.0;
}


bool EFM::make_balance( double& ax, double& ay, double& az, double& vx, double& vy, double& vz, double& omegadotx, double& omegadoty, double& omegadotz, double& omegax, double& omegay, double& omegaz, double& yaw, double& pitch, double& roll )
{
  if( this->m_make_balance != nullptr )
  {
    return ( *( this->m_make_balance ) )( ax, ay, az, vx, vy, vz, omegadotx, omegadoty, omegadotz, omegax, omegay, omegaz, yaw, pitch, roll );
  }
  return false;
}


bool EFM::enable_debug_info()
{
  if( this->m_enable_debug_info != nullptr )
  {
    return ( *( this->m_enable_debug_info ) )( );
  }
  return false;
}


size_t EFM::debug_watch( int level, char* buffer, size_t maxlen )
{
  if( this->m_debug_watch != nullptr )
  {
    return ( *( this->m_debug_watch ) )( level, buffer, maxlen );
  }
  return 0;
}


void EFM::set_plugin_data_install_path( const char* path )
{
  if( this->m_set_plugin_data_install_path != nullptr )
  {
    ( *( this->m_set_plugin_data_install_path ) )( path );
  }
}


void EFM::on_planned_failure( const char* name )
{
  if( this->m_on_planned_failure != nullptr )
  {
    ( *( this->m_on_planned_failure ) )( name );
  }
}


void EFM::on_damage( int element, double element_integrity_factor )
{
  if( this->m_on_damage != nullptr )
  {
    ( *( this->m_on_damage ) )( element, element_integrity_factor );
  }
}


void EFM::repair()
{
  if( this->m_repair != nullptr )
  {
    ( *( this->m_repair ) )( );
  }
}


bool EFM::need_to_be_repaired()
{
  if( this->m_need_to_be_repaired != nullptr )
  {
    return ( *( this->m_need_to_be_repaired ) )( );
  }
  return false;
}


void EFM::set_immortal( bool value )
{
  if( this->m_set_immortal != nullptr )
  {
    ( *( this->m_set_immortal ) )( value );
  }
}


void EFM::unlimited_fuel( bool value )
{
  if( this->m_unlimited_fuel != nullptr )
  {
    ( *( this->m_unlimited_fuel ) )( value );
  }
}


void EFM::set_easy_flight( bool value )
{
  if( this->m_set_easy_flight != nullptr )
  {
    ( *( this->m_set_easy_flight ) )( value );
  }
}


void EFM::set_property_numeric( const char* property_name, float value )
{
  if( this->m_set_property_numeric != nullptr )
  {
    ( *( this->m_set_property_numeric ) )( property_name, value );
  }
}


void EFM::set_property_string( const char* property_name, const char* value )
{
  if( this->m_set_property_string != nullptr )
  {
    ( *( this->m_set_property_string ) )( property_name, value );
  }
}


bool EFM::pop_simulation_event( ed_fm_simulation_event& out )
{
  if( this->m_pop_simulation_event != nullptr )
  {
    return ( *( this->m_pop_simulation_event ) )( out );
  }
  return false;
}


bool EFM::push_simulation_event( const ed_fm_simulation_event& in )
{
  if( this->m_push_simulation_event != nullptr )
  {
    return ( *( this->m_push_simulation_event ) )( in );
  }
  return false;
}


void EFM::suspension_feedback( int idx, const ed_fm_suspension_info* info )
{
  if( this->m_suspension_feedback != nullptr )
  {
    ( *( this->m_suspension_feedback ) )( idx, info );
  }
}


bool EFM::LERX_vortex_update( unsigned idx, LERX_vortex& out )
{
  if( this->m_LERX_vortex_update != nullptr )
  {
    return ( *( this->m_LERX_vortex_update ) )( idx, out );
  }
  return false;
}


void EFM::configure( const char* cfg_path )
{
  if( this->m_configure != nullptr )
  {
    ( *( this->m_configure ) )( cfg_path );
  }
}


void EFM::release()
{
  if( this->m_release != nullptr )
  {
    ( *( this->m_release ) )( );
  }
  this->m_theLoader.Unload();
}


void EFM::cold_start()
{
  if( this->m_cold_start != nullptr )
  {
    ( *( this->m_cold_start ) )( );
  }
}


void EFM::hot_start()
{
  if( this->m_hot_start != nullptr )
  {
    ( *( this->m_hot_start ) )( );
  }
}


void EFM::hot_start_in_air()
{
  if( this->m_hot_start_in_air != nullptr )
  {
    ( *( this->m_hot_start_in_air ) )( );
  }
}


}
