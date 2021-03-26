// Helper functions for music

#include <cs50.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    int multi = 8;
    if (fraction[2] == '2') // this is to get the rest phase
    {
        multi = 4;
    }
    else if (fraction[2] == '4')
    {
        multi = 2;
    }
    else if (fraction[2] == '8') // convert it to the eights
    {
        multi = 1;
    }
    int integral = multi * ((int)fraction[0] - 48);
    return integral;
}

// Calculates frequency (in Hz) of a note

int frequency(string note)
{
    char check = '\0';
    bool flat = false; // this is if there is a flat b notes
    bool hash = false; // this is if there is a # in the notes (sharp)
    char piano_keys[88][4] = {"A0", "A#0", "B0", "C1", "C#1", "D1", "D#1", "E1", "F1", "F#1", "G1", "G#1",
                              "A1", "A#1", "B1", "C2", "C#2", "D2", "D#2", "E2", "F2", "F#2", "G2", "G#2",
                              "A2", "A#2", "B2", "C3", "C#3", "D3", "D#3", "E3", "F3", "F#3", "G3", "G#3",
                              "A3", "A#3", "B3", "C4", "C#4", "D4", "D#4", "E4", "F4", "F#4", "G4", "G#4",
                              "A4", "A#4", "B4", "C5", "C#5", "D5", "D#5", "E5", "F5", "F#5", "G5", "G#5",
                              "A5", "A#5", "B5", "C6", "C#6", "D6", "D#6", "E6", "F6", "F#6", "G6", "G#6",
                              "A6", "A#6", "B6", "C7", "C#7", "D7", "D#7", "E7", "F7", "F#7", "G7", "G#7",
                              "A7", "A#7", "B7", "C8"
                             };
    int x = 0;
    note[0] = toupper(note[0]);
    if (note[1] == 'b')
    {
        note[1] = '#';
        x = (int) note[0];
        if (x == 65) // this is to check if the first digit is 'a'
        {
            note[0] = (char) 71; // this changes it to 'g' as in a piano g comes before a.
        }
        else
        {
            note[0] = (char) x - 1;
        }
        flat = true;
    }
    if (note[1] == '#')
    {
        hash = true;
        if (((int) note[2] - 48) <= 4) // to check if we have to search higher or lower
        {
            check = 'a';
        }
        else
        {
            check = 'b';
        }
    }
    else if (((int) note[1] - 48) <= 4)
    {
        check = 'l';
    }
    else if (((int) note[1] - 48) > 4)
    {
        check = 'g';
    }
    int counter = 0;
    switch (check)
    {
        case 'l':
        case 'a':
            for (int i = 47; i >= 0; i--)
            {
                counter++;
                if (strcmp(piano_keys[i], note) == 0) // this is to check if the notes match that of the piano
                {
                    i = -1;
                    counter = counter * -1;
                }
            }
            break;

        case 'g':
        case 'b':
            for (int i = 49; i <= 87; i++)
            {
                counter++;
                if (strcmp(piano_keys[i], note) == 0)
                {
                    i = 88;
                }
            }
            break;
    }

    int n = counter; // counter is the number of subkeys
    double power = n / 12.0;
    double acpower = pow(2, power);
    double freq = acpower * 440;
    int f = round(freq);
    if (strcmp(note, "B4") == 0) // these are special cases
    {
        f = 494;
    }
    if (strcmp(note, "A#4") == 0)
    {
        f = 466;
    }
    if (strcmp(note, "A4") == 0)
    {
        f = 440;
    }
    return f;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (strcmp(s, "") == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
