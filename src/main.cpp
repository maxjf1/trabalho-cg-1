#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "lib/extras.h"
#include "etc.cpp" //TODO: reorganize modules
#include <iostream>

using namespace std;

/// Estruturas iniciais para armazenar vertices
//  Você poderá utilizá-las adicionando novos métodos (de acesso por exemplo) ou usar suas próprias estruturas.


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
const float STATIC_PRISMAS[][3] = {
        {0.5,   -0.5, -10},
        {-0.25, 0.5,  -20},
        {1.25,  1.25, -20},
        {-1.25, -1,   -45},
};

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

/* Exemplo de cálculo de vetor normal que são definidos a partir dos vértices do triângulo;
  v_2
  ^
  |\
  | \
  |  \       'vn' é o vetor normal resultante
  |   \
  +----> v_1
  v_0
*/

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

bool checkColision(int t) {

}

// update all states
void updateState() {
    if (!animate) return;
    // maximum board position
    const float maxRange[] = {-BHF + BALL_RADIUS, BHF - BALL_RADIUS};

    // TODO: handle prisma colision
    for (int j = 0; j < 4; ++j) {
        // se a distancia e maior do que o raio da bola + raio do triangulo
        if (abs(STATIC_PRISMAS[j][0] - position[0]) > BALL_RADIUS + 0.5) continue;
        cout << "Colisão em " << j << ": " << STATIC_PRISMAS[j][0] - position[0] << endl;
    }

    // overflow
    position[0] = fixRange(position[0] + velocity * 0.1 * direction[0], maxRange[0], maxRange[1]);
    position[1] = fixRange(position[1] + velocity * 0.1 * direction[1], maxRange[0], maxRange[1]);

    // borders colision
    for (int i = 0; i < 2; ++i) {
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
                velocity += 0.05;
                break;
            case 's':
                velocity -= 0.05;
                break;
            case 'a':
                initialDirection += 2;
                break;
            case 'd':
                initialDirection -= 2;
                break;
        }
        velocity = fixRange(velocity, 0, 1);
        initialDirection = fixRange(initialDirection, -180, 180, true);
        direction[0] = cos((initialDirection + 90) * M_PI / 180);
        direction[1] = sin((initialDirection + 90) * M_PI / 180);
    }

    switch (tolower(key)) {
        case ' ':
            animate = !animate;
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

/// Main
int main(int argc, char **argv) {
    // initialize prismas
    for (int i = 0; i < 4; ++i) {
        prismas[i] = makeTriangle(STATIC_PRISMAS[i][0], STATIC_PRISMAS[i][1], STATIC_PRISMAS[i][2]);
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1000, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glutKeyboardFunc(keyboard);
    glutIdleFunc(idle);
    glutMainLoop();
    return 0;
}
