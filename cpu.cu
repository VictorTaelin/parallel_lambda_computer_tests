#include <stdio.h>
#include "test_inputs.cu"
#include "rewriter.cu"

void process(int *mem, int len, int j){
    for (int i=j; i<len-2; i+=3)
        rewrite(mem+i*4, mem+i*4+4, mem+i*4+8);
};

int main(){
    // Loads initial input
    for (int i=0; i < memory_ints; ++i)
        memory[i] = i < program_nodes*4 ? program[i] : 0;

    // Prints it for visualization
    print(memory, 40);

    // Calls rewrite sequentially until the computation is done
    for (int k=0; k<clocks; ++k)
        for (int j=0; j<3; ++j) // for alternating alignments
            process(memory, memory_nodes, j);

    // Print the result (should have only 4 numbers)
    print(memory, 40);
}
