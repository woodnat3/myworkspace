//
//  tools.hpp
//  helpful
//
//  Created by Nate Wood on 7/10/20.
//  Copyright © 2020 Nate Wood. All rights reserved.
//

#ifndef tools_hpp
#define tools_hpp

#include <stdio.h>
#include <iostream>
#include<initializer_list>
using std::initializer_list;
#include<stdexcept>
using std::range_error;
#include<algorithm>
using std::copy; using std::swap;
#include <string>
#include <utility>
#include <memory>


using namespace std;

template <typename T>
struct Node
{
public:
    Node() : data_( T() ), next_( nullptr ), last_( nullptr ){};
    Node(T data) : data_( data ), next_( nullptr ), last_( nullptr ){};
    Node(const Node<T> &node)
    {
        data_ = node->get();
        next_ = node->next();
        last_ = node->last();
    }
    Node<T>* next() { return next_; }
    Node<T>* last() { return last_; }
    void setNext(Node<T>* next) { next_ = next; }
    void setLast(Node<T>* last) { last_ = last; }
    T get() { return data_; }
    
private:
    T data_;
    Node<T>* next_ = nullptr;
    Node<T>* last_ = nullptr;
    
};

template <typename T>
class LinkedList
{
public:
    // constructor
    LinkedList() : begin_( nullptr ), end_( nullptr ), size_( 0 ){};
    LinkedList(T data) { begin_ = new Node<T>(data); end_ = begin_; size_ = 1; }
    // destructor
    ~LinkedList();
    // adds node to the end of the linked list
    void append(T data);
    // searches to find if a value is stored in the linked list
    Node<T>* find(T data);
    // deletes the last node in the list
    void pop();
    // inserts a value in the given position if within the list
    void insert(T data, int pos);
    // deletes a value if it is in the linked list
    void del(T data);
    // gets the node in the given position
    Node<T>* get(int pos);
    void display();
    class Iter
    {
    public:
        Iter() = delete;
        Iter(LinkedList<T>* lst, int pos = 0) : lst_( lst ), pos_( pos ), node_( lst_->get(pos) )
        {
            
        };
        bool operator!=(const Iter& other) const
        {
            return node_ != other.node_;
        }
        const T operator *() { return node_->get(); }
        const Iter& operator++()
        {
            node_ = node_->next();
            return *this;
        }
        const Iter operator++(int)
        {
            node_ = node_->next();
            return *this;
        }
        const Node<T>* operator[](int pos)
        {
            node_ = lst_->get(pos);
            return *this;
        }
    private:
        LinkedList<T>* lst_;
        Node<T>* node_;
        int pos_;
        
    };
    
private:
    Node<T>* begin_ = nullptr;
    Node<T>* end_ = nullptr;
    size_t size_ = 0;
};

template<typename t>
class Vector{
private:
    size_t capacity_ = 10;
    size_t size_ = 0;
    t* data_ = new t[capacity_];
public:
    Vector<t>() = default;
    Vector<t>(size_t capacity);
    Vector<t>(initializer_list<t> lst);
    size_t size();
    size_t capacity();
    void push_back(t val);
    t& operator[](size_t val);
    t& front();
    t& back();
    void insert(t data, int pos);
    void fill(t data, int size);
    void swap(Vector &v1, Vector &v2);
    Vector(Vector& v);
    Vector& operator=(Vector v);
    ~Vector<t>();
};

template <typename T>
class OptTree
{
public:
    OptTree();
    template <typename t>
    class Branch : public OptTree
    {
    public:
        Branch() = delete;
        Branch(int size, Vector<Branch<t>*> paths, t data)
        {
            data_ = data;
            size_ = size;
            if (paths[0] == nullptr)
            {
                Vector<Branch<T>*> temp;
                temp.fill(nullptr, size_);
                paths_ = temp;
            }
            else
            {
                paths_ = paths;
            }
        }
        Vector<Branch<t>*> paths() { return paths_; }
        t get() { return data_; }
        virtual Branch<t>* pickOpt(int pos) { return pos<size_ ? paths_[pos] : nullptr; }
        void setPath(Branch<t>* path, int pos)
        {
            if (pos < size_)
            {
                paths_[pos] = path;
            }
        }
        void operator=(t data)
        {
            data_ = data;
        }
        bool _addBranch(Branch<t>* path)
        {
            for (int i = 0; i < size_; i++)
            {
                if (paths_[i] == nullptr)
                {
                    paths_.insert(path, i);
                    return true;
                }
            }
            for (int i = 0; i < size_; i++)
            {
                return paths_[i]->_addBranch(path);
            }
            return false;
        }
    private:
        Vector<Branch<t>*> paths_;
        t data_;
        int size_;
    };
    OptTree(int size, Vector<Branch<T>*> opts, T data);
    virtual void addBranch(Branch<T>* path);
    virtual void addBranch(T data);
    virtual T get(Branch<T>* path) { return path->get(); }
    virtual Branch<T>* pickOpt(int pos) { return pos<size_ ? dataHead_->paths()[pos] : nullptr; }
    virtual void display();
    
private:
    int size_;
    size_t height_ = 1;
    Branch<T>* dataHead_ = nullptr;
    bool _addBranch(Branch<T>* path)
    {
        for (int i = 0; i < size_; i++)
        {
            if (dataHead_->paths()[i] == nullptr)
            {
                dataHead_->paths().insert(path, i);
                return true;
            }
        }
        for (int i = 0; i < size_; i++)
        {
            return dataHead_->paths()[i]->_addBranch(path);
        }
        return false;
    }
    void _adjustHeight()
    {
        if (dataHead_->paths()[0] != nullptr)
        {
            int num = 1;
            Branch<T>* node = pickOpt(0);
            while (node != nullptr)
            {
                num++;
                node = node->pickOpt(0);
            }
            height_ = num;
        }
        else
        {
            height_ = 1;
        }
    }
//    void _display(Branch<T>* node)
//    {
//        if (node)
//        {
//            for (int i = 0; i < size_; i++)
//            {
//                _display(node->pickOpt(i));
//            }
//            cout << node->get() << endl;
//        }
//    }
};

/*




Beginning of functions





*/

template <typename T>
LinkedList<T>::~LinkedList()
{
    Node<T>* to_del = begin_;
    while (to_del != nullptr){
        begin_ = begin_->next();
        if (to_del != nullptr){
            delete to_del;
        }
        to_del = begin_;
    }
    begin_ = nullptr;
}
template <typename T>
void LinkedList<T>::append(T data)
{
    if (size_ > 0)
    {
        Node<T>* node = new Node<T>(data);
        node->setLast(end_);
        end_->setNext(node);
        end_ = node;
    }
    else
    {
        Node<T>* node = new Node<T>(data);
        //Node<T> node(data);
        begin_ = node;
        end_ = node;
    }
    size_++;
}
template <typename T>
Node<T>* LinkedList<T>::find(T data)
{
    Node<T>* node = begin_;
    if (node->next() != nullptr)
    {
        Node<T>* next = begin_->next();
        while (next != nullptr)
        {
            if (node->get() == data)
            {
                return node;
            }
            else
            {
                node = next;
                next = node->next();
            }
        }
    }
    if (node->get() == data)
    {
        return node;
    }
    else
    {
        return nullptr;
    }
}
template <typename T>
void LinkedList<T>::pop()
{
    Node<T>* temp = end_;
    end_ = temp->last();
    delete temp;
    end_->setNext(nullptr);
    size_--;
}
template <typename T>
void LinkedList<T>::insert(T data, int pos)
{
    if (pos < size_ and pos > 0)
    {
        Node<T>* node = new Node<T>(data);
        Node<T>* tail =  begin_;
        Node<T>* head = tail->next();
        for (int i = 1; i < pos; i++)
        {
            tail = tail->next();
            head = head->next();
        }
        node->setNext(head);
        node->setLast(tail);
        head->setLast(node);
        tail->setNext(node);
        size_++;
    }
    else if (pos == 0)
    {
        Node<T>* node = new Node<T>(data);
        begin_->setLast(node);
        node->setNext(begin_);
        begin_ = node;
        size_++;
    }
    else if (pos == size_)
    {
        Node<T>* node = new Node<T>(data);
        end_->setNext(node);
        node->setLast(end_);
        end_ = node;
        size_++;
    }
}
template <typename T>
void LinkedList<T>::del(T data)
{
    Node<T>* node = begin_;
    //Node<T>* next = begin->next_;
    int count = 1;
    while (node != nullptr)
    {
        if (node->get() == data and count != 1 and count != size_)
        {
            node->last()->setNext(node->next());
            node->next()->setLast(node->last());
            size_--;
            delete node;
            break;
        }
        else
        {
            if (node->get() == data and count == 1)
            {
                begin_ = node->next();
                begin_->setLast(nullptr);
                size_--;
                delete node;
                break;
            }
            else if (node->get() == data and count == size_)
            {
                end_ = node->last();
                end_->setNext(nullptr);
                size_--;
                delete node;
                break;
            }
        }
        node = node->next();
        count++;
    }
}
template <typename T>
Node<T>* LinkedList<T>::get(int pos)
{
    if (pos < size_)
    {
        Node<T>* node = begin_;
        int count = 0;
        while (count < pos)
        {
            node = node->next();
            count++;
        }
        return node;
    }
    else
    {
        return nullptr;
    }
}
template <typename T>
void LinkedList<T>::display()
{
    Iter iter(this, 0);
    cout << "<";
    for (iter; *iter != end_->get(); iter++)
    {
        cout << (*iter) << ", ";
    }
    cout << *iter << ">" << endl;
}

template <typename t>
Vector<t>::Vector(size_t capacity){
    capacity_ = capacity;
    size_ = 0;
    delete[]data_;
    data_ = new t[capacity_];
}
template <typename t>
Vector<t>::Vector(initializer_list<t> lst){
    size_ = lst.size();
    capacity_ = lst.size();
    delete[]data_;
    data_ = new t[capacity_];
    copy(lst.begin(), lst.end(), data_);
}
template <typename t>
size_t Vector<t>::size(){
    return size_;
}
template <typename t>
size_t Vector<t>::capacity(){
    return capacity_;
}
template <typename t>
void Vector<t>::push_back(t val){
    if (size_ >= capacity_){
        capacity_ *= 2;
        t* new_data = new t[capacity_];
        copy(data_, data_+size_, new_data);
        delete[]data_;
        data_ = new t[capacity_];
        copy(new_data, new_data+size_, data_);
        delete[]new_data;
    }
    long size = size_;
    data_[size] = val;
    size_ += 1;
}
template <typename t>
t& Vector<t>::operator[](size_t val){
    if (val < size_){
        t& result = data_[val];
        return result;
    }
    else{
        throw range_error("val out of range");
    }
}
template <typename t>
t& Vector<t>::front(){
    if (size_ == 0){
        throw range_error("Vector empty");
    }
    else{
        t& ref = data_[0];
        return ref;
    }
}
template <typename t>
t& Vector<t>::back(){
    if (size_ == 0){
        throw range_error("Vector empty");
    }
    else{
        t& ref = data_[size_-1];
        return ref;
    }
}
template <typename t>
void Vector<t>::insert(t data, int pos)
{
    if (pos < size_)
    {
        data_[pos] = data;
    }
}
template <typename t>
Vector<t>::Vector(Vector& v){
    capacity_ = v.capacity_;
    size_ = v.size_;
    delete[]data_;
    data_ = new t[capacity_];
    copy(v.data_, v.data_+v.size_, data_);
}
template <typename t>
Vector<t>& Vector<t>::operator=(Vector<t> v){
    swap(*this, v);
    return *this;
}
template <typename t>
Vector<t>::~Vector(){
    delete[]data_;
}
template <typename t>
void Vector<t>::swap(Vector &v1, Vector &v2){
    std::swap(v1.size_, v2.size_);
    std::swap(v1.capacity_, v2.capacity_);
    std::swap(v1.data_, v2.data_);
}
template <typename t>
void Vector<t>::fill(t data, int size)
{
    for (int i = 0; i < size; i++)
    {
        data_[i] = data;
    }
    size_ = size;
}
template <typename T>
OptTree<T>::OptTree()
{
    size_ = 2;
    Vector<Branch<T>*> vec(2);
    vec.fill(nullptr, 2);
    dataHead_ = new OptTree<T>::Branch<T>(2, vec, NULL);
}
template <typename T>
OptTree<T>::OptTree(int size, Vector<Branch<T>*> paths, T data)
{
    size_  = size;
    dataHead_ = new Branch<T>(size, paths, data);
}
template <typename T>
void OptTree<T>::addBranch(Branch<T>* path)
{
    if (dataHead_)
    {
        bool good = _addBranch(path);
        if (good)
        {
            _adjustHeight();
        }
    }
    else
    {
        *dataHead_ = path->get();
    }
}
template <typename T>
void OptTree<T>::addBranch(T data)
{
    if (dataHead_)
    {
        Vector<Branch<T>*>  vec(size_);
        vec.fill(nullptr, size_);
        Branch<T>* path = new Branch<T>(size_, vec, data);
        bool good = _addBranch(path);
        if (good)
        {
            _adjustHeight();
        }
    }
    else
    {
        *dataHead_ = data;
    }
}
template <typename T>
void OptTree<T>::display()
{
    cout << "Branch Size: " << size_ << endl;
    cout <<  "Height: " << height_ << endl;
    for (int i = size_-1; i >= 0; i--)
    {
        //_display(dataHead_->paths()[i]);
    }
    //cout << dataHead_ << endl;
}
#endif /* tools_hpp */
