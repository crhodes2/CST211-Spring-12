#pragma once

template <class KeyType, class DataType>
class AVLNode
{
private:
	KeyType m_key;
	DataType m_data;

	AVLNode<KeyType, DataType>* m_left;
	AVLNode<KeyType, DataType>* m_right;

	short int m_balanceFactor;
	unsigned m_height;

public:
	AVLNode();
	AVLNode(KeyType const& key, DataType const& data);
	AVLNode(AVLNode<KeyType, DataType>* left, AVLNode<KeyType, DataType>* right, KeyType const& key, DataType const& data);
	AVLNode(AVLNode<KeyType, DataType> const& copy);
	~AVLNode();

	AVLNode<KeyType, DataType> const& operator=(AVLNode<KeyType, DataType> const& rhs);

	void setKey(KeyType const& key);
	KeyType getKey() const;

	void setData(DataType const& data);
	DataType& getData();

	void setLeft(AVLNode<KeyType, DataType>* left);
	AVLNode<KeyType, DataType>*& getLeft();

	void setRight(AVLNode<KeyType, DataType>* right);
	AVLNode<KeyType, DataType>*& getRight();
	
	void setBalanceFactor(short int balanceFactor);
	short int getBalanceFactor() const;

	void setHeight(unsigned height);
	unsigned getHeight() const;
};

template <class KeyType, class DataType>
AVLNode<KeyType, DataType>::AVLNode()
	: m_key(KeyType()), m_data(DataType()), m_left(nullptr), m_right(nullptr), m_balanceFactor(0), m_height(0)
{

}

template <class KeyType, class DataType>
AVLNode<KeyType, DataType>::AVLNode(KeyType const& key, DataType const& data)
	: m_key(key), m_data(data), m_left(nullptr), m_right(nullptr), m_balanceFactor(0), m_height(0)
{

}

template <class KeyType, class DataType>
AVLNode<KeyType, DataType>::AVLNode(AVLNode<KeyType, DataType>* left, AVLNode<KeyType, DataType>* right, KeyType const& key, DataType const& data)
	: m_key(key), m_data(data), m_left(left), m_right(right), m_balanceFactor(0), m_height(0)
{
	
}

template <class KeyType, class DataType>
AVLNode<KeyType, DataType>::AVLNode(AVLNode<KeyType, DataType> const& copy)
	: m_key(copy.m_key), m_data(copy.m_data), m_left(copy.m_left), m_right(copy.m_right), m_balanceFactor(copy.m_balanceFactor), m_height(copy.m_height)
{

}

template <class KeyType, class DataType>
AVLNode<KeyType, DataType>::~AVLNode()
{
	delete m_left;
	delete m_right;
}

template <class KeyType, class DataType>
AVLNode<KeyType, DataType> const& AVLNode<KeyType, DataType>::operator=(AVLNode<KeyType, DataType> const& rhs)
{
	if(*this != rhs)
	{
		m_key = rhs.m_key;
		m_data = rhs.m_data;
		m_left = rhs.m_left;
		m_right = rhs.m_right;
		m_balanceFactor = rhs.m_balanceFactor;
	}
}

template <class KeyType, class DataType>
void AVLNode<KeyType, DataType>::setKey(KeyType const& key)
{
	m_key = key;
}

template <class KeyType, class DataType>
KeyType AVLNode<KeyType, DataType>::getKey() const
{
	return m_key;
}

template <class KeyType, class DataType>
void AVLNode<KeyType, DataType>::setData(DataType const& data)
{
	m_data = data;
}

template <class KeyType, class DataType>
DataType& AVLNode<KeyType, DataType>::getData()
{
	return m_data;
}

template <class KeyType, class DataType>
void AVLNode<KeyType, DataType>::setLeft(AVLNode<KeyType, DataType>* left)
{
	m_left = left;
}

template <class KeyType, class DataType>
AVLNode<KeyType, DataType>*& AVLNode<KeyType, DataType>::getLeft()
{
	return m_left;
}

template <class KeyType, class DataType>
void AVLNode<KeyType, DataType>::setRight(AVLNode<KeyType, DataType>* right)
{
	m_right = right;
}

template <class KeyType, class DataType>
AVLNode<KeyType, DataType>*& AVLNode<KeyType, DataType>::getRight()
{
	return m_right;
}

template <class KeyType, class DataType>
void AVLNode<KeyType, DataType>::setBalanceFactor(short int balanceFactor)
{
	m_balanceFactor = balanceFactor;
}

template <class KeyType, class DataType>
short int AVLNode<KeyType, DataType>::getBalanceFactor() const
{
	return m_balanceFactor;
}

template <class KeyType, class DataType>
void AVLNode<KeyType, DataType>::setHeight(unsigned height)
{
	m_height = height;
}

template <class KeyType, class DataType>
unsigned AVLNode<KeyType, DataType>::getHeight() const
{
	return m_height;
}