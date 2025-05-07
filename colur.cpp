#include <GL/glut.h>             // OpenGL Utility Toolkit for rendering and interaction
#include <bits/stdc++.h>         // Includes all standard C++ libraries (used here for M_PI)

const int Height = 500, Width = 500;  // Window dimensions
int CenterX = 250, CenterY = 250;     // Center point of the shape

float angle = 0.0f;              // Rotation angle in radians

float bgcolor[3] = {1.0, 1.0, 1.0};   // Background color (white)
float fillcolor[3] = {0.0, 0.0, 1.0}; // Fill color (blue)

int clickCount = 0;              // Tracks number of mouse clicks

// Sets a pixel at (x, y) with fill color
void setPixel(int x, int y) {
    glColor3fv(fillcolor);      // Set drawing color
    glBegin(GL_POINTS);         // Begin drawing a point
    glVertex2i(x, y);           // Specify the pixel
    glEnd();                    // End drawing
    glFlush();                  // Force execution of OpenGL commands
}

// Reads pixel color at (x, y) into the color array
void getPixelColor(int x, int y, float color[3]) {
    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, color); // Read pixel color
}

// Recursive 4-connected seed fill starting from (x, y)
void seedfill(int x, int y) {
    float color[3];
    getPixelColor(x, y, color); // Get current pixel color
    // Check if pixel is unfilled (matches background color)
    if (color[0] == bgcolor[0] && color[1] == bgcolor[1] && color[2] == bgcolor[2]) {
        setPixel(x, y);         // Fill the pixel
        seedfill(x + 1, y);     // Fill right
        seedfill(x - 1, y);     // Fill left
        seedfill(x, y + 1);     // Fill up
        seedfill(x, y - 1);     // Fill down
    }
}

// Draws a plus shape (12-sided polygon)
void drawPlus() {
    int shape[12][2] = {        // Coordinates of the plus shape
        {-30, 60}, {30, 60}, {30, 30},
        {60, 30}, {60, -30}, {30, -30},
        {30, -60}, {-30, -60}, {-30, -30},
        {-60, -30}, {-60, 30}, {-30, 30}
    };

    glColor3f(0, 0, 0);         // Set color to black for outline
    glBegin(GL_LINE_LOOP);     // Begin drawing a closed loop
    for (int i = 0; i < 12; i++) {
        float x = shape[i][0];  // Original x
        float y = shape[i][1];  // Original y

        // Apply 2D rotation
        float xr = x * cos(angle) - y * sin(angle);
        float yr = x * sin(angle) + y * cos(angle);

        glVertex2f(CenterX + xr, CenterY + yr); // Add rotated point to shape
    }
    glEnd();                    // End drawing
    glFlush();                  // Render to screen
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);  // Clear the screen
    drawPlus();                    // Draw the plus shape

    if (clickCount == 2) {         // After second click
        seedfill(CenterX, CenterY); // Start filling from center
    }

    glFlush();                     // Render everything
}

// Mouse click event handler
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) { // On left click
        clickCount++;              // Increase click count
        if (clickCount == 1) {
            angle = 45.0 * M_PI / 180.0; // Convert 45° to radians and rotate
        }
    }
}

// Initialization routine
void init() {
    glClearColor(1, 1, 1, 1);      // Set background color (white)
    gluOrtho2D(0, Height, 0, Width); // Set orthographic projection
    glMatrixMode(GL_PROJECTION);  // Set projection matrix mode
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);        // Initialize GLUT
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB); // Single buffer, RGB mode
    glutInitWindowSize(Width, Height); // Set window size
    glutCreateWindow("Plus Shape - Click to Rotate and Fill"); // Create window
    init();                       // Initialize rendering context
    glutDisplayFunc(display);     // Set display callback
    glutMouseFunc(mouse);         // Set mouse callback
    glutMainLoop();               // Start event processing loop
    return 0;                     // Exit
}