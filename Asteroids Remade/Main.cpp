#include "stdafx.h"

#include "Core.h"


int main()
{
	if (!Core::GetInstance().Initialise())
		return -1;

	Core::GetInstance().Start();
	Core::GetInstance().Run();
	Core::GetInstance().Shutdown();

	return 0;
}