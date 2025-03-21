#include "cipher.h"
#include <stdio.h>
#include "tests.h"
#include <stdlib.h>
#include <string.h>
#define ARGUMENTS_ERR "The program receives 1 or 4 arguments only.\n"
#define TEST_ERR "Usage: cipher test\n"
#define COMMAND_ERR "The given command is invalid.\n"
#define SHIFT_ERR "The given shift value is invalid.\n"
#define FILE_ERR "The given file is invalid.\n"
#define OPTION_ONE_ARGUMENTS 5
#define OPTION_TWO_ARGUMENTS 2
#define COMMAND 1
#define K_MOVES 2
#define INPUT_TXT 3
#define OUTPUT_TXT 4
#define LINE_LENGTH 1024 //providing line max
#define BASE_CONVERSION 10
#define EMPTY_STRING ""


void call_function(char* function,char string[LINE_LENGTH],int k);






// declaring more tests
int test_cipher_non_cyclic_upper_case_special_char_positive_k(); //
int test_cipher_non_cyclic_upper_case_special_char_negative_k();
int test_cipher_cyclic_upper_case_special_char_positive_k();
int test_cipher_non_cyclic_upper_case__negative_k();
int test_cipher_cyclic_upper_case_special_positive_k();
int test_decipher_cyclic_upper_case_positive_k();
int test_decipher_non_cyclic_upper_case_special_char_positive_k();
int test_decipher_non_cyclic_upper_case_special_char_negative_k();
int test_decipher_non_cyclic_upper_case__negative_k();
int test_decipher_non_cyclic_upper_case__positive_k();
int test_decipher_cyclic_upper_case_special_positive_k();

//reads the file to a string



// check input by order
int check_input(int argc,char *argv[])
{
  if (argc != OPTION_TWO_ARGUMENTS)
  {
    if (argc != OPTION_ONE_ARGUMENTS)
    {
      fprintf (stderr, ARGUMENTS_ERR);
      return EXIT_FAILURE;
    }
    else
    {
      if (strcmp (argv[COMMAND], "cipher") != 0 && strcmp (argv[COMMAND],
                                                           "decipher")
                                                   != 0)
      {
        fprintf (stderr, COMMAND_ERR);
        return EXIT_FAILURE;
      }
      char *endptr;
      strtol(argv[K_MOVES], &endptr,BASE_CONVERSION);
      if(*endptr!='\0' || argv[K_MOVES]==endptr)
      {
        fprintf (stderr, SHIFT_ERR);
        return EXIT_FAILURE;
      }
      FILE *input_file = fopen (argv[INPUT_TXT],"r");
      FILE *output_file = fopen (argv[OUTPUT_TXT],"w");
      if (input_file==NULL || output_file==NULL){
        fprintf (stderr, FILE_ERR);

        return EXIT_FAILURE;
      }
    }
  }
  else if(strcmp(argv[COMMAND], "test") != 0)
  {fprintf(stderr,TEST_ERR);
      return EXIT_FAILURE;}
  return EXIT_SUCCESS;
}
void read_file(char* argv[],char* string)
{

  FILE *input_file = fopen(argv[INPUT_TXT], "r");
  FILE *output_file = fopen(argv[OUTPUT_TXT],"w");
  char* ptr;
  while(fgets(string,LINE_LENGTH,input_file)!=NULL)
  {
//    int k  =
    call_function (argv[COMMAND], string, strtol(argv[K_MOVES],&ptr,
                                            BASE_CONVERSION));

    fputs(string,output_file);
  }
  fclose(input_file);
}
//write the cryptated text to new file
void write_to_file(const char *file_name, char* content){
  FILE *file = fopen(file_name,"w");
  fprintf(file,"%s", content);
  fclose(file);}

//call the right function according to the COMMAND
void call_function(char* function,char string[LINE_LENGTH],int k)
{
  if (strcmp(function,"cipher")==0){
    cipher(string,k);}
  else if(strcmp(function,"decipher")==0){
    decipher(string,k);}
}
//
int all_tests()
{
  if(test_cipher_cyclic_lower_case_special_char_positive_k()){return
        EXIT_FAILURE;}
  if(test_decipher_cyclic_lower_case_special_char_positive_k()){return
        EXIT_FAILURE;}
  if(test_cipher_non_cyclic_lower_case_special_char_negative_k()){return
        EXIT_FAILURE;}
  if(test_decipher_non_cyclic_lower_case_special_char_negative_k()){return
        EXIT_FAILURE;}
  if(test_cipher_cyclic_lower_case_negative_k()){return EXIT_FAILURE;}
  if(test_decipher_cyclic_lower_case_negative_k()){return EXIT_FAILURE;}
  if(test_cipher_cyclic_upper_case_positive_k()){return EXIT_FAILURE;}
  if(test_decipher_cyclic_upper_case_positive_k()){return EXIT_FAILURE;}

  return EXIT_SUCCESS;
}


int main (int argc, char *argv[])
{
    if(check_input(argc,argv)==EXIT_FAILURE){return EXIT_FAILURE;}
    if(strcmp(argv[COMMAND],"test")==0){
      if(all_tests()){return EXIT_FAILURE;}
      else{return EXIT_SUCCESS;}
    }
    char string[LINE_LENGTH];
    char *s = string;
    read_file(argv,s);



    return EXIT_SUCCESS;
}
