#include <iostream>
#include <string>

template< class T >
struct BiTree
{
  T data;
  BiTree< T > * left, * right, * parent;
};

template< class T >
BiTree< T > * rotateRight(BiTree< T > * root)
{
  if (!root || !root->left)
  {
    return nullptr;
  }
  BiTree< T > * rotateNode = root->left;
  root->left = rotateNode->right;
  if (rotateNode->right)
  {
    rotateNode->right->parent = root;
  }
  rotateNode->right = root;
  rotateNode->parent = root->parent;
  root->parent = rotateNode;
  if (rotateNode->parent)
  {
    if (rotateNode->parent->left == root)
    {
      rotateNode->parent->left = rotateNode;
    }
    else
    {
      rotateNode->parent->right = rotateNode;
    }
  }
  return rotateNode;
}

template< class T >
BiTree< T > * rotateLeft(BiTree< T > * root)
{
  if (!root || !root->right)
  {
    return nullptr;
  }
  BiTree< T > * rotateNode = root->right;
  root->right = rotateNode->left;
  if (rotateNode->left)
  {
    rotateNode->left->parent = root;
  }
  rotateNode->left = root;
  rotateNode->parent = root->parent;
  root->parent = rotateNode;
  if (rotateNode->parent)
  {
    if (rotateNode->parent->left == root)
    {
      rotateNode->parent->left = rotateNode;
    }
    else
    {
      rotateNode->parent->right = rotateNode;
    }
  }
  return rotateNode;
}

template< class T, class Cmp >
BiTree< T > * find(BiTree< T > * root, const T & value, Cmp cmp)
{
  while (root)
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

template< class T, class Cmp >
BiTree< T > * convert(const T * data, size_t s, Cmp cmp)
{
  if (s == 0)
  {
    return nullptr;
  }
  BiTree< T > * root = new BiTree< T >{data[0], nullptr, nullptr, nullptr};
  for (size_t i = 1; i < s; ++i)
  {
    BiTree< T > * newNode = nullptr;
    try
    {
      newNode = new BiTree< T >{data[i], nullptr, nullptr, nullptr};
    }
    catch (const std::bad_alloc &)
    {
      deleteTree(root);
      throw;
    }
    BiTree< T > * current = root;
    BiTree< T > * parent = nullptr;
    while (current)
    {
      parent = current;
      if (cmp(data[i], current->data))
      {
        current = current->left;
      }
      else
      {
        current = current->right;
      }
    }
    newNode->parent = parent;
    if (cmp(data[i], parent->data))
    {
      parent->left = newNode;
    }
    else
    {
      parent->right = newNode;
    }
  }
  return root;
}

template< class T >
void deleteTree(BiTree< T > * root)
{
  if (root)
  {
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
  }
}

int main()
{
  size_t count = 0;
  if (!(std::cin >> count))
  {
    std::cerr << "ERROR: wrong input\n";
    return 1;
  }
  int * elements = new int[count];
  for (size_t i = 0; i < count; i++)
  {
    if (!(std::cin >> elements[i]))
    {
      std::cerr << "EEROR: wrong input\n";
      delete[] elements;
      return 1;
    }
  }
  std::less< int > cmp;
  BiTree< int > * root = nullptr;
  try
  {
    root = convert(elements, count, cmp);
  }
  catch (const std::exception & e)
  {
    std::cerr << e.what() << "\n";
    delete[] elements;
    return 1;
  }
  delete[] elements;

  std::string name;
  int num = 0;
  while ((std::cin >> name >> num) && !std::cin.eof())
  {
    BiTree< int > * node = find(root, num, cmp);
    if (!node)
    {
      std::cout << "<INVALID ROTATE>\n";
      deleteTree(root);
      return 0;
    }
    BiTree< int > * rotateNode = nullptr;
    if (name == "left")
    {
      rotateNode = rotateLeft(node);
    }
    else if (name == "right")
    {
      rotateNode = rotateRight(node);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      deleteTree(root);
      return 1;
    }
    if (!rotateNode)
    {
      std::cout << "<INVALID ROTATE>\n";
      continue;
    }
    if (node == root)
    {
      root = rotateNode;
    }
    std::cout << rotateNode->data << "\n";
  }
  deleteTree(root);
}
