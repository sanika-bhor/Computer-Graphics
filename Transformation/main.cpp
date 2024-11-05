#include <iostream>
#include <GL/glut.h>
#include <cmath>

using namespace std;

class Transformation {
public:
    float matrix[3][3];

    // Constructor to initialize identity matrix
    Transformation() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                matrix[i][j] = (i == j) ? 1 : 0;
    }

    // Overloading * operator for matrix multiplication
    Transformation operator*(const Transformation& t) {
        Transformation result;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                result.matrix[i][j] = 0;
                for (int k = 0; k < 3; k++) {
                    result.matrix[i][j] += matrix[i][k] * t.matrix[k][j];
                }
            }
        }
        return result;
    }
};

int input[3][10], output[3][10];
int v;
float angle, sx, sy, xf, yf;
int tx, ty;

void multiplyMatrix(const Transformation& t, int output[3][10], int input[3][10]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < v; j++) {
            output[i][j] = 0;
            for (int k = 0; k < 3; k++) {
                output[i][j] += t.matrix[i][k] * input[k][j];
            }
        }
    }
}

int ROUND_Num(float a) {
    return static_cast<int>(a + 0.5);
}

void draw_objects(int xa, int ya, int xb, int yb) {
    int dx = xb - xa, dy = yb - ya;
    int steps = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    float xinc = dx / (float)steps, yinc = dy / (float)steps;
    float x = xa, y = ya;

    glVertex2d(x, y);
    for (int i = 0; i < steps; i++) {
        x += xinc;
        y += yinc;
        glVertex2d(ROUND_Num(x), ROUND_Num(y));
    }
}

void LineDDA() {
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_LINES);  // Change to GL_LINES to connect vertices

    // Draw original shape
    for (int i = 0; i < v; i++) {
        draw_objects(input[0][i], input[1][i], input[0][(i + 1) % v], input[1][(i + 1) % v]);
    }

    // Draw transformed shape
    for (int i = 0; i < v; i++) {
        draw_objects(output[0][i], output[1][i], output[0][(i + 1) % v], output[1][(i + 1) % v]);
    }

    glEnd();
    glFlush();
}

void performTransformation(int choice) {
    Transformation t;  // Create a new transformation matrix

    switch (choice) {
        case 1: { // Rotation
            cout << "\nEnter the rotation angle (in degrees): ";
            cin >> angle;
            cout << "Enter the pivot point (xf yf): ";
            cin >> xf >> yf;

            float radians = angle * (M_PI / 180.0);
            t.matrix[0][0] = cos(radians);
            t.matrix[0][1] = -sin(radians);
            t.matrix[0][2] = xf * (1 - cos(radians)) + yf * sin(radians);
            t.matrix[1][0] = sin(radians);
            t.matrix[1][1] = cos(radians);
            t.matrix[1][2] = yf * (1 - cos(radians)) - xf * sin(radians);
            t.matrix[2][2] = 1; // Keep the homogeneous coordinate
            break;
        }
        case 2: { // Scaling
            cout << "\nEnter the scaling factors (sx sy): ";
            cin >> sx >> sy;
            cout << "Enter the fixed point (xf yf): ";
            cin >> xf >> yf;

            t.matrix[0][0] = sx;
            t.matrix[1][1] = sy;
            t.matrix[0][2] = xf * (1 - sx);
            t.matrix[1][2] = yf * (1 - sy);
            t.matrix[2][2] = 1; // Keep the homogeneous coordinate
            break;
        }
        case 3: { // Translation
            cout << "\nEnter the translation values (tx ty): ";
            cin >> tx >> ty;

            t.matrix[0][2] = tx;
            t.matrix[1][2] = ty;
            t.matrix[2][2] = 1; // Keep the homogeneous coordinate
            break;
        }
        default:
            cout << "Invalid choice!";
            return;
    }

    // Apply the transformation
    multiplyMatrix(t, output, input);

    // Print transformed output matrix
    cout << "\nTransformed Output Matrix:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < v; j++) {
            cout << output[i][j] << "\t";
        }
        cout << "\n";
    }
}

int main(int argc, char** argv) {
    cout << "\nEnter the number of vertices (up to 10): ";
    cin >> v;
    if (v > 10) {
        cout << "Max vertices exceeded (10). Exiting." << endl;
        return 1; // Exit if the number of vertices exceeds the limit
    }

    for (int i = 0; i < v; i++) {
        cout << "Enter value of x: ";
        cin >> input[0][i];
        cout << "Enter value of y: ";
        cin >> input[1][i];
        input[2][i] = 1; // Homogeneous coordinate
    }

    cout << "\n\nInput Matrix:\n";
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < v; j++) {
            cout << input[i][j] << "\t";
        }
        cout << "\n";
    }

    cout << "\nChoose Transformation Type:\n1. Rotation\n2. Scaling\n3. Translation\n";
    int choice;
    cin >> choice;

    performTransformation(choice);

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Transformation Program");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
    glutDisplayFunc(LineDDA);
    glutMainLoop();

    return 0;
}
