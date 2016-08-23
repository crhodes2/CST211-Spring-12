/************************************************************************
* Class: Row
*
* Purpose: This class represents a 2 dimensional array's row. It is to be 
*		used only by the Array2D class. Constructor was made public 
*		regardless as per UML specs. Destructor not needed.
*
* Manager functions:	
* 	Row(Array2D<T> array, int row)
* 		Constructs a row with a reference to the passed in array, and 
*		assigns the row to the passed in row.	
*
* Methods:		
*	operator[](int column)
*		Overloaded bracket operator used to resolve addresses at given column.
*		Used for data retrieval as well as assignment
*************************************************************************/
#pragma once

template <class T>
class Array2D;

template <class T>
class Row{
	private:
		Array2D<T> const& m_array2D;
		int m_row;

	public:
		Row(Array2D<T> const& array, int row);
		
		T& operator[](int column);
		T const& operator[](int column) const;
};

/**********************************************************************	
* Row(Array2D<T> array, int row)
* Purpose: This function is the one and only constructor for the Row class.
*		It is not to be called from anything but Array2D::Select().
*
* Entry:
*	Params:
*		array: (Array2D<T>) The array the row object is part of.
*		row: (int) The row of the array this object represents.
*
* Exit: Constructs a row object representing the row'th row of the 2D array.
************************************************************************/
template <class T>
Row<T>::Row(Array2D<T> const& array, int row) : m_array2D(array), m_row(row){

}

/**********************************************************************	
* operator[](int column)
* Purpose: This function is a helper function in order for the double 
*		subscript of a 2D array to function properly. It is not to be 
*		called directly.
*
* Entry:
*	Params:
*		column: (int) The column index to retrieve.
*
* Exit: Returns a T reference of the requested element.
************************************************************************/
template <class T>
T& Row<T>::operator[](int column){
	return m_array2D.Select(m_row, column);
}
template <class T>
T const& Row<T>::operator[](int column) const{
	return m_array2D.Select(m_row, column);
}