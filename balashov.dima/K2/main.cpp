#include <iostream>

struct FwdList {
  int value;
  FwdList* next;
};

void deleteList(FwdList* head)
{
  FwdList* temp = head;
  while (temp)
  {
    FwdList* nextHead = temp->next;
    delete temp;
    temp = nextHead;
  }
}

FwdList* duplicate(FwdList * head, size_t numberElement, size_t numberDuplicates)
{
  if (numberElement < 1)
  {
    throw;
  }
  FwdList* nowHead = head;
  for (size_t i = 1; i < numberElement && nowHead != nullptr; i++)
  {
    nowHead = nowHead->next;
  }
  if (nowHead == nullptr)
  {
    throw;
  }
  for (size_t i = 0; i < numberDuplicates; i++)
  {
    FwdList* endHead = new FwdList{ nowHead->value, nullptr };
    endHead->next = nowHead->next;
    nowHead->next = endHead;
  }
  return nowHead;
}

int main()
{
  FwdList* head = nullptr;
  FwdList* lastHead= nullptr;
  int maxCount = 10;

  for (int i = 0; i < 10; i++)
  {
    FwdList* newHead = nullptr;
    try
    {
      newHead = new FwdList{ i, nullptr };
    }
    catch (...)
    {
      deleteList(head);
      std::cerr << "Not enough memory\n";
      return 1;
    }
    lastHead->next = newHead;
    lastHead = newHead;
  }

  int input = 0;
  int count = 0;
  int index = 0;
  while (std::cin >> index >> count)
  {
    try
    {
      duplicate(head, index, count);
    }
    catch (...)
    {
      deleteList(head);
      std::cerr << "Not enough memory\n";
      return 1;
    }
    maxCount += count;
  }

  FwdList* headNow = head;
  std::cout << headNow->value;
  headNow = headNow->next;
  while (headNow != nullptr)
  {
    headNow = headNow->next;
    std::cout << " " << headNow->value;
  }
  std::cout << "\n";
  deleteList(head);
}
