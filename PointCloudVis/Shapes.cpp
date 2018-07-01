#include "stdafx.h"
#include "Shapes.h"
#include <vector>
#include <optional>

namespace Data {


std::unique_ptr<BaseShape> ShapeFactory::CreateShape(const Shapes shape)
{
	switch (shape)
	{
	case Shapes::CYLINDER:
		return std::make_unique<Cylinder>();
	case Shapes::CONE:
		return std::make_unique<Cone>();
	case Shapes::SPHERE:
		return std::make_unique<Sphere>();
	case Shapes::PLANE:
		return std::make_unique<Plane>();

	case Shapes::INVALID:
	default:
		return nullptr;
	}
}

using NameShapePair = std::pair<std::string, ShapeFactory::Shapes>;

static std::vector<NameShapePair> sShapeNameLUT = {
	{"Cylinder", ShapeFactory::Shapes::CYLINDER},
	{"Cone", ShapeFactory::Shapes::CONE},
	{"Shpere", ShapeFactory::Shapes::SPHERE},
	{"Plane", ShapeFactory::Shapes::PLANE},
};

static ShapeFactory::Shapes GetShape(const std::string &name)
{
	for (const NameShapePair &nsp : sShapeNameLUT)
	{
		if (nsp.first == name)
			return nsp.second;
	}
	return ShapeFactory::Shapes::INVALID;
}


std::unique_ptr<BaseShape> ShapeFactory::CreateShape(const std::string & shapeName)
{
	auto shape = GetShape(shapeName);
	return CreateShape(shape);
}

} // namespace Data
