#include <GL/gl.h>
#include <math.h>

typedef struct {
    float position[3];
    float scale;
    float theta;
} Pawn;

void drawStripe() {
    float r1 = 0.0;
    float z1 = 530.114;
    float nr, nz;

    //glVertex3f( r, 0.0, z);
    //glVertex3f( r * cos( theta), r * sin( theta), 0.0, 1.0);
    glBegin(GL_QUAD_STRIP);
    glNormal3f(0.0, 0.0, 1.0);

#define STRIP(r, z) \
    nr = r * cos(-phi); \
    nz = r * sin(-phi); \
    glVertex3f(nr, nz, z1); \
    glVertex3f(nr, nz, z);

    STRIP(24.000, 528.0);
    STRIP(54.102, 512.0);
    STRIP(67.548, 496.0);
    STRIP(75.516, 480.0);
    STRIP(79.341, 464.0);
    STRIP(80.616, 448.0);
    STRIP(78.385, 432.0);
    STRIP(72.010, 416.0);
    STRIP(61.811, 400.0);
    STRIP(43.484, 384.0);
    STRIP(39.021, 380.0);
    STRIP(42.846, 376.0);
    STRIP(54.958, 372.0);
    STRIP(68.026, 368.0);
    STRIP(84.441, 364.0);
    STRIP(89.062, 360.0);
    STRIP(89.381, 356.0);
    STRIP(87.947, 352.0);
    STRIP(79.819, 348.0);
    STRIP(67.389, 336.0);
    STRIP(61.651, 320.0);
    STRIP(58.305, 304.0);
    STRIP(55.117, 272.0);
    STRIP(56.074, 240.0);
    STRIP(61.173, 208.0);
    STRIP(70.576, 176.0);
    STRIP(77.747, 160.0);
    STRIP(88.425, 144.0);
    STRIP(101.015, 140.0);
    STRIP(106.752, 136.0);
    STRIP(108.665, 132.0);
    STRIP(109.621, 128.0);
    STRIP(121.254, 112.0);
    STRIP(142.769, 96.0);
    STRIP(148.825, 88.0);
    STRIP(151.056, 80.0);
    STRIP(151.215, 72.0);
    STRIP(146.434, 64.0);
    STRIP(134.960, 56.0);
    STRIP(134.482, 52.0);
    STRIP(141.494, 48.0);
    STRIP(159.821, 40.0);
    STRIP(164.124, 36.0);
    STRIP(161.415, 32.0);
    STRIP(156.793, 28.0);
    STRIP(145.000, 16.0);
    STRIP(136.713, 4.0);
    STRIP(126.035, 0.0);
#undef STRIP

    glEnd();
}

void dibujarPeon(Pawn *peon) {
    GLfloat c[] = {1.0, 1.0, 1.0, 1.0};
    glMaterialfv(GL_FRONT, GL_DIFFUSE, c);
    glMaterialfv(GL_FRONT, GL_SPECULAR, c);
    glMaterialf(GL_FRONT, GL_SHININESS, 100);

    glPushMatrix();
    glTranslatef(peon->position[0], peon->position[1], peon->position[2]);
    glScalef(peon->scale, peon->scale, peon->scale);

    // Dibujar la parte superior.
    float phi = 0.0;
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 530.114);

    while (phi <= 360.0) {
        float x = 24.0 * cos(-phi);
        float y = 24.0 * sin(-phi);
        float z = 528.0;

        // Calcular la normal usando la matriz de rotación.
        /*
        Vector3d v = Vector3d::Vector3d(2.114 * cos(phi), 2.114 * sin(phi), x, 0.0);
        v.normalize();
        v.set();
        */
        glVertex3f(x, y, z);

        phi += peon->theta;
    }
    glEnd();

    // Dibujar las tiras.
    phi = 0.0;
    glPushMatrix();
    while (phi <= 360.0) {
        drawStripe();
        glRotatef(peon->theta, 0.0, 0.0, 1.0);

        phi += peon->theta;
    }
    glPopMatrix();

    // Dibujar la parte inferior.
    glBegin(GL_TRIANGLE_FAN);
    glNormal3f(0.0, 0.0, -1.0);
    glVertex3f(0.0, 0.0, 0.0);

    phi = 0;
    while (phi <= 360.0) {
        float x = 126.035 * cos(phi);
        float y = 126.035 * sin(phi);
        float z = 0;
        glVertex3f(x, y, z);

        phi += peon->theta;
    }
    glEnd();

    GLfloat reset[] = {0.1, 0.1, 0.1, 1.0};
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, white);
    glMaterialfv(GL_FRONT, GL_SPECULAR, reset);

    glPopMatrix();
}