/*
 * rename.cpp
 *
 *  Created on: 14-Oct-2016
 *      Author: vivek10p14
 */

#include "header.h"

using namespace std;

struct table* rename(string s){

	if(!check_db()){
		cout << "Select Database !!!" << endl; // check if database is selected
		return NULL;
	}
	vector<string> v = string_to_vector(s); // convert string to vector of strings
	if(!proper_rename){
		cout << "Check Syntax !!!" << endl; // check for proper syntax
		return NULL;
	}

	string tab_name = v[v.size()-1]; // get table name


	table* new_tab = load_table(tab_name); // load concerned table into memory

	table* ans = new table();

	vector<string> attr = (new_tab->tot_index);


	for(int i=0;i<attr.size();i++){
		(ans->tot_index).push_back(v[i+1]); // push the new attribute names
	}

	int mint_index = 1;
	int mstring_index = 1; // make structure of new table similar to the old one
	int index = 1;


	for(int i=0;i<attr.size();i++){
		if((new_tab->mint).count(attr[i])==0){
			(ans->mstring)[v[i+1]] = mstring_index;
			mstring_index++;
		}
		else{
			(ans->mint)[v[i+1]] = mint_index;
			mint_index++;
		}
		(ans->attr_index)[v[i+1]] = index;
		index++;
	}

	ans->vint = new_tab->vint;
	ans->vstring = new_tab->vstring;
	delete new_tab; // delete the auxilary table

	return ans; // return answer

}

struct table* rename(vector<string> v, struct table* new_tab){

	table* ans = new table(); // similar to previous one but vector and table are given as input

	vector<string> attr = (new_tab->tot_index);


	for(int i=0;i<attr.size();i++){
		(ans->tot_index).push_back(v[i+1]);
	}

	int mint_index = 1;
	int mstring_index = 1;
	int index = 1;


	for(int i=0;i<attr.size();i++){
		if((new_tab->mint).count(attr[i])==0){
			(ans->mstring)[v[i+1]] = mstring_index;
			mstring_index++;
		}
		else{
			(ans->mint)[v[i+1]] = mint_index;
			mint_index++;
		}
		(ans->attr_index)[v[i+1]] = index;
		index++;
	}


	ans->vint = new_tab->vint;
	ans->vstring = new_tab->vstring;

	delete new_tab;

	return ans;

}

