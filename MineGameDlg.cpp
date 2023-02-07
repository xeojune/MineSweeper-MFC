
// MineGameDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MineGame.h"
#include "MineGameDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMineGameDlg 대화 상자



CMineGameDlg::CMineGameDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MINEGAME_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//게임과 관련된 정보들을 초기화 한다.
	mp_mine_table = NULL;
	mp_check_table = NULL;
	m_start_flag = 0;
}

void CMineGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMineGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CMineGameDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CMineGameDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON1, &CMineGameDlg::OnBnClickedButton1)
	ON_WM_DESTROY()
	ON_WM_LBUTTONUP()
END_MESSAGE_MAP()


// CMineGameDlg 메시지 처리기

BOOL CMineGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	// 게임에서 사용할 글꼴을 생성한다.
	m_font.CreatePointFont(92, L"굴림");

	//기본값 설정
	SetDlgItemInt(IDC_CX_EDIT, 15);
	SetDlgItemInt(IDC_CY_EDIT, 10);
	SetDlgItemInt(IDC_MINE_COUNT_EDIT, 35);

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

//지뢰 찾기 항목이 출력될 시작 X좌표
#define START_X		220
//지뢰 찾기 항목이 출력될 시작 Y 좌표
#define START_Y		200
//한 개 항목의 폭
#define ITEM_WIDTH	20
//한 개 항목의 높이
#define ITEM_HEIGHT 20

void CMineGameDlg::ShowCurrentState(CDC* ap_dc, char* ap_mine_table, char* ap_check_table)
{
	//문자의 배경색을 투명하게 처리한다.
	ap_dc->SetBkMode(TRANSPARENT);
	//색상만 변경해서 사용하는 브러시 객체를 선택한다.
	ap_dc->SelectStockObject(DC_BRUSH);
	//색상만 변경해서 사용하는 펜 객체를 선택한다.
	ap_dc->SelectStockObject(DC_PEN);
	//기본 펜 색상을 어두운 회색으로 설정한다.
	ap_dc->SetDCPenColor(RGB(128, 128, 128));
	//게임에 사용할 글꼴을 선택한다.
	ap_dc->SelectObject(&m_font);

	RECT r;
	for (int y = 0; y < m_cy; y++)
	{
		for (int x = 0; x < m_cx; x++, ap_mine_table++, ap_check_table++)
		{
			//사용자가 선택한 항목이면 밝은 회색으로 출력하고
			//그렇지 않으면 일반 회색으로 출력한다.
			if (*ap_check_table) ap_dc->SetDCBrushColor(RGB(228, 228, 228));
			else ap_dc->SetDCBrushColor(RGB(192, 192, 192));

			//현재 항목의 위치를 계산해서 r 변수에 저장한다.
			::SetRect(&r, START_X + x * ITEM_WIDTH, START_Y + y * ITEM_HEIGHT, START_X + (x + 1) * ITEM_WIDTH + 1, START_Y + (y + 1) * ITEM_HEIGHT + 1);
			//계산된 좌표에 사각형을 그린다.
			ap_dc->Rectangle(&r);

			if (!m_start_flag || *ap_check_table) { //게임이 끝나면 나머지 숫자랑 폭탄을 다 보여주기 위해
				::DrawTextA(ap_dc->m_hDC, ap_mine_table, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			}
		}
	}
}

void CMineGameDlg::OnPaint()
{
	CPaintDC dc(this);

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
		if (mp_mine_table != NULL)
			ShowCurrentState(&dc, mp_mine_table, mp_check_table);
		//CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMineGameDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMineGameDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	/*CDialogEx::OnOK();*/
}


void CMineGameDlg::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnCancel();
}

void CMineGameDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	DeleteMineTable();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

void CMineGameDlg::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	int cx = GetDlgItemInt(IDC_CX_EDIT);
	int cy = GetDlgItemInt(IDC_CY_EDIT);
	int mine_count = GetDlgItemInt(IDC_MINE_COUNT_EDIT);

	//x축 항목은 최소 5이상 최대 25이하로 설정 가능!
	if (cx < 5 || cx > 25) {
		MessageBox(L"x축 항목의 수는 5개 이상 25개 이하로 설정해야 합니다.",
			L"항목 수 입력 오류!", MB_ICONSTOP);
		return;
	}
	//y축 항목은 최소 5이상 최대 17이하로 설정 가능!
	if (cy < 5 || cy > 17) {
		MessageBox(L"y축 항목의 수는 5개 이상 17개 이하로 설정해야 합니다.",
			L"항목 수 입력 오류!", MB_ICONSTOP);
		return;
	}
	//폭탄 개수는 전체 항목의 최소 20%이상이고 최대 40%이하다.
	int min = (int)(cx * cy * 0.2);
	int max = (int)(cx * cy * 0.4);

	//폭탄의 수가 유효한지 체크한다.
	if (mine_count < min || mine_count > max) {
		CString str;
		str.Format(L"지뢰의 개수는 %d개 이상, %d개 이하로 설정해야 합니다.", min, max);
		MessageBox(str, L"지뢰 수 입력 오류!", MB_ICONSTOP);
		return;
	}

	//게임이 시작되었음을 설정한다.
	m_start_flag = 1;
	//사용자가 입력한 정보를 계속 사용하기 위해 멤버 변수로 옯긴다.
	m_cx = cx;
	m_cy = cy;
	m_mine_count = mine_count;

	
	//마인배치.
	CreateMineTable();

	Invalidate();
	//오목판 그리기
	

}

//마인 배치
void CMineGameDlg::CreateMineTable()
{
	DeleteMineTable();

	int x, y, mine_count;

	char* p_pos;

	mp_mine_table = new char[m_cx * m_cy];
	char* p_table = mp_mine_table;

	mp_check_table = new char[m_cx * m_cy];

	memset(mp_mine_table, 0, m_cx * m_cy);
	memset(mp_check_table, 0, m_cx * m_cy); 

	//폭탄 만들기
	for (mine_count = 0; mine_count < m_mine_count; mine_count++)
	{
		x = rand() % m_cx; //범위
		y = rand() % m_cy;

		p_pos = mp_mine_table + y * m_cx + x;
		if (*p_pos == 0) *p_pos = '*';
		else mine_count--;
	}


	for (y = 0; y < m_cy; y++)
	{
		for (x = 0; x < m_cx; x++)
		{
			if (*p_table == 0)
			{
				mine_count = 0;

				if ((y - 1) >= 0) { //음수가 나오지 않게 체크한다.
					//c위치에서 1번 위치의 주소를 계산한다.
					p_pos = p_table - m_cx - 1;
					//1,2,3번 항목을 체크한다.
					if ((x - 1) >= 0 && *p_pos == '*') mine_count++;
					if (*++p_pos == '*') mine_count++;
					if ((x + 1) < m_cx && *++p_pos == '*') mine_count++;
				}

				//4,5 항목 체크
				if ((x - 1) >= 0 && *(p_table - 1) == '*') mine_count++;
				if ((x + 1) < m_cx && *(p_table + 1) == '*') mine_count++;

				if ((y + 1) < m_cy) {//범위를 벗어나지 않게 체크한다.
					//c위치에서 6번 위치의 주소를 계산한다.
					p_pos = p_table + m_cx - 1;
					//6,7,8번 항목을 체크한다.
					if ((x - 1) >= 0 && *p_pos == '*') mine_count++;
					if (*++p_pos == '*') mine_count++;
					if ((x + 1) < m_cx && *++p_pos == '*') mine_count++;
				}
				*p_table = '0' + mine_count;
			}
			p_table++;

		}
	}
}

void CMineGameDlg::DeleteMineTable()
{
	if (mp_mine_table != NULL) delete[] mp_mine_table;
	if (mp_check_table != NULL) delete[] mp_check_table;
}






void CMineGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (!m_start_flag) return;

	unsigned int x = (point.x - START_X) / ITEM_WIDTH;
	unsigned int y = (point.y - START_Y) / ITEM_HEIGHT;

	//계산된 위치가 유효한지 체크한다.
	if (x < (unsigned int)m_cx && y < (unsigned int)m_cy)
	{
		//체크할 위치를 계산한다.
		unsigned int index = y * m_cx + x;

		if (*(mp_check_table + index) == 0)
		{
			if (*(mp_mine_table + index) == '*')
			{
				m_start_flag = 0;
				Invalidate();
				MessageBox(L"폭탄을 선택했습니다!!", L"게임 종료", MB_ICONSTOP);
			}
			else
			{
				//선택했음을 설정한다.
				*(mp_check_table + index) = 1;
				CClientDC dc(this);
				//선택 정보를 반영하여 지뢰 정보를 출력한다.
				ShowCurrentState(&dc, mp_mine_table, mp_check_table);
			}

		}
	}

	CDialogEx::OnLButtonUp(nFlags, point);
}
