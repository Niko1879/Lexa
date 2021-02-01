#pragma once
#include <memory>


namespace Lexa
{
	template<class T>
	class Tree
	{
	private:
		struct Node;
		
		using Pointer = std::unique_ptr<Node>;

		struct Node
		{
			template<class... Args>
			Node(Args&& ...args) : data(std::forward<Args>(args)...) {}

			T data;
			Pointer left;
			Pointer right;
		};

		template<class... Args>
		Pointer MakePtr(Args&&... args)
		{
			return std::make_unique<Node>(std::forward<Args>(args)...);
		}

		Pointer root;
	
	public:
		Tree(const T& data) : root(MakePtr(data)) {}

		Tree(T&& data) noexcept : root(MakePtr(std::move(data))) {}

		Tree(const T& data, Tree&& left, Tree&& right) : Tree(data)
		{
			root->left.swap(left.root);
			root->right.swap(right.root);
		}

		Tree(T&& data, Tree&& left, Tree&& right) : Tree(std::move(data))
		{
			root->left.swap(left.root);
			root->right.swap(right.root);
		}

		T& Data()
		{
			return root->data;
		}

		const T& Data() const
		{
			return root->data;
		}
	};
}