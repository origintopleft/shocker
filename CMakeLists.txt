cmake_minimum_required(VERSION 3.10.0)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake/Modules)
include(Colours)
include(Platform)

project(shocker 
        LANGUAGES CXX
        DESCRIPTION "DualShock 4 management program"
        VERSION 0.0.1)
string(TIMESTAMP BUILD_DATE "%Y.%m.%d %H:%M:%S UTC" UTC)

# for installation rules, from CMake wiki
SET(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib/shocker")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include(Git)
git_init()

include(Cog)
cog_target()

find_package(Qt5
        COMPONENTS Widgets
        REQUIRED)

#include(Doxygen)

#include(Ronn)
#
#generate_manpage(cellar 1)
#add_manpage_target()

#find_package(Boost 1.63 REQUIRED COMPONENTS filesystem program_options system)
#include_directories(${Boost_INCLUDE_DIRS})

#find_package(OpenSSL REQUIRED)
#include_directories(${OPENSSL_INCLUDE_DIR})

include(LavaTargets)

include_directories(include)
#configure_file("${CMAKE_SOURCE_DIR}/include/cmake.hpp.in"
#                "${CMAKE_CURRENT_BINARY_DIR}/include/cmake.hpp")
include_directories("${CMAKE_CURRENT_BINARY_DIR}/include")
set(src "${CMAKE_SOURCE_DIR}/src")

#lava_create_gutlib(
#        SUBDIRS filesystem options targeting
#        LIBRARIES ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES}
#        DEPENDS cog)

lava_create_executable(TARGET shocker
        SUBDIRS shocker
        LIBRARIES Qt5::Widgets
        DEPENDS cog)

install(TARGETS shocker 
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib/shocker
        ARCHIVE DESTINATION share/shocker)
