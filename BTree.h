#ifndef PROJECT_BTREE_H
#define PROJECT_BTREE_H
#include <iostream>
using namespace std;
class Node;
class BTreeNode {
public:
    Node *keys;
    int t,n;
    BTreeNode **nextPtr;
    bool leaf;
    BTreeNode(int temp, bool boolLeaf);
    void insertNonFull(Node k);
    void splitChild(int i, BTreeNode *y);
    int findKey(Node k);
    void remove(Node k);
    void removeFromLeaf(int idx);
    void removeFromNonLeaf(int idx);
    Node getPred(int idx);
    Node getSucc(int idx);
    void fill(int idx);
    void borrowFromPrev(int idx);
    void borrowFromNext(int idx);
    void merge(int idx);
    friend class BTree;
};
class Node{
public:
    int data;
    Node* nextField;
    BTreeNode* self;
};
class BTree {
public:
    BTreeNode *root;
    int t;
    string name;
    string type;
    BTree() {
        int temp = 3;
        root = NULL;
        t = temp;
    }
    void insert(Node k);
    void remove(Node k);
};
BTreeNode::BTreeNode(int t1, bool leaf1) {
    this->t = t1;
    this->leaf = leaf1;
    this->keys = new Node[2 * t - 1];
    this->nextPtr = new BTreeNode *[2 * t];
    this->n = 0;
}
void BTree::insert(Node k) {
    if (root == NULL) {
        root = new BTreeNode(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else {
        if (root->n == 2 * t - 1) {
            BTreeNode *s = new BTreeNode(t, false);
            s->nextPtr[0] = root;
            s->splitChild(0, root);
            int i = 0;
            if (s->keys[0].data < k.data)
                i++;
            s->nextPtr[i]->insertNonFull(k);
            root = s;
        } else
            root->insertNonFull(k);
    }
}
void BTreeNode::insertNonFull(Node k) {
    int i = n - 1;
    if (leaf == true) {
        while (i >= 0 && keys[i].data > k.data) {
            keys[i + 1].data = keys[i].data;
            keys[i + 1].nextField = keys[i].nextField;
            i--;
        }
        keys[i + 1].data = k.data;
        keys[i + 1].nextField = k.nextField;
        n = n + 1;
    } else {
        while (i >= 0 && keys[i].data > k.data)
            i--;
        if (nextPtr[i + 1]->n == 2 * t - 1) {
            splitChild(i + 1, nextPtr[i + 1]);
            if (keys[i + 1].data < k.data)
                i++;
        }
        nextPtr[i + 1]->insertNonFull(k);
    }
}
void BTreeNode::splitChild(int i, BTreeNode *y) {
    BTreeNode *z = new BTreeNode(y->t, y->leaf);
    z->n = t - 1;
    for (int j = 0; j < t - 1; j++) {
        z->keys[j].data = y->keys[j + t].data;
        z->keys[j].nextField = y->keys[j + t].nextField;
    }
    if (y->leaf == false) {
        for (int j = 0; j < t; j++)
            z->nextPtr[j] = y->nextPtr[j + t];
    }
    y->n = t - 1;
    for (int j = n; j >= i + 1; j--)
        nextPtr[j + 1] = nextPtr[j];
    nextPtr[i + 1] = z;
    for (int j = n - 1; j >= i; j--) {
        keys[j + 1].data = keys[j].data;
        keys[j + 1].nextField = keys[j].nextField;
    }
    keys[i].data = y->keys[t - 1].data;
    keys[i].nextField = y->keys[t - 1].nextField;
    n = n + 1;
}
int BTreeNode::findKey(Node k){
    int idx=0;
    while (idx<n && keys[idx].data < k.data)
        idx++;
    return idx;
}
void BTreeNode::remove(Node k){
    int idx = findKey(k);
    int idx2 = idx;
    if (idx < n && keys[idx].data == k.data){
        int flagG = 0;
        while(idx2 < n && keys[idx2].data == k.data) {
            if (keys[idx2].nextField == k.nextField) {
                if (leaf)
                    removeFromLeaf(idx2);
                else
                    removeFromNonLeaf(idx2);
                flagG = 1;
                break;
            }
            idx2++;
        }
        if(flagG == 0){
            idx2 = idx;
            if (leaf)
                return;
            bool flag = ( (idx2==n)? true : false );
            if (nextPtr[idx2]->n < t)
                fill(idx2);
            if (flag && idx2 > n)
                nextPtr[idx2-1]->remove(k);
            else
                nextPtr[idx2]->remove(k);
        }
    }else{
        if (leaf)
            return;

        bool flag;
        if(idx == n)
            flag = true;
        else
            flag = false;
        if (this->nextPtr[idx]->n < t)
            fill(idx);

        if (flag == true && idx > n)
            nextPtr[idx-1]->remove(k);
        else
            nextPtr[idx]->remove(k);
    }
    return;
}
void BTreeNode::removeFromLeaf (int idx){

    for (int i=idx+1; i < this->n; ++i)
        this->keys[i - 1] = this->keys[i];
    this->n -= 1;
    return;
}
void BTreeNode::removeFromNonLeaf(int idx){
    Node k = keys[idx];
    if (nextPtr[idx]->n >= t){
        Node pred = getPred(idx);
        keys[idx] = pred;
        nextPtr[idx]->remove(pred);
    }else if  (nextPtr[idx+1]->n >= t){
        Node succ = getSucc(idx);
        keys[idx] = succ;
        nextPtr[idx+1]->remove(succ);
    }else{
        merge(idx);
        nextPtr[idx]->remove(k);
    }
    return;
}
Node BTreeNode::getPred(int idx){
    BTreeNode *cur = this->nextPtr[idx];
    while (!cur->leaf)
        cur = cur->nextPtr[cur->n];
    return cur->keys[cur->n-1];
}
Node BTreeNode::getSucc(int idx){
    BTreeNode *cur = this->nextPtr[idx+1];
    while (!cur->leaf)
        cur = cur->nextPtr[0];
    return cur->keys[0];
}
void BTreeNode::fill(int idx){
    if (idx!=0 && this->nextPtr[idx-1]->n>= this->t)
        borrowFromPrev(idx);
    else if (idx != this->n && this->nextPtr[idx+1]->n >= this->t)
        borrowFromNext(idx);
    else{
        if (idx != this->n)
            merge(idx);
        else
            merge(idx-1);
    }
    return;
}
void BTreeNode::borrowFromPrev(int idx){
    BTreeNode *child = this->nextPtr[idx];
    BTreeNode *sibling = this->nextPtr[idx-1];
    for (int i=child->n-1; i>=0; --i)
        child->keys[i + 1] = child->keys[i];
    if (!child->leaf){
        for(int i=child->n; i>=0; --i)
            child->nextPtr[i+1] = child->nextPtr[i];
    }
    child->keys[0] = keys[idx-1];
    if(!child->leaf)
        child->nextPtr[0] = sibling->nextPtr[sibling->n];
    keys[idx-1] = sibling->keys[sibling->n-1];
    child->n += 1;
    sibling->n -= 1;
    return;
}
void BTreeNode::borrowFromNext(int idx){
    BTreeNode *child = this->nextPtr[idx];
    BTreeNode *sibling = this->nextPtr[idx+1];
    child->keys[(child->n)] = keys[idx];
    if (!(child->leaf))
        child->nextPtr[(child->n)+1] = sibling->nextPtr[0];
    this->keys[idx] = sibling->keys[0];
    for (int i=1; i<sibling->n; ++i) {
        sibling->keys[i - 1] = sibling->keys[i];
    }
    if (!sibling->leaf){
        for(int i=1; i<=sibling->n; ++i)
            sibling->nextPtr[i-1] = sibling->nextPtr[i];
    }
    child->n += 1;
    sibling->n -= 1;
    return;
}
void BTreeNode::merge(int idx){
    BTreeNode *child = this->nextPtr[idx];
    BTreeNode *sibling = this->nextPtr[idx+1];
    child->keys[t-1] = this->keys[idx];
    for (int i=0; i<sibling->n; ++i)
        child->keys[i + t] = sibling->keys[i];
    if (!child->leaf){
        for(int i=0; i<=sibling->n; ++i)
            child->nextPtr[i+t] = sibling->nextPtr[i];
    }

    for (int i=idx+1; i<n; ++i)
        this->keys[i - 1] = this->keys[i];
    for (int i=idx+2; i<=n; ++i)
        nextPtr[i-1] = nextPtr[i];
    child->n += sibling->n+1;
    this->n -= 1;
    delete(sibling);
    return;
}
void BTree::remove(Node k){
    if (!root)
        return;
    root->remove(k);
    if (this->root->n == 0){
        BTreeNode *tmp = root;
        if (root->leaf)
            root = NULL;
        else
            this->root = this->root->nextPtr[0];
        delete tmp;
    }
    return;
}
#endif //PROJECT_BTREE_H