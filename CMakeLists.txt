cmake_minimum_required(VERSION 3.15)
cmake_policy(VERSION 3.15)

include(FetchContent)
project(projet-cpp VERSION 1.0.0 LANGUAGES CXX)


if(WIN32)
  # SonarLint support for CMake requires the following flag to be set on.
  #(see https://community.sonarsource.com/t/sonarlint-for-visual-studio-v4-38-support-cmake-projects/50127)
  set (CMAKE_EXPORT_COMPILE_COMMANDS ON)
endif()

set (BUILD_SHARED_LIBS FALSE)

FetchContent_Declare(
        box2d
        GIT_REPOSITORY  https://github.com/erincatto/Box2d.git
        GIT_TAG         v2.3.1)

FetchContent_MakeAvailable(box2d)

if(APPLE)
  find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
  include_directories(${SFML_INCLUDE_DIRS})
else()
  # Linux or Windows
  FetchContent_Declare(
          sfml
          GIT_REPOSITORY https://github.com/SFML/SFML.git
          GIT_TAG 2.5.1
  )
  FetchContent_MakeAvailable(sfml)
endif()




set(CMAKE_CXX_STANDARD 20)

# Download and unpack tmxlite at configure time
set (TMXLITE_STATIC_LIB TRUE)
configure_file(CMakeLists_tmxlite.txt.in tmxlite-download/tmxlite/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tmxlite-download/tmxlite )
if(result)
  message(FATAL_ERROR "CMake step for tmxlite failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
        RESULT_VARIABLE result
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/tmxlite-download/tmxlite )
if(result)
  message(FATAL_ERROR "Build step for tmxlite failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add tmxlite directly to our build. This defines tmxlite target
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/tmxlite-src/tmxlite
        ${CMAKE_CURRENT_BINARY_DIR}/tmxlite-build/tmxlite
        EXCLUDE_FROM_ALL)
include_directories("${CMAKE_CURRENT_BINARY_DIR}/tmxlite-src/tmxlite/include")


add_subdirectory(mainLauncher)
add_subdirectory(src)
# enable_testing() must be in the source directory root (see cmake documentation at https://cmake.org/cmake/help/latest/command/enable_testing.html)
# Otherwise, Visual Studio test explorer does not see unit tests (See ticket https://developercommunity.visualstudio.com/t/No-tests-discovered-for-googletest-and-C/1148799#T-ND1150621)
enable_testing()
add_subdirectory(unitTests)
