#pragma once


/////////////// LLRBTree ///////////////

template <typename K, typename V>
class LLRBTree final
{
	template <typename, typename>
	friend class Dictionary;
public:

	V* search(const K& key);

	void insert(const K& key, const V& value);

	void remove(const K& key);

private:

	const static bool RED = true;
	const static bool BLACK = false;

	class Node
	{
	public:

		K key;

		V val;

		Node* left = nullptr;

		Node* right = nullptr;

		Node* parent = nullptr;

		bool color;

		Node(const K& key, const V& val);
	};

	Node* root = nullptr;

	Node* insert(Node* h, const K& key, const V& value);

	Node* rotateLeft(Node* h);

	Node* rotateRight(Node* h);

	Node* moveRedLeft(Node* h);

	Node* moveRedRight(Node* h);

	void flipColors(Node* h);

	bool isRed(Node* h);

	Node* fixUp(Node* h);

	Node* deleteMin(Node* h);

	Node* minNode(Node* h);

	Node* remove(Node* h, const K& key);
};



/////////////// Dictionary ///////////////

template <typename K, typename V>
class Dictionary final
{
public:

	Dictionary();

	~Dictionary();

	void put(const K& key, const V& value);

	void remove(const K& key);

	bool contains(const K& key);

	const V& operator[](const K& key) const;

	V& operator[](const K& key);

	int getSize() const;

	class Iterator
	{
	public:

		Iterator(LLRBTree<K, V>& llrbTreeRef);

		const K& key() const;

		const V& get() const;

		void set(const V& value);

		void next();

		void prev();

		bool hasNext() const;

		bool hasPrev() const;

	private:

		LLRBTree<K, V>& llrbTreeRef;

		typename LLRBTree<K, V>::Node* currentNode;

		typename LLRBTree<K, V>::Node* iteratorRoot;

		typename LLRBTree<K, V>::Node* lastNode;

		bool shouldGoDown;
	};

	Iterator iterator();

	const Iterator iterator() const;

private:

	LLRBTree<K, V> llrbTree;

	int size;
};

#include "Search.cpp"