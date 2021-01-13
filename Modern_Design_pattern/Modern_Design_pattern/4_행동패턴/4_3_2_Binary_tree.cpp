#include <iostream>
#include <string>
#include <coroutine>
#include <experimental/generator>

template <typename T> struct BinaryTree;

template<typename T>
struct Node
{
	T value;

	Node<T>* left = nullptr;
	Node<T>* right = nullptr;
	Node<T>* parent = nullptr;
	BinaryTree<T>* tree = nullptr;

	explicit Node(const T& value) : value{ value } {}
	Node(const T& value, Node<T>* const left, Node<T>* const right) 
		: value{ value }, left{ left }, right{ right } 
	{
		this->left->tree = this->right->tree = tree;
		this->left->parent = this->right->parent = this;
	}

	void set_tree(BinaryTree<T>* t)
	{
		tree = t;
		if (left) left->set_tree(t);
		if (right) right->set_tree(t);
	}

	~Node()
	{
		if (left) delete left;
		if (right) delete right;
	}
};

template <typename T> 
struct BinaryTree
{
    Node<T>* root = nullptr;

    explicit BinaryTree(Node<T>* const root)
        : root{ root }
    {
        root->set_tree(this);
    }

    ~BinaryTree() { if (root) delete root; }
   
    std::experimental::generator<Node<T>*> post_order_impl(Node<T>* node)
    {
        if (node)
        {
            for (auto x : post_order_impl(node->left))
                co_yield x;
            for (auto y : post_order_impl(node->right))
                co_yield y;
            co_yield node;
        }
    }

    std::experimental::generator<Node<T>*> post_order()
    {
        return post_order_impl(root);
    }

    std::experimental::generator<Node<T>*> pre_order_impl(Node<T>* node)
    {
        if (node)
        {
            for (auto x : pre_order_impl(node->left))
                co_yield x;
            co_yield node;
            for (auto y : pre_order_impl(node->right))
                co_yield y;            
        }
    }

    std::experimental::generator<Node<T>*> pre_order()
    {
        return pre_order_impl(root);
    }
};

int main()
{
    BinaryTree<std::string> family{
    new Node<std::string>{"me",
      new Node<std::string>{"mother",
        new Node<std::string>{"mother's mother"},
        new Node<std::string>{"mother's father"}
            },
      new Node<std::string>{"father"}
        }
    };     
  
    
    for (auto it : family.post_order())
    {
        std::cout << it->value << "\n";
    }    

    for (auto it : family.pre_order())
    {
        std::cout << it->value << "\n";
    }
}