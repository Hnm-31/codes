
# include<bits/stdc++.h>
#include<GL/glut.h>
using namespace std;

struct Line{
	int x1,y1,x2,y2;
	char type;
};

//vector<Line> lines;

int flag =0;
void plotpixel(int x,int y){
	glBegin(GL_POINTS);
	glVertex2i(x,y);
	glEnd();
}

void normaldda(int x1,int y1,int x2,int y2){
	int dx = x2-x1;
	int dy = y2-y1;
	float x = x1;
	float y =y1;
	int steps = max(abs(dx),abs(dy));
float xinc = float(dx)/steps;
	float yinc = float(dy)/steps;
	for(int i=0;i<steps;i++){
		plotpixel(int(x),int(y));
		x += xinc;
		y += yinc;
	}
	
}



void dda_dotted(int x1,int y1,int x2,int y2){
	int dx = x2-x1;
	int dy = y2-y1;
	float x = x1;
	float y =y1;
	int steps = max(abs(dx),abs(dy));
	float xinc = float(dx)/steps;
	float yinc = float(dy)/steps;
	
	for(int i=0;i<steps;i++){
		if(i%2==0){
				plotpixel(int(x),int(y));
		}
	
		x += xinc;
		y += yinc;
	}
	
}

void dda_dashed(int x1,int y1,int x2,int y2){
	int dx = x2-x1;
	int dy = y2-y1;
	float x = x1;
	float y =y1;
	int steps = max(abs(dx),abs(dy));
	float xinc = float(dx)/steps;
	float yinc = float(dy)/steps;
	
	for(int i=0;i<steps;i++){
		if(((i/5 )%2)==0){
				plotpixel(int(x),int(y));
		}
	
		x += xinc;
		y += yinc;
	}
	
}

void solid_dda(int x1,int y1,int x2,int y2){
	glPointSize(2);
	normaldda(x1,y1,x2,y2);
	glPointSize(1);
}


void render (){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	gluOrtho2D(-250,250,-250,250);
	glColor3f(1,1,1);
	normaldda(-60,-150,60,-150);
	normaldda(-60,-150,-20,-110);
	normaldda(60,-150,20,-110);
	normaldda(-160,-110,-20,-110);
	normaldda(20,-110,160,-110);
	normaldda(-160,-110,-160,100);
	normaldda(160,-110,160,100);
	normaldda(-160,100,160,100);
	normaldda(-120,-70,120,-70);
	normaldda(120,-70,120,60);
	normaldda(120,60,-120,60);
	normaldda(-120,60,-120,-70);
	normaldda(-120,-70,-60,0);
	normaldda(-60,0,0,-70);
	normaldda(0,-70,90,30);
	normaldda(90,30,120,-70);
	
	
	
	
	glFlush();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("DDA");
    glutDisplayFunc(render);
//    glutMouseFunc(mouse);
//    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
