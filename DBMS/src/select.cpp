/*
 * select.cpp
 *
 *  Created on: 15-Oct-2016
 *      Author: vivek10p14
 */

#include "header.h"

using namespace std;

map<char, string> m; // stores the mapping of individual conditions in where clause



struct table* select(string s){
	if(!check_db()){
		cout << "Select Database !!!" << endl; // check if database is selected
		return NULL;
	}
	vector<string> v = string_to_vector(s);
	if(!proper_select(v)){
		cout << "Check Syntax !!!" << endl; // check for proper syntax
		return NULL;
	}


	vector<string> attr;
	string tab_name = v[v.size()-1]; // get table name
	table* tab = load_table(tab_name); // load table into memory

	for(int i=1;i<v.size();i++){ // get attribute list
		if(v[i]=="where"){
			break;
		}
		else{
			attr.push_back(v[i]);
		}
	}
	if(attr.size()==1 && attr[0]=="*"){ // if list== * set it to all attributes
		attr = (tab->tot_index);
	}

	string exp = ""; // get the where clause
	int flag = 0;
	for(int i=0;i<s.length();i++){
		if(flag==1 && s[i]!='%'){
			exp = exp + s[i];
		}
		if(s[i]=='#'){ // conditions in where clause start with a #
			flag = 1;
		}
		if(s[i]=='%'){ // conditions in where clause ends with %
			break;
		}
	}
	string aux = "";
	int len = exp.size();
	string exr = "";
	char c = 'A';
	int i=0;

	while(i<len){ // get the expression after mapping of individual conditions
		if(exp[i]=='['){
			i++;
			while(exp[i]!=']'){
				aux = aux + exp[i];
				i++;
			}
			i++;
			m[c] = aux;
			aux = "";
			exr = exr + c;
			c++;
		}
		else{
			exr = exr + exp[i];
			i++;
		}
	}

	if(!balanced_paranthesis(exr)){
		cout << "Paranthesis not balanced !!!" << endl; // check for balanced paranthesis
		return NULL;
	}

	string postfix = in_to_post(exr); // convert to postfix

	if(!condition_checks(tab, m)){
		cout << "Check Syntax !!!" << endl; // check for datatype compatibility in individual conditions
		return NULL;
	}

	table* tabl = select_ans(tab,m,postfix); // evaluate the where clause and return the answer

	table* final_ans = project(attr,tabl); // project the required attributes

	delete tab; // free extra memory
	delete tabl;

	return final_ans;

}

struct table* select(vector<string> v, string s, struct table* tab){
	// same as previous implementation
	// the table to be loaded and the string upto where clause are given as inputs
	// the vector form of that string is also given as input
	vector<string> attr;

	for(int i=1;i<v.size();i++){
		if(v[i]=="where"){
			break;
		}
		else{
			attr.push_back(v[i]);
		}
	}
	if(attr.size()==1 && attr[0]=="*"){
		attr = (tab->tot_index);
	}

	string exp = "";
	int flag = 0;
	for(int i=0;i<s.length();i++){
		if(flag==1 && s[i]!='%'){
			exp = exp + s[i];
		}
		if(s[i]=='#'){
			flag = 1;
		}
		if(s[i]=='%'){
			break;
		}
	}
	string aux = "";

	int len = exp.size();
	string exr = "";
	char c = 'A';
	int i=0;

	while(i<len){
		if(exp[i]=='['){
			i++;
			while(exp[i]!=']'){
				aux = aux + exp[i];
				i++;
			}
			i++;
			m[c] = aux;
			aux = "";
			exr = exr + c;
			c++;
		}
		else{
			exr = exr + exp[i];
			i++;
		}
	}

	if(!balanced_paranthesis(exr)){
		cout << "Paranthesis not balanced !!!" << endl;
		return NULL;
	}

	string postfix = in_to_post(exr);

	if(!condition_checks(tab, m)){
		cout << "Check Syntax !!!" << endl;
		return NULL;
	}

	table* tabl = select_ans(tab,m,postfix);


	table* final_ans = project(attr,tabl);


	delete tab;
	delete tabl;

	return final_ans;


}



