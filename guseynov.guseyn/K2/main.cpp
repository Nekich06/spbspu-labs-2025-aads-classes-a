#include <iostream>
#include <cstddef>
#include <stdexcept>

struct FwdList
{
    int value;
    FwdList* next;
};

void printList(std::ostream& out, const FwdList* head);
void deleteList(FwdList* head);
FwdList* duplicateElements(FwdList* head, size_t index, size_t count);
size_t determinateLength(FwdList* head);

int main()
{
    FwdList* head = nullptr;
    FwdList* tail = nullptr;
    try
    {
        FwdList* newElement = new FwdList{ 0, nullptr };
        head = newElement;
        tail = newElement;
        for (int i = 1; i < 10; ++i)
        {
            FwdList* newElement = new FwdList{ i, nullptr };
            tail->next = newElement;
            tail = newElement;
        }
    }
    catch (const std::bad_alloc&)
    {
        std::cerr << "Memory error\n";
        deleteList(head);
        return 1;
    }
    size_t index = 0;
    size_t count = 0;
    while (std::cin >> index >> count && !std::cin.eof())
    {
        try
        {
            duplicateElements(head, index, count);
        }
        catch (const std::exception& e)
        {
            deleteList(head);
            std::cerr << e.what() << "\n";
            return 1;
        }
    }
    printList(std::cout, head);
    std::cout << "\n";
    deleteList(head);
}

void printList(std::ostream& out, const FwdList* head)
{
    out << head->value;
    head = head->next;
    while (head)
    {
        out << " " << head->value;
        head = head->next;
    }
}

void deleteList(FwdList* head)
{
    while (head)
    {
        FwdList* next = head->next;
        delete head;
        head = next;
    }
}

size_t determinateLength(FwdList* head)
{
    FwdList* subhead = head;
    size_t res = 0;
    while (subhead)
    {
        subhead = subhead->next;
        res++;
    }
    return res;
}

FwdList* duplicateElements(FwdList* head, size_t index, size_t count)
{
    if (index < 1)
    {
        throw std::invalid_argument("index must be positive");
    }
    FwdList* subhead = head;
    size_t length = determinateLength(head);
    if (index > length)
    {
        throw std::out_of_range("out of range");
    }
    for (size_t j = 1; j < index; j++)
    {
        subhead = subhead->next;
    }
    FwdList* node = subhead;
    for (size_t i = 0; i < count; ++i)
    {
        FwdList* newElement = new FwdList{ subhead->value, node->next };
        node->next = newElement;
        node = newElement;
    }
    return subhead;
}
