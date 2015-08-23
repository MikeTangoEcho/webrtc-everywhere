#pragma once
#include <list>

// CSharePermissionsDlg dialog

class CSharePermissionsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSharePermissionsDlg)

public:
	CSharePermissionsDlg(CWnd* pParent = NULL);   // standard constructor
	CSharePermissionsDlg(std::list<LPCTSTR>* plVideo, std::list<LPCTSTR>* plAudio, CWnd* pParent = NULL);	// constructeur avec Sources
	virtual ~CSharePermissionsDlg();

// Dialog Data
	enum { IDD = IDD_SHAREPERMISSIONS_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	std::list<LPCTSTR>* p_lVideo;
	std::list<LPCTSTR>* p_lAudio;

	// Gens
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonShare();
	afx_msg void OnBnClickedButtonCancel();
	// Available Capture devices for Video
	CComboBox m_cbVideo;
	// Available Capture Device for Audio
	CComboBox m_cbAudio;
};
