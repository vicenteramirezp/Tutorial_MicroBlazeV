`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 03/09/2026 08:50:37 AM
// Design Name: 
// Module Name: adder_tree_wrapper
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module adder_tree_wrapper #(
        parameter N             = 8,
        parameter DATA_WIDTH    = 16,
        parameter STAGES        = $clog2(N),
        parameter POW2_INPUTS   = 2 ** STAGES,
        parameter O_DATA_WIDTH  = DATA_WIDTH + STAGES
    ) (
        input logic     [127:0]    i_data_flat ,
        output logic    [O_DATA_WIDTH:0]  o_data
    );

    logic [15:0] i_data [0:7];

    genvar i;
    generate
        for (i = 0; i < N; i++) begin : unpack_inputs
            assign i_data[i] = i_data_flat[i*DATA_WIDTH +: DATA_WIDTH];
        end
    endgenerate
    
    comb_adder_tree # (
    .N(N),
    .DATA_WIDTH(DATA_WIDTH)
  )
  comb_adder_tree_inst (
    .i_data(i_data),
    .o_data(o_data)
  );
endmodule
