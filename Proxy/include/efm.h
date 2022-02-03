///////////////////////////////////////////////////////////////////////
// Simple proxy for DCS efm's so don't have to restart DCS every time
//
//
#ifndef __EFM_PROXY_EFM_H__
#define __EFM_PROXY_EFM_H__

#include "common.h"

#define MAX_PROXY_FILEPATH 1024

class EFM
{
  HMODULE m_hEFM;
  // The pointers
  //@{
  PFN_FORCE_SOURCE m_add_local_force;
  PFN_FORCE_SOURCE m_add_global_force;
  PFN_FORCE_COMPONENT_SOURCE m_add_local_force_component;
  PFN_FORCE_COMPONENT_SOURCE m_add_global_force_component;
  PFN_MOMENT_SOURCE m_add_local_moment;
  PFN_MOMENT_SOURCE m_add_global_moment;
  PFN_MOMENT_COMPONENT_SOURCE m_add_local_moment_component;
  PFN_MOMENT_COMPONENT_SOURCE m_add_global_moment_component;
  PFN_SIMULATE m_simulate;
  PFN_SET_SURFACE m_set_surface;
  PFN_SET_ATMOSPHERE m_set_atmosphere;
  PFN_WIND_VECTOR_FIELD_UPDATE_REQUEST m_wind_vector_field_update_request;
  PFN_WIND_VECTOR_FIELD_DONE m_wind_vector_field_done;
  PFN_CURRENT_MASS_STATE m_set_current_mass_state;
  PFN_CURRENT_STATE m_set_current_state;
  PFN_CURRENT_STATE_BODY_AXIS m_set_current_state_body_axis;
  PFN_SET_COMMAND m_set_command;
  PFN_CHANGE_MASS m_change_mass;
  PFN_SET_INTERNAL_FUEL m_set_internal_fuel;
  PFN_GET_INTERNAL_FUEL m_get_internal_fuel;
  PFN_SET_EXTERNAL_FUEL m_set_external_fuel;
  PFN_GET_EXTERNAL_FUEL m_get_external_fuel;
  PFN_REFUELING_ADD_FUEL m_refueling_add_fuel;
  PFN_SET_DRAW_ARGS m_set_draw_args;
  PFN_SET_DRAW_ARGS_V2 m_set_draw_args_v2;
  PFN_SET_DRAW_ARGS m_set_fc3_cockpit_draw_args;
  PFN_SET_DRAW_ARGS_V2 m_set_fc3_cockpit_draw_args_v2;
  PFN_GET_SHAKE_AMPLITUDE m_get_shake_amplitude;
  PFN_CONFIGURE m_configure;
  PFN_FM_RELEASE m_release;
  PFN_GET_PARAM m_get_param;
  PFN_COLD_START m_cold_start;
  PFN_HOT_START m_hot_start;
  PFN_HOT_START_IN_AIR m_hot_start_in_air;
  PFN_MAKE_BALANCE m_make_balance;
  PFN_ENABLE_DEBUG_INFO m_enable_debug_info;
  PFN_DEBUG_WATCH m_debug_watch;
  PFN_SET_PLUGIN_DATA_INSTALL_PATH m_set_plugin_data_install_path;
  PFN_ON_PLANNED_FAILURE m_on_planned_failure;
  PFN_ON_DAMAGE m_on_damage;
  PFN_REPAIR m_repair;
  PFN_NEED_TO_BE_REPAIRED m_need_to_be_repaired;
  PFN_FM_SET_IMMORTAL m_set_immortal;
  PFN_FM_SET_UNLIMITED_FUEL m_unlimited_fuel;
  PFN_FM_SET_EASY_FLIGHT m_set_easy_flight;
  PFN_FM_SET_PROPERTY_NUMERIC m_set_property_numeric;
  PFN_FM_SET_PROPERTY_STRING m_set_property_string;
  PFN_FM_POP_SIMULATION_EVENT m_pop_simulation_event;
  PFN_FM_PUSH_SIMULATION_EVENT m_push_simulation_event;
  PFN_FM_SUSPENSION_FEEDBACK m_suspension_feedback;
  PFN_FM_LERX_VORTEX_UPDATE m_LERX_vortex_update;
  //@}

  FARPROC GetProc( const char* name ); 

public:
  EFM();
  ~EFM();

  bool Load( const char* proxyEFMFilePath );


  void add_local_force( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z );
  void add_global_force( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z );
  bool add_local_force_component( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z );
  bool add_global_force_component( double& x, double& y, double& z, double& pos_x, double& pos_y, double& pos_z );
  void add_local_moment( double& x, double& y, double& z );
  void add_global_moment( double& x, double& y, double& z );
  bool add_local_moment_component( double& x, double& y, double& z );
  bool add_global_moment_component( double& x, double& y, double& z );
  void simulate( double dt );
  void set_surface( double h, double h_obj, unsigned surface_type, double normal_x, double normal_y, double normal_z );
  void set_atmosphere( double h, double t, double a, double ro, double p, double wind_vx, double wind_vy, double wind_vz );
  void wind_vector_field_update_request( wind_vector_field& in_out );
  void wind_vector_field_done();
  void set_current_mass_state( double mass, double center_of_mass_x, double center_of_mass_y, double center_of_mass_z, double moment_of_inertia_x, double moment_of_inertia_y, double moment_of_inertia_z );
  void set_current_state( double ax, double ay, double az, double vx, double vy, double vz, double px, double py, double pz, double omegadotx, double omegadoty, double omegadotz, double omegax, double omegay, double omegaz, double quaternion_x, double quaternion_y, double quaternion_z, double quaternion_w );
  void set_current_state_body_axis( double ax, double ay, double az, double vx, double vy, double vz, double wind_vx, double wind_vy, double wind_vz, double omegadotx, double omegadoty, double omegadotz, double omegax, double omegay, double omegaz, double yaw, double pitch, double roll, double common_angle_of_attack, double common_angle_of_slide );
  void set_command( int command, float value );
  bool change_mass( double& delta_mass, double& delta_mass_pos_x, double& delta_mass_pos_y, double& delta_mass_pos_z, double& delta_mass_moment_of_inertia_x, double& delta_mass_moment_of_inertia_y, double& delta_mass_moment_of_inertia_z );
  void set_internal_fuel( double fuel );
  double get_internal_fuel();
  void set_external_fuel( int station, double fuel, double x, double y, double z );
  double get_external_fuel();
  void refueling_add_fuel( double fuel );
  void set_draw_args( EdDrawArgument* array, size_t size );
  void set_draw_args_v2( float* array, size_t size );
  void set_fc3_cockpit_draw_args( EdDrawArgument* array, size_t size );
  void set_fc3_cockpit_draw_args_v2( float* array, size_t size );
  double get_shake_amplitude();
  void configure( const char* cfg_path );
  // target
  void release();
  double get_param( unsigned param_enum );
  // targets! >>>
  void cold_start();
  void hot_start();
  void hot_start_in_air();
  // targets! <<<
  bool make_balance( double& ax, double& ay, double& az, double& vx, double& vy, double& vz, double& omegadotx, double& omegadoty, double& omegadotz, double& omegax, double& omegay, double& omegaz, double& yaw, double& pitch, double& roll );//radians
  bool enable_debug_info();
  size_t debug_watch( int level, char* buffer, size_t maxlen );
  void set_plugin_data_install_path( const char* path );
  void on_planned_failure( const char* name );
  void on_damage( int Element, double element_integrity_factor );
  void repair();
  bool need_to_be_repaired();
  void set_immortal( bool value );
  void unlimited_fuel( bool value );
  void set_easy_flight( bool value );
  void set_property_numeric( const char* property_name, float value );
  void set_property_string( const char* property_name, const char* value );
  bool pop_simulation_event( ed_fm_simulation_event& out );
  bool push_simulation_event( const ed_fm_simulation_event& in );
  void suspension_feedback( int idx, const ed_fm_suspension_info* info );
  bool LERX_vortex_update( unsigned idx, LERX_vortex& out );
};


#endif /* __EFM_PROXY_EFM_H__ */