cmake_minimum_required(VERSION 3.9)
project(GitList)

set(CMAKE_CXX_STANDARD 14)

add_executable(GitList main.cpp Skiplist/Skiplist.cpp Skiplist/Skiplist.h AVTree/AVLTree.cpp AVTree/AVLTree.h)