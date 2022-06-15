cmake_minimum_required(VERSION 3.8)

project(oscope2100)

set(oscope2100_src src/ConfigFile.cpp  src/oscope2100_common.cpp  src/oscope2100_interface.cpp  src/oscope2100_usb.cpp)

find_package(GTK2 2.0 REQUIRED gtk)
include_directories(${GTK2_INCLUDE_DIRS})

add_executable(oscope2100 ${oscope2100_src})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(oscope2100 PRIVATE Threads::Threads)

target_link_libraries(oscope2100 PRIVATE ${GTK2_LIBRARIES})

find_path(LIBUSB_INCLUDE_DIR
  NAMES libusb.h
  PATH_SUFFIXES "include" "libusb" "libusb-1.0")
find_library(LIBUSB_LIBRARY
  NAMES usb
  PATH_SUFFIXES "lib" "lib32" "lib64")
  
target_include_directories(oscope2100 PRIVATE ${LIBUSB_INCLUDE_DIR})
target_link_libraries(oscope2100 PRIVATE ${LIBUSB_LIBRARY})

install(TARGETS oscope2100 DESTINATION bin)
