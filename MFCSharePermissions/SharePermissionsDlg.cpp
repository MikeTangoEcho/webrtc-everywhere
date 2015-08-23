// SharePermissionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "MFCSharePermissions.h"
#include "SharePermissionsDlg.h"
#include "afxdialogex.h"

// CSharePermissionsDlg dialog

IMPLEMENT_DYNAMIC(CSharePermissionsDlg, CDialogEx)

CSharePermissionsDlg::CSharePermissionsDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSharePermissionsDlg::IDD, pParent)
{

}

CSharePermissionsDlg::CSharePermissionsDlg(std::list<LPCTSTR>* plVideo, std::list<LPCTSTR>* plAudio, CWnd* pParent /*=NULL*/)
	: CDialogEx(CSharePermissionsDlg::IDD, pParent)
{
	p_lVideo = plVideo;
	p_lAudio = plAudio;
}

CSharePermissionsDlg::~CSharePermissionsDlg()
{
}

void CSharePermissionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_VIDEO, m_cbVideo);
	DDX_Control(pDX, IDC_COMBO_AUDIO, m_cbAudio);
}

BEGIN_MESSAGE_MAP(CSharePermissionsDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_SHARE, &CSharePermissionsDlg::OnBnClickedButtonShare)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, &CSharePermissionsDlg::OnBnClickedButtonCancel)
END_MESSAGE_MAP()


// CSharePermissionsDlg message handlers
BOOL CSharePermissionsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: ajoutez ici une initialisation supplémentaire
	if (m_cbAudio && m_cbVideo){
		m_cbVideo.AddString(L"NONE");
		m_cbAudio.AddString(L"NONE");
		for (std::list<LPCTSTR>::iterator it = p_lVideo->begin(); it != p_lVideo->end(); ++it)
			m_cbVideo.AddString(*it);
		for (std::list<LPCTSTR>::iterator it = p_lAudio->begin(); it != p_lAudio->end(); ++it)
			m_cbAudio.AddString(*it);
	}
	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CSharePermissionsDlg::OnBnClickedButtonShare()
{
	EndDialog(IDOK);
}


void CSharePermissionsDlg::OnBnClickedButtonCancel()
{
	EndDialog(IDCANCEL);
}
