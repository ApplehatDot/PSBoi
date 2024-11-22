/*	GWM-GL [Graphical Window Manager for GL]
 * Cross-platform solution for simple window notificaions
 * 
 */ 

#include <GL/freeglut.h>
#include <GL/glut.h>
#include <stdbool.h>
#include <string.h>
#include "GWM.h"
 
void RenderText(GWMConfig* GWM, const char* text) {

    glRasterPos2f(GWM->DescX, GWM->DescY);
    glutBitmapString(GLUT_BITMAP_8_BY_13, text);
        
    
}

void MakeWindow(GWMConfig* GWM, WindowPosition* WP) {
	
    glBegin(GL_LINES);
        // Linia dolna
        glVertex2f(WP->PosX, WP->PosY);
        glVertex2f(WP->PosX + GWM->WinX, WP->PosY);
		
		glVertex2f(WP->PosX, WP->PosY + 10.0f);
        glVertex2f(WP->PosX + GWM->WinX, WP->PosY + 10.0f);
		glVertex2f(WP->PosX, WP->PosY);
        glVertex2f(WP->PosX + GWM->WinX, WP->PosY + 10.0f);
		glVertex2f(WP->PosX, WP->PosY + 10.0f);
        glVertex2f(WP->PosX + GWM->WinX, WP->PosY);

        // Linia prawa
        glVertex2f(WP->PosX + GWM->WinX, WP->PosY);
        glVertex2f(WP->PosX + GWM->WinX, WP->PosY + GWM->WinY);

        // Linia górna
        glVertex2f(WP->PosX + GWM->WinX, WP->PosY + GWM->WinY);
        glVertex2f(WP->PosX, WP->PosY + GWM->WinY);

        // Linia lewa
        glVertex2f(WP->PosX, WP->PosY + GWM->WinY);
        glVertex2f(WP->PosX, WP->PosY);

        // Dodatkowe linie wewnętrzne (proporcjonalne)
        int numLines = 2; // Liczba dodatkowych linii
        float gap = GWM->WinY * 0.05f; // Przerwa między liniami (5% wysokości okna)

        for (int i = 1; i <= numLines; i++) {
            float offset = GWM->WinY - i * gap; // Pozycja linii poniżej górnej krawędzi
            glVertex2f(WP->PosX, WP->PosY + offset);
            glVertex2f(WP->PosX + GWM->WinX, WP->PosY + offset);
        }
    glEnd();


    // Renderowanie tekstu z obsługą nowych linii i łamaniem tekstu
    RenderText(GWM, GWM->DESC); // Przekazujemy maksymalną szerokość okna
}
