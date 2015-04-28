#ifndef _FUN_TREE_H_
#define _FUN_TREE_H_

#include <functional>
#include <iostream>
#include <list>

template <typename T>
class FunTree
{
	private:

		struct Node
		{
			T elt;
			Node *left, *right;
		};

		Node *root;

	public:

		typedef std::function<bool(T, T)> Comparator;
		typedef std::function<void(T)> Operator;
		typedef std::function<T(T)> UnaryOperator;
		typedef std::function<bool(T)> Predicate;
		typedef std::function<T(T, T)> BinaryOperator;
		typedef std::function<void(Node*, std::list<T>&)> Traversal; //?

		static Traversal inorder;

		//template <typename T>
		//friend std::ostream & operator<<(std::ostream &stream, const Traversal &trav);

		template <typename X>
		friend std::string operator<<(const typename FunTree<X>::Traversal &trav, const FunTree<X> &t);

		/*static Traversal preorder = [](Node *node) {
			//wat
		};

		static Traversal postorder = [](Node *node) {
			//wat
		};*/

		FunTree()
		{
			root = nullptr;
		}

		void print_mah_tree()
		{
			print_tree(root);
		}

		void print_tree(Node *node)
		{
			if (node != nullptr)
			{
				print_tree(node->left);
				std::cout << " " << node->elt << " ";
				print_tree(node->right);
			}
		}

		Node & create_node(T elt)
		{
			Node tmp;
			tmp.elt = elt;
			tmp.left = nullptr;
			tmp.right = nullptr;

			return tmp;
		}

		// Inserts a copy
		void insert(T elt, const Comparator &comp = std::less<T>())
		{
			Node *prev, *node = root;

			if (root == nullptr)
				root = create_node(elt);
			else
			{
				bool is_left = false;

				while (node != nullptr)
				{
					prev = node;

					if (comp(elt, node->elt))
					{
						node = node->left;
						is_left = true;
					}
					else
					{
						node = node->right;
						is_left = false;
					}
				}

				if (is_left)
					prev->left = create_node(elt);
				else
					prev->right = create_node(elt);
			}
		}

		// Checks whether an element exists or not
		bool find(T elt, const Comparator &comp)
		{
			//czy elt istnieje?
			return true;
		}

		// If elt is found, it is removed with all subtree
		void erase(T elt, const Comparator &comp)
		{
			//usuwam
		}

		// Applies function to every tree element
		/*void apply(const Operator &operation, const Traversal &traversal = inorder)
		{
			//wat
		}

		// Creates new tree from existing
		FunTree<T> & map(const UnaryOperator &unary_op, traversal, const Comparator &comp)
		{
			//wat
		}

		// Creates new tree from existing, containing elements fitting predicate
		FunTree<T> & filter(const Predicate &predicate, traversal, const Comparator &comp)
		{
			//cool
		}

		// Computes and return result of accumulation tree elements by binary_operation
		blah fold(const BinaryOperator &binary_op, init, traversal)
		{
			// ;____;
		}

		// Returns function g(n) = f(n) op root
		std::function<> fun(f, op)
		{
			//qpa
		}*/
};

/*template <typename T>
std::ostream & operator<<(std::ostream &os, const typename FunTree<T>::Traversal &trav)
{
	return os;
}*/

template <typename T>
typename FunTree<T>::Traversal FunTree<T>::inorder = [](Node *node, std::list<T> &l) {
	if (node != nullptr)
	{
		//inorder(node->left, l);
		std::cout << node->elt << " aaa";
		//l.push_back(node->elt);
		//inorder(node->right, l);
	}
};

template <typename T>
std::string operator<<(const typename FunTree<T>::Traversal &trav, const FunTree<T> &t)
{
	std::list<T> l;
	//std::ostream os(NULL);
	std::string s = "kupa";
	trav(t.root, l);

	for (T elt: l)
		s += /*elt +*/ " ";

	return s;
}

#endif