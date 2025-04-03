#include <iostream>
#include <functional>
#include <string>

template< class T >
struct BiTree
{
  T data;
  BiTree< T >* left = nullptr;
  BiTree< T >* right = nullptr;
  BiTree< T >* parent = nullptr;
};
template< class T >
BiTree< T >* rotate_right(BiTree< T >* root)
{
  if ((root == nullptr) || (root->left == nullptr))
  {
    return nullptr;
  }
  BiTree< T >* result = root->left;
  result->parent = root->parent;
  if (root->parent != nullptr)
  {
    if (root->parent->left == root)
    {
      root->parent->left = result;
    }
    else
    {
      root->parent->right = result;
    }
  }
  root->parent = result;
  root->left = result->right;
  result->right = root;
  return result;
}
template< class T >
BiTree< T >* rotate_left(BiTree< T >* root)
{
  if ((root == nullptr) || (root->right == nullptr))
  {
    return nullptr;
  }
  BiTree< T >* result = root->right;
  result->parent = root->parent;
  if (root->parent != nullptr)
  {
    if (root->parent->left == root)
    {
      root->parent->left = result;
    }
    else
    {
      root->parent->right = result;
    }
  }
  root->parent = result;
  root->right = result->left;
  result->left = root;
  return result;
}
template< class T, class C >
BiTree< T >* find(BiTree< T >* root, const T& value, C compare)
{
  while (root != nullptr)
  {
    if (compare(value, root->data))
    {
      root = root->left;
    }
    else if (compare(root->data, value))
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
template< class T, class C >
BiTree< T >* insert(BiTree< T >* root, const T& value, C compare)
{
  BiTree< T >* result = root;
  if (root == nullptr)
  {
    return new BiTree< T >{value};
  }
  while (true)
  {
    if (compare(value, root->data))
    {
      if (root->left == nullptr)
      {
        root->left = new BiTree< T >{value, nullptr, nullptr, root};
        break;
      }
      else
      {
        root = root->left;
      }
    }
    else
    {
      if (root->right == nullptr)
      {
        root->right = new BiTree< T >{value, nullptr, nullptr, root};
        break;
      }
      else
      {
        root = root->right;
      }
    }
  }
  return result;
}
template< class T >
void destroy(BiTree< T >* root)
{
  if (root == nullptr)
  {
    return;
  }
  destroy(root->left);
  destroy(root->right);
  delete root;
}

int main()
{
  size_t size = 0;
  if (!(std::cin >> size))
  {
    std::cerr << "failed to read size\n";
    return 1;
  }
  BiTree< int >* root = nullptr;
  int number = 0;
  for (; (size != 0) && (std::cin >> number); size--)
  {
    try
    {
      root = insert(root, number, std::less< int >());
    }
    catch (...)
    {
      std::cerr << "failed to construct tree\n";
      destroy(root);
      return 2;
    }
  }
  if (size != 0)
  {
    std::cerr << "failed to read tree\n";
    destroy(root);
    return 1;
  }

  std::string input;
  while (std::cin >> input)
  {
    if (!(std::cin >> number))
    {
      destroy(root);
      std::cout << "<INVALID COMMAND>\n";
      return 1;
    }

    BiTree< int >* node = find(root, number, std::less< int >());
    BiTree< int >* temp = nullptr;
    if (input == "left")
    {
      temp = rotate_left(node);
    }
    else if (input == "right")
    {
      temp = rotate_right(node);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      destroy(root);
      return 1;
    }

    if (temp == nullptr)
    {
      std::cout << "<INVALID ROTATE>\n";
      continue;
    }
    if (node == root)
    {
      root = temp;
    }
    std::cout << temp->data << '\n';
  }
  destroy(root);
}
