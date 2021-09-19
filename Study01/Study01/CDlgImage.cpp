// CDialog.cpp: 구현 파일
//

#include "pch.h"
#include "Study01.h"
#include "CDlgImage.h"
#include "afxdialogex.h"


// CDialog 대화 상자

IMPLEMENT_DYNAMIC(CDlgImage, CDialog)

CDlgImage::CDlgImage(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_CDlgImage, pParent)
{

}

CDlgImage::~CDlgImage()
{
}

void CDlgImage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgImage, CDialog)
END_MESSAGE_MAP()


// CDialog 메시지 처리기
