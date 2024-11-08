
// blowfishDlg.h: 头文件
//

#pragma once

#include "EditPath.h"

// CblowfishDlg 对话框
class CblowfishDlg : public CDialogEx
{
// 构造
public:
	CblowfishDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BLOWFISH_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 密钥
	CString m_strkey;
	CString m_strming;
	// 密文
	CString m_strmi;
	CEditPath m_editPath;
	afx_msg void OnBnClickedBtnSpath();
	afx_msg void OnBnClickedBtnAbout();
	afx_msg void OnBnClickedBtnEnc();
	afx_msg void OnBnClickedBtnDec();

	INT m_bfile;
	CBrush m_brush;

private:
	void fileenc();
	void filedec();
	void getKeyCstrtoChar(char*& key,const int& len);
	void getTextCstrtoChar(char*& text, int& len, CString& strText);

public:
	afx_msg void OnBnClickedBtnRankey();
	afx_msg void OnBnClickedBtnClear();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
