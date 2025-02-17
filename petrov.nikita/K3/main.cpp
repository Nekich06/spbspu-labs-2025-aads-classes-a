#include <iostream>

template< class T >
struct List 
{
  T data;
  List< T > * next;
};

int * allocateMemoryForMassive(int * ptr_massives, size_t number_of_elements);
void clearAllMassives(int ** ptr_massives, size_t number_of_massives);
List< List< int > * > * convert(const int * const * d, size_t m, const size_t * n);

int main()
{
  int ** ptr_massives = nullptr;
  size_t number_of_massives = 0;
  size_t number_of_elements = 0;
  std::cin >> number_of_massives;
  ptr_massives = new int * [number_of_massives];
  for (size_t i = 0; i < number_of_massives; i++)
  {
    std::cin >> number_of_elements;
    allocateMemoryForMassive(ptr_massives[i], number_of_elements);
  }
}

int * allocateMemoryForMassive(int * ptr_massive, size_t number_of_elements)
{
  ptr_massive = new int [number_of_elements];
  for (size_t i = 0; i < number_of_elements; i++)
  {
    std::cin >> ptr_massive[i];
  }
}

void clearAllMassives(int ** ptr_massives, size_t number_of_massives)
{
  
}