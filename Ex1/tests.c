#include "tests.h"
#include <string.h>


#define EXIT_FAILURE 1
#define EXIT_SUCCESS 0
#define K_1 3
#define K_2 2
#define K_3 -1
#define K_4 -3
#define K_5 29
#define K_6 2
#define K_7 45


// See full documentation in header file
int test_cipher_non_cyclic_lower_case_positive_k ()
{
  char in[] = "abc";
  char out[] = "def";
  cipher (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_cipher_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "xy!z";
  char out[] = "za!b";
  cipher (in, K_2);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_cipher_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "bc!d";
  char out[] = "ab!c";
  cipher (in, K_3);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_cipher_cyclic_lower_case_negative_k ()
{
  char in[] = "abc";
  char out[] = "xyz";
  cipher (in, K_4);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_cipher_cyclic_upper_case_positive_k ()
{
  char in[] = "XYZ";
  char out[] = "ABC";
  cipher (in, K_5);
  return strcmp (in, out) != 0;
}

int test_cipher_non_cyclic_upper_case_special_char_positive_k ()
{
  char in[] = "AB!C";
  char out[] = "CD!E";
  cipher (in, K_6);
  return strcmp (in, out) != 0;
}

int test_cipher_non_cyclic_upper_case_special_char_negative_k ()
{
  char in[] = "CD!E";
  char out[] = "AB!C";
  cipher (in, -K_6);
  return strcmp (in, out) != 0;
}

int test_cipher_cyclic_upper_case_special_char_positive_k ()
{
  char in[] =  "AB!C";
  char out[] = "CD!E";
  cipher (in, K_6);
  return strcmp (in, out) != 0;
}

int test_cipher_non_cyclic_upper_case__negative_k ()
{
  char in[] =  "CD!E";
  char out[] = "AB!C";
  cipher (in, -K_6);
  return strcmp (in, out) != 0;
}

int test_cipher_cyclic_upper_case_special_positive_k ()
{
  char in[] = "HIJ!";
  char out[] = "ABC!";
  cipher (in, K_7);
  return strcmp (in, out) != 0;
}

// See full documentation in header file

int test_decipher_non_cyclic_lower_case_positive_k ()
{
  char in[] = "def";
  char out[] = "abc";
  decipher (in, K_1);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decipher_cyclic_lower_case_special_char_positive_k ()
{
  char in[] = "za!b";
  char out[] = "xy!z";
  decipher (in, K_2);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decipher_non_cyclic_lower_case_special_char_negative_k ()
{
  char in[] = "ab!c";
  char out[] = "bc!d";
  decipher (in, K_3);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decipher_cyclic_lower_case_negative_k ()
{
  char in[] = "xyz";
  char out[] = "abc";
  decipher (in, K_4);
  return strcmp (in, out) != 0;
}

// See full documentation in header file
int test_decipher_cyclic_upper_case_positive_k ()
{
  char in[] = "ABC";
  char out[] = "XYZ";
  decipher (in, K_5);
  return strcmp (in, out) != 0;
}

int test_decipher_non_cyclic_upper_case_special_char_positive_k ()
{
  char in[] = "CD!E";
  char out[] = "AB!C";
  decipher (in, K_6);
  return strcmp (in, out) != 0;
}

int test_decipher_non_cyclic_upper_case_special_char_negative_k ()
{
  char in[] = "AB!C";
  char out[] ="CD!E";
  decipher (in, -K_6);
  return strcmp (in, out) != 0;
}

int test_decipher_non_cyclic_upper_case__negative_k ()
{
  char in[] =  "AB!C";
  char out[] = "CD!E";
  decipher (in, -K_6);
  return strcmp (in, out) != 0;
}

int test_decipher_non_cyclic_upper_case__positive_k ()
{
  char in[] =  "CD!E";
  char out[] = "AB!C";
  decipher (in, K_6);
  return strcmp (in, out) != 0;
}

int test_decipher_cyclic_upper_case_special_positive_k ()//checks cyclic
// with special
{
    char in[] = "ABC!";
    char out[] = "HIJ!";
    decipher (in, K_7);
    return strcmp (in, out) != 0;
}















