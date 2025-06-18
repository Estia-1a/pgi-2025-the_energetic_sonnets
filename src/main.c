
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <estia-image.h>
#include <getopt.h>

#include "features.h"
#include "utils.h"
#include "argsparse.h"

int main(int argc, char **argv) {
  /*To use debug mode: 
   - add --debug: freud.exe --debug -f images/input/image.jpeg
   or 
   - Simply run your compiled project with start button on the blue menu bar at the bottom of the VS Code window.
   */

  /*DO NOT EDIT THIS PART*/
  Config configuration ;
  parse_arguments( argc, argv, &configuration ) ;
  check_debug_mode(configuration);
  check_file();
  if ( strncmp( configuration.command, "helloworld", 10 ) == 0 ) {
    /* helloworld() function is defined in feature.h and implemented in feature.c */
    helloWorld();
  } else if ( strcmp( configuration.command, "dimension" ) == 0 ) {
    /* helloworld() function is defined in feature.h and implemented in feature.c */
    dimension(configuration.filenames[0]);
  } else if ( strncmp( configuration.command, "first_pixel", 11 ) == 0 ) {
    /* first_pixel() function is defined in feature.h and implemented in feature.c */
    first_pixel(configuration.filenames[0]);
  } else if ( strncmp( configuration.command, "color_desaturate", 16 ) == 0 ) {
    /* first_pixel() function is defined in feature.h and implemented in feature.c */
    color_desaturate(configuration.filenames[0]);
  } else if ( strncmp( configuration.command, "color_gray_luminance", 20 ) == 0 ) {
    /* first_pixel() function is defined in feature.h and implemented in feature.c */
    color_gray_luminance(configuration.filenames[0]);
  
  } else if ( strncmp( configuration.command, "color_green", 11 ) == 0 ) {
    /* first_pixel() function is defined in feature.h and implemented in feature.c */
    color_green(configuration.filenames[0]);

   } else if ( strncmp( configuration.command, "color_invert", 12 ) == 0 ) {
    /* first_pixel() function is defined in feature.h and implemented in feature.c */
    color_invert(configuration.filenames[0]);
   }

    else if ( strncmp( configuration.command, "color_red", 9 ) == 0 ) {
    /* first_pixel() function is defined in feature.h and implemented in feature.c */
    color_red(configuration.filenames[0]);
   }

    else if (strncmp(configuration.command, "max_component", 13) == 0) {
        /* max_component() function is defined in features.h and implemented in features.c */
        if (argc < 4) {
            printf("Erreur: Composante manquante (R, G, ou B).\n");
   }
    else if (strncmp(configuration.command, "max_pixel", 9) == 0) {
        /* max_pixel() function is defined in features.h and implemented in features.c */
        max_pixel(configuration.filenames[0]);
    }
    else if (strncmp(configuration.command, "min_component", 13) == 0) {
        /* min_component() function is defined in features.h and implemented in features.c */
        if (argc < 4) {
            printf("Erreur: Composante manquante (R, G, ou B).\n");
            return 1;
        }
    }    
  return 0;

  
}