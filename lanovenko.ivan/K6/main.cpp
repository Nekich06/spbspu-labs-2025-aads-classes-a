#include <iostream>
#include <functional>

template < class T >
struct BiTree
{
  T data;
  BiTree< T >* left, * right, * parent;
};

template< class T >
void clearBiTree(BiTree< T >** root)
{
  if (!(*root))
  {
    return;
  }
  clearBiTree(&(*root)->left);
  clearBiTree(&(*root)->right);
  delete *root;
  *root = nullptr;
}

template< class T, class Cmp>
void insert(BiTree< T >* root, BiTree< T >* node, Cmp cmp)
{
  BiTree< T >* yaroot = root;
  BiTree< T >* subroot = nullptr;
  while (yaroot)
  {
    subroot = yaroot;
    if (cmp(node->data, yaroot->data))
    {
      yaroot = yaroot->left;
    }
    else
    {
      yaroot = yaroot->right;
    }
  }
  if (cmp(node->data, subroot->data))
  {
    subroot->left = node;
  }
  else
  {
    subroot->right = node;
  }
  node->parent = subroot;
}

template< class T, class Cmp >
BiTree< T >* convert(size_t s, const T* data, Cmp cmp)
{
  if (s == 0)
  {
    return nullptr;
  }
  BiTree< T >* root = new BiTree< T >{ data[0], nullptr, nullptr, nullptr };
  try
  {
    for (size_t i = 1; i < s; i++)
    {
      BiTree< T >* newNode = new BiTree< T >{ data[i], nullptr, nullptr, nullptr };
      insert(root, newNode, cmp);
    }
  }
  catch (const std::bad_alloc& e)
  {
    clearBiTree(&root);
    throw;
  }
  return root;
}

template< class T, class Cmp >
BiTree< T >* find(BiTree< T >* root, const T& value, Cmp cmp)
{
  BiTree< T >* yaroot = root;
  while (yaroot && yaroot->data != value)
  {
    if (cmp(value, yaroot->data))
    {
      yaroot = yaroot->left;
    }
    else
    {
      yaroot = yaroot->right;
    }
  }
  if (!yaroot)
  {
    throw std::invalid_argument("<INVALID ROTATE>\n");
  }
  return yaroot;
}

template< class T >
BiTree< T >* rotate_left(BiTree< T >* root)
{
  if (root->right == nullptr)
  {
    throw std::invalid_argument("<INVALID ROTATE>\n");
  }
  BiTree< T >* newRoot = root->right;
  if (root->parent)
  {
    newRoot->parent = root->parent;
    root->parent->right = newRoot;
  }
  else
  {
    newRoot->parent = nullptr;
  }
  root->parent = newRoot;
  if (newRoot->left)
  {
    root->right = newRoot->left;
    root->right->parent = root;
  }
  else
  {
    root->right = nullptr;
  }
  newRoot->left = root;
  return newRoot;
}

template< class T >
BiTree< T >* rotate_right(BiTree< T >* root)
{
  if (root->left == nullptr)
  {
    throw std::invalid_argument("<INVALID ROTATE>\n");
  }
  BiTree< T >* newRoot = root->left;
  if (root->parent)
  {
    newRoot->parent = root->parent;
    root->parent->left = newRoot;
  }
  else
  {
    newRoot->parent = nullptr;
  }
  root->parent = newRoot;
  if (newRoot->right)
  {
    root->left = newRoot->right;
    root->left->parent = root;
  }
  else
  {
    root->left = nullptr;
  }
  newRoot->right = root;
  return newRoot;
}

template < class T >
BiTree< T >* getRoot(BiTree< T >* node)
{
  BiTree< T >* temp = node;
  if (!temp->parent)
  {
    return temp;
  }
  while (temp->parent)
  {
    temp = temp->parent;
  }
  return temp;
}

int main()
{
  size_t n = 0;
  int* array = nullptr;
  if (!(std::cin >> n))
  {
    std::cerr << "Input fail\n";
    return 1;
  }
  try
  {
    array = new int[n] {};
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "Out of memmory!\n";
    return 1;
  }
  for (size_t i = 0; i < n; i++)
  {
    int current = 0;
    if (!(std::cin >> current))
    {
      std::cerr << "Input fail!\n";
      delete[] array;
      return 1;
    }
    array[i] = current;
  }
  BiTree< int >* root = nullptr;
  try
  {
    root = convert(n, array, std::less< int >{});
    delete[] array;
  }
  catch (const std::bad_alloc& e)
  {
    delete[] array;
    std::cerr << "Out of memmory";
    return 1;
  }
  std::string command = "";
  int value = 0;
  while (!std::cin.eof() && std::cin >> command)
  {
    if (command == "left" || command == "right")
    {
      if (!(std::cin >> value))
      {
        std::cout << "<INVALID COMMAND>\n";
        clearBiTree(&root);
        return 1;
      }
      try
      {
        BiTree< int >* node = find(root, value, std::less< int >{});
        if (command == "left")
        {
          BiTree< int >* rotated = rotate_left(node);
          root = getRoot(rotated);
          std::cout << rotated->data << "\n";
        }
        else
        {
          BiTree< int >* rotated = rotate_right(node);
          root = getRoot(rotated);
          std::cout << rotated->data << "\n";
        }
      }
      catch (const std::invalid_argument& e)
      {
        std::cout << e.what();
      }
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      clearBiTree(&root);
      return 1;
    }
  }
  clearBiTree(&root);
}
