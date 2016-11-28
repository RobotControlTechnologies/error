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
  src/base_error.h
)

add_library(${PROJECT} STATIC ${SOURCES})

#################################################################################
# Properties
#################################################################################

set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 11)

target_compile_options(${PROJECT} PRIVATE
  -Wall -Werror
  -pedantic
  -fno-strict-aliasing
)

#if(UNIX AND (X86_64 OR X86)) # need detect X86
  target_compile_options(${PROJECT} PUBLIC -m32)
  set_target_properties(${PROJECT} PROPERTIES LINK_FLAGS -m32)
#endif()

set_target_properties(${PROJECT} PROPERTIES DEBUG_POSTFIX "_debug")

#################################################################################
# Libraries
#################################################################################

#################################################################################
# Install
#################################################################################

set(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/install)
target_include_directories(${PROJECT} INTERFACE $<INSTALL_INTERFACE:include>)

install(TARGETS ${PROJECT} EXPORT ${PROJECT} DESTINATION lib)
install(FILES ${PUBLIC_HEADERS} DESTINATION include)
install(EXPORT ${PROJECT} DESTINATION config)
