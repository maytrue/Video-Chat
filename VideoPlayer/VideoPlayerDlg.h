
// VideoPlayerDlg.h : ͷ�ļ�
//

#pragma once

#include "TranscodeSectionThread.h"

// CVideoPlayerDlg �Ի���
class CVideoPlayerDlg : public CDialogEx
{
// ����
public:
	CVideoPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_VIDEOPLAYER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	TranscodeSection* m_window;
	TranscodeSection* m_window1;
	TranscodeSection* m_window2;
	TranscodeSection* m_window3;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnClose();
};
