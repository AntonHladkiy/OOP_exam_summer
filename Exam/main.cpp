#include "BTree/Btree.h"
#include "AVLTree/AVLTree.h"
int main() {
	BTree<int> tree(4);
	for (int i = 0; i < 100; i++) {
		tree.insert(i);
	}
	tree.traverse();
	tree.remove(4);
	tree.traverse();
}