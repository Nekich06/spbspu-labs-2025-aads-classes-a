#include <iostream>
#include <string>

template< class T >
struct BiTree
{
  T data;
  BiTree< T > * left, * right, * parent;
};

template< class T >
BiTree< T >* rotate_right(BiTree< T >* root)
{
  if (root == nullptr || root->left == nullptr)
  {
    throw std::logic_error("<INVALID ROTATE>");
  }
  BiTree< T >* newRoot = root->left;
  BiTree< T >* node = newRoot->right;
  root->left = node;
  if (node)
  {
    node->parent = root;
  }
  newRoot->right = root;
  newRoot->parent = root->parent;
  root->parent = newRoot;
  if (newRoot->parent)
  {
    if (newRoot->parent->right == root)
    {
      newRoot->parent->right = newRoot;
    }
    else
    {
      newRoot->parent->left = newRoot;
    }
  }
  return newRoot;
}

template< class T >
BiTree< T >* rotate_left(BiTree< T >* root)
{
  if (root == nullptr || root->right == nullptr)
  {
    throw std::logic_error("<INVALID ROTATE>");
  }
  BiTree< T >* newRoot = root->right;
  BiTree< T >* node = newRoot->left;
  root->right = node;
  if (node)
  {
    node->parent = root;
  }
  newRoot->left = root;
  newRoot->parent = root->parent;
  root->parent = newRoot;
  if (newRoot->parent)
  {
    if (newRoot->parent->right == root)
    {
      newRoot->parent->right = newRoot;
    }
    else
    {
      newRoot->parent->left = newRoot;
    }
  }
  return newRoot;
}

template< class T, class Cmp >
BiTree< T >* find(BiTree< T >* root, const T& value, Cmp cmp)
{
  if (root == nullptr || root->data == value)
  {
    return root;
  }
  if (cmp(value, root->data))
  {
    return find(root->left, value, cmp);
  }
  else
  {
    return find(root->right, value, cmp);
  }
}

void deleteTree(BiTree< int >* root)
{
  if (root == nullptr)
  {
    return;
  }

  deleteTree(root-> left);
  deleteTree(root->right);

  delete root;
}

void insertNode(BiTree< int >* root, int value)
{
  BiTree< int >* current = root;
  BiTree< int >* parent = nullptr;

  while (current)
  {
    parent = current;
    if (value < current->data)
    {
      current = current->left;
    }
    else
    {
      current = current->right;
    }
  }

  current = new BiTree< int >{ value, nullptr, nullptr, parent };
  if (value < parent->data)
  {
    parent->left = current;
  }
  else
  {
    parent->right = current;
  }
}

BiTree< int >* buildTree(size_t size)
{
  if (size <= 0)
  {
    return nullptr;
  }

  int value = 0;
  if (!(std::cin >> value))
  {
    throw std::invalid_argument("");
  }
  BiTree< int >* root = new BiTree< int >{ value, nullptr, nullptr, nullptr };

  for (size_t i = 1; i < size; i++)
  {
    if (!(std::cin >> value))
    {
      deleteTree(root);
      throw std::invalid_argument("");
    }
    insertNode(root, value);
  }

  return root;
}
int main()
{
  size_t size = 0;
  if (!(std::cin >> size))
  {
    std::cerr << "Incorrect sequence size" << '\n';
    return 1;
  }
  BiTree< int >* root = nullptr;

  try
  {
    root = buildTree(size);
  }
  catch (const std::bad_alloc& e)
  {
    std::cerr << "Memory allocation error!\n";
    return 2;
  }
  catch (const std::invalid_argument& e)
  {
    deleteTree(root);
    std::cerr << "Incorrect input!\n";
    return 1;
  }

  std::string command;
  int value = 0;
  while (std::cin >> command >> value)
  {
    BiTree< int >* node = find(root, value, std::less< int >());
    BiTree< int >* temp = nullptr;
    try
    {
      if (command == "left")
      {
        temp = rotate_left(node);
      }
      else if (command == "right")
      {
        temp = rotate_right(node);
      }
    }
    catch (const std::logic_error& e)
    {
      std::cout << e.what() << '\n';
      continue;
    }
    if (!temp)
    {
      deleteTree(root);
      std::cout << "<INVALID COMMAND>\n";
      return 1;
    }
    if (node == root)
    {
      root = temp;
    }
    std::cout << temp->data << '\n';
  }
  if (!(std::cin.eof()))
  {
    std::cout << "<INVALID COMMAND>\n";
  }

  deleteTree(root);
  return 0;
}
