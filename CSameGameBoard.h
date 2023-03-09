#pragma once
class CSameGameBoard
{
public:
	enum Direction
	{
		DIRECCTION_UP, DIRECTION_DOWN, DIRECTION_LEFT, DIRECTION_RIGHT
	};
	/*Default constructor*/
	CSameGameBoard(void);
	/*Destructor*/
	~CSameGameBoard(void);
	/*Function to randomly setup the board*/
	void SetupBoard(void);
	/*Get the color at a particular location*/
	COLORREF GetBoardSpace(int row, int col);
	/*Accesor functions to get board size information*/
	int GetWidth(void)const { return m_nWidth; }
	int GetHeith(void)const { return m_nHeight; }
	int GetColumns(void)const { return m_nColumns; }
	int GetRows(void)const { return m_nRows; }
	/*Function to delete the board and free memory*/
	void DeleteBoard(void);
	//Funcion para el game over
	bool IsGameOver(void)const;
	//Bloques restantes
	int GetRemainingCount(void) { return m_nRemaining; }
	//Funcion para borrar los bloques adyacentes
	int DeleteBlocks(int row, int col);
	void CompactBoard(void);
	int DeleteNeighBorBlock(int row, int col, int color, Direction direction);
	int GetNumColors(void) { return m_nColors; }
	void setNumsColors(int nColors) { m_nColors = (nColors >= 3 && nColors <= 7) ? nColors : m_nColors; }
	void SetWidth(int nWidth) { m_nWidth = (nWidth >= 3) ? nWidth : 3; }
	void SetHeight(int nHeight) { m_nHeight = (nHeight > 3) ? nHeight : 3; }
	void SetColumns(int nColumns) { m_nColumns = (nColumns >= 5) ? nColumns : 5; }
	void SetRows(int nRows) { m_nRows = (nRows >= 5) ? nRows : 5; }



private:
	/*Function to create the board and allocate memory*/
	void CreateBoard(void);
	/*2D Array pointer*/
	int** m_arrBoard;
	/*List of colors, 0 is background and 1-3 are piece colors*/
	COLORREF m_arrColors[8];
	/*Board size information*/
	int m_nColumns;
	int m_nRows;
	int m_nHeight;
	int m_nWidth;
	int m_nRemaining;
	int m_nColors;
	
};

