#include <iostream>

struct FwdList
{
  int value;
  FwdList* next;
};

void deleteList(FwdList* head)
{
  while (head)
  {
    FwdList* subhead = head;
    head = head->next;
    delete subhead;
  }
}

FwdList* duplicate(FwdList* head, size_t index, size_t count)
{
  if (!head)
  {
    throw std::invalid_argument("Head is empty");
  }
  if (index < 1)
  {
    throw std::out_of_range("Index out of range!");
  }

  FwdList* temp = head;
  for (size_t i = 1; i < index && temp != nullptr; i++)
  {
    temp = temp->next;
  }

  if (temp == nullptr)
  {
    throw std::out_of_range("");
  }

  for (size_t i = 0; i < count; i++)
  {
    FwdList* node = new FwdList{ temp->value, nullptr };
    node->next = temp->next;
    temp->next = node;
  }
  return temp;
}

int main()
{
  FwdList* head = nullptr;
  FwdList* current = nullptr;

  try
  {
    int count = 0;
    head = new FwdList{ count++, nullptr };
    current = head;
    while (count != 10)
    {
      current->next = new FwdList{ count++, nullptr };
      current = current->next;
    }
  }
  catch (const std::bad_alloc& e)
  {
    deleteList(head);
    std::cerr << "Memory allocation error!\n";
    return 2;
  }

  size_t a = 0, b = 0;
  while (std::cin >> a >> b && !std::cin.eof())
  {
    try
    {
      duplicate(head, a, b);
    }
    catch (const std::exception& e)
    {
      deleteList(head);
      std::cerr << e.what() << '\n';
      return 2;
    }
  }

  FwdList * temp = head;
  std::cout << temp->value;
  for (temp = temp->next; temp != nullptr; temp = temp->next)
  {
    std::cout << " " << temp->value;
  }
  std::cout << "\n";
  deleteList(head);
  return 0;
}
