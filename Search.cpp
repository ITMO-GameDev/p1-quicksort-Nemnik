#include "Search.h"

/////////////// Dictionary ///////////////

template <typename K, typename V>
Dictionary<K, V>::Dictionary()
{
	size = 0;
}

template <typename K, typename V>
Dictionary<K, V>::~Dictionary()
{
}

template <typename K, typename V>
void Dictionary<K, V>::put(const K& key, const V& value)
{
	llrbTree.insert(key, value);
	++size;
}

template <typename K, typename V>
void Dictionary<K, V>::remove(const K& key)
{
	if (contains(key))
	{
		llrbTree.remove(key);
		--size;
	}
}

template <typename K, typename V>
bool Dictionary<K, V>::contains(const K& key)
{
	return llrbTree.search(key) != nullptr;
}

template <typename K, typename V>
const V& Dictionary<K, V>::operator[](const K& key) const
{
	V* elementPtr = llrbTree.search(key);

	if (elementPtr != nullptr)
	{
		return *elementPtr;
	}

	return *new V();
}

template <typename K, typename V>
V& Dictionary<K, V>::operator[](const K& key)
{
	V* elementPtr = llrbTree.search(key);

	if (elementPtr != nullptr)
	{
		return *elementPtr;
	}

	V& defaultValueToBeInserted = *new V();

	llrbTree.insert(key, defaultValueToBeInserted);

	return defaultValueToBeInserted;
}

template <typename K, typename V>
int Dictionary<K, V>::getSize() const
{
	return size;
}

template <typename K, typename V>
Dictionary<K, V>::Iterator::Iterator(LLRBTree<K, V>& llrbTreeRef) : llrbTreeRef(llrbTreeRef)
{
	currentNode = llrbTreeRef.root;
	iteratorRoot = llrbTreeRef.root;

	lastNode = currentNode;

	while (lastNode->right != nullptr)
	{
		lastNode = lastNode->right;
	}

	if (lastNode->left != nullptr)
	{
		lastNode = lastNode->left;
	}

	shouldGoDown = true;
}

template <typename K, typename V>
const K& Dictionary<K, V>::Iterator::key() const
{
	return currentNode->key;
}

template <typename K, typename V>
const V& Dictionary<K, V>::Iterator::get() const
{
	return currentNode->val;
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::set(const V& value)
{
	currentNode->val = value;
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::next()
{
	if (shouldGoDown)
	{
		if (currentNode->left != nullptr)
		{
			currentNode = currentNode->left;
		}
		else
		{
			shouldGoDown = false;
		}
	}

	if (!shouldGoDown)
	{
		while (true)
		{
			typename LLRBTree<K, V>::Node* tmp = currentNode;

			if (currentNode == iteratorRoot)
			{
				break;
			}

			currentNode = currentNode->parent;

			if (currentNode->right != nullptr && currentNode->right != tmp)
			{
				break;
			}
		}

		if (currentNode == iteratorRoot)
		{
			iteratorRoot = currentNode->right;
		}

		currentNode = currentNode->right;

		shouldGoDown = true;
	}
}

template <typename K, typename V>
void Dictionary<K, V>::Iterator::prev()
{
	if (currentNode == currentNode->parent->left)
	{
		currentNode = currentNode->parent;
	}
	else
	{
		if (currentNode->parent->left == nullptr)
		{
			currentNode = currentNode->parent;
		}
		else
		{
			currentNode = currentNode->parent->left;

			while (currentNode->right != nullptr)
			{
				currentNode = currentNode->right;
			}
		}
	}
}

template <typename K, typename V>
bool Dictionary<K, V>::Iterator::hasNext() const
{
	return currentNode != lastNode;
}

template <typename K, typename V>
bool Dictionary<K, V>::Iterator::hasPrev() const
{
	return currentNode != llrbTreeRef.root;
}

template <typename K, typename V>
typename Dictionary<K, V>::Iterator Dictionary<K, V>::iterator()
{
	return *(new Iterator(this->llrbTree));
}

template <typename K, typename V>
const typename Dictionary<K, V>::Iterator Dictionary<K, V>::iterator() const
{
	return *(new Iterator(this->llrbTree));
}

/////////////// LLRBTree ///////////////

template <typename K, typename V>
LLRBTree<K, V>::Node::Node(const K& key, const V& val)
{
	this->key = key;
	this->val = val;
	this->color = RED;
}

template <typename K, typename V>
V* LLRBTree<K, V>::search(const K& key)
{
	Node* x = root;

	while (x != nullptr)
	{
		if (key == x->key)
		{
			return &(x->val);
		}
		else if (key < x->key)
		{
			x = x->left;
		}
		else if (key > x->key)
		{
			x = x->right;
		}
	}

	return nullptr;
}

template <typename K, typename V>
void LLRBTree<K, V>::insert(const K& key, const V& value)
{
	root = insert(root, key, value);
	root->color = BLACK;
}

template <typename K, typename V>
void LLRBTree<K, V>::remove(const K& key)
{
	root = remove(root, key);

	if (root != nullptr)
	{
		root->color = BLACK;
	}
}

template <typename K, typename V>
typename LLRBTree<K, V>::Node* LLRBTree<K, V>::insert(Node* h, const K& key, const V& value)
{
	if (h == nullptr)
	{
		return new Node(key, value);
	}

	if (key == h->key)
	{
		h->val = value;
	}
	else if (key < h->key)
	{
		Node* newNode = insert(h->left, key, value);

		newNode->parent = h;
		h->left = newNode;
	}
	else
	{
		Node* newNode = insert(h->right, key, value);

		newNode->parent = h;
		h->right = newNode;
	}

	h = fixUp(h);

	return h;
}

template <typename K, typename V>
typename LLRBTree<K, V>::Node* LLRBTree<K, V>::rotateLeft(Node* h)
{
	Node* x = h->right;

	h->right = x->left;
	x->left = h;

	if (h->right != nullptr)
	{
		h->right->parent = h;
	}
	x->parent = h->parent;
	h->parent = x;

	x->color = h->color;
	h->color = RED;

	return x;
}

template <typename K, typename V>
typename LLRBTree<K, V>::Node* LLRBTree<K, V>::rotateRight(Node* h)
{
	Node* x = h->left;

	h->left = x->right;
	x->right = h;

	if (h->left != nullptr)
	{
		h->left->parent = h;
	}
	x->parent = h->parent;
	h->parent = x;

	x->color = h->color;
	h->color = RED;

	return x;
}

template <typename K, typename V>
typename LLRBTree<K, V>::Node* LLRBTree<K, V>::moveRedLeft(Node* h)
{
	flipColors(h);

	if (isRed(h->right->left))
	{
		h->right = rotateRight(h->right);
		h = rotateLeft(h);

		flipColors(h);
	}

	return h;
}

template <typename K, typename V>
typename LLRBTree<K, V>::Node* LLRBTree<K, V>::moveRedRight(Node* h)
{
	flipColors(h);

	if (isRed(h->left->left))
	{
		h = rotateRight(h);

		flipColors(h);
	}

	return h;
}

template <typename K, typename V>
void LLRBTree<K, V>::flipColors(Node* h)
{
	h->color = !h->color;
	h->left->color = !h->left->color;
	h->right->color = !h->right->color;
}

template <typename K, typename V>
bool LLRBTree<K, V>::isRed(Node* h)
{
	if (h == nullptr)
	{
		return false;
	}

	return h->color == RED;
}

template <typename K, typename V>
typename LLRBTree<K, V>::Node* LLRBTree<K, V>::fixUp(Node* h)
{
	if (isRed(h->right) && !isRed(h->left))
	{
		h = rotateLeft(h);
	}

	if (isRed(h->left) && isRed(h->left->left))
	{
		h = rotateRight(h);
	}

	if (isRed(h->left) && isRed(h->right))
	{
		flipColors(h);
	}

	return h;
}

template <typename K, typename V>
typename LLRBTree<K, V>::Node* LLRBTree<K, V>::deleteMin(Node* h)
{
	if (h->left == nullptr)
	{
		return nullptr;
	}

	if (!isRed(h->left) && !isRed(h->left->left))
	{
		h = moveRedLeft(h);
	}

	h->left = deleteMin(h->left);

	return fixUp(h);
}

template <typename K, typename V>
typename LLRBTree<K, V>::Node* LLRBTree<K, V>::minNode(Node* h)
{
	return (h->left == nullptr) ? h : minNode(h->left);
}

template <typename K, typename V>
typename LLRBTree<K, V>::Node* LLRBTree<K, V>::remove(Node* h, const K& key)
{
	if (key < h->key)
	{
		if (!isRed(h->left) && !isRed(h->left->left))
		{
			h = moveRedLeft(h);
		}

		h->left = remove(h->left, key);
	}
	else
	{
		if (isRed(h->left))
		{
			h = rotateRight(h);
		}

		if (key == h->key && h->right == nullptr)
		{
			return nullptr;
		}

		if (!isRed(h->right) && !isRed(h->right->left))
		{
			h = moveRedRight(h);
		}

		if (key == h->key)
		{
			Node* mn = minNode(h->right);

			h->val = mn->val;
			h->key = mn->key;
			h->right = deleteMin(h->right);
		}
		else
		{
			h->right = remove(h->right, key);
		}
	}

	return fixUp(h);
}