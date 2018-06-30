#pragma once
#include <vector>
#include <memory>
#include "BaseData.h"
namespace Data {

struct DataModel
{
	std::vector<std::unique_ptr<PointCloudContainer>> m_Features;
};

} // namespace Data 
