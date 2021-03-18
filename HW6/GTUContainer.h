#ifndef GTUCONTAINER_H
#define GTUCONTAINER_H

#include <iterator>

namespace GTU{

	template<class T>
	class GTUContainer{
		
		public:

			virtual bool empty()=0;
			/* Checks if the element is empty or not. */

			virtual int size()=0;
			/* Returns a size of elements*/

			virtual int max_size()=0;
			/* Returns a max size capacity*/

			virtual void insert(T new_ele)=0;
			/* Inserts a new element.*/

			virtual void erase()=0;
			/* Erases the last element*/

			virtual T* begin()=0;
			/* Returns a iterrator to begin of the element*/

			virtual T* end()=0;
			/* Returns a iterrator to end of the element*/

			virtual void clear()=0;
			/* Clears the element*/


			/*GTUITERRATOR, FOR TESTS AND VECTOR- SET CLASSES*/
			class GTUIterator{
				public:
					GTUIterator(T* ptr) : pointer(ptr) {}
					GTUIterator operator++(){
						pointer++;
						return *this;
					}
					GTUIterator operator--(){
						pointer--;
						return *this;
					}
					bool operator == (const GTUIterator & other){return pointer==other.pointer;}
					bool operator != (const GTUIterator & other){return !(pointer==other.pointer);}
					T* operator ->(){return pointer;}
					T& operator*(){ return *pointer;}
					void operator=(T& ptr){pointer=ptr;}

				private:	
					T* pointer;
			};

			/*GTUITERRATOR_CONST, FOR TESTS AND VECTOR- SET CLASSES*/
			class GTUIterator_const{
				public:
					GTUIterator_const(T* ptr) : pointer(ptr) {}
					GTUIterator_const operator++(){
						pointer++;
						return *this;
					}
					bool operator == (const GTUIterator & other){return pointer==other.pointer;}
					bool operator != (const GTUIterator & other){return !(pointer==other.pointer);}
					const T* operator ->(){return pointer;}
					const T& operator*(){ return *pointer;}
					void operator=(T *ptr){pointer=*ptr;}

				private:	
					T* pointer;
			};
	};

} //End of namespace.

#endif