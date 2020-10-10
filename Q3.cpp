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

int abs(int a)
{
    if (a < 0)
        return -a;
    return a;
}

class IntegerComp
{
public:
    bool operator()(long long int a, long long int b)
    {
        if (a < b)
            return true;
        return false;
    }
};

class StringComp
{
public:
    bool operator()(string &a, string &b)
    {
        if (a < b)
            return true;
        return false;
    }
};

class CharComp
{
public:
    bool operator()(char a, char b)
    {
        if (a < b)
            return true;
        return false;
    }
};

template <class K, class V>
class Node
{
private:
public:
    K key;
    V value;
    Node<K, V> *left;
    Node<K, V> *right;
    int height;
    Node(K key, V value)
    {
        this->key = key;
        this->value = value;
        this->left = this->right = nullptr;
        this->height = 1;
    }
    Node(K key)
    {
        this->key = key;
        this->left = this->right = nullptr;
        this->height = 1;
    }
};

template <class K, class V, class Comparator>
class OrderedMap
{
private:
    //height ok
    int height(Node<K, V> *node)
    {
        if (node == nullptr)
            return 0;
        return node->height;
    }
    //balance ok
    int balance(Node<K, V> *node)
    {
        if (node == nullptr)
            return 0;
        return height(node->left) - height(node->right);
    }

    //insertutil ok
    Node<K, V> *insertUtil(Node<K, V> *node, Node<K, V> *newnode, bool &inserted)
    {
        // if empty subtree
        if (node == nullptr)
        {
            return newnode;
        }

        if (cmp(newnode->key, node->key))
        {
            node->left = insertUtil(node->left, newnode, inserted);
        }
        else if (cmp(node->key, newnode->key))
        {
            node->right = insertUtil(node->right, newnode, inserted);
        }
        else if (!cmp(newnode->key, node->key) && !cmp(node->key, newnode->key))
        {
            node->value = newnode->value;
            inserted = false;
        }

        node->height = max(height(node->left), height(node->right)) + 1;
        int nodebal = balance(node);

        //left left
        if (nodebal > 1 &&
            (cmp(newnode->key, node->left->key) ||
             (!cmp(newnode->key, node->left->key) && !cmp(node->left->key, newnode->key))))
        {
            return rightRotate(node);
        }

        //right right
        if (nodebal < -1 && cmp(node->right->key, newnode->key))
        {
            return leftRotate(node);
        }

        //left right
        if (nodebal > 1 && cmp(node->left->key, newnode->key))
        {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        //right left
        if (nodebal < -1 &&
            (cmp(newnode->key, node->right->key) ||
             (!cmp(newnode->key, node->right->key) && !cmp(node->right->key, newnode->key))))
        {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }
    //rightrotate ok
    Node<K, V> *rightRotate(Node<K, V> *t2)
    {
        Node<K, V> *t1 = t2->left;
        Node<K, V> *t3 = t1->right;
        t1->right = t2;
        t2->left = t3;
        t2->height = max(height(t2->left), height(t2->right)) + 1;
        t1->height = max(height(t1->left), height(t1->right)) + 1;
        return t1;
    }
    //leftrotate ok
    Node<K, V> *leftRotate(Node<K, V> *t2)
    {
        Node<K, V> *t1 = t2->right;
        Node<K, V> *t3 = t1->left;
        t1->left = t2;
        t2->right = t3;
        t2->height = max(height(t2->left), height(t2->right)) + 1;
        t1->height = max(height(t1->left), height(t1->right)) + 1;
        return t1;
    }
    //minnode ok
    Node<K, V> *minNode(Node<K, V> *node)
    {
        while (node->left != nullptr)
            node = node->left;
        return node;
    }
    //deleteutil ok
    Node<K, V> *deleteUtil(Node<K, V> *node, K &key, bool &deleted)
    {
        if (node == nullptr)
            return nullptr;

        if (cmp(key, node->key))
        {
            node->left = deleteUtil(node->left, key, deleted);
        }
        else if (cmp(node->key, key))
        {
            node->right = deleteUtil(node->right, key, deleted);
        }
        else
        {
            deleted = true;
            if (node->left != nullptr && node->right != nullptr)
            {
                Node<K, V> *inordersuccessor = minNode(node->right);
                node->key = inordersuccessor->key;
                node->right = deleteUtil(node->right, inordersuccessor->key, deleted);
            }
            else if (node->left == nullptr && node->right == nullptr)
            {
                node = nullptr;
            }
            else
            {
                Node<K, V> *temp;
                if (node->left != nullptr)
                    temp = node->left;
                else
                    temp = node->right;

                node->key = temp->key;
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

    void postOrderDel(Node<K, V> *node)
    {
        if (node != nullptr)
        {
            postOrderDel(node->left);
            postOrderDel(node->right);
            delete node->left;
            delete node->right;
        }
    }

public:
    Node<K, V> *root;
    int numNodes;
    Comparator cmp;
    OrderedMap()
    {
        this->root = nullptr;
        this->numNodes = 0;
    }

    void insert(K key, V value)
    {
        bool inserted = true;
        Node<K, V> *newnode = new Node<K, V>(key, value);
        this->root = this->insertUtil(this->root, newnode, inserted);
        if (inserted)
        {
            this->numNodes++;
        }
    }

    void erase(K key)
    {
        bool deleted = false;
        this->root = deleteUtil(this->root, key, deleted);
        if (deleted)
        {
            this->numNodes--;
        }
    }

    bool find(K key)
    {
        Node<K, V> *cur = this->root;
        while (cur != nullptr)
        {
            if (cmp(cur->key, key))
                cur = cur->right;
            else if (cmp(key, cur->key))
                cur = cur->left;
            else
                return true;
        }
        return false;
    }

    int size()
    {
        return this->numNodes;
    }

    void clear()
    {
        postOrderDel(this->root);
        delete this->root;
        this->numNodes = 0;
    }

    V &operator[](K key)
    {
        Node<K, V> *cur = this->root;
        while (cur != nullptr)
        {
            if (cmp(cur->key, key))
                cur = cur->right;
            else if (cmp(key, cur->key))
                cur = cur->left;
            else
                return cur->value;
        }
        bool inserted = true;
        Node<K, V> *newnode = new Node<K, V>(key);
        this->insertUtil(this->root, newnode, inserted);
        if (inserted)
        {
            this->numNodes++;
        }
        return newnode->value;
    }

    void inorder()
    {
        inorderUtil(this->root);
        cout << endl;
    }

    void inorderUtil(Node<K, V> *node)
    {
        if (node != nullptr)
        {
            inorderUtil(node->left);
            cout << node->key << " ";
            inorderUtil(node->right);
        }
    }
};

int main()
{
    OrderedMap<int, int, IntegerComp> m;
    m.insert(3, 5);
    m.insert(4, 20);
    m.inorder();
    cout << m.size() << endl;
    m[5] = 10;
    //m.erase(3);
    m.inorder();
    cout << m.size() << endl;
    cout << m.find(3) << endl;
    cout << m.find(4) << endl;
    cout<<m[4]<<endl;
    m.inorder();
    m.clear();
    cout << m.size() << endl;
}