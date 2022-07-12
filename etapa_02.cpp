// Etapa_02.cpp

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

// Variables propias
GLfloat fAngulo;
GLfloat fVariation;
GLboolean variationBool = true;

// Función que visualiza la escena OpenGL
void display(void)
{
    // Borramos la escena
    glClear(GL_COLOR_BUFFER_BIT);

    // Dibujamos los ejes de coordenadas
    drawAxis();

    glPushMatrix();

    // Combinacion de translacion y rotacion
    glTranslatef(0.5f, 0.5f, 0.0f);
    glRotatef(fAngulo, 0.0f, 0.0f, 1.0f);
    glTranslatef(-0.5f, -0.5f, 0.0f);

    glColor3f(1.0f, 1.0f, 1.0f);

    // Generamos un cuadrado en el 1º cuadrante
    glBegin(GL_POLYGON);
    glVertex3f(0.25f, 0.25f, 0.0f);
    glVertex3f(0.75f, 0.25f, 0.0f);
    glVertex3f(0.75f, 0.75f, 0.0f);
    glVertex3f(0.25f, 0.75f, 0.0f);
    glEnd();

    glPopMatrix();

    glPushMatrix();

    glColor3f(0.0f, 1.0f, 0.0f);

    // Combinacion de translacion y escalado
    glTranslatef(-0.5f, 0.5f, 0.0f);
    glScalef(fVariation, fVariation, fVariation);
    glTranslatef(0.5f, -0.5f, 0.0f);

    // Generamos un cuadrado en el 2º cuadrante
    glBegin(GL_POLYGON);
    glVertex3f(-0.25f, 0.25f, 0.0f);
    glVertex3f(-0.75f, 0.25f, 0.0f);
    glVertex3f(-0.75f, 0.75f, 0.0f);
    glVertex3f(-0.25f, 0.75f, 0.0f);
    glEnd();

    glPopMatrix();

    glPushMatrix();

    glColor3f(1.0f, 0.0f, 0.0f);

    // Combinacion de translacion y escalado
    glTranslatef(-0.5f, -0.5f, 0.0f);
    glTranslatef(fVariation, 0.0f, 0.0f);
    glTranslatef(0.5f, 0.5f, 0.0f);

    // Generamos un cuadrado en el 3º cuadrante
    glBegin(GL_POLYGON);
    glVertex3f(-0.25f, -0.25f, 0.0f);
    glVertex3f(-0.75f, -0.25f, 0.0f);
    glVertex3f(-0.75f, -0.75f, 0.0f);
    glVertex3f(-0.25f, -0.75f, 0.0f);
    glEnd();

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

// Función que se ejecuta cuando la pantalla se reescala
void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    GLfloat aspect = GLfloat(width) / GLfloat(height);
    glLoadIdentity();
    if (width <= height)
    {
        // Si el ancho es más pequeño, extendemos la altura
        glOrtho(-1, 1, -1 / aspect, 1 / aspect, -10.0, 10.0);
    }
    else
    {
        // Si la altura es más pequeña, extendemos el ancho
        glOrtho(-1 * aspect, 1 * aspect, -1, 1, -10.0, 10.0);
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
    glutCreateWindow("Etapa_02");

    // Indicamos cuales son las funciones que usamos
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(100, timer, 0);

    // El color de fondo será el negro (RGBA, RGB + Alpha channel)
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glOrtho(-1.0, 1.0f, -1.0, 1.0f, -1.0, 1.0f);

    // Comienza la ejecución del core de GLUT
    glutMainLoop();
    return 0;
}