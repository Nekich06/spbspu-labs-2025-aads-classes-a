#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
template< class T >
struct BiTree
{
  T data;
  BiTree< T >* left;
  BiTree< T >* right;
  BiTree< T >* parent;
  BiTree(T value):
    data(value),
    left(nullptr),
    right(nullptr),
    parent(nullptr)
  {}
  ~BiTree()
  {
    delete left;
    delete right;
  }
};
template< class T >
BiTree< T >* rotate_right(BiTree< T >* root)
{
  if (!root || !root->left)
  {
    return nullptr;
  }
  BiTree< T >* newRoot = root->left;
  root->left = newRoot->right;
  if (newRoot->right)
  {
    newRoot->right->parent = root;
  }
  newRoot->parent = root->parent;
  newRoot->right = root;
  root->parent = newRoot;
  return newRoot;
}
template< class T >
BiTree< T >* rotate_left(BiTree< T >* root)
{
  if (!root || !root->right)
  {
    return nullptr;
  }
  BiTree< T >* newRoot = root->right;
  root->right = newRoot->left;
  if (newRoot->left)
  {
    newRoot->left->parent = root;
  }
  newRoot->parent = root->parent;
  newRoot->left = root;
  root->parent = newRoot;
  return newRoot;
}
template< class T, class Cmp >
BiTree< T >* find(BiTree< T >* root, const T& value, Cmp cmp)
{
  while (root != nullptr)
  {
    if (cmp(value, root->data))
    {
      root = root->left;
    }
    else if (cmp(root->data, value))
    {
      root = root->right;
    }
    else
    {
      return root;
    }
  }
  return nullptr;
}
void insert(BiTree< int >*& root, int value)
{
  if (!root)
  {
    try
    {
      root = new BiTree<int>(value);
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "ERROR: out of memory\n";
      throw;
    }
    return;
  }
  if (value < root->data)
  {
    insert(root->left, value);
    if (root->left)
    {
      root->left->parent = root;
    }
  }
  else
  {
    insert(root->right, value);
    if (root->right)
    {
      root->right->parent = root;
    }
  }
}
int main()
{
  int length = 0;
  std::cin >> length;
  if (std::cin.fail() || length < 0)
  {
    std::cerr << "ERROR: invalid input\n";
    return 1;
  }
  BiTree< int >* root = nullptr;
  for (int i = 0; i < length; ++i)
  {
    int value = 0;
    std::cin >> value;
    if (std::cin.fail())
    {
      std::cerr << "ERROR: invalid input\n";
      delete root;
      return 1;
    }
    try
    {
      insert(root, value);
    }
    catch (const std::bad_alloc&)
    {
      std::cerr << "ERROR: out of memory\n";
      delete root;
      return 1;
    }
  }
  std::string command;
  while (std::getline(std::cin, command))
  {
    if (command.empty())
    {
      continue;
    }
    std::istringstream is(command);
    std::string rotation;
    int value = 0;
    if (!(is >> rotation >> value))
    {
      std::cout << "<INVALID COMMAND>\n";
      delete root;
      return 1;
    }
    BiTree< int >* node = find(root, value, std::less<int>());
    if (!node)
    {
      std::cout << "<INVALID ROTATE>\n";
      continue;
    }
    if (rotation == "left")
    {
      BiTree< int >* newRoot = rotate_left(node);
      if (!newRoot)
      {
        std::cout << "<INVALID ROTATE>\n";
      }
      else
      {
        std::cout << newRoot->data << "\n";
        if (newRoot->parent == nullptr)
        {
          root = newRoot;
        }
      }
    }
    else if (rotation == "right")
    {
      BiTree< int >* newRoot = rotate_right(node);
      if (!newRoot)
      {
        std::cout << "<INVALID ROTATE>\n";
      }
      else
      {
        std::cout << newRoot->data << "\n";
        if (newRoot->parent == nullptr)
        {
          root = newRoot;
        }
      }
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      delete root;
      return 1;
    }
  }
  delete root;
  return 0;
}
