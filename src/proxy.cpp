
#include "common.h"
#include "proxy.h"

#include <memory>


namespace 
{

std::unique_ptr< Proxy::EFM > s_efmProxy;

}

void ed_fm_set_plugin_data_install_path( const char* path )
{
  if( s_efmProxy )
  {
    Proxy::ToLog( "EMF Proxy : ed_fm_set_plugin_data_install_path() called but we have an exiting proxy loaded, unloading... Please report\n" );
    s_efmProxy.reset();
  }

  try
  {
    std::unique_ptr< Proxy::EFM > loading = std::make_unique< Proxy::EFM >();

    if( loading->Load() == false )
    {
      Proxy::ToLog( "EMF Proxy : Failed to load your EFM" );
      return;
    }

    s_efmProxy  = std::move( loading );

    Proxy::ToLog( "EMF Proxy : Loaded EFM" );

    s_efmProxy->set_plugin_data_install_path( path );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in loading what: %s", ex.what() );
    return;
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in loading" );
    return;
  }
}


void ed_fm_release()
{
  if( !s_efmProxy )
  {
    Proxy::ToLog( "EMF Proxy : ed_fm_release() called but we don't have a EFM loaded" );
    return;
  }

  try
  {
    s_efmProxy->release();
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_release() what: %s", ex.what() );
    return;
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_release()" );
    return;
  }

  s_efmProxy.reset( nullptr );
}


void ed_fm_cold_start()
{
  try
  {
    s_efmProxy->cold_start();
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_cold_start() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_cold_start()" );
  }
}


void ed_fm_hot_start()
{
  try
  {
    s_efmProxy->hot_start();
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_hot_start() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_hot_start()" );
  }
}


void ed_fm_hot_start_in_air()
{
  try
  {
    s_efmProxy->hot_start_in_air();
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_hot_start_in_air() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_hot_start_in_air()" );
  }
}


void ed_fm_add_local_force( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  try
  {
    s_efmProxy->add_local_force( x, y, z, pos_x, pos_y, pos_z );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_add_local_force() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_add_local_force()" );
  }
}


void ed_fm_add_global_force( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  try
  {
    s_efmProxy->add_global_force( x, y, z, pos_x, pos_y, pos_z );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_add_global_force() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_add_global_force()" );
  }
}


bool ed_fm_add_local_force_component( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  try
  {
    bool ret = s_efmProxy->add_local_force_component( x, y, z, pos_x, pos_y, pos_z );
    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_add_local_force_component() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_add_local_force_component()" );
  }
  return false;
}


bool ed_fm_add_global_force_component( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z )
{
  try
  {
    bool ret = s_efmProxy->add_global_force_component( x, y, z, pos_x, pos_y, pos_z );
    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_add_global_force_component() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_add_global_force_component()" );
  }
  return false;
}


void ed_fm_add_local_moment( double& x, double& y, double& z )
{
  try
  {
    s_efmProxy->add_local_moment( x, y, z );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_add_local_moment() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_add_local_moment()" );
  }
}


void ed_fm_add_global_moment( double& x, double& y, double& z )
{
  try
  {
    s_efmProxy->add_global_moment( x, y, z );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_add_global_moment() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_add_global_moment()" );
  }
}


bool ed_fm_add_local_moment_component( double& x, double& y, double& z )
{
  try
  {
    bool ret = s_efmProxy->add_local_moment_component( x, y, z );
    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_add_local_moment_component() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_add_local_moment_component()" );
  }
  return false;
}


bool ed_fm_add_global_moment_component( double& x, double& y, double& z )
{
  try
  {
    bool ret = s_efmProxy->add_global_moment_component( x, y, z );

    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_add_global_moment_component() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_add_global_moment_component()" );
  }
  return false;
}


void ed_fm_simulate( double dt )
{
  try
  {
    s_efmProxy->simulate( dt );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_simulate() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_simulate()" );
  }
}


void ed_fm_set_surface( double h, double h_obj, unsigned surface_type, double normal_x, double normal_y, double normal_z )
{
  try
  {
    s_efmProxy->set_surface( h, h_obj, surface_type, normal_x, normal_y, normal_z );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_surface() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_surface()" );
  }
}


void ed_fm_set_atmosphere( double h, double t, double a, double ro, double p, double wind_vx, double wind_vy, double wind_vz )
{
  try
  {
    s_efmProxy->set_atmosphere( h, t, a, ro, p, wind_vx, wind_vy, wind_vz );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_atmosphere() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_atmosphere()" );
  }
}


void ed_fm_wind_vector_field_update_request( wind_vector_field& in_out )
{
  try
  {
    s_efmProxy->wind_vector_field_update_request( in_out );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_wind_vector_field_update_request() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_wind_vector_field_update_request()" );
  }
}


void ed_fm_wind_vector_field_done()
{
  try
  {
    s_efmProxy->wind_vector_field_done();
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_wind_vector_field_done() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_wind_vector_field_done()" );
  }
}


void ed_fm_set_current_mass_state( double mass, double center_of_mass_x, double center_of_mass_y, double center_of_mass_z, double moment_of_inertia_x, double moment_of_inertia_y, double moment_of_inertia_z )
{
  try
  {
    s_efmProxy->set_current_mass_state( mass, center_of_mass_x, center_of_mass_y, center_of_mass_z, moment_of_inertia_x, moment_of_inertia_y, moment_of_inertia_z );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_current_mass_state() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_current_mass_state()" );
  }
}


void ed_fm_set_current_state( double ax, double ay, double az, double vx, double vy, double vz, double px, double py, double pz, double omegadotx, double omegadoty, double omegadotz, double omegax, double omegay, double omegaz, double quaternion_x, double quaternion_y, double quaternion_z, double quaternion_w )
{
  try
  {
    s_efmProxy->set_current_state( ax, ay, az, vx, vy, vz, px, py, pz, omegadotx, omegadoty, omegadotz, omegax, omegay, omegaz, quaternion_x, quaternion_y, quaternion_z, quaternion_w );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_current_state() what: %s", ex.what() );
    return;
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_current_state()" );
    return;
  }
}


void ed_fm_set_current_state_body_axis( double ax, double ay, double az, double vx, double vy, double vz, double wind_vx, double wind_vy, double wind_vz, double omegadotx, double omegadoty, double omegadotz, double omegax, double omegay, double omegaz, double yaw, double pitch, double roll, double common_angle_of_attack, double common_angle_of_slide )
{
  try
  {
    s_efmProxy->set_current_state_body_axis( ax, ay, az, vx, vy, vz, wind_vx, wind_vy, wind_vz, omegadotx, omegadoty, omegadotz, omegax, omegay, omegaz, yaw, pitch, roll, common_angle_of_attack, common_angle_of_slide );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_current_state_body_axis() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_current_state_body_axis()" );
  }
}


void ed_fm_set_command( int command, float value )
{
  try
  {
    s_efmProxy->set_command( command, value );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_command() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_command()" );
  }
}


bool ed_fm_change_mass( double& delta_mass, double& delta_mass_pos_x, double& delta_mass_pos_y, double& delta_mass_pos_z, double& delta_mass_moment_of_inertia_x, double& delta_mass_moment_of_inertia_y, double& delta_mass_moment_of_inertia_z )
{
  try
  {
    bool ret =s_efmProxy->change_mass( delta_mass, delta_mass_pos_x, delta_mass_pos_y, delta_mass_pos_z, delta_mass_moment_of_inertia_x, delta_mass_moment_of_inertia_y, delta_mass_moment_of_inertia_z );
    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_change_mass() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_change_mass()" );
  }
  return false;
}

void ed_fm_set_internal_fuel( double fuel )
{
  try
  {
    s_efmProxy->set_internal_fuel( fuel );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_internal_fuel() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_internal_fuel()" );
  }
}


double ed_fm_get_internal_fuel()
{
  try
  {
    double ret = s_efmProxy->get_internal_fuel();

    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_get_internal_fuel() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_get_internal_fuel()" );
  }
  return 0.0;
}


void ed_fm_set_external_fuel( int station, double fuel, double x, double y, double z )
{
  try
  {
    s_efmProxy->set_external_fuel( station, fuel, x, y, z );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_external_fuel() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_external_fuel()" );
  }
}


double ed_fm_get_external_fuel()
{
  try
  {
    double ret = s_efmProxy->get_external_fuel();

    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_get_external_fuel() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_get_external_fuel()" );
  }
  return 0.0;
}


void ed_fm_refueling_add_fuel( double fuel )
{
  try
  {
    s_efmProxy->refueling_add_fuel( fuel );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_refueling_add_fuel() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_refueling_add_fuel()" );
  }
}


void ed_fm_set_draw_args_v2( float * array, size_t size )
{
  try
  {
    s_efmProxy->set_draw_args_v2( array, size );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_draw_args_v2() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_draw_args_v2()" );
  }
}


void ed_fm_set_fc3_cockpit_draw_args_v2( float * array, size_t size )
{
  try
  {
    s_efmProxy->set_fc3_cockpit_draw_args_v2( array, size );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_fc3_cockpit_draw_args_v2() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_fc3_cockpit_draw_args_v2()" );
  }

}


void ed_fm_set_draw_args( EdDrawArgument* array, size_t size )
{
  try
  {
    s_efmProxy->set_draw_args( array, size );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_draw_args() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_draw_args()" );
  }
}


void ed_fm_set_fc3_cockpit_draw_args( EdDrawArgument* array, size_t size )
{
  try
  {
    s_efmProxy->set_fc3_cockpit_draw_args( array, size );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_fc3_cockpit_draw_args() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_fc3_cockpit_draw_args()" );
  }
}


double ed_fm_get_shake_amplitude()
{
  try
  {
    double ret = s_efmProxy->get_shake_amplitude();
    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_get_shake_amplitude() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_get_shake_amplitude()" );
  }
  return 0.0;
}

void ed_fm_configure( const char* cfg_path )
{
  try
  {
    s_efmProxy->configure( cfg_path );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_configure() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_configure()" );
  }
}

double ed_fm_get_param( unsigned param_enum )
{
  try
  {
    double ret = s_efmProxy->get_param( param_enum );

    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_get_param() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_get_param()" );
  }
  return 0.0;
}


bool ed_fm_make_balance( double& ax, double& ay, double& az, double& vx, double& vy, double& vz, double& omegadotx, double& omegadoty, double& omegadotz, double& omegax, double& omegay, double& omegaz, double& yaw, double& pitch, double& roll )
{
  try
  {
    bool ret = s_efmProxy->make_balance( ax, ay, az, vx, vy, vz, omegadotx, omegadoty, omegadotz, omegax, omegay, omegaz, yaw, pitch, roll );
    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_make_balance() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_make_balance()" );
  }
  return false;
}


bool ed_fm_enable_debug_info()
{
  try
  {
    bool ret = s_efmProxy->enable_debug_info();

    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in enable_debug_info() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in enable_debug_info()" );
  }
  return false;
}


size_t ed_fm_debug_watch( int level, char* buffer, size_t maxlen )
{
  try
  {
    size_t ret = s_efmProxy->debug_watch( level, buffer, maxlen );

    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_debug_watch() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_debug_watch()" );
  }
  return 0;
}


void ed_fm_on_planned_failure( const char* name )
{
  try
  {
    s_efmProxy->on_planned_failure( name );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_on_planned_failure() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_on_planned_failure()" );
  }
}


void ed_fm_on_damage( int element, double element_integrity_factor )
{
  try
  {
    s_efmProxy->on_damage( element, element_integrity_factor );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_on_damage() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_on_damage()" );
  }
}


void ed_fm_repair()
{
  try
  {
    s_efmProxy->repair();
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_repair() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_repair()" );
  }
}


bool ed_fm_need_to_be_repaired()
{
  try
  {
    bool ret = s_efmProxy->need_to_be_repaired();
    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_need_to_be_repaired() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_need_to_be_repaired()" );
  }
  return false;
}


void ed_fm_set_immortal( bool value )
{
  try
  {
    s_efmProxy->set_immortal( value );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_immortal() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_immortal()" );
  }
}


void ed_fm_unlimited_fuel( bool value )
{
  try
  {
    s_efmProxy->unlimited_fuel( value );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_unlimited_fuel() what: %s", ex.what() );
    return;
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_unlimited_fuel()" );
  }
}

void ed_fm_set_easy_flight( bool value )
{
  try
  {
    s_efmProxy->set_easy_flight( value );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_easy_flight() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_easy_flight()" );
  }
}

void ed_fm_set_property_numeric( const char* property_name, float value )
{
  try
  {
    s_efmProxy->set_property_numeric( property_name, value );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_property_numeric() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_property_numeric()" );
  }
}

void ed_fm_set_property_string( const char* property_name, const char* value )
{
  try
  {
    s_efmProxy->set_property_string( property_name, value );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_set_property_string() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_set_property_string()" );
  }
}

bool ed_fm_pop_simulation_event( ed_fm_simulation_event& out )
{
  try
  {
    bool ret = s_efmProxy->pop_simulation_event( out );
    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_pop_simulation_event() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_pop_simulation_event()" );
  }
  return false;
}

bool ed_fm_push_simulation_event( const ed_fm_simulation_event& in )
{
  try
  {
    bool ret =s_efmProxy->push_simulation_event( in );
    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_push_simulation_event() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_push_simulation_event()" );
  }
  return false;
}

void ed_fm_suspension_feedback( int idx, const ed_fm_suspension_info* info )
{
  try
  {
    s_efmProxy->suspension_feedback( idx, info );
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_suspension_feedback() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_suspension_feedback()" );
  }
}

bool ed_fm_LERX_vortex_update( unsigned idx, LERX_vortex& out )
{
  try
  {
    bool ret = s_efmProxy->LERX_vortex_update( idx, out );
    return ret;
  }
  catch( const std::exception& ex )
  {
    Proxy::ToLog( "EMF Proxy : Exception in ed_fm_LERX_vortex_update() what: %s", ex.what() );
  }
  catch( ... )
  {
    Proxy::ToLog( "EMF Proxy : Unhandled exception in ed_fm_LERX_vortex_update()" );
  }
  return false;
}
