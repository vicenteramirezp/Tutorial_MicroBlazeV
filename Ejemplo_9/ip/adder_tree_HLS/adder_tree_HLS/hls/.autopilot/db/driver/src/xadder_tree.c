// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xadder_tree.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XAdder_tree_CfgInitialize(XAdder_tree *InstancePtr, XAdder_tree_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XAdder_tree_Start(XAdder_tree *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdder_tree_ReadReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_AP_CTRL) & 0x80;
    XAdder_tree_WriteReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XAdder_tree_IsDone(XAdder_tree *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdder_tree_ReadReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XAdder_tree_IsIdle(XAdder_tree *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdder_tree_ReadReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XAdder_tree_IsReady(XAdder_tree *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdder_tree_ReadReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XAdder_tree_EnableAutoRestart(XAdder_tree *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdder_tree_WriteReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XAdder_tree_DisableAutoRestart(XAdder_tree *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdder_tree_WriteReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_AP_CTRL, 0);
}

u32 XAdder_tree_Get_o_data(XAdder_tree *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdder_tree_ReadReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_O_DATA_DATA);
    return Data;
}

u32 XAdder_tree_Get_o_data_vld(XAdder_tree *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XAdder_tree_ReadReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_O_DATA_CTRL);
    return Data & 0x1;
}

u32 XAdder_tree_Get_i_data_BaseAddress(XAdder_tree *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XADDER_TREE_CONTROL_ADDR_I_DATA_BASE);
}

u32 XAdder_tree_Get_i_data_HighAddress(XAdder_tree *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (InstancePtr->Control_BaseAddress + XADDER_TREE_CONTROL_ADDR_I_DATA_HIGH);
}

u32 XAdder_tree_Get_i_data_TotalBytes(XAdder_tree *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return (XADDER_TREE_CONTROL_ADDR_I_DATA_HIGH - XADDER_TREE_CONTROL_ADDR_I_DATA_BASE + 1);
}

u32 XAdder_tree_Get_i_data_BitWidth(XAdder_tree *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XADDER_TREE_CONTROL_WIDTH_I_DATA;
}

u32 XAdder_tree_Get_i_data_Depth(XAdder_tree *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XADDER_TREE_CONTROL_DEPTH_I_DATA;
}

u32 XAdder_tree_Write_i_data_Words(XAdder_tree *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XADDER_TREE_CONTROL_ADDR_I_DATA_HIGH - XADDER_TREE_CONTROL_ADDR_I_DATA_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(int *)(InstancePtr->Control_BaseAddress + XADDER_TREE_CONTROL_ADDR_I_DATA_BASE + (offset + i)*4) = *(data + i);
    }
    return length;
}

u32 XAdder_tree_Read_i_data_Words(XAdder_tree *InstancePtr, int offset, word_type *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length)*4 > (XADDER_TREE_CONTROL_ADDR_I_DATA_HIGH - XADDER_TREE_CONTROL_ADDR_I_DATA_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(int *)(InstancePtr->Control_BaseAddress + XADDER_TREE_CONTROL_ADDR_I_DATA_BASE + (offset + i)*4);
    }
    return length;
}

u32 XAdder_tree_Write_i_data_Bytes(XAdder_tree *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XADDER_TREE_CONTROL_ADDR_I_DATA_HIGH - XADDER_TREE_CONTROL_ADDR_I_DATA_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(char *)(InstancePtr->Control_BaseAddress + XADDER_TREE_CONTROL_ADDR_I_DATA_BASE + offset + i) = *(data + i);
    }
    return length;
}

u32 XAdder_tree_Read_i_data_Bytes(XAdder_tree *InstancePtr, int offset, char *data, int length) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr -> IsReady == XIL_COMPONENT_IS_READY);

    int i;

    if ((offset + length) > (XADDER_TREE_CONTROL_ADDR_I_DATA_HIGH - XADDER_TREE_CONTROL_ADDR_I_DATA_BASE + 1))
        return 0;

    for (i = 0; i < length; i++) {
        *(data + i) = *(char *)(InstancePtr->Control_BaseAddress + XADDER_TREE_CONTROL_ADDR_I_DATA_BASE + offset + i);
    }
    return length;
}

void XAdder_tree_InterruptGlobalEnable(XAdder_tree *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdder_tree_WriteReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_GIE, 1);
}

void XAdder_tree_InterruptGlobalDisable(XAdder_tree *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdder_tree_WriteReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_GIE, 0);
}

void XAdder_tree_InterruptEnable(XAdder_tree *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAdder_tree_ReadReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_IER);
    XAdder_tree_WriteReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_IER, Register | Mask);
}

void XAdder_tree_InterruptDisable(XAdder_tree *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XAdder_tree_ReadReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_IER);
    XAdder_tree_WriteReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_IER, Register & (~Mask));
}

void XAdder_tree_InterruptClear(XAdder_tree *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XAdder_tree_WriteReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_ISR, Mask);
}

u32 XAdder_tree_InterruptGetEnabled(XAdder_tree *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAdder_tree_ReadReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_IER);
}

u32 XAdder_tree_InterruptGetStatus(XAdder_tree *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XAdder_tree_ReadReg(InstancePtr->Control_BaseAddress, XADDER_TREE_CONTROL_ADDR_ISR);
}

