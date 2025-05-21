//
//  main.c
//  red1
//
//  Created by toby on 12.06.24.
//


#include <stdio.h>
#include <math.h>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/cl.h>
#endif


#include "ocl.h"


//reduction by fold 1D limited to 1024^3
int main(int argc, const char * argv[])
{
    printf("hello\n");
    
    //ocl
    struct ocl_obj ocl;
    ocl_init(&ocl);
    
    //size
    cl_int n = pow(1024,3);
    
    //buf
    cl_mem uu = clCreateBuffer(ocl.context, CL_MEM_HOST_READ_ONLY, n*sizeof(float), NULL, &ocl.err);
    
    //kernels
    cl_kernel vec_ini = clCreateKernel(ocl.program, "vec_ini", &ocl.err);
    cl_kernel vec_sum = clCreateKernel(ocl.program, "vec_sum", &ocl.err);
    
    //args
    ocl.err = clSetKernelArg(vec_ini, 0, sizeof(cl_mem), (void*)&uu);
    
    ocl.err = clSetKernelArg(vec_sum, 0, sizeof(cl_mem), (void*)&uu);
    ocl.err = clSetKernelArg(vec_sum, 1, sizeof(cl_int), (void*)&n);
    
    //init
    ocl.err = clEnqueueNDRangeKernel(ocl.command_queue, vec_ini, 1, NULL, (size_t*)&n, NULL, 0, NULL, NULL);
    
    uint l = ceil(log2(n));
    
    //loop
    for(int i=0; i<l; i++)
    {
        size_t p = pow(2,l-i-1);
        
        printf("%2d %2d %u %zu\n", i, l, n, p);
    
        //calc
        ocl.err = clEnqueueNDRangeKernel(ocl.command_queue, vec_sum, 1, NULL, &p, NULL, 0, NULL, NULL);
    }
    
    
    //result
    float r;
    
    //read
    ocl.err = clEnqueueReadBuffer(ocl.command_queue, uu, CL_TRUE, 0, sizeof(float), &r, 0, NULL, NULL);

    //disp
    printf("ana %f %f\n", (float)n, r);


    /*
     ===========
     clean
     ===========
     */
    
    //free
    ocl.err = clReleaseMemObject(uu);
    
    //kernels
    ocl.err = clReleaseKernel(vec_ini);
    ocl.err = clReleaseKernel(vec_sum);

    //clean
    ocl_final(&ocl);
    
    printf("done\n");
    
    return 0;
}


