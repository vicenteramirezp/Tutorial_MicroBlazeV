`timescale 1ns / 1ps

module seq_adder_tree #(
    parameter int N            = 10,
    parameter int DATA_WIDTH   = 16,
    parameter int STAGES       = $clog2(N),
    parameter int POW2_INPUTS  = 2 ** STAGES,
    parameter int O_DATA_WIDTH = DATA_WIDTH + STAGES
) (
    input  logic                    clk,
    input  logic                    reset,
    input  logic [DATA_WIDTH-1:0]   i_data [N-1:0],
    output logic [O_DATA_WIDTH-1:0] o_data
);

    logic [O_DATA_WIDTH-1:0] tree_data [0:STAGES][0:POW2_INPUTS-1];

    genvar stage, adder;
    generate
        for (adder = 0; adder < POW2_INPUTS; adder++) begin : g_stage0
            always_ff @(posedge clk) begin
                if (reset)
                    tree_data[0][adder] <= '0;
                else if (adder < N)
                    tree_data[0][adder] <= O_DATA_WIDTH'(i_data[adder]);
                else
                    tree_data[0][adder] <= '0;
            end
        end

        for (stage = 1; stage <= STAGES; stage++) begin : g_stage
            for (adder = 0; adder < (POW2_INPUTS >> stage); adder++) begin : g_adder
                always_ff @(posedge clk) begin
                    tree_data[stage][adder] <= tree_data[stage-1][2*adder]
                                             + tree_data[stage-1][2*adder+1];
                end
            end
        end
    endgenerate

    always_ff @(posedge clk) begin
        if (reset) o_data <= '0;
        else       o_data <= tree_data[STAGES][0];
    end

endmodule