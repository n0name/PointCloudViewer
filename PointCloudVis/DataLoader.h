#pragma once
#include "DataModel.h"
#include <memory>

namespace Data {

	std::unique_ptr<DataModel> LoadFromDat(const std::wstring &path);

} // namespace Data 
