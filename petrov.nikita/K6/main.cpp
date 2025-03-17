#include <iostream>

template< class T >
struct BiTree 
{
  T data;
  BiTree< T > * left, * right, * parent;
};

template< class T >
BiTree< T > * rotate_right(BiTree< T > * root);

template< class T >
BiTree< T > * rotate_left(BiTree< T > * root);

template< class T, class Cmp >
BiTree< T > * find(BiTree< T > * root, const T & value, Cmp cmp);

template< class T, class Cmp >
BiTree< T > * convert(const T * array, size_t size, Cmp cmp);

int main()
{
  int sequence_length = 0;
  if (!(std::cin >> sequence_length))
  {
    std::cerr << "ERROR: Invalid argument" << "\n";
    return 1;
  }
  else if (std::cin.eof())
  {
    std::cerr << "End of file" << "\n";
    return 2;
  }
  int * elements = new int[sequence_length];
  size_t i = 0;
  while(i != sequence_length && !std::cin && !std::cin.eof())
  {
    std::cin >> elements[i++];
  }
  if (!std::cin)
  {
    delete[] elements;
    std::cerr << "ERROR: Invalid argument" << "\n";
    return 1;
  }
  else if (std::cin.eof())
  {
    delete[] elements;
    std::cerr << "End of file" << "\n";
    return 2;
  }
}