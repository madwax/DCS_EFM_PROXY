################################################################################
# Hot loading of DLLs for DCS EFM
# 
# The Proxy EFM DLL
#
cmake_minimum_required( VERSION 3.15.0 )

if( MOD_USE_PROXY )

	project( efm_proxy )

	add_library( efm_proxy SHARED )

	set( SRC "${PROJECT_SOURCE_DIR}/src" )
	set( INC "${PROJECT_SOURCE_DIR}/include" )
	
	target_compile_definitions( efm_proxy PRIVATE 
		FM_EXPORTS=1
	)

	target_include_directories( efm_proxy PRIVATE 
		"${SRC}"
		"${INC}" 
	)

	target_sources( efm_proxy PRIVATE 
		${INC}/common.h
		${INC}/proxy.h
		${SRC}/proxy.cpp
		${INC}/efm.h
		${SRC}/efm.cpp
	)

	set_target_properties( efm_proxy PROPERTIES OUTPUT_NAME "${MOD_BIN_FILENAME}" )

	if( MSVC )
		foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
			string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
			set_target_properties( efm_proxy PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${ABSOLUTE_MOD_BIN_PATH}" )
			set_target_properties( efm_proxy PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${ABSOLUTE_MOD_BIN_PATH}" )
			set_target_properties( efm_proxy PROPERTIES EXECUTABLE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${ABSOLUTE_MOD_BIN_PATH}" )
		endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
	endif ( MSVC )

	target_link_libraries( efm_proxy PRIVATE DCS )


endif()





















