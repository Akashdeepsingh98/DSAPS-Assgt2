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
};

template <class T>
class AVL
{
private:
    int height(Node<T> *node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }
    int balance(Node<T> *node)
    {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    void inorderUtil(Node<T> *node)
    {
        if (node != nullptr)
        {
            inorderUtil(node->left);
            cout << node->data << " ";
            inorderUtil(node->right);
        }
    }

    Node<T> *insertUtil(Node<T> *node, Node<T> *newnode)
    {
        // if empty tree
        if (node == nullptr)
        {
            return newnode;
        }

        if (newnode->data < node->data)
        {
            node->left = insertUtil(node->left, newnode);
        }
        else if (newnode->data > node->data)
        {
            node->right = insertUtil(node->right, newnode);
        }
        else if (newnode->data == node->data)
        {
            node->left = insertUtil(node->left, newnode);
        }

        int nodebal = balance(node);

        //left left
        if (nodebal > 1 && newnode->data <= node->left->data)
        {
            return rightRotate(node);
        }

        //right right
        if (nodebal < -1 && newnode->data > node->right->data)
        {
            return leftRotate(node);
        }

        //left right
        if (nodebal > 1 && newnode->data > node->left->data)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        //right left
        if (nodebal < -1 && newnode->data < node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

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

    void insert(T data)
    {
        Node<T> *newnode = new Node<T>(data);
        this->root = this->insertUtil(this->root, newnode);
    }

    void inorder()
    {
        inorderUtil(this->root);
        cout << endl;
    }
};

int main()
{
    AVL<int> *a = new AVL<int>();
    a->insert(10);
    a->insert(20);
    a->insert(30);
    a->insert(50);
    a->insert(25);
    a->insert(40);
    a->insert(10);
    a->inorder();
}