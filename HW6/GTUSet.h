#ifndef GTUSET_H
#define GTUSET_H

#include <iostream>
#include "GTUContainer.h"

using namespace std;

namespace GTU{

	template<class T>
	class GTUSet:public GTUContainer<T>{

		private:

			int v_size;
			int v_max_size;
			T *element;

		public:	

		~GTUSet(){delete element;}
		GTUSet():v_size(0),v_max_size(50){element = new T[v_max_size];}
		GTUSet(int starter_size):v_size(0),v_max_size(starter_size){
			element = new T[starter_size];
		}

		bool empty();
		int size();
		int max_size();
		void insert(T new_ele);
		void erase();
		T * begin();
		void clear();
		T * end();

	};

}	//End of namespace.

#endif