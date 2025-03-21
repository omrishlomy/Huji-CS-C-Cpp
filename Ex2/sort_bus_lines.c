#include "sort_bus_lines.h"



int convert_sortype(BusLine *ptr,SortType sort_type)
{
  if(!sort_type)
  {
   int p = ptr->distance;
    return p;
  }
  else
  {
    int p = ptr->duration;
    return p;
  }
}

void bubble(BusLine *start,BusLine *end)
{
  for(BusLine *current=start;current<end;current++)
  {
    if(strcmp(current->name,(current+1)->name)>0)
    {
      BusLine temp= *current;
      *current = *(current +1);
      *(current+1) = temp;
    }
  }
}
void bubble_sort (BusLine *start, BusLine *end)
{
  for(BusLine *i = start;i<end;i++)
  {
    bubble(start,end-(i-start));
  }
}

void swap(BusLine *low,BusLine *high)
{
  BusLine temp = *low;
  *low = *high;
  *high = temp;
}

BusLine *partition (BusLine *start, BusLine *end, SortType sort_type)
{
  BusLine *pivot = end;
  BusLine *low = start;
  BusLine *high = end;
  while(low<high)
  {
    while((convert_sortype (low,sort_type) <= convert_sortype (pivot,
                                                               sort_type)) &&
    (low <high ))
    {
      low++;
    }
    while(convert_sortype (high,sort_type) > convert_sortype
    (pivot,sort_type) && high
    > low)
    {
      high--;
    }
    if(low<high)
    {
      swap(low,high);
    }

  }
  swap(pivot,low);
  return low;
}

void quick_sort(BusLine *start, BusLine *end, SortType sort_type)
{
  if(start < end)
  {
    BusLine *pivot = partition (start,end,sort_type);
    quick_sort (start,pivot-1,sort_type);
    quick_sort (pivot+1,end,sort_type);
  }
}