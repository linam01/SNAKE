#include"bouton.h"
#include"config.h"


int clicke(int x,int y,Tab_btn tab);
void event2(Tab_btn tab);
void dessiner_bouton(Bouton *btn);
Bouton creer_bouton(int x, int y,int largeur,int hauteur,char *texte,Tab_btn *tab,void *fonction);
void menu();

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
		    MLV_rgba(85,85,85,MLV_ALPHA_TRANSPARENT),
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
