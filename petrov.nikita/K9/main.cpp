#include <iostream>

int main()
{
  size_t pairs_number = 0;
  if (!(std::cin >> pairs_number))
  {
    std::cerr << "ERROR: Invalid argument";
    std::cerr << "\n";
    return 1;
  }
  std::pair< int, int > * pairs_massive = new std::pair< int, int >[pairs_number];
  int first_number = 0;
  int second_number = 0;
  size_t i = 0;
  while (i < pairs_number && std::cin)
  {
    std::cin >> first_number;
    std::cin >> second_number;
    if (std::cin && second_number < first_number)
    {
      pairs_massive[i++] = { second_number, first_number };
    }
    else
    {
      pairs_massive[i++] = { first_number, second_number };
    }
  }
  std::cout << pairs_massive[0].first << " ";
  std::cout << pairs_massive[0].second;
  for (size_t i = 1; i < pairs_number; i++)
  {
    std::cout << " " << pairs_massive[i].first;
    std::cout << " " << pairs_massive[i].second;
  }
  delete pairs_massive;
  std::cout << "\n";
}