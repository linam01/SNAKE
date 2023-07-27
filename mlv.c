//
// Attention ! 
// Pour pouvoir compiler ce programme sous windows et sous macintosh,
// il faut, pour la déclaration du main, respecter strictement la syntaxe
// suivante :
//
/*
int main( int argc, char *argv[] ){
        int width = 640, height = 480;
        MLV_Image *red_image, *blue_image;
        //
        // Créé et affiche la fenêtre
        //
        MLV_create_window(
                "advanced - 7 - transparency", "transparency", width, height
        );
        MLV_clear_window( MLV_COLOR_GREEN );
        //
        // Lit un fichier et charge l'image contenu dans le
        // fichier en mémoire.
        //
        blue_image = MLV_load_image( "bleu.png" );
        red_image = MLV_load_image( "red.png" );
        MLV_draw_adapted_text_box(
                100, 40, "avec la composante\nalpha d'origine", 4,
                MLV_COLOR_GREEN,  MLV_COLOR_BLACK, MLV_COLOR_GREEN,
                MLV_TEXT_CENTER
        );
        //
        // Affiche l'image
        //
        MLV_draw_image( blue_image, 47, 113 );
        MLV_draw_image( red_image, 47, 306 );
        //
        // Affiche l'image
        //
        MLV_draw_image( blue_image, 187, 185 );
        MLV_draw_image( red_image, 187, 234 );
        //
        // Suprime la transparence de l'image et la remplace 
        // par une transparence uniforme opaque 
        //
        MLV_set_alpha_on_image( MLV_ALPHA_OPAQUE, red_image );
        MLV_set_alpha_on_image( MLV_ALPHA_OPAQUE, blue_image );
        MLV_draw_adapted_text_box(
                330, 20, "sans la\ncomposante\nalpha", 4,
                MLV_COLOR_GREEN,  MLV_COLOR_BLACK, MLV_COLOR_GREEN,
                MLV_TEXT_CENTER
        );
        //
        // Affiche l'image
        //
        MLV_draw_image( blue_image, 328, 113 );
        MLV_draw_image( red_image, 328, 306 );
        //
        // Suprime la transparence de l'image et la remplace 
        // par une transparence uniforme 
        //
        MLV_set_alpha_on_image( 50, red_image );
        MLV_set_alpha_on_image( 127, blue_image );
        
        MLV_draw_adapted_text_box(
                435, 20, "la composante alpha\nest remplacée par une\ncomposante uniforme", 4,
                MLV_COLOR_GREEN,  MLV_COLOR_BLACK, MLV_COLOR_GREEN,
                MLV_TEXT_CENTER
        );
        //
        // Affiche l'image
        //
        MLV_draw_image( blue_image, 468, 113 );
        MLV_draw_image( red_image, 468, 306 );
        //
        // Met à jour l'affichage
        //
        MLV_actualise_window();
        //
        // Attend 2 secondes
        //
        MLV_wait_seconds( 300 );
        //
        // Libère l'image qui a été crée
        //
        MLV_free_image( blue_image );
        MLV_free_image( red_image );
        //
        // Ferme la fenêtre
        //
        MLV_free_window();
        return 0;
	}
*/
#define _ISOC99_SOURCE
#include <math.h>
#include<stdio.h>
#include <MLV/MLV_all.h>
typedef struct _Color {
  int red;
  int green;
  int blue;
} Color;
typedef struct _Point {
  int x;
  int y;
} Point;
typedef struct _Triangle {
  Point R;
  Point G;
  Point B;
} Triangle;
typedef struct _Graphics {
  int width;
  int height;
  int width_box;
  int height_box;
  int height_bar;
  Triangle triangle;
} Graphics;
void saturate_color(
		    const Color* color,
		    Color* result 
		    ){
  int max = 1;
  if( (color->red != 0.0 ) || ( color->green != 0.0 ) || ( color->blue != 0.0 ) ){
    max = color->red;
    if( max < color->blue ) max = color->blue;
    if( max < color->green ) max = color->green;
  }
  result->red = (255 * color->red)/max;
  result->green = (255 * color->green)/max;
  result->blue = (255 * color->blue)/max;
}
typedef enum {
  INSIDE,
  OUTSIDE
} Position_in_the_triangle;
Position_in_the_triangle get_color_of_triangle(
					       const Point *cursor, const Triangle * triangle, Color *result
					       ){
  double rx,ry,gx,gy,bx,by;
  double determinant;
  double a,b,c;
  Position_in_the_triangle position;
  rx = triangle->R.x - cursor->x; 
  gx = triangle->G.x - cursor->x; 
  bx = triangle->B.x - cursor->x; 
  ry = triangle->R.y - cursor->y; 
  gy = triangle->G.y - cursor->y; 
  by = triangle->B.y - cursor->y; 
  determinant = -(by - gy)*rx + (bx - gx)*ry - bx*gy + by*gx;
  a = (-bx*gy + by*gx)/determinant;
  b = (bx*ry - by*rx)/determinant;
  c = (-gx*ry + gy*rx)/determinant;
  if(
     ( a < 0.0 ) || ( b < 0.0 ) || ( c < 0.0 )
     ){
    a = 1/3.0;
    b = 1/3.0;
    c = 1/3.0;
    position = OUTSIDE;
  }else{
    position = INSIDE;
  }
        int nuance = 255;
        result->red = nearbyint( nuance * a );
        result->green = nearbyint( nuance * b );
        result->blue = nearbyint( nuance * c );
        return position;
}
void get_color_of_bar(
		      const Point* cursor, const Graphics* graphics,
		      const  Color* bar_color, Color* result
		      ){
  Color satured_color;
  saturate_color( bar_color, &satured_color );
  double nuance = (cursor->x)/ (double) graphics->width;
  result->red = nearbyint( nuance * satured_color.red );
  result->green = nearbyint( nuance * satured_color.green );
  result->blue = nearbyint( nuance * satured_color.blue );
}
typedef enum {
  TRIANGLE,
  BAR
} Click_position;
Click_position get_color(
			 const Point* cursor,
			 const Graphics* graphics,
			 const Color * bar_color,
			 Color * result
			 ){
  if( cursor->y >= graphics->height- graphics->height_bar ){
    get_color_of_bar(       cursor, graphics, bar_color, result     );
    return BAR;
  }else{
    get_color_of_triangle( cursor, &(graphics->triangle), result );
    return TRIANGLE;
  }
}
void draw_text(
	       const Color *color, const Graphics * graphics, int y_translation
	       ){
  int text_width,text_height;
  MLV_get_size_of_text(
		       "R:%d, G:%d, B:%d, A:%d ",
		       &text_width, &text_height,
		       color->red, color->green, color->blue, MLV_ALPHA_OPAQUE
		       );
        
  MLV_draw_text(
                graphics->width - graphics->width_box - text_width,
                (graphics->height_box/2) - (text_height/2) + y_translation ,
                "R:%d, G:%d, B:%d, A:%d ",
                MLV_COLOR_RED,
                color->red, color->green, color->blue, MLV_ALPHA_OPAQUE
		);
}
void draw_foreground(
		     const Point *cursor, const Graphics * graphics, const Color* bar_color
		     ){
  MLV_load_screen();
  Color cursor_color;
  get_color( cursor, graphics, bar_color, &cursor_color );
  MLV_draw_filled_rectangle( 
			    graphics->width-graphics->width_box,0,
			    graphics->width_box,graphics->height_box,
			    MLV_rgba(
				     cursor_color.red, cursor_color.green, cursor_color.blue,
				     MLV_ALPHA_OPAQUE 
				     )
			     );
  draw_text( &cursor_color, graphics, 0 );
  MLV_actualise_window();
}
void draw_background(
		     const Graphics * graphics,
		     const Color* bar_color,
		     const Color* selection_color
		     ){
  int width = graphics->width;
  int height = graphics->height;
  int height_bar = graphics->height_bar;
  Point point;
  Color color;
  MLV_clear_window( MLV_COLOR_BLACK );
  for( point.x = 0; point.x< width; point.x++){
    for( point.y=0; point.y<height;point.y++ ){
      if(
	 get_color_of_triangle(
			       &point, &(graphics->triangle), &color
			       ) == INSIDE
	 ){
	MLV_draw_point( 
		       point.x, point.y,
		       MLV_rgba(
				color.red, color.green, color.blue,
				MLV_ALPHA_OPAQUE
				)
			);
      }
    }
  }
  int i;
        
  Color bar_color_satured;
  saturate_color( bar_color, &bar_color_satured );
        
  for( i=0; i<width; i++ ){
    MLV_Color color = MLV_rgba(
			       (bar_color_satured.red*i)/width , 
			       (bar_color_satured.green*i)/width, 
			       (bar_color_satured.blue*i)/width,
			       MLV_ALPHA_OPAQUE 
			       ); 
    MLV_draw_line( i, height-height_bar, i, height, color );
  }
  MLV_draw_filled_rectangle(
			    graphics->width-graphics->width_box,
			    graphics->height_box, graphics->width_box,graphics->height_box,
			    MLV_rgba(
				     selection_color->red, selection_color->green, selection_color->blue,
				     MLV_ALPHA_TRANSPARENT
				     )
			    );
  draw_text( selection_color, graphics, graphics->height_box );
  MLV_save_screen();
}
void set_triangle( Graphics * graphics, int posx, int posy, int size ){
  int height = size*sqrt(3)/2.0;
  graphics->triangle.R.x = posx;
  graphics->triangle.R.y = posy + height;
  graphics->triangle.G.x = posx + size;
  graphics->triangle.G.y = posy + height;
  graphics->triangle.B.x = posx + size/2;
  graphics->triangle.B.y = posy;
}
int main( int argc, char *argv[] ){
  Graphics graphics;
  graphics.width=640; graphics.height=480;
  graphics.width_box=120; graphics.height_box=80;
  graphics.height_bar = 40;
  set_triangle( &graphics, 50, 100, 300 );
  Point cursor; cursor.x = 0; cursor.y = 0;
  MLV_Button_state state;
  MLV_Keyboard_button key;
  Color selection_color; 
  get_color_of_triangle( &cursor, &(graphics.triangle), &selection_color );
  Color bar_color = selection_color;
  MLV_Event event = MLV_NONE;
  MLV_create_window( 
		    "medium - 6 - colors", "colors", graphics.width, graphics.height
		     );
  draw_background( &graphics, &bar_color, &selection_color );
  draw_foreground( &cursor, &graphics, &bar_color );
  int continue_to_run = 0;
  while( ! continue_to_run ){
    while(
	  (
	   event = MLV_get_event( 
				 &key, NULL, NULL,
				 NULL, NULL,
				 &(cursor.x), &(cursor.y), NULL,
				 &state
				  ) 
	   ) != MLV_NONE
	  ){
      switch( event ){
      case MLV_MOUSE_MOTION :
	break;
      case MLV_MOUSE_BUTTON :
	if( state == MLV_PRESSED ){
	  if(
	     get_color( 
		       &cursor, &graphics, &bar_color, &selection_color 
			) == TRIANGLE
	     ){
	    bar_color = selection_color;
	  }
	  printf(
		 "MLV_rgba( %d , %d , %d, MLV_ALPHA_OPAQUE )\n",
		 selection_color.red, selection_color.green, 
		 selection_color.blue
		 );
	  draw_background( &graphics, &bar_color, &selection_color );
	  draw_foreground( &cursor, &graphics, &bar_color );
	};
	break;
      case MLV_KEY :
	if( key == MLV_KEYBOARD_ESCAPE ){
	  continue_to_run = 1;
	}
	break;
      default:;
      }
    }
    draw_foreground( &cursor, &graphics, &bar_color );
    MLV_delay_according_to_frame_rate();
  }
  MLV_free_window();
  return 0;
}
