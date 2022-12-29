#pragma once
#include <memory>
#include <iostream>
#include <vector>

#include "Debug.h"


namespace Tree
{
	template<class T>
	class Tree
	{
	private:
		using Pointer = std::unique_ptr<Tree>;

		T data;
		Pointer left;
		Pointer right;

	public:
		Tree(const T& data) :
			data(data), left(nullptr),
			right(nullptr)
		{}

		Tree(T&& data) :
			data(std::move(data)),
			left(nullptr),
			right(nullptr)
		{}

		Tree(const T& data, Tree&& left, Tree&& right) :
			data(data),
			left(new Tree(std::move(left))),
			right(new Tree((std::move(right))))
		{}

		Tree(T&& data, Tree&& left, Tree&& right) :
			data(std::move(data)),
			left(new Tree(std::move(left))),
			right(new Tree((std::move(right))))
		{}

		Tree(const T& data, Tree&& child, bool left) :
			data(data)
		{
			if (left) this->left.reset(new Tree(std::move(child)));
			else this->right.reset(new Tree(std::move(child)));
		}

		Tree(T&& data, Tree&& child, bool left) :
			data(std::move(data))
		{
			if (left) this->left.reset(new Tree(std::move(child)));
			else this->right.reset(new Tree(std::move(child)));
		}

		Tree(Tree&& other) = default;
		Tree(const Tree&) = delete;
		Tree& operator=(const Tree&) = delete;

		T& Data()
		{
			return data;
		}

		const T& Data() const
		{
			return data;
		}

		bool HasLeft() const
		{
			return left.get() != nullptr;
		}

		bool HasRight() const
		{
			return right.get() != nullptr;
		}

		bool IsLeaf() const
		{
			return !(HasLeft() || HasRight());
		}

		Tree& Left()
		{
			D(if (!HasLeft()) throw std::out_of_range("Left child not set"));
			return *left;
		}

		const Tree& Left() const
		{
			D(if (!HasLeft()) throw std::out_of_range("Left child not set"));
			return *left;
		}

		Tree& Right()
		{
			D(if (!HasRight()) throw std::out_of_range("Right child not set"));
			return *right;
		}

		const Tree& Right() const
		{
			D(if (!HasRight()) throw std::out_of_range("Right child not set"));
			return *right;
		}
	};


	namespace
	{
		template<class T, class F>
		void FindUnique(const Tree<T>& tree, F& pred, std::vector<T>& ret)
		{
			if (pred(tree.Data()) && std::find(ret.begin(), ret.end(), tree.Data()) == ret.end())
				ret.push_back(tree.Data());

			if (tree.HasLeft()) FindUnique(tree.Left(), pred, ret);
			if (tree.HasRight()) FindUnique(tree.Right(), pred, ret);
		}
	}


	template<class T, class F>
	std::vector<T> FindUnique(const Tree<T>& tree, F pred)
	{
		std::vector<T> ret;
		FindUnique(tree, pred, ret);
		return ret;
	}


	template<class T>
	bool operator==(const Tree<T>& t1, const Tree<T>& t2)
	{
		if (t1.HasLeft() && !t2.HasLeft())  return false;
		if (!t1.HasLeft() && t2.HasLeft())   return false;
		if (t1.HasRight() && !t2.HasRight()) return false;
		if (!t1.HasRight() && t2.HasRight())  return false;

		bool equal = t1.Data() == t2.Data();
		if (equal && t1.HasLeft()) equal = t1.Left() == t2.Left();
		if (equal && t1.HasRight()) equal = t1.Right() == t2.Right();
		return equal;
	}


	template<class T>
	std::ostream& operator<<(std::ostream& stream, const Tree<T>& tree)
	{
		stream << tree.Data() << std::endl;
		if (tree.HasLeft()) stream << "L:" << tree.Left();
		if (tree.HasRight()) stream << "R:" << tree.Right();
		return stream;
	}
}