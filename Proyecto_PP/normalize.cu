#include <cuda_runtime.h>
__global__ void normalize(float* x, float minv, float maxv, int n){
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  if(i < n){
    float v = x[i];
    x[i] = (v - minv) / (maxv - minv + 1e-8f);
  }
}
extern "C" void normalize_cuda(float* d_x, float minv, float maxv, int n){
  int blk = 256;
  int grid = (n + blk - 1) / blk;
  normalize<<<grid, blk>>>(d_x, minv, maxv, n);
  cudaDeviceSynchronize();
}
