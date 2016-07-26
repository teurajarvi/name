// Write a program that can save (appending not overwriting!) 
// a name into a file and display all names when asked. Write a
// simple UI inside a loop for this purpose. 

/* yleiset kirjastot */
#include <stdio.h>  /* lukemista ja tulostusta varten */
#include <ctype.h>  /* tyypin tarkistamista varten    */
#include <stdlib.h> /* muuntaa merkin luvuksi         */
#include <string.h> /* string pituuden laskeminen     */

/* omat headerit */
#include "name.h"

/* tässä tiedostossa näkyvät muuttujat */
FILE *nimi_tiedosto;
char user_nimi[50];

/* ohjelman pääfunktio */
int main(void)
	{
	printf( " Kirjoita nimi niin tallennan sen taulukkoon. \n" );

	printf( "\n Nimi: " );
	scanf( "%s", user_nimi );

    kirjoita_nimi_taulukkoon( );
    tulosta_nimet( );

	return 0;
	}

void kirjoita_nimi_taulukkoon( )
    {
    char *nimi;
    int file_size;

    nimi = malloc( strlen( user_nimi ) );
    strcpy( nimi, user_nimi );

    // luodaan/avataan tiedosto append moodissa nimiä varten
    nimi_tiedosto = fopen( "nimi.txt", "a" );

    // tämä on se helpoin vaihtoehto toteuttaa tämä
    // kirjoitetaan nimi tiedostoon ja lisätään loppuun rivinvaihto
    fputs( nimi, nimi_tiedosto );
    fputs( "\n", nimi_tiedosto );

#if 0
    // toteutetaan monimutkaisempi vaihtoehto
    // kuljetaan tiedoston loppuun
    fseek( nimi_tiedosto, 0, SEEK_END );
    // kysytään tiedoston koko
    ftell( nimi_tiedosto );
    // kopioidaan nimi tiedostoon
    fwrite( nimi, 1, sizeof(nimi), nimi_tiedosto );
    fseek( nimi_tiedosto, 0, SEEK_END );
    ftell( nimi_tiedosto );
    // lisätään rivinvaihto
    fputs( "\n", nimi_tiedosto );
#endif

    printf( "\n Lisättiin nimi: %s\n", nimi );

    // vapautetaan nimi ja suljetaan tiedosto
    free( nimi );
    fclose( nimi_tiedosto );
    }

void tulosta_nimet( )
    {
    int character;

    // avataan tiedosto nimien tulostusta varten
    nimi_tiedosto = fopen( "nimi.txt", "r" );

    if ( NULL == nimi_tiedosto )
        {
        printf( "FILE open error" );
        }
    else
        {
        printf( "\n Tulostetaan kaikki nimet tiedostosta: \n\n" );
        while(1)
            {
            character = fgetc( nimi_tiedosto );
        
            if( feof( nimi_tiedosto ) )
                { 
                break;
                }

            printf( "%c", character );
            }

        printf( "\n" );

        // suljetaan tiedosto
        fclose( nimi_tiedosto );
        }
    }
