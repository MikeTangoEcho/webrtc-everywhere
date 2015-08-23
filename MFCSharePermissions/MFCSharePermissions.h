// MFCSharePermissions.h : main header file for the MFCSharePermissions DLL
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCSharePermissionsApp
// See MFCSharePermissions.cpp for the implementation of this class
//

class CMFCSharePermissionsApp : public CWinApp
{
public:
	CMFCSharePermissionsApp();

// Overrides
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
