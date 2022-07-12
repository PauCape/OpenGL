// Etapa_03.cpp

// Autores: Alejandro Medina Perelló y Pau Capellá Ballester

// Imports
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

// Tamaño incial de la ventana
const int W_WIDTH = 500;
const int W_HEIGHT = 500;
static const int FPS = 60;

// Declaraciones de funciones
void drawAxis();
void init();

// Variables propias
GLfloat fAngulo;
GLfloat fVariation;
GLboolean variationBool = true;

// Función que visualiza la escena OpenGL
void display(void)
{
    // Borramos la escena
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujamos una malla blanca
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

    // Dibujamos los ejes de coordenadas
    drawAxis();

    glPushMatrix();

    // Combinacion de translacion
    glTranslatef(-0.6f, 0.0f, 0.4f);
    glTranslatef(fVariation, 0.0f, 0.0f);

    glutWireTeapot(0.3);

    glPopMatrix();

    glPushMatrix();

    // Combinacion de translacion y rotación
    glTranslatef(0.3f, 0.0f, -0.5f);
    glRotatef(fAngulo, 0, 1, 0);

    glutWireTeapot(0.3);

    glPopMatrix();

    glPushMatrix();

    // Combinacion de translacion y escalado
    glTranslatef(-0.6f, 0.0f, -0.6f);
    glScalef(fVariation, fVariation, fVariation);

    glutWireTeapot(0.3);

    glPopMatrix();

    glutSwapBuffers();
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

void timer(int v)
{
    // Incrementamos el ángulo
    fAngulo += 3.0f;
    // Si es mayor que dos pi la decrementamos
    if (fAngulo > 360)
        fAngulo -= 360;
    // Indicamos que es necesario repintar la pantalla
    glutPostRedisplay();

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

// Funcion que utilizamos para inicializar los parametros de nuestra escena
void init()
{
    // El color que usamos para limpiar la escena es el negro
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    // Preparamos los parametros del Frustum
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-0.5, 0.5, -0.5, 0.5, 1, 40);

    // Coloamos la escena de forma que podamos observar los ejes de coordenadas
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(0, 0, -3);
    glRotatef(40, 1, 0, 0);
    glRotatef(-70, 0, 1, 0);
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
    glutCreateWindow("Etapa_03");

    // Indicamos cuales son las funciones que usamos
    glutDisplayFunc(display);
    glutTimerFunc(100, timer, 0);

    // Llamamos al metodo de inicialización
    init();

    // Comienza la ejecución del core de GLUT
    glutMainLoop();
    return 0;
}