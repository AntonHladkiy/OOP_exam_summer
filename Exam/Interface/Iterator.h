//#pragma once
//#include "Container.h"
//template <typename T>
//class Iterator {
//public:
//    Iterator() {};
//    virtual bool operator== (const Iterator<T>* rhs) const = 0;
//
//    virtual  bool operator!= (const Iterator<T>* rhs) const = 0;
//
//    // dereference operator. return a reference to
//    // the value pointed to by nodePtr
//    const T& operator* () const {
//        return nodePtr->key;
//    }
//
//    // preincrement. move forward to next larger value
//    virtual Iterator<T>* operator++ () = 0;
//    void setCurr(T key) {
//        nodeCurr = new NodeInterface<T>(key);
//    }
//    NodeInterface<T>* getCurr() {
//        return nodeCurr;
//    }
//    NodeInterface<T>* nodeCurr;
//    Container<T>* Container;
//};