#pragma once
#include <thread>
#include "Renderer.h"
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>
#include <CL\cl.h>

#define NUM_ELEMENTS_X 768
#define NUM_ELEMENTS_Y 768
#define NUM_ELEMENTS (NUM_ELEMENTS_X*NUM_ELEMENTS_Y)




class Updater
{
public:
	Updater(void);
	~Updater(void);

	void updateCancer(float * cellList, int size, int xDimension, int yDimension);
	void Updater::test(float * cellList);
	
};






