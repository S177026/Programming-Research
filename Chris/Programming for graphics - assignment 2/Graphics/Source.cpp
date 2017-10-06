#include <glew.h>
#include <glut.h>
#include <iostream>
#include <vector>
#include "textfile.h" // header file for code to read a textfile

int winXRes = 600;
int winYRes = 600;
GLuint vbo = 0;//used to store the vertex buffer object
GLuint vao = 0;//used to store the vertex array object

int numOfVertex = 108;

float drawCubeVert[108];

char *vs = nullptr;
char *fs = nullptr;
GLuint sID;

char ch = '1';
FILE *filePointer;
int read = 0;
GLfloat x, y, z;

struct Vertex
{
	float x;
	float y;
	float z;
};

static std::vector<Vertex*> vertList;
static std::vector<Vertex*>Faces;


/*
 *Check that the shader has compiled, this is because we cannot see in the same way as normal code, if 
 * there is a compile error in the shader code.
 */
void shaderCompilerCheck(GLuint ID)
{
	GLint comp;
	glGetShaderiv(ID, GL_COMPILE_STATUS, &comp);//return the compile status from the shader

	if(comp == GL_FALSE)//if it fails, print an error message
	{
		printf("Shader Compilation failed");
		GLchar messages[256];
		glGetShaderInfoLog(ID, sizeof(messages), 0, &messages[0]);
		printf("message %s \n", messages);
	}
}

/*
 * Checks that the shader has been linked into the main application correctly
 * Outputs errors in the shader
 */
void shaderLinkCheck(GLuint ID)
{
	GLint linkStatus, validateStatus;
	glGetProgramiv(ID, GL_LINK_STATUS, &linkStatus);//return the linker status from the shader

	if (linkStatus == GL_FALSE)
	{
		printf("Shader linking failed\n");
		GLchar messages[256];
		glGetProgramInfoLog(ID, sizeof(messages), 0, &messages[0]);
		printf("message %s \n", messages);
	}
	glValidateProgram(ID);
	glGetProgramiv(ID, GL_VALIDATE_STATUS, &validateStatus);//return the result of the validation process
	if (validateStatus == GL_FALSE)//if the application failed to validate, print the error
	{
		printf("Shader validation failed\n");
		GLchar messages[256];
		glGetProgramInfoLog(ID, sizeof(messages), 0, &messages[0]);
		printf("message %s \n", messages);
	}
}

/*
 * function to create the vert and frag shaders
 */
void shaders()
{
	sID = glCreateProgram();

	GLuint vID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fID = glCreateShader(GL_FRAGMENT_SHADER);

	vs = textFileRead("VertexShader.vert");
	fs = textFileRead("FragmentShader.frag");

	glShaderSource(vID, 1, &vs, NULL);//loads the contents of the vert shader
	glShaderSource(fID, 1, &fs, NULL);//loads the contents of the fragment shader


	glCompileShader(vID);//compile the vert shader
	glCompileShader(fID);//compile the frag shader
	shaderCompilerCheck(vID);//check for compile errors in the vert shader
	shaderCompilerCheck(fID);//check for compile errors in the frag shader

	glAttachShader(sID, vID);//attached the shader to the main program
	glAttachShader(sID, fID);//attached the fragment shader to the main program

	glBindAttribLocation(sID, 0, "VertexPosition");//bind the index 0 to the shader input variable  "VertexPosition"
	glBindAttribLocation(sID, 1, "VertexColor");//bind index 1 to the shader input variable VertexColor;
	glLinkProgram(sID);//send the vertex shader program to the GPU vertex processor, and the fragment to the GPU fragment processor

	shaderLinkCheck(sID);//check the linker for errors

	GLuint Buffers[2];

	glGenBuffers(1, Buffers);//create 2 buffer objects
	vbo = Buffers[0];//set vbo to the first buffer object

	//vertex array
	glBindBuffer(GL_ARRAY_BUFFER, vbo);//make the buffer object a vertex array
	glBufferData(GL_ARRAY_BUFFER, numOfVertex * sizeof(float), drawCubeVert, GL_STATIC_DRAW);//set the size of the buffer and insert the data



	glGenVertexArrays(1, &vao); //generate a name for the vert array
	glBindVertexArray(vao);//bind the vert array object

	glEnableVertexAttribArray(0);//enable the vert array
	glEnableVertexAttribArray(1);//enable the color array

	//map index 0 to the position buffer
	glBindBuffer(GL_ARRAY_BUFFER, vao);
	glVertexAttribPointer(0, 3, GL_FLOAT,GL_FALSE, 0, NULL);//apply some properties to the verticies
	


}


void ReadOBJ()
{
	filePointer = fopen("cube.obj", "r"); //Open the file for reading
	if (!filePointer)
	{
		std::cout << "Can't open file: " << std::endl;
		exit(1);
	}
	int i = 0;
	int j = 0;
	while (!(feof(filePointer))) // while not at the end of the file
	{

		read = fscanf(filePointer, "%c %f %f %f", &ch, &x, &y, &z);

		
		if (read == 4 && ch == 'v')//if the char is v, populate the vertex array
		{
			Vertex *vert = new Vertex;
			vertList.push_back(vert);

			vertList[i]->x = x;
			vertList[i]->y = y;
			vertList[i]->z = z;
			
			i++;
		}
		if (read == 4 && ch == 'f')//if it is f, populate the face array
		{
			Vertex *face = new Vertex;
			Faces.push_back(face);
			
			Faces[j]->x = x;
			Faces[j]->y = y;
			Faces[j]->z = z;

			j++;
		}

	}
	std::cout << "File read successfully." << std::endl;
}

/*split the vertex vector into an array*/
void genFaces()
{
	int faceIndex = 0;
	for (auto &face : Faces)//for every face in the array
	{
		drawCubeVert[faceIndex] = vertList[face->x - 1]->x;	//////////////////////////////////////////
		faceIndex++;										//Find the x/y/z for each face			//
		drawCubeVert[faceIndex] = vertList[face->x - 1]->y; //in the list and assign it to the array//
		faceIndex++;										//////////////////////////////////////////
		drawCubeVert[faceIndex] = vertList[face->x - 1]->z;
		faceIndex++;
		drawCubeVert[faceIndex] = vertList[face->y - 1]->x;
		faceIndex++;
		drawCubeVert[faceIndex] = vertList[face->y - 1]->y;
		faceIndex++;
		drawCubeVert[faceIndex] = vertList[face->y - 1]->z;
		faceIndex++;
		drawCubeVert[faceIndex] = vertList[face->z - 1]->x;
		faceIndex++;
		drawCubeVert[faceIndex] = vertList[face->z - 1]->y;
		faceIndex++;
		drawCubeVert[faceIndex] = vertList[face->z - 1]->z;
		faceIndex++;
	}
}
/*
 * draws the shaders to the screen
 */
void renderShader()
{
	glUseProgram(sID);//use the shader program which was set in main
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, numOfVertex);//use the first 3 verticies from position 0 to draw a triangle
	glUseProgram(0);//unbind the shader program
}


void Display()
{
	//clear the screen, set the perspective and the view mode
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	gluPerspective(45.0, 1.0, 1.0, 100.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//then render the shaders
	renderShader();
	//then swap the buffers
	glutSwapBuffers();
	glutPostRedisplay();
}
/*initialise the basic gl functions and read the obj file + set up the required faces from this*/
void initGL()
{

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0, 2.0, 0.0, 2.0, -1.0, 1.0);
	ReadOBJ();
	genFaces();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	glutInitWindowPosition(200, 50);
	glutInitWindowSize(winXRes, winYRes);
	glutCreateWindow("Oliver Chamberlain Graphics assignment 2 shaders example");
	glewInit();
	initGL();

	//check if the glsl is available
	if (GLEW_ARB_vertex_shader && GLEW_ARB_fragment_shader)
		printf("Ready for GLSL\n");
	else
	{
		printf("No GLSL support\n");
		exit(1);
	}

	shaders();//create the shader programs

	glutDisplayFunc(Display);

	glutMainLoop();
	return 0;
}