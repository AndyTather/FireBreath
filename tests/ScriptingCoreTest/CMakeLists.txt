#/**********************************************************\ 
#Original Author: Richard Bateman (taxilian)
#
#Created:    Nov 20, 2009
#License:    Dual license model; choose one of two:
#            New BSD License
#            http://www.opensource.org/licenses/bsd-license.php
#            - or -
#            GNU Lesser General Public License, version 2.1
#            http://www.gnu.org/licenses/lgpl-2.1.html
#            
#Copyright 2009 PacketPass, Inc and the Firebreath development team
#\**********************************************************/

# Written to work with cmake 2.6
cmake_minimum_required (VERSION 2.6)
set (CMAKE_BACKWARDS_COMPATIBILITY 2.6)

Project (UnitTest_ScriptingCore)
if (VERBOSE)
    message ("Generating project ${PROJECT_NAME} in ${CMAKE_CURRENT_BINARY_DIR}")
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}")
include_directories("${ScriptingCore_SOURCE_DIR}")
include_directories("${FB_ROOT}/src/PluginAuto")
include_directories("${FB_CONFIG_DIR}")
include_directories("${UnitTest++_SOURCE_DIR}/src")
include_directories("${Boost_INCLUDE_DIRS}")
if (WIN32)
    include_directories("${ATL_INCLUDE_DIRS}")
endif()

if (VERBOSE)
    message("CMAKE_CURRENT_SOURCE_DIR: ${CMAKE_CURRENT_SOURCE_DIR}")
    message("SCRIPTINGCORE_SOURCE_DIR: ${ScriptingCore_SOURCE_DIR}")
    message("PLUGINAUTO_SOURCE_DIR: ${FB_ROOT}/src/PluginAuto")
    message("FB_CONFIG_DIR: ${FB_CONFIG_DIR}")
    message("UNITTEST: ${UnitTest++_SOURCE_DIR}/src")
    message("Boost_INCLUDE_DIRS: ${Boost_INCLUDE_DIRS}")
    message("ATL_INCLUDE_DIRS: ${ATL_INCLUDE_DIRS}")
endif()

file (GLOB GENERAL RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}
    ./[^.]*.h
    ./[^.]*.cpp
    )

set (SOURCES
    ${GENERAL}
    ${FB_PLUGINAUTO_SOURCE_DIR}/null/NullLogger.cpp
    )

add_executable(${PROJECT_NAME} ${SOURCES})
set_target_properties(${PROJECT_NAME} PROPERTIES FOLDER "UnitTests")

set_target_properties (${PROJECT_NAME} PROPERTIES
    LINK_FLAGS "${LINK_FLAGS}"
    )

target_link_libraries (${PROJECT_NAME}
    ScriptingCore
    PluginCore
    UnitTest++
    )
link_boost_library ( ${PROJECT_NAME} system )
link_boost_library ( ${PROJECT_NAME} date_time )
link_boost_library ( ${PROJECT_NAME} regex )

if (APPLE)
    find_library(FRAMEWORK_CARBON Carbon) 
    find_library(FRAMEWORK_SYSCONFIG SystemConfiguration)
    include_directories(${FOUNDATION}/Headers)
    target_link_libraries (${PROJECT_NAME}
        ${FRAMEWORK_CARBON}
        ${FRAMEWORK_SYSCONFIG}
        )
endif()

if (WIN32)
    target_link_libraries (${PROJECT_NAME}
        Wininet
        )
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${FB_BIN_DIR}"
)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND "${FB_BIN_DIR}/${CMAKE_CFG_INTDIR}/${PROJECT_NAME}")
