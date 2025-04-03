#include <iostream>
#include <functional>

template< class T, class Cmp >
struct BiTree
{
  T data;
  Cmp cmp;
  BiTree< T, Cmp > * left, * right, * parent;
};

template< class T, class Cmp >
BiTree< T, Cmp > * extract(BiTree< T, Cmp > * root, const T & value, BiTree< T, Cmp > ** result)
{
  auto extracted = find(root, value, root->cmp);
  *result = extracted;
  if (!extracted)
  {
    return root;
  }
  if (!extracted)
  {
    return extracted;
  }
  auto subroot = root;
  if (subroot->left)
  {
    subroot = subroot->left;
    while (subroot->right)
    {
      subroot = subroot->right;
    }
  }
  else if (subroot->right)
  {
    subroot = subroot->right;
    while (subroot->left)
    {
      subroot = subroot->left;
    }
  }
  else
  {
    return nullptr;
  }
  if (subroot->parent->right == subroot)
  {
    subroot->parent->right = nullptr;
  }
  else if (subroot->parent->left == subroot)
  {
    subroot->parent->left = nullptr;
  }
  if (subroot->parent != root)
  {
    if (subroot->parent->right == subroot)
    {
      subroot->parent->right = nullptr;
    }
    else if (subroot->parent->left == subroot)
    {
      subroot->parent->left = nullptr;
    }
    auto temp = root;
    root = subroot;
    root->left = temp->left;
    root->right = temp->right;
    temp->left->parent = root;
    temp->right->parent = root;
    root->parent = nullptr;
    subroot = nullptr;
  }
  else
  {
    if (subroot->parent->right == subroot)
    {
      auto temp = root;
      subroot->parent->right = nullptr;
      root = subroot;
      root->left = temp->left;
      temp->left->parent = root;
      root->parent = nullptr;
      subroot = nullptr;
    }
    else
    {
      auto temp = root;
      subroot->parent->left = nullptr;
      root = subroot;
      root->right = temp->right;
      temp->right->parent = root;
      root->parent = nullptr;
      subroot = nullptr;
    }
  }
  return root;
}

template< class T, class Cmp >
std::ostream & outputBiTree(std::ostream & out, BiTree< T, Cmp > * root)
{
  if (!root)
  {
    return out;
  }
  while (root->left)
  {
    root = root->left;
  }
  out << root->data;
  if (root->parent)
  {
    while (root->parent)
    {
      root = root->parent;
      auto subroot = root;
      out << " " << root->data;
      while (root->right)
      {
        root = root->right;
        auto subroot = root;
        while (root->left)
        {
          root = root->left;
        }
        out << " " << root->data;
        while (root != subroot)
        {
          root = root->parent;
          out << " " << root->data;
        }
      }
      while (root != subroot)
      {
        root = root->parent;
      }
    }
  }
  else
  {
    while (root->right)
    {
      root = root->right;
      auto subroot = root;
      while (root->left)
      {
        root = root->left;
      }
      out << " " << root->data;
      while (root != subroot)
      {
        root = root->parent;
        out << " " << root->data;
      }
    }
  }
  return out;
}

template< class T, class Cmp >
BiTree< T , Cmp > * convert(const T * array, size_t size, Cmp cmp)
{
  if (!array)
  {
    return nullptr;
  }
  BiTree< T, Cmp > * root = new BiTree< T, Cmp >{ array[0], cmp, nullptr, nullptr, nullptr };
  try
  {
    for (size_t i = 1; i < size; i++)
    {
      auto temp = root;
      while (temp->left || temp->right)
      {
        if (cmp(array[i], temp->data) && temp->left)
        {
          temp = temp->left;
        }
        else if (!cmp(array[i], temp->data) && temp->right)
        {
          temp = temp->right;
        }
        else
        {
          break;
        }
      }
      if (cmp(array[i], temp->data))
      {
        temp->left = new BiTree< T, Cmp >{ array[i], cmp, nullptr, nullptr, temp };
      }
      else
      {
        temp->right = new BiTree< T, Cmp >{ array[i], cmp, nullptr, nullptr, temp };
      }
    }
  }
  catch(const std::bad_alloc & e)
  {
    clearBiTree(root);
    throw;
  }
  return root;
}

template< class T, class Cmp >
BiTree< T, Cmp > * find(BiTree< T, Cmp > * root, const T & value, Cmp cmp)
{
  if (!root)
  {
    return root;
  }
  while (root->data != value)
  {
    if (cmp(value, root->data) && root->left)
    {
      root = root->left;
    }
    else if (!cmp(value, root->data) && root->right)
    {
      root = root->right;
    }
    else
    {
      root = nullptr;
      break;
    }
  }
  return root;
}

template< class T, class Cmp >
void clearBiTree(BiTree< T, Cmp > * root)
{
  if (root)
  {
    clearBiTree(root->left);
    auto todelete = root;
    clearBiTree(root->right);
    delete todelete;
  }
}

int main()
{
  size_t sequence_length = 0;
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
  int * elements_array = nullptr;
  BiTree< int, std::less< int > > * root = nullptr;
  try
  {
    if (sequence_length)
    {
      elements_array = new int[sequence_length];
    }
    else
    {
      elements_array = nullptr;
    }
    size_t i = 0;
    while(i != sequence_length && std::cin && !std::cin.eof())
    {
      std::cin >> elements_array[i++];
    }
    if (!std::cin)
    {
      throw std::invalid_argument("ERROR: Invalid argument");
    }
    else if (std::cin.eof())
    {
      throw std::logic_error("End of file");
    }
    root = convert(elements_array, sequence_length, std::less< int >());
  }
  catch (const std::invalid_argument & e)
  {
    clearBiTree(root);
    delete[] elements_array;
    std::cerr << e.what() << "\n";
    return 1;
  }
  catch (const std::logic_error & e)
  {
    clearBiTree(root);
    delete[] elements_array;
    std::cerr << e.what() << "\n";
    return 2;
  }
  catch (const std::bad_alloc & e)
  {
    clearBiTree(root);
    delete[] elements_array;
    std::cerr << "ERROR: Out of memory" << "\n";
    return 3;
  }
  delete[] elements_array;
  int number = 0;
  while (!std::cin.eof())
  {
    std::cin >> number;
    if (std::cin.eof())
    {
      break;
    }
    else if (!std::cin)
    {
      outputBiTree(std::cout, root);
      std::cout << "\n";
      clearBiTree(root);
      std::cerr << "ERROR: Invalid argument";
      std::cerr << "\n";
      return 4;
    }
    BiTree< int, std::less< int > > * extracted = nullptr;
    root = extract(root, number, std::addressof(extracted));
    if (extracted)
    {
      delete extracted;
    }
    else
    {
      std::cout << "<INVALID NODE>";
      std::cout << "\n";
    }
  }
  outputBiTree(std::cout, root);
  std::cout << "\n";
  clearBiTree(root);
}
