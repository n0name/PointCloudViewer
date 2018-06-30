#pragma once
#include <valarray>
#include <limits>

namespace Data {



template <typename DataType> struct MyRect;
template <typename DataType> struct Vector2D;
template <typename DataType> struct Vector3D;

using DVector3D = Vector3D<double>;
using DVector2D = Vector2D<double>;
using DRect			= MyRect<double>;

template <typename DataType>
struct Vector2D 
{
	DataType x = DataType(0);
	DataType y = DataType(0);

	Vector2D CreateOrtogon() const { return { -y, x }; }
	bool IsInside(MyRect<DataType> &rRect) const;
};

template <typename DataType>
struct Vector3D 
{
	DataType x = DataType(0);
	DataType y = DataType(0);
	DataType z = DataType(0);

	Vector2D<DataType> xy() const { return { x, y }; }
	Vector2D<DataType> yz() const { return { y, z }; }
	Vector2D<DataType> xz() const { return { x, z }; }
};

#undef max
#undef min

template <typename DataType>
struct MyRect 
{
	DataType l = std::numeric_limits<DataType>::max();
	DataType r = -std::numeric_limits<DataType>::max();
	DataType t = -std::numeric_limits<DataType>::max();
	DataType d = std::numeric_limits<DataType>::max();

	MyRect<DataType> operator | (const MyRect<DataType> &rOther) const;
	MyRect<DataType>& operator |= (const MyRect<DataType> &rOther);
};


struct PointCloudContainer
{
	std::valarray<DVector3D> m_Points;
};

struct BaseShape : PointCloudContainer
{
	DVector3D m_Position;
};

struct Cylinder : PointCloudContainer
{
	DVector3D m_Axis;
	double m_Radius;
	double m_Height;
};

struct Cone : PointCloudContainer
{
	DVector3D m_Axis;
	double m_RadiusAtBase;
	double m_Height;
};

} // namespace Data 