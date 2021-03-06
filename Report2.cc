#include <iostream>
using namespace std;
#include <cstdlib>
#include<iomanip>

#include<vector>
#include<iterator>
#include<algorithm>
#include<string>

#include <fstream>

#include "Report2.h"
#include "Record.h"

Report2_PercentageChange::Report2_PercentageChange(){
	l=new AscBehaviour<float>();
	repo2=new ReportData<float>(l);
}
Report2_PercentageChange::~Report2_PercentageChange(){
	delete repo2;
}


void Report2_PercentageChange::compute(){

	collc.clear();
	vector<string> key=animalTypeMap.getKeys();
	int sum2=0;
	int sum1=0;
	vector<Record*> temp;
	vector<int> sumCollec;
	for(int i=0;i<key.size();i++){
		temp.clear();
		vector<Record*>& a=yearMap[2011];
		vector<Record*>& b=yearMap[2016];
		for(int j=0;j<a.size();j++){
			if(a[j]->getanimalType()==key[i] && a[j]->getRegion()=="CAN"){
				temp.push_back(a[j]);
				sum1+=a[j]->getnumAnimals();
			}
		}
		for(int j=0;j<b.size();j++){
			if(b[j]->getanimalType()==key[i] && b[j]->getRegion()=="CAN"){
				temp.push_back(b[j]);
				sum2+=b[j]->getnumAnimals();
			}
		}
		if(temp.size()==1){
			if(temp[0]->getYear()==2011){
				temp.push_back(new Record(2016,"CAN",0,0,"All",key[i]));

			}else{
				temp.push_back(new Record(2011,"CAN",0,0,"All",key[i]));

			}
		}
		collc.push_back(temp);
	}
	sumCollec.push_back(sum1);
	sumCollec.push_back(sum2);
	formatData(repo2,sumCollec);
	printReport(repo2);	

}

void Report2_PercentageChange::formatData(ReportData<float>* cb,vector<int> test){
	vector<vector<float>> lls;
	
	for(int i=0;i<collc.size();i++){
		float tel;
		vector<float> ttl;
		for(int j=0;j<collc[i].size();j++){
			tel= 100*(collc[i][j]->getnumAnimals())/(float)test[j];
			ttl.push_back(tel);
		}
		lls.push_back(ttl);
	}
	
	for(int i=0;i<collc.size();i++){
		stringstream ss;
		float percDiff=0;
		ss<<setw(20)<<right<<collc[i][0]->getanimalType()<<"";
		for(int j=0;j<lls[i].size();j++){
			ss<<"   "<< setw(7)<<right<<setprecision (1)<<fixed<<lls[i][j];
			if(j>0){
				percDiff=lls[i][j]-lls[i][j-1];
			}
		}
		if(percDiff<0){
			ss<<"   "<< setw(7)<<right<<setprecision (1)<<fixed<<percDiff<<endl;
			cb->add(percDiff,ss.str());
		}else{
			ss<<"   "<< setw(4)<<right<<setprecision (1)<<fixed<<"+"<<percDiff<<endl;
			cb->add(percDiff,ss.str());
		}
	}
	
}

void Report2_PercentageChange::printReport(ReportData<float>* c){
	
	cout<<"\n\t \tPERCENTAGE CHANGE OF ANIMALS (2011-2016)\t\t\n";
	cout<<"\t---------------------------------------------------------\n";
	cout<<"\t\t ANIMAL TYPE\t  2011\t    2016     Change"<<endl<<endl;
	cout<<*c;
	cout<<"\t---------------------------------------------------------\n";
	ofstream outfile("Report2.txt",ios::out);
	if (!outfile) {
    		cout << "Error:  could not open file" << endl;
    		exit(1);
  	}
	outfile<<"\n\t \tPERCENTAGE CHANGE OF ANIMALS (2011-2016)\t\t\n";
	outfile<<"\t---------------------------------------------------------\n";
	outfile<<"\t\t ANIMAL TYPE\t  2011\t    2016     Change"<<endl<<endl;
	outfile<<*c;
	outfile<<"\t---------------------------------------------------------\n";
	repo2->CLEAN();
}

