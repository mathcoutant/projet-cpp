
file(GLOB SOURCES CONFIGURE_DEPENDS *.h *.cpp)

add_library(src ${SOURCES} Game.h Entity.cpp Entity.h Player.cpp Player.h PhysicWorld.cpp PhysicWorld.h PlayerState.h MoveState.cpp MoveState.h HitState.cpp HitState.h DigState.cpp DigState.h Grave.cpp Grave.h Coin.cpp Coin.h)
target_include_directories(src PUBLIC ./)
target_link_libraries(src PUBLIC sfml-system sfml-graphics sfml-window sfml-audio box2d tmxlite)