/*******************************************************************
*  Copyright(c) 2016 Chen Gonghao
*  All rights reserved.
*
*  chengonghao@yeah.net
*
*  文件内容:cghSet的实现
******************************************************************/

#ifndef _CGH_SET_
#define _CGH_SET_

#include "globalConstruct.h"
#include "cghAlloc.h"
#include "rb_tree.h"

namespace CGH{
	template<class key, class compare = std::less<key>, class Alloc = cghAllocator<key>>/* 默认情况下采用递增排序 */
	class cghSet{

		#pragma region typedef

	private:
		typedef key		key_type;
		typedef key		value_type;
		typedef compare key_compare;
		typedef compare value_compare;
		typedef	cgh_rb_tree<key_type, value_type, std::identity<value_type>, key_compare, Alloc>	rep_type;
		rep_type t;
	public:
		typedef typename rep_type::const_pointer	pointer;
		typedef typename rep_type::const_pointer	const_pointer;
		typedef typename rep_type::const_reference	reference;
		typedef typename rep_type::const_reference	const_ference;
		typedef typename rep_type::iterator			iterator;
		typedef typename rep_type::size_type		size_type;
		typedef typename rep_type::difference_type	difference_type;

		#pragma endregion

		#pragma region 构造函数
	public:
		cghSet() :t(compare()){}
		cghSet(const cghSet<key, compare, Alloc>&x) :t(x.t){}
		cghSet<key, compare, Alloc>& operator=(const cghSet<key, compare, Alloc>&x)
		{
			t = x.t;
			return *this;
		}
		#pragma endregion

		#pragma region 提供给用户的函数
		/* 返回键比较函数 */
		key_compare key_comp()const{ return t.key_comp(); }

		/* 返回值比较函数 */
		value_compare value_comp()const{ return t.key_comp(); }

		/* 返回迭代器，指定set的第一个元素 */
		iterator begin(){ return t.begin(); }

		/* 返回迭代器，指定set的最后一个元素 */
		iterator end(){ return t.end(); }

		/* set是否为空 */
		bool empty() const{ return t.empty(); }

		/* set大小 */
		size_type size()const{ return t.size(); }

		/* set最大容量 */
		size_type max_size()const{ return t.max_size(); }

		/* 插入元素到set中 */
		std::pair<iterator, bool> insert(const value_type&x)
		{
			std::pair<typename rep_type::iterator, bool> p = t.insert_unique(x);
			return std::pair<iterator, bool>(p.first, p.second);
		}

		/* 
			返回迭代器，指向要查找的元素
			如果没有找到，返回end
		*/
		iterator find(const key_type&x){ return t.find(x); }
		#pragma endregion

	};
}

#endif