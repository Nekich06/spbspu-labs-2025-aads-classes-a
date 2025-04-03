template <class T>
struct List {
    T data;
    List<T> *next;
};

List< List< int > * > * convert(const int * const * d, size_t m, const size_t * n);

template< class T, class C >
size_t count(const List< List< T > * > * head, C condition);

int main()
{

}
