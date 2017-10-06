//https://oliverchamberlainblog.wordpress.com/

#include <iostream>
#include <glut.h>
#include <IL/ilut.h> 
#include <math.h>
#include <freeglut.h>


GLint win1ID;
GLint win2ID;


GLint giXRes = 600;
GLint giYRes = 600;
GLfloat zRotate = 0;
GLfloat rotateSpeed = 0.01f;

GLuint boxImage; // variable to hold the name of the box image
GLuint tileImage;
GLuint iceImage;
GLuint cubeTexture1;
GLuint cubeTexture2;
GLuint sphereTexture;

// mouse movement variables //
float angle = 0.0f; // angle of rotation for the camera
float lx = 0.0f, lz = -1.0f;// actual vector representing the cameras direction
float x = 0.0f, z = 5.0f; // xz pos of camera

float camX = 10;
float camY = -10;

// key states
// variables set to zero when no key pressed
float deltaAngle = 0.0f;
float deltaMove = 0;
int xOrigin = -1;

//transform variables//
GLfloat sphereX = 1;
GLfloat sphereY = -1;
GLfloat moveAmount = 0.001;
GLfloat rotation = 0.0f;

void InitTextures(void)
{
	// Define wrapping behaviour for material//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	// Define texture Filtering behaviour for material//
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	//Load textures//
	boxImage = ilutGLLoadImage("box.bmp"); // Load an image and apply it to the variable boxImage
	tileImage = ilutGLLoadImage("tile.jpg");
	iceImage = ilutGLLoadImage("ice.jpg");

	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // Define how material is sent further down the rendering pipeline
	cubeTexture1 = boxImage;
	cubeTexture2 = tileImage;
	sphereTexture = iceImage;
}
/*
*Draws a cube
*Define all of the cube's vertices and all of the required texture coordinates
*defined in a counter clockwise order with the surface normals pointing outwards
*/
void drawCube() {
	zRotate += rotateSpeed;//set up the rotation speed for the cube, increase the rotation variable by a set increment variable
	glRotatef(zRotate, 0.5, 1.0, 0.0);//apply the cube's rotation from the rotation variable

	glEnable(GL_TEXTURE_2D); //enable texture mapping

	glBindTexture(GL_TEXTURE_2D, cubeTexture1);//set the texture to the box image
	glBegin(GL_POLYGON);

	// Define vertices in counter-clockwise (CCW) order with normal pointing out	
	glTexCoord2f(1.0, 0.0);//set the local co-ordinates for the texture
	glVertex3f(1.0f, 1.0f, -1.0f);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0f, 1.0f, -1.0f);

	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, 1.0f, 1.0f);

	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	glEnd();


	glBegin(GL_POLYGON);
	// Bottom face (y = -1.0f)	
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, -1.0f, 1.0f);

	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, -1.0f, -1.0f);	
	
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	
	glEnd();
	glBegin(GL_POLYGON);

	// Front face  (z = 1.0f)	
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	
	glEnd();
	
	glBindTexture(GL_TEXTURE_2D, cubeTexture2);//change the bound texture to the tile image

	glBegin(GL_POLYGON);
	// Back face (z = -1.0f)
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, 1.0f, -1.0f);
	
	glEnd();

	glBegin(GL_POLYGON);
	// Left face (x = -1.0f)
	glTexCoord2f(1.0, 0.0);
	glVertex3f(-1.0f, 1.0f, 1.0f);
	
	glTexCoord2f(1.0, 1.0);
	glVertex3f(-1.0f, 1.0f, -1.0f);
	
	glTexCoord2f(0.0, 1.0);
	glVertex3f(-1.0f, -1.0f, -1.0f);
	
	glTexCoord2f(0.0, 0.0);
	glVertex3f(-1.0f, -1.0f, 1.0f);
	
	glEnd();

	glBegin(GL_POLYGON);
	// Right face (x = 1.0f)
	glTexCoord2f(1.0, 0.0);
	glVertex3f(1.0f, 1.0f, -1.0f);
	
	glTexCoord2f(1.0, 1.0);
	glVertex3f(1.0f, 1.0f, 1.0f);
	
	glTexCoord2f(0.0, 1.0);
	glVertex3f(1.0f, -1.0f, 1.0f);
	
	glTexCoord2f(0.0, 0.0);
	glVertex3f(1.0f, -1.0f, -1.0f);
	
	glEnd();

	glDisable(GL_TEXTURE_2D);// switch off 2d texture mapping


}
void computePos(float deltaMove)
{
	x += deltaMove * lx *0.1f;
	z += deltaMove *lz * 0.1f;
}
void Sphere()// spawn a sphere, move it from the bottom right corner, to the bottom left, then the top left, and from there on move it back to the bottom right corner.
{

	

	GLUquadricObj * qObj = gluNewQuadric();//create a pointer to a quadric, allowing it to create 
	gluQuadricNormals(qObj, GLU_SMOOTH);//set the quadric normals
	gluQuadricTexture(qObj, GL_TRUE);//and allow it to be textured

	glEnable(GL_TEXTURE_2D);//enable 2d texturing
	glBindTexture(GL_TEXTURE_2D, sphereTexture);//bind the ice texture 
	glTranslatef(sphereX, sphereY, -3);//transform the sphere's position by its x and y positions (worked out below) and set its z position to -3
	gluSphere(qObj, 0.75, 32, 32);//Create the sphere which will have the bound texture
	glDisable(GL_TEXTURE_2D);//disable 2d texturing

	//satellite//
	glRotatef(rotation, 0, 1, 1); //rotate around the z axis
	glTranslatef(1.5,0.5 ,0); // and translate the sphere, this translation is in relation to the 
	glutSolidSphere(0.5, 32, 32);//then finally render the sphere


	//move the sphere in a square around the cube, with it's satellite in tow
	if (sphereX > -4)
	{
		sphereX -= moveAmount;
	}

	else if (sphereX <= -4)
	{
		if (sphereY < 4)
		{
			sphereY += moveAmount;
		}
	}
	 if (sphereY >= 4)
	{

		sphereX += moveAmount+ 0.001;
	}

	 if (sphereY >= 4 && sphereX >= 4)
	 {
		 sphereY = -4;
	 }

	 //increase rotation angle, for the satellite

	 rotation += 0.2f;

	 if (rotation >= 360)//in the case that rotation exceeds or equals a full circle(360) reset it to 0
	 {
		 rotation = 0;
	 }
}
/*renders text from a char array to be drawn to the screen*/
void Text(const char *text, int length, float x, float y)
{
	glMatrixMode(GL_PROJECTION);
	double *matrix = new double[16];
	glGetDoublev(GL_PROJECTION_MATRIX, matrix);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -5, 5);//set co-ordinate system for the placement of the text (0,800 x, 0,600 y)
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glPopMatrix();
	glRasterPos2f(x, y);//position
	for (int i = 0; i < length; i++)//loop through the characters to draw each letter to the screen, rasterPos moves the next letter across by the width of the previous letter
	{
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, (int)text[i]);//set the font and size of the font for the character and give it which character in the array to render, casted into an int to get it's ascii value
	}
	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixd(matrix);
	glMatrixMode(GL_MODELVIEW);
}
/*Called from display to render text */
void RenderText()
{
	std::string text;//create a string, a string is more suitable here because we do not want to define a length for a char array
	text = "Oliver Chamberlain S179650";//define the string
	Text(text.c_str(), text.size(), 250, 500);//string constent: to c_str which converts it to a char array, string length, x position, y position
}

void menuFunc(int entry)
{
	/*Switch state controls which textures are shown*/
	switch (entry)
	{
	case 3:
		cubeTexture1 = boxImage;//tex1 - box
		break;
	case 4:
		cubeTexture1 = tileImage;//tex1 - tile
		break;
	case 5:
		cubeTexture1 = iceImage;//tex1 - ice
		break;
	case 6:
		cubeTexture2 = boxImage;//tex2 - box
		break;
	case 7:
		cubeTexture2 = tileImage;//tex2 - tile
		break;
	case 8:
		cubeTexture2 = iceImage;//tex2 - ice
		break;
	case 9:
		sphereTexture = boxImage;//sphere - box
		break;
	case 10:
		sphereTexture = tileImage;//sphere - tile
		break;
	case 11:
		sphereTexture = iceImage;
		break;


	}
}
//both display1 and display 2 call the same functions as eachother, so that they can render the same things, the only thing that
//is changed between the two is that the camera positions are changed to allow for a different view in each viewport
void display1()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear the color buffer
	glMatrixMode(GL_PROJECTION);//enter projection mode
	glLoadIdentity();//load the identity matrix to clear it
	gluPerspective(45.0, 1.0, 1.0, 100.0);//set the correct perspective
	glMatrixMode(GL_MODELVIEW);//enter modelview 
	glLoadIdentity();//then make sure that the maxtrix is clear again
	glClearColor(1.0, 1.0, 1.0, 1.0);//change background colour to white
	

	glTranslatef(0.0f, 0.0f, -5.0f);//move the camera backwards to be able to more easily see the rendered objects
	gluLookAt(x, 0, z,//camera pos
			  x+lx, 0, z+lz,// target pos
			  0, 1, 0); // up vector
	
	
	glPushMatrix();
	drawCube();// draw the textured cube
	glPopMatrix();

	Sphere();//draw the textured sphere and it's satellite
	RenderText();
	

	glutSwapBuffers();//swap the buffers
	glutPostRedisplay();
}
void display2()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);//clear the color buffer
	glMatrixMode(GL_PROJECTION);//enter projection mode
	glLoadIdentity();//load the identity matrix to clear it
	gluPerspective(45.0, 1.0, 1.0, 100.0);//set the correct perspective
	glMatrixMode(GL_MODELVIEW);//enter modelview 
	glLoadIdentity();//then make sure that the maxtrix is clear again
	glClearColor(1.0, 1.0, 1.0, 1.0);//change background colour to white


	//glTranslatef(0.0f, 0.0f, 10.0f);//move the camera backwards to be able to more easily see the rendered objects
	gluLookAt(0, camY, camX,//camera pos
		0, 0, 0,// target pos - camera always looks at 0,0,0 regardless of its position
		0, 1, 0); // up vector


	glPushMatrix();
	drawCube();// draw the textured cube
	glPopMatrix();

	Sphere();//draw the textured sphere and it's satellite
	RenderText();


	glutSwapBuffers();//swap the buffers
	glutPostRedisplay();
}
// Re-size event. Called back when the window first appears and
// whenever the window is re-sized with its new width and height 
void reshape(GLsizei width, GLsizei height) {		// GLsizei must be non-negative integer

													// Compute aspect ratio of the new window
	if (height == 0) height = 1;					// To prevent divide by 0
	GLfloat aspect = (GLfloat)width / (GLfloat)height;

	// Set the viewport to cover the new window
	glViewport(0, 0, width, height);

	// Set the aspect ratio of the clipping volume to match the viewport
	glMatrixMode(GL_PROJECTION);  // Enable the Projection matrix
	glLoadIdentity();             // Reset

								  // Enable perspective projection with fovy, aspect, zNear and zFar
	gluPerspective(45.0f, aspect, 0.1f, 100.0f);
}
void initGL() {
	glFrontFace(GL_CW); // assumes verticies are clockwise
	glCullFace(GL_BACK);

	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);//enable depth text
	glDepthFunc(GL_LEQUAL);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);//set up the coordinate space

	glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);// use the normals from each surface to calculate the lighting
	glEnable(GL_LIGHTING);// enable lighting
	glEnable(GL_LIGHT0);// create a light (light0)


	GLfloat qaAmbientLight[] = { 1.0,0.3,0.2,1.0 };//ambient settings
	GLfloat qaDiffuseLight[] = { 0.8,0.8,0.8,1.0 };//diffuse settings
	GLfloat qaSpecularLight[] = { 1.0,1.0,1.0,1.0 };//specular settings
	
	//define behaviour of the lights//
	glLightfv(GL_LIGHT0, GL_AMBIENT, qaAmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, qaDiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, qaDiffuseLight);


	GLfloat qaLightPosition[]	= {sphereX, sphereY, 1.0, 1.0};		// vector to store location of light0
	glLightfv(GL_LIGHT0, GL_POSITION, qaLightPosition);		// Set position of light0



}
void initMenu()
{
	int subMenuTex1 = glutCreateMenu(menuFunc);
	glutAddMenuEntry("Box", 3);
	glutAddMenuEntry("Tile", 4);
	glutAddMenuEntry("Ice", 5);

	int subMenuTex2 = glutCreateMenu(menuFunc);
	glutAddMenuEntry("Box", 6);
	glutAddMenuEntry("Tile", 7);
	glutAddMenuEntry("Ice", 8);

	int subMenuSphereTex = glutCreateMenu(menuFunc);
	glutAddMenuEntry("Box", 9);
	glutAddMenuEntry("Tile", 10);
	glutAddMenuEntry("Ice", 11);

	int mainMenu = glutCreateMenu(menuFunc);
	glutAddSubMenu("Box Texture one", subMenuTex1);
	glutAddSubMenu("Box Texture two", subMenuTex2);
	glutAddSubMenu("Sphere Texture", subMenuSphereTex);
	

	glutAttachMenu(GLUT_RIGHT_BUTTON);
}
void pressKey(int key, int x, int y)
{
	switch (key)//check to see if the button has been pressed, set the deltaMove variable accordingly
	{
	case GLUT_KEY_UP:deltaMove = 0.5f; break;
	case GLUT_KEY_DOWN: deltaMove = -0.5f; break;
	}
}
void releaseKey(int key, int x, int y)
{
	switch (key)//if the key is released break, otherwise set deltaMove to nothing
	{
	case GLUT_KEY_UP: break;
	case GLUT_KEY_DOWN: deltaMove = 0; break;
	}
}
void mouseMove(int x, int y)
{
	if (xOrigin >= 0)//if the origin is greater than or equal to 0
	{
		deltaAngle = (x - xOrigin) * 0.001f;//then deltaAngle is equal to the x mouse position minus the origin multiplied by 0.001


		//use the sin and -cos of angle + the difference between origin angle and end angle to update camera
		lx = sin(angle + deltaAngle);
		lz = -cos(angle + deltaAngle);
	}
}
void mouseButton(int button, int state, int x, int y)
{
	// only if lmb is pressed
	if (state == GLUT_LEFT_BUTTON) 
	{
		// when released
		if (state == GLUT_UP)
		{
			angle += deltaAngle;
			xOrigin = -1;
		}
		else {//state = down
			xOrigin = x;
		}
	}
}
void Timer(int iUnused)
{
	glutPostRedisplay();
	glutTimerFunc(1, Timer, 0);
}
int main(int argc, char** argv) {
	glutInit(&argc, argv);

	
	//window1
	glutInitDisplayMode(GLUT_DOUBLE);//set the diplay mode
	glutInitWindowSize(giXRes, giYRes);//set the window size
	glutInitWindowPosition(50, 50);//set the position
	win1ID = glutCreateWindow("Programming for graphics -Oliver Chamberlain(s179650) window 1");//create the window and set the title 
	glutDisplayFunc(display1);
	initMenu();
	initGL();
	ilInit();//inititalise Devil
	iluInit();
	glutReshapeFunc(reshape);
	
	//key presses for camera move on window1 // 
	glutSpecialFunc(pressKey);
	glutSpecialUpFunc(releaseKey);

	glutMouseFunc(mouseButton);
	glutMotionFunc(mouseMove);

	ilutRenderer(ILUT_OPENGL);
	InitTextures(); // Custom function to configure the textures for window 2
	
					
					
					
	//window2
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(giXRes, giYRes);
	glutInitWindowPosition(250, 250);
	win2ID = glutCreateWindow("Programming for graphics - Oliver Chamberlain(s179650) window 2");
	glutDisplayFunc(display2);
	
	initMenu();
	initGL();//initialize openGL variables
	ilInit();//inititalise Devil
	iluInit();
	ilutRenderer(ILUT_OPENGL);//set the renderer

	InitTextures(); //initialise textures for window 2

	

	

	//initGL();//initialise opengl

	glutMainLoop();
	return 0;
}

