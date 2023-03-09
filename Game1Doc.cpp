// Game1Doc.cpp : implementation of the CGame1Doc class
//

#include "pch.h"
#include "framework.h"
#include "Game1.h"
#include "Game1Doc.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Game1.h"
#endif


#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CGame1Doc

IMPLEMENT_DYNCREATE(CGame1Doc, CDocument)

BEGIN_MESSAGE_MAP(CGame1Doc, CDocument)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CGame1Doc, CDocument)
END_DISPATCH_MAP()


//Constructor y destructor
//CGame1Doc::CGame1Doc() {}
//CGame1Doc::~CGame1Doc(){}



// Note: we add support for IID_IGame1 to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the
//  dispinterface in the .IDL file.

// {cde89a96-0efb-4c4c-b632-8c57db574e3a}
static const IID IID_IGame1 =
{0xcde89a96,0x0efb,0x4c4c,{0xb6,0x32,0x8c,0x57,0xdb,0x57,0x4e,0x3a}};

BEGIN_INTERFACE_MAP(CGame1Doc, CDocument)
	INTERFACE_PART(CGame1Doc, IID_IGame1, Dispatch)
END_INTERFACE_MAP()


// CGame1Doc construction/destruction

CGame1Doc::CGame1Doc() noexcept
{
	// TODO: add one-time construction code here

	EnableAutomation();

	AfxOleLockApp();
}

CGame1Doc::~CGame1Doc()
{
	AfxOleUnlockApp();
}

BOOL CGame1Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)
	//Iniciar o resetear el tablero de juego
	m_board.SetupBoard();

	return TRUE;
}



// CGame1Doc serialization

void CGame1Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CGame1Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CGame1Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CGame1Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CGame1Doc diagnostics

#ifdef _DEBUG
void CGame1Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGame1Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG




// CGame1Doc commands
