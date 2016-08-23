#pragma once

template <class T>
class AbstractIterator{
protected:
public:
	virtual void MoveNext() = 0;
	virtual void Reset() = 0;
	virtual bool IsDone() = 0;
	virtual T const& GetCurrent() = 0;

};