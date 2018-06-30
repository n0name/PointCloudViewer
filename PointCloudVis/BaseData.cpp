#include "stdafx.h"
#include "BaseData.h"

#include <cmath>
namespace Data {

	template <typename DataType>
	MyRect<DataType> MyRect<DataType>::operator | (const MyRect<DataType> &rOther) const
	{
		return { std::min(l, rOther.l),
			std::max(r, rOther.r),
			std::max(t, rOther.t),
			std::min(b, rOther.b) };
	}

	template <typename DataType>
	MyRect<DataType>& MyRect<DataType>::operator |= (const MyRect<DataType> &rOther)
	{
		*this = { std::min(l, rOther.l),
			std::max(r, rOther.r),
			std::max(t, rOther.t),
			std::min(b, rOther.b) };

		return *this;
	}

	template <typename DataType>
	bool Vector2D<DataType>::IsInside(MyRect<DataType> &rRect) const
	{
		return (x >= rRect.l && x <= rRect.r)
			&& (y >= rRect.b && y <= rRect.t);
	}

} // namespace Data