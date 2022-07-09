#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <string.h>
#include <stdint.h>

//Def von Type BYTE
typedef uint8_t BYTE;

//Def von Konstanten
const int BLOCK_SIZE = 512;

//Anlegen von Buffer für einen Block
BYTE buffer[BLOCK_SIZE];

//Counter für Bilddatei name
int Bildcounter = 0;

//FILE Output;


int main(int argc, char *argv[])
{
    //command-line argument
    //Check command-line argument
    if (argc != 2)
    {
        printf("Falsche Eingabe!\n");
        return 1;
    }

    //Datei öfnen
    FILE *raw_file = fopen(argv[1],"r");
    if (raw_file == 0)
    {
        printf("Konnte nicht geöfnet werden!\n");
        return 1;
    }

    //initialize variables
    char name[] = "000.jpg";
    FILE *output = NULL;

    //--> transfer a Block into a Buffer (521Bytes)
    while (fread(buffer, 1, BLOCK_SIZE, raw_file) == BLOCK_SIZE)
    {
        //looking for JPEGs’ signatures
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0b11100000) >= 1)
        {
            //first JPG?
            if (Bildcounter == 0)
            {
                //first jpg
                output = fopen (name, "w");

                //global variable
                Bildcounter++;
            }
            else
            {
                //Not first jpg
                //Closing last jpg
                fclose(output);

                //Name for next jpg
                sprintf(name,"%03i.jpg", Bildcounter);

                //Create new file
                output = fopen (name, "w");

                //global variable
                Bildcounter++;
            }
        }
        //Write block into current file if jpg signatures found before
        if (Bildcounter)
        {
            fwrite(buffer, BLOCK_SIZE, 1, output);
        }
    }
    //Schließen letzte Datei
    fclose(output);
    fclose(raw_file);
}

