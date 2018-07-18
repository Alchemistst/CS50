// Helper functions for music

#include <cs50.h>

#include "helpers.h"

#include <math.h>

#include <string.h>

//Functions prototypes
int ascii_int(char a);

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // TODO
    int num = 0, den = 0;
    bool is_denominator = false;
    //Iterate the string
    for (int i = 0, n = strlen(fraction); i < n; i++)
    {
        if (is_denominator && fraction[i] != '/')
        {
            den = ascii_int(fraction[i]);
        }
        else if (fraction[i] != '/')
        {
            num = ascii_int(fraction[i]);
        }
        else
        {
            is_denominator = true;
        }
    }

    //return de number of eighths
    return (8 / den) * num;

}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char letter;
    char accidental = '?';
    char octave;

    char notes[] = {'C', 'D', 'E', 'F', 'G', 'A', 'B'};

    double semitones = -9;
    int counter = 0;

    letter = note[0]; //Letter of the note

    //Segmenting the string
    if (strlen(note) == 2)
    {
        octave = note[1];
    }
    else
    {
        accidental = note[1];
        octave = note[2];
    }

    //Figuring out semitones for the note to get to A
    while (letter != notes[counter])
    {
        semitones++;
        if (notes[counter] != 'E')
        {
            semitones ++;
        }
        counter++;
    }

    //Figuring out semitones for the octave to get to 4
    semitones = semitones + 12 * (ascii_int(octave) - 4);

    //Adding the extra accidentals
    if (accidental == '#')
    {
        semitones ++;
    }
    else if (accidental == 'b')
    {
        semitones --;
    }

    return (int) round(440 * pow(2, semitones / 12));

}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    //get_string returns "" (empty string) when just \n written.
    //Here, is_rest, returns true if silence found, or else, false.
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

//ascii_int recieves a char (which we assume it's going to be a number) and casts that char number into its int value
int ascii_int(char a)
{
    return a - 48;
}