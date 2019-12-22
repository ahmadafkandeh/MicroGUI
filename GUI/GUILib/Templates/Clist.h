#ifndef _CList_H
#define _CList_H
#include "./Type.h"
template <class T>
class CList
{
public:
	CList();
	~CList();
	int 				ADD(T objptr);
	void 				Replace(int index,T objptr);
	bool 				RemoveByref(T objptr);
	void 				RemoveByindex(int index);
	void				RemoveAll();
	bool 				Contains(T objptr);
	int 				Count();
 	int 				GetIndex(T objptr);
	T 					GetObject(int index);
private:
	void 				ReAllocCList();
	void 				Remove(int index);
private:
	int 				m_EndOfCList;
	int 				m_size;
	hwnd_type 	m_last_index;
	T					  *m_CList;
};
//------------------------------------------------------------------------
//constructor of class
template <class T>
CList<T>::CList(){
	m_EndOfCList=10;
	m_CList=new T[m_EndOfCList];
	m_size=0;
	m_last_index=0;
	
}
//destructor of class
template <class T>
CList<T>::~CList()
{
		delete [] m_CList;
}
//Function to add items in CList
template <class T>
int CList<T>::ADD(T objptr)
{
	if (!Contains(objptr))
	{
		m_CList[m_size]=objptr;
		m_size++;
		if (m_size>=m_EndOfCList)
			ReAllocCList();
		m_last_index++;
		return m_last_index;
	}
	return 0;
}

template <class T>
void CList<T>::Replace(int index,T objptr)
{
	m_CList[index]=objptr;
}
//private Function to Remove an item from List by it's index
template <class T>
void CList<T>::Remove(int index)
{
		int temp=m_size-index;
		while(temp--)
		{
			m_CList[index]=m_CList[index+1];
			index++;
		}
		m_size--;
}
//function to remove all of Items from list
template <class T>
void CList<T>::RemoveAll()
{
	delete [] m_CList;
	m_CList=new T[10];
	m_EndOfCList=10;
	m_size=0;
	m_last_index=0;
}
//function to remove items from list by their refrence
template <class T>
bool CList<T>::RemoveByref(T objptr)
{
	if (Contains(objptr))
	{
		Remove(GetIndex(objptr));
		return true;
	}
	return false;
}
//function to remove objects from list by their index
template <class T>
void CList<T>::RemoveByindex(int index)
{
	if ( index < 0 || index > m_size )return;
	Remove(index);
}

//Function to check existance of an object.
template <class T>
bool CList<T>::Contains(T objptr)
{
	for (unsigned int i=0;i<m_size;i++)
	{
		if (m_CList[i]==objptr)
		return true;
	}
	return false;
}
//property to return the Sum of objects in list
template <class T>
int CList<T>::Count()
{
	return m_size;
};
//internal function to get index of an added object.
template <class T>
int CList<T>::GetIndex(T objptr)
{
	for (int i=0;i<m_size;i++)
	{
		if (m_CList[i]==objptr)
			return i;
	}
	return 0;
};
//Function to get objects reference by their index.
template <class T>
T CList<T>::GetObject(int index)
{
	return m_CList[index];
};
//internal function to reallocating the List Size
template <class T>
void CList<T>::ReAllocCList()
{	
	m_EndOfCList+=10;
	T *temp=new T[m_EndOfCList];
	for(int i=0;i<m_size;i++)
		temp[i]=m_CList[i];
	delete [] m_CList;
	m_CList=temp;
};

#endif
