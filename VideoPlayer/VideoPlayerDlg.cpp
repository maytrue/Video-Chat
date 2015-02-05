
// VideoPlayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "VideoPlayer.h"
#include "VideoPlayerDlg.h"
#include "afxdialogex.h"
#include "TranscodeSectionThread.h"
#include "AVPlaySuite.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CVideoPlayerDlg �Ի���



CVideoPlayerDlg::CVideoPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CVideoPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CVideoPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CVideoPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CVideoPlayerDlg ��Ϣ�������

BOOL CVideoPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	ts_Initialize();

	m_window = ts_CreateTranscodeSection();
	m_window1 = ts_CreateTranscodeSection();
	m_window2 = ts_CreateTranscodeSection();
	m_window3 = ts_CreateTranscodeSection();

	if (!ts_SetWindow(m_window, this, IDC_VIEW)
		//|| !ts_SetWindow(m_window1, this, IDC_VIEW2)
		//|| !ts_SetWindow(m_window2, this, IDC_VIEW3)
		//|| !ts_SetWindow(m_window3, this, IDC_VIEW4))
		)
	{
		MessageBox(_T("Set window failed !"));
		return FALSE;
	}

	//ts_OpenSound(m_window);

	//ts_SetVolumn(m_window, 100);


	
	AVInputSuite *pSuite = new AVInputSuite;
	//pSuite->OpenFileInput("D:\\MOVIE\\1234.mp4");

	pSuite->OpenCameraInput();
	ts_SetInputSuite(m_window, pSuite);

	AVOutputSuite *pOSuite = new AVOutputSuite;

	//if (!pOSuite->OpenRTPOutput("rtp://127.0.0.1:10000"))
	if (!pOSuite->OpenFileOutput("D://test.h264"))
	//if (!pOSuite->OpenRTMPOutput("rtmp://localhost/publishlive/livestream"))
	{
		MessageBox(_T("Open Output Failed"));
	}
	if (!pOSuite->OpenAudioStream())
	{
		MessageBox(_T("Open AudioStream Failed"));
	}
	if (!pOSuite->OpenVideoStream(720, 480))
	{
		MessageBox(_T("Open Video Stream Failed"));
	}
	if (!pOSuite->WriteHeader())
	{
		MessageBox(_T("Write Header Failed"));
	}

	//pOSuite->CreateSdpFile("D:\\testvideo.sdp");

	ts_AddOutputSuite(m_window, pOSuite);

	ts_OpenRecorder(m_window);

	//AVOutputSuite *pOSuite2 = new AVOutputSuite;
	//if (!pOSuite2->OpenFileOutput("D:\\test.mp4")
	//	&& (!pOSuite2->OpenVideoStream(720, 480)))
	//{
	//	MessageBox(_T("Open Output Failed"));
	//}
	//pOSuite2->CreateSdpFile("D:\\testvideo.sdp");
	//pOSuite2->WriteHeader();
	//
	//ts_AddOutputSuite(m_window, pOSuite2);

	//AVInputSuite *pSuite1 = new AVInputSuite;
	//pSuite1->OpenFileInput("D:\\MOVIE\\1234.mp4");
	////pSuite->OpenCameraInput();
	//ts_SetInputSuite(m_window1, pSuite1);


	//AVInputSuite *pSuite2 = new AVInputSuite;
	//pSuite2->OpenFileInput("D:\\MOVIE\\1234.mp4");
	////pSuite->OpenCameraInput();
	//ts_SetInputSuite(m_window2, pSuite2);


	//AVInputSuite *pSuite3 = new AVInputSuite;
	//pSuite3->OpenFileInput("D:\\MOVIE\\1234.mp4");
	////pSuite->OpenCameraInput();
	//ts_SetInputSuite(m_window3, pSuite3);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CVideoPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CVideoPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CVideoPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CVideoPlayerDlg::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	ts_CloseRecorder(m_window);

	ts_DestroyTranscodeSection(&m_window);
	ts_DestroyTranscodeSection(&m_window1);
	ts_DestroyTranscodeSection(&m_window2);
	ts_DestroyTranscodeSection(&m_window3);

	CDialogEx::OnClose();
}
