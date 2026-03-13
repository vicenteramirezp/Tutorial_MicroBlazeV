#ifndef HLS_CONFIG
#define HLS_CONFIG

#define N 8
#define POW2_N 8 // Next power of 2
#define STAGES 3 // log2(8)

// Prototype must match the synthesized instance
void adder_tree(int *o_data, int i_data[N]);

#endif