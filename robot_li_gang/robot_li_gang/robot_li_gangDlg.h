
// robot_li_gangDlg.h : ͷ�ļ�
//

#pragma once


// Crobot_li_gangDlg �Ի���
class Crobot_li_gangDlg : public CDialogEx
{
// ����
public:
	Crobot_li_gangDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_ROBOT_LI_GANG_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString m_x1;
	CString m_y1;
	CString m_z1;

	CString m_x2;
	CString m_y2;
	CString m_z2;
	
	CString m_th1;
	CString m_th2;
	CString m_th3;

	CString m_th4;
	CString m_th5;
	CString m_th6;

	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedstart();
	afx_msg void OnBnClickedstop();
	afx_msg void OnBnClickedimage();
	afx_msg void OnBnClickedgo();
};
