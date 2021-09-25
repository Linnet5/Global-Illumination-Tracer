#pragma once

/* **********************************************************
 * Class to represent a bi-directional iterator for BSTs     *
 * Bi-directional iterators can be moved in both directions, *
 * increasing and decreasing order of items keys             *
 * ***********************************************************/

template <typename Comparable>
class BinarySearchTree<Comparable>::Iterator {
public:
    // Some properties for Iterator  -- so that Iterator can be used with STL-algorithms
    using iterator_category = std::bidirectional_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = Comparable;
    using pointer           = Comparable*;  // or also value_type*
    using reference         = Comparable&;  // or also value_type&

    /* ****************************************************************** */

    // Exercise 2: ADD CODE   

    //Default constructor
    Iterator() {
        ptr = nullptr;
        t = nullptr;
    }

    reference operator*() const {
        return ((*ptr).element);
    }//O(1)

    pointer operator->() const {
        return &(ptr->element);
    }//O(1)

    //Pre-increment
    Iterator& operator++() {
        ptr = t->find_successor(ptr);
        return *this;
    } //Complexity of find_successor O(n)

    //Post-increment
    Iterator operator++(int) {
        //Return the iterator adress that it had before updating
        Iterator temp = *this;
        ++(*this);
        return temp;
    } //-''-

    //Pre-decrement
    Iterator& operator--() {
        ptr = t->find_predecessor(ptr);
        return *this;
    }//O(n)

    //Post-decrement
    Iterator operator--(int) {
        Iterator temp = *this;
        --(*this);
        return temp;
    }//O(n)

    bool operator==(const Iterator &it) const {
        return(ptr == it.ptr);
    }//O(1)

    bool operator!=(const Iterator& it) const {
        return(ptr != it.ptr);
    }//O(1)

    //template <typename Comparable>
    friend class BinarySearchTree;

private:
    Node* ptr;
    BinarySearchTree* t;

    Iterator(Node* inNode, BinarySearchTree* inT) {
        ptr = inNode;
        t = inT;
    }//O(1)
};