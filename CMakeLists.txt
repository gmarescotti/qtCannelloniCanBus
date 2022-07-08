cmake_minimum_required(VERSION 3.1)
project(qtCannelloniCanBusPlugin CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

find_package(Qt5Core REQUIRED)
find_package(Qt5SerialBus REQUIRED)
find_package(Qt5Network REQUIRED)

include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5SerialBus_INCLUDE_DIRS}
    ${Qt5Network_INCLUDE_DIRS} ${CMAKE_BINARY_DIR})

add_library(${PROJECT_NAME} SHARED
  QtCannelloniCanBusPlugin.cpp
  CannelloniCanBackend.cpp
  cannelloni/parser.cpp
  )

target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::SerialBus Qt5::Network)

if(MSVC)
    include_directories(./linux_porting)
    target_link_libraries(${PROJECT_NAME} Ws2_32)
    include_directories(cannelloni/ cannelloni/include/ linux_porting/)
    add_definitions(-D_WIN32_WINNT_WIN10_TH2=0x0A000001
        -D_WIN32_WINNT_WIN10_RS1=0x0A000002
        -D_WIN32_WINNT_WIN10_RS2=0x0A000003
        -D_WIN32_WINNT_WIN10_RS3=0x0A000004
        -D_WIN32_WINNT_WIN10_RS4=0x0A000005
        -D_WIN32_WINNT_WIN10_RS5=0x0A000006)
endif()
