#include <iostream>
#include <stdexcept>
#include <string>

template< class T >
struct List
{
  T data;
  List< T >* next;
};

void freeList(List< List< int >* >* head)
{
  while (head)
  {
    List< int >* innerHead = head->data;
    while (innerHead)
    {
      List< int >* temp = innerHead;
      innerHead = innerHead->next;
      delete temp;
    }
    List< List< int >* >* temp = head;
    head = head->next;
    delete temp;
  }
}
List< List< int >* >* convert(const int* const* d, size_t m, const size_t* n)
{
  if (m == 0) return nullptr;
  List< List< int >* >* head = new List< List< int >* >();
  List< List< int >* >* tail = head;
  try
  {
    for (size_t i = 0; i < m; ++i)
    {
      if (n[i] == 0)
      {
        continue;
      }
      List< int >* innerHead = new List< int >{ d[i][0], nullptr };
      List< int >* current = innerHead;
      for (size_t j = 1; j < n[i]; ++j)
      {
        List< int >* newList = new List< int >{ d[i][j], nullptr };
        current->next = newList;
        current = newList;
      }
      tail->next = new List< List< int >* >{ innerHead, nullptr };
      tail = tail->next;
    }
  }
  catch (const std::bad_alloc&)
  {
    freeList(head);
    throw;
  }
  return head;
}

template< class T, class C >
size_t count(const List< List< T >* >* head, C condition)
{
  size_t count = 0;
  while (head)
  {
    List< int >* current = head->data;
    while (current)
    {
      if (condition(current->data))
      {
        ++count;
      }
      current = current->next;
    }
    head = head->next;
  }
  return count;
}

void freeArray(int** array, size_t count)
{
  for (size_t i = 0; i < count; ++i)
  {
    delete[] array[i];
  }
  delete[] array;
}

int main()
{
  size_t arrayCount = 0;
  if (!(std::cin >> arrayCount))
  {
    std::cerr << "ERROR: invalid input\n";
    return 1;
  }
  if (arrayCount == 0)
  {
    std::string condition;
    std::cin >> condition;
    if (condition == "odd" || condition == "even")
    {
      std::cout << "0\n";
    }
    else
    {
      std::cout << "0 0\n";
    }
    return 0;
  }
  int** arrays = nullptr;
  size_t* sizes = nullptr;
  try
  {
    arrays = new int*[arrayCount];
    sizes = new size_t[arrayCount];
    for (size_t i = 0; i < arrayCount; ++i)
    {
      size_t elementCount = 0;
      if (!(std::cin >> elementCount))
      {
        throw std::runtime_error("ERROR: fail in reading\n");
      }
      sizes[i] = elementCount;
      arrays[i] = new int[elementCount];
      for (size_t j = 0; j < elementCount; ++j)
      {
        if (!(std::cin >> arrays[i][j]))
        {
          throw std::runtime_error("ERROR: fail in reading\n");
        }
      }
    }
  }
  catch (const std::bad_alloc&)
  {
    delete[] sizes;
    freeArray(arrays, arrayCount);
    std::cerr << "ERROR: out of memory\n";
    return 1;
  }
  catch (const std::runtime_error& e)
  {
    delete[] sizes;
    freeArray(arrays, arrayCount);
    std::cerr << e.what() << "\n";
    return 1;
  }
  List< List< int >* >* head = nullptr;
  try
  {
    head = convert(arrays, arrayCount, sizes);
  }
  catch (const std::bad_alloc&)
  {
    delete[] sizes;
    freeArray(arrays, arrayCount);
    std::cerr << "ERROR: out of memory\n";
    return 1;
  }
  std::string condition;
  std::cin >> condition;
  size_t oddCount = count(head, [](int n) { return n % 2 != 0; });
  size_t evenCount = count(head, [](int n) { return n % 2 == 0; });
  if (condition == "odd")
  {
    std::cout << oddCount << "\n";
  }
  else if (condition == "even")
  {
    std::cout << evenCount << "\n";
  }
  else
  {
    std::cout << oddCount << " " << evenCount << "\n";
  }
  delete[] sizes;
  freeArray(arrays, arrayCount);
  freeList(head);
  return 0;
}
