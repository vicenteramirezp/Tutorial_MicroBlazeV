
#include "xparameters.h"
#include "xil_exception.h"
#include <iomanip>
#include <iostream>
#include <xil_types.h>
#include <xstatus.h>
#include "xinterrupt_wrap.h"

#include "ap_fixed.h"

#include "xhls_pp.h"

#define HLS_IP_BASEADDRESS 		XPAR_HLS_PP_0_BASEADDR
#define HLS_INTERRUPTS 			XPAR_HLS_PP_0_INTERRUPTS
#define HLS_INTERRUPT_PARENT	XPAR_HLS_PP_0_INTERRUPT_PARENT

#define N           5
#define DESIGN_W    16
#define DESIGN_I    4
#define N_TESTS     100

typedef ap_fixed<DESIGN_W, DESIGN_I, AP_RND_CONV, AP_SAT> fixed_t;
typedef ap_fixed<2*DESIGN_W, 2*DESIGN_I, AP_RND_CONV, AP_SAT> fixed_res_t;

volatile int ip_status;

enum IP_ready
{
    IP_READY,
    IP_BUSY
};

void IPHandle(void *InstPtr)
{
    float result;
    u32 result_int;
    fixed_res_t result_fixed;
    XHls_pp_InterruptDisable(&ip, 1);

    result_int = XHls_pp_Get_pp(&ip);

    result_fixed = *((fixed_res_t *) &result_int);

    std::cout << "Resultado: " << std::fixed<< std::setprecision(10) << result_fixed.to_float() << std::endl;

    ip_status = IP_READY;
    XHls_pp_InterruptClear(&ip,1);
    XHls_pp_InterruptEnable(&ip,1);
}

void get_vector_from_host(fixed_t vec1[N])
{
    float temp;
    for (int i=0; i< N; i++)
    {
        //scanf("%f", &temp);
        std::cin >> temp;
        vec1[i] = temp;
    }
}

int main()
{
    int status;
    u32 vec_a_int [N];
    u32 vec_b_int [N];

    fixed_t vec_a_fixed [N];
    fixed_t vec_b_fixed [N];

    std::cout << "Running! ..." << std::endl;

    for(int i = 0; i < N_TESTS; i++)
    {
        get_vector_from_host(vec_a_fixed);
        get_vector_from_host(vec_b_fixed);

        for (int j = 0; j < N; j++)
        {
            // Avoidable, but useful for tracing individual value conversions. 
            vec_a_int[j] = *((u32*) &vec_a_fixed[j]); // Reinterprets vec_a_fixed[j] as u32 via pointer cast.
            vec_b_int[j] = *((u32*) &vec_b_fixed[j]);
        }
        status = DOT_PRODUCT_IP_clearTrigger(DOT_PRODUCT_IP_ADDR);

        status = DOT_PRODUCT_IP_compute(DOT_PRODUCT_IP_ADDR, vec_a_int, vec_b_int, &result_int);
        //if (status != XST_SUCCESS) return status; 

        result_fixed = *((fixed_res_t *) &result_int);
        //xil_printf("Resultado: %.10f\n", result_fixed.to_float());
        std::cout << "Resultado: " << std::fixed<< std::setprecision(10) << result_fixed.to_float() << std::endl;

    }

    return 0;
}
