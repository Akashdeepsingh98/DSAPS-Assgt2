#include <iostream>
using namespace std;

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int min(int a, int b)
{
    if (a > b)
        return b;
    return a;
}

template <class T>
class Node
{
private:
public:
    T data;
    Node<T> *left;
    Node<T> *right;
    int height;
    Node(T data)
    {
        this->data = data;
        this->left = this->right = nullptr;
    }

    int balanceFactor()
    {
        if (this->left == nullptr && this->right == nullptr)
        {
            return 0;
        }
        else if (this->left == nullptr)
        {
            return -this->right->height;
        }
        else if (this->right == nullptr)
        {
            return this->left->height;
        }
        else
        {
            return this->left->height - this->right->height;
        }
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
        z->height = max(z->left->height, z->right->height) + 1;
        y->height = max(y->left->height, y->right->height) + 1;
        return y;
    }

    Node<T> *leftRotate(Node<T> *z)
    {
        Node<T> *y = z->right;
        Node<T> *yleft = y->left;
        y->left = z;
        z->right = yleft;
        z->height = max(z->left->height, z->right->height) + 1;
        y->height = max(y->left->height, y->right->height) + 1;
        return y;
    }

    Node<T> *insertUtil(Node<T> *node, Node<T> *newnode)
    {
        // if empty tree
        if (node == nullptr)
        {
            return newnode;
        }

        if (*newnode < node->data)
        {
            node->left = insertUtil(node->left, newnode);
        }
        else if (*newnode > node->data)
        {
            node->right = insertUtil(node->right, newnode);
        }
        else if (*newnode == node->data)
        {
            node->left = insertUtil(node->left, newnode);
        }
    }

    void insert(T data)
    {
        Node<T> *newnode = new Node<T>(data);
        this->insertUtil(this->root, newnode);
    }
};

int main()
{
    AVL<int> *a = new AVL<int>();
    a->insert(5);
    cout << a->root->data << endl;
}