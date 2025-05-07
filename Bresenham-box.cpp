#include <GL/glut.h>
#include <cmath>
#include <iostream>
using namespace std;

// Window size globals
int winWidth = 600, winHeight = 600;

// Variables for mouse click count and P, Q coordinates
int clickCount = 0;
bool shapeDrawn = false;
int px, py, qx, qy;

// Draw a dashed line from (xi, yi) to (xf, yf) using Bresenham's algorithm
void dashed_line(int xi, int yi, int xf, int yf) {
    int dx = abs(xf - xi), dy = abs(yf - yi);
    int x = xi, y = yi;
    int x_change = (xi > xf) ? -1 : 1;
    int y_change = (yi > yf) ? -1 : 1;
    int P;
    
    glBegin(GL_POINTS);
    if (dx > dy) {
        P = 2 * dy - dx;
        for (int i = 0; i <= dx; i++) {
            if (i % 20 < 10)  // Draw for half the time, skip for the other half
                glVertex2i(x, y);
            x += x_change;
            if (P > 0) {
                y += y_change;
                P += 2 * (dy - dx);
            } else {
                P += 2 * dy;
            }
        }
    } else {
        P = 2 * dx - dy;
        for (int i = 0; i <= dy; i++) {
            if (i % 20 < 10)
                glVertex2i(x, y);
            y += y_change;
            if (P > 0) {
                x += x_change;
                P += 2 * (dx - dy);
            } else {
                P += 2 * dx;
            }
        }
    }
    glEnd();
}

// Draw the figure based solely on points P and Q.
// This will draw an outer square between P & Q, an inscribed (rotated) square
// by connecting the midpoints of the outer square's sides, and an inner square.
void draw_figure_from_PQ(int px, int py, int qx, int qy) {
    int left = min(px, qx);
    int right = max(px, qx);
    int bottom = min(py, qy);
    int top = max(py, qy);
    int midX = (left + right) / 2;
    int midY = (bottom + top) / 2;

    // Outer square
    dashed_line(left, bottom, left, top);
    dashed_line(left, top, right, top);
    dashed_line(right, top, right, bottom);
    dashed_line(right, bottom, left, bottom);

    // Rotated square (diamond) corners
    int topMid[2] = { midX, top };
    int rightMid[2] = { right, midY };
    int bottomMid[2] = { midX, bottom };
    int leftMid[2] = { left, midY };

    // Draw diamond
    dashed_line(topMid[0], topMid[1], rightMid[0], rightMid[1]);
    dashed_line(rightMid[0], rightMid[1], bottomMid[0], bottomMid[1]);
    dashed_line(bottomMid[0], bottomMid[1], leftMid[0], leftMid[1]);
    dashed_line(leftMid[0], leftMid[1], topMid[0], topMid[1]);

    // Center of diamond
    int cx = midX;
    int cy = midY;

    // Inner square by scaling diamond vertices toward center
   // Get midpoints of edges of diamond (Square 2)
int mid1[2] = { (topMid[0] + rightMid[0]) / 2, (topMid[1] + rightMid[1]) / 2 };
int mid2[2] = { (rightMid[0] + bottomMid[0]) / 2, (rightMid[1] + bottomMid[1]) / 2 };
int mid3[2] = { (bottomMid[0] + leftMid[0]) / 2, (bottomMid[1] + leftMid[1]) / 2 };
int mid4[2] = { (leftMid[0] + topMid[0]) / 2, (leftMid[1] + topMid[1]) / 2 };

// Draw inner square (aligned with Square 2)
dashed_line(mid1[0], mid1[1], mid2[0], mid2[1]);
dashed_line(mid2[0], mid2[1], mid3[0], mid3[1]);
dashed_line(mid3[0], mid3[1], mid4[0], mid4[1]);
dashed_line(mid4[0], mid4[1], mid1[0], mid1[1]);

}


// Display callback: clears the screen and draws the figure (if available)
void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1, 1, 1);
    if (shapeDrawn)
        draw_figure_from_PQ(px, py, qx, qy);
    glFlush();
}

// Mouse click callback: transform screen coordinates to our orthographic system and set P, Q.
void mouseClick(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Transform from window coordinates to OpenGL coordinates.
        // Our coordinate system is centered at (0,0):
        int glX = x - winWidth / 2;
        int glY = (winHeight - y) - winHeight / 2;  // Invert y because window coordinates start at top
        if (clickCount == 0) {
            px = glX;
            py = glY;
            clickCount = 1;
            cout << "P set at (" << px << ", " << py << ")\n";
        } else if (clickCount == 1) {
            qx = glX;
            qy = glY;
            clickCount = 2;
            shapeDrawn = true;
            cout << "Q set at (" << qx << ", " << qy << ")\n";
        }
        glutPostRedisplay();
    }
}

// Keyboard callback: if 'r' or 'R' is pressed, reset the figure so you can draw a new one.
void keyboard(unsigned char key, int x, int y) {
    if (key == 'r' || key == 'R') {
        clickCount = 0;
        shapeDrawn = false;
        glClear(GL_COLOR_BUFFER_BIT);
        glutPostRedisplay();
        cout << "Canvas reset. Click to set new P and Q.\n";
    }
}

// Initialization: sets the clear color and defines an orthographic projection centered at (0,0)
void init() {
    glClearColor(0, 0, 0, 0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-winWidth / 2, winWidth / 2, -winHeight / 2, winHeight / 2);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth, winHeight);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Interactive Dashed Line Figure");
    init();
    glutDisplayFunc(display);
    glutMouseFunc(mouseClick);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}