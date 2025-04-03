#include <iostream>
#include <cstddef>
#include <stdexcept>

template< class T >
struct BiTree {
  T data;
  BiTree< T > * left, * right, * parent;
};

template< class T >
void clearBiTree(BiTree< T > * root)
{
  if (root != nullptr)
  {
    clearBiTree(root->left);
    clearBiTree(root->right);
    delete root;
  }
}

template< class T, class Cmp >
BiTree< T > * find(BiTree< T > * root, const T & value, Cmp cmp)
{
  BiTree< T > * current = root;
  while (current != nullptr)
  {
    if (cmp(value, current->data))
    {
      current = current->left;
    }
    else if (cmp(current->data, value))
    {
      current = current->right;
    }
    else
    {
      return current;
    }
  }
  return nullptr;
}

template< class T >
BiTree< T > * rotate_right(BiTree< T > * node)
{
  if (node == nullptr || node->left == nullptr)
  {
    throw std::runtime_error("<INVALID ROTATE>");
  }
  BiTree< T > * new_root = node->left;
  node->left = new_root->right;
  if (new_root->right != nullptr)
  {
    new_root->right->parent = node;
  }
  new_root->right = node;
  new_root->parent = node->parent;
  if (node->parent != nullptr)
  {
    if (node->parent->left == node)
    {
      node->parent->left = new_root;
    }
    else
    {
      node->parent->right = new_root;
    }
  }
  node->parent = new_root;
  return new_root;
}

template< class T >
BiTree< T > * rotate_left(BiTree< T > * node) {
  if (node == nullptr || node->right == nullptr)
  {
    throw std::runtime_error("<INVALID ROTATE>") ;
  }
  BiTree< T > * new_root = node->right;
  node->right = new_root->left;
  if (new_root->left != nullptr)
  {
    new_root->left->parent = node;
  }
  new_root->left = node;
  new_root->parent = node->parent;
  if (node->parent != nullptr)
  {
    if (node->parent->left == node)
    {
      node->parent->left = new_root;
    }
    else
    {
      node->parent->right = new_root;
    }
  }
  node->parent = new_root;
  return new_root;
}

template< class T, class Compare = std::less< T > >
BiTree< T > * createBiTree(T * arr, size_t size, Compare cmp = Compare())
{
  BiTree< T > * root = nullptr;
  try
  {
    for (size_t i = 0; i < size; ++i)
    {
      BiTree< T > * new_node = new BiTree< T >{arr[i], nullptr, nullptr, nullptr};
      if (root == nullptr)
      {
        root = new_node;
      }
      else
      {
        BiTree< T > * current = root;
        bool flag = true;
        while (flag)
        {
          if (cmp(arr[i], current->data))
          {
            if (current->left == nullptr)
            {
              current->left = new_node;
              new_node->parent = current;
              flag = false;
            }
            else
            {
              current = current->left;
            }
          }
          else
          {
            if (current->right == nullptr)
            {
              current->right = new_node;
              new_node->parent = current;
              flag = false;
            }
            else
            {
              current = current->right;
            }
          }
        }
      }
    }
  }
  catch (const std::bad_alloc & e)
  {
    clearBiTree(root);
    throw;
  }
  return root;
}

int main()
{
  size_t length = 0;
  if (!(std::cin >> length))
  {
    std::cerr << "Input error\n";
    return 1;
  }
  int * arr = nullptr;
  try
  {
    arr = new int[length];
  }
  catch (const std::bad_alloc & e)
  {
    std::cerr << "Out of memory\n";
    return 1;
  }
  for (size_t i = 0; i < length; ++i)
  {
    if (!(std::cin >> arr[i]))
    {
      delete[] arr;
      std::cerr << "Input error\n";
      return 1;
    }
  }

  BiTree< int > * root = nullptr;
  try
  {
    root = createBiTree(arr, length);
  }
  catch (const std::bad_alloc & e)
  {
    delete[] arr;
    std::cerr << "Out of memory\n";
    return 1;
  }
  delete[] arr;

  std::string command;
  while (std::cin >> command)
  {
    int num = 0;
    if (!(std::cin >> num) || (command != "left" && command != "right"))
    {
      std::cout << "<INVALID COMMAND>\n";
      clearBiTree(root);
      return 1;
    }
    BiTree< int > * node = find(root, num, std::less< int >());
    if (node == nullptr)
    {
      std::cout << "<INVALID ROTATE>\n";
      continue;
    }
    BiTree< int > * new_node = nullptr;
    try
    {
      if (command == "left")
      {
        new_node = rotate_left(node);
      }
      else
      {
        new_node = rotate_right(node);
      }
    }
    catch (const std::runtime_error & e)
    {
      std::cout << e.what() << '\n';
      continue;
    }
    if (node == root)
    {
      root = new_node;
    }
    std::cout << new_node->data << "\n";
  }
  clearBiTree(root);
}
