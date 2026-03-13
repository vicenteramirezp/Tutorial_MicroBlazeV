`timescale 1ns / 1ps

module comb_adder_tree #(
        parameter N             = 10,
        parameter DATA_WIDTH    = 16,
        parameter STAGES        = $clog2(N),
        parameter POW2_INPUTS   = 2 ** STAGES,
        parameter O_DATA_WIDTH  = DATA_WIDTH + STAGES
    ) (
        input logic     [DATA_WIDTH-1:0]    i_data [N-1:0],
        output logic    [O_DATA_WIDTH:0]  o_data
    );
    
    logic [O_DATA_WIDTH:0] tree_data [0:POW2_INPUTS-1][0:STAGES];
    
    genvar stage, adder;
    generate 
        for(stage = 0; stage <= STAGES; stage++) begin 
            localparam ST_OUT_NUM = POW2_INPUTS >> stage;
            localparam ST_WIDTH = DATA_WIDTH +stage;
            
            
            for(adder = 0; adder < ST_OUT_NUM; adder++) begin
                always_comb begin
                    if (stage == 0) begin
                        if (adder < N) begin
                            tree_data[adder][stage] = '0 + i_data[adder];
                        end else begin
                            tree_data[adder][stage][O_DATA_WIDTH:0] = '0;
                        end
                    end else begin
                        tree_data[adder][stage] = '0 + tree_data[adder*2][stage-1] + tree_data[adder*2+1][stage-1];
                    end // if/else stage == 0
                end // always_comb
            end // for adder
        end // for stage
    endgenerate
    
    assign o_data = tree_data[0][STAGES];
    
endmodule
