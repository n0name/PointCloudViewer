#pragma once

#include <string>
#include "resource.h"




class Application : public CWinApp
{
	BOOL InitInstance();
	static Application *GetApplication();
};
