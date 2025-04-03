#include <iostream>
#include <string>

template < class T >
struct List {
  T data;
  List< T > * next;
};

void rmArr(int** arr, size_t size)
{
  for (size_t i = 0; i < size; i++)
  {
    delete[] arr[i];
  }
  delete[] arr;
}

void rmList(List< List< int > * > * head)
{
  while (head)
  {
    List< List< int > * > * tempHead = head->next;
    List< int > * subHead = head->data;
    while (subHead)
    {
      List< int > * node = subHead->next;
      delete subHead;
      subHead = node;
    }
    delete head;
    head = tempHead;
  }
}

bool isEven(int n)
{
  return n % 2 == 0;
}

bool isOdd(int n)
{
  return n % 2 != 0;
}

template< class T, class C >
size_t count(const List< List< T > * > * head, C word)
{
  size_t s = 0;
  while (head)
  {
    List< int > * sHead = head->data;
    while (sHead)
    {
      if (word(sHead->data))
      {
        s++;
      }
      sHead = sHead->next;
    }
    head = head->next;
  }
  return s;
}

List< List< int > * > * convert(const int* const* arr, size_t m, const size_t* n)
{
  List< List< int > * > * head = new List< List< int > * >{ nullptr, nullptr };
  List< List< int > * > * tail = head;
  for (size_t i = 0; i < m; i++)
  {
    List< int > * sHead = nullptr;
    List< int > * sTail = nullptr;
    try
    {
      sHead = new List< int >{ arr[i][0], nullptr };
      sTail = sHead;
      for (size_t j = 1; j < n[i]; j++)
      {
        List< int > * newPart = new List< int >{ arr[i][j], nullptr };
        sTail->next = newPart;
        sTail = newPart;
      }
      tail->next = new List< List< int > * >{ sHead, nullptr };
      tail = tail->next;
    }
    catch (const std::bad_alloc &)
    {
      rmList(head);
      throw;
    }
  }
  return head;
}

int main()
{
  size_t m = 0;
  if (!(std::cin >> m))
  {
    std::cerr << "Error: Main -> cin m.\n";
    return 1;
  }

  int** arr = nullptr;
  size_t* numElem = nullptr;
  try
  {
    arr = new int*[m];
    numElem = new size_t[m];
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Error: main -> arr bad_alloc\n";
    delete[] arr;
    return 1;
  }

  for (size_t i = 0; i < m; i++)
  {
    if (!(std::cin >> numElem[i]))
    {
      std::cerr << "Error: Main -> cin size.\n";
      rmArr(arr, i);
      delete[] numElem;
      return 1;
    }

    try
    {
      arr[i] = new int[numElem[i]];
    }
    catch (const std::bad_alloc &)
    {
      std::cerr << "Error: main -> arr bad_alloc\n";
      rmArr(arr, i);
      delete[] numElem;
      return 1;
    }

    for (size_t j = 0; j < numElem[i]; j++)
    {
      if (!(std::cin >> arr[i][j]))
      {
        std::cerr << "Error: main -> cin arr[i][j].\n";
        rmArr(arr, i + 1);
        delete[] numElem;
        return 1;
      }
    }
  }

  List< List< int > * > * head = nullptr;
  try
  {
    head = convert(arr, m, numElem);
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Error: main -> convert bad_alloc\n";
    rmArr(arr, m);
    delete[] numElem;
    return 1;
  }
  rmArr(arr, m);
  delete[] numElem;

  std::string word = "";
  std::cin >> word;
  if (word == "even")
  {
    std::cout << count(head, isEven);
  }
  else if (word == "odd")
  {
    std::cout << count(head, isOdd);
  }
  else
  {
    std::cout << count(head, isOdd) << " " << count(head, isEven);
  }
  std::cout << "\n";
  rmList(head);
}
