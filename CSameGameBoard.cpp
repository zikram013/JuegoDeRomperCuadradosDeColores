#include "pch.h"
#include "CSameGameBoard.h"
//#include "StdAfx.h"


//Constructor
CSameGameBoard::CSameGameBoard(void) :m_arrBoard(NULL), m_nColumns(15), m_nRows(15), m_nHeight(35), m_nWidth(35),m_nRemaining(0),m_nColors(3) {
	m_arrColors[0] = RGB(0, 0, 0);
	m_arrColors[1] = RGB(255, 0, 0);
	m_arrColors[2] = RGB(255, 255, 64);
	m_arrColors[3] = RGB(0, 0, 255);
	m_arrColors[4] = RGB(0, 255, 0);
	m_arrColors[5] = RGB(0, 255, 255);
	m_arrColors[6] = RGB(255, 0, 128);
	m_arrColors[7] = RGB(0, 64, 0);
	SetupBoard();
}

//Destructor
CSameGameBoard::~CSameGameBoard(void) {
	//Simply delete the board
	DeleteBoard();
}

//Opciones de tablero de juego
void CSameGameBoard::SetupBoard(void) {
	if (m_arrBoard == NULL) {
		CreateBoard();
	}
	for (int row = 0; row < m_nRows; row++) {
		for (int col = 0; col < m_nColumns; col++) {
			m_arrBoard[row][col] = (rand() % m_nColors) + 1;
		}
	}
	m_nRemaining = m_nRows * m_nColumns;
}

//Colores del juego
COLORREF CSameGameBoard::GetBoardSpace(int row, int col) {
	//Check the bounds of array
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns) {
		return m_arrColors[0];
	}
	return m_arrColors[m_arrBoard[row][col]];
}

void CSameGameBoard::DeleteBoard(void) {
	//Comprobacion para no borrar un tablero que es NULL
	if (m_arrBoard != NULL) {
		for (int row = 0; row < m_nRows; row++) {
			if (m_arrBoard[row] != NULL) {
				//Delete each row first
				delete[]m_arrBoard[row];
				m_arrBoard[row] = NULL;
			}
		}
		//Finalmente borramos el array de las filas
		delete[]m_arrBoard;
		m_arrBoard = NULL;
	}
}

bool CSameGameBoard::IsGameOver(void) const
{
	//columna por columna y de izquierda a derecha
	for (int col = 0; col < m_nColumns; col++) {
		for (int row = m_nRows - 1; row >= 0; row--) {
			int nColor = m_arrBoard[row][col];
			if (nColor == 0) {
				break;
			}
			else {
				if (row - 1 >= 0 && m_arrBoard[row - 1][col] == nColor) {
					return false;
				}
				else if (col + 1 < m_nColumns && m_arrBoard[row][col + 1] == nColor) {
					return false;
				}
			}
		}
	}
	return true;
}

int CSameGameBoard::DeleteBlocks(int row, int col)
{
	//Nos aseguramos que tanto las filas como las columnas sean valores validos
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns) {
		return -1;
	}
	//No debemos borrar los bloques el background que crean el tablero de juego
	int nColor = m_arrBoard[row][col];
	if (nColor == 0) {
		return -1;
	}
	//Comprobamos que las casillas adyacentes tengan el mismo color
	int nCount = -1;
	if ((row - 1 >= 0 && m_arrBoard[row - 1][col] == nColor) ||
		(row + 1 < m_nRows && m_arrBoard[row + 1][col] == nColor) ||
		(col - 1 >= 0 && m_arrBoard[row][col - 1] == nColor) ||
		(col + 1 < m_nColumns && m_arrBoard[row][col + 1] == nColor)) {
		//llamadas recursivas
		m_arrBoard[row][col] = 0;
		nCount = 1;
		//LLamadas recursiva para abajo
		nCount += DeleteNeighBorBlock(row - 1, col, nColor, DIRECTION_DOWN);
		//Llamada recursiva para arriba
		nCount += DeleteNeighBorBlock(row + 1, col, nColor, DIRECCTION_UP);
		//Llamada recuriva para la derecha
		nCount += DeleteNeighBorBlock(row, col - 1, nColor, DIRECTION_RIGHT);
		//Llamada recurisva para la izquierda
		nCount += DeleteNeighBorBlock(row, col + 1, nColor, DIRECTION_LEFT);
		CompactBoard();
		m_nRemaining -= nCount;
	}
	return nCount;
}

void CSameGameBoard::CompactBoard(void)
{
	//Primer movimiento siempre es hacia abajo al ocupar todo el espacion la ventana
	for (int col = 0; col < m_nColumns; col++) {
		int nNextEmptyRow = m_nRows - 1;
		int nNextOccupiedRow = nNextEmptyRow;
		while (nNextOccupiedRow >= 0 && nNextEmptyRow>=0) {
			while (nNextEmptyRow >= 0 && m_arrBoard[nNextEmptyRow][col] != 0) {
				nNextEmptyRow--;
			}
			if (nNextEmptyRow >= 0) {
				nNextOccupiedRow = nNextEmptyRow - 1;
				while (nNextOccupiedRow >= 0 && m_arrBoard[nNextOccupiedRow][col] == 0) {
					nNextOccupiedRow--;
				}
				if(nNextOccupiedRow>=0){
					m_arrBoard[nNextEmptyRow][col] = m_arrBoard[nNextOccupiedRow][col];
					m_arrBoard[nNextOccupiedRow][col] = 0;
				}
			}
		}
	}
	//Movimiento de izquieda a derecha para cuando se vacian las columnas de derecha a izquierda
	int nNextEmptyCol = 0;
	int nNextOccupiedCol = nNextEmptyCol;
	while (nNextEmptyCol < m_nColumns && nNextOccupiedCol < m_nColumns) {
		//Primer encuentra la primera columna vacia
		while (nNextEmptyCol < m_nColumns && m_arrBoard[m_nRows - 1][nNextEmptyCol] != 0) {
			nNextEmptyCol++;
		}
		if (nNextEmptyCol < m_nColumns) {
			nNextOccupiedCol = nNextEmptyCol + 1;
			while (nNextOccupiedCol < m_nColumns && m_arrBoard[m_nRows - 1][nNextOccupiedCol] == 0) {
				nNextOccupiedCol++;
			}
			if (nNextOccupiedCol < m_nColumns) {
				for (int row = 0; row < m_nRows; row++) {
					m_arrBoard[row][nNextEmptyCol] = m_arrBoard[row][nNextOccupiedCol];
					m_arrBoard[row][nNextOccupiedCol] = 0;
				}
			}
		}
	}
}

int CSameGameBoard::DeleteNeighBorBlock(int row, int col, int color, Direction direction)
{
	int nCount = 1;
	//Comprobamos si esta en el cuadro
	if (row < 0 || row >= m_nRows || col < 0 || col >= m_nColumns) {
		return 0;
	}
	//Comprobamos que sean del mismo color
	if (m_arrBoard[row][col] != color) {
		return 0;
	}
	//Si no puede ir hacia arriba
	if (direction != DIRECCTION_UP) {
		nCount += DeleteNeighBorBlock(row - 1, col, color, DIRECTION_DOWN);
	}
	//Comprobamos que pueda ir hacia abajo
	if (direction != DIRECTION_DOWN) {
		nCount += DeleteNeighBorBlock(row + 1, col, color, DIRECCTION_UP);
	}
	//Izquierda
	if (direction != DIRECTION_LEFT) {
		nCount += DeleteNeighBorBlock(row, col - 1, color, DIRECTION_RIGHT);
	}
	if (direction != DIRECTION_RIGHT) {
		nCount += DeleteNeighBorBlock(row, col + 1, color, DIRECTION_LEFT);
	}
	return nCount;
}

void CSameGameBoard::CreateBoard(void) {
	//If there is already a board, delete it
	if (m_arrBoard != NULL) {
		DeleteBoard();
	}
	//Creamos el array de filas
	m_arrBoard = new int* [m_nRows];
	//Creacion por cada fila
	for (int row = 0; row < m_nRows; row++) {
		m_arrBoard[row] = new int[m_nColumns];
		for (int col = 0; col < m_nColumns; col++) {
			m_arrBoard[row][col] = 0;
		}
	}
}


