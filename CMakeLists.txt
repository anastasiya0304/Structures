cmake_minimum_required(VERSION 3.9)
project(GitList)

set(CMAKE_CXX_STANDARD 14)

add_executable(GitList main.cpp SkipList.cpp SkipList.h AVLTree.cpp AVLTree.h)