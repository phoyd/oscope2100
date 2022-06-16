cmake_minimum_required(VERSION 3.8)

project(oscope2100)

set(oscope2100_src src/ConfigFile.cpp  src/oscope2100_common.cpp  src/oscope2100_interface.cpp  src/oscope2100_usb.cpp)

add_executable(oscope2100 ${oscope2100_src})

#--- pthreads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(oscope2100 PRIVATE Threads::Threads)

#--- gtk2

find_package(GTK2 2.0 REQUIRED gtk)
include_directories(${GTK2_INCLUDE_DIRS})
target_link_libraries(oscope2100 PRIVATE ${GTK2_LIBRARIES})

# TODO: Port to GTK3: 
# find_package(PkgConfig REQUIRED)
# pkg_check_modules(GTK3 REQUIRED gtk+-3.0)
# include_directories(${GTK3_INCLUDE_DIRS})
# target_link_libraries(oscope2100 PRIVATE ${GTK3_LIBRARIES})

#--- libusb
find_path(LIBUSB_INCLUDE_DIR
  NAMES libusb.h
  PATH_SUFFIXES "include" "libusb" "libusb-1.0")
find_library(LIBUSB_LIBRARY
  NAMES usb
  PATH_SUFFIXES "lib" "lib32" "lib64")
target_include_directories(oscope2100 PRIVATE ${LIBUSB_INCLUDE_DIR})
target_link_libraries(oscope2100 PRIVATE ${LIBUSB_LIBRARY})

set(SHAREDIR ${CMAKE_INSTALL_PREFIX}/share/dso2100)
configure_file(udev/dso2100.rules 99-dso2100.rules @ONLY)

install(TARGETS oscope2100 DESTINATION bin)
