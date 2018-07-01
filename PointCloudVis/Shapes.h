#pragma once

#include "BaseData.h"
#include <memory>
#include <string>


namespace Data {

struct BaseShape : PointCloudContainer
{
	DVector3D m_Position = { 0, 0, 0 };
};

struct Cylinder : BaseShape
{
	DVector3D m_Axis = { 0, 0, 0 };
	double m_Radius = { 0 };
	double m_Height = { 0 };
};

struct Cone : BaseShape
{
	DVector3D m_Axis = { 0, 0, 0 };
	double m_RadiusAtBase = 0;
	double m_Height = 0;
};

struct Sphere : BaseShape
{
	double m_Radius = 0;
};

struct Plane : BaseShape
{
	DVector3D m_Normal = { 0, 0, 0 };
};

struct ShapeFactory {
	enum class Shapes {
		INVALID,
		CYLINDER,
		CONE,
		SPHERE,
		PLANE
	};

	static std::unique_ptr<BaseShape> CreateShape(const Shapes shape);
	static std::unique_ptr<BaseShape> CreateShape(const std::string &shapeName);

};



} // namespace Data
