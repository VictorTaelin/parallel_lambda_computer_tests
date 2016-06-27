#include <stdio.h>
#include "test_inputs.cu"
#include "rewriter.cu"
#include "now.cu"

const int ints_per_node = 4;

const int threads_per_block = 32;
const int nodes_per_thread = 32;
const int thread_ticks = 1;
const int block_ticks = 16;
const int kernel_calls = 1300;

const int ints_per_thread = nodes_per_thread * ints_per_node;
const int nodes_per_block = nodes_per_thread * threads_per_block;
const int ints_per_block = nodes_per_block * ints_per_node;

__global__ void process(int *mem, int phase){
    __shared__ int smem[ints_per_block];

    int thread_global_num = blockIdx.x*blockDim.x + threadIdx.x;
    int thread_local_num = threadIdx.x;

    // Reads from global to local memory
    int offset = phase ? ints_per_block/2 : 0;
    int smem_idx = thread_local_num * ints_per_thread;
    int mem_idx = thread_global_num * ints_per_thread + offset;

    // printf("KERNEL ph:%d | local = %d/%d, global = %d | mem from %d til %d, smem from %d til %d, smem_size = %d\n", 
        // phase,
        // thread_local_num, 
        // blockDim.x, 
        // thread_global_num,
        // mem_idx,
        // mem_idx+ints_per_thread,
        // smem_idx,
        // smem_idx+ints_per_thread,
        // ints_per_block);

    for (int i=0; i<ints_per_thread; ++i){
        // printf("%d + %d = %d\n", mem_idx, i, mem_idx+i);
        smem[smem_idx+i] = mem_idx+i < memory_ints ? mem[mem_idx+i] : 0;
    }
    __syncthreads();

    // Calls the kernel
    for (int u = 0, ph = 0; u < block_ticks; ++u, ph = !ph){
        int local_offset = ph ? ints_per_thread/2 : 0;
        // int local_offset = 0;
        for (int t = 0; t<thread_ticks; ++t){ // Many ticks on thread's space
            if (ph == 0 || threadIdx.x < blockDim.x-1) {
                // printf("TICK %d %d | mem from %d til %d, smem from %d til %d\n", 
                    // t,
                    // u,
                    // mem_idx+local_offset,
                    // mem_idx+local_offset+ints_per_thread,
                    // smem_idx+local_offset,
                    // smem_idx+local_offset+ints_per_thread);
                tick(smem + smem_idx + local_offset, nodes_per_thread);
            };
            __syncthreads();
        };
    };

    // Writes to global mamory
    for (int i=0; i<ints_per_thread; ++i)
        if (mem_idx+i < memory_ints)
            mem[mem_idx+i] = smem[smem_idx+i];
};

int main(){

    for (int i=0; i < memory_ints; ++i)
        memory[i] = i < program_nodes*4 ? program[i] : 0;

    int *device_memory;
    cudaMalloc((void**)&device_memory, sizeof memory);
    cudaMemcpy(device_memory, memory, memory_size, cudaMemcpyHostToDevice);

    dim3 block_size(threads_per_block, 1);
    dim3 grid_size_0(memory_nodes / nodes_per_block + 1, 1);
    dim3 grid_size_1(memory_nodes / nodes_per_block, 1);
    printf("%d %d \n", block_size.x, grid_size_0.x);

    print(memory, 40);

    double t = now();
    for (int k=0; k<kernel_calls; ++k){
        process<<<grid_size_0, block_size>>>(device_memory, 0);
        process<<<grid_size_1, block_size>>>(device_memory, 1);

        // cudaMemcpy(memory, device_memory, memory_size, cudaMemcpyDeviceToHost);
        // print(memory, memory_nodes);
    };
    printf("%f\n", now()-t);

    cudaMemcpy(memory, device_memory, memory_size, cudaMemcpyDeviceToHost);
    print(memory, 40);
    cudaFree(device_memory);
}
