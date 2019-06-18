cmake_minimum_required(VERSION 3.13)
project(DataStructure)

set(CMAKE_CXX_STANDARD 14)

add_executable(DataStructure main.cpp BTree.cpp BTree.h BTreeNode.cpp BTreeNode.h)