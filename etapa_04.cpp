// Etapa_04.cpp

// Autores: Alejandro Medina Perelló y Pau Capellá Ballester

// Imports
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>

#define PI 3.1415

// Tamaño incial de la ventana
const int W_WIDTH = 500;
const int W_HEIGHT = 500;
static const int FPS = 60;

// Declaraciones de funciones
void drawAxis();
void init();
void myCamera();

// Variables propias
GLfloat fAngulo;
GLfloat fVariation;
GLboolean variationBool = true;
GLdouble pos_camara_X = 3.486033;
GLdouble pos_camara_Y = 2.351840;
GLdouble pos_camara_Z = 1.871893;
GLdouble angulo_x = -49.994000;
GLdouble angulo_y = 180.014100;

// Colores
GLfloat WHITE[] = {1, 1, 1};
GLfloat RED[] = {1, 0, 0};
GLfloat GREEN[] = {0, 1, 0};
GLfloat MAGENTA[] = {1, 0, 1};

// Mi camara
void myCamera()
{

    gluLookAt(pos_camara_X, pos_camara_Y, pos_camara_Z,
              pos_camara_X + cos(angulo_x * (180 / PI)) * cos(angulo_y * (180 / PI)),
              pos_camara_Y + sin(angulo_y * (180 / PI)),
              pos_camara_Z + sin(angulo_x * (180 / PI)) * cos(angulo_y * (180 / PI)),
              0, 1, 0);
}

// Función que visualiza la escena OpenGL
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    myCamera();

    glPushMatrix();

    // Dibujamos una malla blanca
    glPushMatrix();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);
    for (GLfloat i = -2.5; i <= 2.5; i += 0.25)
    {
        glVertex3f(i, 0, 2.5);
        glVertex3f(i, 0, -2.5);
        glVertex3f(2.5, 0, i);
        glVertex3f(-2.5, 0, i);
    }
    glEnd();
    glPopMatrix();

    // Dibujamos los ejes de coordenadas
    drawAxis();

    glPushMatrix();
    glColor3f(255.0f, 0.0f, 0.0f);
    // Combinacion de translacion y rotación
    glTranslatef(0.8f, 0.0f, -0.8f);
    glRotatef(fAngulo, 0, 1, 0);
    glutWireTeapot(0.5);
    glPopMatrix();

    glPopMatrix();

    glutSwapBuffers();
}

void timer(int v)
{
    // Incrementamos el ángulo
    fAngulo += 3.0f;
    // Si es mayor que dos pi la decrementamos
    if (fAngulo > 360)
        fAngulo -= 360;

    // Incremetamos y decrementamos la variable de variación
    if (variationBool == true)
    {
        fVariation += 0.01f;
        if (fVariation > 1)
        {
            variationBool = false;
        }
    }
    else if (variationBool == false)
    {
        fVariation -= 0.01f;
        if (fVariation < 0)
        {
            variationBool = true;
        }
    }

    // Indicamos que es necesario repintar la pantalla
    glutPostRedisplay();

    glutTimerFunc(1000 / FPS, timer, v);
}

// Función que sirve para dibujar los ejes de coordenadas
void drawAxis()
{
    glLineWidth(3.0f);

    glPushMatrix();

    glColor3f(255.0f, 255.0f, 0.0f);

    glBegin(GL_LINES);
    glVertex3f(0.0f, -0.5f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();

    glColor3f(0.0f, 0.0f, 255.0f);

    glBegin(GL_LINES);
    glVertex3f(-0.5f, 0.0f, 0.0f);
    glVertex3f(0.5f, 0.0f, 0.0f);
    glEnd();

    glColor3f(255.0f, 0.0f, 0.0f);

    glBegin(GL_LINES);
    glVertex3f(0.0f, 0.0f, -0.5f);
    glVertex3f(0.0f, 0.0f, 0.5f);
    glEnd();

    glPopMatrix();

    glLineWidth(1.0f);
}

// Funcion que utilizamos para inicializar los parametros de nuestra escena
void init()
{
    // El color que usamos para limpiar la escena es el negro
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

// Función que se ejecuta cuando la pantalla se reescala
void reshape(GLint w, GLint h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, GLfloat(w) / GLfloat(h), 1.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
}

// Función que sirve para obtener las teclas
void KeyPress(int key, int x, int y)
{
    switch (key)
    {

    case GLUT_KEY_UP:
        pos_camara_X += 0.1f * cos(angulo_x * (180 / PI)) * cos(angulo_y * (180 / PI));
        pos_camara_Y += 0.1f * sin(angulo_y * (180 / PI));
        pos_camara_Z += 0.1f * sin(angulo_x * (180 / PI)) * cos(angulo_y * (180 / PI));
        break;
    case GLUT_KEY_DOWN:

        pos_camara_X -= 0.1f * cos(angulo_x * (180 / PI)) * cos(angulo_y * (180 / PI));
        pos_camara_Y -= 0.1f * sin(angulo_y * (180 / PI));
        pos_camara_Z -= 0.1f * sin(angulo_x * (180 / PI)) * cos(angulo_y * (180 / PI));
        break;
    case GLUT_KEY_LEFT:
        pos_camara_X -= 0.1f * sin((angulo_x) * (180 / PI));
        pos_camara_Y += 0;
        pos_camara_Z += 0.1f * cos((angulo_x) * (180 / PI));
        break;
    case GLUT_KEY_RIGHT:
        pos_camara_X += 0.1f * sin((angulo_x) * (180 / PI));
        pos_camara_Y += 0;
        pos_camara_Z -= 0.1f * cos((angulo_x) * (180 / PI));
        break;
    }
}

void KeyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'w':
    case 'W':
        angulo_y -= 0.0003f;
        break;
    case 's':
    case 'S':
        angulo_y += 0.0003f;
        break;
    case 'a':
    case 'A':
        angulo_x -= 0.0003f;
        break;
    case 'd':
    case 'D':
        angulo_x += 0.0003f;
        break;
    }
}

// Función principal
int main(int argc, char **argv)
{
    // Inicializamos la librería GLUT
    glutInit(&argc, argv);

    // Indicamos como ha de ser la nueva ventana
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) / 2) - 250, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 250);
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);

    // Creamos la nueva ventana
    glutCreateWindow("Etapa_04");

    // Indicamos cuales son las funciones que usamos
    glutDisplayFunc(display);
    glutTimerFunc(100, timer, 0);
    glutSpecialFunc(KeyPress);
    glutKeyboardFunc(KeyInput);
    glutReshapeFunc(reshape);

    // Llamamos al metodo de inicialización
    init();

    // Comienza la ejecución del core de GLUT
    glutMainLoop();
    return 0;
}