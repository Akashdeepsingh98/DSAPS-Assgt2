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
        this->height = 1;
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
            cout << node->data << " " << node->height << endl;
            inorderUtil(node->right);
        }
    }

    Node<T> *insertUtil(Node<T> *node, Node<T> *newnode)
    {
        // if empty subtree
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

        node->height = max(height(node->left), height(node->right)) + 1;
        int nodebal = balance(node);
        //cout<<nodebal<<endl;

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
        if (nodebal < -1 && newnode->data <= node->right->data)
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    Node<T> *rightRotate(Node<T> *z)
    {
        Node<T> *y = z->left;
        Node<T> *yright = y->right;
        y->right = z;
        z->left = yright;
        z->height = max(height(z->left), height(z->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node<T> *leftRotate(Node<T> *z)
    {
        Node<T> *y = z->right;
        Node<T> *yleft = y->left;
        y->left = z;
        z->right = yleft;
        z->height = max(height(z->left), height(z->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;
        return y;
    }

    Node<T> *minNode(Node<T> *node)
    {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }

    Node<T> *deleteUtil(Node<T> *node, T &data)
    {
        if (node == nullptr)
            return nullptr;

        if (data < node->data)
        {
            node->left = deleteUtil(node->left, data);
        }
        else if (data > node->data)
        {
            node->right = deleteUtil(node->right, data);
        }
        else
        {
            if (node->left != nullptr && node->right != nullptr)
            {
                Node<T> *inordersuccessor = minNode(node->right);
                node->data = inordersuccessor->data;
                node->right = deleteUtil(node->right, inordersuccessor->data);
            }
            else if (node->left == nullptr && node->right == nullptr)
            {
                node = nullptr;
            }
            else
            {
                Node<T> *temp;
                if (node->left != nullptr)
                    temp = node->left;
                else
                    temp = node->right;

                node->data = temp->data;
                node->left = node->right = nullptr;
            }
        }

        if (node == nullptr)
            return nullptr;

        node->height = max(height(node->left), height(node->right)) + 1;
        int nodebal = balance(node);

        //left left
        if (nodebal > 1 && balance(node->left) >= 0)
        {
            return rightRotate(node);
        }

        //right right
        if (nodebal < -1 && balance(node->right) <= 0)
        {
            return leftRotate(node);
        }

        //left right
        if (nodebal > 1 && balance(node->left) < 0)
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        //right left
        if (nodebal < -1 && balance(node->right) > 0)
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

    void deleteNode(T data)
    {
        this->root = deleteUtil(this->root, data);
    }
};

int main()
{
    AVL<int> *a = new AVL<int>();
    a->insert(10);
    //a->inorder();
    a->insert(20);
    //a->inorder();
    a->insert(30);
    //a->inorder();
    a->insert(50);
    //a->inorder();
    a->insert(25);
    //a->inorder();
    a->insert(40);
    //a->insert(10);
    a->inorder();
    a->deleteNode(50);
    a->inorder();
}