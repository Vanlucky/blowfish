
// blowfishDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "blowfish.h"
#include "blowfishDlg.h"
#include "afxdialogex.h"

#include "EditPath.h"
#include "bf.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const char zifu[] = "1234567890abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CblowfishDlg 对话框



CblowfishDlg::CblowfishDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_BLOWFISH_DIALOG, pParent)
	, m_strkey(_T(""))
	, m_strming(_T(""))
	, m_strmi(_T(""))

	, m_bfile(1)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CblowfishDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_KEY, m_strkey);
	DDX_Text(pDX, IDC_EDIT_MING, m_strming);
	DDX_Text(pDX, IDC_EDIT_MI, m_strmi);
	DDX_Control(pDX, IDC_EDIT_PATH, m_editPath);

	DDX_Radio(pDX, IDC_RADIO_FILE, m_bfile);
}

BEGIN_MESSAGE_MAP(CblowfishDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_SPATH, &CblowfishDlg::OnBnClickedBtnSpath)
	ON_BN_CLICKED(IDC_BTN_ABOUT, &CblowfishDlg::OnBnClickedBtnAbout)
	ON_BN_CLICKED(IDC_BTN_ENC, &CblowfishDlg::OnBnClickedBtnEnc)
	ON_BN_CLICKED(IDC_BTN_DEC, &CblowfishDlg::OnBnClickedBtnDec)
	ON_BN_CLICKED(IDC_BTN_RANKEY, &CblowfishDlg::OnBnClickedBtnRankey)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CblowfishDlg::OnBnClickedBtnClear)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CblowfishDlg 消息处理程序

BOOL CblowfishDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标


	srand((unsigned int)time(NULL));

	CBitmap bitmap;
	bitmap.LoadBitmap(IDB_BMP_MATRIX);   //这个IDB_BITMAP1要自己添加
	m_brush.CreatePatternBrush(&bitmap);
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CblowfishDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CblowfishDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CblowfishDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CblowfishDlg::OnBnClickedBtnSpath()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strFile = L"";

	// 创建一个 CFileDialog 对象 dlgFile，用于打开文件选择对话框
	CFileDialog dlgFile(TRUE,    // TRUE 表示打开文件而不是保存文件 
		NULL,    // 默认文件扩展名， 如果此参数为 NULL，则不附加扩展
		NULL,     // 显示在 Filename （文件名） 框中的初始文件名，如果为 NULL，则不显示初始文件名
		OFN_HIDEREADONLY,    // 可用于自定义对话框的一个或多个标志的组合 
		_T("All Files (*.*)|*.*|Config Files (*.cfg)|*.cfg||"),    // 一系列字符串对，用于指定可应用于文件的筛选器 
		NULL);    // 指向文件对话框的父窗口或所有者窗口的指针

	// 以模态方式显示文件选择对话框，如果用户选择了文件并点击了“打开”按钮，
	// DoModal 会返回 IDOK，否则返回 IDCANCEL
	if (dlgFile.DoModal())
	{
		// 获取用户选择的文件完整路径
		strFile = dlgFile.GetPathName();

		// 将目录显示在编辑框控件中
		m_editPath.SetWindowTextW(strFile.GetString());
	}
}


void CblowfishDlg::OnBnClickedBtnAbout()
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}


void CblowfishDlg::OnBnClickedBtnEnc()
{
	UpdateData(true);

	if (m_bfile == 0)
	{
		fileenc();
		return;
	}

	if (m_strkey.IsEmpty() || m_strming.IsEmpty())
	{
		MessageBox(_T("请检查密钥和明文是否输入完整！"));
		return;
	}

	// 获取char*类型的明文
	char* cming;
	int minglen = 0;
	getTextCstrtoChar(cming, minglen, m_strming);

	// 获取char*类型的密钥
	int keylen = m_strkey.GetLength();
	char* key;
	getKeyCstrtoChar(key, keylen);

	Blowfish blowfish;
	blowfish.SetKey((unsigned char*)key, keylen);
	blowfish.Encrypt((unsigned char*)cming, (unsigned char*)cming, minglen);

	// 将char*密文转成CString显示在编辑框控件中
	wchar_t* wCharnew = NULL;
	wCharnew = (wchar_t*)malloc(minglen * sizeof(wchar_t) / 2);
	memset(wCharnew, 0, minglen);
	memcpy(wCharnew, cming, minglen);
	m_strmi = wCharnew;

	UpdateData(false);
	free(wCharnew);
	free(cming);
	free(key);
	return;
}


void CblowfishDlg::OnBnClickedBtnDec()
{
	UpdateData(true);

	if (m_bfile == 0)
	{
		filedec();
		return;
	}

	if (m_strkey.IsEmpty() || m_strmi.IsEmpty())
	{
		MessageBox(_T("请检查密钥和密文是否输入完整！"));
		return;
	}

	// 获取char*类型的密文
	char* cmi;
	int milen = 0;
	getTextCstrtoChar(cmi, milen, m_strmi);

	// 获取char*类型的密钥
	int keylen = m_strkey.GetLength();
	char* key;
	getKeyCstrtoChar(key, keylen);

	Blowfish blowfish;
	blowfish.SetKey((unsigned char*)key, keylen);
	blowfish.Decrypt((unsigned char*)cmi, (unsigned char*)cmi, milen);

	// 将char*明文转成CString显示在编辑框控件中
	wchar_t* wCharnew = NULL;
	wCharnew = (wchar_t*)malloc(milen * sizeof(wchar_t) / 2);
	memset(wCharnew, 0, milen);
	memcpy(wCharnew, cmi, milen);
	m_strming = wCharnew;

	UpdateData(false);
	free(wCharnew);
	free(cmi);
	free(key);
	return;
}

void CblowfishDlg::fileenc()
{
	if (m_editPath.GetWindowTextLength() == 0)
	{
		MessageBox(_T("请选择文件！"));
		return;
	}

	CString strFile;
	m_editPath.GetWindowText(strFile);
	CFile file;
	if (!file.Open(strFile, CFile::typeBinary | CFile::modeReadWrite))
	{
		MessageBox(_T("打开文件失败！"));
		return;
	}

	// 获取char* 类型的文件内容
	int len = file.GetLength();
	int lenhex = len + ((len % 16 != 0) ? (16 - len % 16) : 0);

	char* ftext = (char*)malloc(lenhex * sizeof(char));
	memset(ftext, 0, lenhex);
	file.Read(ftext, len);
	//CString strText = ftext;
	//MessageBox(strText);

	// 获取char*类型的密钥
	int keylen = m_strkey.GetLength();
	char* key;
	getKeyCstrtoChar(key, keylen);

	Blowfish blowfish;
	blowfish.SetKey((unsigned char*)key, keylen);
	blowfish.Encrypt((unsigned char*)ftext, (unsigned char*)ftext, lenhex);
	file.SeekToBegin();
	file.Write(ftext, lenhex);
	file.Close();
	return;
}

void CblowfishDlg::filedec()
{
	if (m_editPath.GetWindowTextLength() == 0)
	{
		MessageBox(_T("请选择文件！"));
		return;
	}

	CString strFile;
	m_editPath.GetWindowText(strFile);
	//CString strText;
	CFile file;
	if (!file.Open(strFile, CFile::typeBinary | CFile::modeReadWrite))
	{
		MessageBox(_T("打开文件失败！"));
		return;
	}

	int len = file.GetLength();
	if (len % 16 != 0)
	{
		MessageBox(_T("文件长度不为16的倍数！解密失败！"));
		return;
	}
	//int lenhex;
	//if (len % 16 != 0)
	//	lenhex = len + (16 - len % 16);
	//else
	//	lenhex = len;

	char* ftext = (char*)malloc(len * sizeof(char));
	memset(ftext, 0, len);
	file.Read(ftext, len);
	//strText = ftext;
	//MessageBox(strText);

	// 获取char*类型的密钥
	int keylen = m_strkey.GetLength();
	char* key;
	getKeyCstrtoChar(key, keylen);

	Blowfish blowfish;
	blowfish.SetKey((unsigned char*)key, keylen);
	blowfish.Decrypt((unsigned char*)ftext, (unsigned char*)ftext, len);
	file.SeekToBegin();
	file.Write(ftext, len);
	file.Close();
	return;
}

void CblowfishDlg::getKeyCstrtoChar(char*& key, const int& len)
{
	wchar_t* wChar1 = m_strkey.GetBuffer(m_strkey.GetLength());
	m_strkey.ReleaseBuffer();
	// 将得到的wchar* 类型转为 char*类型
	size_t len1 =  wcslen(wChar1) + 1;
	size_t converted1 = 0;
	//char* utext;
	key = (char*)malloc(len1 * sizeof(char));
	wcstombs_s(&converted1, key, len1, wChar1, _TRUNCATE);
	//CString strKey;
	//strKey = key;
	//strKey.Format(_T("%s %d"), strKey, len);
	//MessageBox(strKey);
}

void CblowfishDlg::getTextCstrtoChar(char*& text, int& len, CString& strText)
{
	int strlen = 2 * strText.GetLength();
	len = strlen + ((strlen % 16 != 0) ? (16 - strlen % 16) : 0);
	wchar_t* wChar = strText.GetBuffer(strlen);
	strText.ReleaseBuffer();
	// 将得到的wchar* 类型转为 char*类型
	text = (char*)malloc(len * sizeof(char));
	memset(text, 0, len);
	memcpy(text, (char*)wChar, strlen);
	//CString strKey;
	//for (int i = 0; i < len; i++)
	//	strKey.Format(_T("%s%c"), strKey, text[i]);
	//MessageBox(strKey);
}


void CblowfishDlg::OnBnClickedBtnRankey()
{
	UpdateData(true);
	CString strKey;
	for (int i = 0; i < 16; i++)
	{
		//strKey.Format(_T("%s%c"), strKey, zifu[rand() % 63]);
		strKey += zifu[rand() % 62];
	}
	m_strkey = strKey;
	UpdateData(false);
}


void CblowfishDlg::OnBnClickedBtnClear()
{
	UpdateData(true);
	//m_strkey.Empty();
	m_strming.Empty();
	m_strmi.Empty();
	UpdateData(false);
}


HBRUSH CblowfishDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	
	// TODO:  在此更改 DC 的任何特性
	//UINT id = pWnd->GetDlgCtrlID();
	if (pWnd == this)
	{
		return m_brush;
	}
	else if (nCtlColor == CTLCOLOR_STATIC)
	{
		pDC->SetTextColor(RGB(0, 0, 255));
		//pDC->SetBkMode(TRANSPARENT);
		//return (HBRUSH)::GetStockObject(NULL_BRUSH);
	}


	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}
