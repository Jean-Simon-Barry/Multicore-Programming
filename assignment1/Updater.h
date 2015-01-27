#pragma once
#include <thread>
#include <Renderer.h>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <vector>

class Updater
{
public:
	Updater(void);
	~Updater(void);
	static void updateMedicine(std::vector<VertexCell> & cellList, std::vector<VertexCell> & medicineCells);
	static void updateCancer(std::vector<VertexCell> & cellList1, int xDimension, int yDimension);
};






