
#ifndef HLS_CONFIG

#define HLS_CONFIG

#include <ap_fixed.h>

/* Vector length */
#define N 5
#define DESIGN_W 16
#define DESIGN_I 4


/* Data type */
typedef ap_fixed<DESIGN_W, DESIGN_I, AP_RND_CONV, AP_SAT> data_t;
typedef ap_fixed<2*DESIGN_W, 2*DESIGN_I, AP_RND_CONV, AP_SAT> res_data_t;

void hls_pp(res_data_t *pp, data_t x[N], data_t y[N]);

#endif
