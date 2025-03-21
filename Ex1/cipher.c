#include "cipher.h"
#include <string.h>
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1
#define ALPHABETIC_NUMBERS 26
#define LINE_LENGTH 1024
#define COMMAND 1
#define K_MOVES 2
#define INPUT_TXT 3
#define OUTPUT_TXT 4



/// IN THIS FILE, IMPLEMENT EVERY FUNCTION THAT'S DECLARED IN cipher.h.


// See full documentation in header file
void cipher (char s[], int k)
{
  k = k % ALPHABETIC_NUMBERS;
  int letter = 0;
  while(s[letter])
  {
    if ('A' <= s[letter] && s[letter] <= 'Z')
    {
      if ((s[letter] + k) <= 'Z')
      {
        if (s[letter] + k >= 'A')
        { s[letter] = s[letter] + k; }
        else
        { s[letter] = s[letter] + k + ALPHABETIC_NUMBERS; }
      }
      else
      {
        s[letter] = ((s[letter] + k) % 'Z') +'A'-1;
      }
    }
    else if ('a' <= s[letter] && s[letter] <= 'z')
    {
      if (s[letter] + k <= 'z')
      {
        if (s[letter] + k >= 'a')
        { s[letter] = s[letter] + k; }
        else
        {
          s[letter] = s[letter] + k + ALPHABETIC_NUMBERS;
        }
      }
      else
      {
        s[letter] = ((s[letter] + k) % 'z') + 'a'-1;
      }
    }
    letter ++;
  }

}

// See full documentation in header file
void decipher (char s[], int k) // same as cipher with opposite K
{
  cipher (s, -k);
}

