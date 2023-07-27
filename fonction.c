#include<stdio.h>
#include<stdlib.h>
#include <MLV/MLV_all.h>
#include"fonction.h"
#include "config.h"

Serpent initialise_serpent(Serpent *serpent,int x, int y){
  serpent->longueur=1;
  serpent->tete.posX=x;
  serpent->tete.posY=y;
  serpent->queu[0].posX=x;
  serpent->queu[0].posY=y;
  return *serpent;
}

//init la grille BORDURE = -1 VIDE = 0
void initialise_grille(int grille[][GRILLE_HAUTEUR]){
  int i,j;
  for (i=0;i<GRILLE_LARGEUR;i++){
    for(j=0;j<GRILLE_HAUTEUR;j++){
      if(i==0 || j==0 || i==GRILLE_LARGEUR-1 || j==GRILLE_HAUTEUR-1){
	grille[i][j]=BORDURE;
      }
      else 
	grille[i][j]=VIDE;
    }
  }
}

void corps_serpent(Serpent *serpent,int grille[][GRILLE_HAUTEUR]){
  int x,y;
  int i;        
  for(i=serpent->longueur;i>=0;i--){
    if(i==0){
      serpent->queu[i].posX =serpent->tete.posX;
      serpent->queu[i].posY=serpent->tete.posY;           
    }
    else if(i!=0){
      serpent->queu[i].posX=serpent->queu[i-1].posX;
      serpent->queu[i].posY=serpent->queu[i-1].posY;
    }        
    x=serpent->queu[i].posX;
    y=serpent->queu[i].posY;       
    if(i!=serpent->longueur){
      if(i==0){
	grille[x][y]=TETE_SERPENT;
      }
      else
	grille[x][y]=CORP_SERPENT;
    }            
    else{
      grille[x][y]=VIDE;
    } 
  }
}

void affiche_grille_MLV(int grille[][GRILLE_HAUTEUR]){
  int i, j,taille_ligne,taille_colonne; 
  for (i=0; i<GRILLE_LARGEUR; i++){
    for (j=0; j<GRILLE_HAUTEUR; j++){
      taille_ligne=i*30+150;
      taille_colonne=j*30+150;
      if(grille[i][j]==BORDURE){
	MLV_draw_filled_rectangle(taille_colonne,taille_ligne,30,30,MLV_COLOR_BROWN);
      }
      if(grille[i][j]==VIDE){
	MLV_draw_filled_rectangle(taille_colonne,taille_ligne,30,30,MLV_COLOR_BLACK);
      }
      if(grille[i][j]==POMME){
	MLV_draw_filled_circle(taille_colonne+20,taille_ligne+20,10,MLV_COLOR_RED);
      }
      if (grille[i][j]==TETE_SERPENT){
	MLV_draw_filled_rectangle(taille_colonne,taille_ligne,30,30,MLV_COLOR_GREEN);
      }
      if (grille[i][j]==CORP_SERPENT){
	MLV_draw_filled_rectangle(taille_colonne,taille_ligne,30,30,MLV_COLOR_GREEN);
      }             
    }
  }
  MLV_actualise_window(); 
}

// a supprimer 
void afficher_grille(int grille[][GRILLE_HAUTEUR]){
  int i,j;
  for(i=0;i<GRILLE_LARGEUR;i++){
    for(j=0;j<GRILLE_HAUTEUR;j++){
      if(grille[i][j]==BORDURE){
	printf("$");
      }
      if(grille[i][j]==POMME){
	printf("P");
      }
      if(grille[i][j]==VIDE){
	printf(" ");
      }
      if (grille[i][j]==TETE_SERPENT){
	printf("B");
      }
      if (grille[i][j]==CORP_SERPENT){
	printf("*");
      }             
    }
    printf("\n");  
  }
}

//met une pomme dans la grille
Pomme poser_pomme(int grille[][GRILLE_HAUTEUR],Pomme *pomme){
  int i,j;
  do{
    i=rand()%GRILLE_LARGEUR;
    j=rand()%GRILLE_HAUTEUR;
  }while(grille[i][j] != VIDE);
  pomme->posX=i;
  pomme->posY=j;
  grille[pomme->posX][pomme->posY]= POMME;
  return *pomme;
}

//test condition de defaite
int defaite(int grille[][GRILLE_HAUTEUR],Serpent *serpent){
  int i,j;
  for(i=0;i<GRILLE_LARGEUR;i++){
    for(j=0;j<GRILLE_HAUTEUR;j++){         
      if ( serpent->tete.posX==0 || serpent->tete.posY==0 ||serpent->tete.posY==GRILLE_HAUTEUR-1 || serpent->tete.posX==GRILLE_LARGEUR-1 ){
	printf("GAME OVER !\n");
	return 1;
      } 
    }
  }
  for(i=1;i<serpent->longueur;i++){
    if(serpent->tete.posX == serpent->queu[i].posX && serpent->tete.posY == serpent->queu[i].posY){
      printf("GAME OVER !\n");
      return 1;
    }
  }
  return 0;
}
    
/*
  void deplacement(int grille[][GRILLE_HAUTEUR],MLV_KEYBOARD sym,Serpent *serpent){
  switch(sym){
  case MLV_KEYBOARD_LEFT:
  gauche(serpent);
  break;
  case MLV_KEYBOARD_RIGHT:
  droite(serpent);
  break;
  case MLV_KEYBOARD_UP:
  haut(serpent);
  break;
  case MLV_KEYBOARD_DOWN:
  bas(serpent);
  break;
  }
  }
*/

//deplacement : manque a faire suivre la tete par le corp
void gauche(Serpent *serpent){
  serpent->tete.posY--;
}
void droite(Serpent *serpent){
  serpent->tete.posY++;
}
void bas(Serpent *serpent){
  serpent->tete.posX++;  
}
void haut(Serpent *serpent){
  serpent->tete.posX--;    
}

//test si le serpent mange une pomme 
int manger_pomme(Pomme *pomme,Serpent *serpent){
  if(pomme->posX == serpent->tete.posX && pomme->posY == serpent->tete.posY)
    return 1;
  else
    return 0;
}

void sauvegarde_partie(int grille[][GRILLE_HAUTEUR],Serpent *serpent,Pomme *pomme, char i){
  FILE* fichier=NULL;
  char nom_fichier[24];
  sprintf(nom_fichier,"%c_sauvegarde_partie.bin",i);
  
  printf("SAUV dans : <%s>\n",nom_fichier);
  fichier=fopen(nom_fichier,"wb");
  if(fichier==NULL){
    printf("impossible d'ouvrir le fichier\n");
    exit(EXIT_FAILURE);
  }
  fwrite(grille,sizeof(int),1,fichier);
  fwrite(serpent,sizeof(Serpent),1,fichier);
  fwrite(pomme,sizeof(Pomme),1,fichier);
  fclose(fichier);
  printf("FIN SAUV\n");

}

void sauvegarde_score(Score *score){
  FILE* fichier=NULL;
  fichier=fopen("sauvegarde_score.bin","wb");
  if(fichier==NULL){
    printf("impossible d'ouvrir le fichier\n");
    exit(EXIT_FAILURE);
  }
  fwrite(score,sizeof(Score),1,fichier);
  fclose(fichier);
}
void chargement_score(Score *score){
  FILE* fichier=NULL;
  fichier=fopen("sauvegarde_score.bin","rb");
  if(fichier==NULL){
    printf("impossible d'ouvrir le fichier\n");
    exit(EXIT_FAILURE);
  }
  if(fread(score,sizeof(Score),1,fichier)!=1){
    printf("erreur1");
    exit(0);
  }
  fclose(fichier);
}
void chargement_partie(int grille[][GRILLE_HAUTEUR],Serpent *serpent,Pomme *pomme, char i){
  FILE* fichier=NULL;
  char nom_fichier[24];
  sprintf(nom_fichier,"%c_sauvegarde_partie.bin",i);
  
  printf("SAUV dans : <%s>\n",nom_fichier);
  fichier=fopen(nom_fichier,"rb");
  if(fichier==NULL){
    printf("impossible d'ouvrir le fichier\n");
    exit(EXIT_FAILURE);
  }
  if(fread(grille,sizeof(int),1,fichier)!=1){
    printf("erreur1");
    exit(0);
  }
  if(fread(serpent,sizeof(Serpent),1,fichier)!=1){
    printf("erreur2");
    exit(0);
  }
  if(fread(pomme,sizeof(Pomme),1,fichier)!=1){
    printf("erreur3");
    exit(0);
  }
  fclose(fichier);
}

void score_(Score *score){
  int i;
  score->score++;
  if(score->score > score->m_score[0]){
    //
    for(i=9;i>0;i--){
      score->m_score[i] = score->m_score[i-1];
    }
    // a faire uniqument en fin de partie ou a la pause ou quand on quitte une partie 
    score->m_score[0]=score->score;
  }
}

void afficher_text_jeux(Score *score,char *nom){
  char score_mlv[20],m_score_mlv[20];
  nom="lina";
  sprintf(score_mlv,"%d",score->score);
  sprintf(m_score_mlv,"%d",score->m_score[0]);
  
  MLV_draw_text(150,50,"SCORE : ",MLV_COLOR_WHITE);
  MLV_draw_text(370,50,score_mlv,MLV_COLOR_WHITE);
  
  MLV_draw_text(900,50,"MEILLEUR SCORE : ",MLV_COLOR_WHITE);
  MLV_draw_text(1400,50,m_score_mlv,MLV_COLOR_WHITE);
  MLV_actualise_window();
}

/*
void niveau(int niveau,Score *score,Piege *piege,int grille[][GRILLE_HAUTEUR]){
  int i,j;
  if(score->score==3){
    do{
      i=rand()%GRILLE_LARGEUR;
      j=rand()%GRILLE_HAUTEUR;
    }while(Grille[i][j] != VIDE);
    piege->posX=i;
    piege->posY=j;
    grille[i][j]= BORDURE;
    // return *piege;
  }
}
*/

void jeux(int grille[][GRILLE_HAUTEUR],Serpent *serpent,Pomme *pomme,Score *score){
  int i =1;
  MLV_Button_state state;
  MLV_Event event = MLV_NONE;
  MLV_Keyboard_button sym1 =MLV_KEYBOARD_LEFT, sym =MLV_KEYBOARD_LEFT ;
  afficher_text_jeux(score,"lina");
  while(defaite(grille,serpent)!=1){
    sym1=sym;
    event = MLV_get_event(&sym,NULL,NULL,NULL, NULL,NULL,NULL, NULL, &state);
    if(event==MLV_NONE || state == MLV_RELEASED){
      sym=sym1;
      event=MLV_KEY;
      state=MLV_PRESSED;
    }
    switch(event){
    case MLV_KEY :
      if (state == MLV_PRESSED){ 
	switch(sym){
	case MLV_KEYBOARD_q :
	  sauvegarde_partie(grille,serpent,pomme,i);
	  sauvegarde_score(score);
	  exit(0);
	  break;
	case MLV_KEYBOARD_LEFT :
	  /* if(tmp_sym == MLV_KEYBOARD_LEFT){
	     haut(serpent);}
	     else{ */ 
	  gauche(serpent);
	  // }
	  break;
	case MLV_KEYBOARD_RIGHT :
	  /* if(tmp_sym == MLV_KEYBOARD_RIGHT){
	     bas(serpent);
	     }else{ */
	  droite(serpent);
	  //}
	  break;
	case MLV_KEYBOARD_DOWN :
	  /*if(tmp_sym == MLV_KEYBOARD_DOWN){
	    droite(serpent);
	    }else{*/
	  bas(serpent);
	  //}
	  break;
	case MLV_KEYBOARD_UP :
	  /*if(tmp_sym == MLV_KEYBOARD_UP){
	    gauche(serpent);
	    }else{*/
	  haut(serpent);
	  //}
	  break;
	case MLV_KEYBOARD_SPACE :
	  // sauvegarde_score(score);
	  // sauvegarde_partie(grille,serpent,pomme,i);
	  /*for(int i=0;i<10;i++){
	    printf("au momeent de la pause  MEILLEUR SCORE %d : %d\n",i,score->m_score[i]);
	    }*/
	  choix_save_partie();
	  MLV_wait_keyboard(NULL,NULL,NULL);
	  break;
	default :
	  break;
	}
      }
    }
    //  tmp_sym=sym;
    if(manger_pomme(pomme,serpent)==1){
      poser_pomme(grille,pomme);
      score_(score);
      serpent->longueur++;
      corps_serpent(serpent,grille);
      afficher_text_jeux(score,"lina");
    }
    else{
      corps_serpent(serpent,grille);
    }
    affiche_grille_MLV(grille);
    afficher_grille(grille);
   
    MLV_wait_milliseconds(300);
  }
  affichade_defaite("text-1670516159521.png");
}


void nouvelle_partie(int grille[][GRILLE_HAUTEUR], Serpent *serpent,Pomme *pomme,Score *score){
  MLV_clear_window(MLV_COLOR_BLACK);
  fond_image();
  initialise_grille(grille);
  *serpent = initialise_serpent(serpent,GRILLE_LARGEUR/2,GRILLE_HAUTEUR/2);
  *pomme = poser_pomme(grille,pomme);
  corps_serpent(serpent,grille);
  affiche_grille_MLV(grille);
  afficher_grille(grille); 
  score->score=0;
  jeux(grille,serpent,pomme,score);  
}

/*  char direction;
    while(defaite(grille,serpent)!=1){
    printf("score %d \n",score->score);
    printf("VOTRE CHOIX g d h b ? ");
    direction = getchar();
    printf("%d %d \n",serpent->queu[0].posX,serpent->queu[0].posY);
    printf("%c \n",direction);
    f_direction(grille,direction,serpent);
    
    if(manger_pomme(pomme,serpent)== 1){
    poser_pomme(grille,pomme);
    //score->score++;
    score_(score);
    serpent->longueur++;
    corps_serpent(serpent,grille);
    }
    else{
    corps_serpent(serpent,grille);
    }
    viderBuffer();
    afficher_grille(grille);
    sauvegarde_partie(grille,serpent,pomme);
    }*/
