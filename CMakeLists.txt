cmake_minimum_required(VERSION 3.4 FATAL_ERROR)
set(PROJECT error)
project(${PROJECT} LANGUAGES CXX)

#################################################################################
# Sources
#################################################################################
set(SOURCES
  src/error.cpp
)

set(PUBLIC_HEADERS
  src/error.h
)

add_library(${PROJECT} STATIC ${SOURCES})

#################################################################################
# Libraries
#################################################################################

###############################
## Module_headers
###############################
if(NOT MODULE_HEADERS_PATH)
  set(MODULE_HEADERS_PATH "../module_headers")
endif()

if(NOT MODULE_HEADERS_PATH STREQUAL MODULE_HEADERS_PATH_INTERNAL)
  unset(MODULE_HEADERS_DIR)
endif()
set(MODULE_HEADERS_PATH_INTERNAL ${MODULE_HEADERS_PATH} CACHE INTERNAL "" FORCE)

find_path(MODULE_HEADERS_DIR NAMES "current/module.h" PATHS ${MODULE_HEADERS_PATH} NO_DEFAULT_PATH)
if(MODULE_HEADERS_DIR)
  target_include_directories(${PROJECT} PUBLIC ${MODULE_HEADERS_DIR})
else()
  message(SEND_ERROR "Please set MODULE_HEADERS_PATH, current value: ${MODULE_HEADERS_PATH}")
endif()

#################################################################################
# Properties
#################################################################################

set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 11)

target_compile_options(${PROJECT} PRIVATE
  -Wall -Werror
  -pedantic
  -fno-strict-aliasing
  -fmax-errors=2
)

if(UNIX AND (X86_64 OR X86))
  target_compile_options(${PROJECT} PUBLIC -m32)
endif()

set_target_properties(${PROJECT} PROPERTIES DEBUG_POSTFIX "_d")

#################################################################################
# Install
#################################################################################

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
target_include_directories(${PROJECT} INTERFACE $<INSTALL_INTERFACE:include>)

install(TARGETS ${PROJECT} EXPORT ${PROJECT} DESTINATION lib)
install(FILES ${PUBLIC_HEADERS} DESTINATION include)
install(EXPORT ${PROJECT} DESTINATION config)
