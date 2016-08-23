/************************************************************************
* Class: Array2D
*
* Purpose: This class represents a 2 dimensional dynamic array that can 
*		have any dimension. It is templated so that it can allow any datatype 
*		for the array.
*
* Manager functions:	
* 	Array2D()
* 		Constructs a 0x0 2D array with a starting index of 0 	
*	Array2D(int row, int col)
*		Constructs a row x col 2D array
*	Array2D(Array2D const& copy)
*		Copy constructor
*	operator=(Array2D const& rhs)
*		Overloaded operator= function
*	~Array2D()
*		Destructor, resets the object to initial conditions
*
* Methods:		
*	operator[](int index)
*		Overloaded bracket operator used to resolve addresses at given index. 
*		Takes into consideration start_index. Used for assignment and value 
*		retrieval. Returns a Row<T>. Always called with double subscript.
*	getRow()
*		Returns the number of rows in the array.
*	setRow(int rows)
*		Sets the number of rows in the array. Resizes as necessary.
*	getColumn()
*		Returns the number of columns in the array.
*	setColumn(int columns)
*		Sets the number of columns in the array. Resizes as necessary.
*	Select(int row, int column)
*		Used by Row::operator[] to aid in resolving double subscripts.
*************************************************************************/
#pragma once
#include "Row.h"
#include "Exception.h"

template <class T>
class Array2D{
	private:
		T** m_array;
		int m_row;
		int m_col;
	public:
		Array2D();
		Array2D(int row, int col);
		Array2D(Array2D const& copy);
		~Array2D();

		Array2D& operator=(Array2D const& rhs);
		Row<T> operator[](int index);
		const Row<T> operator[](int index) const;
		int getRow() const;
		void setRow(int rows);
		int getColumn() const;
		void setColumn(int columns);
		T& Select(int row, int column) const;
};

/**********************************************************************	
* Array2D()
* Purpose: This function is the default constructor for the Array2D class. 
*		It defaults to a 0x0 array.
*
* Entry:
*	None.
*
* Exit: Constructs a Array2D object with the above default size.
************************************************************************/
template <class T>
Array2D<T>::Array2D() : m_row(0), m_col(0), m_array(0){

}

/**********************************************************************	
* Array2D(int row, int col)
* Purpose: This function is the 2arg constructor for the Array2D class. 
*		It sets up the array with row rows and col columns.
*
* Entry:
*	Params:
*		row: (int) The desired number of rows.
*		col: (int) The desired number of cols.
*
* Exit: Constructs a Array2D object with the given size.
************************************************************************/
template <class T>
Array2D<T>::Array2D(int row, int col) : m_row(row), m_col(col){
	m_array = new T*[row];

	for(int r=0; r<row; ++r){
		m_array[r] = new T[col];
	}
}

/**********************************************************************	
* Array2D(Array2D<T> copy)
* Purpose: This function is the copy constructor for the Array2D class. 
*		It constructs an array of the same dimensions and the same 
*		content as copy.
*
* Entry:
*	Params:
*		copy: (Array2D) The array to copy from.
*
* Exit: Constructs a Array2D object with the same content/dimensions as 
*		the passed in Array2D.
************************************************************************/
template <class T>
Array2D<T>::Array2D(Array2D const& copy) : m_row(0), m_col(0), m_array(0){
	
	// check if array needs to be resized, and if so, resize appropriately
	if(copy.m_row != m_row){
		setRow(copy.m_row);
	}

	if(copy.m_col != m_col){
		setColumn(copy.m_col);
	}

	// now, copy the data over
	for(int r=0; r<copy.m_row; ++r){
		for(int c=0; c<copy.m_col; ++c){
			m_array[r][c] = copy.m_array[r][c];
		}
	}
}

/**********************************************************************	
* ~Array2D()
* Purpose: This function is the destructor for the Array2D class. It 
*		resets the row and col to 0 as well as zeros out the contents 
*		of the array.
*
* Entry:
*	None.
*
* Exit: Constructs a Array2D object with the above default size.
************************************************************************/
template <class T>
Array2D<T>::~Array2D(){
	// first, go through and delete each column array
	for(int r=0; r<m_row; ++r){
		delete m_array[r];
	}
	// then delete the row array
	delete [] m_array;
	
	m_row = 0;
	m_col = 0;
}

/**********************************************************************	
* operator=(Array2D<T> rhs)
* Purpose: This function is the operator= for Array2D. It sets the left 
*		hand object with the same contents and dimensions as the right
*		hand side Array2D.
*
* Entry:
*	Params:
*		rhs: (Array2D<T>) The right hand array to assign values from.
*
* Exit: Sets the Array2D object to the same contents/dimensions as the 
*		right hand Array2D object.
************************************************************************/
template <class T>
Array2D<T>& Array2D<T>::operator=(Array2D<T> const& rhs){

	// check if dimensions need to change and if so, resize accordingly
	if(rhs.m_row != m_row){
		setRow(rhs.m_row);
	}

	if(rhs.m_col != m_col){
		setColumn(rhs.m_col);
	}
	
	// now, copy the data over
	for(int r=0; r<rhs.m_row; ++r){
		for(int c=0; c<rhs.m_col; ++c){
			m_array[r][c] = rhs.m_array[r][c];
		}
	}

	return *this;
}

/**********************************************************************	
* Row<T> operator[](int index)
* Purpose: This function takes an index and returns a row object for the 
*		requested row. It should never be called without having a second 
*		subscript.
*
* Entry:
*	Params:
*		index: (int) The requested row index.
*
* Exit: Returns a Row<T> object of the requested row.
************************************************************************/
template <class T>
Row<T> Array2D<T>::operator[](int index){
	if(index >= m_row){
		throw Exception("Index out of bounds: Row index too high.");
	}else if(index < 0){
		throw Exception("Index out of bounds: Row index too low.");
	}
	return Row<T>(*this, index);
}
template <class T>
const Row<T> Array2D<T>::operator[](int index) const{
	if(index >= m_row){
		throw Exception("Index out of bounds: Row index too high.");
	}else if(index < 0){
		throw Exception("Index out of bounds: Row index too low.");
	}
	return (const Row<T>(*this, index));
}

/**********************************************************************	
* int getRow()
* Purpose: This function returns the number of rows in the Array.
*
* Entry:
*	None.
*
* Exit: Returns the number of rows in the array.
************************************************************************/
template <class T>
int Array2D<T>::getRow() const{
	return m_row;
}

/**********************************************************************	
* setRow(int rows)
* Purpose: Sets the array's number of rows. Will resize the m_array member 
*		as needed. 
*
* Entry:
*	Params:
*		rows: (int) Number of desired rows. Must be positive.
*
* Exit: m_rows is set and m_array is resized to accomodate the new size.
************************************************************************/
template <class T>
void Array2D<T>::setRow(int rows){
	if(rows < 0){
		throw Exception("Cannot set a negative row length.");
	}

	if(rows != m_row){
		T** new_array = new T*[rows];

		int last_index = 0;
		if(rows > m_row){
			// enlarging array, copy data up to current amount of rows
			last_index = m_row;
		}else if(rows < m_row){
			// shrinking array, copy data up to new number of rows
			last_index = rows;
		}

		for(int r=0; r<last_index; ++r){
			new_array[r] = m_array[r]; // only need to copy over the address of the col arrays as column isn't changing
		}

		// if array is being shrunk, this loop will never run.
		for(int r=last_index; r<rows; ++r){
			// if there is additional rows being added, allocate blank arrays for them
			new_array[r] = new T[m_col];
		}

		m_row = rows;

		if(m_array){
			for(int r=0; r<m_row; ++r){
				delete m_array[r];
			}
			delete [] m_array;
		}
		m_array = new_array;
	}
}

/**********************************************************************	
* int getColumn()
* Purpose: This function returns the number of columns in the Array.
*
* Entry:
*	None.
*
* Exit: Returns the number of columns in the array.
************************************************************************/
template <class T>
int Array2D<T>::getColumn() const{
	return m_col;
}

/**********************************************************************	
* setColumn(int columns)
* Purpose: Sets the array's number of columns. Will resize the m_array member 
*		as needed. 
*
* Entry:
*	Params:
*		cols: (int) Number of desired cols. Must be positive.
*
* Exit: m_cols is set and m_array is resized to accomodate the new size.
************************************************************************/
template <class T>
void Array2D<T>::setColumn(int columns){
	if(columns < 0){
		throw Exception("Cannot set a negative column length.");
	}

	int last_index = 0;
	if(columns > m_col){
		// enlarging each column array, copy data up to current amount of columns
		last_index = m_col;
	}else if(columns < m_col){
		// shrinking each column array, copy data up to new number of rows
		last_index = columns;
	}

	if(columns != m_col){
		T* new_array = 0; // the temporary pointer that holds the address of each new column array
		for(int r=0; r<m_row; ++r){
			new_array = new T[columns];

			// copying old data over
			for(int c=0; c<last_index; ++c){
				new_array[c] = m_array[r][c];
			}

			delete m_array[r];
			m_array[r] = new_array;
		}

		m_col = columns;
	}
}

/**********************************************************************	
* T Select(int row, int column)
* Purpose: Used by Row::operator[] to resolve a double subscript 
*		operator to a row and column coordinate in the array. Exception 
*		will be thrown if indices are out of bounds.
*
* Entry:
*	Params:
*		row: (int) Row index
*		column: (int) Column index
*
* Exit: Returns the requested T element.
************************************************************************/
template <class T>
T& Array2D<T>::Select(int row, int column) const{
	if(row >= m_row){
		throw Exception("Index out of bounds: Row index too high.");
	}else if(row < 0){
		throw Exception("Index out of bounds: Row index too low.");
	}else if(column >= m_col){
		throw Exception("Index out of bounds: Column index too high.");
	}else if(column < 0){
		throw Exception("Index out of bounds: Column index too low.");
	}

	return m_array[row][column];
}