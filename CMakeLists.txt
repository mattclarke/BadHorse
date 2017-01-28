cmake_minimum_required(VERSION 2.8.7)
project(BadHorse)

if(UNIX)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=gnu++11")
endif()

# GTEST INSTALL
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to the build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
                 ${CMAKE_BINARY_DIR}/googletest-build)

                 
## BUILD
FILE(GLOB MY_HEADERS "include/*.h")              
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include) 
#add_executable(BadHorse src/main.cpp ${MY_HEADERS})


## TESTS
enable_testing ()
add_executable(BadHorseTest tests/BadHorseTest.cpp ${MY_HEADERS})  
target_link_libraries(BadHorseTest gtest_main gmock_main)
add_test(NAME badhorse_test COMMAND BadHorseTest)