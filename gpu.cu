#include <stdio.h>
#include "test_inputs.cu"
#include "rewriter.cu"

__global__ void process(int *mem, int len, int j){
    int i = (blockIdx.x*blockDim.x + threadIdx.x)*3 + j;
    if (i >= len-2) return;
    rewrite(mem+i*4, mem+i*4+4, mem+i*4+8);
};

int main(){
    for (int i=0; i < memory_ints; ++i)
        memory[i] = i < program_nodes*4 ? program[i] : 0;

    int *device_memory;
    cudaMalloc((void**)&device_memory, sizeof memory);
    cudaMemcpy(device_memory, memory, memory_size, cudaMemcpyHostToDevice);

    dim3 block_size(16, 1);
    dim3 grid_size(memory_nodes / block_size.x / 3, 1);

    print(memory, 40);
    for (int k=0; k<clocks; ++k)
        for (int j=0; j<3; ++j)
            process<<<block_size, grid_size>>>(device_memory, memory_nodes, j);

    cudaMemcpy(memory, device_memory, memory_size, cudaMemcpyDeviceToHost);
    cudaFree(device_memory);

    print(memory, 40);
}
