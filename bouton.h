

typedef struct Bouton{
  int x;
  int y;
  char *text;
  MLV_Font *font;
  int largeur;
  int hauteur;
  void (*fonction)(int j);
}Bouton;

typedef struct Tab_btn{
  int nb_btn;
  Bouton tab_btn[5];
}Tab_btn;

int clicke(int x,int y,Tab_btn tab);
void event2(Tab_btn tab);
void dessiner_bouton(Bouton *btn);
Bouton creer_bouton(int x, int y,int largeur,int hauteur,char *texte,Tab_btn *tab,void *fonction);
void menu();
