#include "test_bus_lines.h"
#include <stdlib.h>
#include <stdio.h>




int is_sorted_by_distance (const BusLine *start, const BusLine *end)
  {
    for(const BusLine *current = start;current < end-1;current ++)
    {
      if(current->distance > (current->distance)+1)
      {
        return EXIT_FAILURE;
      }
    }
    return EXIT_SUCCESS;
  }

int is_sorted_by_duration (const BusLine *start, const BusLine *end)
{
  for(const BusLine *current = start;current <end-1;current++)
  {
    if(current->duration>(current->duration)+1)
    {
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

int is_sorted_by_name (const BusLine *start, const BusLine *end)
{
  for(const BusLine *current = start;current < end-1;current++)
  {
    if(current -> name> (current ->name)+1)
    {
      return EXIT_FAILURE;
    }
  }
  return EXIT_SUCCESS;
}

int is_equal(const BusLine *start_sorted,const BusLine *end_sorted,
             const BusLine *start_original,const BusLine *end_original)
{
  long long original_array_length = end_original - start_original+1;
  long long sorted_array_length = end_sorted - start_sorted+1;
  if(original_array_length != sorted_array_length)
      {
        return EXIT_FAILURE;
      }
  int same_names = 0;
  for(int i=0;i<original_array_length;i++)
  {
    for(int j=0;j<original_array_length;j++)
    {
      if(strcmp(start_sorted->name,start_original->name)==0)
      {
        same_names++;
        break;
      }
    }
  }
  if (same_names !=sorted_array_length){return EXIT_FAILURE;}
  return EXIT_SUCCESS;
}