#include<windows.h>
#include <GL/glut.h>
#include <math.h>

#define pi (2*acos(0.0))

double angle = 0;
double length;


void drawSphere(double radius,int slices,int stacks);
void drawCone(double radius,double height,int segments);
void drawCylinder(double radius, double height, int slices);


struct point{
    double x,y,z;
};


void drawAxes()
{

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);{
        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f( 1000,0,0);
        glVertex3f(-1000,0,0);

        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(0,-1000,0);
        glVertex3f(0, 1000,0);

        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0,0, 1000);
        glVertex3f(0,0,-1000);
    }glEnd();

}


void drawGrid()
{
	int i;

    glColor3f(0.6, 0.6, 0.6);	//grey
    glBegin(GL_LINES);{
        for(i=-8;i<=8;i++){

            if(i==0)
                continue;	//SKIP the MAIN axes

            //lines parallel to Y-axis
            glVertex3f(i*10, -90, 0);
            glVertex3f(i*10,  90, 0);

            //lines parallel to X-axis
            glVertex3f(-90, i*10, 0);
            glVertex3f( 90, i*10, 0);
        }
    }glEnd();

}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a, a,2);
		glVertex3f( a,-a,2);
		glVertex3f(-a,-a,2);
		glVertex3f(-a, a,2);
	}glEnd();
}

void drawPyramid(double base, double height)
{
    glBegin(GL_QUADS);
        glColor3f(0,1,0);
        glVertex3f(0,0,0);
        glVertex3f(base,0,0);
        glVertex3f(base, base, 0);
        glVertex3f(0,base,0);
    glEnd();

    glBegin(GL_TRIANGLES);

        glColor3f(1,1,0);
        glVertex3f(base/2, base/2, height);
        glVertex3f(0, base, 0);
        glVertex3f(base, base, 0);

        glColor3f(0,1,1);
        glVertex3f(base/2, base/2, height);
        glVertex3f(base, base, 0);
        glVertex3f(base, 0, 0);

        glColor3f(1,0,1);
        glVertex3f(base/2, base/2, height);
        glVertex3f(base, 0, 0);
        glVertex3f(0,0,0);

        glColor3f(1,1,1);
        glVertex3f(base/2, base/2, height);
        glVertex3f(0,0,0);
        glVertex3f(0,base,0);

    glEnd();
}

void drawCube(double length)
{
    glBegin(GL_QUADS);

        glColor3f(1,0,0);
        glVertex3f(0,0,length);
        glVertex3f(length, 0, length);
        glVertex3f(length, length, length);
        glVertex3f(0, length, length);

        glColor3f(0,1,0);
        glVertex3f(length, 0, length);
        glVertex3f(length, 0, 0);
        glVertex3f(length, length, 0);
        glVertex3f(length, length, length);

        glColor3f(0,0,1);
        glVertex3f(length, length, 0);
        glVertex3f(0, length, 0);
        glVertex3f(0,0,0);
        glVertex3f(length, 0, 0);

        glColor3f(0,1,1);
        glVertex3f(0,0,0);
        glVertex3f(0, length, 0);
        glVertex3f(0, length, length);
        glVertex3f(0, 0, length);

        glColor3f(1,1,0);
        glVertex3f(length, length, 0);
        glVertex3f(0, length, 0);
        glVertex3f(0, length, length);
        glVertex3f(length, length, length);

        glColor3f(1,0,1);
        glVertex3f(0,0,0);
        glVertex3f(0,0, length);
        glVertex3f(length, 0, length);
        glVertex3f(length, 0, 0);
    glEnd();
}


void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/********************
	/ set-up camera here
	********************/
	//load the correct matrix -- MODEL-VIEW matrix
	glMatrixMode(GL_MODELVIEW);

	//initialize the matrix
	glLoadIdentity();

	//now give three info
	//1. where is the camera (viewer)?
	//2. where is the camera looking?
	//3. Which direction is the camera's UP direction?

	gluLookAt(100,100,100,	0,0,0,	0,0,1);



	//again select MODEL-VIEW
	glMatrixMode(GL_MODELVIEW);


	/****************************
	/ Add your objects from here
	****************************/
	//add objects

	drawAxes();
	drawGrid();
	glPushMatrix();
       glRotated(angle,0,1,0);

        glPushMatrix();
        glTranslated(0,0,65);
        drawSphere(10,50,50);
        glPopMatrix();

        glPushMatrix();
        glTranslated(0,0,30);
        drawCone(15,25,80);
        glPopMatrix();
        drawCube(30);
	glPopMatrix();


	//drawCone(40,50,50);

	/*glRotated(angle, 0, 1, 0);
	glTranslated(-20, -20, 0);
	drawPyramid(40, 50);*/

	//drawCylinder(40,50, 100);

	/*glScaled(1.5, 0.5, 0.75);
	drawCube(50);*/

	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
    angle += 0.25;
	//codes for any changes in Models, Camera
	glutPostRedisplay(); // marks the current window as needing to be redisplayed
}

void init(){
	//codes for initialization

	//clear the screen
	glClearColor(0,0,0,0);

	/************************
	/ set-up projection here
	************************/
	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	5000.0);
	//field of view in the Y (vertically)
	//aspect ratio that determines the field of view -
	//in the X direction (horizontally) = width/height
	//near distance
	//far distance
}




void drawCircle(double radius,int segments)
{
    int i;
    struct point points[100];
    glColor3f(0.7,0.7,0.7);
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw segments using generated points
    for(i=0;i<segments;i++)
    {
        glBegin(GL_LINES);
        {
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}

void drawCone(double radius,double height,int segments)
{
    int i;
    double shade;
    struct point points[100];
    //generate points
    for(i=0;i<=segments;i++)
    {
        points[i].x=radius*cos(((double)i/(double)segments)*2*pi);
        points[i].y=radius*sin(((double)i/(double)segments)*2*pi);
    }
    //draw triangles using generated points
    for(i=0;i<segments;i++)
    {
        //create shading effect
        if(i<segments/2)shade=2*(double)i/(double)segments;
        else shade=2*(1.0-(double)i/(double)segments);
        glColor3f(shade,shade,shade);

        glBegin(GL_TRIANGLES);
        {
            glVertex3f(0,0,height);
			glVertex3f(points[i].x,points[i].y,0);
			glVertex3f(points[i+1].x,points[i+1].y,0);
        }
        glEnd();
    }
}


void drawSphere(double radius,int slices,int stacks)
{
	struct point points[100][100];
	int i,j;
	double h,r;
	//generate points
	for(i=0;i<=stacks;i++)
	{
		h=radius*sin(((double)i/(double)stacks)*(pi/2));
		r=radius*cos(((double)i/(double)stacks)*(pi/2));
		for(j=0;j<=slices;j++)
		{
			points[i][j].x=length + r*cos(((double)j/(double)slices)*2*pi);
			points[i][j].y=length + r*sin(((double)j/(double)slices)*2*pi);
			points[i][j].z=h +length;
		}
	}
	//draw quads using generated points
	for(i=0;i<stacks;i++)
	{
        glColor3f((double)i/(double)stacks,(double)i/(double)stacks,(double)i/(double)stacks);
		for(j=0;j<slices;j++)
		{
			glBegin(GL_QUADS);{
			    //upper hemisphere
				glVertex3f(points[i][j].x,points[i][j].y,points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,points[i+1][j].z);
                //lower hemisphere
                glVertex3f(points[i][j].x,points[i][j].y,-points[i][j].z);
				glVertex3f(points[i][j+1].x,points[i][j+1].y,-points[i][j+1].z);
				glVertex3f(points[i+1][j+1].x,points[i+1][j+1].y,-points[i+1][j+1].z);
				glVertex3f(points[i+1][j].x,points[i+1][j].y,-points[i+1][j].z);
			}glEnd();
		}
	}
}

void drawCylinder(double radius, double height, int slices)
{
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
        for(int i=0; i<=slices; i++)
        {
            glVertex3f(radius*cos(2*pi * i/slices), radius*sin(2*pi* i/slices), 0);
        }
    glEnd();

    glBegin(GL_POLYGON);
        for(int i=0; i<=slices; i++)
        {
            glVertex3f(radius*cos(2*pi * i/slices), radius*sin(2*pi* i/slices), height);
        }
    glEnd();


    glColor3f(1,1,0);
    glBegin(GL_QUADS);
        for(int i=0; i<slices; i++)
        {
            glVertex3f(radius*cos(2*pi * i/slices), radius*sin(2*pi* i/slices), 0);
            glVertex3f(radius*cos(2*pi * (i+1)/slices), radius*sin(2*pi* (i+1)/slices), 0);

            glVertex3f(radius*cos(2*pi * (i+1)/slices), radius*sin(2*pi* (i+1)/slices), height);
            glVertex3f(radius*cos(2*pi * i/slices), radius*sin(2*pi* i/slices), height);
        }
    glEnd();
}





int main(int argc, char **argv){

	glutInit(&argc,argv);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color
	/*
	GLUT_DOUBLE - allows for display on the double buffer window

    GLUT_RGB - shows color (Red, green, blue)

    GLUT_DEPTH - allows for depth buffer
    */

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);
	//When depth testing is enabled, OpenGL tests the depth value
	//of a fragment against the content of the depth buffer

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)


	glutMainLoop();		//The main loop of OpenGL

	return 0;
}
