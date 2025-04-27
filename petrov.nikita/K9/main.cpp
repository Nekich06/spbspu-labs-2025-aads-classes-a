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
public:
  using this_t = TriTreeIterator< T, Cmp >;
  TriTreeIterator(TriTree< T, Cmp > * root):
    node_(root)
  {}
  TriTreeIterator(const this_t & rhs) = default;
  TriTreeIterator(this_t && rhs) = default;
  this_t & operator=(const this_t & rhs) = default;
  this_t & operator=(this_t && rhs) = default;
  bool operator==(this_t rhs)
  {
    return node_ == rhs.node_;
  }
  bool operator!=(this_t rhs)
  {
    return !(*this == rhs);
  }
  bool hasNext() const
  {
    if (node_->middle || node_->right || node_->parent->left == node_)
    {
      return true;
    }
    auto temp = node_->parent;
    while (temp->parent && temp->parent->data.second < temp->data.second)
    {
      temp = temp->parent;
    }
    temp = temp->parent;
    return temp;
  }
  bool hasPrev() const;
  this_t prev() const;
  this_t next() const
  {
    auto temp = node_;
    if (node_->middle)
    {
      temp = node_->middle;
    }
    else if (node_->right)
    {
      temp = node_->right;
    }
    else if (node_->parent->left == node_)
    {
      temp = node_->parent;
      return this_t(temp);
    }
    else if (node_->parent->middle == node_ && node_->parent->right)
    {
      temp = node_->parent->right;
    }
    else
    {
      while (temp->parent->data.second < temp->data.second)
      {
        temp = temp->parent;
      }
      if (temp->parent->middle == temp && temp->parent->right)
      {
        temp = temp->parent->right;
      }
      else
      {
        temp = temp->parent;
        return this_t(temp);
      }
    }
    while (temp->left)
    {
      temp = temp->left;
    }
    return this_t(temp);
  }
  std::pair< T, T > & data()
  {
    return node_->data;
  }
private:
  TriTree< T, Cmp > * node_;
};

template< class T, class Cmp >
TriTreeIterator< T, Cmp > begin(TriTree< T, Cmp > * root)
{
  while (root->left)
  {
    root = root->left;
  }
  return TriTreeIterator< T, Cmp >(root);
}

template< class T, class Cmp >
TriTreeIterator< T, Cmp > rbegin(TriTree< T, Cmp > * root)
{
  while (root->right)
  {
    root = root->right;
  }
  return TriTreeIterator< T, Cmp >(root);
}

template< class T, class Cmp >
void clearTriTree(TriTree< T, Cmp > * root)
{
  if (root)
  {
    clearTriTree(root->left);
    clearTriTree(root->middle);
    clearTriTree(root->right);
  }
  delete root;
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
        if (cmp(array[i].second, temp->data.second) && cmp(temp->data.first, array[i].first) && temp->middle)
        {
          temp = temp->middle;
        }
        else if (cmp(array[i].second, temp->data.first) && temp->left)
        {
          temp = temp->left;
        }
        else if (cmp(temp->data.second, array[i].first) && temp->right)
        {
          temp = temp->right;
        }
        else
        {
          break;
        }
      }
      if (cmp(array[i].second, temp->data.second) && cmp(temp->data.first, array[i].first))
      {
        temp->middle = new TriTree< T, Cmp >{ array[i], nullptr, nullptr, nullptr, temp };
      }
      else if (cmp(array[i].second, temp->data.first))
      {
        temp->left = new TriTree< T, Cmp >{ array[i], nullptr, nullptr, nullptr, temp };
      }
      else if (cmp(temp->data.second, array[i].first))
      {
        temp->right = new TriTree< T, Cmp >{ array[i], nullptr, nullptr, nullptr, temp };
      }
      else
      {
        continue;
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
  else if (!pairs_number)
  {
    return 0;
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
  if (!std::cin)
  {
    delete[] pairs_array;
    std::cerr << "ERROR: Invalid argument";
    std::cerr << "\n";
    return 1;
  }
  TriTree< int, std::less< int > > * root = convert(pairs_array, pairs_number, std::less< int >());
  outputTriTreeOfPairs(std::cout, root) << '\n';
  std::string command_name;
  int begin_of_segment = 0;
  int end_of_segment = 0;
  auto last_it = rbegin(root);
  while (!std::cin.eof())
  {
    std::cin >> command_name;
    std::cin >> begin_of_segment;
    std::cin >> end_of_segment;
    if (std::cin.eof())
    {
      continue;
    }
    else if (!std::cin || begin_of_segment > end_of_segment)
    {
      std::cin.clear();
      std::cin.ignore(1024, '\n');
      std::cout << "<INVALID COMMAND>";
      std::cout << "\n";
      continue;
    }
    size_t count = 0;
    if (pairs_number > 1)
    {
      if (command_name == "intersects")
      {
        for (auto it = begin(root); it.hasNext(); it = it.next())
        {
          if ((it.data().first >= begin_of_segment && it.data().first <= end_of_segment) ||
              (it.data().second >= begin_of_segment &&  it.data().second <= end_of_segment))
          {
            count++;
          }
          if (it.next() == last_it)
          {
            if ((it.data().first >= begin_of_segment && it.data().first <= end_of_segment) ||
                (it.data().second >= begin_of_segment &&  it.data().second <= end_of_segment))
            {
              count++;
            }
          }
        }
        std::cout << count << "\n";
      }
      else if (command_name == "covers")
      {
        for (auto it = begin(root); it.hasNext(); it = it.next())
        {
          if (it.data().first >= begin_of_segment && it.data().first <= end_of_segment &&
              it.data().second >= begin_of_segment &&  it.data().second <= end_of_segment)
          {
            count++;
          }
          if (it.next() == last_it)
          {
            if (it.data().first >= begin_of_segment && it.data().first <= end_of_segment &&
                it.data().second >= begin_of_segment &&  it.data().second <= end_of_segment)
            {
              count++;
            }
          }
        }
        std::cout << count << "\n";
      }
      else if (command_name == "avoids")
      {
        for (auto it = begin(root); it.hasNext(); it = it.next())
        {
          if (!((it.data().first >= begin_of_segment && it.data().first <= end_of_segment) ||
              (it.data().second >= begin_of_segment &&  it.data().second <= end_of_segment)))
          {
            count++;
          }
          if (it.next() == last_it)
          {
            if (!((it.data().first >= begin_of_segment && it.data().first <= end_of_segment) ||
                (it.data().second >= begin_of_segment &&  it.data().second <= end_of_segment)))
            {
              count++;
            }
          }
        }
        std::cout << count << "\n";
      }
      else
      {
        std::cerr << "ERROR: Invalid command";
        std::cerr << "\n";
        clearTriTree(root);
        delete[] pairs_array;
        return 2;
      }
    }
    else
    {
      if (command_name == "intersects")
      {
        auto it = begin(root);
        if ((it.data().first >= begin_of_segment && it.data().first <= end_of_segment) ||
            (it.data().second >= begin_of_segment &&  it.data().second <= end_of_segment))
        {
          count++;
        }
        std::cout << count << "\n";
      }
      else if (command_name == "covers")
      {
        auto it = begin(root);
        if (it.data().first >= begin_of_segment && it.data().first <= end_of_segment &&
            it.data().second >= begin_of_segment &&  it.data().second <= end_of_segment)
        {
          count++;
        }
        std::cout << count << "\n";
      }
      else if (command_name == "avoids")
      {
        auto it = begin(root);
        if (!((it.data().first >= begin_of_segment && it.data().first <= end_of_segment) ||
            (it.data().second >= begin_of_segment &&  it.data().second <= end_of_segment)))
        {
          count++;
        }
        std::cout << count << "\n";
      }
      else
      {
        std::cerr << "ERROR: Invalid command";
        std::cerr << "\n";
        clearTriTree(root);
        delete[] pairs_array;
        return 2;
      }
    }
  }
  clearTriTree(root);
  delete[] pairs_array;
}