/*
 * project.cpp
 *
 *  Created on: 13-Oct-2016
 *      Author: vivek10p14
 */

#include "header.h"

struct table* project(string s){

	if(!check_db()){ // check if database is selected
		cout << "Select Database !!!" << endl;
		return NULL;
	}

	vector<string> v = string_to_vector(s); // convert to vector of strings
	if(!project_syntax(v)){ // check for proper syntax
		cout << "Check Syntax !!!" << endl;
		return NULL;
	}

	table* tab = load_table(v[v.size()-1]); // load table into memory

	if(tab==NULL){
		cout << "Empty Set !!!" << endl; // if nothing is reported return NULL
		return NULL;
	}
	vector<string> attr_list;
	for(int i=1;i<v.size();i++){ // get list of attributes
		if(v[i]=="from"){
			break;
		}
		attr_list.push_back(v[i]);
	}
	if(attr_list.size()==1 && attr_list[0]=="*"){ // if list  = * then set it to complete attribute list
		attr_list = tab->tot_index;
	}

	table* new_table = new table();

	(new_table->tot_index) = attr_list;

	int int_index = 1;
	int string_index = 1;
	int index = 1;
	vector<int> aux_int;
	vector<string> aux_string;

	for(int i=0;i<attr_list.size();i++){ // make structure of new table similar to the old one
		if((tab->mint)[attr_list[i]]!=0){

			(new_table->mint)[attr_list[i]] = int_index;
			int_index++;
			(new_table->vint).push_back((tab->vint)[(tab->mint)[attr_list[i]]-1]);
		}
		else{

			(new_table->mstring)[attr_list[i]] = string_index;
			string_index++;
			(new_table->vstring).push_back((tab->vstring)[(tab->mstring)[attr_list[i]]-1]);
		}
		(new_table->attr_index)[attr_list[i]] = index;
		index++;
	}

	table* final_table = remove_redundancy(new_table); // remove redundancy from table

	return final_table; // return the final answer

}

struct table* project(vector<string> attr_list, struct table* tab){

	table* new_table = new table(); //similar to the previous implementation but attribute list and table are
	(new_table->tot_index) = attr_list; // received as input

	int int_index = 1;
	int string_index = 1;
	int index = 1;
	vector<int> aux_int;
	vector<string> aux_string;

	for(int i=0;i<attr_list.size();i++){
		if((tab->mint).count(attr_list[i])!=0){

			(new_table->mint)[attr_list[i]] = int_index;
			int_index++;
			(new_table->vint).push_back((tab->vint)[(tab->mint)[attr_list[i]]-1]);
		}
		else{

			(new_table->mstring)[attr_list[i]] = string_index;
			string_index++;
			(new_table->vstring).push_back((tab->vstring)[(tab->mstring)[attr_list[i]]-1]);
		}
		(new_table->attr_index)[attr_list[i]] = index;
		index++;
	}

	table* final_table = remove_redundancy(new_table);


	delete new_table;

	return final_table;

}



