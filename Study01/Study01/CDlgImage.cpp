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
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CDialog 메시지 처리기


void CDlgImage::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 여기에 메시지 처리기 코드를 추가합니다.
					   // 그리기 메시지에 대해서는 CDialog::OnPaint()을(를) 호출하지 마십시오.

	DrawImage();
}


void CDlgImage::DrawImage()
{
	// Image Data 출력 부분..

	CStatic* staticSize = (CStatic*)GetDlgItem(IDC_STATIC_IMAGE);
	CClientDC dc(staticSize);

	CRect cRect;

	staticSize->GetClientRect(cRect);

	if(m_ImgFile != NULL)
	{
		float fW = (float)m_ImgFile.GetWidth();
		float fH = (float)m_ImgFile.GetHeight();


		float fRectW = cRect.right - cRect.left;
		float fRectH = cRect.bottom - cRect.top;

		float fRect_rate = fRectW / fRectH;
		float fImg_rate = fW / fH;


		// 비율 조정을 가로 중심인지,, 세로 중심인지,,
		int nPrioity_range =
			((fImg_rate > fRect_rate && fImg_rate < 1) || (fImg_rate < fRect_rate && fImg_rate >= 1)) ? 1 : 0;

		if(nPrioity_range)
			fRectW = fRectH * fImg_rate;
		else
			fRectH = fRectW / fImg_rate;


		// size 재정의
		cRect.left = 0;
		cRect.right = (int)fRectW;
		cRect.top = 0;
		cRect.bottom = (int)fRectH;


		dc.SetStretchBltMode(COLORONCOLOR);		// COLORONCOLOR : 원본 깨짐 방지
		m_ImgFile.StretchBlt(dc.m_hDC, 0, 0, cRect.right, cRect.bottom);

	//	m_ImgFile.BitBlt(dc.m_hDC, 0, 0, nW, nH, 0, 0);				// 메모리 DC -> 화면 DC로 비트맵 전송 func
	//	m_ImgFile.StretchBlt(dc.m_hDC, 0, 0, cr.right, cr.bottom);	// DC size에 맞추어 Image Data 출력 (비율 깨짐)


	}

}


void CDlgImage::Binarization(int nThreshold)
{
	if(m_ImgFile != NULL)
	{
		// GetPixelAddress()
		// Image 정보 중 x,y 위치의 pixel Data (Gray Value) 가져옴.
		unsigned char* fm = (unsigned char*)m_ImgFile.GetPixelAddress(0, m_ImgFile.GetHeight() - 1);

		int nW = m_ImgFile.GetWidth();
		int nH = m_ImgFile.GetHeight();

		/*int nThreshold =  128/ *70* /;*/

		for(int j = 0; j < nH; j++)
		{
			for(int i = 0; i < nW; i++)
			{
				// 이미지의 첫 시작점 기준에서...
				// 첫번째 j(col - y)부터 i(row - x) 만큼 한칸씩 이동하며
				// 해당 pixel 위치의 주소값 temp에 담기
				unsigned char* fmTemp;
				fmTemp = fm + j * nW + i;

				// 이진화
				if(*fmTemp < nThreshold)
					*fmTemp = 0;
				else
					*fmTemp = 0xff;

			}
		}
	}

}

void CDlgImage::Centroid()
{
	if(m_ImgFile != NULL)
	{
		unsigned char* fm = (unsigned char*)m_ImgFile.GetPixelAddress(0, m_ImgFile.GetHeight() - 1);

		int nW = m_ImgFile.GetWidth();
		int nH = m_ImgFile.GetHeight();

		int nXsum = 0;
		int nYsum = 0;
		int nCount = 0;

		for(int j = 0; j < nH; j++)
		{
			for(int i = 0; i< nW; i++)
			{
				
				unsigned char* fmTemp;
				fmTemp = fm + j * nW + i;
				if(*fmTemp == 0 /*0xff*/)
				{
					nXsum += i;
					nYsum += j;
					nCount++;
				}
			}
		}
		
		// 무게중심
		// Centroid = ( X / count , Y / count)
		if(nCount > 0)
		{
			for(int i = -10; i < 11; i++)
			{
				unsigned char* fmTemp;
				fmTemp = fm + nYsum / nCount * nW + nXsum / nCount + i;
				*fmTemp = 0x3f;	// gray color
			}	// x축

			for(int i = -10; i < 11; i++)
			{
				unsigned char* fmTemp;
				fmTemp = fm + nYsum / nCount * nW + nXsum / nCount + i * nW;
				*fmTemp = 0x3f;	// gray color
			}	// y축
		}
	}

}
