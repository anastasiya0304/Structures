cmake_minimum_required(VERSION 3.9)
project(AVL_Skip)

set(CMAKE_CXX_STANDARD 11)

add_executable(AVL_Skip main.cpp Skiplist.cpp Skiplist.h AVLTree.cpp AVLTree.h)