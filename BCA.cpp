#include <GL/glut.h>
#include <iostream>
#include <cmath>

int centerX, centerY, R;
int clickCount = 0;
bool readyToDraw = false;

void plotpixel(int x, int y, int xc, int yc) {
    glBegin(GL_POINTS);
    glVertex2i(x + xc, y + yc);
    glVertex2i(y + xc, x + yc);
    glVertex2i(y + xc, -x + yc);
    glVertex2i(x + xc, -y + yc);
    glVertex2i(-y + xc, -x + yc);
    glVertex2i(-x + xc, -y + yc);
    glVertex2i(-y + xc, x + yc);
    glVertex2i(-x + xc, y + yc);
    glEnd();
}

void circle(int xc, int yc, int r) {
    int x = 0, y = r;
    int p = 3 - 2 * r;
    while (x <= y) {
        plotpixel(x, y, xc, yc);
        if (p >= 0) {
            y--;
            p = p + 4 * (x - y) + 10;
        } else {
            p = p + 4 * x + 6;
        }
        x++;
    }
}

void bangle() {
    int n = 31;
    float angleStep = 2 * 3.14 / n;
    int r = R / 10;

    for (int i = 0; i < n; i++) {
        float theta = i * angleStep;
        int x = R * cos(theta);
        int y = R * sin(theta);
        circle(centerX + 1.14 * x, centerY + 1.14 * y, r);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (readyToDraw) {
        circle(centerX, centerY, R);
        circle(centerX, centerY, R - 10);
        bangle();
    }
    glFlush();
}

void mouse(int button, int state, int x, int y) {
    if (!readyToDraw && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        y = 500 - y;  // Convert to OpenGL coordinate system
        if (clickCount == 0) {
            centerX = x - 250;
            centerY = y - 250;
            clickCount++;
        } else if (clickCount == 1) {
            int x2 = x - 250;
            int y2 = y - 250;
            R = std::sqrt((x2 - centerX) * (x2 - centerX) + (y2 - centerY) * (y2 - centerY));
            readyToDraw = true;
            glutPostRedisplay();
        }
    }
}

void keyboard(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R') {
        // Reset everything
        readyToDraw = false;
        clickCount = 0;
        glutPostRedisplay();
        std::cout << "Reset: Click again to choose center and radius.\n";
    }
}

void init() {
    glClearColor(0, 0, 0, 0);
    glColor3f(1, 1, 0);
    glPointSize(2.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-250, 250, -250, 250);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Bangle Drawing with Mouse and Reset");

    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
