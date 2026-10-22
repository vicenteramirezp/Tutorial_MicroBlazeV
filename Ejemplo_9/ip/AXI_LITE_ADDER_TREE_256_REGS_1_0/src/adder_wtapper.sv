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
        input logic clk,
        input logic reset,
        input logic     [N*DATA_WIDTH-1:0]    i_data_flat,
        output logic    [O_DATA_WIDTH:0]  o_data
    );

    logic [DATA_WIDTH-1:0] i_data [0:N-1];

    genvar i;
    generate
        for (i = 0; i < N; i++) begin : unpack_inputs
            assign i_data[i] = i_data_flat[i*DATA_WIDTH +: DATA_WIDTH];
        end
    endgenerate
    
    // comb_adder_tree # (
    // .N(N),
    // .DATA_WIDTH(DATA_WIDTH)
    // )
    // comb_adder_tree_inst (
    //     .i_data(i_data),
    //     .o_data(o_data)
    // );
    seq_adder_tree # (
        .N(N),
        .DATA_WIDTH(DATA_WIDTH),
        .STAGES(STAGES),
        .POW2_INPUTS(POW2_INPUTS),
        .O_DATA_WIDTH(O_DATA_WIDTH)
    )
    seq_adder_tree_inst (
        .clk(clk),
        .reset(!reset),
        .i_data(i_data),
        .o_data(o_data)
    );
endmodule