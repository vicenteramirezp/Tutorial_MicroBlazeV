// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
// control
// 0x000 : Control signals
//         bit 0  - ap_start (Read/Write/COH)
//         bit 1  - ap_done (Read/COR)
//         bit 2  - ap_idle (Read)
//         bit 3  - ap_ready (Read/COR)
//         bit 7  - auto_restart (Read/Write)
//         bit 9  - interrupt (Read)
//         others - reserved
// 0x004 : Global Interrupt Enable Register
//         bit 0  - Global Interrupt Enable (Read/Write)
//         others - reserved
// 0x008 : IP Interrupt Enable Register (Read/Write)
//         bit 0 - enable ap_done interrupt (Read/Write)
//         bit 1 - enable ap_ready interrupt (Read/Write)
//         others - reserved
// 0x00c : IP Interrupt Status Register (Read/TOW)
//         bit 0 - ap_done (Read/TOW)
//         bit 1 - ap_ready (Read/TOW)
//         others - reserved
// 0x010 : Data signal of o_data
//         bit 31~0 - o_data[31:0] (Read)
// 0x014 : Control signal of o_data
//         bit 0  - o_data_ap_vld (Read/COR)
//         others - reserved
// 0x400 ~
// 0x7ff : Memory 'i_data' (256 * 32b)
//         Word n : bit [31:0] - i_data[n]
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define XADDER_TREE_CONTROL_ADDR_AP_CTRL     0x000
#define XADDER_TREE_CONTROL_ADDR_GIE         0x004
#define XADDER_TREE_CONTROL_ADDR_IER         0x008
#define XADDER_TREE_CONTROL_ADDR_ISR         0x00c
#define XADDER_TREE_CONTROL_ADDR_O_DATA_DATA 0x010
#define XADDER_TREE_CONTROL_BITS_O_DATA_DATA 32
#define XADDER_TREE_CONTROL_ADDR_O_DATA_CTRL 0x014
#define XADDER_TREE_CONTROL_ADDR_I_DATA_BASE 0x400
#define XADDER_TREE_CONTROL_ADDR_I_DATA_HIGH 0x7ff
#define XADDER_TREE_CONTROL_WIDTH_I_DATA     32
#define XADDER_TREE_CONTROL_DEPTH_I_DATA     256

