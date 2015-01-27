#pragma once
#include <stdlib.h>
#include <glew.h>
#include <glut.h>
#include <gl\GL.h>
#include <iostream>
#include <sstream>
#include <VertexCell.h>
#include <vector>

static int MAX_WIDTH = 900;
static int MAX_HEIGHT = 900;

class Renderer
{
public:
	static enum COLOR
	{
		red, yellow, green
	};
	Renderer(void);
	~Renderer(void);
	void displayCellNumbers(int healthSize, int cancerSize, int medicineSize);

	void drawPositionListVertex(std::vector<VertexCell> &cellVector);

	bool isBufferInit;
	GLuint vboId;   

	void initBuffer(std::vector<VertexCell> &cellVector);
};

