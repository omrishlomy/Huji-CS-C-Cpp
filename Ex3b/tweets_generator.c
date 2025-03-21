
#include "stdlib.h"
#include "stdio.h"
#include "markov_chain.h"
#include "string.h"
#include "limits.h"
#include "linked_list.h"
#include "stdbool.h"
#define DELIMITERS " \n\t\r"
#define MAX_LEN_TWEET 20
#define LAST_ARG 5
#define INT_BASE 10
#define MAX_LINE_LENGTH 1000
#define DELIMITERS " \n\t\r"
#define FILE_PATH_ERROR "Error: incorrect file path"
#define NUM_ARGS_ERROR "Usage: invalid number of arguments"
#define FILE_PATH_ERROR "Error: incorrect file path"
#define NUM_ARGS_ERROR "Usage: invalid number of arguments"


void print_tweets(void* data)
{
  const char *to_print = data;
  printf("%s%s",to_print," ");

}
int comparing_strings(void* data_1,void* data_2)
{
  const char *str_1 = data_1;
  const char *str_2 = data_2;
  return strcmp (str_1,str_2);
}
void free_string(void* data_ptr)
{
  char *data = data_ptr;
  free(data);
}
void *copy_string(void* data_ptr)
{
  char *tmp = (char *)data_ptr;
  size_t length = strlen(tmp) +1;
  char *data = malloc(length);
  if(data ==NULL)
  {
    printf("%s",ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  strcpy (data,tmp);
  return data;
}
bool last_word(void* data_ptr)
{
    if(data_ptr==NULL){return false;}
    char *word = data_ptr;
    while(*word!= '\0')
    {
      word++;
    }
    if(*(--word)=='.')
    {
      return true;
    }
    return false;
  }

int fill_database(FILE *fp,int words_to_read,MarkovChain *markov_chain)
{
  int words_read = 0;
  Node *prev =NULL;
  while(words_read < words_to_read)
  {
    char line[MAX_LINE_LENGTH]={0};
    if(fgets(line, MAX_LINE_LENGTH, fp)==NULL)
    {
      if (feof(fp))
      {
        fclose (fp);
        return EXIT_SUCCESS;
      }
      printf ("%s", FILE_PATH_ERROR);
      return EXIT_FAILURE;
    }
    char *pch = strtok (line, DELIMITERS);

    while (pch != NULL && words_read<words_to_read)
    {
      Node *current = add_to_database (markov_chain, pch);
      if(current ==NULL)
      {
        free_markov_chain(&markov_chain);
        fclose (fp);
        return EXIT_FAILURE;
      }
      if (prev != NULL)
      {
        add_node_to_frequency_list (prev->data, current->data,markov_chain);

      }
      prev = current;
      pch = strtok (NULL, DELIMITERS);
      words_read++;
    }
  }
  fclose (fp);
  return EXIT_SUCCESS;
}

int words_number(int argc,char *argv[])
{
  if(argc ==4)
  {
    int words_to_read = INT_MAX;
    return words_to_read;
  }
  else if(argc==LAST_ARG)
  {
    char **endptr =NULL;
    int words_to_read = strtol((argv[4]),endptr,INT_BASE);
    return words_to_read;
  }
  else
  {
    return EXIT_FAILURE;
  }
}
LinkedList *generate_list()
{
  LinkedList *list = malloc (sizeof(LinkedList));
  if(list==NULL)
  {
    printf ("%s\n",ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  list->first =NULL;
  list->last = NULL;
  list->size = 0;
  return list;
}
int handle_error(char* error_msg)
{
  printf ("%s\n",error_msg);
  return EXIT_FAILURE;
}

int main(int argc,char *argv[])
{
  if((argc !=4) & (argc!=LAST_ARG)){ return handle_error (NUM_ARGS_ERROR);}
  MarkovChain *markov_chain = malloc(sizeof(*markov_chain));
  if(markov_chain == NULL){return handle_error (ALLOCATION_ERROR_MASSAGE);}
  markov_chain->print_func = print_tweets;
  markov_chain->comp_func = comparing_strings;
  markov_chain->free_data = free_string;
  markov_chain->copy_func = copy_string;
  markov_chain->is_last = last_word;
  markov_chain->database = generate_list ();
  if(markov_chain->database==NULL)
  {free(markov_chain);
    return handle_error (ALLOCATION_ERROR_MASSAGE);}
  int words_to_read = words_number(argc,argv);
  if(words_to_read==EXIT_FAILURE)
  {free_markov_chain(&markov_chain);
    return EXIT_FAILURE;}
  FILE *fp = fopen (argv[3],"r");
  if(fp==NULL)
  {free_markov_chain(&markov_chain);
    return handle_error (FILE_PATH_ERROR);}
  if(fill_database(fp,words_to_read,markov_chain)!=0){return EXIT_FAILURE;}
  char **endptr = NULL;
  int tweets_number = strtol((argv[2]),endptr,INT_BASE);
  int seed= strtol((argv[1]),endptr,INT_BASE);
  srand (seed);
  for(int tweet = 1;tweet<=tweets_number;tweet++)
  {
    MarkovNode *first_node = get_first_random_node (markov_chain);
    printf("%s%d%s","Tweet ",tweet,": ");
    generate_random_sequence(markov_chain,first_node,MAX_LEN_TWEET);
    printf("\n");
  }
  free_markov_chain(&markov_chain);
  return  EXIT_SUCCESS;}


