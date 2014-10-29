
// FlashToCocosXDlg.h : 头文件
//

#pragma once
#include <iostream>

// CFlashToCocosXDlg 对话框
class CFlashToCocosXDlg : public CDialogEx
{
// 构造
public:
	CFlashToCocosXDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_FLASHTOCOCOSX_DIALOG };

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
