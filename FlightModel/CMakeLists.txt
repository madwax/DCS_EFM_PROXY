################################################################################
# CMake file for building the Super Cool AH-6J mod
# This is for education only!
# Thanks nibbylot!
#
cmake_minimum_required( VERSION 3.15.0 )

project( efm )

add_library( efm SHARED )

set( SRC "${PROJECT_SOURCE_DIR}" )

target_compile_definitions( efm PRIVATE 
	FM_EXPORTS=1
)

target_include_directories( efm PRIVATE 
	"${SRC}"
	"${SRC}/include" 
)

target_sources( efm PRIVATE 
	${SRC}/dllmain.cpp
	${SRC}/stdafx.cpp
	${SRC}/stdafx.h
	${SRC}/targetver.h
	${SRC}/AH6.cpp
	${SRC}/Aerodynamics/AH6Aero.h
	${SRC}/Aerodynamics/AH6AeroData.h
	${SRC}/Airframe/AH6Airframe.h
	${SRC}/Electrics/AH6ElectricSystem.h
	${SRC}/Engine/AH6Engine.h
	${SRC}/Engine/AH6FuelSystem.h
	${SRC}/EquationsOfMotion/AH6EquationsOfMotion.h
	${SRC}/include/AH6Constants.h
	${SRC}/include/Cockpit/ccParametersAPI.h
	${SRC}/include/Cockpit/CockpitAPI_Declare.h
	${SRC}/include/ED_FM_Utility.h
	${SRC}/include/FM/API_Declare.h
	${SRC}/include/FM/wHumanCustomPhysicsAPI.h
	${SRC}/include/UtilityFunctions.h
	${SRC}/Inputs/AH6Inputs.h
)
if( MOD_USE_PROXY )
	set_target_properties( efm PROPERTIES OUTPUT_NAME "${MOD_BIN_FILENAME}.real" )
else()
	set_target_properties( efm PROPERTIES OUTPUT_NAME "${MOD_BIN_FILENAME}" )
endif()

#set_target_properties( efm PROPERTIES CMAKE_RUNTIME_OUTPUT_DIRECTORY "${ABSOLUTE_MOD_BIN_PATH}" )
#set_target_properties( efm PROPERTIES CMAKE_LIBRARY_OUTPUT_DIRECTORY "${ABSOLUTE_MOD_BIN_PATH}" )
#set_target_properties( efm PROPERTIES CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${ABSOLUTE_MOD_BIN_PATH}" )

if( MSVC )
	foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
		string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
		set_target_properties( efm PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${ABSOLUTE_MOD_BIN_PATH}" )
		set_target_properties( efm PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${ABSOLUTE_MOD_BIN_PATH}" )
		set_target_properties( efm PROPERTIES EXECUTABLE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} "${ABSOLUTE_MOD_BIN_PATH}" )
	endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )
endif ( MSVC )









