#include "pch.h"
#include "EditPath.h"
BEGIN_MESSAGE_MAP(CEditPath, CEdit)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


void CEditPath::OnDropFiles(HDROP hDropInfo)
{
	// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
		// TODO: �ڴ�������Ϣ������������/�����Ĭ��ֵ
	if (hDropInfo)
	{
		int nDrag; //��ק�ļ�������
		nDrag = DragQueryFile(hDropInfo, 0xFFFFFFFF, NULL, 0);
		if (nDrag == 1)
		{
			// ����ק���ļ����ļ���
			TCHAR Path[MAX_PATH + 1] = { 0 };
			// �õ�����ק���ļ���
			DragQueryFile(hDropInfo, 0, Path, MAX_PATH);
			// ���ļ�����ʾ����
			SetWindowText(Path);
			DragFinish(hDropInfo);
		}
		else
		{
			MessageBox(_T("ֻ����קһ���ļ���"));
		}
		CEdit::OnDropFiles(hDropInfo);
	}
	CEdit::OnDropFiles(hDropInfo);
}

