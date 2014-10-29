
// FlashToCocosXDlg.h : ͷ�ļ�
//

#pragma once
#include <iostream>

// CFlashToCocosXDlg �Ի���
class CFlashToCocosXDlg : public CDialogEx
{
// ����
public:
	CFlashToCocosXDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_FLASHTOCOCOSX_DIALOG };

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
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();

public:
	//xml parse
	void readXml(const std::string &filename);
	
	std::string getRotationByA(const std::string &_a, const std::string &_b, const std::string &_c, const std::string &_d);
	std::string getScaleXByA(const std::string &_a, const std::string &_b, const std::string &_c, const std::string &_d);
	std::string getScaleYByA(const std::string &_a, const std::string &_b, const std::string &_c, const std::string &_d);
public:
	CString selectFilePath;

	float aabb;
};
