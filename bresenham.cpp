# include<GL/gl.h>
# include<GL/freeglut.h>
# include<bits/stdc++.h>
# include<cstdlib>

using namespace std;

void solid_line(int xi,int yi,int xf,int yf){
	int dx = xf-xi;
	int dy = yf-yi;
	if (dx<0) dx = -dx;
	if(dy<0) dy = -dy;
	int x = xi;
	int y = yi;
	int P;
	int x_change = xi>xf ? -1:1;
	int y_change = yi>yf ? -1:1;
	 glVertex2i(x,y);
	if(dx ==0){
		glBegin(GL_POINTS);
		for(int i=1;i<dy;i++){
			 y += y_change;
			 glVertex2i(x,y);
			 
		}
		glEnd();
		return;
	}
	if(dy ==0){
		glBegin(GL_POINTS);
		for(int i=1;i<dx;i++){
			 x += x_change;
			 glVertex2i(x,y);
			 
		}
		glEnd();
		return;
	}
	glBegin(GL_POINTS);
	if(dx>dy){
		P = 2 * dy-dx;
		for(int i=0;i<dx;i++){
			if(P>0){
			y += y_change;
			P = P + 2*(dy-dx);
		
			}
			else{
			P = P + 2 *dy;
			}
			x += x_change;
			glVertex2i(x,y);
		}
		
	}
	else{
			P = 2 * dx-dy;
		for(int i=0;i<dy;i++){
			if(P>0){
			x += x_change;
			P = P + 2*(dx-dy);
		
		}
		else{
			P = P + 2 *dx;
		}
			 y += y_change;
			glVertex2i(x,y);
		}
	
	}
		glEnd();
}

void dotted_line(int xi,int yi,int xf,int yf){
	int dx = xf-xi;
	int dy = yf-yi;
	if (dx<0) dx = -dx;
	if(dy<0) dy = -dy;
	int x = xi;
	int y = yi;
	int P;
	int x_change = xi>xf ? -1:1;
	int y_change = yi>yf ? -1:1;
	 glVertex2i(x,y);
	if(dx ==0){
		glBegin(GL_POINTS);
		for(int i=1;i<dy;i++){
			 y += y_change;
			if(i% 10 ==0){
				 glVertex2i(x,y);
			}
			 
		}
		glEnd();
		return;
	}
	if(dy ==0){
		glBegin(GL_POINTS);
		for(int i=1;i<dx;i++){
			 x += x_change;
			 	if(i% 10 ==0){
				 glVertex2i(x,y);
			}
			 
		}
		glEnd();
		return;
	}
	glBegin(GL_POINTS);
	if(dx>dy){
		P = 2 * dy-dx;
		for(int i=0;i<dx;i++){
			if(P>0){
			y += y_change;
			P = P + 2*(dy-dx);
		
			}
			else{
			P = P + 2 *dy;
			}
			x += x_change;
				if(i% 10 ==0){
				 glVertex2i(x,y);
			}
		}
		
	}
	else{
			P = 2 * dx-dy;
		for(int i=0;i<dy;i++){
			if(P>0){
			x += x_change;
			P = P + 2*(dx-dy);
		
		}
		else{
			P = P + 2 *dx;
		}
			 y += y_change;
				if(i% 10 ==0){
				 glVertex2i(x,y);
			}
		}
	
	}
		glEnd();
}

void dashed_line(int xi,int yi,int xf,int yf){
	int dx = xf-xi;
	int dy = yf-yi;
	if (dx<0) dx = -dx;
	if(dy<0) dy = -dy;
	int x = xi;
	int y = yi;
	int P;
	int x_change = xi>xf ? -1:1;
	int y_change = yi>yf ? -1:1;
	 glVertex2i(x,y);
	 
	if(dx ==0){
		glBegin(GL_POINTS);
		for(int i=1;i<dy;i++){
			 y += y_change;
			 if(i%20<10){
			 	glVertex2i(x,y);
			 }
			 
		}
		glEnd();
		return;
	}
	if(dy ==0){
		glBegin(GL_POINTS);
		for(int i=1;i<dx;i++){
			 x += x_change;
			 if(i%20<10){
			 	glVertex2i(x,y);
			 }
			 
		}
		glEnd();
		return;
	}
	glBegin(GL_POINTS);
	if(dx>dy){
		P = 2 * dy-dx;
		for(int i=0;i<dx;i++){
			if(P>0){
			y += y_change;
			P = P + 2*(dy-dx);
		
			}
			else{
			P = P + 2 *dy;
			}
			x += x_change;
			if(i%20<10){
			 	glVertex2i(x,y);
			 }
		}
		
	}
	else{
			P = 2 * dx-dy;
		for(int i=0;i<dy;i++){
			if(P>0){
			x += x_change;
			P = P + 2*(dx-dy);
		
		}
		else{
			P = P + 2 *dx;
		}
			 y += y_change;
			if(i%20<10){
			 	glVertex2i(x,y);
			 }
		}
	
	}
		glEnd();
}


void render (){
	glClearColor(0,0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,1,1);
	gluOrtho2D(0,500,0,500);
	dashed_line(100,100,100,400);
	dashed_line(100,400,400,400);
	dashed_line(400,400,400,100);
	dashed_line(400,100,100,100);
	dashed_line(100,250,250,400);
	dashed_line(250,400,400,250);
	dashed_line(400,250,250,100);
	dashed_line(250,100,100,250);
	dashed_line(175,325,325,325);
	dashed_line(325,325,325,175);
	dashed_line(325,175,175,175);
	dashed_line(175,175,175,325);
	
	
	glEnd();
	glFlush();
	
}

int main( int argc , char ** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(500,500);

	glutCreateWindow("Bresehnam");
	glutDisplayFunc(render);
	glutMainLoop();
	return 0;
	
}
