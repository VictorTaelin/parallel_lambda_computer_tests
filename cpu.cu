#include <stdio.h>
#include "test_inputs.cu"
#include "rewriter.cu"
#include "now.cu"

int main(){

    // Loads initial input
    for (int i=0; i < memory_ints; ++i)
        memory[i] = i < program_nodes*4 ? program[i] : 0;

    // Prints it for visualization
    print(memory, 40);

    double t = now();

    // Calls rewrite sequentially until the computation is done
    for (int k=0; k<clocks; ++k){
        tick(memory, memory_nodes);
        // print(memory, memory_nodes);
    }

    // Print the result (should have only 4 numbers)
    print(memory, 40);

    printf("%f\n", now()-t);
}
