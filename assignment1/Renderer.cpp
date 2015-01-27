#include "Renderer.h"


Renderer::Renderer(void)
{
}


Renderer::~Renderer(void)
{
}



void Renderer::drawPositionListVertex(std::vector<VertexCell> &cellVector){

	if(cellVector.size() !=0){
		
		VertexCell vcs = cellVector[1];
		glGenBuffers(1, &vboId);
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		glBufferData(GL_ARRAY_BUFFER, cellVector.size() * sizeof(VertexCell), &(cellVector.front()), GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		//glColor3f(0.0f,1.0f,0.0f);

		//step 1
		glBindBuffer(GL_ARRAY_BUFFER, vboId);
		//step 2
		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_COLOR_ARRAY);
		//step 3
		glVertexPointer(2, GL_FLOAT, sizeof(VertexCell), 0);
		glColorPointer(3, GL_FLOAT, sizeof(VertexCell), (void*)(sizeof( float ) * 2));
		//step 4
		glDrawArrays(GL_POINTS, 0, cellVector.size());
		//step 5
		glDisableClientState(GL_COLOR_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	
		glDeleteBuffers(1, &vboId);
		//cellVector.clear();
	}
          
}


void Renderer::displayCellNumbers(int healthSize, int cancerSize, int medicineSize){

	glColor3f(1.0, 1.0, 1.0 );
	
	std::string strHealth = "Health Cells : "+std::to_string(healthSize);
	std::string strCancer = "Cancer Cells : "+std::to_string(cancerSize);
	std::string strMedicine = "Medicine Cells : "+std::to_string(medicineSize);
	const char * cHealth = strHealth.c_str();
	const char * cCancer = strCancer.c_str();
	const char * cMedicine = strMedicine.c_str();

	int len;
	glRasterPos2f(0, MAX_HEIGHT+50);
	len = (int)strlen(cHealth);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, cHealth[i]);
	  }

	glRasterPos2f(0, MAX_HEIGHT + 100);
	len = (int)strlen(cCancer);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, cCancer[i]);
	  }

	glRasterPos2f(0, MAX_HEIGHT + 150);
	len = (int)strlen(cMedicine);
	for (int i = 0; i < len; i++) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, cMedicine[i]);
	  }
	
  
}

