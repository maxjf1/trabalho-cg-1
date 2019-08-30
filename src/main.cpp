#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "lib/extras.h"

/// Estruturas iniciais para armazenar vertices
//  Você poderá utilizá-las adicionando novos métodos (de acesso por exemplo) ou usar suas próprias estruturas.
class vertex {
public:
    float x = 0,
            y = 0,
            z = 0;
};

class triangle {
public:
    vertex v[3];
};

/// Globals
float zdist = 4.0;
float rotationX = 0.0, rotationY = 0.0;
int last_x, last_y;
int width, height;

const float BALL_RADIUS = 0.25;

float velocity = 0.5;
float direction = 0.0;
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

/**
 * Calculate normal
 * @param t
 * @return
 */
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

/**
 * Calculate and set normal
 * @param t
 */
void setCalcNormal(triangle t) {
    vertex normal = calcNormal(t);
    glNormal3f(normal.x, normal.y, normal.z);

}

void drawObject() {
    vertex vetorNormal;
    vertex v[4] = {{-1.0f, -1.0f, 0.0f},
                   {1.0f,  -1.0f, 0.0f},
                   {-1.0f, 1.0f,  0.0f},
                   {1.0f,  1.0f,  -0.5f}};

    triangle t[2] = {{v[0], v[1], v[2]},
                     {v[1], v[3], v[2]}};

    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 2; i++) // triangulos
    {
        vetorNormal = calcNormal(t[i]); // Passa face triangular e endereço do vetor normal de saída
        glNormal3f(vetorNormal.x, vetorNormal.y, vetorNormal.z);
        for (int j = 0; j < 3; j++) // vertices do triangulo
            glVertex3d(t[i].v[j].x, t[i].v[j].y, t[i].v[j].z);
    }
    glEnd();
}

void drawBoard() {
    glPushMatrix();


    setColorBase();

    // base
    glNormal3f(0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(-2, -2, 0);
    glVertex3f(2, -2, 0);
    glVertex3f(2, 2, 0);
    glVertex3f(-2, 2, 0);
    glEnd();

    // bottom
    glNormal3f(0, 1, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(-2, -2, 0.5);
    glVertex3f(2, -2, 0.5);
    glVertex3f(2, -2, 0);
    glVertex3f(-2, -2, 0);
    glEnd();

    // right
    glNormal3f(-1, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(2, -2, 0.5);
    glVertex3f(2, 2, 0.5);
    glVertex3f(2, 2, 0);
    glVertex3f(2, -2, 0);
    glEnd();

    // top
    glNormal3f(0, -1, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(2, 2, 0.5);
    glVertex3f(-2, 2, 0.5);
    glVertex3f(-2, 2, 0);
    glVertex3f(2, 2, 0);
    glEnd();

    // left
    glNormal3f(1, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    glVertex3f(-2, 2, 0.5);
    glVertex3f(-2, -2, 0.5);
    glVertex3f(-2, -2, 0);
    glVertex3f(-2, 2, 0);
    glEnd();
    glPopMatrix();
}

void drawSphere() {

    glPushMatrix();
    glNormal3f(0, 0, 1);
    setColor(0, 1, 0);
    glTranslatef(0, -2 + BALL_RADIUS, BALL_RADIUS);
    glutSolidSphere(BALL_RADIUS, 100, 100);
    glPopMatrix();

}

void drawArrow() {

    glPushMatrix();


    glPushMatrix();
    setColor(0, 0, 1);
    glTranslatef(0, -2, BALL_RADIUS);
    glRotatef(direction, 0, 0, 1);
    glTranslatef(0, BALL_RADIUS * 2.2, 0);
    glRotatef(90, -1, 0, 0);
    glutSolidCone(BALL_RADIUS / 2, velocity + 0.01, 100, 100);
    glPopMatrix();
    glPopMatrix();

}

void drawPrism(float x = 0, float y = 0, float rotation = 0) {

    triangle t = {{
                          {-0.25, 0},
                          {0.25, 0},
                          {0, 0.5},
                  }
    };

    glPushMatrix();

    glTranslatef(x, y, 0);
    glRotatef(rotation, 0, 0, -1);

    setColor(1, 0, 0);
    glNormal3f(0, 0, 1);
    glBegin(GL_TRIANGLES);
    for (int i = 0; i < 3; ++i) {
        glVertex3f(t.v[i].x, t.v[i].y, 0.5);
    }
    glEnd();

    for (int j = 0; j < 3; ++j) {
        int next = (j + 1) % 3;
        setCalcNormal({{
                               {t.v[j].x, t.v[j].y, 0.5},
                               {t.v[j].x, t.v[j].y, 0},
                               {t.v[next].x, t.v[next].y, 0},
                       }
                      });
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(t.v[j].x, t.v[j].y, 0.5);
        glVertex3f(t.v[j].x, t.v[j].y, 0);
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

//    glPushMatrix();
//    glRotatef(rotationY, 0.0, 1.0, 0.0);
//    glRotatef(rotationX, 1.0, 0.0, 0.0);
//    drawObject();
//    glPopMatrix();


    glRotatef(rotationY, 0, 1, 1);
    glRotatef(rotationX, 1, 0, 1);
    glPushMatrix();

    drawArrow();
    drawSphere();

    drawPrism(0.5, -0.5, -10);
    drawPrism(-0.25, 0.5, -20);
    drawPrism(1.25, 1.25, -20);
    drawPrism(-1.25, -1, -45);
    drawBoard();

    glPopMatrix();

    glutSwapBuffers();
}

void idle() {
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

float fixRange(float value, float min, float max) {
    if (value > max)
        return max;
    else if (value < min)
        return min;
    return value;
}

void keyboard(unsigned char key, int x, int y) {

    switch (tolower(key)) {
        case 'w':
            velocity += 0.05;
            break;
        case 's':

            velocity -= 0.05;
            break;
        case 'a':
            direction += 1;
            break;
        case 'd':
            direction -= 1;
            break;
        case ' ':
            animate != animate;
            break;
        case 27:
            exit(0);
            break;
    }

    velocity = fixRange(velocity, 0, 1);
    direction = fixRange(direction, -90, 90);
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
