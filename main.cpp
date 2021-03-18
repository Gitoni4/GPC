#include <GL/glut.h>

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <algorithm>

// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

using namespace std;

const float PI_CONST = (float) M_PI;

// concoida lui Nicomede (concoida dreptei)
// $x = a + b \cdot cos(t), y = a \cdot tg(t) + b \cdot sin(t)$. sau
// $x = a - b \cdot cos(t), y = a \cdot tg(t) - b \cdot sin(t)$. unde
// $t \in (-\pi / 2, \pi / 2)$
void Display1() {
    double xmax, ymax, xmin, ymin;
    double a = 1, b = 2;
    double pi = 4 * atan(1);
    double ratia = 0.05;

    // calculul valorilor maxime/minime ptr. x si y
    // aceste valori vor fi folosite ulterior la scalare
    xmax = a - b - 1;
    xmin = a + b + 1;
    ymax = ymin = 0;
    for (double t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
        double x1, y1, x2, y2;
        x1 = a + b * cos(t);
        xmax = (xmax < x1) ? x1 : xmax;
        xmin = (xmin > x1) ? x1 : xmin;

        x2 = a - b * cos(t);
        xmax = (xmax < x2) ? x2 : xmax;
        xmin = (xmin > x2) ? x2 : xmin;

        y1 = a * tan(t) + b * sin(t);
        ymax = (ymax < y1) ? y1 : ymax;
        ymin = (ymin > y1) ? y1 : ymin;

        y2 = a * tan(t) - b * sin(t);
        ymax = (ymax < y2) ? y2 : ymax;
        ymin = (ymin > y2) ? y2 : ymin;
    }

    xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
    ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

    // afisarea punctelor propriu-zise precedata de scalare
    glColor3f(1, 0.1, 0.1); 
    glBegin(GL_LINE_STRIP);
    for (double t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
        double x1, y1, x2, y2;
        x1 = (a + b * cos(t)) / xmax;
        x2 = (a - b * cos(t)) / xmax;
        y1 = (a * tan(t) + b * sin(t)) / ymax;
        y2 = (a * tan(t) - b * sin(t)) / ymax;

        glVertex2f(x1, y1);
    }
    glEnd();

    glBegin(GL_LINE_STRIP);
    for (double t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
        double x1, y1, x2, y2;
        x1 = (a + b * cos(t)) / xmax;
        x2 = (a - b * cos(t)) / xmax;
        y1 = (a * tan(t) + b * sin(t)) / ymax;
        y2 = (a * tan(t) - b * sin(t)) / ymax;

        glVertex2f(x2, y2);
    }
    glEnd();
}

// graficul functiei
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$,
void Display2() {
    double pi = 4 * atan(1);
    double xmax = 8 * pi;
    double ymax = exp(1.1);
    double ratia = 0.05;

    // afisarea punctelor propriu-zise precedata de scalare
    glColor3f(1, 0.1, 0.1); 
    glBegin(GL_LINE_STRIP);
    for (double x = 0; x < xmax; x += ratia) {
        double x1, y1;
        x1 = x / xmax;
        y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

        glVertex2f(x1, y1);
    }
    glEnd();
}

float nearestIntDistance(float x) {

    float lowerBound = x - (int)x;
    float upperBound = (int)x + 1 - x;

    if (lowerBound < upperBound)
        return lowerBound;

    return upperBound;

}

void Display3() {
    float minX = 0.0;
    float maxX = 100.0;

    float ratio = 0.05;

    glColor3f(1, 0.1, 0.1);
    glBegin(GL_LINE_STRIP);

    glVertex2f(0.0, 1.0);

    for (float x = minX; x <= maxX; x += ratio)
    {
        glVertex2f(x / 20.0, nearestIntDistance(x) / x);
    }

    glEnd();

}

void Display4() {
    float a = 0.3, b = 0.2;

    float ratio = 0.05;
    float pi = PI_CONST;
    float minT = (-1) * pi;
    float maxT = pi;

    glColor3f(1, 0.1, 0.1); 
    glBegin(GL_LINE_STRIP);

    for (float t = minT + ratio; t < maxT; t += ratio) {
        auto cosOfT = cosf(t);
        float x = 2.0 * (a * cosOfT + b) * cosOfT;
        float y = 2.0 * (a * cosOfT + b) * sinf(t);

        glVertex2f(x - 0.2, y);
    }

    glEnd();
}

void Display5() {

}

void Display6() {
    float a = 0.1, b = 0.2;

    float ratio = 0.01;
    float minT = -15.0;
    float maxT = 15.0;

    glColor3f(1, 0.1, 0.1); 

    glBegin(GL_LINE_STRIP);

    for (float t = minT; t < maxT; t += ratio) {
        float x = a * t - b * sinf(t);
        float y = a - b * cosf(t);

        glVertex2f(x, y);
    }

    glEnd();
}

void Display7() {
    float r = 0.3, R = 0.1;

    float ratio = 0.05;
    float minT = 0.0;
    float maxT = PI_CONST * 2.0;

    glColor3f(1, 0.1, 0.1); 
    glBegin(GL_LINE_STRIP);

    for (float t = minT; t <= maxT; t += ratio) {
        float x = (R + r) * cosf(r / R * t) - r * cos(t + r / R * t);
        float y = (R + r) * sinf(r / R * t) - r * sin(t + r / R * t);

        glVertex2f(x, y);
    }

    glEnd();
}

void Display8() {
    float r = 0.3, R = 0.1;

    float ratio = 0.05;
    float minT = 0.0;
    float maxT = PI_CONST * 2.0;

    glColor3f(1, 0.1, 0.1); 
    glBegin(GL_LINE_STRIP);

    for (float t = minT; t <= maxT; t += ratio) {
        float x = (R - r) * cosf(r / R * t) - r * cos(t - r / R * t);
        float y = (R - r) * sinf(r / R * t) - r * sin(t - r / R * t);

        glVertex2f(x, y);
    }

    glEnd();
}

void Display9() {
    float a = 0.4;
    float ratio = 0.003;

    float pi = PI_CONST;
    float minT = -(pi / 4.0);
    float maxT = (pi / 4.0);

    glColor3f(1, 0.1, 0.1); 
    glBegin(GL_LINE_STRIP);

    for (float t = minT; t < maxT; t += ratio) {
        float r = a * sqrtf(2 * cosf(2 * t));

        float x = r * cosf(t);
        float y = r * sinf(t);
        glVertex2f(x, y);
    }

//    glEnd();
//    glBegin(GL_LINE_STRIP);
    for (float t = maxT - ratio; t > minT; t -= ratio) {
        float r = -a * sqrtf(2 * cosf(2 * t));

        float x = r * cosf(t);
        float y = r * sinf(t);
        glVertex2f(x, y);
    }

    glEnd();
}

void Display0() {
    float a = 0.02;
    float ratio = 0.05;

    float maxT = 50.0;

    auto e = static_cast<float>(M_E);

    glColor3f(1, 0.1, 0.1); 
    glBegin(GL_LINE_STRIP);

    for (float t = ratio; t < maxT; t += ratio) {
        float r = a * powf(e, 1.0 + t);
        float x = r * cosf(t);
        float y = r * sinf(t);

        glVertex2f(x, y);
    }

    glEnd();
}

void Init(void) {

    glClearColor(1.0, 1.0, 1.0, 1.0);

    glLineWidth(1);

//   glPointSize(4);

    glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
    glClear(GL_COLOR_BUFFER_BIT);

    switch (prevKey) {
        case '1':
            Display1();
            break;
        case '2':
            Display2();
            break;
        case '3':
            Display3();
            break;
        case '4':
            Display4();
            break;
        case '5':
            Display5();
            break;
        case '6':
            Display6();
            break;
        case '7':
            Display7();
            break;
        case '8':
            Display8();
            break;
        case '9':
            Display9();
            break;
        case '0':
            Display0();
            break;
        default:
            break;
    }

    glFlush();
}

void Reshape(int w, int h) {
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
    prevKey = key;
    if (key == 27) // escape
        exit(0);
    glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char **argv) {

    glutInit(&argc, argv);

    glutInitWindowSize(dim, dim);

    glutInitWindowPosition(100, 100);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow(argv[0]);

    Init();

    glutReshapeFunc(Reshape);

    glutKeyboardFunc(KeyboardFunc);

    glutMouseFunc(MouseFunc);

    glutDisplayFunc(Display);

    glutMainLoop();

    return 0;
}