
// Game1View.h : interface of the CGame1View class
//

#pragma once


class CGame1View : public CView
{
protected: // create from serialization only
	CGame1View() noexcept;
	DECLARE_DYNCREATE(CGame1View)

// Attributes
public:
	CGame1Doc* GetDocument() const;

	void OnInitialUpdate();

// Operations
public:

// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//void OnLButtonDown(UINT nFlags, CPoint point);
protected:

// Implementation
public:
	virtual ~CGame1View();
	void ResizeWindow();
	
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	void UpdateLevelColorCount(int numColor, CCmdUI* pCmdUi);
	void SetColorCount(int numColors);
	//void SetupBlock(bool setup);
	/*Para cambiar la dificultad*/
	afx_msg void OnLevel3level();
	afx_msg void OnLevel4level();
	afx_msg void OnLevel5();
	afx_msg void OnLevel6color();
	afx_msg void OnLevel7colors();
	/*Funciones para actualizar el menu de opciones*/
	afx_msg void OnUpdateLevel3level(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevel4level(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevel5(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevel6color(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLevel7colors(CCmdUI* pCmdUI);
	/*Establecer los numeros*/
	//afx_msg void OnSetupBlockcount();
	//afx_msg void OnSetupBlocksize();
	afx_msg void OnSetupBlocksize();
	afx_msg void OnSetupBlockcount();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in Game1View.cpp
inline CGame1Doc* CGame1View::GetDocument() const
   { return reinterpret_cast<CGame1Doc*>(m_pDocument); }
#endif

