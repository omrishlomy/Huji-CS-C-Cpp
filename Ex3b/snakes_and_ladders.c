#include <string.h> // For strlen(), strcmp(), strcpy()
#include "markov_chain.h"


#define MAX(X, Y) (((X) < (Y)) ? (Y) : (X))
#define EMPTY -1
#define BOARD_SIZE 100
#define MAX_GENERATION_LENGTH 60

#define DICE_MAX 6
#define NUM_OF_TRANSITIONS 20

#define NUM_ARGS_ERROR "Usage: invalid number of arguments"
#define MAX_LEN_PATH 60
#define INT_BASE 10
#define EQUAL 0
#define NOT_EQUAL 1


/**
 * represents the transitions by ladders and snakes in the game
 * each tuple (x,y) represents a ladder from x to if x<y or a snake otherwise
 */
const int transitions[][2] = {{13, 4},
                              {85, 17},
                              {95, 67},
                              {97, 58},
                              {66, 89},
                              {87, 31},
                              {57, 83},
                              {91, 25},
                              {28, 50},
                              {35, 11},
                              {8,  30},
                              {41, 62},
                              {81, 43},
                              {69, 32},
                              {20, 39},
                              {33, 70},
                              {79, 99},
                              {23, 76},
                              {15, 47},
                              {61, 14}};

/**
 * struct represents a Cell in the game board
 */
typedef struct Cell {
    int number; // Cell number 1-100
    int ladder_to;  // ladder_to represents the jump of the ladder in
    // case there is one from this square
    int snake_to;  // snake_to represents the jump of the snake in
    // case there is one from this square
    //both ladder_to and snake_to should be -1 if the Cell doesn't have them
} Cell;

/** Error handler **/
int handle_error_snakes(char *error_msg, MarkovChain **database)
{
    printf("%s", error_msg);
    if (database != NULL)
    {
        free_markov_chain(database);
    }
    return EXIT_FAILURE;
}

bool last_cell(void* data_ptr)
{
  Cell *cell = data_ptr;
  if(cell->number==BOARD_SIZE)
  {
    return true;
  }
  return false;
}
void *copy_cell(void* data_ptr)
{
  Cell *tmp = data_ptr;
  Cell *data = malloc(sizeof(Cell));
  if(data == NULL)
  {
    printf("%s",ALLOCATION_ERROR_MASSAGE);
    return NULL;
  }
  memcpy (data,tmp,sizeof(Cell));
//  data->snake_to = tmp->snake_to;
//  data->ladder_to = tmp->ladder_to;
//  data->number = tmp->number;

  return data;
}
void free_cell(void *data_ptr)
{
  Cell *data = data_ptr;
  free(data);
}
int comp_cells(void* data_1,void* data_2)
{
  Cell *cell_1 = data_1;
  Cell *cell_2 = data_2;
  if(cell_1->number < cell_2->number){return NOT_EQUAL;}
  else if(cell_1->number == cell_2->number){return EQUAL;}
  else {return NOT_EQUAL;}
}
void print_cells(void* data_ptr)
{
  Cell *cell = data_ptr;
  if(cell->number==BOARD_SIZE)
  {
    printf("%s%d%s"," [",cell->number,"] ");
    return;
  }
  else
  {
    printf ("%s%d%s", " [", cell->number, "] ");
    if (cell->snake_to != EMPTY)
    {
      printf ("%s", "-snake to->");
    }
    else if (cell->ladder_to != EMPTY)
    {
      printf ("%s", "-ladder to->");
    }
    else
    {
      printf("%s","->");
    }
  }

}
int create_board(Cell *cells[BOARD_SIZE])
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        cells[i] = malloc(sizeof(Cell));
        if (cells[i] == NULL)
        {
            for (int j = 0; j < i; j++) {
                free(cells[j]);
            }
            handle_error_snakes(ALLOCATION_ERROR_MASSAGE,NULL);
            return EXIT_FAILURE;
        }
        *(cells[i]) = (Cell) {i + 1, EMPTY, EMPTY};
    }

    for (int i = 0; i < NUM_OF_TRANSITIONS; i++)
    {
        int from = transitions[i][0];
        int to = transitions[i][1];
        if (from < to)
        {
            cells[from - 1]->ladder_to = to;
        }
        else
        {
            cells[from - 1]->snake_to = to;
        }

    }
    return EXIT_SUCCESS;
}

/**
 * fills database
 * @param markov_chain
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int fill_database_snakes(MarkovChain *markov_chain)
{
    Cell* cells[BOARD_SIZE];
    if(create_board(cells) == EXIT_FAILURE)
    {
        return EXIT_FAILURE;
    }
    MarkovNode *from_node = NULL, *to_node = NULL;
    size_t index_to;
    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        if(add_to_database(markov_chain, cells[i])==NULL)
        { free_markov_chain (&markov_chain);
          return EXIT_FAILURE;}
    }

    for (size_t i = 0; i < BOARD_SIZE; i++)
    {
        from_node = get_node_from_database(markov_chain,
                                           cells[i])->data;

        if (cells[i]->snake_to != EMPTY || cells[i]->ladder_to != EMPTY)
        {
            index_to = MAX(cells[i]->snake_to,cells[i]->ladder_to) - 1;
            to_node = get_node_from_database(markov_chain,
                                             cells[index_to])->data;
            add_node_to_frequency_list(from_node,
                                       to_node, markov_chain);
        }
        else
        {
            for (int j = 1; j <= DICE_MAX; j++)
            {
                index_to = ((Cell*) (from_node->data))->number + j - 1;
                if (index_to >= BOARD_SIZE)
                {
                    break;
                }
                to_node = get_node_from_database(
                    markov_chain,
                    cells[index_to])->data;
                int  res = add_node_to_frequency_list(from_node,
                                                      to_node,
                                                      markov_chain);
                if(res==EXIT_FAILURE){return EXIT_FAILURE;}
            }
        }
    }
    for (size_t i = 0; i < BOARD_SIZE; i++){free(cells[i]);}
    return EXIT_SUCCESS;}


LinkedList *make_linked_list()
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

/**
 * @param argc num of arguments
 * @param argv 1) Seed
 *             2) Number of sentences to generate
 * @return EXIT_SUCCESS or EXIT_FAILURE
 */
int main(int argc,char *argv[])
{
  if(argc !=3)
  {
    printf ("%s\n",NUM_ARGS_ERROR);
    return EXIT_FAILURE;
  }
  MarkovChain *markov_chain = malloc(sizeof(*markov_chain));
  if(markov_chain == NULL)
  {
    printf("%s\n",ALLOCATION_ERROR_MASSAGE);
    return EXIT_FAILURE;
  }
  markov_chain->print_func = print_cells;
  markov_chain->comp_func = comp_cells;
  markov_chain->free_data = free_cell;
  markov_chain->copy_func = copy_cell;
  markov_chain->is_last = last_cell;
  markov_chain->database = make_linked_list();
  if(markov_chain->database==NULL)
  {
    printf ("%s\n",ALLOCATION_ERROR_MASSAGE);
    free(markov_chain);
    return EXIT_FAILURE;
  }
  if(fill_database_snakes(markov_chain)!=0)
  {
    return EXIT_FAILURE;
  }
  char **endptr = NULL;
  int paths_number = strtol((argv[2]),endptr,INT_BASE);
  int seed= strtol((argv[1]),endptr,INT_BASE);
  srand (seed);
  for(int path = 1;path<=paths_number;path++)
  {
    MarkovNode *first_node = markov_chain->database->first->data;
    printf("%s%d%s","Random Walk ",path,":");
    generate_random_sequence(markov_chain,first_node,MAX_LEN_PATH);
    printf("\n");
  }
  free_markov_chain(&markov_chain);
  return  EXIT_SUCCESS;
}

