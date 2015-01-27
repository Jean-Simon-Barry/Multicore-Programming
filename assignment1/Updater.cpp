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



void Updater::updateMedicine(std::vector<VertexCell> & cellList, std::vector<VertexCell> & medicineCells){
	int neighbourCount = 0;
	for (int i = 1; i < std::sqrt(cellList.size()) - 1; i++){
		for (int j = 1; j < std::sqrt(cellList.size()) - 1; j++){
			if (cellList[(i * std::sqrt(cellList.size())) + j].color == 0){
				for (std::vector<VertexCell>::iterator medicineCell = medicineCells.begin(); medicineCell != medicineCells.end(); medicineCell++){

					if ((std::abs(cellList[(i * std::sqrt(cellList.size())) + j].x - medicineCell->x) <= 1.0f) 
						&& (std::abs(cellList[(i * std::sqrt(cellList.size())) + j].y - medicineCell->y) <= 1.0f)){
						neighbourCount++;
					}
					if (neighbourCount >= 6){
						cellList[(i * std::sqrt(cellList.size())) + j].color = 1;
						cellList[(i * std::sqrt(cellList.size())) + j].r = 0.0f;
						cellList[(i * std::sqrt(cellList.size())) + j].g = 1.0f;
						cellList[(i * std::sqrt(cellList.size())) + j].b = 0.0f;

						cellList[((i * std::sqrt(cellList.size())) + (j - 1))].color = 1; //left
						changeVertexColor(cellList[((i * std::sqrt(cellList.size())) + (j - 1))], 0.0f, 1.0f, 0.0f);

						cellList[(((i - 1) * std::sqrt(cellList.size())) + (j - 1))].color = 1;  //top left
						changeVertexColor(cellList[(((i - 1) * std::sqrt(cellList.size())) + (j - 1))], 0.0f, 1.0f, 0.0f);

						cellList[(((i + 1) * std::sqrt(cellList.size())) + (j - 1))].color = 1; //bottom left
						changeVertexColor(cellList[(((i + 1) * std::sqrt(cellList.size())) + (j - 1))], 0.0f, 1.0f, 0.0f);

						cellList[((i * std::sqrt(cellList.size())) + (j + 1))].color = 1;//right
						changeVertexColor(cellList[((i * std::sqrt(cellList.size())) + (j + 1))], 0.0f, 1.0f, 0.0f);

						cellList[(((i - 1) * std::sqrt(cellList.size())) + (j + 1))].color = 1; //top right
						changeVertexColor(cellList[(((i - 1) * std::sqrt(cellList.size())) + (j + 1))], 0.0f, 1.0f, 0.0f);

						cellList[(((i + 1) * std::sqrt(cellList.size())) + (j + 1))].color = 1; //bottom right
						changeVertexColor(cellList[(((i + 1) * std::sqrt(cellList.size())) + (j + 1))], 0.0f, 1.0f, 0.0f);

						cellList[(((i + 1) * std::sqrt(cellList.size())) + j)].color = 1;//bottom
						changeVertexColor(cellList[(((i + 1) * std::sqrt(cellList.size())) + j)], 0.0f, 1.0f, 0.0f);

						cellList[(((i - 1) * std::sqrt(cellList.size())) + j)].color = 1; //top
						changeVertexColor(cellList[(((i - 1) * std::sqrt(cellList.size())) + j)], 0.0f, 1.0f, 0.0f);

						medicineCells.clear();
						return;
					}

				}
				neighbourCount = 0;
			}
		}
	}
}

void myfunction(VertexCell vc) {  // function:
	if (vc.color == 2){
		vc.color = 1;
		vc.r = 1.0f;
		vc.g = 0.0f;
		vc.b = 0.0f;
	}
}




void Updater::updateCancer(std::vector<VertexCell> & cellList1, int xDimension, int yDimension){
	int neighbourCount = 0;
	//for each healthy cell we find the cancer cells that are within 1 and 
	for (int i = 1; i < xDimension-1; i++){
		for (int j = 1; j < yDimension-1; j++){

			if (cellList1[(i * xDimension) + j].color == 1){

				if (cellList1[((i * xDimension) + (j - 1))].color == 0) //left
					neighbourCount++;
				if (cellList1[(((i - 1) * xDimension) + (j - 1))].color == 0) //top left
					neighbourCount++;
				if (cellList1[(((i + 1) * xDimension) + (j - 1))].color == 0) //bottom left
					neighbourCount++;

				if (cellList1[((i * xDimension) + (j + 1))].color == 0) //right
					neighbourCount++;
				if (cellList1[(((i - 1) * xDimension) + (j + 1))].color == 0) //top right
					neighbourCount++;
				if (cellList1[(((i + 1) * xDimension) + (j + 1))].color == 0) //bottom right
					neighbourCount++;

				if (cellList1[(((i + 1) * xDimension) + j)].color == 0) //bottom
					neighbourCount++;
				if (cellList1[(((i - 1) * xDimension) + j)].color == 0) //top
					neighbourCount++;

				if (neighbourCount >= 6){
					cellList1[(i * xDimension) + j].color = 0;
					cellList1[(i * xDimension) + j].r = 1.0f;
					cellList1[(i * xDimension) + j].g = 0.0f;
					cellList1[(i * xDimension) + j].b = 0.0f;
				}
			}
			neighbourCount = 0; //reset
		}
	}
}
