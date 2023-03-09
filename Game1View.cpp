
// Game1View.cpp : implementation of the CGame1View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Game1.h"
#endif

#include "Game1Doc.h"
#include "Game1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGame1View

IMPLEMENT_DYNCREATE(CGame1View, CView)

BEGIN_MESSAGE_MAP(CGame1View, CView)
	ON_COMMAND(ID_LEVEL_3LEVEL, &CGame1View::OnLevel3level)
	ON_COMMAND(ID_LEVEL_4LEVEL, &CGame1View::OnLevel4level)
	ON_COMMAND(ID_LEVEL_5, &CGame1View::OnLevel5)
	ON_COMMAND(ID_LEVEL_6COLOR, &CGame1View::OnLevel6color)
	ON_COMMAND(ID_LEVEL_7COLORS, &CGame1View::OnLevel7colors)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_3LEVEL, &CGame1View::OnUpdateLevel3level)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_4LEVEL, &CGame1View::OnUpdateLevel4level)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_5, &CGame1View::OnUpdateLevel5)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_6COLOR, &CGame1View::OnUpdateLevel6color)
	ON_UPDATE_COMMAND_UI(ID_LEVEL_7COLORS, &CGame1View::OnUpdateLevel7colors)
END_MESSAGE_MAP()

// CGame1View construction/destruction

CGame1View::CGame1View() noexcept
{
	// TODO: add construction code here

}

CGame1View::~CGame1View()
{
}

BOOL CGame1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGame1View drawing

void CGame1View::OnDraw(CDC* pDC)
{
	CGame1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	//Salva el estado actual del dispositivo
	int nDCSave = pDC->SaveDC();
	CRect rcClient;
	GetClientRect(&rcClient);
	COLORREF clr = pDoc->GetBoardSpace(-1, 1);
	pDC->FillSolidRect(&rcClient, clr);
	CBrush br;
	br.CreateStockObject(HOLLOW_BRUSH);
	CBrush* pbrOld = pDC->SelectObject(&br);
	for (int row = 0; row < pDoc->GetRows(); row++) {
		for (int col = 0; col < pDoc->GetColumns(); col++) {
			clr = pDoc->GetBoardSpace(row, col);
			CRect rcBlock;
			rcBlock.top = row * pDoc->GetHeight();
			rcBlock.left = col * pDoc->GetWidth();
			rcBlock.right = rcBlock.left + pDoc->GetWidth();
			rcBlock.bottom = rcBlock.top + pDoc->GetHeight();
			pDC->FillSolidRect(&rcBlock, clr);
			pDC->Rectangle(&rcBlock);
		}
	}
	//Restore the device context
	pDC->RestoreDC(nDCSave);
	br.DeleteObject();
	// TODO: add draw code for native data here
}


// CGame1View diagnostics

#ifdef _DEBUG
void CGame1View::AssertValid() const
{
	CView::AssertValid();
}

void CGame1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGame1Doc* CGame1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGame1Doc)));
	return (CGame1Doc*)m_pDocument;
}
#endif //_DEBUG


void CGame1View::OnInitialUpdate() {
	CView::OnInitialUpdate();
	ResizeWindow();
}

void CGame1View::ResizeWindow() {
	//Primero un puntero hacia el documento
	CGame1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) {
		return;
	}
	CRect rcClient, rcWindow;
	GetClientRect(&rcClient);
	GetParentFrame()->GetWindowRect(&rcWindow);
	//Calculamos la diferencia
	int nWidthDiff = rcWindow.Width() - rcClient.Height();
	int nHeightDiff = rcWindow.Width() - rcClient.Width();
	//Cambiar el tamaño son el game board
	rcWindow.right = rcWindow.left + pDoc->GetWidth() * pDoc->GetColumns() + nWidthDiff;
	rcWindow.bottom = rcWindow.top + pDoc->GetHeight() * pDoc->GetRows() + nHeightDiff;
	GetParentFrame()->MoveWindow(&rcWindow);

}

void CGame1View::OnLButtonDown(UINT nFlags, CPoint point) {
	CView::OnLButtonDblClk(nFlags, point);
	CGame1Doc* pDoc = GetDocument();
	if (!pDoc) {
		return;
	}
	//Obtener donde hemos pinchado
	int row = point.y / pDoc->GetHeight();
	int col = point.x / pDoc->GetWidth();
	//Borramos los bloques de la vista
	int count = pDoc->DeleteBlocks(row,col);
	if (count > 0) {
		Invalidate();
		UpdateWindow();
		if (pDoc->IsGameOver()) {
			int remaining = pDoc->GetRemainingCoutn();
			CString message;
			message.Format(_T("No more moves left\nBlocks remaining: %d"),remaining);
			MessageBox(message, _T("Game Over"), MB_OK || MB_ICONINFORMATION);
		}
	}	
	
	//CView::OnLButtonDown(nFlags, point);
}
// CGame1View message handlers

void CGame1View::SetColorCount(int numColors) 
{
	CGame1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) {
		return;
	}
	pDoc->SetNumColors(numColors);
	Invalidate();
	UpdateWindow();
}

void CGame1View::UpdateLevelColorCount(int numColor,CCmdUI *pCmdUi) {
	CGame1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) {
		return;
	}
	pCmdUi->SetCheck(pDoc->GetNumColors() == numColor);
}

void CGame1View::OnLevel3level()
{
	// TODO: Add your command handler code here
	SetColorCount(3);
}


void CGame1View::OnLevel4level()
{
	// TODO: Add your command handler code here
	SetColorCount(4);
}


void CGame1View::OnLevel5()
{
	// TODO: Add your command handler code here
	SetColorCount(5);
}


void CGame1View::OnLevel6color()
{
	// TODO: Add your command handler code here
	SetColorCount(6);
}


void CGame1View::OnLevel7colors()
{
	// TODO: Add your command handler code here
	SetColorCount(7);
}


void CGame1View::OnUpdateLevel3level(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	UpdateLevelColorCount(3, pCmdUI);
}


void CGame1View::OnUpdateLevel4level(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	UpdateLevelColorCount(4, pCmdUI);
}


void CGame1View::OnUpdateLevel5(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	UpdateLevelColorCount(5, pCmdUI);
}


void CGame1View::OnUpdateLevel6color(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	UpdateLevelColorCount(6, pCmdUI);
}


void CGame1View::OnUpdateLevel7colors(CCmdUI* pCmdUI)
{
	// TODO: Add your command update UI handler code here
	UpdateLevelColorCount(7, pCmdUI);
}
