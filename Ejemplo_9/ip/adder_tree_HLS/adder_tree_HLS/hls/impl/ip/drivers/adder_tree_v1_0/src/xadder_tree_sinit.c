// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2025.2 (64-bit)
// Tool Version Limit: 2025.11
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2025 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xadder_tree.h"

extern XAdder_tree_Config XAdder_tree_ConfigTable[];

#ifdef SDT
XAdder_tree_Config *XAdder_tree_LookupConfig(UINTPTR BaseAddress) {
	XAdder_tree_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XAdder_tree_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XAdder_tree_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XAdder_tree_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XAdder_tree_Initialize(XAdder_tree *InstancePtr, UINTPTR BaseAddress) {
	XAdder_tree_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XAdder_tree_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XAdder_tree_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XAdder_tree_Config *XAdder_tree_LookupConfig(u16 DeviceId) {
	XAdder_tree_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XADDER_TREE_NUM_INSTANCES; Index++) {
		if (XAdder_tree_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XAdder_tree_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XAdder_tree_Initialize(XAdder_tree *InstancePtr, u16 DeviceId) {
	XAdder_tree_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XAdder_tree_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XAdder_tree_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif

