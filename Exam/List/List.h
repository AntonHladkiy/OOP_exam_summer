#pragma once
#include <iostream>
template <typename T>
class DoubleLinkedList:public Container<T> {
private:
	class Node {
	public:
		T key;
		Node* next;
		Node* prev;
		Node(T _key) {
			key = _key;
			next = this;
			prev = this;
		}
	};
public:
	DoubleLinkedList() {
		head = nullptr;
	}
	Node* head;
	void show();
	vector<T> get_all_values();
	void insert(const T& key) override;
	void remove(const T& key)override;
	NodeInterface<T>* search_universal(const T& key)override;
	Node* search(T key) {
		if (head) {
			if (head->key == key) {
				return head;
			}
			else {
				Node* temp = head->next;
				while (temp != head) {
					if (temp->key == key) {
						return temp;
					}
					temp = temp->next;
				}
				return nullptr;
			}
		}
		else {
			return head;
		}
	}
};

template<typename T>
inline void DoubleLinkedList<T>::show()
{
	if (head) {
		std::cout << head->key << " ";
		Node* temp = head->next;
		while (temp != head) {
			std::cout << temp->key << " ";
			temp = temp->next;
		}

	}
}

template<typename T>
inline vector<T> DoubleLinkedList<T>::get_all_values()
{
	vector<T> res;
	if (head) {
		res.push_back(head->key);
		Node* temp = head->next;
		while (temp != head) {
			res.push_back(temp->key);
			temp = temp->next;
		}

	}
	return res;
}

template<typename T>
inline NodeInterface<T>* DoubleLinkedList<T>::search_universal(const T& key)
{
	if (search(key)) {
		return new NodeInterface<T>(key);
	}
	else {
		return nullptr;
	}
}


template<typename T>
inline void DoubleLinkedList<T>::insert(const T& key)
{
	if (search(key)) {
		return;
	}
	if (!head) {
		head = new Node(key);
	} else{
		Node* temp = new Node(key);
		temp->next = head;
		temp->prev = head->prev;
		temp->prev->next = temp;
		head->prev = temp;
	}
}

template<typename T>
inline void DoubleLinkedList<T>::remove(const T& key)
{
	if (head) {
		if (head->key == key) {
			if (head->next!=head) {
				head->next->prev = head->prev;
				head->prev->next = head->next;
				Node* temp = head;
				head = head->next;
				delete temp;
			}
			else {
				head = nullptr;
			}
		}
		else {
			Node* temp = head->next;
			while (temp != head) {
				if (temp->key == key) {
					temp->next->prev = temp->prev;
					temp->prev->next = temp->next;
					Node* temp1 = temp;
					delete temp1;
					break;
				}
				temp = temp->next;
			}
		}
	}
	else {
		head = nullptr;
	}
}

//template<typename T>
//inline DoubleLinkedList<T>::Node* DoubleLinkedList<T>::search(T key)
//{
//	if (head) {
//		if (head->key == key) {
//			return head;
//		}
//		else {
//			Node* temp = head->next;
//			while (temp != head) {
//				if (temp->key == key) {
//					return temp;
//				}
//				temp = temp->next;
//			}
//			return nullptr;
//		}
//	}
//	else {
//		return head;
//	}
//}
