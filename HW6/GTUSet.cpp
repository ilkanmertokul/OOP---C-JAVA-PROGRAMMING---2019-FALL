#include <iostream>
#include <vector>

#include "GTUSet.h"

using namespace std;
using namespace GTU;

namespace GTU{

	template <class T>
	bool GTUSet<T>::empty(){

		if(v_max_size<1 || v_size<1) return true;
		else	for(int i=0;i<v_size;i++)	if(element != NULL) return false;

		return true;
	}

	template <class T>
	int GTUSet<T>::size(){
		return v_size;
	}

	template <class T>
	int GTUSet<T>::max_size(){
		return v_max_size;
	}

	template <class T>
	void GTUSet<T>::insert(T new_ele){

		try{
			for(int i=0;i< v_size;i++){
				if(element[i]==new_ele){
					throw new_ele;
				}
			}
		}	
		catch(int anew_ele){
			cout << "Error putting " << anew_ele;
		}
		
		v_size++;

		if(v_size>=v_max_size){

			v_max_size+=50;
			T temp_array[v_max_size];

			for(int i=0;i< v_size-1;i++)	temp_array[i] = element[i];
			element = new T[v_max_size];

			for(int i=0;i< v_size; i++) element[i]=temp_array[i];
		}

		element[v_size-1] = new_ele ;
	
		int j=v_size-1;
		T temp;

		while(j>1){
			if(element[j-1]<element[j-2]){
				temp=element[j-1];
				element[j-1]=element[j-2];
				element[j-2]=element[j-1];

			}
			j--;
		}
	}

	template <class T>
	void GTUSet<T>::erase(){

		element[v_size]=0;
		v_size--;
	}

	template <class T>
	void GTUSet<T>::clear(){
		v_size=0;
		v_max_size=50;
		element = new T[50];
	}

	template <class T>
	T * GTUSet<T>::end(){ 
		return &element[v_size-1];
	}

	template <class T>
	T * GTUSet<T>::begin(){ 
		return &element[0];
	}

}	//End of namespace.