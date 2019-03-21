#include"bst.hpp"
#include<stack>

template<typename T>
class Set{
    private:
    BST<T> tree;

    class Iterator{
        private:
        std::stack<Node<T>*> nodes;

        public:
        Node<T>* curr;
        Iterator(Node<T>*);
        Iterator()
        :curr(nullptr)
        {}

        Iterator& operator++();
        bool operator!=(const Iterator& rhs) { return this->curr!=rhs.curr;  }
        T& operator*() { return curr->key;}

    };

    public:

    Set() = default;
    ~Set() = default;
    Set(const Set&) = default;
    Set(Set&&);

    Set& operator=(Set& rhs) = default;
    Set& operator=(Set&&);

    T* insert(T);
    T* find(T);
    bool remove(T);

    int size();
    T* minimum();
    T* maximum();

    Iterator begin();
    Iterator end();
};


// template<typename T>
// Set<T>::Set(const Set<T>& rhs)
// {
//     std::cout<<"Copy"<<std::endl;
//     BST<T> tr=rhs.tree;
//     //tree=tr;
// }

template<typename T>
Set<T>::Set(Set&& rhs)
{
    tree=std::move(rhs.tree);
}

// template<typename T>
// Set<T>& Set<T>::operator=(Set rhs)
// {
//     std::cout<<"operator"<<std::endl;
//     swap(this->tree,rhs.tree);
//     return *this;
// }

template<typename T>
T* Set<T>::insert(T key)
{
    T* found=tree.find(key);
    if(found == nullptr) return tree.insert(key);
    else return found; 
}

template<typename T>
T* Set<T>::find(T key)
{
    return tree.find(key);
}

template<typename T>
bool Set<T>::remove(T key)
{
    return tree.remove(key);
}

template<typename T>
int Set<T>::size()
{
    return tree.size();
}


template<typename T>
typename Set<T>::Iterator Set<T>::begin()
{
    return ++Iterator(tree.getRoot());
    //return ++Iterator(tree.getRoot());
}

template<typename T>
typename Set<T>::Iterator Set<T>::end()
{
    Iterator end;
    end.curr=nullptr;
    return end;
}

template<typename T>
Set<T>::Iterator::Iterator(Node<T>* node)
{
    Node<T>* temp=node;
    while(temp != nullptr)
    {
        nodes.push(temp);
        temp=temp->left;
    }

    // curr=nodes.top();
    // nodes.pop();
}

template<typename T>
typename Set<T>::Iterator& Set<T>::Iterator::operator++()
{
    if(nodes.empty()){
        curr=nullptr;
        return *this;
    }

    Node<T>* top=nodes.top();
    nodes.pop();


    if(top->right != nullptr){
        Node<T>* curr=top->right;
        while(curr != nullptr){
            nodes.push(curr);
            curr=curr->left;
        }
    }
    curr=top;

    return *this;
}