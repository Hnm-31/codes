#include <iostream>
#include <cmath>
#include <GL/glut.h>

using namespace std;

float xd1, yd1, xd2, yd2;
int ymax = 100, ymin = -100, xmax = 100, xmin = -100;
static int p = 0;

float round_value(float v) {
    return floor(v + 0.5);
}

void plotpoint(float a, float b) {
    glBegin(GL_POINTS);
    glVertex2f(a, b);
    glEnd();
}

void dda(float X1, float Y1, float X2, float Y2) {
    float dx = X2 - X1;
    float dy = Y2 - Y1;
    int steps = fabs(dx) > fabs(dy) ? fabs(dx) : fabs(dy);

    float xinc = dx / steps;
    float yinc = dy / steps;

    float x = X1;
    float y = Y1;

    plotpoint(x, y);

    for (int k = 0; k < steps; k++) {
        x += xinc;
        y += yinc;
        plotpoint(round_value(x), round_value(y));
    }

    glFlush();
}

int computeOutCode(int x, int y) {
    int code = 0;
    if (y > ymax) code |= 8;
    if (y < ymin) code |= 4;
    if (x > xmax) code |= 2;
    if (x < xmin) code |= 1;
    return code;
}

void cohen(float x1, float y1, float x2, float y2) {
    int c1 = computeOutCode(x1, y1);
    int c2 = computeOutCode(x2, y2);
    float m = (x2 != x1) ? (y2 - y1) / (x2 - x1) : 0;

    while ((c1 | c2) != 0) {
        if ((c1 & c2) != 0) return;

        int c = c1 ? c1 : c2;
        float xi = (c == c1) ? x1 : x2;
        float yi = (c == c1) ? y1 : y2;
        float x, y;

        if (c & 8) {
            y = ymax;
            x = xi + (ymax - yi) / m;
        } else if (c & 4) {
            y = ymin;
            x = xi + (ymin - yi) / m;
        } else if (c & 2) {
            x = xmax;
            y = yi + m * (xmax - xi);
        } else if (c & 1) {
            x = xmin;
            y = yi + m * (xmin - xi);
        }

        if (c == c1) {
            xd1 = x;
            yd1 = y;
            c1 = computeOutCode(xd1, yd1);
        } else {
            xd2 = x;
            yd2 = y;
            c2 = computeOutCode(xd2, yd2);
        }
    }

    p++;
    glutPostRedisplay();
}

void myKey(unsigned char ch, int x, int y) {
    if (ch == 'c' || ch == 'C') {
        cohen(xd1, yd1, xd2, yd2);
        glFlush();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0, 0.0, 0.0);  // Red for clipping window
    dda(xmin, ymin, xmax, ymin);
    dda(xmax, ymin, xmax, ymax);
    dda(xmax, ymax, xmin, ymax);
    dda(xmin, ymax, xmin, ymin);

    if (p > 0)
        glColor3f(0.5, 1.0, 0.5);  // Light green for clipped line
    else
        glColor3f(0.0, 0.0, 1.0);  // Blue for initial line

    dda(xd1, yd1, xd2, yd2);
    glFlush();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 0.0);  // White background
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(2);
    gluOrtho2D(-320, 320, -240, 240); // Viewport setup
    glFlush();
}

int main(int argc, char **argv) {
    cout << "Window coordinates are (-100, 100, -100, 100)\n";
    cout << "Enter coordinates of the line (X1 Y1 X2 Y2):\n";

    cout << "X1: "; cin >> xd1;
    cout << "Y1: "; cin >> yd1;
    cout << "X2: "; cin >> xd2;
    cout << "Y2: "; cin >> yd2;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Cohen-Sutherland Line Clipping - C++ Version");
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(myKey);
    glutMainLoop();

    return 0;
}
