################################################################################
#
# Common Stuff for intergrating with DCS
#
#

# If we have another copy floating around then stop it
include_guard( GLOBAL )

cmake_minimum_required( VERSION 3.18.0 )

# The root location of your DCS Game folder
set( DCS_GAME_DIR "" CACHE STRING "The location of your DCS game folder" )

# This is to the root of the users mod folder 
set( USER_MOD_DIR "" CACHE STRING "The location of your mod root folder under Saved Games" )
set( USER_MOD_NAME "" CACHE STRING "The name of your mod" )
set( USER_MOD_EFM_BIN_NAME "" CACHE STRING "The name of the EFM dll. If empty mod name is used" )

get_filename_component( USER_MOD_DIR_ABS ${USER_MOD_DIR} ABSOLUTE )

option( USER_MOD_PROXY_SUPPORT "Enable EFM Proxy Support" OFF )

# We want to use DCS's header files as there kept up todate.
# As the library is only header-only tell cmake is an interface lib

add_library( DCS INTERFACE )

target_include_directories( DCS INTERFACE "${DCS_GAME_DIR}/API/include" )


function( dcs_efm_bin_name refArg )

	if( "${USER_MOD_EFM_BIN_NAME}" STREQUAL "" )
		set( ${refArg} 	"${USER_MOD_NAME}" PARENT_SCOPE )
	else()
		set( ${refArg} 	"${USER_MOD_EFM_BIN_NAME}" PARENT_SCOPE )
	endif()

endfunction()



function( dcs_set_output_bin project )

	if( MSVC )
		foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
			string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
			set_target_properties( ${project} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${USER_MOD_DIR}/bin" )
			set_target_properties( ${project} PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${USER_MOD_DIR}/bin" )
			set_target_properties( ${project} PROPERTIES EXECUTABLE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${USER_MOD_DIR}/bin" )
		endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
	endif ( MSVC )

endfunction()

function( dcs_set_as_efm_proxy project )

	set( nameIs "" )
	dcs_efm_bin_name( nameIs )
		
	set_target_properties( ${project} PROPERTIES OUTPUT_NAME "${nameIs}" )
	
	message( ERROR "Output name : ${nameIs}" )

endfunction()

function( dcs_set_as_efm project )

	set( nameIs "" )
	dcs_efm_bin_name( nameIs )

	if( USER_MOD_PROXY_SUPPORT )
		set_target_properties( ${project} PROPERTIES OUTPUT_NAME "${nameIs}.real" )
	else()
		set_target_properties( ${project} PROPERTIES OUTPUT_NAME "${nameIs}" )
	endif()

endfunction()