// CDlgParameter.cpp: 구현 파일
//

#include "pch.h"
#include "Study01.h"
#include "CDlgParameter.h"
#include "afxdialogex.h"

#include "Study01Dlg.h"


// CDlgParameter 대화 상자

IMPLEMENT_DYNAMIC(CDlgParameter, CDialog)

CDlgParameter::CDlgParameter(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CDlgParameter, pParent)
	, m_nThreshold(0)
{
	m_pParent = pParent;
}

CDlgParameter::~CDlgParameter()
{
}

void CDlgParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_THRESHOLD, m_nThreshold);
}


BEGIN_MESSAGE_MAP(CDlgParameter, CDialog)
END_MESSAGE_MAP()



// CDlgParameter 메시지 처리기

int CDlgParameter::GetThresholdValue()
{
	if(m_nThreshold < 0 && m_nThreshold > 255)
		m_nThreshold = 128;

	return m_nThreshold;
}

BOOL CDlgParameter::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.


	// 키가 > GetDlgItem에서 눌렸는지 확인
	if(pMsg->message == WM_KEYDOWN && pMsg->hwnd == GetDlgItem(IDC_EDIT_THRESHOLD)->m_hWnd)
	{
		if(pMsg->wParam == VK_RETURN)
		{
			UpdateData(true);

			CStudy01Dlg* pDlg = (CStudy01Dlg*)m_pParent;

			pDlg->SetThresholdData(m_nThreshold);
			pDlg->m_pDlgParameter->ShowWindow(SW_HIDE);
			pDlg->m_pDlgImage->ShowWindow(SW_SHOW);


			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}
