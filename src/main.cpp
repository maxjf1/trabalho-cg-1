#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <float.h>

#include "lib/extras.h"
#include "etc.cpp" //TODO: reorganize modules
#include <iostream>

using namespace std;

// Definitions
float fixRange(float value, float min, float max, bool circular = false);


/// Globals
float zdist = 4.0;
float rotationX = 0, rotationY = 0;
int last_x, last_y;
int width, height;

const float BALL_RADIUS = 0.25;
const float TRIANGLE_RADIUS = 0.3;
const float FPS = 60;
const float BHF = 2; // Board Half Width

// prismas iniciais
float prismaPositions[4][3];

float velocity = 0.5;
float initialDirection = 0;
float direction[2] = {0.5, 0.5};
float position[2] = {0, -BHF + BALL_RADIUS};
triangle prismas[4];
bool animate = false;

/// Functions
void init(void) {
    initLight(width, height); // Função extra para tratar iluminação.
}

// Calculate normal
vertex calcNormal(triangle t) {
    vertex vn;
    vertex v_0 = t.v[0],
            v_1 = t.v[1],
            v_2 = t.v[2];
    vertex v1, v2;
    double len;

    /* Encontra vetor v1 */
    v1.x = v_1.x - v_0.x;
    v1.y = v_1.y - v_0.y;
    v1.z = v_1.z - v_0.z;

    /* Encontra vetor v2 */
    v2.x = v_2.x - v_0.x;
    v2.y = v_2.y - v_0.y;
    v2.z = v_2.z - v_0.z;

    /* Calculo do produto vetorial de v1 e v2 */
    vn.x = (v1.y * v2.z) - (v1.z * v2.y);
    vn.y = (v1.z * v2.x) - (v1.x * v2.z);
    vn.z = (v1.x * v2.y) - (v1.y * v2.x);

    /* normalizacao de n */
    len = sqrt(pow(vn.x, 2) + pow(vn.y, 2) + pow(vn.z, 2));

    vn.x /= len;
    vn.y /= len;
    vn.z /= len;

    return vn;
}

// calculate and set GLUT normal
void setCalcNormal(triangle t) {
    vertex normal = calcNormal(t);
    glNormal3f(normal.x, normal.y, normal.z);

}

/**
 * Fix an value range
 * @param circular if true, when the values overflow the min value, it's reset to the max value and vice-versa
 */
float fixRange(float value, float min, float max, bool circular) {
    if (value > max)
        return circular ? min : max;
    else if (value < min)
        return circular ? max : min;
    return value;
}

float rad(float angle) {
    return angle * M_PI / 180;
}

float calcDistance(float aX, float aY, float bX, float bY) {
    return sqrt(pow(aX - bX, 2) + pow(aY - bY, 2));
}

void drawBoard() {
    glPushMatrix();

    setColorBase();

    // base
    glNormal3f(0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(-BHF, -BHF, 0);
    glVertex3f(BHF, -BHF, 0);
    glVertex3f(BHF, BHF, 0);
    glVertex3f(-BHF, BHF, 0);
    glEnd();

    // bottom
    glNormal3f(0, 1, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(-BHF, -BHF, 0.5);
    glVertex3f(BHF, -BHF, 0.5);
    glVertex3f(BHF, -BHF, 0);
    glVertex3f(-BHF, -BHF, 0);
    glEnd();

    // right
    glNormal3f(-1, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(BHF, -BHF, 0.5);
    glVertex3f(BHF, BHF, 0.5);
    glVertex3f(BHF, BHF, 0);
    glVertex3f(BHF, -BHF, 0);
    glEnd();

    // top
    glNormal3f(0, -1, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(BHF, BHF, 0.5);
    glVertex3f(-BHF, BHF, 0.5);
    glVertex3f(-BHF, BHF, 0);
    glVertex3f(BHF, BHF, 0);
    glEnd();

    // left
    glNormal3f(1, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(-BHF, BHF, 0.5);
    glVertex3f(-BHF, -BHF, 0.5);
    glVertex3f(-BHF, -BHF, 0);
    glVertex3f(-BHF, BHF, 0);
    glEnd();
    glPopMatrix();
}

void drawSphere() {

    glPushMatrix();
    glNormal3f(0, 0, 1);
    setColor(0, 1, 0);
    glTranslatef(position[0], position[1], BALL_RADIUS);
    glutSolidSphere(BALL_RADIUS, 100, 100);
    glPopMatrix();

}


void drawArrow() {
    const float height = velocity + 0.01;
    glPushMatrix();

    glPushMatrix();
    setColor(0, 0, 1);
    glTranslatef(position[0], position[1], BALL_RADIUS);
    glRotatef(initialDirection, 0, 0, 1);
    glTranslatef(0, BALL_RADIUS * 1.2, 0);
    glRotatef(90, -1, 0, 0);
    glutSolidCone(BALL_RADIUS / 2, height, 100, 100);
    glPopMatrix();
    glPopMatrix();

}

triangle makeTriangle(float x = 0, float y = 0, float rotation = 0) {
    int i;
    triangle t;

    //generate the base triangle
    for (i = 0; i < 3; ++i) {
        t.v[i].x = TRIANGLE_RADIUS * sin(rad(90 + ((2 - i) * 120)));
        t.v[i].y = TRIANGLE_RADIUS * cos(rad(90 + ((2 - i) * 120)));
    }

    // rotate the triangle
    float r = -rotation * M_PI / 180;
    for (i = 0; i < 3; ++i) {
        float x = t.v[i].x * cos(r) - t.v[i].y * sin(r);
        t.v[i].y = t.v[i].x * sin(r) + t.v[i].y * cos(r);
        t.v[i].x = x;
    }

    // translate
    for (i = 0; i < 3; ++i) {
        t.v[i].x += x;
        t.v[i].y += y;
    };

    return t;
}

void drawPrism(triangle t) {
    int i;

    glPushMatrix();

    setColor(1, 0, 0);
    glNormal3f(0, 0, 1);
    glBegin(GL_TRIANGLES);
    for (i = 0; i < 3; ++i)
        glVertex3f(t.v[i].x, t.v[i].y, 0.5);
    glEnd();

    for (i = 0; i < 3; ++i) {

        int next = (i + 1) % 3;
        setCalcNormal({{
                               {t.v[i].x, t.v[i].y, 0.5},
                               {t.v[i].x, t.v[i].y, 0},
                               {t.v[next].x, t.v[next].y, 0},
                       }
                      });
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(t.v[i].x, t.v[i].y, 0.5);
        glVertex3f(t.v[i].x, t.v[i].y, 0);
        glVertex3f(t.v[next].x, t.v[next].y, 0);
        glVertex3f(t.v[next].x, t.v[next].y, 0.5);
        glEnd();
    }

    glPopMatrix();

}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(0.0, 0.0, zdist, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(rotationY, 0, 1, 1);
    glRotatef(rotationX, 1, 0, 1);
    glPushMatrix();

    if (!animate)
        drawArrow();
    drawSphere();

    for (int i = 0; i < 4; ++i)
        drawPrism(prismas[i]);

    drawBoard();

    glPopMatrix();

    glutSwapBuffers();
}

float vectorAngle(float ax, float ay) {
    return acos(ax * 1 + ay * 0) * (180.0 / M_PI);

}

// update all states
void updateState() {
    if (!animate) return;

    // maximum board position
    const float maxRange[] = {-BHF + BALL_RADIUS, BHF - BALL_RADIUS};
    float movement = velocity * 0.1;

    // Move the ball and handle overflow
    position[0] = fixRange(position[0] + movement * direction[0], maxRange[0], maxRange[1]);
    position[1] = fixRange(position[1] + movement * direction[1], maxRange[0], maxRange[1]);

    // TODO: handle prisma colision
    for (int j = 0; j < 4; ++j) {
        int i;
        int pontoDistante = 2;
        // se a distancia e maior do que o raio da bola + raio do triangulo
        float distance = calcDistance(prismaPositions[j][0], prismaPositions[j][1], position[0], position[1]);
        if (distance > (BALL_RADIUS + TRIANGLE_RADIUS)) continue;

        for (i = 0; i < 3; ++i) {
            // verifica ponto mais distance
            if (calcDistance(position[0], position[1], prismas[j].v[i].x, prismas[j].v[i].y) >
                calcDistance(position[0], position[1], prismas[j].v[pontoDistante].x, prismas[j].v[pontoDistante].y)) {
                pontoDistante = i;
            }
        }
        i = (pontoDistante + 1) % 3;
        int fi = (i + 1) % 3;
        // Obtem equação Ax + B
        // coeficiente angular.
        float a = (prismas[j].v[fi].y - prismas[j].v[i].y) /
                  (prismas[j].v[fi].x - prismas[j].v[i].x);
        // coeficiente linear
        float b = (-prismas[j].v[i].x) * a + prismas[j].v[i].y;

        // distancia entre centro da esfera e reta
        float d = fabs(a * position[0] - position[1] + b) /
                  sqrt(pow(a, 2) + 1);


        // colision happened
        if (d - BALL_RADIUS <= 0) {
            // rollback animation (or else, it will get stuck)
            position[0] = fixRange(position[0] - movement * direction[0], maxRange[0], maxRange[1]);
            position[1] = fixRange(position[1] - movement * direction[1], maxRange[0], maxRange[1]);

            // handle infinite directionAngle
            float directionAngle = ((position[1] + direction[1]) - position[1]) /
                                   ((position[0] + direction[0]) - position[0]);
            if (fabs(directionAngle) == INFINITY) {
                directionAngle = directionAngle >= 0 ? FLT_MIN : FLT_MAX;
            }

            // get the colision angle
            float angle = atan((
                                       (a - directionAngle) /
                                       (1 + a * directionAngle)
                               )) * (180.0 / M_PI);


            // rotate the direction
            float r = fabs(angle * 2) * (angle / fabs(angle));
            r = r * M_PI / 180;

            // rotação
            float x = direction[0] * cos(r) - direction[1] * sin(r);
            direction[1] = direction[0] * sin(r) + direction[1] * cos(r);
            direction[0] = x;

            // Re-run the movement of the ball
            position[0] = fixRange(position[0] + movement * direction[0], maxRange[0], maxRange[1]);
            position[1] = fixRange(position[1] + movement * direction[1], maxRange[0], maxRange[1]);

            break;
        }
    }

    // borders colision
    for (
            int i = 0;
            i < 2; ++i) {
        if (position[i] == maxRange[0] || position[i] == maxRange[1])
            direction[i] *= -1;
    }
}

void idle() {
    float t, frameTime;
    static float tLast = 0.0;
    // Get elapsed time
    t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    // Calculate frame time
    frameTime = t - tLast;

    // Check if the desired frame time was achieved. If not, skip animation.
    if (frameTime <= 1.0 / FPS)
        return;

    updateState();
    glutPostRedisplay();
}

void reshape(int w, int h) {
    width = w;
    height = h;

    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, (GLfloat) w / (GLfloat) h, 0.01, 200.0);
}

void keyboard(unsigned char key, int x, int y) {

    if (!animate) {
        switch (tolower(key)) {
            case 'w':
                velocity += 0.025;
                break;
            case 's':
                velocity -= 0.025;
                break;
            case 'a':
                initialDirection += 5;
                break;
            case 'd':
                initialDirection -= 5;
                break;
        }
        velocity = fixRange(velocity, -1, 1);
        initialDirection = fixRange(initialDirection, -180, 180, true);
        direction[0] = cos((initialDirection + 90) * M_PI / 180);
        direction[1] = sin((initialDirection + 90) * M_PI / 180);
    }

    switch (tolower(key)) {
        case ' ':
            animate = !animate;
            break;
        case 'r':
            prismaPositions[0][2] += 1;
            prismas[0] = makeTriangle(prismaPositions[0][0], prismaPositions[0][1], prismaPositions[0][2]);
            break;

        case 't':
            prismaPositions[0][2] -= 1;
            prismas[0] = makeTriangle(prismaPositions[0][0], prismaPositions[0][1], prismaPositions[0][2]);
            break;
        case 27:
            exit(0);
            break;
    }
}

// Motion callback
void motion(int x, int y) {
    rotationX += (float) (y - last_y);
    rotationY += (float) (x - last_x);

    last_x = x;
    last_y = y;
}

// Mouse callback
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        last_x = x;
        last_y = y;
    }
    if (button == 3) // Scroll up
    {
        zdist += 1.0f;
    }
    if (button == 4) // Scroll Down
    {
        zdist -= 1.0f;
    }
}

void generatePrisms() {
    srand(time(NULL));
    for (int i = 0; i < 4; ++i) {
        bool found = false;
        float x, y, r;
        while (!found) {
            found = true;
            // generate points inside the box (using the triangle radius)
            x = (float) rand() / (float) RAND_MAX * (4 - 2 * TRIANGLE_RADIUS) - 2 + TRIANGLE_RADIUS;
            y = (float) rand() / (float) RAND_MAX * (4 - 2 * TRIANGLE_RADIUS) - 2 + TRIANGLE_RADIUS;
            r = rand() % 360;
            // distance from the ball
            if (calcDistance(position[0], position[1], x, y) <= (TRIANGLE_RADIUS + BALL_RADIUS) * 1.1) {
                found = false;
                continue;
            }

            // Distance between prisms
            for (int j = 0; j < i; ++j) {
                float distance = calcDistance(prismaPositions[j][0], prismaPositions[j][1], x, y);
                if (distance <= TRIANGLE_RADIUS * 2.1) {
                    found = false;
                    break;
                }
            }

            prismaPositions[i][0] = x;
            prismaPositions[i][1] = y;
            prismaPositions[i][2] = r;
            prismas[i] = makeTriangle(prismaPositions[i][0], prismaPositions[i][1], prismaPositions[i][2]);
        }
    }
}

/// Main
int main(int argc, char **argv) {
    generatePrisms();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
//    glutMouseFunc(mouse);
//    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
