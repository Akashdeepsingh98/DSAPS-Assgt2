#include <iostream>
using namespace std;

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

    T getval(int &keyhash)
    {
        if (keyhash >= capacity)
        {
            cout << "Provide valid key" << endl;
            return -1;
        }
        if (this->arr[keyhash] == nullptr)
        {
            cout << "Provided key has no value" << endl;
            return -1;
        }
        return this->arr[keyhash]->data;
    }

    Node<T> &setval(int &keyhash)
    {
        if (keyhash >= this->capacity)
        {
            this->incrSize(keyhash + 1);
        }
        this->arr[keyhash] = new Node<T>(0);
        return this->arr[keyhash];
    }
};

template <class K, class V>
class UnorderedMap
{
private:
public:
    Vector<V> vector;
    int capacity;
    UnorderedMap()
    {
        this->capacity = 50;
    }
    void insert(K key, V value)
    {
        int keyhash = this->hashfunc(key);
        this->vector.insert(keyhash, value);
    }
    int hashfunc(K &key)
    {
        return int(key);
    }
    void erase(K &key)
    {
        int keyhash = this->hashfunc(key);
        this->vector.erase(keyhash);
    }
    bool find(K &key)
    {
        int keyhash = this->hashfunc(key);
        return this->vector.find(keyhash);
    }

    V operator[](K key) 
    {
        int keyhash = this->hashfunc(key);
        return this->vector.getval(keyhash);
    }

    //Node<V> &operator[](K key)
    //{
    //    int keyhash = this->hashfunc(key);
    //    return this->vector.setval(keyhash);
    //}
};

int main()
{
    UnorderedMap<int, int> um;
    um.insert(3,5);
    cout<<um[3]<<endl;
}