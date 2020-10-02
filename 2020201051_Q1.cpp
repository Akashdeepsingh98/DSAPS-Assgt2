#include <iostream>

template <class T>
class Node
{
private:
public:
    T data;
    Node<T> *left, right;
    Node(T data)
    {
        this->data = data;
        this->left = this->right = nullptr;
    }
};

template <class T>
class AVL
{
private:
public:
    Node<T> *root;
    AVL()
    {
        this->root = nullptr;
    }

    Node<T> *rightRotate(Node<T> *z)
    {
        Node<T> *y = z->left;
        Node<T> *yright = y->right;
        y->right = z;
        z->left = yright;
        return y;
    }

    Node<T> *leftRotate(Node<T> *z)
    {
        Node<T> *y = z->right;
        Node<T> *yleft = y->left;
        y->left = z;
        z->right = yleft;
        return y;
    }
};

int main()
{
}