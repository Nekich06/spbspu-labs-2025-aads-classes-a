#include <iostream>
#include <functional>

namespace
{
  template< class T >
  struct BiTree {
    T data;
    BiTree< T > * left, * right, * parent;
  };

  template< class T >
  BiTree< T >* rotate_right(BiTree< T >* const root)
  {
    if (root == nullptr || root->left == nullptr)
    {
      throw std::logic_error("<INVALID ROTATE>");
    }
    BiTree< T >* rotate_tree = root->left;
    if (root->parent != nullptr)
    {
      if (root->parent->left == root)
      {
        root->parent->left = rotate_tree;
      }
      else
      {
        root->parent->right = rotate_tree;
      }
    }
    root->left = rotate_tree->right;
    if (rotate_tree->right != nullptr)
    {
      rotate_tree->right->parent = root;
    }
    rotate_tree->right = root;
    rotate_tree->parent = root->parent;
    root->parent = rotate_tree;
    return rotate_tree;
  }

  template< class T >
  BiTree< T >* rotate_left(BiTree< T >* const root)
  {
    if (root == nullptr || root->right == nullptr)
    {
      throw std::logic_error("<INVALID ROTATE>");
    }
    BiTree< T >* rotate_tree = root->right;
    if (root->parent != nullptr)
    {
      if (root->parent->left == root)
      {
        root->parent->left = rotate_tree;
      }
      else
      {
        root->parent->right = rotate_tree;
      }
    }
    root->right = rotate_tree->left;
    if (rotate_tree->left != nullptr)
    {
      rotate_tree->left->parent = root;
    }
    rotate_tree->left = root;
    rotate_tree->parent = root->parent;
    root->parent = rotate_tree;
    return rotate_tree;
  }

  template< class T, class Cmp >
  BiTree< T >* find(BiTree< T >* root, const T& value, Cmp cmp)
  {
    while (root != nullptr && value != root->data)
    {
      if (cmp(value, root->data))
      {
        root = root->left;
      }
      else
      {
        root = root->right;
      }
    }
    return root;
  }

  template< class T >
  void clear(BiTree< T >* root)
  {
    if (root)
    {
      clear(root->left);
      clear(root->right);
      delete root;
    }
  }

  template< class T, class Cmp >
  BiTree< T >* insertValue(BiTree< T >* const root, const T value, Cmp cmp)
  {
    if (root == nullptr)
    {
      return new BiTree< T >{value, nullptr, nullptr, nullptr};
    }
    else if (cmp(value, root->data))
    {
      root->left = insertValue(root->left, value, cmp);
      if (root->left->parent == nullptr)
      {
        root->left->parent = root;
      }
    }
    else
    {
      root->right = insertValue(root->right, value, cmp);
      if (root->right->parent == nullptr)
      {
        root->right->parent = root;
      }
    }
    return root;
  }
}

int main()
{
  size_t size = 0;
  std::cin >> size;
  if (!std::cin >> size)
  {
    std::cerr << "Wrong input\n";
    return 1;
  }
  BiTree< int >* root = nullptr;
  int value = 0;
  for (size_t i = 0; i < size; ++i)
  {
    if (!(std::cin >> value))
    {
      clear(root);
      std::cerr << "Wrong input\n";
      return 1;
    }
    try
    {
      root = insertValue(root, value, std::less<int>());
    }
    catch (const std::bad_alloc&)
    {
      clear(root);
      std::cerr << "Memory error\n";
      return 1;
    }
  }
  std::string rotate_command = "";
  int num = 0;
  while (std::cin >> rotate_command)
  {
    if (!(std::cin >> num))
    {
      clear(root);
      std::cout << "INVALID COMMAND\n";
      return 1;
    }
    BiTree< int >* find_tree = find(root, num, std::less< int >());
    BiTree< int >* rotate_tree = nullptr;
    try
    {
      if (rotate_command == "left")
      {
        rotate_tree = rotate_left(find_tree);
      }
      else if (rotate_command == "right")
      {
        rotate_tree = rotate_right(find_tree);
      }
      else
      {
        clear(root);
        std::cout << "INVALID COMMAND\n";
        return 1;
      }
    }
    catch (const std::logic_error& e)
    {
      std::cout << e.what() << "\n";
      continue;
    }
    std::cout << rotate_tree->data << "\n";
    if (find_tree == root)
    {
      root = rotate_tree;
    }
  }
  clear(root);
  return 0;
}
