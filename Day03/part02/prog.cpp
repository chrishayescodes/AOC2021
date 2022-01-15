#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
using namespace std;

enum Filter
{
  ONES = 1,
  ZEROS = 2,
  NONE = 0
};

int16_t binary_str_to_int16(const char *s)
{
  return (int16_t)strtol(s, NULL, 2);
}

struct node
{
  struct node *next;
  int16_t data;
};

struct node *copy_list(struct node *head)
{
  if (head == NULL)
  {
    return NULL;
  }
  else
  {

    // Allocate the memory for new Node
    // in the heap and set its data
    struct node *newnode = (struct node *)malloc(
        sizeof(struct node));

    newnode->data = head->data;

    // Recursively set the next pointer of
    // the new Node by recurring for the
    // remaining nodes
    newnode->next = copy_list(head->next);

    return newnode;
  }
}

void push(struct node *&head, int data)
{
  struct node *newnode = (node *)malloc(sizeof(struct node));
  newnode->data = data;
  newnode->next = head;
  head = newnode;
}

int length(struct node *head)
{
  int count = 0;
  struct node *current = head;
  while (current != NULL)
  {
    count++;
    current = current->next;
  }
  return (count);
}

int count_masked(struct node *head, int16_t mask)
{
  int count = 0;
  struct node *current = head;
  while (current != NULL)
  {
    if (current->data & mask)
      count++;
    current = current->next;
  }
  return (count);
}

int16_t flip_bits(int16_t value, bool filterones)
{
  int16_t compare = value;
  if (!filterones)
    compare = value ^ 0b1111111111111111;
  return compare;
}

node *filter_and_free(node *head, int16_t mask, bool filterones)
{
  node *output;
  node **temp = &output;
  do
  {
    while (head != NULL && flip_bits(head->data, filterones) & mask)
    {
      node *p = head;
      head = head->next;
      free(p);
    }
    *temp = head;
    while (*temp != NULL && !(flip_bits((*temp)->data, filterones) & mask))
      temp = &(*temp)->next;
    head = *temp;
  } while (head != NULL);
  return output;
}

node *filter_ones(node *head, int16_t mask)
{
  return filter_and_free(head, mask, true);
}

node *filter_zeros(node *head, int16_t mask)
{
  return filter_and_free(head, mask, false);
}

node *filter_by_pred(node *head, int16_t mask, Filter (*filter)(int16_t, int16_t))
{
  if (head->next != NULL)
  {
    int currlength = length(head);
    int onecount = count_masked(head, mask);
    switch (filter(currlength, onecount))
    {
      case NONE:
        return head;
      case ONES:
        return filter_ones(head, mask);
      case ZEROS:
        return filter_zeros(head, mask);
      default:
        return head;
    }
  }
  return head;
}

Filter oxygen_filter(int16_t currlength, int16_t onecount)
{
  int16_t zerocount = currlength - onecount;
  if (onecount == currlength || zerocount == currlength)
    return NONE;
  if (onecount > zerocount)
    return ONES; //ones most common, use ones
  if (onecount == zerocount)
    return ONES; //ones equal, use ones
  if (zerocount > onecount)
    return ZEROS; //zeros most comon, use zeros
  return ZEROS;   //all other use zeros
}

Filter co2_filter(int16_t currlength, int16_t onecount)
{
  int16_t zerocount = currlength - onecount;
  if (zerocount == currlength || onecount == currlength)
    return NONE;
  if (zerocount == onecount)
    return ZEROS; //neither least common, use zero
  if (zerocount < onecount)
    return ZEROS; //zero least common, use zero
  if (onecount < zerocount)
    return ONES; //ones least common, use ones
  return NONE;
}

int create_list_from_file(std::string filename, struct node *&head)
{
  std::ifstream file(filename);

  if (!file.is_open())
  {
    printf("ERROR: unable to open file: %s\n", filename.c_str());
    return 1;
  }

  std::string line;
  while (std::getline(file, line))
  {
    int16_t inputflags = binary_str_to_int16(line.c_str());
    push(head, inputflags);
  }
  file.close();
  return 0;
}

void printnodelist(node *head)
{
  struct node *temp = head;
  while (temp != NULL)
  {
    printf("%d, ", temp->data);
    temp = temp->next;
  }
  printf("\n");
}

int main()
{
  std::string inputfile = "/home/input.txt";
  struct node *head = NULL;
  int success = create_list_from_file(inputfile, head);
  if (success != 0)
    return success;
  int inputlength = length(head);
  int16_t start = 0b0000100000000000;
  int16_t flags[12];
  for (int i = 0; i < 12; i++)
    flags[i] = start >> i;
  struct node *oxygen = copy_list(head);
  struct node *co2 = copy_list(head);

  for (int i = 0; i < 12; i++)
  {
    oxygen = filter_by_pred(oxygen, flags[i], oxygen_filter);
    //printnodelist(oxygen);
    co2 = filter_by_pred(co2, flags[i], co2_filter);
    //printnodelist(co2);
  }
  long long answer = oxygen->data * co2->data;
  printf("OXYGEN: %d, CO2: %d, ANSWER: %lld\n", oxygen->data, co2->data, answer);
  return 0;
}