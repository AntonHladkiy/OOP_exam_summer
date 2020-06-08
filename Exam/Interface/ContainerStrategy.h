#pragma once
#include "AVLTree/AVLTree.h"
#include "BTree/Btree.h"
#include "List/List.h"
template <typename T>
class SeparateChaning;
template <typename T>
class ContainerStrategy {
public:
	virtual Container<T>* get_container()=0;
};
template <typename T>
class BTreeContainer:public ContainerStrategy<T> {
public:
	Container<T>* get_container() override {
		return new BTree<T>(3);
	}
};
template <typename T>
class ListContainer :public ContainerStrategy<T> {
public:
	Container<T>* get_container() override {
		return new DoubleLinkedList<T>();
	}
};
template <typename T>
class AVLTreeContainer :public ContainerStrategy<T> {
public:
	Container<T>* get_container() override {
		return new AVLTree<T>();
	}
};
template <typename T>
class SeparateChainingHashContainer :public ContainerStrategy<T> {
public:
	Container<T>* get_container() override {
		return new SeparateChaning<T>();
	}
};
