/*
 * product.cpp
 *
 *  Created on: 14-Oct-2016
 *      Author: vivek10p14
 */

#include "header.h"

using namespace std;

struct table* product(string s){
	if(!check_db()){
		cout << "Select Database !!!" << endl; // check if database is selected
		return NULL;
	}
	vector<string> v = string_to_vector(s); // convert string to vector containing individual words
	if(!proper_product(v)){
		cout << "Check Syntax !!!" << endl; // check for proper syntax
	}
	vector<string> project1,project2;
	int pivot = 0;
	for(int i=0;i<v.size();i++){
		if(v[i]=="product"){ // build both the projection quereis
			pivot = 1;
		}
		else{
			if(pivot==0){
				project1.push_back(v[i]);
			}
			else{
				project2.push_back(v[i]);
			}
		}
	}
	table* table1 = project(vector_to_string(project1)); // get the first table of product
	table* table2 = project(vector_to_string(project2));// get the second table of product

	if(table1==NULL || table2==NULL){ // none of the tables should be NULL
		cout << "Error !!!" << endl;
		return NULL;
	}
	//cout << "apple" << endl;
	vector<string> attr_list1 = (table1->tot_index); // get attribute list of both queries
	vector<string> attr_list2 = (table2->tot_index);

	table* ans = new table(); // new table for storing product

	vector<int> aux_int; // empty vectors
	vector<string> aux_string;

	sort(attr_list1.begin(), attr_list1.end()); // sort both attribute lists
	sort(attr_list2.begin(), attr_list2.end());

	vector<string> common;
	set_intersection(attr_list1.begin(),attr_list1.end(),attr_list2.begin(),attr_list2.end(),back_inserter(common));
	// intersection of both attribute lists
	if(common.size()!=0){ //intersection must be null i.e they must not have common attribute names
		cout << "Attribute names cannot be common use rename" << endl;
		return NULL;
	}

	if((table1->tot_index).size()>(table2->tot_index).size()){
		swap(table1,table2);
	}

	int index = 1;
	int mint_index = 1;
	int mstring_index = 1;



	vector<string> attr = (table1->tot_index); // build structure for answer table
	for(int i=0;i<attr.size();i++){
		(ans->tot_index).push_back(attr[i]);
		(ans->attr_index)[attr[i]] = index;
		index++;
		if((table1->mint)[attr[i]]==0){
			(ans->mstring)[attr[i]] = mstring_index;
			mstring_index++;
			(ans->vstring).push_back(aux_string);
		}
		else{
			(ans->mint)[attr[i]] = mint_index;
			mint_index++;
			(ans->vint).push_back(aux_int);
		}
	}

	attr = table2->tot_index;

	for(int i=0;i<attr.size();i++){ //build structure for answer table
		(ans->tot_index).push_back(attr[i]);
		(ans->attr_index)[attr[i]] = index;
		index++;
		if((table2->mint)[attr[i]]==0){
			(ans->mstring)[attr[i]] = mstring_index;
			mstring_index++;
			(ans->vstring).push_back(aux_string);
		}
		else{
			(ans->mint)[attr[i]] = mint_index;
			mint_index++;
			(ans->vint).push_back(aux_int);
		}
	}

	int tuples1 = 0;
	int tuples2 = 0;


	if((table1->vint).size()!=0){ // calculate number of tuples in table1
		tuples1 = (table1->vint)[0].size();
	}
	else{
		tuples1 = (table1->vstring)[0].size();
	}

	if((table2->vint).size()!=0){ // calculate number of tuples in table2
		tuples2 = (table2->vint)[0].size();
	}
	else{
		tuples2 = (table2->vstring)[0].size();
	}

	if(tuples1==0 || tuples2==0){
		cout << "Empty Tables"<< endl;
		return NULL;
	}


	attr = table1->tot_index;


	for(int i=0;i<attr.size();i++){ // insert tuples from table1 in answer
		for(int j=0;j<tuples1;j++){

			if((ans->mint).count(attr[i])==0){

				int push_index = (ans->mstring)[attr[i]]-1;

				int pop_index = (table1->mstring)[attr[i]]-1;

 				for(int k=0;k<tuples2;k++){

					(ans->vstring)[push_index].push_back((table1->vstring)[pop_index][j]);
				}

			}
			else{
				int push_index = (ans->mint)[attr[i]]-1;
				int pop_index = (table1->mint)[attr[i]]-1;
				for(int k=0;k<tuples2;k++){
					(ans->vint)[push_index].push_back((table1->vint)[pop_index][j]);
				}
			}
		}
	}


	attr = table2->tot_index; // insert tables from table2 in answer

	for(int i=0;i<attr.size();i++){
		if((ans->mint).count(attr[i])==0){
			int push_index = (ans->mstring)[attr[i]]-1;
			int pop_index = (table2->mstring)[attr[i]]-1;
			vector<string> vq;
			vector<string> vw = (table2->vstring)[pop_index];
			for(int j=0;j<tuples1;j++){
				vq.insert(vq.end(),vw.begin(),vw.end());
			}
			((ans->vstring)[push_index]).insert(((ans->vstring)[push_index]).end(),vq.begin(),vq.end());

		}
		else{
			int push_index = (ans->mint)[attr[i]]-1;
			int pop_index = (table2->mint)[attr[i]]-1;
			vector<int> vq;
			vector<int> vw = (table2->vint)[pop_index];
			for(int j=0;j<tuples1;j++){
				vq.insert(vq.end(),vw.begin(),vw.end());
			}
			((ans->vint)[push_index]).insert(((ans->vint)[push_index]).end(),vq.begin(),vq.end());
		}
	}


	delete table1; // delete the auxilary tables
	delete table2;

	return ans; // return the answer


}

struct table* product(struct table* table1, struct table* table2){

	if(table1==NULL || table2==NULL){ // no need to load tables
		cout << "Error !!!" << endl; // they are already provided
		return NULL;
	}
	// follow same procedure as above

	vector<string> attr_list1 = (table1->tot_index);
	vector<string> attr_list2 = (table2->tot_index);

	table* ans = new table();

	vector<int> aux_int;
	vector<string> aux_string;

	sort(attr_list1.begin(), attr_list1.end());
	sort(attr_list2.begin(), attr_list2.end());

	vector<string> common;
	set_intersection(attr_list1.begin(),attr_list1.end(),attr_list2.begin(),attr_list2.end(),back_inserter(common));
	if(common.size()!=0){
		cout << "Attribute names cannot be common use rename" << endl;
		return NULL;
	}

	if((table1->tot_index).size()>(table2->tot_index).size()){
		swap(table1,table2);
	}

	int index = 1;
	int mint_index = 1;
	int mstring_index = 1;



	vector<string> attr = (table1->tot_index);
	for(int i=0;i<attr.size();i++){
		(ans->tot_index).push_back(attr[i]);
		(ans->attr_index)[attr[i]] = index;
		index++;
		if((table1->mint).count(attr[i])==0){
			(ans->mstring)[attr[i]] = mstring_index;
			mstring_index++;
			(ans->vstring).push_back(aux_string);
		}
		else{
			(ans->mint)[attr[i]] = mint_index;
			mint_index++;
			(ans->vint).push_back(aux_int);
		}
	}

	attr = table2->tot_index;

	for(int i=0;i<attr.size();i++){
		(ans->tot_index).push_back(attr[i]);
		(ans->attr_index)[attr[i]] = index;
		index++;
		if((table2->mint).count(attr[i])==0){
			(ans->mstring)[attr[i]] = mstring_index;
			mstring_index++;
			(ans->vstring).push_back(aux_string);
		}
		else{
			(ans->mint)[attr[i]] = mint_index;
			mint_index++;
			(ans->vint).push_back(aux_int);
		}
	}

	int tuples1 = 0;
	int tuples2 = 0;


	if((table1->vint).size()!=0){
		tuples1 = (table1->vint)[0].size();
	}
	else{
		tuples1 = (table1->vstring)[0].size();
	}

	if((table2->vint).size()!=0){
		tuples2 = (table2->vint)[0].size();
	}
	else{
		tuples2 = (table2->vstring)[0].size();
	}

	if(tuples1==0 || tuples2==0){
		cout << "Empty Tables"<< endl;
		return NULL;
	}



	attr = table1->tot_index;


	for(int i=0;i<attr.size();i++){
		for(int j=0;j<tuples1;j++){

			if((ans->mint).count(attr[i])==0){

				int push_index = (ans->mstring)[attr[i]]-1;

				int pop_index = (table1->mstring)[attr[i]]-1;

 				for(int k=0;k<tuples2;k++){

					(ans->vstring)[push_index].push_back((table1->vstring)[pop_index][j]);
				}

			}
			else{

				int push_index = (ans->mint)[attr[i]]-1;
				int pop_index = (table1->mint)[attr[i]]-1;
				for(int k=0;k<tuples2;k++){

					(ans->vint)[push_index].push_back((table1->vint)[pop_index][j]);
				}

			}
		}
	}


	attr = table2->tot_index;

	for(int i=0;i<attr.size();i++){
		if((ans->mint).count(attr[i])==0){
			int push_index = (ans->mstring)[attr[i]]-1;
			int pop_index = (table2->mstring)[attr[i]]-1;
			vector<string> vq;
			vector<string> vw = (table2->vstring)[pop_index];
			for(int j=0;j<tuples1;j++){
				vq.insert(vq.end(),vw.begin(),vw.end());
			}
			((ans->vstring)[push_index]).insert(((ans->vstring)[push_index]).end(),vq.begin(),vq.end());

		}
		else{
			int push_index = (ans->mint)[attr[i]]-1;
			int pop_index = (table2->mint)[attr[i]]-1;
			vector<int> vq;
			vector<int> vw = (table2->vint)[pop_index];
			for(int j=0;j<tuples1;j++){
				vq.insert(vq.end(),vw.begin(),vw.end());
			}
			((ans->vint)[push_index]).insert(((ans->vint)[push_index]).end(),vq.begin(),vq.end());
		}
	}


	delete table1;
	delete table2;

	return ans;


}






