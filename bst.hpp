#include<iostream>
#include<utility>

template<typename T>
class Node{
    public:
    Node* left;
    Node* right;
    T key;

    Node(T k)
    :left(nullptr),right(nullptr),key(k)
    {
    }
};

template<typename T>
class BST{
    private:
    Node<T>* root;
    int treeSize;

    void deleteRec(Node<T>*);
    Node<T>* remove(Node<T>*,T,bool&);
    Node<T>* minValNode(Node<T>*);
    void copy(Node<T>*&,Node<T>*);

    void _printInorder(Node<T>*);
    void _printPostorder(Node<T>*);
    void _printPreorder(Node<T>*);

    friend void swap(BST& first,BST& second)
    {
    using std::swap;

    swap(first.root, second.root);
    swap(first.treeSize,second.treeSize);
    second.root = nullptr;
    }

    public:

    BST();
    ~BST();

    BST(const BST&);
    BST& operator=(BST);
    BST(BST&&);
    BST& operator=(BST&&);

    //stdmove

    int size();


    T* minimum();
    T* maximum();

    T* insert(T);
    T* find(T);
    bool remove(T);

    void printInorder();
    void printPostorder();
    void printPreorder();

    Node<T>* getRoot() { return root;}
    //printowanie ...
};


template<typename T>
BST<T>::BST()
:treeSize(0),root(nullptr)
{
}

template<typename T>
BST<T>::~BST()
{
    std::cout<<"bst destr "<<this<<std::endl;
    deleteRec(root);

}

template<typename T>
void BST<T>::deleteRec(Node<T>* tmp)
{
    if(tmp){
    deleteRec(tmp->left);
    deleteRec(tmp->right);
    delete tmp;
    }
}

template<typename T>
int BST<T>::size() { return treeSize; }


template<typename T>
T* BST<T>::minimum()
{
    Node<T>* tmp=root;
    while(tmp->left != nullptr) tmp=tmp->left;
    return &tmp->key;
}

template<typename T>
T* BST<T>::maximum()
{
    Node<T>* tmp=root;
    while(tmp->right != nullptr) tmp=tmp->right;
    return &tmp->key;
}

template<typename T>
T* BST<T>::insert(T key)
{
    int tempDepth=1;
    Node<T>* toInsert=new Node<T>(key);
    Node<T>* temp=root;

    if(temp==nullptr){
        root=toInsert;
        treeSize=1;
        return &root->key;
    }

    while(true)
    {
        if(key < temp->key){
        if(temp->left==nullptr){
            temp->left = toInsert;
            break;
        }
        else{
            temp = temp->left;
        }
    }
    else{
        if(temp->right==nullptr){
            temp->right = toInsert;
            break;
        }
        else{
            temp = temp->right;
            }
        }
    }
    
    treeSize++;

    return &toInsert->key;
}

template<typename T>
T* BST<T>::find(T key)
{
    Node<T>* temp=root;
    while(temp!=nullptr){
        if(key == temp->key) return &temp->key;
        else if(key < temp->key ) temp=temp->left;
        else temp=temp->right;
    }
    return nullptr;
}

template<typename T>
bool BST<T>::remove(T key)
{
    bool erased;
    root=remove(root,key,erased);
    return erased;
}

template<typename T>
Node<T>* BST<T>::remove(Node<T>* temp, T key, bool& erased)
{
    if( temp == nullptr ) return nullptr;

    if( key < temp->key ) temp->left=remove(temp->left, key,erased);
    else if( key > temp->key ) temp->right=remove(temp->right, key,erased);
    else{
        //one child
        if(temp->left == nullptr){
            Node<T>* tmp=temp->right;
            delete temp;
            erased=true;
            treeSize--;
            return tmp;
        }
        else if(temp->right==nullptr){
            Node<T>* tmp=temp->left;
            erased=true;
            treeSize--;
            delete temp;
            return tmp;
        }
        //two children

        //get smallest in right subtree
        Node<T>* tmp=minValNode(temp->right);

        temp->key=tmp->key;
        temp->right=remove(temp->right,tmp->key,erased);
        erased=true;
    }
    return temp;
}

template<typename T>
Node<T>* BST<T>::minValNode(Node<T>* temp)
{
    Node<T>* curr=temp;
    while(curr->left != nullptr)
        curr=curr->left;

    return curr;
}


template<typename T>
BST<T>::BST(const BST& other)
:root(nullptr)
{
    std::cout<<"bst copy "<<this<<std::endl;
    if(other.root != nullptr) copy(root,other.root);
    treeSize=other.treeSize;
}

template<typename T>
void BST<T>::copy(Node<T>*& lhs, Node<T>* rhs)
{
    if(rhs == nullptr) lhs=nullptr;
    else{
        lhs=new Node<T>(rhs->key);
        copy(lhs->left,rhs->left);
        copy(lhs->right,rhs->right);
    }
}

template<typename T>
BST<T>& BST<T>::operator=(BST<T> rhs)
{
    std::cout<<"bst operator "<<this<<" "<<&rhs<<std::endl;
    swap(*this, rhs);
    return *this;
}

template<typename T>
BST<T>::BST(BST<T>&& rhs)
{
    swap(*this,rhs);
}

template<typename T>
BST<T>& BST<T>::operator=(BST<T>&& rhs)
{
    swap(*this,rhs);
    return *this;
}

template<typename T>
void BST<T>::printPostorder(){
    _printPostorder(root);
}

template<typename T>
void BST<T>::_printPostorder(Node<T>* temp){
    if(temp!=nullptr){
        _printPostorder(temp->left);
        _printPostorder(temp->right);
        std::cout<<temp->key<<" ";
    }
}

template<typename T>
void BST<T>::printPreorder(){
    _printPreorder(root);
}

template<typename T>
void BST<T>::_printPreorder(Node<T>* temp){
    if(temp!=nullptr){
        std::cout<<temp->key<<" ";
        _printPreorder(temp->left);
        _printPreorder(temp->right);
    }
}

template<typename T>
void BST<T>::printInorder() { _printInorder(root);}

template<typename T>
void BST<T>::_printInorder(Node<T>* temp)
{
    if(temp!=nullptr){
        _printInorder(temp->left);
        std::cout<<temp->key<<" ";
        _printInorder(temp->right);
    }
}