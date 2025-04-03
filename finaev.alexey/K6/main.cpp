#include <iostream>

template< class T >
struct BiTree
{
  T data;
  BiTree< T >* left;
  BiTree< T >* right;
  BiTree< T >* parent;
  BiTree< T >(T x):
    data(x),
    left(nullptr),
    right(nullptr),
    parent(nullptr)
  {}
};

template< class T >
void deleteTree(BiTree< T >* tree)
{
  if (tree)
  {
    deleteTree(tree->left);
    deleteTree(tree->right);
    delete tree;
  }
}

BiTree< int >* convert(int* nums, size_t size)
{
  if(!nums)
  {
    return nullptr;
  }
  BiTree< int >* head = new BiTree< int >(nums[0]);
  BiTree< int >* current = head;
  for (size_t i = 1; i < size; ++i)
  {
    BiTree< int >* elem = nullptr;
    try
    {
      elem = new BiTree< int >(nums[i]);
    }
    catch (const std::bad_alloc&)
    {
      deleteTree(head);
      throw;
    }
    while (true)
    {
      if (nums[i] < current->data)
      {
        if (current->left)
        {
          current = current->left;
        }
        else
        {
          current->left = elem;
          elem->parent = current;
          break;
        }
      }
      else
      {
        if (current->right)
        {
          current = current->right;
        }
        else
        {
          current->right = elem;
          elem->parent = current;
          break;
        }
      }
    }
    current = head;
  }
  return head;
}

template< class T >
BiTree< T >* rotate_right(BiTree< T >* root)
{
  if (!root || !root->left)
  {
    throw std::logic_error("<INVALID ROTATE>\n");
  }
  BiTree< T >* newHead = root->left;
  root->left = newHead->right;
  newHead->right = root;
  newHead->parent = root->parent;
  root->parent = newHead;
  if (!newHead->parent)
  {
    return newHead;
  }
  else
  {
    if (newHead->parent->left == root)
    {
      newHead->parent->left = newHead;
      return newHead;
    }
    else
    {
      newHead->parent->right = newHead;
      return newHead;
    }
  }
}

template< class T >
BiTree< T >* rotate_left(BiTree< T >* rotateRoot)
{
  BiTree< T >* root = rotateRoot;
  if (!root || !root->right)
  {
    throw std::logic_error("<INVALID ROTATE>\n");
  }
  BiTree< T >* newHead = root->right;
  root->right = newHead->left;
  newHead->left = root;
  newHead->parent = root->parent;
  root->parent = newHead;
  if (!newHead->parent)
  {
    return newHead;
  }
  else
  {
    if (newHead->parent->left == root)
    {
      newHead->parent->left = newHead;
      return newHead;
    }
    else
    {
      newHead->parent->right = newHead;
      return newHead;
    }
  }
}

template< class T, class Cmp >
BiTree< T >* find(BiTree< T >* root, const T& value, Cmp cmp)
{
  if (!root)
  {
    return nullptr;
  }
  if (root->data == value)
  {
    return root;
  }
  else
  {
    if (cmp(value, root->data))
    {
      root = find(root->right, value, cmp);
      return root;
    }
    else
    {
      root = find(root->left, value, cmp);
      return root;
    }
  }
}

int main()
{
  size_t size = 0;
  std::cin >> size;
  int* nums = nullptr;
  if (size != 0)
  {
    nums = new int[size];
  }
  size_t i = 0;
  while (!std::cin.eof() && i < size)
  {
    int a = 0;
    std::cin >> a;
    nums[i++] = a;
  }
  if (std::cin.fail())
  {
    delete[] nums;
    std::cerr << "uncorrect argument\n";
    return 1;
  }
  if (i < size)
  {
    delete[] nums;
    std::cerr << "incomplete sequence!\n";
    return 1;
  }
  BiTree< int >* head = nullptr;
  try
  {
    head = convert(nums, size);
  }
  catch (const std::bad_alloc&)
  {
    std::cerr << "bad alloc!\n";
    delete[] nums;
    return 1;
  }
  std::string cmd = "";
  int data = 0;
  BiTree< int >* res = nullptr;
  while (!std::cin.eof() && std::cin >> cmd)
  {
    std::cin >> data;
    if (std::cin.fail())
    {
      std::cout << "<INVALID COMMAND>\n";
      delete[] nums;
      deleteTree(head);
      return 1;
    }
    if (cmd == "left")
    {
      BiTree< int >* cur = head;
      BiTree< int >* temp = find(cur, data, std::less< int >());
      try
      {
        res = rotate_left(temp);
        std::cout << res->data << "\n";
        if (temp == head)
        {
          head = res;
        }
      }
      catch(const std::logic_error& e)
      {
        std::cout << e.what();
      }
    }
    else if (cmd == "right")
    {
      BiTree< int >* cur = head;
      BiTree< int >* temp = find(cur, data, std::less< int >());
      try
      {
        res = rotate_right(temp);
        std::cout << res->data << "\n";
        if (temp == head)
        {
          head = res;
        }
      }
      catch(const std::logic_error& e)
      {
        std::cout << e.what();
      }
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
      delete[] nums;
      deleteTree(head);
      return 1;
    }
  }
  delete[] nums;
  deleteTree(head);
}
