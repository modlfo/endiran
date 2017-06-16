include_directories(/opt/Wolfram/WolframEngine/11.0/SystemFiles/IncludeFiles/C ${CMAKE_CURRENT_LIST_DIR}/../RaspiCamLib/src/)

add_library(MathematicaRaspiCamLib SHARED endiranCamera.h endiranWrapper.cc endiranWrapper.h)

target_link_libraries(MathematicaRaspiCamLib raspicam)

install(TARGETS MathematicaRaspiCamLib DESTINATION lib)
