

#include <stdio.h>
#include "xil_types.h"
#include "xil_cache.h"
#include "xparameters.h"
#include "display_ctrl.h"

// Tamaño del cuadro 
#define MAX_FRAME (1280*1024)
#define FRAME_STRIDE (1280*4)

DisplayCtrl dispCtrl; // Display driver struct
u32 frameBuf[DISPLAY_NUM_FRAMES][MAX_FRAME]; // Buffers para los cuadros
void *pFrames[DISPLAY_NUM_FRAMES]; // Arreglo de punteros a los cuadros

int main(void) {
	// Inicializar arreglos de punteros a los cuadros
	int i;
	for (i = 0; i < DISPLAY_NUM_FRAMES; i++)
		pFrames[i] = frameBuf[i];

	// Inicializar controlador del display (inicializa AXI_VDMA, Video Timing controller y Dinamic clock gen)
	DisplayInitialize(&dispCtrl, XPAR_XAXIVDMA_0_BASEADDR, XPAR_XVTC_0_BASEADDR, XPAR_AXI_DYNCLK_0_BASEADDR, pFrames, FRAME_STRIDE);

	// Elije el primer frame
	DisplayChangeFrame(&dispCtrl, 0);

	// Fija la resolucion
	DisplaySetMode(&dispCtrl, &VMODE_1280x1024);

	// Habilita la imagen
	DisplayStart(&dispCtrl);

	// Parametros obtenidos del controlador del display para la animacion
	int x, y;
	u32 stride = dispCtrl.stride / 4;
	u32 width = dispCtrl.vMode.width;
	u32 height = dispCtrl.vMode.height;

	u32 *frame;
	int right = 1;
	int down = 1;
	int xpos = 0;
	int ypos = 0;
	int step =4;
	u32 buff = dispCtrl.curFrame;

	// Animacion de un cuadrito moviendose
	while (1) {
			// Alterna entre los dos cuadros guardados en memoria
			buff = !buff;
			frame = dispCtrl.framePtr[buff];

			// Rellena la pantalla con blanco
			memset(frame, 0xFF, MAX_FRAME*4);

			// Ajusta la posicion del cuadrado (si llega al borde de la pantalla choca)
			if (right) {
				xpos=xpos+step;
				if (xpos == width-64)
					right = 0;
			}
			else {
				xpos=xpos-step;
				if (xpos == 0)
					right = 1;
			}
			if (down) {
				ypos=ypos+step;
				if (ypos == height-64) {
					down = 0;
				}
			}
			else {
				ypos=ypos-step;
				if (ypos == 0) {
					down = 1;
				}
			}

			// Dibuja el cuadrado en la posicion
			for (x = xpos; x < xpos+64; x++) {
				for (y = ypos; y < ypos+64; y++) {
					frame[y*stride + x] = 0;
				}
			}

			// Limpia el cache para no interferir con la imagen
			Xil_DCacheFlush();

			// Cambia el frame activo al buffer
			DisplayChangeFrame(&dispCtrl, buff);

			// Espera a que el controlador del display este listo para cambiar los cuadros
			DisplayWaitForSync(&dispCtrl);
	}

	return 0;
}
