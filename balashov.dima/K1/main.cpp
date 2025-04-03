#include <iostream>

struct List
{
  int value;
  List * next;
  List * before;
};

void deleteList(List *list)
{
  while (list != nullptr)
  {
    List *newList = list->before;
    delete list;
    list = newList;
  }
}

List* convertArrayToList(int* array, int countElementOfArray)
{
  List* head = new List;
  head->value = array[0];
  head->next = nullptr;
  head->before = nullptr;

  List* nowHead = head;

  for (int i = 1; i < countElementOfArray; ++i)
  {
    List* newNewHead = nullptr;
    try
    {
      newNewHead = new List;
    }
    catch (...)
    {
      deleteList(newNewHead);
    }
    newNewHead->value = array[i];
    newNewHead->next = nullptr;
    newNewHead->before = nowHead;
    nowHead->next = newNewHead;
    nowHead = newNewHead;
  }
  return nowHead;
}

int main()
{
  int maxCount = 10;
  int * array = nullptr;
  try
  {
    array = new int[10];
  }
  catch (...)
  {
    return 1;
  }

  int input;
  int realCount = 0;
  for (int i = 0; i < maxCount; i++)
  {
    std::cin >> input;
    if (std::cin.fail() && !std::cin.eof())
    {
      break;
    }
    array[i] = input;
    realCount++;
  }

  List* newCoolList = nullptr;
  try
  {
    newCoolList = convertArrayToList(array, realCount);
  }
  catch (...)
  {
    delete[] array;
  }

  for (int i = 0; i < realCount; i++)
  {
    std::cout << newCoolList->value << " ";
    newCoolList = newCoolList->before;
  }
  std::cout << "\n";
  deleteList(newCoolList);
  delete[] array;
  return 0;
}
