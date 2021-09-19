﻿#pragma once

#include "CDlgParameter.h"

// CDialog 대화 상자

class CDlgImage : public CDialog
{
	DECLARE_DYNAMIC(CDlgImage)

public:
	CDlgImage(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CDlgImage();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgImage };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()

public:
	CImage m_ImgFile;


public:
	void DrawImage();
	void Binarization(int nThreshold);
	void Centroid();

public:
	afx_msg void OnPaint();
};
