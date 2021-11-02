#include "../lib/keyboard.h"

int wScreen = 800, hScreen = 600;
GLdouble xCam = -5, yCam = 15, zCam = -5;
GLdouble inc = 0.5;
Keyboard k;
void init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(wScreen, hScreen);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("Comando de Jogo");

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glShadeModel(GL_SMOOTH);
    gluLookAt(-100, 30, -100, 5, 2, 10, 0, 1, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, wScreen, hScreen);
    // glMatrixMode(GL_PROJECTION);
    // glLoadIdentity();
    // gluPerspective(45, (float)wScreen / hScreen, 0.1, 100);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // Keyboard k = Keyboard();
    // k.draw();
    k.draw();
    gluLookAt(-100, 30, -100, 5, 2, 10, 0, 1, 0);

    glutSwapBuffers();
}

void teclasNotAscii(int key, int x, int y)
{
    //.. observador pode andar � volda da cena  (setas esquerda / direita)
    //.. observador pode andar para cima e para baixo (setas cima / baixo )

    if (key == GLUT_KEY_UP)
    {
        yCam += 0.1;
    }
    if (key == GLUT_KEY_DOWN)
    {
        yCam -= 0.1;
    }
    if (key == GLUT_KEY_LEFT)
    {
        xCam -= 0.1;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        xCam += 0.1;
    }
    cout << "YCam=" << yCam << ",xCam=" << xCam << endl;
    glutPostRedisplay();
}

int main(int argc, char **argv)
{
    init(argc, argv);
    k = Keyboard();
    // k.draw();
    display();
    cout << "Boo\n";
    glutDisplayFunc(display);
    glutSpecialFunc(teclasNotAscii);
    glutMainLoop();
}