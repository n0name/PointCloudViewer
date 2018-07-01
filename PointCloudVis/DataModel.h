#pragma once
#include <vector>
#include <memory>
#include "BaseData.h"
#include "Shapes.h"

namespace Data {

struct DataModel
{
	std::vector<std::unique_ptr<BaseShape>> m_Features;
};

} // namespace Data 
