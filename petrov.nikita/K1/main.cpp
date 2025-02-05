#include <iostream>

struct BiList
{
  int value;
  BiList * prev, * next;
};

BiList * transformArrayToList(const int * start, size_t size);
void clearListFromTail(BiList * tail, size_t size_of_list);

int main()
{
  constexpr size_t max_capacity = 10;
  int * ptr_massive = nullptr;
  try
  {
    ptr_massive = new int[max_capacity];
  }
  catch(const std::bad_alloc & e)
  {
    std::cerr << "ERROR: Out of memory\n";
    return 1;
  }
  size_t size = 0;
  while (size != 10 && !std::cin.eof() && std::cin)
  {
    std::cin >> ptr_massive[size++];
    if (!std::cin)
    {
      size--;
    }
  }
  BiList * tail = nullptr;
  if (size)
  {
    int * start_of_massive = ptr_massive;
    BiList * end_of_list = nullptr;
    try
    {
      end_of_list = transformArrayToList(start_of_massive, size);
      tail = end_of_list;
    }
    catch(const std::bad_alloc & e)
    {
      delete[] ptr_massive;
      std::cerr << "ERROR: Out of memory\n";
      return 1;
    }
    std::cout << end_of_list->value;
    size_t i = 1;
    while (i != size)
    {
      end_of_list = end_of_list->prev;
      std::cout << " " << end_of_list->value;
      i++;
    }
  }
  std::cout << "\n";
  clearListFromTail(tail, size);
  delete[] ptr_massive;
}

BiList * transformArrayToList(const int * start, size_t size)
{
  BiList * head = nullptr;
  size_t created = 0;
  head = new BiList{ start[0], nullptr, nullptr };
  created++;
  try
  {
    while (created != size)
    {
      head->next = new BiList{ start[created++], head, nullptr };
      head = head->next;
    }
  }
  catch(const std::bad_alloc & e)
  {
    clearListFromTail(head, created);
    throw;
  }
  return head;
}

void clearListFromTail(BiList * tail, size_t size_of_list)
{
  size_t i = 1;
  while (i != size_of_list)
  {
    tail = tail->prev;
    delete tail->next;
    i++;
  }
  delete tail;
}
