
#include "hls_config.h"

template <int STAGES, int POW2_INPUTS>
void adder_tree (res_data_t *o_data, res_data_t *i_data)
{
	res_data_t data[POW2_INPUTS][STAGES];

	for (int stage = 0; stage <= STAGES; stage++)
	{
		int ST_OUT_NUM = POW2_INPUTS >> stage;
		for (int adder = 0; adder < ST_OUT_NUM; adder++)
		{
			if (stage == 0)
			{
				if (adder < N)
				{
					data[adder][stage] = i_data[adder];
				}
				else
				{
					data[adder][stage] = 0;
				}
			}
			else
			{
				data[adder][stage] = data[adder*2][stage-1] + data[adder*2+1][stage-1];
			}
		}
	}

	*o_data = data[0][STAGES];
}


void hls_pp(res_data_t *pp, data_t x[N], data_t y[N])
{
#pragma HLS INTERFACE mode=s_axilite port=x
#pragma HLS INTERFACE mode=s_axilite port=y
#pragma HLS INTERFACE mode=s_axilite port=pp
#pragma HLS INTERFACE mode=s_axilite port=return //indica que tenga pines de control, ya que es un void (la funcion), si fuera de algun tipo distinto de void habria un puerto fisico

	res_data_t res[N];


	MainLoop: for (int i = 0; i < N; ++i)
	{
		#pragma HLS UNROLL
		res[i] = x[i]*y[i];
	}

	// for (int i = 0; i < N; ++i)
	// 	{
	// 		#pragma HLS UNROLL
	// 		r+= res[i];
	// 	}

	adder_tree<3, 8>(pp, res); // <ceil(log(N)),2**ceil(log(N))>

}


