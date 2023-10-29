cmake_minimum_required(VERSION 3.7.2)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)

project(QuantValue VERSION 1.0.0 LANGUAGES CXX)

option(QV_LINTER_ENABLE        "Enable QuantValue clang-tidy linting" ON)
option(QV_DOC_ENABLE           "Enable QuantValue documentation documentation" OFF)
option(QV_TEST_ENABLE          "Enable QuantValue testing" OFF)
option(QV_HAS_CONSTEXPR_ENABLE "Enable QuantValue compile time computation" OFF)

if(CMAKE_CXX_STANDARD)
  set(PARENT_CXX_STANDARD ${CMAKE_CXX_STANDARD})
  message(STATUS "CXX standard of parent project: ${PARENT_CXX_STANDARD}")
endif()

if(PARENT_CXX_STANDARD)
  if(PARENT_CXX_STANDARD LESS 17)
    message(FATAL_ERROR "${PROJECT_NAME} ${PROJECT_VERSION} does not support ${PARENT_CXX_STANDARD}")
  endif()
else()
    set(CMAKE_CXX_STANDARD 17)
endif()

set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(QV_LINTER_ENABLE)
  set(CMAKE_CXX_CLANG_TIDY clang-tidy; -header-filter=.;)
endif()

if(QV_DOC_ENABLE)
  find_package(Doxygen)
  if(DOXYGEN_FOUND) 
    set(DOXYGEN_IN ${PROJECT_SOURCE_DIR}/Doxyfile.in) 
    set(DOXYGEN_OUT ${PROJECT_SOURCE_DIR}/docs/Doxyfile)
    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)	
    message("Doxygen build start !")
    add_custom_target( 
      docs ALL
      COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
      WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
      COMMENT "Generating documentation with Doxygen"
      VERBATIM 
    ) 
  else()
    message(WARNING "Doxygen need to be installed to generate the doxygen documentation")
  endif()
endif()

include(GNUInstallDirs)

set(QV_TARGET_NAME                         ${PROJECT_NAME})
set(QV_CONFIG_INSTALL_DIR                 "cmake/${PROJECT_NAME}" CACHE INTERNAL "")
set(QV_INCLUDE_INSTALL_DIR                "${CMAKE_INSTALL_INCLUDEDIR}")
set(QV_TARGETS_EXPORT_NAME                "${QV_TARGET_NAME}Targets")
set(QV_CMAKE_DIR                          "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(QV_CMAKE_CONFIG_TEMPLATE_FILE         "${QV_CMAKE_DIR}/${PROJECT_NAME}Config.cmake.in")
set(QV_CMAKE_CONFIG_VERSION_TEMPLATE_FILE "${QV_CMAKE_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(QV_CMAKE_CONFIG_DIR                   "${CMAKE_CURRENT_BINARY_DIR}")
set(QV_CMAKE_CONFIG_VERSION_OUTPUT_FILE   "${QV_CMAKE_CONFIG_DIR}/${PROJECT_NAME}ConfigVersion.cmake")
set(QV_CMAKE_CONFIG_PROJECT_OUTPUT_FILE   "${QV_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Config.cmake")
set(QV_CMAKE_CONFIG_TARGETS_OUTPUT_FILE   "${QV_CMAKE_CONFIG_DIR}/${PROJECT_NAME}Targets.cmake")
set(QV_INCLUDE_BUILD_DIR                  "${PROJECT_SOURCE_DIR}/include/")
set(QV_INCLUDE_DIR                        "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_library(${QV_TARGET_NAME} INTERFACE)

target_compile_definitions(
  ${QV_TARGET_NAME}
  INTERFACE
  $<$<BOOL:${QV_HAS_CONSTEXPR_ENABLE}>:QV_HAS_CONSTEXPR=1>
)

target_include_directories(
  ${QV_TARGET_NAME} 
  INTERFACE 
  $<BUILD_INTERFACE:${QV_INCLUDE_BUILD_DIR}>
  $<INSTALL_INTERFACE:include>
)


add_executable(test test/main.cpp)

target_link_libraries(test ${QV_TARGET_NAME})

include(CMakePackageConfigHelpers)

configure_package_config_file(
  ${QV_CMAKE_CONFIG_TEMPLATE_FILE}
  ${QV_CMAKE_CONFIG_PROJECT_OUTPUT_FILE}
  INSTALL_DESTINATION ${QV_CONFIG_INSTALL_DIR} 
)

write_basic_package_version_file(
  ${QV_CMAKE_CONFIG_VERSION_OUTPUT_FILE}
  VERSION ${${PROJECT_NAME}_VERSION}
  COMPATIBILITY ExactVersion 
)

install(
  DIRECTORY ${QV_INCLUDE_BUILD_DIR}
  DESTINATION ${QV_INCLUDE_INSTALL_DIR}
)

install(
  TARGETS ${QV_TARGET_NAME}
  EXPORT  ${QV_TARGETS_EXPORT_NAME}
  INCLUDES DESTINATION ${QV_INCLUDE_INSTALL_DIR}
)

install(
  EXPORT ${QV_TARGETS_EXPORT_NAME}
  FILE   "${QV_TARGETS_EXPORT_NAME}.cmake"
  DESTINATION ${QV_CONFIG_INSTALL_DIR}
)

install(
  FILES 
    ${QV_CMAKE_CONFIG_PROJECT_OUTPUT_FILE}
    ${QV_CMAKE_CONFIG_VERSION_OUTPUT_FILE} 
  DESTINATION ${QV_CONFIG_INSTALL_DIR}
)
  
if(QV_TEST_ENABLE)
  include(FetchContent)
  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
  )
  
  # For Windows: Prevent overriding the parent project's compiler/linker settings
  if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
  endif()
  
  find_package(GTest CONFIG REQUIRED)
  enable_testing()
  include(CTest)
  add_subdirectory(tests)
endif()

