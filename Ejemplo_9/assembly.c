#include "xil_printf.h"
#include "xtmrctr.h"


XTmrCtr     TimerInstance;

#define TIMER_COUNTER_0   0
#define TIMER_COUNTER_1   1

int main(void)
{
    u32 ticks;
    int Status;

    Status = XTmrCtr_Initialize(&TimerInstance, XPAR_AXI_TIMER_0_BASEADDR);
    if (Status != XST_SUCCESS) return XST_FAILURE;

    /* ================================================================ */
    /*  Overhead de medición.                                           */
    /* ================================================================ */

    XTmrCtr_Reset(&TimerInstance, TIMER_COUNTER_0);
    XTmrCtr_Start(&TimerInstance, TIMER_COUNTER_0);
    XTmrCtr_Stop(&TimerInstance, TIMER_COUNTER_0);
    ticks = XTmrCtr_GetValue(&TimerInstance, TIMER_COUNTER_0);

    xil_printf("Overhead ventana vacia: %d\r\n", ticks);



    /* ================================================================ */
    /*  Medición de escritura en un periferico                          */
    /* ================================================================ */


    u32 value = 1; 
    u32 addr  = XPAR_AXI_LITE_ADDER_TREE_0_BASEADDR;

    XTmrCtr_Reset(&TimerInstance, TIMER_COUNTER_0);
    XTmrCtr_Start(&TimerInstance, TIMER_COUNTER_0);
    __asm__ volatile (
        "sw %0, 0(%1)"            
        :                         
        : "r"(value), "r"(addr)   
        : "memory"
    );
    XTmrCtr_Stop(&TimerInstance, TIMER_COUNTER_0);
    ticks = XTmrCtr_GetValue(&TimerInstance, TIMER_COUNTER_0);
    xil_printf("ticks = %d\r\n", ticks);

    /* ================================================================ */
    /*  Medición de escritura en un periferico con 1 NOP                */
    /* ================================================================ */


     value = 1;  
     addr  = XPAR_AXI_LITE_ADDER_TREE_0_BASEADDR;

    XTmrCtr_Reset(&TimerInstance, TIMER_COUNTER_0);
    XTmrCtr_Start(&TimerInstance, TIMER_COUNTER_0);
    __asm__ volatile(
    "nop\n\t"
    "sw %0, 0(%1)\n\t"
    :
    : "r"(value), "r"(addr)
    : "memory");
    XTmrCtr_Stop(&TimerInstance, TIMER_COUNTER_0);
    ticks = XTmrCtr_GetValue(&TimerInstance, TIMER_COUNTER_0);
    xil_printf("ticks 1 nop = %d\r\n", ticks);

    /* ================================================================ */
    /*  Medición de escritura en un periferico con 2 NOP                */
    /* ================================================================ */


     value = 1;  
     addr  = XPAR_AXI_LITE_ADDER_TREE_0_BASEADDR;

    XTmrCtr_Reset(&TimerInstance, TIMER_COUNTER_0);
    XTmrCtr_Start(&TimerInstance, TIMER_COUNTER_0);
    __asm__ volatile(
    "nop\n\t"
    "nop\n\t"
    "sw %0, 0(%1)\n\t"
    :
    : "r"(value), "r"(addr)
    : "memory");
    XTmrCtr_Stop(&TimerInstance, TIMER_COUNTER_0);
    ticks = XTmrCtr_GetValue(&TimerInstance, TIMER_COUNTER_0);
    xil_printf("ticks 2 nop = %d\r\n", ticks);



    /* ================================================================ */
    /*  Medición de escritura en un periferico con 3 NOP                */
    /* ================================================================ */


     value = 1;  
     addr  = XPAR_AXI_LITE_ADDER_TREE_0_BASEADDR;

    XTmrCtr_Reset(&TimerInstance, TIMER_COUNTER_0);
    XTmrCtr_Start(&TimerInstance, TIMER_COUNTER_0);
    __asm__ volatile(
    "nop\n\t"
    "nop\n\t"
    "nop\n\t"
    "sw %0, 0(%1)\n\t"
    :
    : "r"(value), "r"(addr)
    : "memory");
    XTmrCtr_Stop(&TimerInstance, TIMER_COUNTER_0);
    ticks = XTmrCtr_GetValue(&TimerInstance, TIMER_COUNTER_0);
    xil_printf("ticks 3 nop = %d\r\n", ticks);
    xil_printf("\r\n");


    
    return 0;
}