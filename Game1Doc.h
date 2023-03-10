
// Game1Doc.h : interface of the CGame1Doc class
//


#pragma once
#include <afx.h>
#include "CSameGameBoard.h"


class CGame1Doc : public CDocument
{
protected: // create from serialization only
	CGame1Doc() noexcept;
	virtual ~CGame1Doc();
	DECLARE_DYNCREATE(CGame1Doc);
	

// Attributes
public:

// Operations
public:
	/*Funciones para acceder al tablero de juego*/
	COLORREF GetBoardSpace(int row, int col) { return m_board.GetBoardSpace(row, col); }
	void DeleteBoard(void) { m_board.DeleteBoard(); }
	void SetupBoard(void) { m_board.SetupBoard(); }
	int GetWidth(void) { return m_board.GetWidth(); }
	int GetHeight(void) { return m_board.GetHeith(); }
	int GetColumns(void) { return m_board.GetColumns(); }
	int GetRows(void) { return m_board.GetRows(); }
	bool IsGameOver() { return m_board.IsGameOver(); }
	int DeleteBlocks(int row, int col) { return m_board.DeleteBlocks(row, col); }
	int GetRemainingCoutn() { return m_board.GetRemainingCount(); }
	//int DeleteNeighBorBlock(int row, int col, int color, Direction direction) { return m_board.DeleteNeighBorBlock(row, col, color, direction); }
	int GetNumColors() { return m_board.GetNumColors(); }
	void SetNumColors(int nColors) {
			m_board.setNumsColors(nColors);
			m_board.SetupBoard();	
	};
	void SetWidth(int width) { m_board.SetWidth(width); }
	void SetHeigth(int height) { m_board.SetHeight(height); }
	void SetColumns(int columns) { m_board.SetColumns(columns); }
	void SetRows(int rows) { m_board.SetRows(rows); }
	

// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

protected:
	/*Instanciamos el juego*/
	CSameGameBoard m_board;
// Implementation
public:
	//virtual ~CGame1Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

	// Generated OLE dispatch map functions;

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};

//void CGame1Doc::SetNumColors(int nColors) {
//	m_board.setNumsColors(nColors);
//	m_board.SetupBoard();
//}
