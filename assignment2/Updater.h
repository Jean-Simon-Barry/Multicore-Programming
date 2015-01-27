#pragma once
#include <thread>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include "cuda_runtime.h"
#include "device_launch_parameters.h"
#include <cuda.h>
#include "Renderer.h"





class Updater
{
public:
	Updater(void);
	~Updater(void);

	static void updateCancer(std::vector<VertexCell> & cellList1, int xDimension, int yDimension, int size);
	
};






