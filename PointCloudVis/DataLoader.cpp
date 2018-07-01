#include "stdafx.h"
#include "DataLoader.h"
#include "DataModel.h"

#include "Shapes.h"

#include <fstream>
#include <string>
#include <list>
#include <sstream>
#include <tuple>
#include <functional>

#define MAX_PARSELINE 1000 // We don't expect more than 1000 symbols per line

namespace Data {

static std::list<std::string> tokenize(const std::string &str, const char delim)
{
	std::list<std::string> tokens;
	std::istringstream iss;
	iss.str(str);
	for (std::string tempTok; std::getline(iss, tempTok, delim);)
	{
		tokens.emplace_back(tempTok);
	}
	return std::move(tokens);
}


std::unique_ptr<DataModel> LoadFromDat(const std::wstring & path)
{
	std::ifstream ifs(path);

	std::unique_ptr<DataModel> model{ new DataModel };
	std::unique_ptr<BaseShape> curShape{ nullptr };
	std::vector<DVector3D> tempPts;

	for (std::string line; std::getline(ifs, line); )
	{
		if (line[0] == '[')
		{
			if (curShape.get())
			{
				curShape->m_Points = { tempPts.data(), tempPts.size() }; // This should copy the data inside the feature
				tempPts.clear();
				model->m_Features.push_back(std::move(curShape));
			}

			curShape = ShapeFactory::CreateShape(line.substr(2, line.size() - 4));
		}
		else if (curShape.get())
		{
			auto tokens = tokenize(line, ',');
			double temp[3] = { 0, 0, 0 };
			ASSERT(tokens.size() == 3);
			int i = 0;
			for (const auto &t : tokens)
				temp[i++] = std::stod(t);

			tempPts.push_back({ temp[0], temp[1], temp[2] });
		}
	}

	// Handle last shape
	if (curShape.get())
	{
		curShape->m_Points = { tempPts.data(), tempPts.size() }; // This should copy the data inside the feature
		tempPts.clear();
		model->m_Features.push_back(std::move(curShape));
	}


	return std::move(model);
}

} // namespace Data 
