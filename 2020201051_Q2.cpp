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
    Node(T data)
    {
        this->data = data;
        this->next = nullptr;
    }
    Node()
    {
        this->next = nullptr;
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

    void insert(long long int keyhash, T value)
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

    void erase(long long int &keyhash)
    {
        if (keyhash >= this->capacity)
            return;
        this->arr[keyhash] = nullptr;
    }

    bool find(long long int &keyhash)
    {
        if (keyhash >= this->capacity)
            return false;
        if (this->arr[keyhash] == nullptr)
            return false;
        return true;
    }

    T &getval(long long int &keyhash)
    {
        if (keyhash >= capacity)
        {
            this->incrSize(keyhash + 1);
            this->arr[keyhash] = new Node<T>();
        }
        if (this->arr[keyhash] == nullptr)
        {
            this->arr[keyhash] = new Node<T>();
        }
        return this->arr[keyhash]->data;
    }

    Node<T> &setval(long long int &keyhash)
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
        long long int keyhash = this->hasher(key);
        this->vector.insert(keyhash, value);
    }
    void erase(K key)
    {
        long long int keyhash = this->hasher(key);
        this->vector.erase(keyhash);
    }
    bool find(K key)
    {
        long long int keyhash = this->hasher(key);
        return this->vector.find(keyhash);
    }

    V &operator[](K key)
    {
        long long int keyhash = this->hasher(key);
        return this->vector.getval(keyhash);
    }
};

int main()
{
    //UnorderedMap<string, string, StringHash> um;
    //um.insert("name", "akashdeep");
    //um["surname"] = "singh";
    //cout << um["name"] << endl;
    //cout << um["surname"] << endl;

    UnorderedMap<int, int, IntegerHash> um;
    um.insert(3,5);
    um[5] = 7;
    cout<<um[um[3]]<<endl;
}