
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "hls_config.h"

constexpr float REL_TOL = 2.0f;
constexpr int TRIALS = 10;


int main() {
    std::cout << "Running C++ simulation!" << std::endl;

    int testResult = 0;
    std::ifstream idata("golden_Inputs.dat");
	std::ifstream rdata("golden_Reference.dat");

    if (!rdata.is_open()) {
        std::cerr << "Error reading golden_Reference file!" << std::endl;
        return 1;
    }

	if (!idata.is_open()) {
        std::cerr << "Error reading golden_Inputs file!" << std::endl;
        return 1;
    }

    int output;
    int input[N];

    float buffer;
    float pp_rel_err = 0.0f;

    for (int i = 0; i < TRIALS; ++i) {
        float temp = 0.0f;

        // Read vector input
        for (int j = 0; j < N; ++j) {
            idata >> temp;
            input[j] = static_cast<uint32_t>(temp);
        }

        // Read reference output
        rdata >> temp;
        buffer = temp;

     
       
        // Call HLS function
        hls_pp(&output, x, y);

        pp_rel_err = 100.0f * std::fabs((output - buffer) / buffer);

        std::cout << "TRIAL: " << i
                  << ",\t Expected: " << buffer
                  << "\tGot: " << output
                  << " Err: " << pp_rel_err << "%\n";

        if (pp_rel_err > REL_TOL) {
            std::cout << "PP error exceeds tolerance!" << std::endl;
            ++testResult;
        }
    }

    rdata.close();
	idata.close();

    std::cout << "*******************************************\n";
    if (testResult) {
        std::cout << "*\t \t  FAIL \n";
    } else {
        std::cout << "*\t \t  PASS \n";
    }
    std::cout << "*******************************************\n";

    return testResult;
}
