#include "hls_config.h"


template <int S, int P>
void adder_tree_logic(int *o_data, int i_data[N]) {

    int data[P][S + 1];
    for (int stage = 0; stage <= S; stage++) {
        #pragma HLS UNROLL 
        int ST_OUT_NUM = P >> stage;
        for (int adder = 0; adder < ST_OUT_NUM; adder++) {
          #pragma HLS UNROLL
            if (stage == 0) {
                data[adder][stage] = (adder < N) ? i_data[adder] : 0;
            } else {
                data[adder][stage] = data[adder * 2][stage - 1] + data[adder * 2 + 1][stage - 1];
            }
        }
    }
    *o_data = data[0][S];
}

// Top-level function for Synthesis
void adder_tree(int *o_data, int i_data[N]) {
    #pragma HLS INTERFACE mode=s_axilite port=i_data
    #pragma HLS INTERFACE mode=s_axilite port=o_data
    #pragma HLS INTERFACE mode=s_axilite port=return

    adder_tree_logic<STAGES, POW2_N>(o_data, i_data);
}