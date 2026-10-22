// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XADDER_TREE_H
#define XADDER_TREE_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "xadder_tree_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Control_BaseAddress;
} XAdder_tree_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u32 IsReady;
} XAdder_tree;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XAdder_tree_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XAdder_tree_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XAdder_tree_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XAdder_tree_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XAdder_tree_Initialize(XAdder_tree *InstancePtr, UINTPTR BaseAddress);
XAdder_tree_Config* XAdder_tree_LookupConfig(UINTPTR BaseAddress);
#else
int XAdder_tree_Initialize(XAdder_tree *InstancePtr, u16 DeviceId);
XAdder_tree_Config* XAdder_tree_LookupConfig(u16 DeviceId);
#endif
int XAdder_tree_CfgInitialize(XAdder_tree *InstancePtr, XAdder_tree_Config *ConfigPtr);
#else
int XAdder_tree_Initialize(XAdder_tree *InstancePtr, const char* InstanceName);
int XAdder_tree_Release(XAdder_tree *InstancePtr);
#endif

void XAdder_tree_Start(XAdder_tree *InstancePtr);
u32 XAdder_tree_IsDone(XAdder_tree *InstancePtr);
u32 XAdder_tree_IsIdle(XAdder_tree *InstancePtr);
u32 XAdder_tree_IsReady(XAdder_tree *InstancePtr);
void XAdder_tree_EnableAutoRestart(XAdder_tree *InstancePtr);
void XAdder_tree_DisableAutoRestart(XAdder_tree *InstancePtr);

u32 XAdder_tree_Get_o_data(XAdder_tree *InstancePtr);
u32 XAdder_tree_Get_o_data_vld(XAdder_tree *InstancePtr);
u32 XAdder_tree_Get_i_data_BaseAddress(XAdder_tree *InstancePtr);
u32 XAdder_tree_Get_i_data_HighAddress(XAdder_tree *InstancePtr);
u32 XAdder_tree_Get_i_data_TotalBytes(XAdder_tree *InstancePtr);
u32 XAdder_tree_Get_i_data_BitWidth(XAdder_tree *InstancePtr);
u32 XAdder_tree_Get_i_data_Depth(XAdder_tree *InstancePtr);
u32 XAdder_tree_Write_i_data_Words(XAdder_tree *InstancePtr, int offset, word_type *data, int length);
u32 XAdder_tree_Read_i_data_Words(XAdder_tree *InstancePtr, int offset, word_type *data, int length);
u32 XAdder_tree_Write_i_data_Bytes(XAdder_tree *InstancePtr, int offset, char *data, int length);
u32 XAdder_tree_Read_i_data_Bytes(XAdder_tree *InstancePtr, int offset, char *data, int length);

void XAdder_tree_InterruptGlobalEnable(XAdder_tree *InstancePtr);
void XAdder_tree_InterruptGlobalDisable(XAdder_tree *InstancePtr);
void XAdder_tree_InterruptEnable(XAdder_tree *InstancePtr, u32 Mask);
void XAdder_tree_InterruptDisable(XAdder_tree *InstancePtr, u32 Mask);
void XAdder_tree_InterruptClear(XAdder_tree *InstancePtr, u32 Mask);
u32 XAdder_tree_InterruptGetEnabled(XAdder_tree *InstancePtr);
u32 XAdder_tree_InterruptGetStatus(XAdder_tree *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif
