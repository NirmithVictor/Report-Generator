#include <iostream>
using namespace std;
#include <cstdlib>

#include<vector>
#include"Record.h"

template <class T>
class Map{

	private:
		vector<T> keys;
		vector<vector<Record*>> values;
	public:
		void add(T,Record*);
		int getKeySize();
		vector<T>& getKeys();
		vector<Record*>& operator[](T);
};

template <class T>
void Map<T>::add(T key,Record* rec){
	if(keys.size()==0){
		keys.push_back(key);
		vector<Record*> newcollection;
		newcollection.push_back(rec);
		values.push_back(newcollection);
	}
	else{
		if(keys.size()==values.size()){
			bool a=true;
			
			//
			for(int i=0;i<keys.size();i++){
				if(keys[i]==key){
				//add to corresponding values key
					values[i].push_back(rec);
					a=false;
				}
			}
			//we have to create a new collection ? and then add that to the values collection
			if(a){
				keys.push_back(key);
				vector<Record*> newcollection;
				newcollection.push_back(rec);
				values.push_back(newcollection);
			}
		}
		else{
			cout<<"OVERLOAD "<<endl;
		}
		
	}
}

template <class T>
int Map<T>::getKeySize(){
	return keys.size();
}

template <class T>
vector<T>& Map<T>::getKeys(){
	return keys;
}

template <class T>
vector<Record*>& Map<T>::operator[](T a){
	try{
		for(int i=0;i<keys.size();i++){
			if(a==keys[i]){
				return values[i];
			}
		}
		throw("Error");
	}
	catch(const char* s){
		throw(s);	
	}
}





/*
-> map class that contains all the data that will be read from a file as shall be in the reportGenerator class
-> we have also have a bunch of getter for keys and keySize
-> we have a add function that adds to the keys and the collection if the key doesn't exist else we just add to the collection of the keys if it exists
-> we have a subscriptoperator that returns the values for a particular key
*/




