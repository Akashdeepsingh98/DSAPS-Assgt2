#include <iostream>
using namespace std;

class IntegerHash
{
public:
    long long int operator()(long long int a)
    {
        return a;
    }
};

class StringHash
{
public:
    long long int operator()(string s)
    {
        long long int sum = 0;
        for (int i = 0; i < s.size(); i++)
        {
            sum += s[i];
        }
        return sum;
    }
};

class DecimalHash
{
public:
    long long int operator()(long double a)
    {
        return (long long int)a;
    }
};

class CharHash
{
public:
    int operator()(char a)
    {
        return a;
    }
};

template <class T>
class Node
{
private:
public:
    Node<T> *next;
    T data;
    Node(T &data)
    {
        this->data = data;
        this->next = nullptr;
    }
    void operator=(T data)
    {
        this->data = data;
    }
};

template <class T>
class Vector
{
private:
public:
    Node<T> **arr;
    int capacity;
    Vector()
    {
        this->arr = new Node<T> *[50];
        for (int i = 0; i < 50; i++)
        {
            this->arr[i] = nullptr;
        }
        this->capacity = 50;
    }

    void insert(int keyhash, T value)
    {
        if (keyhash >= this->capacity)
        {
            this->incrSize(keyhash + 1);
        }

        this->arr[keyhash] = new Node<T>(value);
    }

    void incrSize(int newsize)
    {
        Node<T> **newarr = new Node<T> *[newsize];
        for (int i = 0; i < this->capacity; i++)
        {
            newarr[i] = this->arr[i];
        }
        this->arr = newarr;
        this->capacity = newsize;
    }

    void erase(int &keyhash)
    {
        if (keyhash >= this->capacity)
            return;
        this->arr[keyhash] = nullptr;
    }

    bool find(int &keyhash)
    {
        if (keyhash >= this->capacity)
            return false;
        if (this->arr[keyhash] == nullptr)
            return false;
        return true;
    }

    void getval(int &keyhash, T &result)
    {
        if (keyhash >= capacity)
        {
            cout << "Provide valid key" << endl;
            return;
        }
        if (this->arr[keyhash] == nullptr)
        {
            cout << "Provided key has no value" << endl;
            return;
        }
        //return this->arr[keyhash]->data;
        result = this->arr[keyhash]->data;
    }

    Node<T> &setval(int &keyhash)
    {
        if (keyhash >= this->capacity)
        {
            this->incrSize(keyhash + 1);
        }
        this->arr[keyhash] = new Node<T>(0);
        return *(this->arr[keyhash]);
    }
};

template <class K, class V, class Hasher>
class UnorderedMap
{
private:
public:
    Vector<V> vector;
    int capacity;
    Hasher hasher;
    UnorderedMap()
    {
        this->capacity = 50;
    }
    void insert(K key, V value)
    {
        int keyhash = this->hasher(key);
        this->vector.insert(keyhash, value);
    }
    void erase(K key)
    {
        int keyhash = this->hasher(key);
        this->vector.erase(keyhash);
    }
    bool find(K key)
    {
        int keyhash = this->hasher(key);
        return this->vector.find(keyhash);
    }

    V operator[](K key)
    {
        int keyhash = this->hasher(key);
        V result;
        this->vector.getval(keyhash, result);
        return result;
    }
};

int main()
{
    UnorderedMap<string, string, StringHash> um;
    um.insert("name", "akash");
    cout << um["named"] << endl;
}