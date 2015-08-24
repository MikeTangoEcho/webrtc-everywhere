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
	p_lSourceInfos = NULL;
}

CSharePermissionsDlg::CSharePermissionsDlg(std::shared_ptr<_Sequence<_SourceInfo>> plSourceInfos,
	std::string* pVideoSourceId, std::string* pAudioSourceId,
	CWnd* pParent /*=NULL*/)
	: CDialogEx(CSharePermissionsDlg::IDD, pParent)
{
	p_lSourceInfos = plSourceInfos;
	p_VideoSourceId = pVideoSourceId;
	p_AudioSourceId = pAudioSourceId;
}

CSharePermissionsDlg::~CSharePermissionsDlg()
{
}

void CSharePermissionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_VIDEO, m_cbVideo);
	DDX_Control(pDX, IDC_COMBO_AUDIO, m_cbAudio);
	DDX_Control(pDX, IDC_STATIC_HOST, m_sHostmsg);
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
	CString str;
	std::string kVideo("video");
	std::string kAudio("audio");
	if (p_lSourceInfos)
	{
		for (std::vector<std::shared_ptr<_SourceInfo> >::iterator it = p_lSourceInfos->values.begin();
				it != p_lSourceInfos->values.end(); ++it)
		{
			str = CString(it->get()->label.c_str());
			if (it->get()->kind == kVideo)
				m_cbVideo.AddString(str);
			else if (it->get()->kind == kAudio)
				m_cbAudio.AddString(str);
		}
	}
	str.LoadString(IDS_NOMEDIA);
	m_cbVideo.AddString(str);
	m_cbAudio.AddString(str);
	m_cbVideo.SetCurSel(0);
	m_cbAudio.SetCurSel(0);
	return TRUE;  // retourne TRUE, sauf si vous avez défini le focus sur un contrôle
}

void CSharePermissionsDlg::OnBnClickedButtonShare()
{
	setChosenSources();
	EndDialog(IDOK);
}


void CSharePermissionsDlg::OnBnClickedButtonCancel()
{
	EndDialog(IDCANCEL);
}


void CSharePermissionsDlg::setChosenSources()
{
	if (p_lSourceInfos && p_AudioSourceId && p_VideoSourceId)
	{
		CString str;
		CString sVideo;
		CString sAudio;
		std::string kVideo("video");
		std::string kAudio("audio");
		m_cbVideo.GetLBText(m_cbVideo.GetCurSel(), sVideo);
		m_cbAudio.GetLBText(m_cbAudio.GetCurSel(), sAudio);

		for (std::vector<std::shared_ptr<_SourceInfo> >::iterator it = p_lSourceInfos->values.begin();
			it != p_lSourceInfos->values.end(); ++it)
		{
			str = CString(it->get()->label.c_str());
			if (it->get()->kind == kVideo && sVideo == str)
				*p_VideoSourceId = it->get()->sourceId;
			else if (it->get()->kind == kAudio && sAudio == str)
				*p_AudioSourceId = it->get()->sourceId;
		}
	}
}
