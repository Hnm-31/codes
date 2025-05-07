#include <GL/glut.h>
#include <cmath>
float angle = 0.0f; // Rotation angle of windmill blades

void init() {
    glClearColor(0.7f, 0.9f, 1.0f, 1.0f); // Light sky blue background
   
    gluOrtho2D(-1, 1, -1, 1); // 2D orthographic projection
     glMatrixMode(GL_PROJECTION);
}

void drawPole() {
    glColor3f(0.4f, 0.3f, 0.2f); // Brown pole
    glBegin(GL_POLYGON);
        glVertex2f(-0.02f, -0.6f);
        glVertex2f(0.02f, -0.6f);
        glVertex2f(0.02f, 0.2f);
        glVertex2f(-0.02f, 0.2f);
    glEnd();
}

void drawBlade(float rotation_angle) {
    glPushMatrix();
    glRotatef(rotation_angle, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f); // White blades
    // One blade
    glBegin(GL_POLYGON);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(0.02f, 0.3f);
        glVertex2f(-0.02f, 0.3f);
    glEnd();
    glPopMatrix();
}
void drawWindmill() {
    glPushMatrix();
    glTranslatef(0.0f, 0.2f, 0.0f); // Move to top of pole (pivot point)
    drawBlade(angle);       // Blade 1
    drawBlade(angle + 120); // Blade 2
    drawBlade(angle + 240); // Blade 3
    glPopMatrix();
}
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawPole();
    drawWindmill();
    glFlush();
}
void timer(int) {
    angle += 2.0f;
    if (angle > 360.0f) angle -= 360.0f;
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0); // ~60 fps
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Rotating Windmill - OpenGL");
    init();
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
