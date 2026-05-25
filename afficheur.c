/*
 * afficheur.c
 *
 *  Created on: Mars 28, 2026
 *      Author: USER
 */
#include "afficheur.h"
#include "photo.h"


char Haut[30];
char Bas[30];
char Gauche [30];
char Droite[30];
char Luminosité[30];
char Ligne1[20];
char Ligne2[20];
char Ligne3[20];



void affiche_installation(){
	ILI9341_Init();
	ILI9341_Rotate(ILI9341_Orientation_Landscape_2);
	ILI9341_Fill(ILI9341_COLOR_ORANGE);
	ILI9341_Puts(58, 10, "SYSTEME EN INSTALLATION....", &Font_7x10, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
	ILI9341_Puts(80, 100, "XXXXXXXXXX", &Font_16x26, ILI9341_COLOR_BLACK, ILI9341_COLOR_ORANGE);
	ILI9341_Puts(150, 220, "Jean-Claude Badlane", &Font_7x10, ILI9341_COLOR_YELLOW, ILI9341_COLOR_BLACK);
}
void affiche_on(){
	sprintf(Haut, "Haut: %4d", haut);
	sprintf(Bas, "Bas: %4d", bas);
	sprintf(Gauche, "Gauche: %4d", gauche);
	sprintf(Droite, "Droite: %4d", droite);

	ILI9341_Puts(5, 60, Haut, &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
	ILI9341_Puts(5, 80, Bas, &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
	ILI9341_Puts(5, 100, Gauche, &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
	ILI9341_Puts(5, 120, Droite, &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);

	//printf("Capteurs -> H:%d B:%d G:%d D:%d\r\n", haut, bas, gauche,droite);
	//HAL_Delay(500)	;
	// Effacer les anciennes barres
	ILI9341_DrawFilledRectangle(160, 63, 260, 75,  ILI9341_COLOR_WHITE);
	ILI9341_DrawFilledRectangle(160, 83, 260, 95,  ILI9341_COLOR_WHITE);
	ILI9341_DrawFilledRectangle(160, 103, 260, 115, ILI9341_COLOR_WHITE);
	ILI9341_DrawFilledRectangle(160, 123, 260, 135, ILI9341_COLOR_WHITE);

	// Dessiner les nouvelles barres
	ILI9341_DrawFilledRectangle(160, 63, 160+barre_haut,   75,  ILI9341_COLOR_BLUE);
	ILI9341_DrawFilledRectangle(160, 83, 160+barre_bas,    95,  ILI9341_COLOR_BLUE);
	ILI9341_DrawFilledRectangle(160, 103, 160+barre_gauche, 115, ILI9341_COLOR_BLUE);
	ILI9341_DrawFilledRectangle(160, 123, 160+barre_droite, 135, ILI9341_COLOR_BLUE);
}
void affiche_haut(){
	ILI9341_Puts(200, 10, "HAUT", &Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
	sprintf(Luminosité, "Luminosite: %4d", haut);
	ILI9341_Puts(5, 60, Luminosité, &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
}
void affiche_bas(){
	ILI9341_Puts(200, 10, "BAS", &Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
	sprintf(Luminosité, "Luminosite: %4d", bas);
	ILI9341_Puts(5, 60, Luminosité, &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
}
void affiche_gauche(){

	ILI9341_Puts(170, 10, "GAUCHE", &Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
	sprintf(Luminosité, "Luminosite: %4d", gauche);
	ILI9341_Puts(5, 60, Luminosité, &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);

}
void affiche_droite(){
	ILI9341_Puts(170, 10, "DROITE", &Font_16x26, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
	sprintf(Luminosité, "Luminosite: %4d", droite);
	ILI9341_Puts(5, 60, Luminosité, &Font_11x18, ILI9341_COLOR_WHITE, ILI9341_COLOR_BLACK);
}
void affiche_nuit(){
	sprintf(Ligne1,"Il fait nuit");
	sprintf(Ligne2,"Le systeme est en veille.");
	sprintf(Ligne3,"Merci.");
    ILI9341_Puts(88, 20, Ligne1, &Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE);
    ILI9341_Puts(22, 60, Ligne2, &Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE);
    ILI9341_Puts(127, 100, Ligne3, &Font_11x18, ILI9341_COLOR_BLACK, ILI9341_COLOR_BLUE);

}

