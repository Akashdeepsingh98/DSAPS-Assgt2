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

        if (this->arr[keyhash] == nullptr)
        {
            this->arr[keyhash] = new Node<T>(value);
            return;
        }

        Node<T> *cur = this->arr[keyhash];
        while (cur->next != nullptr)
        {
            cur = cur->next;
        }
        cur->next = new Node<T>(value);
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
        if (this->arr[keyhash] == nullptr)
            return;
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
    void insert(K &key, V &value)
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
};

int main()
{
}