cmake_minimum_required(VERSION 3.10)
project(game)

set(CMAKE_CXX_STANDARD 17)
include_directories("${CMAKE_SOURCE_DIR}/SFML-2.6.2/include")
link_directories("${CMAKE_SOURCE_DIR}/SFML-2.6.2/lib")


add_executable(game
 src/main.cpp
 src/Game.cpp
 src/Player.cpp
 src/Bullet.cpp
 src/Enemy.cpp
 src/StrongEnemy.cpp
)

target_link_libraries(game sfml-graphics sfml-window sfml-system)