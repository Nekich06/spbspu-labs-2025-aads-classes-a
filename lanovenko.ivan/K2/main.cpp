#include <iostream>

struct FwdList
{
  int value;
  FwdList* next;
};

FwdList* insert(FwdList* head, size_t n, size_t k)
{
  FwdList* subhead = head;
  if (n <= 0)
  {
    throw std::invalid_argument("Wrong element!\n");
  }
  for (size_t i = 1; i < n; i++)
  {
    subhead = subhead->next;
  }
  if (subhead == nullptr)
  {
    throw std::invalid_argument("Wrong index!\n");
  }
  for (size_t i = 0; i < k; i++)
  {
    FwdList* node = new FwdList{ subhead->value, nullptr };
    node->next = subhead->next;
    subhead->next = node;
  }
  return subhead;
}


void deleteList(FwdList* head)
{
  while (head != nullptr)
  {
    FwdList* subhead = head;
    head = head->next;
    delete subhead;
  }
}


FwdList* createList()
{
  FwdList* head = nullptr;
  FwdList* subhead = nullptr;
  try
  {
    head = new FwdList{ 0,nullptr };
    subhead = head;
    for (int i = 1; i < 10; i++)
    {
      head->next = new FwdList{ i, nullptr };
      head = head->next;
    }
  }
  catch (const std::bad_alloc& e)
  {
    deleteList(head);
    throw;
  }
  return subhead;
}

int main()
{
  FwdList* buf = nullptr;
  try
  {
    buf = createList();
  }
  catch (const std::bad_alloc& e)
  {
    return 1;
  }
  int element = 0, index = 0;
  while (std::cin >> element && std::cin >> index && !std::cin.eof())
  {
    try
    {
      insert(buf, element, index);
    }
    catch (const std::exception& e)
    {
      deleteList(buf);
      std::cerr << e.what();
      return 1;
    }
  }
  FwdList* temporary = buf;
  std::cout << temporary->value;
  for (temporary = temporary->next; temporary != nullptr; temporary = temporary->next)
  {
    std::cout << " " << temporary->value;
  }
  std::cout << '\n';
  deleteList(buf);
}
