#include "BTree/Btree.h";
#include "AVLTree/AVLTree.h"
#include "List/List.h"
#include "HashTable/OpenAdressing.h"
int main() {
	OpenAdressingHash<int> hash(19);
	for (int i = 0; i < 10; i++) {
		hash.insert(i);
	};
	std::cout << " ";
	/*for (int i = 0; i < 10; i++) {
		hash.remove(i);
	};*/
	/*BTree<int> tree(4);
	for (int i = 0; i < 100; i++) {
		(tree).insert(i);
	}
	Hash<BTree<int>> hash(10);

	std::cout << hash.get_hash(tree);*/
	/*BTree<int> tree(4);
	for (int i = 0; i < 100; i++) {
		tree.insert(i);
	}
	tree.traverse();
	tree.remove(4);
	tree.traverse();
	DoubleLinkedList<int> list;
	for (int i = 0; i < 100; i++) {
		list.insert(i);
	}
	list.show();
	for (int i = 0; i < 100; i++) {
		list.remove(i);
	}
	list.show();*/
}