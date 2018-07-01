#pragma once

#include <string>
#include "resource.h"

namespace Data { struct DataModel; }

class Application : public CWinApp
{
public:
	static Application *GetApplication();
	void LoadModel(const std::wstring &rFilePath);
private:
	BOOL InitInstance();
	std::unique_ptr<Data::DataModel> m_Model;
};
