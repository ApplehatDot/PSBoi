/*
 * MEGC project #5
 * Tworzenie projektu animacji OpenGL
 * z gościem ze zdjęcia (PSBoi)
 */
 
#include <GL/glut.h>
#include <GL/freeglut.h>
#include <math.h>
#include "GWM.h"

#define wWidth 500
#define wHeight 500

#define DefVelX 0.07f
#define DefPosX -20.0f
#define DefVelY -0.1f
#define DefPosY 540.0f

// circle colors [RGB]
#define cR 20.0
#define cG 79.0
#define cB 42.0

float Gx = DefPosX;
float Gy = DefPosY;
float velocityY = DefVelY; // Prędkość spadania
float velocityX = DefVelX;
float time = 0.0f; // Zmienna czasu

// dla GWM
WindowPosition WP_ = {0.0f, 0.0f};
WindowPosition WP;
GWMConfig GWM;
GWMConfig GWM_ = {
	200.0f,
	50.0f,
	" Your PC can produce\n mind boggling effects.",
	1.0f,
	32.5f
};


void DrawCircle(float x, float y, GLfloat radius){
	
	int triangleAmount = 10;
	int i;
	GLfloat twicePi = 2.0 * M_PI;
	
	glPointSize(5.0f);
	glBegin(GL_TRIANGLE_FAN);
	
		glColor3f(cR / 255.0f, cG / 255.0f, cB / 255.0f);
	
		glVertex2f(x, y);
	
		for(i = 0; i <= triangleAmount;i++){
			glVertex2f(
				x + (radius * cos(i * twicePi / triangleAmount)),
				y + (radius * sin(i * twicePi / triangleAmount))
			);
		}
	
	glEnd();
	
}

void DrawEyes(float x, float y){
	glBegin(GL_POINTS);
		
		glColor3f(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f);
		
		glVertex2f(x + 10.0f, y + 5.0f);
		glVertex2f(x + 25.0f, y + 5.0f);
	glEnd();
}

void DrawInvertedTriangle(float x, float y) {
    float halfBase = 10.0f / 2.0f;

    glBegin(GL_TRIANGLES);
        glColor3f(131.0f / 255.0f, 133.0f / 255.0f, 28.0f / 255.0f); // ton pod zółty.

        glVertex2f(x + 29.0f, y - 42.0f);
        glVertex2f(x + 19.0f - halfBase, y);
        glVertex2f(x + 19.0f + halfBase, y);
    glEnd();
}

void DrawSillyLegs(float x, float y){
	glLineWidth(2.5f);
	glBegin(GL_LINES);
		
		glColor3f(0.0f / 255.0f, 0.0f / 255.0f, 0.0f / 255.0f);
		
		glVertex2f(x - 10.0f, y - 32.0f);
		glVertex2f(x - 10.0f, y - 47.0f);
		
		glVertex2f(x + 10.0f, y - 30.0f);
		glVertex2f(x + 10.0f, y - 45.0f);
		
		glVertex2f(x - 16.0f, y - 42.0f);
		glVertex2f(x, y - 53.0f);
		
		glVertex2f(x, y - 41.0f);
		glVertex2f(x + 20.0f, y - 52.0f);
	glEnd();
}

void DrawHand(float x, float y){	DrawCircle(x - 30.0f, y - 10, 10);	};


void SpadochronLinie(float x, float y){
	glLineWidth(2.0f);
	glBegin(GL_LINES);
		glColor3f(130.0f / 255.0f, 126.0f / 255.0f, 126.0f / 255.0f);
		glVertex2f(x - 33.0f, y - 10.0f);
		glVertex2f(x - 53.0f, y + 80.0f);
		
		glVertex2f(x - 33.0f, y - 10.0f);
		glVertex2f(x - 73.0f, y + 100.0f);
		
		glVertex2f(x + 30.0f, y);
		glVertex2f(x + 100.0f, y + 80.0f);
		
		glVertex2f(x + 30.0f, y - 10.0f);
		glVertex2f(x + 140.0f, y + 55.0f);
	glEnd();
}

void SpadochronMaterial(float x, float y){
	glBegin(GL_TRIANGLES);
	
		// Ostatnia część - Po ułożeniu w POLYGON
		
		glColor3f(94.0f/255.0f, 82.0f/255.0f, 35.0f/255.0f);
		// EAC
		glVertex2f(x + 85.5f, y + 102.5f);
		glVertex2f(x + 100.0f, y + 80.0f);
		glVertex2f(x + 130.0f, y + 90.5f);
		
		
		glColor3f(84.0f/255.0f, 73.0f/255.0f, 28.0f/255.0f);
		//ABC
		glVertex2f(x + 100.0f, y + 80.0f);
		glVertex2f(x + 140.0f, y + 55.0f);
		glVertex2f(x + 130.0f, y + 90.5f);
		
		glColor3f(133.0f/255.0f, 114.0f/255.0f, 38.0f/255.0f); // mosiądzowy
		// CDE
		glVertex2f(x + 130.0f, y + 90.5f);
		glVertex2f(x + 103.5f, y + 110.5f);
		glVertex2f(x + 85.5f, y + 102.5f);
		
		// czemu rysowana jako pierwszy fragment?
		// nie muszę męczyć się że płat wystaje.
		
		
		glColor3f(133.0f/255.0f, 13.0f/255.0f, 13.0f/255.0f); // "ciumna" czerwień
		
		glVertex2f(x - 53.0f, y + 80.0f);
		glVertex2f(x - 73.0f, y + 100.0f);
		glVertex2f(x - 3.0f, y + 90.0f);
		
		glColor3f(168.0f/255.0f, 30.0f/255.0f, 30.0f/255.0f); // "juśniejsza" czerwień
		
		glVertex2f(x - 3.0f, y + 90.0f);
		glVertex2f(x - 20.0f, y + 120.0f);
		glVertex2f(x - 73.0f, y + 100.0f );
		
		glColor3f(191.0f/255.0f, 34.0f/255.0f, 34.0f/255.0f); // "joskrowa" czerwień
		
		glVertex2f(x - 73.0f, y + 100.0f);
		glVertex2f(x - 20.0f, y + 120.0f);
		glVertex2f(x - 60.5f, y + 120.0f);
		
		/* ^^^^ zabawne z tym matematykowanie
		 * (73 + 23)/2 = 48
		 * (48 + 73)/2 = 60.5
		 */
		 
		glColor3f(156.0f/255.0f, 89.0f/255.0f, 22.0f/255.0f); // ciemna pomarańcz
		
		glVertex2f(x - 20.0f, y + 115.0f);
		glVertex2f(x - 3.0f, y + 90.0f);
		glVertex2f(x + 40.0f, y + 90.0f);
		 
		glColor3f(194.0f/255.0f, 111.0f/255.0f, 29.0f/255.0f); // jaśniejsza pomarańcz
		
		glVertex2f(x + 40.0f, y + 90.0f);
		glVertex2f( x + 21.5f, y + 120.0f);
		glVertex2f(x - 20.0f, y + 115.0f);
		
		glColor3f(232.0f/255.0f, 123.0f/255.0f, 14.0f/255.0f); // jaśniejsza pomarańcz
		
		glVertex2f(x - 20.0f, y + 115.0f);
		glVertex2f(x + 21.5f, y + 120.0f);
		glVertex2f(x + 0.75f , y + 125.5f); 
		
		glColor3f(181.0f/255.0f, 159.0f/255.0f, 71.0f/255.0f); // ciemna wanilia
		
		glVertex2f(x + 21.5f, y + 120.0f); // a
		glVertex2f(x + 40.0f, y + 90.0f); // b
		glVertex2f(x + 80.0f, y + 90.0f); // c
		
		glColor3f(212.0f/255.0f, 181.0f/255.0f, 57.0f/255.0f); // jasna wanilia
		
		glVertex2f(x + 80.0f, y + 90.0f); // c
		glVertex2f(x + 50.5f, y + 120.0f); // b
		glVertex2f(x + 21.5f, y + 120.0f); // a
		
		glColor3f(42.0f/255.0f, 74.0f/255.0f, 27.0f/255.0f); // ciemna limonka
		
		glVertex2f(x + 53.0f, y + 115.0f); // a
		glVertex2f(x + 80.0f, y + 90.0f); // b
		glVertex2f(x + 120.0f, y + 83.5f); // c
		
		glColor3f(62.0f/255.0f, 102.0f/255.0f, 44.0f/255.0f); // jasna limonka
		
		glVertex2f(x + 120.0f, y + 83.5f); // c
		glVertex2f(x + 80.5f, y + 115.0f); // b
		glVertex2f(x + 53.0f, y + 115.0f); // a 
	glEnd();
		

		
}

/*
	Przed rysowaniem ostatniego fragmentu,
	na początek narysowałem POLYGON, by mniej
	więcej zopisać wymiary.

void LastPiece(float x, float y){
	// Dopasowanie w POLYGON
	// finalnie w TRIANGLES
	
	glBegin(GL_POLYGON);	 
	
		glColor3f(94.0f/255.0f, 82.0f/255.0f, 35.0f/255.0f); // ..?
		glVertex2f(x + 100.0f, y + 80.0f); // A
		glVertex2f(x + 140.0f, y + 55.0f); // B
		glVertex2f(x + 130.0f, y + 90.5f); // C
		glVertex2f(x + 103.5f, y + 110.5f); // D
		glVertex2f(x + 85.5f, y + 102.5f); // E
		
	glEnd();
}

*/

void display(){
	glClearColor(209.0f/255.0f, 163.0f/255.0f, 163.0f/255.0f, 1.0f);	
	glClear(GL_COLOR_BUFFER_BIT);
	
	glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, wWidth, 0, wHeight);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
	
	glColor3f(cR / 255.0f, cG / 255.0f, cB / 255.0f);
	
	// na ten czas statyczne 200, 160 [Gx, Gy]
	// by potem działało przy zmianie współrzędnych
	
	DrawCircle(Gx, Gy, 35); // head
	DrawEyes(Gx, Gy);
	DrawInvertedTriangle(Gx, Gy); // nose
	DrawSillyLegs(Gx, Gy);
	DrawHand(Gx, Gy);
	SpadochronLinie(Gx, Gy);
	SpadochronMaterial(Gx, Gy);
	MakeWindow(&GWM_, &WP_);
	
	WP.PosX = 245.0f;
	WP.PosY = 400.0f;
	GWM.DESC = " MEGC #5 - PSBoi Animated\n Created By ApplehatDoesStuff\n\n Distributed under\n MEGC Projects License";
	GWM.WinX = 250.0f;
	GWM.WinY = 100.0f;
	GWM.DescX = 246.0f;
	GWM.DescY = 474.0f;
	
	MakeWindow(&GWM, &WP);
	
	glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glutSwapBuffers();
}

void update(int value) {
    time += 0.02f; // Aktualizuj czas
    Gy += velocityY; // Aktualizuj pozycję w osi Y
    Gx += velocityX; // Aktualizuj pozycję w osi X

    // Jeśli osiągnie prawą krawędź, zatrzymaj przesuwanie w osi X
    if (Gx > 500.0f) {
        Gx = 500.0f;
        velocityX = 0.0f; // Zatrzymaj przesuwanie w osi X
    }

    // Reset po osiągnięciu dolnej granicy
    if (Gy < -110.0f) {
        Gy = DefPosY; // Resetuj pozycję w osi Y
        Gx = DefPosX;   // Resetuj pozycję w osi X
        velocityX = DefVelX; // Przywróć prędkość w osi X
        time = 0.0f;      // Resetuj czas
    }

    glutPostRedisplay(); // Odśwież scenę
    glutTimerFunc(16, update, 0); // Ustaw ponowne wywołanie funkcji za 16 ms (60 FPS)
}



void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
	gluOrtho2D(0, wWidth, 0, wHeight);
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
	glutReshapeWindow(wWidth, wHeight);
}


int main(int argc, char** argv){
	glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(wWidth, wHeight);

    glutCreateWindow("MEGC #5 - PSBoi animated");

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, update, 0);

    glutMainLoop();

    return 0;
}
