#include "Updater.h"


Updater::Updater(void)
{
}


Updater::~Updater(void)
{
}


void changeVertexColor(VertexCell &vc, float r, float g, float b){
	vc.r = r;
	vc.g = g;
	vc.b = b;
}

const char * source_str  = "__kernel void checkSurround(__global float *out)"
                           "{"
                           
                           /* Get the 2D X and Y indices */
                           "    int index_x = get_global_id(0);"
                           "    int index_y = get_global_id(1);"
 
                           /* Map the two 2D indices to a single linear, 1D index */
                           "    int grid_width = get_num_groups(0) * get_local_size(0);"
                           "    int index = index_y * grid_width + index_x;"
 
                           /* Map the two 2D group indices to a single linear, 1D group index */
                           "    float result = get_group_id(1) * get_num_groups(0) + get_group_id(0);"
 
                           /* Write out the result */
						   "if(index % 5 == 2){"
							"   out[index] == 1.0f;"
						   "}"
						   "    out[index] = result;";
						  
    

void printArray(int *host_array, int num_elements){
    size_t i;
    for (i = 0; i < num_elements; ++i)
    {
        printf("%3d ", host_array[i]);
        if (i % 50 == 49)
            printf("\n");
    }
    printf("\n");
}

void Updater::test(float * cellList){

	for(int i=0; i<200000; i+=5){
		cellList[i+2] = 0.0f;
		cellList[i+3] = 0.0f;
		cellList[i+4] = 0.0f;
	}


	for(int i=0; i<200000; i+=5){
		cellList[i+2] = 1.0f;
	}

}

void Updater::updateCancer(float * cellList, int size, int xDimension, int yDimension){
	
	cl_platform_id platform_id = NULL;
    cl_device_id device_id = NULL;   
    cl_uint num_devices;
    cl_uint num_platforms;
    cl_int ret = clGetPlatformIDs(1, &platform_id, &num_platforms);
    ret = clGetDeviceIDs( platform_id, CL_DEVICE_TYPE_GPU, 1, &device_id, &num_devices);

	//float results[200*200*5];
  
    /* Create an OpenCL context */
    cl_context context = clCreateContext( NULL, 1, &device_id, NULL, NULL, &ret);
 
    /* Create a command queue */
    cl_command_queue command_queue = clCreateCommandQueue(context, device_id, 0, &ret);
 
    /* Allocate host array. Note that the elements are zeroed. */
    float * results = (float*)calloc(NUM_ELEMENTS * 5, sizeof(*results));
 
 
    /* Create device memory buffer */
    cl_mem dev_mem_obj = clCreateBuffer(context, CL_MEM_WRITE_ONLY,
                                      NUM_ELEMENTS * sizeof(&cellList), NULL, &ret);

	cl_mem dev_mem_obj = clCreateBuffer(context, CL_MEM_READ_WRITE, NUM_ELEMENTS * sizeof(*results) * 5, NULL, &ret);
    cl_mem input = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * NUM_ELEMENTS * 5, NULL, &ret);
 
    /* Create a program from the kernel source */
    cl_program program = clCreateProgramWithSource(context, 1, &source_str, NULL, &ret);
  
    /* Build the program */
    ret = clBuildProgram(program, 1, &device_id, NULL, NULL, NULL);
  
    /* Create the OpenCL kernel */
    cl_kernel kernel = clCreateKernel(program, "checkSurround", &ret);
	
	cl_mem dev_array_buffer = clCreateBuffer(context, CL_MEM_READ_WRITE, NUM_ELEMENTS * sizeof(*cellList), cellList, &ret);

	ret = clEnqueueWriteBuffer(command_queue, input, CL_TRUE, 0, NUM_ELEMENTS * sizeof(*cellList) * 5, cellList, 0, NULL, NULL );

	ret = clEnqueueWriteBuffer(command_queue, dev_mem_obj, CL_TRUE, 0, sizeof(float) * NUM_ELEMENTS, (void*)&cellList, 0, NULL, NULL);
 
    /* Set the kernel argument */
    ret = clSetKernelArg(kernel, 0, sizeof(cl_mem), &dev_mem_obj);
 
    /* Execute the OpenCL kernel */
    size_t global_item_size[2] = { NUM_ELEMENTS_X, NUM_ELEMENTS_Y};
    size_t local_item_size[2] = {32, 32};
    ret = clEnqueueNDRangeKernel(command_queue, kernel, 2, NULL, 
            global_item_size, local_item_size, 0, NULL, NULL);
 
    /* Read the results from the device memory buffer back into host array */
    ret = clEnqueueReadBuffer(command_queue, dev_mem_obj, CL_TRUE, 0,
                              NUM_ELEMENTS * sizeof(&results), results, 0, NULL, NULL);
 
    ret = clFlush(command_queue);
    ret = clFinish(command_queue);
 
    if (ret != CL_SUCCESS) {
        printf("OpenCL error executing kernel: %d\n", ret);
        goto cleanup;
    }

	memcpy(cellList, results, NUM_ELEMENTS * sizeof(&results) * 5);
	cleanup:
    /* Clean up */
    ret = clReleaseKernel(kernel);
    ret = clReleaseProgram(program);
    ret = clReleaseMemObject(dev_mem_obj);
	//ret = clReleaseMemObject(input);
    ret = clReleaseCommandQueue(command_queue);
    ret = clReleaseContext(context);
    

}