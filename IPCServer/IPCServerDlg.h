
// IPCServerDlg.h: 头文件
//

#pragma once
#include "../Common/Common.h"

// CIPCServerDlg 对话框
class CIPCServerDlg : public CDialogEx, public IServer
{
// 构造
public:
	CIPCServerDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_IPCSERVER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

public:
	virtual void SendData(char* pszData, int nLen);
	virtual void OnDataArrive(char* pszData, int nLen);


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
	CListBox m_client_list;
	CListBox m_func_list;
	CEdit m_message;
	CEdit m_send;
};
