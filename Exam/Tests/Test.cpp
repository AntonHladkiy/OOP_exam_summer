#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "../BTree/Btree.h";
#include "../AVLTree/AVLTree.h"
#include "../List/List.h"
#include "../HashTable/OpenAdressing.h"
#include "../HashTable/SeparateChaining.h"
#include "../Set/Set.h"
#include "../Interface/ContainerStrategy.h"
#include <vector>


TEST_CASE("trees")
{
	SUBCASE("AVL") {
		AVLTree<int> tree;
		for (int i = 0; i < 10; i++) {
			tree.insert(i);
		}
		int k = 0;
		for (auto i = tree.begin(); i != tree.end(); ++i) {
			REQUIRE(*i == k);
			k++;
		}
		REQUIRE(tree.search(5) != nullptr);
		REQUIRE(tree.search(5)->key ==5);
		REQUIRE(tree.search(10)==nullptr);
		tree.remove(6);
		REQUIRE(tree.search(6) == nullptr);
	}
	SUBCASE("BTree") {
		BTree<int> tree(3);
		for (int i = 0; i < 10; i++) {
			tree.insert(i);
		}
		int k = 0;
		vector<int> temp = tree.get_all_values();
		for (auto i = 0; i <temp.size(); ++i) {
			REQUIRE(temp[i] == k);
			k++;
		}
		REQUIRE(tree.search(5) != nullptr);
		REQUIRE(tree.search_universal(5)->key == 5);
		REQUIRE(tree.search(10) == nullptr);
		tree.remove(6);
		REQUIRE(tree.search(6) == nullptr);
	}
}
TEST_CASE("list") {
	DoubleLinkedList<int> list;
	for (int i = 0; i < 10; i++) {
		list.insert(i);
	}
	int k = 0;
	vector<int> temp = list.get_all_values();
	for (auto i = 0; i < temp.size(); ++i) {
		REQUIRE(temp[i] == k);
		k++;
	}
	REQUIRE(list.search(5) != nullptr);
	REQUIRE(list.search_universal(5)->key == 5);
	REQUIRE(list.search(10) == nullptr);
	list.remove(6);
	REQUIRE(list.search(6) == nullptr);
}
TEST_CASE("Hash") {
	SUBCASE("SeparateChaining") {
		SeparateChaning<int> hash(14);
		for (int i = 0; i < 10; i++) {
			hash.insert(i);
		}
		
		REQUIRE(hash.search_universal(5) != nullptr);
		REQUIRE(hash.search_universal(5)->key == 5);
		REQUIRE(hash.search_universal(10) == nullptr);
		hash.remove(6);
		REQUIRE(hash.search_universal(6) == nullptr);
	}
}
TEST_CASE("Set") {
	Set<int> set;
	for (int i = 0; i < 10; i++) {
		set.insert(i);
	}
	int k = 0;
	vector<int> temp = set.container->get_all_values();
	for (auto i = 0; i < temp.size(); ++i) {
		REQUIRE(temp[i] == k);
		k++;
	}
	REQUIRE(set.include(5) ==true);
	REQUIRE(set.include(10) == false);
	set.remove(6);
	REQUIRE(set.include(6) == false);
}
TEST_CASE("Set Operations") {
	SUBCASE("/") {
		Set<int> set1(new ListContainer<int>);
		for (int i = 0; i < 10; i++) {
			set1.insert(i);
		}
		Set<int> set2(new ListContainer<int>);
		for (int i = 5; i < 10; i++) {
			set2.insert(i);
		}
		Set<int> set3 = set1 / set2;
		int k = 0;
		vector<int> temp = set3.container->get_all_values();
		for (auto i = 0; i < temp.size(); ++i) {
			REQUIRE(temp[i] == k);
			k++;
		}
	}
	SUBCASE("+") {
		Set<int> set1(new ListContainer<int>);
		for (int i = 0; i < 10; i++) {
			set1.insert(i);
		}
		Set<int> set2(new ListContainer<int>);
		for (int i = 5; i < 10; i++) {
			set2.insert(i);
		}
		Set<int> set3 = set1 + set2;
		int k = 0;
		vector<int> temp = set3.container->get_all_values();
		for (auto i = 0; i < temp.size(); ++i) {
			REQUIRE(temp[i] == k);
			k++;
		}
	}
}