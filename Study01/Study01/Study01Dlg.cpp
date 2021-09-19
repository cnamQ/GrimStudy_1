
// Study01Dlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Study01.h"
#include "Study01Dlg.h"
#include "afxdialogex.h"

#include "CDlgNew.h"

#include <fstream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define COLOR_LABEL_BK RGB(100,0,0)
#define COLOR_LABEL_TEXT RGB(255,255,255)


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
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


// CStudy01Dlg 대화 상자



CStudy01Dlg::CStudy01Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUDY01_DIALOG, pParent)
	, m_dNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CStudy01Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_NEW, m_btnDlgNew);
	DDX_Text(pDX, IDC_EDIT1, m_dNum);
	DDX_Control(pDX, IDC_STATIC_01, m_lblNum);
}

BEGIN_MESSAGE_MAP(CStudy01Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_NEW, &CStudy01Dlg::OnBnClickedButtonNew)
	ON_BN_CLICKED(IDOK, &CStudy01Dlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON2, &CStudy01Dlg::OnBnClickedButton2)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON_IMAGE, &CStudy01Dlg::OnBnClickedButtonImage)
	ON_BN_CLICKED(IDC_BUTTON_PARAMETER, &CStudy01Dlg::OnBnClickedButtonParameter)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CStudy01Dlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CStudy01Dlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_BINARIZ, &CStudy01Dlg::OnBnClickedButtonBinariz)
	ON_BN_CLICKED(IDC_BUTTON_CENTROID, &CStudy01Dlg::OnBnClickedButtonCentroid)
END_MESSAGE_MAP()


// CStudy01Dlg 메시지 처리기

BOOL CStudy01Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
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

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.


	//////////////////////////////////////////////////////////////////////////
	//
	InitButton(&m_btnDlgNew);
	InitLabel(&m_lblNum);
	InitDialog();


	UpdateIni(true);

	//////////////////////////////////////////////////////////////////////////

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CStudy01Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CStudy01Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CStudy01Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStudy01Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(m_pDlgImage)
		delete m_pDlgImage;
	if(m_pDlgParameter)
		delete m_pDlgParameter;

}



void CStudy01Dlg::OnBnClickedButtonNew()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
// 	CDlgNew Dlg;
// 	Dlg.DoModal();

	UpdateData(true);
	m_lblNum.SetText(m_dNum);

}

void CStudy01Dlg::InitButton(CCtrlButtonST* pButton)
{
	CFont font;
	font.CreatePointFont(12, _T("Consolas"));

	pButton->SetFont(&font);
	pButton->SetColor(CCtrlButtonST::BTNST_COLOR_BK_IN, COLOR_LABEL_BK);
	pButton->SetColor(CCtrlButtonST::BTNST_COLOR_BK_OUT, COLOR_LABEL_BK);

	pButton->SetColor(CCtrlButtonST::BTNST_COLOR_FG_IN, COLOR_LABEL_TEXT);
	pButton->SetColor(CCtrlButtonST::BTNST_COLOR_FG_OUT, COLOR_LABEL_TEXT);

}

void CStudy01Dlg::InitLabel(CLabel* pLabel)
{
	pLabel->SetFontName(_T("Consolas"));
	pLabel->SetFontSize(12);

	pLabel->SetBkColor(COLOR_LABEL_BK);
	pLabel->SetTextColor(COLOR_LABEL_TEXT);


}

void CStudy01Dlg::InitDialog()
{
	CRect cr(20, 50, 550, 350);

	m_pDlgImage = new CDlgImage(this);
	m_pDlgImage->Create(IDD_CDlgImage, this);		// Create Modeless 
	m_pDlgImage->MoveWindow(cr);

	m_pDlgParameter = new CDlgParameter(this);
	m_pDlgParameter->Create(IDD_CDlgParameter, this);		// Create Modeless 
	m_pDlgParameter->MoveWindow(cr);

	SetDlgView(DLG_VIEW_IMAGE);


}

void CStudy01Dlg::SetDlgView(int nMode)
{
	if(nMode & DLG_VIEW_IMAGE)
		m_pDlgImage->ShowWindow(SW_SHOW);
	else
		m_pDlgImage->ShowWindow(SW_HIDE);


	if(nMode & DLG_VIEW_PARAMETER)
		m_pDlgParameter->ShowWindow(SW_SHOW);
	else
		m_pDlgParameter->ShowWindow(SW_HIDE);



}

void CStudy01Dlg::UpdateIni(BOOL bLoad)
{
	CString fileName = CString("D://99_Code//cnamQ//GrimStudy_1//Study01//Study01//Glim.ini");
	ifstream file(fileName);

	if(!file.good())
		bLoad = false;

	CString str(fileName);
	CString strSection(_T("Parameters"));
	
	CIni ini(str, strSection);

	ini.SerGet(bLoad, m_dNum, _T("NUM"));

	UpdateData(false);

}



void CStudy01Dlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(true);
	UpdateIni(false);

	CDialogEx::OnOK();
}


void CStudy01Dlg::OnBnClickedButton2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	
	/*
	UpdateData(true)		컨트롤 -> 변수 값 전송
	UpdateData(false)		변수 -> 컨트롤 값 전송
	
	UpdateData()는 컨트롤과 변수의 값이 변경되면 갱신시켜주는 함수.
	꼭! DoDataExchange에 컨트롤과 변수가 연결된 상태여야 한다.
	이전 방식으로는,,, GetDlgItem() & SetDlgItem 등을 써왔던 방식과 같다.
	
	UpdateData() 할때마다 DoDataExchange()가 호출된다.
	*/

	m_bTest = !m_bTest;

	UpdateData(m_bTest);
}




void CStudy01Dlg::OnBnClickedButtonImage()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetDlgView(DLG_VIEW_IMAGE);

}


void CStudy01Dlg::OnBnClickedButtonParameter()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetDlgView(DLG_VIEW_PARAMETER);
}


void CStudy01Dlg::OnBnClickedButtonSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	char strFilter[] = "BMP ONLY (*.BMP) | *.BMP;*.bmp | All Files(*.*)|*.*||";

	CFileDialog fileDlg(TRUE, CString(".BMP"), NULL, 0, CString(strFilter));

	if(fileDlg.DoModal() == IDOK)
	{
		m_pDlgImage->m_ImgFile.Save(fileDlg.GetPathName());
	}
}


void CStudy01Dlg::OnBnClickedButtonLoad()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	


	char strFilter[] = "BMP ONLY (*.BMP) | *.BMP;*.bmp | All Files(*.*)|*.*||";

	CFileDialog fileDlg(TRUE, CString(".BMP"), NULL, 0, CString(strFilter));

	if(fileDlg.DoModal() == IDOK)
	{
		// Img Info 존재여부 확인 후, 존재 시 제거
		if(m_pDlgImage->m_ImgFile != NULL)
		{
			m_pDlgImage->m_ImgFile.Destroy();
		}

		HRESULT hr = m_pDlgImage->m_ImgFile.Load(fileDlg.GetPathName());

		if(SUCCEEDED(hr))
		{
 			m_pDlgParameter->ShowWindow(SW_HIDE);
			m_pDlgImage->ShowWindow(SW_HIDE);
			m_pDlgImage->ShowWindow(SW_SHOW);
		}
	}
}


void CStudy01Dlg::OnBnClickedButtonBinariz()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pDlgImage->Binarization(GetThresholdData());

	m_pDlgParameter->ShowWindow(SW_HIDE);
	m_pDlgImage->ShowWindow(SW_HIDE);
	m_pDlgImage->ShowWindow(SW_SHOW);

}


void CStudy01Dlg::OnBnClickedButtonCentroid()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_pDlgImage->Centroid();

	m_pDlgParameter->ShowWindow(SW_HIDE);
	m_pDlgImage->ShowWindow(SW_HIDE);
	m_pDlgImage->ShowWindow(SW_SHOW);
}
