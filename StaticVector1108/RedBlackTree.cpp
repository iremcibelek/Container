#include "RedBlackTree.h"


template<typename T, std::size_t Capacity>
RedBlackTree<T, Capacity>::RedBlackTree(PoolRBT<T, Capacity>& pool)
	: pool(pool), root(nullptr), count(0) {
}

template<typename T, std::size_t Capacity>
RedBlackTree<T, Capacity>::~RedBlackTree() {
	clear();
}


template<typename T, std::size_t Capacity>
typename RedBlackTree<T, Capacity>::Node* RedBlackTree<T, Capacity>::getRoot() const {
	return root;
}


template<typename T, std::size_t Capacity>
typename RedBlackTree<T, Capacity>::Node* RedBlackTree<T, Capacity>::getGrandparent(Node* x) {
	if(x!= nullptr && x->parent != nullptr)
		return x->parent->parent;
	return nullptr;
}


template<typename T,std::size_t Capacity>
typename RedBlackTree < T, Capacity>::Node* RedBlackTree<T, Capacity>::getUncle(Node* x) {
	Node* g = getGrandparent(x);
	if (g == nullptr)
		return nullptr;

	Node* u = nullptr;
	if (x->parent == g->left) // X's parent is g's left child 
		u = g->right; // u has to be right child
	else
		u = g->left;

	return u;
}


template<typename T,std::size_t Capacity>
typename RedBlackTree<T, Capacity>::Node* RedBlackTree<T, Capacity>::getSibling(Node* x) {
	if (x == nullptr || x->parent == nullptr)
		return nullptr;

	if (x == x->parent->left)
		return x->parent->right;
	else
		return x->parent->left;
}


template<typename T,std::size_t Capacity>
Color RedBlackTree<T, Capacity>::getColor(Node* x) const {
	if (x == nullptr)
		return B;
	return x->color;
}


template<typename T,std::size_t Capacity>
void RedBlackTree<T, Capacity>::swapColors(Node* a, Node* b) {
	if (a != nullptr && b != nullptr) {
		Color temp = a->color;
		a->color = b->color;
		b->color = temp;
	}
}


template<typename T,std::size_t Capacity>
typename RedBlackTree<T, Capacity>::Node* RedBlackTree<T,Capacity>::getSuccessor(Node* x) {
	while (x != nullptr && x->left != nullptr) {
		x = x->left;
	}
	return x;
}


template<typename T,std::size_t Capacity>
void RedBlackTree<T, Capacity>::leftRotate(Node* x) {
	Node* y = x->right;

	x->right = y->left; // y's left subtree became x's right subtree
	if (y->left != nullptr)
		y->left->parent = x;

	y->parent = x->parent; //x's old parent is y's now
	if (x->parent == nullptr) //x was the root
		root = y;
	else if (x == x->parent->left) // x was a left child
		x->parent->left = y; // y replaced x
	else // x was a right child
		x->parent->right = y;

	// Connect x and y
	y->left = x;
	x->parent = y;
}


template<typename T,std::size_t Capacity>
void RedBlackTree<T, Capacity>::rightRotate(Node* y) {
	Node* x = y->left;

	y->left = x->right; //x's right subtree became y's left subtree
	if (x->right != nullptr)
		x->right->parent = y;

	x->parent = y->parent; // y's old parent is x's now
	if (y->parent == nullptr) // y was the root 
		root = x; // new root

	else if (y == y->parent->left) // y was a left child
		y->parent->left = x; // x replaced x
	else // y was a right child
		y->parent->right = x;

	// Connection 
	x->right = y;
	y->parent = x;
}


template<typename T, std::size_t Capacity>
void RedBlackTree<T, Capacity>::fixRedProperty(Node* x) {
	while (x != root && x->parent != nullptr && x->parent->color == R) {
		Node* p = x->parent;
		Node* u = getUncle(x);
		Node* g = getGrandparent(x);

		if (g == nullptr)
			break;

		if (getColor(u) == R) { // Uncle is red
			p->color = B;
			u->color = B;
			g->color = R;
			// Repeat the all rocoloring steps for 
			// Grandparent considering it as X.
			x = g;
		}

		else { // Uncle is black
			// Left Case
			if (p == g->left) {
				if (x == p->right) { // Left Right Case
					// Left Rotation to P
					x = p;
					leftRotate(x);
					p = x->parent;
				}
				// Left Left Case
				rightRotate(g);
				swapColors(g, p);
			}
			else { // Right Case
				if (x == p->left) { // Right Left Case
					// Right Rotation to P
					x = p;
					rightRotate(x);
					p = x->parent;
				}
				// Right Right Case
				leftRotate(g);
				swapColors(g, p);
			}

		}
	}
	root->color = B;
}


template<typename T,std::size_t Capacity>
bool RedBlackTree<T, Capacity>::insert(const T& value) {
	
	Node* newNode = pool.acquire();
	if (newNode == nullptr)
		return false;

	// newNode data definition
	newNode->data = value;
	newNode->color = R;
	newNode->left = nullptr;
	newNode->right = nullptr;
	newNode->parent = nullptr;

	// New root and its color must be black.
	if (root == nullptr) {
		root = newNode;
		root->color = B;
		count++;
		return true;
	}

	// Apply BST alghoritm
	Node* temp = root;
	Node* p = nullptr;

	while (temp != nullptr) {
		p = temp; // parent
		if (value < temp->data)
			temp = temp->left;

		else if (value > temp->data)
			temp = temp->right;

		else { // duplicate value
			pool.release(newNode);
			return false;
		}
	}

	// newNode's parent is p
	newNode->parent = p;
	if (value < p->data)
		p->left = newNode; // Left Child
	if (value > p->data)
		p->right = newNode; // Right Child
	count++;

	fixRedProperty(newNode);
	return true;
}


template<typename T,std::size_t Capacity>
void RedBlackTree<T, Capacity>::transplant(Node* u, Node* v) {
	if (u->parent == nullptr)
		root = v;

	else if (u == u->parent->left)  // u sol agac ise
		u->parent->left = v; // yerine v'yi koy
	else 
		u->parent->right = v;

	if (v != nullptr) // v bos degilse bagla 
		v->parent = u->parent;
}


// copy paste aldm bunu direkt tekrar bak
template<typename T, std::size_t Capacity>
void RedBlackTree<T, Capacity>::fixDoubleBlack(Node* x, Node* xParent) {
	while (x != root && getColor(x) == B) {
		// x sol kol tarafýndaysa
		if (x == (xParent ? xParent->left : nullptr)) {
			// x nullptr ise kardeþ xParent->right, deðilse getSibling(x)
			Node* s = (x != nullptr) ? getSibling(x) : (xParent ? xParent->right : nullptr);

			// Sibling Kýrmýzýysa
			if (getColor(s) == R) {
				s->color = B;
				xParent->color = R;
				leftRotate(xParent);
				s = (x != nullptr) ? getSibling(x) : xParent->right;
			}

			// Sibling Siyah ve her iki çocuðu da Siyahsa
			if (getColor(s->left) == B && getColor(s->right) == B) {
				s->color = R;
				x = xParent;
				xParent = x->parent; // Sorunu bir üst seviyeye aktar
			}
			else {
				// Kural 3(b): Near child (sol) Kýrmýzý, Far child (sað) Siyahsa
				if (getColor(s->right) == B) {
					if (s->left != nullptr)
						s->left->color = B;
					s->color = R;
					rightRotate(s);
					s = (x != nullptr) ? getSibling(x) : xParent->right;
				}

				// Kural 3(a): Far child (sað) Kýrmýzýysa
				s->color = xParent->color;
				xParent->color = B;
				if (s->right != nullptr)
					s->right->color = B;
				leftRotate(xParent);
				x = root; // Dengeleme tamamlandý
				break;
			}
		}
		// x sað kol tarafýndaysa (Simetrik Durum)
		else {
			Node* s = (x != nullptr) ? getSibling(x) : (xParent ? xParent->left : nullptr);

			// Kural 1: Sibling Kýrmýzýysa
			if (getColor(s) == R) {
				s->color = B;
				xParent->color = R;
				rightRotate(xParent);
				s = (x != nullptr) ? getSibling(x) : xParent->left;
			}

			// Kural 2: Sibling Siyah ve her iki çocuðu da Siyahsa
			if (getColor(s->left) == B && getColor(s->right) == B) {
				s->color = R;
				x = xParent;
				xParent = x->parent;
			}
			else {
				// Kural 3(b): Near child (sað) Kýrmýzý, Far child (sol) Siyahsa
				if (getColor(s->left) == B) {
					if (s->right != nullptr)
						s->right->color = B;
					s->color = R;
					leftRotate(s);
					s = (x != nullptr) ? getSibling(x) : xParent->left;
				}

				// Kural 3(a): Far child (sol) Kýrmýzýysa
				s->color = xParent->color;
				xParent->color = B;
				if (s->left != nullptr)
					s->left->color = B;
				rightRotate(xParent);
				x = root;
				break;
			}
		}
	}

	if (x != nullptr) {
		x->color = B;
	}
}


template<typename T,std::size_t Capacity>
bool RedBlackTree<T, Capacity>::erase(const T& value) {

	// Perform Standart BST Deletion
	if (root == nullptr)
		return  false;

	Node* toDeleted = root;
	while (toDeleted != nullptr && toDeleted->data != value) {
		if (value < toDeleted->data)
			toDeleted = toDeleted->left;
		if (value > toDeleted->data)
			toDeleted = toDeleted->right;
	}

	if (toDeleted == nullptr)
		return false;

	Node* y = toDeleted; // Sökülecek olan düðüm (Cift cocuk icin kullanýyoruz)
	Node* x = nullptr; // toDeleted's child who takes its place 
	Color yOriginalColor = getColor(y); 
	Node* xParent = nullptr;


	if (toDeleted->left == nullptr) { // No left subtree
		x = toDeleted->right; // y'nin sag cocugu
		xParent = toDeleted->parent;
		transplant(toDeleted, toDeleted->right);
	}

	else if (toDeleted->right == nullptr) { // No right subtree
		x = toDeleted->left;
		xParent = toDeleted->parent;
		transplant(toDeleted, toDeleted->left);
	}

	else { // Two child
		y = getSuccessor(toDeleted->right);
		yOriginalColor = y->color;
		x = y->right; // y'nin sadece sað çocuðu olabilir

		if (y->parent == toDeleted) {
			if (x != nullptr)
				x->parent = y;
			xParent = y;
		}
		else {
			xParent = y->parent;
			transplant(y, y->right);
			y->right = toDeleted->right;
			y->right->parent = y;
		}

		// y'yi toDeleted'ýn yerine taþý
		transplant(toDeleted, y);
		y->left = toDeleted->left;
		y->left->parent = y;
		y->color = toDeleted->color; // toDeleted'ýn rengini devralýr
	}

	pool.release(toDeleted);
	count--;

	if (yOriginalColor == B) 
		fixDoubleBlack(x, xParent);
	
	return true;
}


template<typename T,std::size_t Capacity>
T* RedBlackTree<T, Capacity>::min() {
	if (root == nullptr)
		return nullptr;

	Node* temp = root;
	while (temp->left != nullptr) {
		temp = temp->left;
	}
	return &temp->data;
}


template<typename T, std::size_t Capacity>
const T* RedBlackTree<T, Capacity>::min() const {
	if (root == nullptr)
		return nullptr;

	Node* temp = root;
	while (temp->left != nullptr) {
		temp = temp->left;
	}
	return &temp->data;
}


template<typename T,std::size_t Capacity>
T* RedBlackTree<T, Capacity>::max() {
	if (root == nullptr)
		return nullptr;

	Node* temp = root;
	while (temp->right != nullptr) {
		temp = temp->right;
	}
	return &temp->data;
}


template<typename T,std::size_t Capacity>
const T* RedBlackTree<T, Capacity>::max() const {
	if (root == nullptr)
		return nullptr;

	Node* temp = root;
	while (temp->right != nullptr) {
		temp = temp->right;
	}
	return &temp->data;
}


template <typename T,std::size_t Capacity>
std::size_t RedBlackTree<T, Capacity>::size() const {
	return count;
}


template <typename T,std::size_t Capacity>
bool RedBlackTree<T, Capacity>::isEmpty() {
	return root == nullptr;
}


template<typename T,std::size_t Capacity>
bool RedBlackTree<T, Capacity>::isFull() {
	return count == Capacity;
}


template<typename T,std::size_t Capacity>
std::size_t RedBlackTree<T, Capacity>::capacity() const {
	return pool.returnCapacity();
}


template <typename T,std::size_t Capacity>
void RedBlackTree<T, Capacity>::clearRec(Node* current) {
	if (current == nullptr)
		return;
	clearRec(current->left);
	clearRec(current->right);
	pool.release(current);
}


template<typename T,std::size_t Capacity>
void RedBlackTree<T, Capacity>::clear() {
	clearRec(root);
	root = nullptr;
	count = 0;
}


template<typename T,std::size_t Capacity>
bool RedBlackTree<T, Capacity>::exists(const T& value) {
	Node* temp = root;

	while (temp != nullptr) {
		if (value == temp->data)
			return true;
		if (value < temp->data)
			temp = temp->left;
		else
			temp = temp->right;
	}
	return false;
}


template class RedBlackTree<int, 5>;