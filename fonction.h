#include"type.h"


Serpent initialise_serpent(Serpent *serpent,int x, int y);
void corps_serpent(Serpent *serpent,int grille[][GRILLE_HAUTEUR]);
void initialise_grille(int grille[][GRILLE_HAUTEUR]);
void afficher_grille(int grille[][GRILLE_HAUTEUR]);
Pomme poser_pomme(int grille[][GRILLE_HAUTEUR],Pomme *pomme);
int defaite(int grille[][GRILLE_HAUTEUR],Serpent *serpent);
void affiche_grille_MLV(int grille[][GRILLE_HAUTEUR]);

void gauche(Serpent *serpent);
void droite(Serpent *serpent);
void bas(Serpent *serpent);
void haut(Serpent *serpent);

int manger_pomme(Pomme *pomme,Serpent *serpent);
void f_direction(int grille[][GRILLE_HAUTEUR], char direction,Serpent *serpent);


void sauvegarde_partie(int grille[][GRILLE_HAUTEUR],Serpent *serpent,Pomme *pomme, char i);
void chargement_partie(int grille[][GRILLE_HAUTEUR],Serpent *serpent,Pomme *pomme, char i);

void score_(Score *score);
void sauvegarde_score(Score *score);
void chargement_score(Score *score);


void afficher_text_jeux(Score *score,char *nom);

void jeux(int grille[][GRILLE_HAUTEUR],Serpent *serpent,Pomme *pomme,Score *score);
void nouvelle_partie(int grille[][GRILLE_HAUTEUR], Serpent *serpent,Pomme *pomme,Score *score);
void continuer_partie(int grille[][GRILLE_HAUTEUR], Serpent *serpent,Pomme *pomme,Score *score);
