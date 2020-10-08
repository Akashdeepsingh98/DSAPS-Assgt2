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
    //inorderutil doubtful
    void inorderUtil(Node<K, V> *node)
    {
        if (node != nullptr)
        {
            inorderUtil(node->left);
            cout << node->value << " ";
            inorderUtil(node->right);
        }
    }
    //insertutil ok
    Node<K, V> *insertUtil(Node<K, V> *node, Node<K, V> *newnode)
    {
        // if empty subtree
        if (node == nullptr)
        {
            return newnode;
        }

        if (cmp(newnode->key, node->key))
        {
            node->left = insertUtil(node->left, newnode);
        }
        else if (cmp(node->key, newnode->key))
        {
            node->right = insertUtil(node->right, newnode);
        }
        else if (!cmp(newnode->key, node->key) && !cmp(node->key, newnode->key))
        {
            node->left = insertUtil(node->left, newnode);
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
    Node<K,V> *rightRotate(Node<K,V> *t2)
    {
        Node<T> *t1 = t2->left;
        Node<T> *t3 = t1->right;
        t1->right = t2;
        t2->left = t3;
        t2->height = max(height(t2->left), height(t2->right)) + 1;
        t1->height = max(height(t1->left), height(t1->right)) + 1;
        return t1;
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

        if (cmp(data, node->data))
        {
            node->left = deleteUtil(node->left, data);
        }
        else if (cmp(node->data, data))
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

    void inorderForOcc(Node<T> *node, int &count, T &data)
    {
        if (node != nullptr)
        {
            inorderForOcc(node->left, count, data);
            if (node->data == data)
            {
                count++;
            }
            inorderForOcc(node->right, count, data);
        }
    }

    Node<T> *findle(T data)
    {
        Node<T> *cur = this->root;
        Node<T> *cur2 = this->root;
        Node<T> *prevcandidate = cur;
        while (cur2 != nullptr)
        {
            if (cur2->data == data)
            {
                return cur2;
            }
            else if (cmp(cur2->data, data))
            {
                prevcandidate = cur2;
                cur = cur2;
                break;
            }
            cur2 = cur2->left;
        }

        if (cur2 == nullptr)
            return nullptr;

        while (true)
        {
            if (cur->data == data)
            {
                return cur;
            }
            else if (cmp(cur->data, data))
            {
                prevcandidate = cur;
                if (cur->right != nullptr)
                {
                    if (cmp(data, cur->right->data))
                    {
                        if (cur->right->left == nullptr)
                        {
                            return prevcandidate;
                        }
                        else
                        {
                            cur = cur->right;
                        }
                    }
                    else
                    {
                        cur = cur->right;
                    }
                }
                else
                {
                    return prevcandidate;
                }
            }
            else
            {
                // data < cur->data
                if (cur->left == nullptr)
                {
                    return prevcandidate;
                }
                else
                {
                    if (cmp(cur->left->data, data))
                    {
                        prevcandidate = cur->left;
                        if (cur->left->right == nullptr)
                        {
                            return cur->left;
                        }
                        else
                        {
                            cur = cur->left;
                        }
                    }
                    else
                    {
                        cur = cur->left;
                    }
                }
            }
        }
    }

    void revInorder(Node<T> *node, int &count, int k, Node<T> **kth)
    {
        if (node != nullptr)
        {
            revInorder(node->right, count, k, kth);
            count++;
            if (count == k)
            {
                if (*kth == nullptr)
                    *kth = node;
                return;
            }
            revInorder(node->left, count, k, kth);
        }
    }

    void countRange(Node<T> *node, int &count, T &ldata, T &udata)
    {
        if (node != nullptr)
        {
            if ((cmp(ldata, node->data) || (!cmp(ldata, node->data) && !cmp(node->data, ldata))) && (cmp(node->data, udata) || (!cmp(node->data, udata) && !cmp(udata, node.data))))
            {
                count++;
                countRange(node->left, count, ldata, udata);
                countRange(node->right, count, ldata, udata);
            }
            else if (cmp(node->data, ldata))
            {
                countRange(node->right, count, ldata, udata);
            }
            else if (cmp(udata, node->data))
            {
                countRange(node->left, count, ldata, udata);
            }
        }
    }

public:
    Node<T> *root;
    Comparator cmp;
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

    bool search(T data)
    {
        Node<T> *cur = this->root;
        while (cur != nullptr)
        {
            if (cmp(cur->data, data))
                cur = cur->right;
            else if (cmp(data < cur->data))
                cur = cur->left;
            else
                return true;
        }
        return false;
    }

    int countOccurence(T data)
    {
        int count = 0;
        Node<T> *cur = this->root;
        while (cur != nullptr)
        {
            if (cmp(cur->data, data))
                cur = cur->right;
            else if (cmp(data < cur->data))
                cur = cur->left;
            else
            {
                inorderForOcc(cur, count, data);
                break;
            }
        }
        return count;
    }

    Node<T> *lowerBound(T data)
    {
        Node<T> *cur = this->root;
        Node<T> *prevcandidate = cur;
        Node<T> *cur2 = this->root;
        while (cur2 != nullptr)
        {
            if (!cmp(cur2->data, data) && !cmp(data, cur2->data))
            {
                return cur2;
            }
            else if (cmp(data, cur2->data))
            {
                prevcandidate = cur2;
                cur = cur2;
                break;
            }
            cur2 = cur2->right;
        }
        if (cur2 == nullptr)
        {
            return nullptr;
        }

        while (true)
        {
            if (!cmp(cur->data, data) && !cmp(data, cur->data))
            {
                return cur;
            }
            else if (cmp(data, cur->data))
            {
                prevcandidate = cur;
                if (cur->left != nullptr)
                {
                    if (cmp(cur->left->data, data))
                    {
                        if (cur->left->right == nullptr)
                        {
                            return prevcandidate;
                        }
                        else
                        {
                            cur = cur->left;
                        }
                    }
                    else
                    {
                        cur = cur->left;
                    }
                }
                else
                {
                    return prevcandidate;
                }
            }
            else
            {
                if (cur->right != nullptr)
                {
                    if (cmp(data, cur->right->data))
                    {
                        prevcandidate = cur->right;
                        if (cur->right->left == nullptr)
                        {
                            return cur->right;
                        }
                        else
                        {
                            cur = cur->right;
                        }
                    }
                    else
                    {
                        cur = cur->right;
                    }
                }
                else
                {
                    return prevcandidate;
                }
            }
        }
        return nullptr;
    }

    Node<T> *upperBound(T data)
    {
        Node<T> *cur = this->root;
        Node<T> *prevcandidate = cur;
        Node<T> *cur2 = this->root;
        while (cur2 != nullptr)
        {
            if (cmp(data, cur2->data))
            {
                prevcandidate = cur2;
                cur = cur2;
                break;
            }
            cur2 = cur2->right;
        }
        if (cur2 == nullptr)
        {
            return nullptr;
        }

        while (true)
        {
            if (!cmp(cur->data, data) && !cmp(data, cur->data))
            {
                if (cur->right == nullptr)
                {
                    return prevcandidate;
                }
                else
                {
                    cur = cur->right;
                }
            }
            else if (cmp(data, cur->data))
            {
                prevcandidate = cur;
                if (cur->left == nullptr)
                {
                    return prevcandidate;
                }
                else
                {
                    cur = cur->left;
                }
            }
            else
            {
                if (cur->right == nullptr)
                {
                    return prevcandidate;
                }
                else
                {
                    cur = cur->right;
                }
            }
        }
    }

    Node<T> *closestElement(T data)
    {
        Node<T> *ge = lowerBound(data);
        Node<T> *le = findle(data);
        if (ge == nullptr)
            return le;
        if (le == nullptr)
            return ge;
        if (!cmp(le->data, data) && !cmp(data, le->data))
            return ge;
        if (!cmp(ge->data, data) && !cmp(data, ge->data))
            return le;
        if (abs(le->data - data) <= abs(ge->data - data))
            return le;
        return ge;
    }

    Node<T> *kthlargest(int k)
    {
        Node<T> *kth = nullptr;
        int count = 0;
        revInorder(this->root, count, k, &kth);
        return kth;
    }

    int countInRange(T ldata, T udata)
    {
        int count = 0;
        countRange(this->root, count, ldata, udata);
        return count;
    }
};

int main()
{
}