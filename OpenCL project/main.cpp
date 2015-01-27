#pragma once
#include <stdlib.h>
#include "Renderer.h"
#include "Updater.h"
#include <thread>
#include <vector>
#include <glut.h>
#include <algorithm>
#include <math.h>

double round(double d)
{
  return floor(d + 0.5);
}
void changeColor(VertexCell &vc, int colorIN, float rIN, float gIN, float bIN){

	vc.color = colorIN;
	vc.r  = rIN;
	vc.g = gIN;
	vc.b = bIN;
}
GLfloat cellGrid[2949120];

const int xDimension = 768;
const int yDimension = 768;
int medicineQuantity = 0;
bool medFlag;
static float mouseX;
static float mouseY;
static bool zoomToggle = false;
float zoomValue = 2.0f;

//renderer runs on the main thread and does all the openGL rendering
Renderer *renderer;

//updater takes care of all the computation. Will utilize multi-threads based on the division of the data as above
Updater *updater;


void display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, MAX_WIDTH, MAX_HEIGHT+100, 0);

	//for testing purps
	//glPointSize(5);
	if(zoomToggle){		
		glScaled(0.5*zoomValue, 0.5*zoomValue, 0);
	}
	//display the number of healthy cells, cancer cells, medicine cells at the bottom of the screen
	renderer->displayCellNumbers(std::count_if(cellGrid.begin(),cellGrid.end(), count_healthy()), std::count_if(cellGrid.begin(),cellGrid.end(), count_cancer()),
		std::count_if(cellGrid.begin(),cellGrid.end(), count_medicine()), mouseX, mouseY);	
	renderer->drawPositionListVertex(cellGrid);
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
				//TODO: check if position is cancer cell first, then spawn.
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
		mouseY = (y / (0.5*zoomValue));
	}
}

void timer(int value)
{
	updater->updateCancer(cellGrid, 50000, xDimension, yDimension);
	updater->updateMedicine(cellGrid, medicineCells);
	glutPostRedisplay();
	glutTimerFunc(33.33,timer,0);
}


void populateCellVectorFullScreen(float *cellList, int maxX, int maxY){
	for(int i=0; i<maxX; i+=5){
		for(int j=0; j<maxY; j+=5){
			double probability = (rand() / (double)(RAND_MAX + 1));
			if (probability > 1.0f){
				//healthy
				cellList[j+(i*maxX)] = (float)i;
				cellList[(j+(i*maxX))+1] = (float)j;
				cellList[(j+(i*maxX))+2] = 1.0f; //r
				cellList[(j+(i*maxX))+3] = 1.0f; //g
				cellList[(j+(i*maxX))+4] = 1.0f; //b
			}
			else{
				//cancer cells
				cellList[j+(i*maxX)] = (float)i;
				cellList[(j+(i*maxX))+1] = (float)j;
				cellList[(j+(i*maxX))+2] = 1.0f; //r
				cellList[(j+(i*maxX))+3] = 1.0f; //g
				cellList[(j+(i*maxX))+4] = 1.0f; //b

			}
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
	populateCellVectorFullScreen(cellGrid, xDimension, yDimension);
	/*
		INIT OPENGL AND LOOP
	*/
	glutInit(&argc, argv);
	//use double buffer
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH );
	glutInitWindowSize(MAX_WIDTH,MAX_HEIGHT+100);
	glutCreateWindow("Cancer vs Health. FIGHT!");
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeyboardFunc);
	glutMouseFunc(MyMouseFunc);
	glutPassiveMotionFunc(getMouseCoord);
	timer(0);
	glewInit();
	//initialize vertex buffer
	renderer->initBuffer();
	glutMainLoop();

	delete[] updater;
	delete[] renderer;
	delete[] &cellGrid;
	return 0;
}