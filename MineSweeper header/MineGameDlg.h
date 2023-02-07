
// MineGameDlg.h: 헤더 파일
//

#pragma once


// CMineGameDlg 대화 상자
class CMineGameDlg : public CDialogEx
{
private:
	//가로 항목의 개수, 세로 항목의 개수, 지뢰의 개수
	int m_cx, m_cy, m_mine_count;
	//지뢰가 생성된 정보, 사용자가 체크한 위치 정보
	char* mp_mine_table, * mp_check_table;
	//게임 시작 여부(시작:1, 중지:0)
	char m_start_flag;
	//지뢰 숫자를 표시할 때 사용할 글꼴
	CFont m_font;

private:
	void CreateMineTable();

	void DeleteMineTable();

	void ShowCurrentState(CDC* ap_dc, char* ap_mine_table, char* ap_check_table);

// 생성입니다.
public:
	CMineGameDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MINEGAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnDestroy();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
