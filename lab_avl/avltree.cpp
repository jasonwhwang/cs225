/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
int AVLTree<K, V>::getHeight(Node* node)
{
    if(node == NULL) {
        return -1;
    }
    //return 1 + std::max(getHeight(node->left), getHeight(node->right));
    return node->height;
}

template <class K, class V>
int AVLTree<K,V>::getBalance(Node* node)
{
    if(node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    *_out << __func__ << endl;
    if(t->right == NULL) { return; }
    Node* tRightCpy = t->right;
    t->right = tRightCpy->right;
    tRightCpy->left = t;
    t->height = max(getHeight(t->left), getHeight(t->right)) +1;
    tRightCpy->height = max(getHeight(tRightCpy->left), getHeight(tRightCpy->right)) +1;
    t = tRightCpy;
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    *_out << __func__ << endl; 
    if(t->left == NULL) { return; }
    Node* tLeftCpy = t->left;
    t->left = tLeftCpy->left;
    tLeftCpy->right = t;
    t->height = max(getHeight(t->left), getHeight(t->right)) +1;
    tLeftCpy->height = max(getHeight(tLeftCpy->left), getHeight(tLeftCpy->right)) +1;
    t = tLeftCpy;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    *_out << __func__ << endl;
 
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    *_out << __func__ << endl;
 
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    int balance = getBalance(subtree);
    if(balance<-1 && subtree->key > subtree->right->key) {
        rotateLeft(subtree);
    } else if(balance<-1 && subtree->key < subtree->right->key) {
        rotateRightLeft(subtree);
    } else if(balance>1 && subtree->key < subtree->left->key) {
        rotateRight(subtree);
    } else if(balance>1 && subtree->key > subtree->left->key) {
        rotateLeftRight(subtree);
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    if(root == NULL) {
        root = new Node(key, value);
        root->height = 0;
        return;
    }

    if(subtree->key > key) {
        if(subtree->left == NULL) {
            subtree->left = new Node(key,value);
        } else {
            insert(subtree->left,key,value);
        }
    }

    if(subtree->key < key) {
        if(subtree->right == NULL) {
            subtree->right = new Node(key,value);
        } else {
            insert(subtree->right,key,value);
        }
    }

    subtree->height = getHeight(subtree);
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        remove(subtree->left,key);
    } else if (key > subtree->key) {
        remove(subtree->right,key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            delete(subtree);
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            
        } else {
            /* one-child remove */
            if(subtree->left != NULL) {
                
            }
        }
        // your code here
    }
}
