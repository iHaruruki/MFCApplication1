
// MFCApplication1Dlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
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


// CMFCApplication1Dlg ダイアログ



CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
	, m_count(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_count);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CMFCApplication1Dlg::OnBnClickedStart)
	ON_EN_CHANGE(IDC_EDIT1, &CMFCApplication1Dlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// CMFCApplication1Dlg メッセージ ハンドラー

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
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

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CMFCApplication1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CMFCApplication1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCApplication1Dlg::OnBnClickedStart()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。
	CWnd *cwdPict = GetDlgItem(IDC_PICTURE);	// ピクチャボックスの ID を取得
	CDC *dcPict = cwdPict->GetDC();				// デバイス・コンテキストの取得

	//ピクチャーボックスをクリア
	CRect rect;
	cwdPict->GetClientRect(&rect);
	dcPict->FillSolidRect(&rect, RGB(255, 255, 255));

	COLORREF color = RGB(0, 0, 0);				// 色(黒)の設定

	// ペンの設定
	CPen* oldPen;
	CPen newPen(PS_SOLID, 1, RGB(0, 255, 255)); // 白色のペン

	int		startX = 50, startY = 80;	// 開始点
	int		endX = 250, endY = 170;		// 終了点
	double moveX, moveY;				// 移動量
	int loop; // 繰り返し用変数

	UpdateData(TRUE); // データの更新

	// 1 回の移動量
	moveX = (endX - startX) / (double)m_count;
	moveY = (endY - startY) / (double)m_count;

	dcPict->Ellipse(startX - 10, startY - 10, startX + 10, startY + 10);

	for (loop = 0; loop < m_count; loop++) {
		// 前の円を消す
		oldPen = dcPict->SelectObject(&newPen);	 // 古いペンを保存して新しいペンに変える
		dcPict->Ellipse(startX + moveX * loop - 10, startY + moveY * loop - 10,
			startX + moveX * loop + 10, startY + moveY * loop + 10);

		// 次の円を描く
		dcPict->SelectObject(oldPen); // 古いペンに戻す
		dcPict->Ellipse(startX + moveX * (loop + 1) - 10, startY + moveY * (loop + 1) - 10,
			startX + moveX * (loop + 1) + 10, startY + moveY * (loop + 1) + 10);

		Sleep(100); // 100ms 停止する
	}
	UpdateData(FALSE); // データの更新

	newPen.DeleteObject(); // 新しいペンを捨てる
}


void CMFCApplication1Dlg::OnEnChangeEdit1()
{
	// TODO: これが RICHEDIT コントロールの場合、このコントロールが
	// この通知を送信するには、CDialogEx::OnInitDialog() 関数をオーバーライドし、
	// CRichEditCtrl().SetEventMask() を関数し呼び出します。
	// OR 状態の ENM_CHANGE フラグをマスクに入れて呼び出す必要があります。
	/*UpdateData(TRUE);

	m_count = GetDlgItemInt(IDC_EDIT1);

	UpdateData(FALSE);*/
	// TODO: ここにコントロール通知ハンドラー コードを追加してください。
}
