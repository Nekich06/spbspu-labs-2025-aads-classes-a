#include <iostream>

template< class T, class Cmp >
struct TriTree 
{
  std::pair< T, T > data;
  TriTree< T, Cmp > * left, * middle, * right, * parent;
};

template< class T, class Cmp >
struct TriTreeIterator 
{
  /* ??? */
  using this_t = TriTreeIterator< T, Cmp >;
  bool hasNext() const;
  bool hasPrev() const;

  this_t prev() const;
  this_t next() const;

  std::pair< T, T > & data();
};

template< class T, class Cmp >
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp > * root);

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > * root);

template< class T, class Cmp >
void clearTriTree(TriTree< T, Cmp > * root)
{
  if (root)
  {
    clearTriTree(root->left);
    auto todelete = root;
    clearTriTree(root->middle);
    clearTriTree(root->right);
    delete todelete;
  }
}

template< class T, class Cmp >
TriTree< T, Cmp > * convert(std::pair< T, T > * array, size_t size, Cmp cmp)
{
  if (!array)
  {
    return nullptr;
  }
  TriTree< T, Cmp > * root = new TriTree< T, Cmp >{ array[0], nullptr, nullptr, nullptr, nullptr };
  try
  {
    for (size_t i = 1; i < size; i++)
    {
      auto temp = root;
      while (temp->left || temp->middle || temp->right)
      {
        if (cmp(array[i].second, temp->data.first) && temp->left)
        {
          temp = temp->left;
        }
        else if (cmp(temp->data.first, array[i].second) && temp->middle)
        {
          temp = temp->middle;
        }
        else if (!cmp(array[i].second, temp->data.second) && temp->right)
        {
          temp = temp->right;
        }
        else
        {
          break;
        }
      }
      if (cmp(array[i].second, temp->data.first))
      {
        temp->left = new TriTree< T, Cmp >{ array[i], nullptr, nullptr, nullptr, temp };
      }
      else if (cmp(temp->data.first, array[i].second))
      {
        temp->middle = new TriTree< T, Cmp >{ array[i], nullptr, nullptr, nullptr, temp };
      }
      else
      {
        temp->right = new TriTree< T, Cmp >{ array[i], nullptr, nullptr, nullptr, temp };
      }
    }
  }
  catch(const std::bad_alloc & e)
  {
    clearTriTree(root);
    throw;
  }
  return root;
}

std::ostream & outputTriTreeOfPairs(std::ostream & out, const TriTree< int, std::less< int > > * root)
{
  if (root)
  {
    outputTriTreeOfPairs(out, root->left);
    out << root->data.first << " " << root->data.second << " ";
    outputTriTreeOfPairs(out, root->middle);
    outputTriTreeOfPairs(out, root->right);
  }
  return out;
}

int main()
{
  size_t pairs_number = 0;
  if (!(std::cin >> pairs_number))
  {
    std::cerr << "ERROR: Invalid argument";
    std::cerr << "\n";
    return 1;
  }
  std::pair< int, int > * pairs_array = new std::pair< int, int >[pairs_number];
  int first_number = 0;
  int second_number = 0;
  size_t i = 0;
  while (i < pairs_number && std::cin)
  {
    std::cin >> first_number;
    std::cin >> second_number;
    if (std::cin && second_number < first_number)
    {
      pairs_array[i++] = { second_number, first_number };
    }
    else
    {
      pairs_array[i++] = { first_number, second_number };
    }
  }
  TriTree< int, std::less< int > > * root = convert(pairs_array, pairs_number, std::less< int >());
  outputTriTreeOfPairs(std::cout, root);
  delete pairs_array;
  std::cout << "\n";
}