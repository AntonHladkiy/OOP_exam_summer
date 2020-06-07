#include "BTree/Btree.h"

int main() {
	BTree<int> tree(3);
	for (int i = 0; i < 100; i++) {
		tree.insert(i);
	}
	tree.insert(0);
	tree.traverse();
}