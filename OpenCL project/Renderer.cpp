#include "Renderer.h"


Renderer::Renderer(void)
{
}


Renderer::~Renderer(void)
{
}

 void Renderer::initBuffer(){
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	
 }


void Renderer::drawPositionListVertex(float* cellVector){

		float size = MAX_HEIGHT * MAX_WIDTH * 5;
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(GLfloat), &cellVector[0], GL_DYNAMIC_DRAW);	
		//glColor3f(0.0f,1.0f,0.0f);

		//step 1
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		//step 2
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		//step 3
		glVertexPointer(2, GL_FLOAT, sizeof(GLfloat)*5, 0);
		glColorPointer(3, GL_FLOAT, sizeof(GLfloat)*5, (void*)(sizeof(GLfloat) * 2));
		//step 4
		glDrawArrays(GL_POINTS, 0, size);
		//glDrawArrays(GL_POINTS, 0, 5);
		//step 5
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);        
}


void Renderer::displayCellNumbers(int healthSize, int cancerSize, int medicineSize, int mousePosX, int mousePosY){

	glColor3f(1.0, 1.0, 1.0 );
	
	std::string strHealth = "Health Cells : "+std::to_string(healthSize);
	std::string strCancer = "Cancer Cells : "+std::to_string(cancerSize);
	std::string strMedicine = "Medicine Cells : "+std::to_string(medicineSize);
	std::string mousePositionX = "Mouse position : "+std::to_string(mousePosX);
	std::string mousePositionY = "Mouse position : "+std::to_string(mousePosY);
	const char * cHealth = strHealth.c_str();
	const char * cCancer = strCancer.c_str();
	const char * cMedicine = strMedicine.c_str();
	const char * mPosX = mousePositionX.c_str();
	const char * mPosY = mousePositionY.c_str();

	int len;
	glRasterPos2f(0, MAX_HEIGHT+33);
	len = (int)strlen(cHealth);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, cHealth[i]);
	  }

	glRasterPos2f(0, MAX_HEIGHT + 66);
	len = (int)strlen(cCancer);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, cCancer[i]);
	  }

	glRasterPos2f(0, MAX_HEIGHT + 100);
	len = (int)strlen(cMedicine);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, cMedicine[i]);
	  }

	glRasterPos2f(500, MAX_HEIGHT+50);
	len = (int)strlen(mPosX);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, mPosX[i]);
	  }
	glRasterPos2f(500, MAX_HEIGHT+100);
	len = (int)strlen(mPosY);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, mPosY[i]);
	  }
	
  
}

