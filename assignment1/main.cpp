#pragma once
#include <stdlib.h>
#include <Renderer.h>
#include <Updater.h>
#include <thread>
#include <vector>
#include <glut.h>
#include <algorithm>




std::vector<VertexCell> cellsQuad1 = std::vector<VertexCell>();


//MEDICINE CELLS. Since these are spawned dynamically, and there won't be that many of them, we use 1 vector.
std::vector<VertexCell> medicineCells = std::vector<VertexCell>();


//std::vector<VertexCell> &testVertexCells = std::vector<VertexCell>();

int xDimesnsion=900, yDimension = 900;
int medicineQuantity = 0;
bool medFlag;
static float mouseX;
static float mouseY;
static bool zoomToggle;
float zoomValue = 2.0f;

//renderer runs on the main thread and does all the openGL rendering
Renderer *renderer;

//updater takes care of all the computation. Will utilize multi-threads based on the division of the data as above
Updater *updater;


void display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, MAX_WIDTH, MAX_HEIGHT+200, 0);

	//for testing purps
	//glPointSize(2);

	if(zoomToggle){		
		glScaled(0.5*zoomValue, 0.5*zoomValue, 0);
	}
	

	//display the number of healthy cells, cancer cells, medicine cells at the bottom of the screen
	renderer->displayCellNumbers(std::count_if(cellsQuad1.begin(),cellsQuad1.end(), count_healthy()), std::count_if(cellsQuad1.begin(),cellsQuad1.end(), count_cancer()),
		medicineCells.size());
	
	renderer->drawPositionListVertex(cellsQuad1);
	//renderer->drawPositionListVertex(cancerCells);
	renderer->drawPositionListVertex(medicineCells);
	
	glutSwapBuffers();
}

void menuHandler(int option){
	switch(option){
	//inject medicine key
	case 0:
		std::cout<<"Enter the amount of medicine you wish to dispense (in pixels)"<<std::endl;
		std::cin >> medicineQuantity;
		std::cout<<"Now click mouse on screen to deliver to the position you want"<<std::endl;
		medFlag = true;
		break;
	//zoom in
	case 1:
		zoomValue++;
		zoomToggle = true;
		std::cout << "zooming in \n" << std::endl;
		break;
	case 2:
		zoomValue=2.0f;
		zoomToggle = false;
		std::cout << "zooming out \n" << std::endl;
		break;
	}
}

void myKeyboardFunc(unsigned char Key, int x, int y)
{
	switch(Key){
	case 'm': 
		menuHandler(0); 
		break;
	case 'z':
		menuHandler(1);
		break;	
	case 'x':
		menuHandler(2);
		break;	
	case 27: 
	exit(1); 
	break;
	};
}

void MyMouseFunc(int button, int state, int x, int y)
{
	switch(button)
	{
		case GLUT_LEFT_BUTTON:
		if (state==GLUT_DOWN) // LEFT-BUTTON DOWN
		{
			if(medFlag){
				VertexCell *vc;
				//updater->checkMedAndCancerMultiThread(cancervector1, cancervector2, cancervector3, cancervector4, xpos, ypos);
				for(int i=0; i<medicineQuantity; i++){
					
					vc = new VertexCell();
					vc->x = mouseX-1;
					vc->y = mouseY+1;
					vc->r = 1.0f;
					vc->g = 1.0f;
					vc->b = 0.0f;
					vc->color = 2;
					medicineCells.push_back(*vc);

					vc = new VertexCell();
					vc->x = mouseX;
					vc->y = mouseY+1;
					vc->r = 1.0f;
					vc->g = 1.0f;
					vc->b = 0.0f;
					vc->color = 2;
					medicineCells.push_back(*vc);

					vc = new VertexCell();
					vc->x = mouseX+1;
					vc->y = mouseY+1;
					vc->r = 1.0f;
					vc->g = 1.0f;
					vc->b = 0.0f;
					vc->color = 2;
					medicineCells.push_back(*vc);

					vc = new VertexCell();
					vc->x = mouseX+1;
					vc->y = mouseY;
					vc->r = 1.0f;
					vc->g = 1.0f;
					vc->b = 0.0f;
					vc->color = 2;
					medicineCells.push_back(*vc);

					vc = new VertexCell();
					vc->x = mouseX+1;
					vc->y = mouseY-1;
					vc->r = 1.0f;
					vc->g = 1.0f;
					vc->b = 0.0f;
					vc->color = 2;
					medicineCells.push_back(*vc);

					vc = new VertexCell();
					vc->x = mouseX;
					vc->y = mouseY-1;
					vc->r = 1.0f;
					vc->g = 1.0f;
					vc->b = 0.0f;
					vc->color = 2;
					medicineCells.push_back(*vc);

					vc = new VertexCell();
					vc->x = mouseX-1;
					vc->y = mouseY-1;
					vc->r = 1.0f;
					vc->g = 1.0f;
					vc->b = 0.0f;
					vc->color = 2;
					medicineCells.push_back(*vc);

					vc = new VertexCell();
					vc->x = mouseX-1;
					vc->y = mouseY;
					vc->r = 1.0f;
					vc->g = 1.0f;
					vc->b = 0.0f;
					vc->color = 2;
					medicineCells.push_back(*vc);			
				}
			}
			medFlag = false;
			glutDetachMenu(GLUT_RIGHT_BUTTON);
		}
		else // LEFT-BUTTON UP
		{
			//glutAttachMenu(GLUT_RIGHT_BUTTON);
		}
		break;
		case GLUT_RIGHT_BUTTON:
		break;
	};
}

void getMouseCoord(int x, int y)
{
	if(!zoomToggle){
		mouseX = x;
		mouseY = y;
	}
	else{
		mouseX = x / (0.5*zoomValue);
		mouseY = x / (0.5*zoomValue);
	}
}


void timer(int value)
{
	updater->updateCancer(cellsQuad1, (int)std::sqrt(cellsQuad1.size()), (int)std::sqrt(cellsQuad1.size()));
	updater->updateMedicine(cellsQuad1, medicineCells);
	glutPostRedisplay();
	glutTimerFunc(33.33,timer,0);
}

void populateCellVectorRandom(int nbOfCells, std::vector<VertexCell> &cellList, float r, float g, float b, int minX, int maxX, int minY, int maxY){

	VertexCell *vc;
	for(int i=0; i<nbOfCells; i++){
		
		vc = new VertexCell();
		vc->x = minX + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxX-minX)));
		vc->y = minY + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(maxY-minY)));
		vc->r = r;
		vc->g = g;
		vc->b = b;

		cellList.push_back(*vc);
	}
}


void populateCellVectorFullScreen(std::vector<VertexCell> &cellList, int maxX, int maxY){

	VertexCell *vc;
	for(float i=0; i<maxX; i++){
		for(float j=0; j<maxY; j++){
			vc = new VertexCell();
			double probability = (rand() / (double)(RAND_MAX + 1));
			if (probability > 0.05){
				vc->x = i;
				vc->y = j;
				vc->r = 0.0f;
				vc->g = 1.0f;
				vc->b = 0.0f;
				vc->color = 1;//green
			}
			else{
				vc->x = i;
				vc->y = j;
				vc->r = 1.0f;
				vc->g = 0.0f;
				vc->b = 0.0f;
				vc->color = 0;//red

			}

			cellList.push_back(*vc);
		}
	}
}

int main(int argc, char **argv)
{
	/*
	ITINITIALING DATASTRUCTURES
	*/
	renderer = new Renderer();
	updater = new Updater();
	srand ( time(0) );
	std::cout<< "Cancer vs Health. FIGHT!"<<std::endl;


	populateCellVectorFullScreen(cellsQuad1, xDimesnsion, yDimension);

	//sort on the y position
	std::stable_sort(cellsQuad1.begin(), cellsQuad1.end(), sort_on_y());


	/*
		INIT OPENGL AND LOOP
	*/
	glutInit(&argc, argv);
	//use double buffer
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize(MAX_WIDTH,MAX_HEIGHT+200);
	glutCreateWindow("Cancer vs Health. FIGHT!");
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboardFunc);
	glutMouseFunc(MyMouseFunc);
	glutPassiveMotionFunc(getMouseCoord);
	timer(0);
	glewInit();
	glutMainLoop();

	delete[] updater;
	delete[] renderer;
	delete[] &cellsQuad1;
	

	//delete[] &cancerCells;
	


	return 0;
}