/*
 * nested.cpp
 *
 *  Created on: 15-Oct-2016
 *      Author: vivek10p14
 */

#include "header.h"

using namespace std;

map<char, string> operators; // store mapping of operators
map<char, string> operands; // store mapping of operands

map<char,string> type; // store mapping of operators to types

struct table* nested(string s){

	int l = s.length();
	string str = "";
	string aux = "";
	char rator = 'a';
	char rand = 'A';
	int i = 0;
	while(i<l){
		if(s[i]=='<'){ // each operand is surrounded by <>
			i++;
			while(s[i]!='>'){
				aux = aux+s[i];
				i++;
			}
			operands[rand] = aux;

			str = str + rand;
			aux = "";
			rand++;
			i++;
		}
		else if(s[i]=='{'){ // each operator is surrounded by {}
			i++;
			while(s[i]!='}'){
				aux = aux + s[i];
				i++;
			}
			operators[rator] = aux;

			str = str + rator;
			aux = "";
			rator++;
			i++;
		}
		else{
			str = str + s[i];
			i++;
		}
	}

	for(map<char,string>::iterator it=operators.begin();it!=operators.end();++it){ // map each operator to its type
		string s1 = it->second;
		string aux = "";
		int l = s1.length();
		for(int i=0;i<l;i++){
			if(s1[i]==' '){ // to find type check the first word of the query
				break;
			}
			else{
				aux = aux + s1[i];
			}
		}
		type[it->first] = aux;
	}

	if(!balanced_paranthesis(str)){
		cout << "Unbalanced Paranthesis !!!" << endl; // check for balanced paranthesis
		return NULL;
	}

	string postfix = infix_post(str,type); // convert infix to postfix

	table* ans = nested_eval(postfix,operators,operands,type); // call for evaluation

	return ans; // return answer


}


