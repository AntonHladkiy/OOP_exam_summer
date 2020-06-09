#include "BTree/Btree.h";
#include "AVLTree/AVLTree.h"
#include "List/List.h"
#include "HashTable/OpenAdressing.h"
#include "HashTable/SeparateChaining.h"
#include "Set/Set.h"
#include "Interface/ContainerStrategy.h"
int main() {
	Set<int> set1(new AVLTreeContainer<int>);
	for (int i = 0; i < 10; i++) {
		set1.insert(i);
	}
	set1.show();
	Set<int> set2(new AVLTreeContainer<int>);
	for (int i = 5; i < 15; i++) {
		set2.insert(i);
	}
	set2.show();
	Set<int> set3=set1^set2;
	set1.show();
	set3.show();
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