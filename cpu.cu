#include <stdio.h>
#include "test_inputs.cu"
#include "rewriter.cu"

void process(int *mem, int len, int j){
    for (int i=j; i<len-2; i+=3)
        rewrite(mem+i*4, mem+i*4+4, mem+i*4+8);
};

int main(){
    for (int i=0; i < memory_ints; ++i)
        memory[i] = i < program_nodes*4 ? program[i] : 0;

    print(memory, 40);

    for (int k=0; k<clocks*3; ++k)
        for (int j=0; j<3; ++j)
            process(memory, memory_nodes, j);

    print(memory, 40);
}
