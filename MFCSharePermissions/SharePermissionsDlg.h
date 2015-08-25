#pragma once
#include <list>
#include "SourceInfos.h"
#include "afxwin.h"

// CSharePermissionsDlg dialog

class CSharePermissionsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSharePermissionsDlg)

public:
	CSharePermissionsDlg(CWnd* pParent = NULL);   // standard constructor
	CSharePermissionsDlg(std::shared_ptr<_Sequence<_SourceInfo>> plSourceInfos,
		LPTSTR host, LPCH pVideoSourceId, LPCH pAudioSourceId,
		CWnd* pParent = NULL);	// constructeur avec Sources
	virtual ~CSharePermissionsDlg();

// Dialog Data
	enum { IDD = IDD_SHAREPERMISSIONS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	std::shared_ptr<_Sequence<_SourceInfo>> p_lSourceInfos;
	LPCH p_VideoSourceId;
	LPCH p_AudioSourceId;
	LPTSTR pHost;
	// Gens
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
	void setChosenSources();
public:
	afx_msg void OnBnClickedButtonShare();
	afx_msg void OnBnClickedButtonCancel();
	// Available Capture devices for Video
	CComboBox m_cbVideo;
	// Available Capture Device for Audio
	CComboBox m_cbAudio;
	CStatic m_sHostmsg;
};
