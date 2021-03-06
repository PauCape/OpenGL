// Etapa_06.cpp

// Autores: Alejandro Medina Perelló y Pau Capellá Ballester

// Imports
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <cmath>
#include <iostream>

#define PI 3.1415

// Tamaño incial de la ventana
const int W_WIDTH = 500;
const int W_HEIGHT = 500;
static const int FPS = 60;
static int shoulderAngle = 0, elbowAngle = 0, armRotation = 0;

// Declaraciones de funciones
void drawAxis();
void init();
void myCamera();
void light();
void board();
void cargarmenu();

// Variables propias
GLfloat fAngulo;
GLfloat fVariation;
GLboolean variationBool = true;
GLdouble pos_camara_X = 8.486033;
GLdouble pos_camara_Y = 6.351840;
GLdouble pos_camara_Z = 6.871893;
GLdouble angulo_x = -49.994000;
GLdouble angulo_y = 180.014100;
GLfloat light0_posX = 0.0;
GLfloat light0_posY = 2.0;
GLfloat light0_posZ = 0.0;
GLfloat light1_posX = 0.0;
GLfloat light1_posY = 2.0;
GLfloat light1_posZ = 0.0;
GLfloat light2_posX = 0.0;
GLfloat light2_posY = 0.0;
GLfloat light2_posZ = 0.0;
GLboolean shadowType = true;
GLboolean switchLight0 = true;
GLboolean switchLight1 = true;
GLboolean switchLight2 = true;
GLboolean switchFog = false;
GLboolean ControlLuz = false;
GLboolean ControlCamara = false;

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

void wireBox(GLdouble width, GLdouble height, GLdouble depth)
{
    glPushMatrix();
    glScalef(width, height, depth);
    glLineWidth(3.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutWireCube(1.0);
    glLineWidth(1.0f);
    glPopMatrix();
}

void fog()
{
    GLfloat densidad = 0.05;
    float colorf[] = {0.5, 0.5, 0.5, 1};

    if (switchFog)
        glEnable(GL_FOG);
    else
        glDisable(GL_FOG);

    glFogi(GL_FOG_MODE, GL_EXP2);
    glFogfv(GL_FOG_COLOR, colorf);
    glFogf(GL_FOG_DENSITY, densidad);
    glHint(GL_FOG_HINT, GL_NICEST);
}

// Función que visualiza la escena OpenGL
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    fog();

    myCamera();

    drawAxis();

    board();

    light();

    glPushMatrix();
    glRotatef(armRotation, 0.0, 1.0, 0.0);

    glPushMatrix();

    glRotatef((GLfloat)shoulderAngle, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    wireBox(2.0, 0.3, 1.0);

    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbowAngle, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    wireBox(2.0, 0.3, 1.0);

    glPushMatrix();
    glRotatef(-25, 0.0, 0.0, 1.0);
    glTranslatef(light2_posX + 1.2, light2_posY, light2_posZ);
    glColor3f(1.0f, 0.0f, 0.0f);
    glutSolidCube(0.3);
    glTranslatef(-light2_posX, -light2_posY, -light2_posZ);
    glPopMatrix();

    GLfloat light2_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat light2_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light2_specular[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat light2_position[] = {light2_posX, light2_posY, light2_posZ, 1.0};
    GLfloat light2_spot_direccion[] = {0.0, -1.0, 0.0, -1.0};

    glLightfv(GL_LIGHT2, GL_AMBIENT, light2_ambient);
    glLightfv(GL_LIGHT2, GL_DIFFUSE, light2_diffuse);
    glLightfv(GL_LIGHT2, GL_SPECULAR, light2_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light2_position);
    glLightfv(GL_LIGHT2, GL_SPOT_DIRECTION, light2_spot_direccion);
    glLightf(GL_LIGHT2, GL_SPOT_CUTOFF, 40.0);

    glPopMatrix();
    glPopMatrix();

    glPushMatrix();
    glColor3f(1.0f, 0.0f, 0.0f);
    glTranslatef(-4.0f, 0.5f, -4.0f);
    glutSolidSphere(1, 20, 20);
    glPopMatrix();

    glutSwapBuffers();
}

void timer(int v)
{
    // Incrementamos el ángulo
    fAngulo += 1.0f;

    // Si es mayor que dos pi la decrementamos
    if (fAngulo > 360)
        fAngulo -= 360;

    // Incremetamos y decrementamos la variable de variación
    if (variationBool == true)
    {
        fVariation += 0.03f;
        if (fVariation > 10)
        {
            variationBool = false;
        }
    }
    else if (variationBool == false)
    {
        fVariation -= 0.03f;
        if (fVariation < -10)
        {
            variationBool = true;
        }
    }

    // Variaciones en la posición de las luces
    light0_posX = fVariation;
    light1_posX = -5 * sin(fAngulo * 2 * (PI / 180));
    light1_posZ = -5 * cos(fAngulo * 2 * (PI / 180));

    // Indicamos que es necesario repintar la pantalla
    glutPostRedisplay();

    glutTimerFunc(1000 / FPS, timer, v);
}

void board()
{
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {

            if ((i % 2) == 0 && (j % 2) == 0)
                glColor3f(0.0f, 0.0f, 0.0f);
            else if ((i % 2) == 1 && (j % 2) == 1)
                glColor3f(0.0f, 0.0f, 0.0f);
            else
                glColor3f(0.6f, 0.6f, 0.6f);

            glPushMatrix();
            glTranslatef(-10 + i, -1.8, 8 - j);
            glutSolidCube(1);
            glTranslatef(-i, 1.8, j);
            glEnd();

            glPopMatrix();
        }
    }
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

void light()
{
    glPushMatrix();
    glTranslatef(light0_posX, light0_posY, light0_posZ);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidCube(0.3);
    glTranslatef(-light0_posX, -light0_posY, -light0_posZ);
    glPopMatrix();

    GLfloat light0_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat light0_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light0_specular[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat light0_position[] = {light0_posX, light0_posY, light0_posZ, 1.0};
    GLfloat light0_spot_direccion[] = {0.0, -1.0, 0.0, -1.0};

    glLightfv(GL_LIGHT0, GL_AMBIENT, light0_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
    glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, light0_spot_direccion);
    glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 40.0);

    glPushMatrix();
    glTranslatef(light1_posX, light1_posY, light1_posZ);
    glColor3f(1.0f, 1.0f, 1.0f);
    glutSolidCube(0.3);
    glTranslatef(-light1_posX, -light1_posY, -light1_posZ);
    glPopMatrix();

    GLfloat light1_ambient[] = {0.2, 0.2, 0.2, 1.0};
    GLfloat light1_diffuse[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat light1_specular[] = {0.5, 0.5, 0.5, 1.0};
    GLfloat light1_position[] = {light1_posX, light1_posY, light1_posZ, 1.0};
    GLfloat light1_spot_direccion[] = {0.0, -1.0, 0.0, -1.0};

    glLightfv(GL_LIGHT1, GL_AMBIENT, light1_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, light1_spot_direccion);
    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 40.0);

    if (switchLight0)
        glEnable(GL_LIGHT0);
    else
        glDisable(GL_LIGHT0);
    if (switchLight1)
        glEnable(GL_LIGHT1);
    else
        glDisable(GL_LIGHT1);
    if (switchLight2)
        glEnable(GL_LIGHT2);
    else
        glDisable(GL_LIGHT2);
    glEnable(GL_LIGHTING);
}

// Funcion que utilizamos para inicializar los parametros de nuestra escena
void init()
{
    // El color que usamos para limpiar la escena es el negro
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
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
    case GLUT_KEY_LEFT:
        (elbowAngle += 5) %= 360;
        break;
    case GLUT_KEY_RIGHT:
        (elbowAngle -= 5) %= 360;
        break;
    case GLUT_KEY_UP:
        (shoulderAngle += 5) %= 360;
        break;
    case GLUT_KEY_DOWN:
        (shoulderAngle -= 5) %= 360;
        break;
    default:
        return;
    }
}

void KeyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 't':
    case 'T':
        (armRotation += 5) %= 360;
        break;
    case 'g':
    case 'G':
        (armRotation -= 5) %= 360;
        break;
    case '1':
        if (switchLight0 == true && ControlLuz == true)
            switchLight0 = false;
        else
            switchLight0 = true;
        break;
    case '2':
        if (switchLight1 == true && ControlLuz == true)
            switchLight1 = false;
        else
            switchLight1 = true;
        break;
    case '3':
        if (switchLight2 == true && ControlLuz == true)
            switchLight2 = false;
        else
            switchLight2 = true;
        break;
    case '4':
        if (switchFog == true)
            switchFog = false;
        else
            switchFog = true;
        break;
    case 'w':
    case 'W':
        if (ControlCamara == true)
            angulo_y -= 0.0003f;
        break;
    case 's':
    case 'S':
        if (ControlCamara == true)
            angulo_y += 0.0003f;
        break;
    case 'a':
    case 'A':
        if (ControlCamara == true)
            angulo_x -= 0.0003f;
        break;
    case 'd':
    case 'D':
        if (ControlCamara == true)
            angulo_x += 0.0003f;
        break;
    case 32:
        if (shadowType)
            glShadeModel(GL_FLAT);
        else
            glShadeModel(GL_SMOOTH);
        if (shadowType)
            shadowType = false;
        else
            shadowType = true;
        break;
    }
}

void menu(int valor)
{
    switch (valor)
    {
    case 0:
        if (ControlCamara == true)
        {
            ControlCamara = false;
            cargarmenu();
        }
        else
        {
            ControlCamara = true;
            cargarmenu();
        }
        break;
    case 1:
        if (ControlLuz == true)
        {
            ControlLuz = false;
            cargarmenu();
        }
        else
        {
            ControlLuz = true;
            cargarmenu();
        }
        break;
    case 2:
        pos_camara_X = -0.006036;
        pos_camara_Y = 8.405707;
        pos_camara_Z = 1.426396;
        angulo_x = -49.977200;
        angulo_y = 180.030300;
        break;
    case 3:
        pos_camara_X = 6.708357;
        pos_camara_Y = 0.393704;
        pos_camara_Z = 0.051496;
        angulo_x = -50.004200;
        angulo_y = 180.005100;
        break;
    case 4:
        pos_camara_X = 8.486033;
        pos_camara_Y = 6.351840;
        pos_camara_Z = 6.871893;
        angulo_x = -49.994000;
        angulo_y = 180.014100;
        break;
    }
}

void cargarmenu()
{

    int Control_Camara = glutCreateMenu(menu);

    if (ControlCamara == false)
    {
        glutAddMenuEntry("Control camara ON", 0);
    }
    else
    {
        glutAddMenuEntry("Control camara OFF", 0);
    }

    int Control_Luz = glutCreateMenu(menu);

    if (ControlLuz == false)
    {
        glutAddMenuEntry("Control luces ON", 1);
    }
    else
    {
        glutAddMenuEntry("Control luces OFF", 1);
    }

    int vistas = glutCreateMenu(menu);
    glutAddMenuEntry("Vista 01 ON", 2);
    glutAddMenuEntry("Vista 02 ON", 3);
    glutAddMenuEntry("Vista 03 ON", 4);

    glutCreateMenu(menu);
    glutAddSubMenu("Control Camara", Control_Camara);
    glutAddSubMenu("control Luces", Control_Luz);
    glutAddSubMenu("Vistas", vistas);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

// Función principal
int main(int argc, char **argv)
{
    // Inicializamos la librería GLUT
    glutInit(&argc, argv);

    // Indicamos como ha de ser la nueva ventana
    glutInitWindowPosition((glutGet(GLUT_SCREEN_WIDTH) / 2) - 250, (glutGet(GLUT_SCREEN_HEIGHT) / 2) - 250);
    glutInitWindowSize(W_WIDTH, W_HEIGHT);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_MULTISAMPLE);

    // Creamos la nueva ventana
    glutCreateWindow("Etapa_06");

    // Indicamos cuales son las funciones que usamos
    glutDisplayFunc(display);
    glutTimerFunc(100, timer, 0);
    glutSpecialFunc(KeyPress);
    glutKeyboardFunc(KeyInput);
    glutReshapeFunc(reshape);

    // Llamamos al metodo de inicialización
    init();
    cargarmenu();

    // Comienza la ejecución del core de GLUT
    glutMainLoop();
    return 0;
}