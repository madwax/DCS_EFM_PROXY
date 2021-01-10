################################################################################
# Hot loading of DLLs for DCS EFM
# 
# The structure is simple
# There are 2 projects
# The Proxy - This is loaded by DCS in your mod.  This will load The Target everytime you start a new FM session.
# The Target - Your real FM.  
#
cmake_minimum_required( VERSION 3.15.0 )

project( MOD_EFM )

# Were are the EFM and ProxyEFM going.
set( MOD_BIN_PATH "../bin" CACHE STRING "The location of your mod's bin directory" )
# The name of the dll
set( MOD_BIN_FILENAME "" CACHE STRING "The name of the EFM DLL" )
# If we are to build the EFM or Proxy + EFM
option( MOD_USE_PROXY "If we should build with Proxy support" OFF )
# Workout the true path were the dll's will go
get_filename_component( ABSOLUTE_MOD_BIN_PATH ${MOD_BIN_PATH} ABSOLUTE)
# We want to go after DCS own headers
set( DCS_LOCATION "" CACHE STRING "Please enter the root of your DCS install" )

# We want to use DCS's header files as there kept up todate.
# As the library is only header-only tell cmake is an interface lib
add_library( DCS INTERFACE )
target_include_directories( DCS INTERFACE "${DCS_LOCATION}/API/include" )

message( "Everything is going to: ${ABSOLUTE_MOD_BIN_PATH}" )

# See Proxy_EFM.ReadMe.txt about this!
# This is your EFM ;)
# add_subdirectory( ./FlightModel )

# This is the proxy EFM
add_subdirectory( ./Proxy )



