
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES} Game.h Entity.cpp Entity.h Player.cpp Player.h)
target_include_directories(src PUBLIC ./)
target_link_libraries(src PUBLIC sfml-system sfml-graphics sfml-window sfml-audio box2d tmxlite)