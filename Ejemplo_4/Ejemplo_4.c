//Libreria del periferico generada con el con los comandos descritos en el script "create_driver.tcl"
#include "adder_tree_rtl.h"

#include <stdio.h>
#include "xil_printf.h"
#include "xparameters.h"
#include "xil_io.h"


int main() {
    xil_printf("--- Prueba Adder Tree descrito en RTL ---\r\n");

    // Entradas de 16 bits
    uint16_t input[8] = {10, 20, 30, 40, 50, 60, 70, 80};

    // Como los registros son de 32 bits, se guardan dos entradas en cada uno
    uint32_t reg0_val = ((uint32_t)input[1] << 16) | input[0];
    uint32_t reg1_val = ((uint32_t)input[3] << 16) | input[2];
    uint32_t reg2_val = ((uint32_t)input[5] << 16) | input[4];
    uint32_t reg3_val = ((uint32_t)input[7] << 16) | input[6];

    // Escritura de entradas
    ADDER_TREE_RTL_mWriteReg(XPAR_ADDER_TREE_RTL_0_BASEADDR, ADDER_TREE_RTL_S00_AXI_SLV_REG0_OFFSET, reg0_val);
    ADDER_TREE_RTL_mWriteReg(XPAR_ADDER_TREE_RTL_0_BASEADDR, ADDER_TREE_RTL_S00_AXI_SLV_REG1_OFFSET, reg1_val);
    ADDER_TREE_RTL_mWriteReg(XPAR_ADDER_TREE_RTL_0_BASEADDR, ADDER_TREE_RTL_S00_AXI_SLV_REG2_OFFSET, reg2_val);
    ADDER_TREE_RTL_mWriteReg(XPAR_ADDER_TREE_RTL_0_BASEADDR, ADDER_TREE_RTL_S00_AXI_SLV_REG3_OFFSET, reg3_val);

    // Lectura de salida
    int total_sum = ADDER_TREE_RTL_mReadReg(XPAR_ADDER_TREE_RTL_0_BASEADDR, ADDER_TREE_RTL_S00_AXI_SLV_REG4_OFFSET);
    xil_printf("Resultado obtenido de la IP: %d\r\n", total_sum);

    return 0;
}