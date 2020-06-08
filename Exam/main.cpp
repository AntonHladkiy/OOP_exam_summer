#include "BTree/Btree.h"
#include "AVLTree/AVLTree.h"
#include "List/List.h"
int main() {
	/*BTree<int> tree(4);
	for (int i = 0; i < 100; i++) {
		tree.insert(i);
	}
	tree.traverse();
	tree.remove(4);
	tree.traverse();*/
	DoubleLinkedList<int> list;
	for (int i = 0; i < 100; i++) {
		list.insert(i);
	}
	list.show();
	for (int i = 0; i < 100; i++) {
		list.remove(i);
	}
	list.show();
}