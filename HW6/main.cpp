#include <iostream>

#include "GTUContainer.h"

#include "GTUVector.cpp"
#include "GTUVector.h"

#include "GTUSet.h"
#include "GTUSet.cpp"

using namespace std;
using namespace GTU;


template <class T>
void for_each(GTUContainer<double>::GTUIterator iterrator_START , GTUContainer<double>::GTUIterator iterrator_END, T function){
	do{
		function(*iterrator_START);
		++iterrator_START;
	}while( !(iterrator_START == iterrator_END));
}

void add_one(int num){
	/*USED FOR For_each TEST*/
	cout << " " << num;
}

template <class T>
int find(GTUContainer<double>::GTUIterator iterrator_START , GTUContainer<double>::GTUIterator iterrator_END, T value){

	int index=0;

	while( !(iterrator_START == iterrator_END)){
		if(*iterrator_START == value)	return index;
		++index;
		++iterrator_START;
	}

	return -1;
}

int main(){
	
	cout << "Welcome to test program for SET and VECTOR." << endl;

	int i;

	cout << endl << "********** VECTOR TEST ********" << endl; 
	GTUVector<double> test_v;
	GTUContainer<double>::GTUIterator iterrator_v(NULL);

	/*CHANGE LINE 21 FOR TYPE.*/
	cout << "Type choice is DOUBLE. You can change it by changing the code." << endl;

	for(i=0;i<30;i++) test_v.insert(i+10); //filling the GTUVector.

	/*TEST FOR OPERATOR OVERLOAD [.] */
	cout << "Test for [.] => " 
		<< "test[4] : " << test_v[4]
		<< ", test[15] : " << test_v[15] << endl;;

	iterrator_v = test_v.begin();
	cout << "Iterrator is now pointing to vector's begin()." << endl;

	cout << "Tests for iterrator_v => "
		<< *iterrator_v << " -> doing ++ operator -> " ; 
		++iterrator_v;
	cout << *iterrator_v << " -> doing -- operator -> ";
		--iterrator_v;
	cout << *iterrator_v << "." << endl;

	iterrator_v = test_v.end();
	cout << "Iterrator is now pointing to vector's end()." << endl;
	cout << *iterrator_v << " -> doing -- operator -> ";
		--iterrator_v;
	cout << *iterrator_v << "." << endl;

	cout << endl <<"********** SET TEST ********" <<endl; 

	GTUSet<int> test_s;
	GTUContainer<int>::GTUIterator iterrator_s(NULL);

	/*CHANGE LINE 52 FOR TYPE.*/
	cout << "Type choice is INTEGER. You can change it by changing the code." << endl;

	for(i=0;i<20;i++) test_s.insert(i+10); //filling the GTUSet.

	iterrator_s = test_s.begin();
	cout << "Iterrator is now pointing to set's begin()." << endl;

	cout << "Tests for iterrator_v => "
		<< *iterrator_s << " -> doing ++ operator -> " ; 
		++iterrator_s;
	cout << *iterrator_s << " -> doing -- operator -> ";
		--iterrator_s;
	cout << *iterrator_s << "." << endl;
	
	iterrator_s = test_s.end();
	cout << "Iterrator is now pointing to set's end()." << endl;

	cout << *iterrator_s << " -> doing -- operator -> ";
		--iterrator_s;
	cout << *iterrator_s << "." << endl;

	cout << endl << "*********** FIND TEST ******************" << endl;

	double chosen_num = 19;
	cout << "FINDING "<< chosen_num << ". is at = " << find(test_v.begin(),test_v.end(),chosen_num) << " place." << endl
		<< "-1 means not found." << endl;

	cout << endl << "*********** FOR_EACH TEST******************" << endl
		<< "Function for for_each will print all elements." << endl;

	for_each(test_v.begin(),test_v.end(),add_one);
	cout << endl;

	exit(1);

	return 0;
}