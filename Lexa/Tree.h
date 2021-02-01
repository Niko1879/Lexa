#pragma once
#include <memory>


namespace Lexa
{
	template<class T>
	class Tree
	{
	private:
	
		
		using Pointer = std::unique_ptr<Tree>;

		template<class... Args>
		Pointer MakePtr(Args&&... args)
		{
			return std::make_unique<Tree>(std::forward<Args>(args)...);
		}

		T data;
		Pointer left;
		Pointer right;
	
	public:
		Tree(const T& data) : data(data), left(nullptr), right(nullptr) {}

		Tree(T&& data) noexcept : data(std::move(data)), left(nullptr), right(nullptr) {}

		Tree(const T& data, Tree&& left, Tree&& right) : Tree(data)
		{
			this->left = MakePtr(std::move(left));
			this->right = MakePtr(std::move(right));
		}

		Tree(T&& data, Tree&& left, Tree&& right) : Tree(std::move(data))
		{
			this->left = MakePtr(std::move(left));
			this->right = MakePtr(std::move(right));
		}

		T& Data()
		{
			return data;
		}

		const T& Data() const
		{
			return data;
		}

		Tree& Left()
		{
			return *left;
		}

		const Tree& Left() const
		{
			return *left;
		}

		Tree& Right()
		{
			return *right;
		}

		const Tree& Right() const
		{
			return *right;
		}
	};
}