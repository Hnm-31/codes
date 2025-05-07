#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

vector<vector<float>> triangle = {
    {100, 200, 1},
    {200, 100, 1},
    {150, 200, 1}
};

vector<vector<float>> result = triangle;

void drawShape(const vector<vector<float>> shape) {
    glBegin(GL_LINE_LOOP);
    for (int i = 0; i < shape.size(); i++) {
        glVertex2f(shape[i][0], shape[i][1]);
    }
    glEnd();
}

vector<vector<float>> multiply(vector<vector<float>>a, vector<vector<float>>b) {

    vector<vector<float>> res(a.size(), vector<float>(b[0].size(), 0));
    for (int i = 0; i < a.size(); i++)
        for (int j = 0; j < b[0].size(); j++)
            for (int k = 0; k < a[0].size(); k++)
                res[i][j] += a[i][k] * b[k][j];
    return res;
}


void translation(float tx, float ty) {
    vector<vector<float>> tMat = {
        {1, 0, 0},
        {0, 1, 0},
        {tx, ty, 1}
    };
    result = multiply(triangle, tMat);
}

void scaling(float sx, float sy) {
    vector<vector<float>> sMat = {
        {sx, 0, 0},
        {0, sy, 0},
        {0, 0, 1}
    };
    result = multiply(triangle, sMat);
}

void rotation(float angle) {
    float rad = angle * M_PI / 180;
    vector<vector<float>> rMat = {
        {cos(rad), sin(rad), 0},
        {-sin(rad), cos(rad), 0},
        {0, 0, 1}
    };
    result = multiply(triangle, rMat);
}


// Add this shearing function
void shearing(float shx, float shy) {
    vector<vector<float>> shMat = {
        {1, shx, 0},
        {shy, 1, 0},
        {0, 0, 1}
    };
    result = multiply(triangle, shMat);
}

void reflection(int choice) {
    vector<vector<float>> rMat;

    switch (choice) {
        case 1: // Reflect across X-axis
            rMat = {
                {1, 0, 0},
                {0, -1, 0},
                {0, 0, 1}
            };
            break;
        case 2: // Reflect across Y-axis
            rMat = {
                {-1, 0, 0},
                {0, 1, 0},
                {0, 0, 1}
            };
            break;
        case 3: // Reflect across origin
            rMat = {
                {-1, 0, 0},
                {0, -1, 0},
                {0, 0, 1}
            };
            break;
        default:
            cout << "Invalid choice\n";
            return;
    }

    result = multiply(triangle, rMat);
}

void render(){
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluOrtho2D(-300, 300, -300, 300);

    // Draw axes
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_LINES);
    glVertex2i(-300, 0); glVertex2i(300, 0);
    glVertex2i(0, -300); glVertex2i(0, 300);
    glEnd();

    // Draw transformed triangle
    glColor3f(1, 0, 0);
    drawShape(result);

    glFlush();
}

void Menu(int option) {
    switch (option) {
        case 1: {
            float tx, ty;
            cout << "Enter tx and ty: ";
            cin >> tx >> ty;
            translation(tx, ty);
            break;
        }
        case 2: {
            float sx, sy;
            cout << "Enter sx and sy: ";
            cin >> sx >> sy;
            scaling(sx, sy);
            break;
        }
        case 3: {
            float angle;
            cout << "Enter angle (degrees): ";
            cin >> angle;
            rotation(angle);
            break;
        }
        case 4:
            result = triangle; // Reset
            break;
        case 5:
            float sh_x, sh_y;
            cout << "Enter shear values (shx and shy): ";
            cin >> sh_x >> sh_y;
            shearing(sh_x, sh_y);
            break;
            
        case 6:
        
            int refl_choice;
            cout << "Reflect across:\n1. X-axis\n2. Y-axis\n3. Origin\nEnter choice: ";
            cin >> refl_choice;
            reflection(refl_choice);
            break;
        
        
        case 7:
            exit(0);
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(600, 600);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("2D Transformations Using Matrices");
    glClearColor(1, 1, 1, 1);
    glutDisplayFunc(render);

    glutCreateMenu(Menu);
    glutAddMenuEntry("1. Translate", 1);
    glutAddMenuEntry("2. Scale", 2);
    glutAddMenuEntry("3. Rotate", 3);
    glutAddMenuEntry("4. Reset", 4);
    glutAddMenuEntry("5.Shear",5);
    glutAddMenuEntry("6. Reflect", 6);
    glutAddMenuEntry("6. Exit", 7);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    glutMainLoop();
    return 0;
}