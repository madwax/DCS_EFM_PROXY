################################################################################
# Hot loading of DLLs for DCS EFM
# 
# The Proxy EFM DLL
#
cmake_minimum_required( VERSION 3.18.0 )

project( efm_proxy )

include( ./dcs.cmake )

# If we have included this file then we want proxy support so force it
unset( USER_MOD_PROXY_SUPPORT CACHE )
set( USER_MOD_PROXY_SUPPORT ON CACHE BOOL "Forced Proxy as its cmake project is included" FORCE )
message( NOTICE "Forceing using EFM Proxy as the CMake Project file as included" )

# global section 	
set( SRC "${PROJECT_SOURCE_DIR}/src" )
set( INC "${PROJECT_SOURCE_DIR}/include" )

# The proxy 
add_library( efm_proxy SHARED )

# C++17 
target_compile_features( efm_proxy PUBLIC cxx_std_17 )

target_compile_definitions( efm_proxy PUBLIC
	FM_EXPORTS=1
)

target_include_directories( efm_proxy PUBLIC
	"${SRC}"
	"${INC}" 
)

target_sources( efm_proxy PRIVATE 
	${INC}/common.h
	${INC}/os.h
	${INC}/config.h
	${SRC}/config.cpp
	${INC}/log.h
	${SRC}/log.cpp
	${INC}/loader.h
	${SRC}/loader.cpp
	${INC}/efm.h
	${SRC}/efm.cpp
	${INC}/proxy.h
	${SRC}/proxy.cpp
	${SRC}/dllmain.cpp
)

# Defines the name of the dll
dcs_set_as_efm_proxy( efm_proxy )
# Puts this into the mod dir when built
dcs_set_output_bin( efm_proxy )

target_link_libraries( efm_proxy PRIVATE DCS )
