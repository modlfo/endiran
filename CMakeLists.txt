cmake_minimum_required(VERSION 3.6)

set(CMAKE_BUILD_TYPE Release)

add_subdirectory(RaspiCamLib)

add_subdirectory(MathematicaRaspiCamLib)


if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
   set(CMAKE_INSTALL_PREFIX ${CMAKE_CURRENT_LIST_DIR}/install)
endif()
