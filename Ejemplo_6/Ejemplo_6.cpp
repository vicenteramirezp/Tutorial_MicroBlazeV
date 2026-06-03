#include "xparameters.h"
#include "xil_exception.h"
#include <iomanip>
#include <iostream>
#include <xil_types.h>
#include <xstatus.h>
#include "xinterrupt_wrap.h"

#include "ap_fixed.h"
#include "xil_cache.h"
#include "xhls_pp.h"

#define N           5
#define DESIGN_W    16
#define DESIGN_I    4
#define N_TESTS     100

typedef ap_fixed<DESIGN_W, DESIGN_I, AP_RND_CONV, AP_SAT> fixed_t;
typedef ap_fixed<2*DESIGN_W, 2*DESIGN_I, AP_RND_CONV, AP_SAT> fixed_res_t;

uint16_t get_bits(fixed_t val) {
	return (uint16_t)val.range();
}

int main()
{
	int status;
	XHls_pp hls_pp;
	XHls_pp_Config *hls_config = XHls_pp_LookupConfig(XPAR_HLS_PP_0_BASEADDR);
	XHls_pp_CfgInitialize(&hls_pp,hls_config);
	fixed_t vec_a[N];
	fixed_t vec_b[N];
	
	u32 packed_a[3];
	u32 packed_b[3];
	
	std::cout << "Running! ..." << std::endl;
	
	while (true) {
		// Recibir datos
		float temp;
		for (int i = 0; i < N; i++) { if (!(std::cin >> temp)) return 0; vec_a[i] = temp; }
		for (int i = 0; i < N; i++) { if (!(std::cin >> temp)) return 0; vec_b[i] = temp; }
		
		// Empaquetado
		// Debido a que los registros son de 32 bits y las palabras a escribir son de 16 bits, se tiene que realizar manejo de estas
		// Based on: Word n: bit [15:0] - x[2n], bit [31:16] - x[2n+1]
		
		// Word 0: x[0] and x[1]
		packed_a[0] = (uint32_t)get_bits(vec_a[0]) | ((uint32_t)get_bits(vec_a[1]) << 16);
		packed_b[0] = (uint32_t)get_bits(vec_b[0]) | ((uint32_t)get_bits(vec_b[1]) << 16);
		
		// Word 1: x[2] and x[3]
		packed_a[1] = (uint32_t)get_bits(vec_a[2]) | ((uint32_t)get_bits(vec_a[3]) << 16);
		packed_b[1] = (uint32_t)get_bits(vec_b[2]) | ((uint32_t)get_bits(vec_b[3]) << 16);
		// Word 2: x[4]
		packed_a[2] = (uint32_t)get_bits(vec_a[4]);
		packed_b[2] = (uint32_t)get_bits(vec_b[4]);
		// 3. Write to Hardware
		// We only write 3 words because the address space for 'x' is 0x20 to 0x2F (16 bytes)
		XHls_pp_Write_x_Words(&hls_pp, 0, (word_type *)packed_a, 3);
		XHls_pp_Write_y_Words(&hls_pp, 0, (word_type *)packed_b, 3);
		
		// Ejecucion
		XHls_pp_Start(&hls_pp);
		while (!XHls_pp_IsDone(&hls_pp));
		
		// Leer Resultado
		u32 result_int = XHls_pp_Get_pp(&hls_pp);
		fixed_res_t result_fixed;
		result_fixed = *((fixed_res_t *) &result_int);
		
		std::cout << "Resultado: " << std::fixed<< std::setprecision(10) << result_fixed.to_float() << std::endl;
		
	}
	
	return 0;
}
