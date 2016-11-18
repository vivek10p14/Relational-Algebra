/*
 * evaluation.cpp
 *
 *  Created on: 15-Oct-2016
 *      Author: vivek10p14
 */

#include "header.h"

using namespace std;

bool eval_condition(struct table* temp, int x, string s){ // evaluation of a single condition stored in a string s for given tuple at index x
	vector<string> v = string_to_vector(s);
	bool find1,find2;
	if((temp->attr_index).count(v[0])==1){ // if both lhs and rhs are attributes
		find1 = true;
	}
	else{
		find1 = false;
	}
	if((temp->attr_index).count(v[2])==1){
		find2 = true;
	}
	else{
		find2 = false;
	}

	if(find1 && find2){ // if both are attributes they must be of same type
		// check for all types of comparators
		if(v[1]=="="){
			if((temp->mint).count(v[0])==0){
				return( (temp->vstring)[(temp->mstring)[v[0]]-1][x] == (temp->vstring)[(temp->mstring)[v[2]]-1][x] );
			}
			else{
				return( (temp->vint)[(temp->mint)[v[0]]-1][x] == (temp->vint)[(temp->mint)[v[2]]-1][x] );
			}
		}
		if(v[1]=="<"){
			if((temp->mint).count(v[0])==0){
				return( (temp->vstring)[(temp->mstring)[v[0]]-1][x] < (temp->vstring)[(temp->mstring)[v[2]]-1][x] );
			}
			else{
				return( (temp->vint)[(temp->mint)[v[0]]-1][x] < (temp->vint)[(temp->mint)[v[2]]-1][x] );
			}
		}
		if(v[1]==">"){
			if((temp->mint).count(v[0])==0){
				return( (temp->vstring)[(temp->mstring)[v[0]]-1][x] > (temp->vstring)[(temp->mstring)[v[2]]-1][x] );
			}
			else{
				return( (temp->vint)[(temp->mint)[v[0]]-1][x] > (temp->vint)[(temp->mint)[v[2]]-1][x] );
			}
		}
		if(v[1]=="!="){
			if((temp->mint).count(v[0])==0){
				return( (temp->vstring)[(temp->mstring)[v[0]]-1][x] != (temp->vstring)[(temp->mstring)[v[2]]-1][x] );
			}
			else{
				return( (temp->vint)[(temp->mint)[v[0]]-1][x] != (temp->vint)[(temp->mint)[v[2]]-1][x] );
			}
		}
		if(v[1]==">="){
			if((temp->mint).count(v[0])==0){
				return( (temp->vstring)[(temp->mstring)[v[0]]-1][x] >= (temp->vstring)[(temp->mstring)[v[2]]-1][x] );
			}
			else{
				return( (temp->vint)[(temp->mint)[v[0]]-1][x] >= (temp->vint)[(temp->mint)[v[2]]-1][x] );
			}
		}
		if(v[1]=="<="){
			if((temp->mint).count(v[0])==0){
				return( (temp->vstring)[(temp->mstring)[v[0]]-1][x] <= (temp->vstring)[(temp->mstring)[v[2]]-1][x] );
			}
			else{
				return( (temp->vint)[(temp->mint)[v[0]]-1][x] <= (temp->vint)[(temp->mint)[v[2]]-1][x] );
			}
		}

	}
	else if(find1){ // if one of them is an attribute the other must me compatible to compare
		// check for all comparators
		if((temp->mint).count(v[0])==0){
			//cout << "yak" << endl;
			if(v[1]=="="){
				//cout << "wall" << endl;
				//cout <<  (temp->vstring)[(temp->mstring)[v[0]]-1][x] << endl;
				return( (temp->vstring)[(temp->mstring)[v[0]]-1][x] == v[2] );
			}
			if(v[1]=="<"){
				return( (temp->vstring)[(temp->mstring)[v[0]]-1][x] < v[2] );
			}
			if(v[1]==">"){
				return( (temp->vstring)[(temp->mstring)[v[0]]-1][x] > v[2] );
			}
			if(v[1]=="!="){
				return( (temp->vstring)[(temp->mstring)[v[0]]-1][x] != v[2] );
			}
			if(v[1]=="<="){
				return( (temp->vstring)[(temp->mstring)[v[0]]-1][x] <= v[2] );
			}
			if(v[1]==">="){
				return( (temp->vstring)[(temp->mstring)[v[0]]-1][x] >= v[2] );
			}
		}
		else{
			int y = string_to_int(v[2]);
			if(v[1]=="="){
				return( (temp->vint)[(temp->mint)[v[0]]-1][x] == y );
			}
			if(v[1]=="<"){
				return( (temp->vint)[(temp->mint)[v[0]]-1][x] < y );
			}
			if(v[1]==">"){
				return( (temp->vint)[(temp->mint)[v[0]]-1][x] > y );
			}
			if(v[1]=="!="){
				return( (temp->vint)[(temp->mint)[v[0]]-1][x] != y );
			}
			if(v[1]=="<="){
				return( (temp->vint)[(temp->mint)[v[0]]-1][x] <= y );
			}
			if(v[1]==">="){
				return( (temp->vint)[(temp->mint)[v[0]]-1][x] >= y );
			}
		}
	}
	else if(find2){ // if one of them is attribute the other must be of comparable type
		// check for all possible comparators
		if((temp->mint).count(v[2])==0){
			if(v[1]=="="){
				return( (temp->vstring)[(temp->mstring)[v[2]]-1][x] == v[0] );
			}
			if(v[1]=="<"){
				return( (temp->vstring)[(temp->mstring)[v[2]]-1][x] < v[0] );
			}
			if(v[1]==">"){
				return( (temp->vstring)[(temp->mstring)[v[2]]-1][x] > v[0] );
			}
			if(v[1]=="!="){
				return( (temp->vstring)[(temp->mstring)[v[2]]-1][x] != v[0] );
			}
			if(v[1]=="<="){
				return( (temp->vstring)[(temp->mstring)[v[2]]-1][x] <= v[0] );
			}
			if(v[1]==">="){
				return( (temp->vstring)[(temp->mstring)[v[2]]-1][x] >= v[0] );
			}
		}
		else{
			int y = string_to_int(v[0]);
			if(v[1]=="="){
				return( (temp->vint)[(temp->mint)[v[2]]-1][x] == y );
			}
			if(v[1]=="<"){
				return( (temp->vint)[(temp->mint)[v[2]]-1][x] < y );
			}
			if(v[1]==">"){
				return( (temp->vint)[(temp->mint)[v[2]]-1][x] > y );
			}
			if(v[1]=="!="){
				return( (temp->vint)[(temp->mint)[v[2]]-1][x] != y );
			}
			if(v[1]=="<="){
				return( (temp->vint)[(temp->mint)[v[2]]-1][x] <= y );
			}
			if(v[1]==">="){
				return( (temp->vint)[(temp->mint)[v[2]]-1][x] >= y );
			}
		}
	}
	else{ // if none is attribute the just assume then to be strings and compare
		// check for all possible comparators
		if(v[1]=="="){
			return( v[0]==v[2] );
		}
		if(v[1]=="<"){
			return( v[0]<v[2] );
		}
		if(v[1]==">"){
			return( v[0]>v[2] );
		}
		if(v[1]=="!="){
			return( v[0]!=v[2] );
		}
		if(v[1]=="<="){
			return( v[0]<=v[2] );
		}
		if(v[1]==">="){
			return( v[0]>=v[2] );
		}
	}
	return true;
}

bool eval_postfix(struct table* temp, int x, map<char, string> m, string s){ // evaluate postfix expression for a given tuple at index x

	int l = s.length();

	stack<bool> st; // stack to store return value of each condition
	for(int i=0;i<l;i++){
		if(s[i]=='&' || s[i]=='|'){ // if operator is found pop top 2 elements and apply the operator on them and push the result
			bool x1,x2;
			x1 = st.top();
			st.pop();
			x2 = st.top();
			st.pop();
			if(s[i]=='&'){
				st.push(x1 && x2);
			}
			else{

				st.push(x1 || x2);

			}
		}
		else{

			bool k = eval_condition(temp,x,m[s[i]]); // else evaluate the condition and push its value

			st.push(k);
		}
	}

	return st.top(); // finally return the top of stack
}

struct table* select_ans(struct table* temp, map<char, string> m, string s){ // the first function to start the evaluation of where clause
	table* tab = new table(); // create a new table
	tab->tot_index = temp->tot_index; // copy the table structure
	tab->attr_index = temp->attr_index;
	tab->mint = temp->mint;
	tab->mstring = temp->mstring;
	vector<int> aux_int;
	vector<string> aux_string;
	for(int i=0;i<(temp->vint).size();i++){
		(tab->vint).push_back(aux_int);
	}
	for(int i=0;i<(temp->vstring).size();i++){
		(tab->vstring).push_back(aux_string);
	}
	int tuple = 0;
	if((temp->vint).size()!=0){
		tuple = (temp->vint)[0].size();
	}
	else if((temp->vstring).size()!=0){
		tuple = (temp->vstring)[0].size();
	}
	if(tuple==0){
		cout << "Empty Table" << endl;
		return NULL;
	}

	for(int i=0;i<tuple;i++){ // for each tuple in the table

		if(eval_postfix(temp,i,m,s)){ // if the postfix expression holds true

			for(int j=0;j<(temp->vint).size();j++){ // copy that tuple in the new table

				(tab->vint)[j].push_back((temp->vint)[j][i]);

			}
			//cout << "toy" << endl;
			for(int j=0;j<(temp->vstring).size();j++){
				//cout << (temp->vstring).size() << endl;
				(tab->vstring)[j].push_back((temp->vstring)[j][i]);
			}
		}
	}
	return tab; // return the new table
}

struct table* nested_eval(string postfix, map<char, string> operators, map<char, string> operands, map<char, string> types){
	stack<struct table*> st; // create a table* stack as each operation would return a table

	int l = postfix.length();

	for(int i=0;i<l;i++){

		if(postfix[i]>='A' && postfix[i]<='Z'){ // operand here means a table that is to be directly loaded into memory
			table* t = load_table(operands[postfix[i]]);

			if(t!=NULL){
				st.push(t); // after loading if successful push it to stack
			}
			else{
				cout << "NULL returned while loading table !!!" << endl;
				return NULL;
			}
		}
		else{ // if operator is found
			if(types[postfix[i]]=="rename"){ //check operator type
				string s = operators[postfix[i]];
				vector<string> v = string_to_vector(s); // based on operator type find its input parameters
				table* t = st.top();
				st.pop();
				table* t1 = rename(v,t); // evaluate that operation
				if(t1!=NULL){
					st.push(t1); // if not NULL push to stack
				}
				else{
					cout << "NULL returned while renaming !!!" << endl; // is NULL is returned show error and exit
					return NULL;
				}

			}
			else if(types[postfix[i]]=="union"){ // same applies throughout this function

				table* t1 = st.top();
				st.pop();
				table* t2 = st.top();
				st.pop();
				table* t3 = set_union(t2,t1);
				if(t3!=NULL){
					st.push(t3);
				}
				else{
					cout << "NULL returned while performing union !!!" << endl;
					return NULL;
 				}
			}
			else if(types[postfix[i]]=="difference"){
				table* t1 = st.top();
				st.pop();
				table* t2 = st.top();
				st.pop();
				table* t3 = set_difference(t2,t1);
				if(t3!=NULL){
					st.push(t3);
				}
				else{
					cout << "NULL returned while performing difference !!!" << endl;
					return NULL;
 				}
			}
			else if(types[postfix[i]]=="product"){
				table* t1 = st.top();
				st.pop();
				table* t2 = st.top();
				st.pop();
				table* t3 = product(t2,t1);
				if(t3!=NULL){
					st.push(t3);
				}
				else{
					cout << "NULL returned while performing product !!!" << endl;
					return NULL;
 				}
			}
			else if(types[postfix[i]]=="select"){
				string s = operators[postfix[i]];
				vector<string> v = string_to_vector(operators[postfix[i]]);
				table* t = st.top();
				st.pop();
				table* t2 = select(v,s,t);
				if(t2!=NULL){
					st.push(t2);
				}
				else{
					cout << "NULL returned while performing select !!!" << endl;
					return NULL;
				}
			}
			else if(types[postfix[i]]=="project"){
				table* t = st.top();
				st.pop();
				string s = operators[postfix[i]];
				vector<string> v = string_to_vector(s);
				vector<string> attr_list;
				for(int i=1;i<v.size();i++){
					if(v[i]=="from"){
						break;
					}
					attr_list.push_back(v[i]);
				}
				if(attr_list.size()==1 && attr_list[0]=="*"){
					attr_list = t->tot_index;
				}
				table* t1 = project(attr_list,t);
				if(t1!=NULL){
					st.push(t1);
				}
				else{
					cout << "NULL returned while projection !!!" << endl;
					return NULL;
				}
			}
		}

	}
	table* final_ans = st.top(); // finally return top of the stack
	st.pop();

	return final_ans;

}



