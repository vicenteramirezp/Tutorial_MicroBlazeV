#include <stdio.h>
#include <xgpio.h>
#include "xparameters.h"
#include "xuartlite.h"
#include "xintc.h"
#include "xil_exception.h"
#include "xil_printf.h"

// Instancias de perifericos
XIntc IntcInstance;
XUartLite UartInstance;
XGpio GpioInstance;
// Handler de UART
void UartHandler(void *CallbackRef) {
    XUartLite *UartPtr = (XUartLite *)CallbackRef;
    u8 ReadBuffer[5];

    unsigned int ReceivedCount = XUartLite_Recv(UartPtr, ReadBuffer, 5);

    if (ReceivedCount > 0) {
        xil_printf("Interrupcion de UART! Recibio: %s\r\n", ReadBuffer);
    }
    XIntc_Acknowledge(&IntcInstance, XPAR_FABRIC_AXI_UARTLITE_0_INTR);
}
// Handler de GPIO
void GpioHandler(void *CallbackRef) {
    XGpio *GpioPtr = (XGpio *)CallbackRef;
    u32 buttonState;
    //  Leer el estado actual de los botones en el Canal 2
    buttonState = XGpio_DiscreteRead(GpioPtr, 2);
    // Limpiar el registro de interrupcion asociado a gpio
    XGpio_InterruptClear(GpioPtr, XGPIO_IR_CH2_MASK);
    // Identificar y mostrar qué botón se presionó
    if (buttonState != 0) {
        xil_printf("Boton presionado! Valor: 0x%X\r\n", buttonState);
    }
    XGpio_DiscreteWrite(GpioPtr,1,buttonState);
    // Lanzar el ACK al controlador de la interrupcion
    XIntc_Acknowledge(&IntcInstance, XPAR_FABRIC_AXI_GPIO_0_INTR);
}

int main() {
    int Status;

    // Inicializar UARTLite
    Status = XUartLite_Initialize(&UartInstance, XPAR_XUARTLITE_0_BASEADDR);
    if (Status != XST_SUCCESS) return XST_FAILURE;
    // Inicializar GPIOS
    Status =XGpio_Initialize(&GpioInstance,XPAR_AXI_GPIO_0_BASEADDR);
    if (Status != XST_SUCCESS) return XST_FAILURE;
    
    // Inicializar Controlador de interrupciones
    Status = XIntc_Initialize(&IntcInstance, XPAR_XINTC_0_BASEADDR);
    if (Status != XST_SUCCESS) return XST_FAILURE;

    // Conectar Handler de UART 
    Status = XIntc_Connect(&IntcInstance, XPAR_FABRIC_AXI_UARTLITE_0_INTR,
                           (XInterruptHandler)UartHandler, &UartInstance);
    if (Status != XST_SUCCESS) return XST_FAILURE;

    // Conectar Handler de GPIO
     Status = XIntc_Connect(&IntcInstance, XPAR_FABRIC_AXI_GPIO_0_INTR,
                           (XInterruptHandler)GpioHandler, &GpioInstance);
    if (Status != XST_SUCCESS) return XST_FAILURE;

    XGpio_InterruptGlobalEnable(&GpioInstance);
    XGpio_InterruptEnable(&GpioInstance, XGPIO_IR_CH2_MASK);
    // Habilitar controlador de interrupciones
    Status = XIntc_Start(&IntcInstance, XIN_REAL_MODE);
    if (Status != XST_SUCCESS) return XST_FAILURE;

    // Habilitar interrupciones
    XIntc_Enable(&IntcInstance, XPAR_FABRIC_AXI_UARTLITE_0_INTR);
    XIntc_Enable(&IntcInstance, XPAR_FABRIC_AXI_GPIO_0_INTR);

    // Habilitar excepciones (en MicroBlazeV es prerequisito para hacer uso de interrupciones)
    Xil_ExceptionInit();
    Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
                                 (Xil_ExceptionHandler)XIntc_InterruptHandler,
                                 &IntcInstance);
    Xil_ExceptionEnable();

    // 7. Enable UART Peripheral Interrupts
    XUartLite_EnableInterrupt(&UartInstance);
    xil_printf("Ejemplo de interrupciones listo, presione un boton o mande un mensaje a traves de la terminal serial\r\n");
    XIntc_SimulateIntr(&IntcInstance, XPAR_FABRIC_AXI_UARTLITE_0_INTR);
    
    while(1);
    return 0;
}