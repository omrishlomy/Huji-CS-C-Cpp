#include "sort_bus_lines.h"
#include "test_bus_lines.h"
#include <stdlib.h>
#include <stdio.h>


typedef enum MemoryCapacities{
    M_LINE_NAME = 21,
    M_BUS_LINE = 32,
    M_MAX_INPUT = 60

}MemoryCapacities;

#define WRONG_ARG "Usage: the program takes only valid arguments"
#define G_NUMBER_OF_LINES  "Enter number of lines. Then enter\n"
#define ERR_NUMBER_OF_LINES  "Error: Number of lines must be natural number\n"
#define G_LINE_INFO  "Enter line info. Then enter\n"
#define ERR_LINE_NAME "Error: bus name should contains only digits and small chars\n"
#define ERR_DISTANCE "Error: distance should be an integer between 0 to 1000 (includes)\n"
#define ERR_DURATION "Error: duration should be an integer between 10 and 100 (includes)\n"
#define ERR_MEMORY "Error: not enough memory capacity\n"
#define MAX_DISTANCE 1000
#define MAX_DURATION 100
#define MIN_DURATION 10


void print_array(BusLine *start_sorted,BusLine *end_sorted)
{
  while(start_sorted <= end_sorted)
  {
    printf("%s,%d,%d\n",start_sorted->name,start_sorted->distance,
           start_sorted->duration);
    start_sorted ++;
  }
}
void delete_space(char* ptr)
{
  while(*ptr != '\0')
  {
    ptr++;
    if (*ptr == '\n' || *ptr == '\r')
    {
      *(ptr) = '\0';
      break;
    }
  }
}

int check_name_length(char *ptr)
{
  int length = 0;
  while(*ptr != ',')
  {
    length++;
    ptr++;
  }
  if (length > M_LINE_NAME)
  {
    printf("%s\n","Error: Line name is too long");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

int check_name_info(BusLine *line)
{
  char *ptr = line->name;
  while(*ptr!='\0')
  {
    if(!('0'<=*ptr && *ptr<='9') && !('a'<=*ptr && *ptr<='z'))
    {
      printf("%s",ERR_LINE_NAME);
      return EXIT_FAILURE;
    }
    ptr++;
  }
  return EXIT_SUCCESS;
}

int check_distance_duration(BusLine *line)
{
  if(line->distance <0 || line->distance > MAX_DISTANCE)
  {
    printf ("%s", ERR_DISTANCE);
    return EXIT_FAILURE;
  }
  if(line->duration < MIN_DURATION || line->duration > MAX_DURATION)
  {
    printf("%s",ERR_DURATION);
    return  EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
BusLine *get_lines_info(BusLine *line)
{
    printf("%s",G_LINE_INFO);
    char *start = malloc (M_BUS_LINE);
    if(start == NULL){
      printf ("%s",ERR_MEMORY);
      free(start);
      return line;
    }
    if(fgets(start,M_BUS_LINE,stdin))
    {
      delete_space (start);
      if(check_name_length(start))
      {
        line->duration = 0;
        return line;
      }
      if (sscanf(start,"%21[^,], %d ,%d",(line->name),&(line->distance),
                 &(line->duration))==3)
      {
        if(check_distance_duration(line))
        {
          free(start);
          line->duration = 0;
          return line;
        }
        if(check_name_info (line))
        {
          free(start);
          line->duration = 0;
          return line;
        }
        free(start);
        return line;
      }
      else
      {
        printf ("%s","Error: couldn't get variables\n");
        free(start);
        line->duration= 0;
        return line;

      }
    }
    else
    {
      printf ("%s","couldn't get variables\n");
      line->duration = 0;
      return line;
    }
}

int get_number_of_lines() //get the number of lines
{
  printf("%s",G_NUMBER_OF_LINES);
  char* num = calloc (1,M_MAX_INPUT);
  if(fgets(num,M_MAX_INPUT,stdin))
  {
    char *p = NULL;
    int number_of_lines = strtol(num,&p,M_MAX_INPUT);
    delete_space (num);
    if (sscanf(num,"%d",&number_of_lines)==1)
    {
      if(number_of_lines<=0)
      {
        free(num);
        printf("%s",ERR_NUMBER_OF_LINES);
        return EXIT_SUCCESS;
      }
      else
      {
        free(num);
        return number_of_lines;
      }
    }
    else
    {
      free(num);
      num = NULL;
      printf("%s",ERR_NUMBER_OF_LINES);
      return EXIT_SUCCESS;}

  }
  else
  {
    free(num);
    num = NULL;
    printf("%s",ERR_NUMBER_OF_LINES);
    return EXIT_SUCCESS;}
}

void all_tests(const BusLine *start_sorted, const BusLine *end_sorted,const BusLine
*start_original,const BusLine *end_original)
{
  if(is_sorted_by_distance (start_sorted,end_sorted))
  {
    printf("TEST 1 FAILED: not sorted by distance\n");
  }
  else{printf("TEST 1 PASSED: sorted by distance\n");}
  if(is_equal (start_sorted,end_sorted,start_original,end_original))
  {
    printf("TEST 2 FAILED: not equal by distance\n");
  }
  else{printf("TEST 2 PASSED: equal by distance\n");}
  if(is_sorted_by_duration (start_sorted, end_sorted))
  {
    printf("TEST 3 FAILED: not sorted by duration\n");
  }
  else{ printf("TEST 3 PASSED: sorted by duration\n");}
  if(is_equal (start_sorted,end_sorted,start_original,end_original))
  {
    printf("TEST 4 FAILED: not equal by duration\n");
  }
  else{  printf("TEST 4 PASSED: equal by duration\n");}
  if(is_sorted_by_name (start_sorted,end_sorted))
  {
    printf("TEST 5 FAILED: not sorted by name\n");
  }
  else{  printf("TEST 5 PASSED: sorted by name\n");}
  if(is_equal (start_sorted,end_sorted,start_original,end_original))
  {
    printf("TEST 6 FAILED: not equal by name\n");
  }
  else{  printf("TEST 6 PASSED: equal by duration\n");}
}


void call_function(char* type,BusLine *start_sorted,BusLine *end_sorted,BusLine
*start_original,BusLine *end_original)
{
  if(!strcmp(type,"by_name"))
  {
    bubble_sort(start_sorted,end_sorted);
  }
  if(!strcmp(type,"by_duration"))
  {
    quick_sort (start_sorted,end_sorted,DURATION);
  }
  if(!strcmp(type,"by_distance"))
  {
    quick_sort (start_sorted,end_sorted,DISTANCE);
  }
  if(!strcmp(type,"test"))
  {
  all_tests(start_sorted,end_sorted,start_original,end_original);
  }
}


int main (int argc, char *argv[])
{
  char *type = (argv[1]);
  if(((strcmp (type,"by_name")!=0) && (strcmp(type,"by_duration")!=0) &&
  (strcmp(type,"by_distance")!=0) && (strcmp(type,"test")!=0)) || (argc!=2))
  {printf("%s",WRONG_ARG);
    return EXIT_FAILURE;}
  int number_of_lines = 0;
  while(!number_of_lines)
  {number_of_lines = get_number_of_lines ();}
  BusLine *start_sorted = calloc (number_of_lines, M_BUS_LINE);
  if (start_sorted ==NULL)
  {free(start_sorted);
    return EXIT_FAILURE;}
  BusLine *end_sorted = start_sorted + number_of_lines-1;
  for (BusLine *current = start_sorted;current <= end_sorted; current++)
  {current->duration = 0;
    while(!current->duration){current = get_lines_info (current);}}
  BusLine *start_original = calloc (number_of_lines,M_BUS_LINE);
  if(start_original==NULL)
  { free(start_sorted);
    return EXIT_FAILURE;}
  memcpy(start_original,start_sorted,(number_of_lines*sizeof(BusLine)));
  BusLine *end_original = start_original + number_of_lines-1;
  call_function (type,start_sorted,end_sorted,start_original,end_original);
  if(strcmp(type,"test")!=0){print_array (start_sorted,end_sorted);}
  if(is_equal(start_sorted,end_sorted,start_original,end_original))
  {
    free(start_sorted);
    free(start_original);
    return EXIT_FAILURE;
  }
  free(start_sorted);
  free(start_original);
    return EXIT_SUCCESS;}






