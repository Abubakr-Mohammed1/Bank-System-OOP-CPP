#pragma once
#include <iostream>
#include "clsUtil.h"
#include "global.h"

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
		cout << "\n\n" << clsUtil::Tabs(5) << "-----------------------------------\n";

		cout << "\n" << clsUtil::Tabs(5) << "User: " << CurrentUser.UserName << "\n";
		cout << clsUtil::Tabs(5) << "Date: " << clsDate::DateToString(clsDate()) << "\n\n";
	}

	static bool CheckAccessRights(clsUser::ePermissions Permissions)
	{
		if (!CurrentUser.CheackAccessPermissions(Permissions))
		{
			cout << clsUtil::Tabs(5) << "-----------------------------------";
			cout << "\n\n" << clsUtil::Tabs(5) << "Access Denied! Contact Your Admin.";
			cout << "\n\n" << clsUtil::Tabs(5) << "-----------------------------------\n";
			return false;
		}
		else
		{
			return true;
		}
	}



};

