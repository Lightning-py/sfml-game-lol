cmake_minimum_required(VERSION 3.10)


project(game)






add_compile_options(-Wall)
add_link_options(-lsfml-graphics -lsfml-window -lsfml-system)



add_executable(game main.cpp)

