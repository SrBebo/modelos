#include <windows.h>
#include <GL/glut.h>
#include <cmath>

float cameraRadius = 5.0;
float cameraAngleX = 45.0;
float cameraAngleY = 45.0;

float planeX = 2.0; //posicion de camara en eje x
float planeY = 0.0; //posicion de camara en eje y
float planeZ = 0.0; //posicion de camara en eje z
float planeSpeed = 0.2;

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void drawCube() {
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);

    glutWireCube(1.0);

    glColor4f(0.0f, 0.0f, 0.0f, 0.0f);
    glutSolidCube(0.6);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    float cameraX = cameraRadius * sin(cameraAngleY * (3.14159 / 180.0)) * cos(cameraAngleX * (3.14159 / 180.0));
    float cameraY = cameraRadius * sin(cameraAngleX * (3.14159 / 180.0));
    float cameraZ = cameraRadius * cos(cameraAngleY * (3.14159 / 180.0)) * cos(cameraAngleX * (3.14159 / 180.0));

    gluLookAt(cameraX, cameraY, cameraZ, 0, 0, 0, 0, 1, 0);

    glPushMatrix();
    glTranslatef(planeX, planeY, planeZ);
    drawCube();
    glPopMatrix();

    glutSwapBuffers();
}

void reshape(GLsizei w, GLsizei h) {
    if (h == 0) {
        h = 1;
    }
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0f, (GLfloat)w / (GLfloat)h, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
}

void mover(int key, int, int) {
    switch (key) {
    case GLUT_KEY_LEFT:
        cameraAngleY -= 5.0;
        break;
    case GLUT_KEY_RIGHT:
        cameraAngleY += 5.0;
        break;
    case GLUT_KEY_UP:
        cameraAngleX += 5.0;
        break;
    case GLUT_KEY_DOWN:
        cameraAngleX -= 5.0;
        break;
    }
    glutPostRedisplay();
}

void teclado(unsigned char key, int x, int y) {
    switch (key) {
    case 'w':
        planeZ += planeSpeed;
        break;
    case 's':
        planeZ -= planeSpeed;
        break;
    case 'a':
        planeX -= planeSpeed;
        break;
    case 'd':
        planeX += planeSpeed;
        break;
    case 'e':
        planeY -= planeSpeed;
        break;
    case 'q':
        planeY += planeSpeed;
        break;
    }
    glutPostRedisplay();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(10, 10);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow("Cubo con Cámara Móvil");
    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutSpecialFunc(mover);
    glutKeyboardFunc(teclado);
    init();
    glutMainLoop();
    return 0;
}
