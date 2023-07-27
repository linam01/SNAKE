#include"config.h"


/**
 *@param structure pour le jeux

 */
typedef struct Pomme{
  int posX;
  int posY;
}Pomme;

typedef struct Tete_Serpent{ 
  int posX;
  int posY;
}Tete_Serpent;

typedef struct Corp_serpent{ 
  int posX;
  int posY;
}Corp_serpent;

typedef struct Serpent{ 
  int longueur;
  Corp_serpent queu[GRILLE_LARGEUR*GRILLE_HAUTEUR];
  Tete_Serpent tete;
}Serpent;

typedef struct Score{
  int m_score[10];
  int score;
}Score;

typedef struct Piege{
  int posX;
  int posY;
  int niveau;
}Piege; 



int grille[GRILLE_LARGEUR][GRILLE_HAUTEUR];
Pomme pomme;
Score score;
Serpent serpent;
