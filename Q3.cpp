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
    Node<K, V> *insertUtil(Node<K, V> *node, Node<K, V> *newnode, bool &inserted)
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
            //node->left = insertUtil(node->left, newnode);
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
        Node<T> *t1 = t2->left;
        Node<T> *t3 = t1->right;
        t1->right = t2;
        t2->left = t3;
        t2->height = max(height(t2->left), height(t2->right)) + 1;
        t1->height = max(height(t1->left), height(t1->right)) + 1;
        return t1;
    }
    //leftrotate ok
    Node<K, V> *leftRotate(Node<K, V> *t2)
    {
        Node<T> *t1 = t2->right;
        Node<T> *t3 = t1->left;
        t1->left = t2;
        t2->right = t3;
        t2->height = max(height(t2->left), height(t2->right)) + 1;
        t1->height = max(height(t1->left), height(t1->right)) + 1;
        return t1;
    }
    //minnode doubtful
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
    //inorderForOcc doubtful
    void inorderForOcc(Node<K, V> *node, int &count, K &key)
    {
        if (node != nullptr)
        {
            inorderForOcc(node->left, count, key);
            if (node->key == key)
            {
                count++;
            }
            inorderForOcc(node->right, count, key);
        }
    }
    //findle doubtful
    Node<K, V> *findle(K key)
    {
        Node<T> *cur = this->root;
        Node<T> *cur2 = this->root;
        Node<T> *prevcandidate = cur;
        while (cur2 != nullptr)
        {
            if (cur2->key == key)
            {
                return cur2;
            }
            else if (cmp(cur2->key, key))
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
            if (cur->key == key)
            {
                return cur;
            }
            else if (cmp(cur->key, key))
            {
                prevcandidate = cur;
                if (cur->right != nullptr)
                {
                    if (cmp(key, cur->right->key))
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
                if (cur->left == nullptr)
                {
                    return prevcandidate;
                }
                else
                {
                    if (cmp(cur->left->key, key))
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
    //revInorder doubtful
    void revInorder(Node<K, V> *node, int &count, int k, Node<K, V> **kth)
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
    //countrange doubtful
    void countRange(Node<K, V> *node, int &count, K &lkey, K &ukey)
    {
        if (node != nullptr)
        {
            if ((cmp(lkey, node->key) || (!cmp(lkey, node->key) && !cmp(node->key, lkey))) &&
                (cmp(node->key, ukey) || (!cmp(node->key, ukey) && !cmp(ukey, node->key))))
            {
                count++;
                countRange(node->left, count, lkey, ukey);
                countRange(node->right, count, lkey, ukey);
            }
            else if (cmp(node->key, lkey))
            {
                countRange(node->right, count, lkey, ukey);
            }
            else if (cmp(ukey, node->key))
            {
                countRange(node->left, count, lkey, ukey);
            }
        }
    }

public:
    Node<K, V> *root;
    int numNodes;
    Comparator cmp;
    AVL()
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

    void inorder()
    {
        inorderUtil(this->root);
        cout << endl;
    }

    void deleteNode(K key)
    {
        bool deleted = false;
        this->root = deleteUtil(this->root, data, deleted);
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
            else if (cmp(key < cur->key))
                cur = cur->left;
            else
                return true;
        }
        return false;
    }

    int countOccurence(K key)
    {
        int count = 0;
        Node<K, V> *cur = this->root;
        while (cur != nullptr)
        {
            if (cmp(cur->key, key))
                cur = cur->right;
            else if (cmp(key < cur->key))
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

    int size()
    {
        return this->numNodes;
    }

    void postOrderDel(Node<K,V>* node)
    {
        if(node!=nullptr)
        {
            postOrderDel(node->left);
            postOrderDel(node->right);
            delete this->left;
            delete this->right;
        }
    }

    void clear()
    {
        postOrderDel(this->root);
        delete this->root;
    }
};

int main()
{
    
}