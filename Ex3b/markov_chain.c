#include "markov_chain.h"


/**
 * Get random number between 0 and max_number [0, max_number).
 * @param max_number
 * @return Random number
 */
int get_random_number(int max_number)
{
    return rand() % max_number;
}

Node* get_node_from_database(MarkovChain *markov_chain, void *data_ptr)
{
  Node *current = markov_chain->database->first;
  while(current!=NULL)
  {
    //if the Node already in the chain
    if (markov_chain->comp_func((current->data->data), data_ptr) == 0)
    {
      return current;
    }
    current = current->next;

  }
  return current;
}

Node* add_to_database(MarkovChain *markov_chain, void *data_ptr)
{
  Node *start = get_node_from_database (markov_chain,data_ptr);
  if(start!=NULL)
  {
    return start;
  }
  Node *ptr = markov_chain->database->first;
  while(ptr != NULL)
  {
    ptr = ptr->next;
  }
  MarkovNode *new_node = malloc(sizeof (MarkovNode));
  if(new_node==NULL)
  {
    printf("%s",ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  new_node->data = markov_chain->copy_func(data_ptr);
  if(new_node->data==NULL)
  {
    free(new_node);
    printf("%s",ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  if(new_node->data==NULL){return NULL;}
  new_node->frequency_list = malloc (sizeof(MarkovNodeFrequency));
  if(new_node->frequency_list==NULL)
  {
    markov_chain->free_data(new_node->data);
    free(new_node);
    printf("%s",ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  new_node->frequency_list->markov_node = NULL;
  new_node->frequency_list->frequency = 0;
  new_node->frequency_list->size = 0;
  new_node->next = NULL;
  if(add(markov_chain->database,new_node))
  {
    printf ("%s",ALLOCATION_ERROR_MASSAGE);
    return NULL;}
  return markov_chain->database->last;
}

int add_node_to_frequency_list(MarkovNode *first_node
    , MarkovNode *second_node,MarkovChain *markov_chain)
{
  if(first_node==NULL || second_node ==NULL)
  {
    return EXIT_FAILURE;
  }
  if(first_node->frequency_list==NULL)
  {
    first_node->frequency_list = malloc (sizeof(MarkovNodeFrequency));
    if(first_node->frequency_list==NULL)
    {
      printf("%s",ALLOCATION_ERROR_MASSAGE);
      return EXIT_FAILURE;
    }
  }
  int i = 0;
  for(;i < first_node->frequency_list->size;i++)
  {
    if(markov_chain->comp_func(first_node->frequency_list[i]
                  .markov_node->data,second_node->data)==0)
    {
      first_node->frequency_list[i].frequency++;
      return EXIT_SUCCESS;
    }
  }
  MarkovNodeFrequency *temp = realloc(first_node->frequency_list,
                                      (first_node->frequency_list->size+1)
                                      *(sizeof(MarkovNodeFrequency)));
  if(temp == NULL)
  {
    printf("%s",ALLOCATION_ERROR_MASSAGE);
    free(first_node->frequency_list);
    return EXIT_FAILURE;
  }
  first_node->frequency_list = temp;
  first_node->frequency_list[i].markov_node = second_node;
  first_node->frequency_list[i].frequency = 1;
  first_node->frequency_list->size++;
  return EXIT_SUCCESS;
}

void free_markov_chain(MarkovChain ** ptr_chain)
{
  if(ptr_chain==NULL || *ptr_chain==NULL)
  {
    return;
  }
  MarkovChain *chain = *ptr_chain;
  Node* current = chain->database->first;
  while(current!=NULL)
  {
//    printf("%d\n",sizeof ((current->data->data)));
    chain->free_data(current->data->data);
    current->data->data = NULL;
    free(current->data->frequency_list);
    current->data->frequency_list = NULL;
    free(current->data);
    current->data = NULL;
    Node *temp = current;
    current = current->next;
    free(temp);
    temp = NULL;
  }
  free(chain->database);
  chain->database = NULL;
  free(chain);
  chain = NULL;
  ptr_chain = NULL;
}

MarkovNode* get_first_random_node(MarkovChain *markov_chain)
{
  if(markov_chain==NULL || markov_chain->database==NULL
     ||markov_chain->database->first==NULL)
  {
    return NULL;
  }
  while(1)
  {
    Node *current = markov_chain->database->first;
    int first_word_index = get_random_number (markov_chain->database->size);
    for (int count = 0; count < first_word_index; count++)
    {
      current = current->next;
    }
    if (!markov_chain->is_last(current->data->data))
    {
      return current->data;
    }
  }
}

MarkovNode* get_next_random_node(MarkovNode *cur_markov_node)
{
  if (cur_markov_node == NULL || cur_markov_node->frequency_list->size == 0)
  {
    return NULL;
  }
  int all_freq = 0;
  for (int i = 0; i < cur_markov_node->frequency_list->size; i++)
  {
    all_freq += cur_markov_node->frequency_list[i].frequency;
  }
  int word_index = get_random_number (all_freq);
  int current_index = 0;
  for (int appearance_num = 0;
       appearance_num < cur_markov_node->frequency_list->size;
       appearance_num++)
  {
    current_index += cur_markov_node->frequency_list[appearance_num]
        .frequency;
    if (word_index < current_index)
    {
      return cur_markov_node->frequency_list[appearance_num].markov_node;
    }
  }
  return NULL;
}

void generate_random_sequence(MarkovChain *markov_chain, MarkovNode *
first_node, int max_length)
{
  MarkovNode *current = first_node;
  for(int word_num=1;word_num<=max_length;word_num++)
  {
    if(current==NULL)
    {
      return;
    }
    markov_chain->print_func(current->data);
    if(markov_chain->is_last(current->data))
    {
      break;
    }
    current = get_next_random_node (current);
  }

}