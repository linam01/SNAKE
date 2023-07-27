#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include <MLV/MLV_all.h>
#include"fonction.h"
#include"config.h"

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
Bouton creer_bouton(int x, int y,int largeur,int hauteur,char *texte,Tab_btn *tab,void *fonction);void fond_image();
void dessiner_bouton(Bouton *btn);
void menu();
void afficher_m_score(Score *score);
void affichade_defaite(char *img);
void affichage_regle();
void init();
void afficher_m_score(Score *score);
void affichage_regle();
void affichade_defaite(char *img);
void fond_image();

int main(){
  srand(time(NULL));
  init();
  exit(0);  
}

void go(int j){
  int i;
  MLV_clear_window(MLV_COLOR_BLACK);
  printf("GO \n");
  printf("j %d \n",j);
  chargement_score(&score);
  for(i=0;i<10;i++){
    printf("apres chargment dans go MEILLEUR SCORE %d : %d\n",i,score.m_score[i]);
  }
  switch(j){
  case 0:
    nouvelle_partie(grille,&serpent,&pomme,&score);
    printf("nvl partie\n");
    break;
  case 1:
    printf("continuer partie\n");
    choix_partie();
    break;
  case 2:
    printf("instruction\n");
    affichage_regle();
    break;
  case 3:
    printf("score\n");
    afficher_m_score(&score);
    break;
  case 4:
    printf("quitter\n");
    exit(0);
    break;
  }
}

//sauvegarde partie
void choix_sauv(int j){ 
  switch(j){
  case 0:
    printf("j : %d\n",j);

    sauvegarde_partie(grille,&serpent,&pomme,'1');
    break;
  case 1:
    sauvegarde_partie(grille,&serpent,&pomme,'2');
    break;
  case 2:
    sauvegarde_partie(grille,&serpent,&pomme,'3');
    break;
  case 3:
    sauvegarde_partie(grille,&serpent,&pomme,'4');
    break;
  }
}

void choix(int j){    
  switch(j){
  case 0:
    chargement_partie(grille,&serpent,&pomme,'1');
    break;
  case 1:
    chargement_partie(grille,&serpent,&pomme, '2');
    break;
  case 2:
    chargement_partie(grille,&serpent,&pomme,'3');
    break;
  case 3:
    chargement_partie(grille,&serpent,&pomme,'4');
    break;
  }
  continuer_partie(grille,&serpent,&pomme,&score);
}


int choix_partie(){
  Bouton btn,btn1,btn2,btn3;
  Tab_btn tab;
  char i;
  tab.nb_btn=0;
  btn=creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6,500,100,"PARTIE 1",&tab,choix);
  btn1=creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6+150,500,100,"PARTIE 2",&tab,choix);
  btn2=creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6+300,500,100,"PARTIE 3",&tab,choix);
  btn3=creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6+450,500,100,"PARTIE 4",&tab,choix);
  dessiner_bouton(&btn);
  dessiner_bouton(&btn1);
  dessiner_bouton(&btn2);
  dessiner_bouton(&btn3);
  MLV_actualise_window();
  event2(tab);
  MLV_clear_window(MLV_COLOR_BLACK);
}

int choix_save_partie(){
  Bouton btn,btn1,btn2,btn3;
  Tab_btn tab;
  char i;
  tab.nb_btn=0;
  btn=creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6,500,100,"PARTIE 1",&tab,choix_sauv);
  btn1=creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6+150,500,100,"PARTIE 2",&tab,choix_sauv);
  btn2=creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6+300,500,100,"PARTIE 3",&tab,choix_sauv);
  btn3=creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6+450,500,100,"PARTIE 4",&tab,choix_sauv);
  dessiner_bouton(&btn);
  dessiner_bouton(&btn1);
  dessiner_bouton(&btn2);
  dessiner_bouton(&btn3);
  MLV_actualise_window();
  event2(tab);
  MLV_clear_window(MLV_COLOR_BLACK);
}


void continuer_partie(int grille[][GRILLE_HAUTEUR], Serpent *serpent,Pomme *pomme,Score *score){
  int i;
  MLV_clear_window(MLV_COLOR_BLACK);
  fond_image();
  initialise_grille(grille);
  chargement_score(score);
  *pomme = poser_pomme(grille,pomme);
  affiche_grille_MLV(grille);
  afficher_grille(grille);
  score->score=serpent->longueur-1;
  jeux(grille,serpent,pomme,score); 
}

void init(){
  int x,y;
  MLV_create_window_with_default_font("beginner -2 -snake","SNAKE",
				      WINDOW_LARGEUR,
				      WINDOW_HAUTEUR,
				      "Supergame-L3vxW.otf",
				      60);
 
   MLV_Image *image2= MLV_load_image("text-1670504022745.png");
  fond_image();
  MLV_draw_image(image2,400,300);
  MLV_actualise_window();
  MLV_wait_mouse(&x,&y);
  MLV_free_image(image2);
  menu();
  MLV_free_window();
}

void affichage_regle(){
  MLV_clear_window(MLV_COLOR_BLACK);
  Tab_btn tab;
  Bouton btn;
  tab.nb_btn=0;
  btn =creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6+450,500,100,"MENU",&tab,menu);
  MLV_draw_text(200,200,"règles ",MLV_COLOR_WHITE);
  dessiner_bouton(&btn);
  MLV_actualise_window();
  event2(tab);
}

void affichade_defaite(char *img){
  MLV_Image *image= MLV_load_image(img);
  Bouton btn;
  Tab_btn tab;
  tab.nb_btn=0;
  btn=creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6+450,500,100,"MENU",&tab,menu);
  MLV_draw_image(image,600,400);
  dessiner_bouton(&btn);
  MLV_actualise_window();
  event2(tab);
}

void afficher_m_score(Score *score){
  MLV_clear_window(MLV_COLOR_BLACK);
  Tab_btn tab;
  Bouton btn;
  char m_score_mlv[10];
  int i;
  tab.nb_btn=0;
  btn=creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6+450,500,100,"MENUE",&tab,menu);
  for(i=0;i<10;i++){
    sprintf(m_score_mlv,"%d",score->m_score[i]);
    MLV_draw_text(500,i*50+50,"lina",MLV_COLOR_WHITE);
    MLV_draw_text(700,i*50+50,m_score_mlv,MLV_COLOR_WHITE);
  }
  dessiner_bouton(&btn);
  MLV_actualise_window();
  event2(tab);
}

void menu(){
  MLV_clear_window(MLV_COLOR_BLACK);
  fond_image();
  Bouton btn,btn2,btn3,btn4,btn5;
  Tab_btn tab;
  tab.nb_btn =0;
  btn  = creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6,500,100,"JOUER",&tab,go); 
  btn2 = creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6+150,500,100,"CONTINUER",&tab,go);
  btn3 = creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6+300,500,100,"INSTRUCTION",&tab,go);
  btn4 = creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6+450,500,100,"SCORE",&tab,go);
  btn5 = creer_bouton(WINDOW_LARGEUR/3,WINDOW_HAUTEUR/6+600,500,100,"QUITTER",&tab,go);
 
  dessiner_bouton(&btn);
  dessiner_bouton(&btn2);
  dessiner_bouton(&btn3);
  dessiner_bouton(&btn4);
  dessiner_bouton(&btn5);
  MLV_actualise_window();
  event2(tab);
}


void event2(Tab_btn tab){
  MLV_Event event;
  MLV_Button_state state;
  MLV_Keyboard_button sym;
  int sortie=0;
  int x,y;
  while(sortie==0){ 
    event = MLV_get_event(&sym, NULL, NULL, NULL, NULL, &x, &y, NULL, &state);
    switch(event){
    case MLV_KEY :
      if (state == MLV_PRESSED)
	if(sym == MLV_KEYBOARD_q){
	  printf("touche pressée \n");
	  exit(0);
	}
      break;
    case MLV_MOUSE_BUTTON :
      if (state == MLV_PRESSED){
	printf("mousse pressée \n");
	printf("pos mousse x  %d y %d \n",x,y);
	clicke(x,y,tab);
	break; 
      }
    }
  }
}

void dessiner_bouton(Bouton *btn){
  MLV_draw_text_box(btn->x,
		    btn->y,
		    btn->largeur,btn->hauteur,
		    btn->text,
		    TAILLE_INTERLIGNE,
		    MLV_COLOR_WHITE,
		    MLV_COLOR_ORANGE,
		    MLV_rgba(0,0,0,MLV_ALPHA_TRANSPARENT),
		    MLV_TEXT_CENTER,MLV_HORIZONTAL_CENTER,MLV_VERTICAL_CENTER);
}

Bouton creer_bouton(int x, int y,int largeur,int hauteur,char *texte,Tab_btn *tab,void *fonction){
  Bouton btn;
  btn.x =x;
  btn.y =y;
  btn.hauteur=hauteur;
  btn.largeur=largeur;
  btn.text = texte;
  btn.fonction = fonction;
  tab->tab_btn[tab->nb_btn]=btn;
  tab->nb_btn++;
  return btn;
}

void fond_image(){
  MLV_Image *image= MLV_load_image("1140191.jpg");
  int image_width, image_height;
  MLV_resize_image_with_proportions(image,WINDOW_LARGEUR,WINDOW_HAUTEUR);
  MLV_get_image_size( image, &image_width, &image_height);
  MLV_change_window_size( image_width, image_height );
  MLV_draw_image(image,0,0);
}

int clicke(int x,int y,Tab_btn tab){
  int i;
  /* int tabx;
     int taby;
     int tabxlargeur;
     int tabxhauetur;*/
  printf(" \nDANS CLIQUE\n");
  for(i=0;i< tab.nb_btn;i++){
    /* tabx =tab.tab_btn[i].x;
       taby =tab.tab_btn[i].y;
       tabxlargeur =tab.tab_btn[i].x +tab.tab_btn[i].largeur;
       tabxhauetur =tab.tab_btn[i].y + tab.tab_btn[i].hauteur;*/
    // printf(" nb tab %d\n tabx %d\n,tab y%d\n,taxlargeur%d\n tabx hauteur %d\n", tab.nb_btn,tabx,taby ,tabxlargeur, tabxhauetur);
    if(x >= tab.tab_btn[i].x && y >= tab.tab_btn[i].y
       &&(x<=tab.tab_btn[i].x +tab.tab_btn[i].largeur)
       &&(y <=tab.tab_btn[i].y + tab.tab_btn[i].hauteur)){
      printf("OKOK\n");
      tab.tab_btn[i].fonction(i);
    }
  }
  printf("FIN DU CLIQUE \n");
}
