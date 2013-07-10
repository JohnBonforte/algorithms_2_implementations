#ifndef FIRST_TREE_H
#define FIRST_TREE_H

#include <iostream>
#include <queue>
#include <vector>
using std::cout;
using std::endl;

template <class TTT> class Node { public:    
    Node(const TTT &value):value(value), left(0), right(0) {}
    ~Node() { if(left) delete left; if(right) delete right; }
    TTT value;
    Node<TTT> *left;
    Node<TTT> *right;
};

template <class TTT>
class Tree {
public:
    Tree();
    ~Tree();
    void insert(const TTT &value);
    int size() const;
    bool contains(const TTT &value);    
    bool remove(const TTT &value);
    Node<TTT>* findNode(const TTT &value);
    Node<TTT>* findParent(const TTT &value);
    void show_level() const;
    std::vector<TTT> traversePreorder(); 
    std::vector<TTT> traversePostorder(); 
    std::vector<TTT> traverseInorder(); 
private:
    bool contains(Node<TTT>* current, const TTT &value);    
    void insertNode(Node<TTT>* current, const TTT &value);    
    void clearNode(Node<TTT>* current);
    std::vector<TTT> traversePreorder(Node<TTT>* root); 
    std::vector<TTT> traversePostorder(Node<TTT>* root); 
    std::vector<TTT> traverseInorder(Node<TTT>* root); 

    Node<TTT>* findParent(const TTT &value, Node<TTT>* root);
    Node<TTT>* findNode(Node<TTT>* root, const TTT &value);

    Node<TTT>* m_root;
    int count;
};

template <class TTT>
Tree<TTT>::Tree():m_root(0), count(0) { }

template <class TTT>
Tree<TTT>::~Tree() { 
    // recursively call the clears
    clearNode(m_root);
}

template <class TTT>
void Tree<TTT>::clearNode(Node<TTT>* current) {
    if(current) {
        // if(current->left) clearNode(current->left);
        // if(current->right) clearNode(current->right);
        delete current;
        current = 0;
    }
}

template <class TTT>
void Tree<TTT>::insert(const TTT &value) {
    // if there's no root element, this will be it
    if(m_root==0) { 
        m_root = new Node<TTT>(value);
        cout << "no head node so " << value << " inserted\n";
    }
    else {
       cout << "there's a head node, insertNode with " << value << endl;
       insertNode(m_root, value); 
    }
    count++;
}

template <class TTT>
int Tree<TTT>::size() const { return count; }

template <class TTT>
void Tree<TTT>::insertNode(Node<TTT>* current, const TTT &value) {
    if(value < current->value) {
        cout << value << " < " << current->value << " insert left" << endl;
       if(current->left) {
           cout << "there's already a node, insert Node\n";
           insertNode(current->left, value);  
       }     
       else {
           cout << "node empty so allocate " << value << endl;
           current->left = new Node<TTT>(value);
       }
    }
    else { // >=
        cout << value << " >= " << current->value << " insert right" << endl;
       if(current->right) {
           cout << "there's already a node, insert Node\n";
           insertNode(current->right, value);  
       }     
       else {
           cout << "node empty so allocate " << value << endl;
           current->right = new Node<TTT>(value);
       }
    }
}

template <class TTT>
bool Tree<TTT>::contains(const TTT &value) {
   return contains(m_root, value); 
}  

template <class TTT>
bool Tree<TTT>::contains(Node<TTT>* current, const TTT &value) {    
    // if there is no local root it clearly can't contain the value
    if(!current) return false; 
    // if the local root value satisfies the condition
    if(current->value == value) return true;    
    if(value < current->value) {
        return contains(current->left, value);
    } 
    // else >=
    return contains(current->right, value);
}

template <class TTT>
void Tree<TTT>::show_level() const {
    // int height = 0;
    std::queue<TTT> line;
    if(m_root)
    {
        line.push_back(m_root->value);
    }
}

template <class TTT>
bool Tree<TTT>::remove(const TTT &value) {
    Node<TTT>* nodeToRemove = findNode(value);
    // empty tree
    if(!nodeToRemove) { 
        cout << "there's no node to remove" << endl;
        return false;
    }
    // if this is the right value
    Node<TTT>* parent = findParent(value);
    if(count == 1) {
        cout << "just one node\n";
        m_root = 0;
    }  // remove only node
    else if(!nodeToRemove->left && !nodeToRemove->right) {
       // leaf node 
       cout << "leaf node\n";
       if(nodeToRemove->value < parent->value) {
            parent->left = 0;
       }
       else {
            parent->right = 0;
       }
       delete nodeToRemove;
    }
    else if(!nodeToRemove->left && nodeToRemove->right) {
        // there's a right node only
       cout << "there's a right node only \n";
       if(nodeToRemove->value < parent->value) {
            parent->left = nodeToRemove->right;
       }
       else {
            parent->right = nodeToRemove->right;
       }
       delete nodeToRemove;
    }
    else if(nodeToRemove->left && !nodeToRemove->right) {
        // there's a left node only
       cout << "there's a left node only \n";
       if(nodeToRemove->value < parent->value) {
            parent->left = nodeToRemove->left;
       }
       else {
            parent->right = nodeToRemove->left;
       }
       delete nodeToRemove;
    }
    else {
        // there's both left and right nodes
        cout << " there's both left and right nodes" << endl;
        Node<TTT>* largestValue = nodeToRemove->left;
        // search for the utmost right value
        // because, by definition that's the highest
        while(largestValue->right) {
            largestValue = largestValue->right;
        }
        Node<TTT>* parentToLargest = findParent(largestValue->value);
        cout << "replace with largestValue " << largestValue->value << endl;
        nodeToRemove->value = largestValue->value;
        // Ugly fix
        if(parentToLargest==nodeToRemove) {
            delete largestValue;
            nodeToRemove->left = 0;
        } 
        else {
            delete parentToLargest->right;
            parentToLargest->right = 0;
        }
        // delete parentToLargest->right;
        // parentToLargest->right = 0;
    }
    count--;
    return true;

    // if(value == nodeToRemove->value) {
    //     // no children (leaf)
    //     if(!nodeToRemove->left && !nodeToRemove->right)  {
    //         delete nodeToRemove;
    //         nodeToRemove = 0;
    //     }
    //     else {
    //         
    //     }
    //     return true;
    // }
}

template <class TTT>
Node<TTT>* Tree<TTT>::findNode(const TTT &value){
    return findNode(m_root, value);
}
template <class TTT>
Node<TTT>* Tree<TTT>::findNode(Node<TTT>* root, const TTT &value){
    if(!root) return 0;
    if(value == root->value) return root;
    if(value < root->value) return findNode(root->left, value);  
    else return findNode(root->right, value);
}
template <class TTT>
Node<TTT>* Tree<TTT>::findParent(const TTT &value){
    return findParent(value, m_root);
}
template <class TTT>
Node<TTT>* Tree<TTT>::findParent(const TTT &value, Node<TTT>* root){
    // there can't be a parent node if it's just one node
    if(value == root->value) return 0; 
    if(value < root->value) {
        if(!root->left) return 0;
        if(value == root->left->value) return root;
        return findParent(value, root->left);
    }
    else {
        if(!root->right) return 0;
        if(value == root->right->value) return root;
        return findParent(value, root->right);
    }
}

// template <class TTT>
template <class TTT>
std::vector<TTT> Tree<TTT>::traversePreorder(){ 
    return traversePreorder(m_root);
}
template <class TTT>
std::vector<TTT> Tree<TTT>::traversePostorder(){ 
    return traversePostorder(m_root);
}
template <class TTT>
std::vector<TTT> Tree<TTT>::traverseInorder(){ 
    return traverseInorder(m_root);
}

template <class TTT>
std::vector<TTT> Tree<TTT>::traversePreorder(Node<TTT>* root){
    std::vector<TTT> result;
    if(root) {
        // root
        result.push_back(root->value);

        // left
        auto temp = traversePreorder(root->left);
        result.insert(result.end(), temp.begin(), temp.end());

        // right
        temp = traversePreorder(root->right);
        result.insert(result.end(), temp.begin(), temp.end());
    }
    return result;
} 
template <class TTT>
std::vector<TTT> Tree<TTT>::traversePostorder(Node<TTT>* root){
    std::vector<TTT> result;
    if(root) {
        // left
        auto left = traversePostorder(root->left);
        result.insert(result.end(), left.begin(), left.end());

        // right
        auto right = traversePostorder(root->right);
        result.insert(result.end(), right.begin(), right.end());

        // root
        result.push_back(root->value);
        cout << "post order " << root->value << endl;
    }
    return result;
} 
template <class TTT>
std::vector<TTT> Tree<TTT>::traverseInorder(Node<TTT>* root){
    std::vector<TTT> result;
    if(root) {

        // left
        auto temp = traverseInorder(root->left);
        result.insert(result.end(), temp.begin(), temp.end());

        // root
        result.push_back(root->value);

        // right
        temp = traverseInorder(root->right);
        result.insert(result.end(), temp.begin(), temp.end());

    }
    return result;
} 
#endif
