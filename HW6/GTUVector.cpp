#include <iostream>
#include <vector>

#include "GTUVector.h"

using namespace std;

namespace GTU{

	template <class T>
	bool GTUVector<T>::empty(){

		if(v_max_size<1 || v_size<1) return true;
		else	for(int i=0;i<v_size;i++)	if(element != NULL) return false;

		return true;
	}

	template <class T>
	int GTUVector<T>::size(){
		return v_size;
	}

	template <class T>
	int GTUVector<T>::max_size(){
		return v_max_size;
	}

	template <class T>
	void GTUVector<T>::insert(T new_ele){
		
		if(v_size>=v_max_size){
		 	T temp_array[v_size];

		 	for(int i=0;i< v_size;i++)	temp_array[i] = element[i];

		 	v_max_size+=5;
			element = new T[v_max_size];

			for(int i=0;i< v_size; i++) element[i]=temp_array[i];
		}

		element[v_size-1]=new_ele;
		v_size++;
	}

	template <class T>
	void GTUVector<T>::erase(){

		element[v_size]=0;
		v_size--;
	}

	template <class T>
	void GTUVector<T>::clear(){
		v_size=0;
		v_max_size=50;
		element = new T[50];
	}

	template <class T>
	T * GTUVector<T>::end(){ 
		return &element[v_size-1];
	}

	template <class T>
	T * GTUVector<T>::begin(){ 
		return &element[0];
	}


}	//End of namespace.