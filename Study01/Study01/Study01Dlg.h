
// Study01Dlg.h: 헤더 파일
//

#pragma once

#include "CtrlButtonST.h"
#include "Label.h"
#include "ini.h" 

#include "CDlgImage.h"
#include "CDlgParameter.h"


// CStudy01Dlg 대화 상자
class CStudy01Dlg : public CDialogEx
{
// 생성입니다.
public:
	CStudy01Dlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDY01_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnDestroy();

	DECLARE_MESSAGE_MAP()


public:
	bool m_bTest = false;

	CCtrlButtonST m_btnDlgNew;
	double m_dNum;
	CLabel m_lblNum;

	CDlgImage* m_pDlgImage;
	CDlgParameter* m_pDlgParameter;
	
public:
	afx_msg void OnBnClickedButtonNew();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButtonImage();
	afx_msg void OnBnClickedButtonParameter();


public:
	void InitButton(CCtrlButtonST* pButton);
	void InitLabel(CLabel* pLabel);
	void InitDialog();
	void SetDlgView(int nMode);

	void UpdateIni(BOOL bLoad);
	
	
};
