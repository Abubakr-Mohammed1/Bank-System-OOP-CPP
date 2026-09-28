#pragma once
#include <iostream>
#include "clsUtil.h"

using namespace std;

class clsScreen
{

protected:

	static void _DrawScreenHeader(string Title, string SubTitle = "")
	{
		cout << clsUtil::Tabs(5) << "-----------------------------------";
		cout << "\n\n" << clsUtil::Tabs(5) << Title;
		if (SubTitle != "")
		{
			cout << "\n" << clsUtil::Tabs(5) << SubTitle;
		}
		cout << "\n\n" << clsUtil::Tabs(5) << "-----------------------------------\n\n";
	}



};

