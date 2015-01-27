#include "Updater.h"


Updater::Updater(void)
{
}


Updater::~Updater(void)
{
}

__global__ void addKernel(std::vector<VertexCell> & cellList1, int xDimension)
{
	int neighbourCount = 0;
	//32 x 16 blocks
	// 24 x 48 grid of 32x16 blocks = 768 x 768
	/*int i = blockIdx.y * blockDim.y + threadIdx.y;
	int j = blockIdx.x * blockDim.x + threadIdx.x;
	if (cellList1[(i * xDimension) + j].color == 1){

					if (cellList1[((i * xDimension) + (j - 1))].color == 0){ //left						
						neighbourCount++;						
					}
					if (cellList1[(((i - 1) * xDimension) + (j - 1))].color == 0){ //top left						
						neighbourCount++;					
					}
					if (cellList1[(((i + 1) * xDimension) + (j - 1))].color == 0){ //bottom left					
						neighbourCount++;						
					}
					if (cellList1[((i * xDimension) + (j + 1))].color == 0){ //right						
						neighbourCount++;						
					}
					if (cellList1[(((i - 1) * xDimension) + (j + 1))].color == 0){ //top right						
						neighbourCount++;						
					}
					if (cellList1[(((i + 1) * xDimension) + (j + 1))].color == 0){ //bottom right						
						neighbourCount++;						
					}
					if (cellList1[(((i + 1) * xDimension) + j)].color == 0){ //bottom						
						neighbourCount++;						
					}
					if (cellList1[(((i - 1) * xDimension) + j)].color == 0){ //top						
						neighbourCount++;						
					}
					if (neighbourCount >= 6){						
						cellList1[(i * xDimension) + j].color = 0;
						cellList1[(i * xDimension) + j].r = 1.0f;
						cellList1[(i * xDimension) + j].g = 0.0f;
						cellList1[(i * xDimension) + j].b = 0.0f;
					}
				}else if (cellList1[(i * xDimension) + j].color == 0){

					if (cellList1[((i * xDimension) + (j - 1))].color == 2){ //left						
						neighbourCount++;						
					}
					if (cellList1[(((i - 1) * xDimension) + (j - 1))].color == 2){ //top left						
						neighbourCount++;					
					}
					if (cellList1[(((i + 1) * xDimension) + (j - 1))].color == 2){ //bottom left					
						neighbourCount++;						
					}
					if (cellList1[((i * xDimension) + (j + 1))].color == 2){ //right						
						neighbourCount++;						
					}
					if (cellList1[(((i - 1) * xDimension) + (j + 1))].color == 2){ //top right						
						neighbourCount++;						
					}
					if (cellList1[(((i + 1) * xDimension) + (j + 1))].color == 2){ //bottom right						
						neighbourCount++;						
					}
					if (cellList1[(((i + 1) * xDimension) + j)].color == 2){ //bottom						
						neighbourCount++;						
					}
					if (cellList1[(((i - 1) * xDimension) + j)].color == 2){ //top						
						neighbourCount++;						
					}
					if (neighbourCount >= 6){						
						cellList1[(i * xDimension) + j].color = 1;
						cellList1[(i * xDimension) + j].r = 0.0f;
						cellList1[(i * xDimension) + j].g = 1.0f;
						cellList1[(i * xDimension) + j].b = 0.0f;
					}
				}			
				neighbourCount = 0;		
			*/
}

void changeVertexColor(VertexCell &vc, float r, float g, float b){
	vc.r = r;
	vc.g = g;
	vc.b = b;
}

/*struct updateCancerStruct {

	std::vector<VertexCell> &cellList1;
	int xDimension;
	int yDimension;
	mutable int neighbourCount;

	void operator()(const tbb::blocked_range2d<size_t>& r) const  {
			
		for (size_t i = r.rows().begin(); i != r.rows().end(); ++i){
			for (size_t j = r.cols().begin(); j != r.cols().end(); ++j) {
				if (cellList1[(i * xDimension) + j].color == 1){

					if (cellList1[((i * xDimension) + (j - 1))].color == 0){ //left						
						neighbourCount++;						
					}
					if (cellList1[(((i - 1) * xDimension) + (j - 1))].color == 0){ //top left						
						neighbourCount++;					
					}
					if (cellList1[(((i + 1) * xDimension) + (j - 1))].color == 0){ //bottom left					
						neighbourCount++;						
					}
					if (cellList1[((i * xDimension) + (j + 1))].color == 0){ //right						
						neighbourCount++;						
					}
					if (cellList1[(((i - 1) * xDimension) + (j + 1))].color == 0){ //top right						
						neighbourCount++;						
					}
					if (cellList1[(((i + 1) * xDimension) + (j + 1))].color == 0){ //bottom right						
						neighbourCount++;						
					}
					if (cellList1[(((i + 1) * xDimension) + j)].color == 0){ //bottom						
						neighbourCount++;						
					}
					if (cellList1[(((i - 1) * xDimension) + j)].color == 0){ //top						
						neighbourCount++;						
					}
					if (neighbourCount >= 6){						
						cellList1[(i * xDimension) + j].color = 0;
						cellList1[(i * xDimension) + j].r = 1.0f;
						cellList1[(i * xDimension) + j].g = 0.0f;
						cellList1[(i * xDimension) + j].b = 0.0f;
					}
				}else if (cellList1[(i * xDimension) + j].color == 0){

					if (cellList1[((i * xDimension) + (j - 1))].color == 2){ //left						
						neighbourCount++;						
					}
					if (cellList1[(((i - 1) * xDimension) + (j - 1))].color == 2){ //top left						
						neighbourCount++;					
					}
					if (cellList1[(((i + 1) * xDimension) + (j - 1))].color == 2){ //bottom left					
						neighbourCount++;						
					}
					if (cellList1[((i * xDimension) + (j + 1))].color == 2){ //right						
						neighbourCount++;						
					}
					if (cellList1[(((i - 1) * xDimension) + (j + 1))].color == 2){ //top right						
						neighbourCount++;						
					}
					if (cellList1[(((i + 1) * xDimension) + (j + 1))].color == 2){ //bottom right						
						neighbourCount++;						
					}
					if (cellList1[(((i + 1) * xDimension) + j)].color == 2){ //bottom						
						neighbourCount++;						
					}
					if (cellList1[(((i - 1) * xDimension) + j)].color == 2){ //top						
						neighbourCount++;						
					}
					if (neighbourCount >= 6){						
						cellList1[(i * xDimension) + j].color = 1;
						cellList1[(i * xDimension) + j].r = 0.0f;
						cellList1[(i * xDimension) + j].g = 1.0f;
						cellList1[(i * xDimension) + j].b = 0.0f;
					}
				}			
				neighbourCount = 0;		
			}		
		}
	}
	updateCancerStruct(std::vector<VertexCell> & cellList, int xDim, int yDim) : cellList1(cellList), xDimension(xDim), yDimension(yDim) {}
};*/

void Updater::updateCancer(std::vector<VertexCell> & cellList1, int xDimension, int yDimension, int size){
	
	/*tbb::parallel_for(tbb::blocked_range2d<size_t>(1, (xDimension-1), 1000, 1, (yDimension-1), 1000),
		updateCancerStruct(cellList1, xDimension, yDimension));*/
	int N = 10;
	int *dev_data = 0;
	cudaError_t cudaStatus;

	cudaStatus = cudaMalloc((void**)&dev_data, cellList1.size() * sizeof(VertexCell));
	if (cudaStatus != cudaSuccess) { 
		fprintf(stderr, "cudaMalloc failed!");
		exit(1);
	}

	cudaStatus = cudaMemcpy(dev_data, &cellList1[0], size * sizeof(VertexCell), cudaMemcpyHostToDevice);
	if (cudaStatus != cudaSuccess) {
	 fprintf(stderr, "cudaMemcpy failed!");
	 exit(1);
	}

	addKernel<<<N, size>>>(cellList1, 768);

}