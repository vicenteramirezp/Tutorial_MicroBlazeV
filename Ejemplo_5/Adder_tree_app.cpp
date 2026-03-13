
//#include "/home/vicente/Desktop/Memoria/Adder_tree_hls/Adder_tree_platform/hw/sdt/drivers/adder_tree_v1_0/src/xadder_tree.h"
#include "xadder_tree.h"
#include <stdio.h>
//#include "platform.h"
#include "xil_printf.h"
#include "xparameters.h"


int main() {
    int status;
    xil_printf("--- HLS Adder tree Test ---\r\n");

    // Inicializa IP
    XAdder_tree hls_inst;
    XAdder_tree_Config *tree_config = XAdder_tree_LookupConfig(XPAR_XADDER_TREE_0_BASEADDR);
    status = XAdder_tree_CfgInitialize(&hls_inst, tree_config);
    if (status != XST_SUCCESS) {
        xil_printf("ERROR: Inicializacion fallada\r\n");
        return XST_FAILURE;
    }

    // Datos de entrada
    int input[8] ={10,20,30,40,50,60,70,80};
    // Escribir datos
    XAdder_tree_Write_i_data_Words(&hls_inst, 0, (word_type*)input, 8);

    
    // Manda señal de inicio al periferico
    XAdder_tree_Start(&hls_inst);
    //Esperar a recibir resultado
    while (!XAdder_tree_IsDone(&hls_inst));

    // Leer resultado
    int result = XAdder_tree_Get_o_data(&hls_inst);
    xil_printf("Resultado obtenido de la IP: %d\r\n", result);
    return 0;
}