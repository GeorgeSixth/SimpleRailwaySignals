cmake_minimum_required(VERSION 3.15)
project(RailwaySignaling VERSION 1.0.0 LANGUAGES CXX)

# Vérification du type de build
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

# Configuration C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_COMPILER g++-13)
set(CMAKE_C_COMPILER gcc-13)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Trouver les dépendances
find_package(Boost REQUIRED COMPONENTS system filesystem)
find_package(GTest REQUIRED)

# Bibliothèque principale
add_library(railway_signaling
    src/RailwaySignal.cpp
    src/SignalState.cpp
    src/SignalCommand.cpp
)

target_include_directories(railway_signaling PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
    ${Boost_INCLUDE_DIRS}
)

target_link_libraries(railway_signaling PUBLIC
    ${Boost_LIBRARIES}
    Boost::system
    Boost::filesystem
)

# Exécutable principal
add_executable(railway_signal_demo
    src/main.cpp
)

target_link_libraries(railway_signal_demo PRIVATE
    railway_signaling
)

# Tests unitaires
enable_testing()
add_executable(railway_signaling_test
    tests/railway_signal_test.cpp
)

target_link_libraries(railway_signaling_test
    PRIVATE
    railway_signaling
    GTest::GTest
    GTest::Main
)

add_test(NAME railway_signaling_test COMMAND railway_signaling_test)
