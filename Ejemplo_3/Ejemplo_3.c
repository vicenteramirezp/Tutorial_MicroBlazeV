#include <stdio.h>
#include <xgpio.h>
#include "xparameters.h"
#include "xuartlite.h"
#include "xintc.h"
#include "xil_exception.h"
#include "xil_printf.h"

XIntc     IntcInstance;
XUartLite UartInstance;
XGpio     GpioInstance;

#define BUTTON_CHANNEL  1
#define LED_CHANNEL     2
#define BUTTON_IR_MASK  XGPIO_IR_CH1_MASK

void UartHandler(void *CallbackRef) {
    XUartLite *UartPtr = (XUartLite *)CallbackRef;
    u8 ReadBuffer[2] = {0};  // 1 char + null terminator

    unsigned int ReceivedCount = XUartLite_Recv(UartPtr, ReadBuffer, 1);
    if (ReceivedCount > 0) {
        xil_printf("Interrupcion de UART! Recibio: %s\r\n", ReadBuffer);
    }
    XIntc_Acknowledge(&IntcInstance, XPAR_FABRIC_AXI_UARTLITE_0_INTR);
}

void GpioHandler(void *CallbackRef) {
    XGpio *GpioPtr = (XGpio *)CallbackRef;

    XGpio_InterruptDisable(GpioPtr, BUTTON_IR_MASK);

    u32 buttonState = XGpio_DiscreteRead(GpioPtr, BUTTON_CHANNEL);
    XGpio_DiscreteWrite(GpioPtr, LED_CHANNEL, buttonState);

    if (buttonState != 0) {
        xil_printf("Boton presionado! Valor: 0x%X\r\n", buttonState);
    }

    XGpio_InterruptClear(GpioPtr, BUTTON_IR_MASK);
    XIntc_Acknowledge(&IntcInstance, XPAR_FABRIC_AXI_GPIO_0_INTR);
    XGpio_InterruptEnable(GpioPtr, BUTTON_IR_MASK);
}

int main() {
    int Status;
    // Inicializacion de los perifericos
    Status = XUartLite_Initialize(&UartInstance, XPAR_XUARTLITE_0_BASEADDR);
    if (Status != XST_SUCCESS) return XST_FAILURE;

    Status = XGpio_Initialize(&GpioInstance, XPAR_AXI_GPIO_0_BASEADDR);
    if (Status != XST_SUCCESS) return XST_FAILURE;

    // Channel 1 = botones (entradas), Channel 2 = LEDs (salidas)
    XGpio_SetDataDirection(&GpioInstance, BUTTON_CHANNEL, 0xFFFFFFFF);
    XGpio_SetDataDirection(&GpioInstance, LED_CHANNEL,    0x00000000);
    XGpio_InterruptClear(&GpioInstance, XGPIO_IR_CH1_MASK | XGPIO_IR_CH2_MASK);

    //Inicializacion del controlador de interrupciones
    Status = XIntc_Initialize(&IntcInstance, XPAR_XINTC_0_BASEADDR);
    if (Status != XST_SUCCESS) return XST_FAILURE;

    // Conexiones de interrupción al controlador
    Status = XIntc_Connect(&IntcInstance, XPAR_FABRIC_AXI_UARTLITE_0_INTR,
                           (XInterruptHandler)UartHandler, &UartInstance);
    if (Status != XST_SUCCESS) return XST_FAILURE;

    Status = XIntc_Connect(&IntcInstance, XPAR_FABRIC_AXI_GPIO_0_INTR,
                           (XInterruptHandler)GpioHandler, &GpioInstance);
    if (Status != XST_SUCCESS) return XST_FAILURE;

    // Habilita el controlador
    Status = XIntc_Start(&IntcInstance, XIN_REAL_MODE);
    if (Status != XST_SUCCESS) return XST_FAILURE;
    //Habilita las interrupciones de los dos perifericos dentro del controlador
    XIntc_Enable(&IntcInstance, XPAR_FABRIC_AXI_UARTLITE_0_INTR);
    XIntc_Enable(&IntcInstance, XPAR_FABRIC_AXI_GPIO_0_INTR);

    // Habilitacion  de excepciones (necesario para el uso de interrupciones en Risc-v)
    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
                                 (Xil_ExceptionHandler)XIntc_InterruptHandler,
                                 &IntcInstance);
    Xil_ExceptionEnable();

    // Habilita las interrupciones desde los perifericos de ambos perifericos
    XUartLite_EnableInterrupt(&UartInstance);
    XGpio_InterruptEnable(&GpioInstance, BUTTON_IR_MASK);
    XGpio_InterruptGlobalEnable(&GpioInstance);

    xil_printf("Presione un boton o mande un mensaje por la terminal.\r\n");

    while (1);
    return 0;
}
