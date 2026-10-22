# Copyright (C) 2026 Advanced Micro Devices, Inc.  All rights reserved.
# Copyright (c) 2021 Xilinx, Inc.  All rights reserved.
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.15)
project(AXI_LITE_ADDER_TREE_256_REGS)

find_package(common)
collector_create (PROJECT_LIB_HEADERS "${CMAKE_CURRENT_SOURCE_DIR}")
collector_create (PROJECT_LIB_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}")
include_directories(${CMAKE_BINARY_DIR}/include)
collect (PROJECT_LIB_SOURCES xAXI_LITE_ADDER_TREE_256_REGS_g.c)
collect (PROJECT_LIB_SOURCES AXI_LITE_ADDER_TREE_256_REGS.c)
collect (PROJECT_LIB_HEADERS AXI_LITE_ADDER_TREE_256_REGS.h)
collector_list (_sources PROJECT_LIB_SOURCES)
collector_list (_headers PROJECT_LIB_HEADERS)
file(COPY ${_headers} DESTINATION ${CMAKE_BINARY_DIR}/include)
add_library(AXI_LITE_ADDER_TREE_256_REGS STATIC ${_sources})
set_target_properties(AXI_LITE_ADDER_TREE_256_REGS PROPERTIES LINKER_LANGUAGE C)
