/*
 * infix_postfix.cpp
 *
 *  Created on: 15-Oct-2016
 *      Author: vivek10p14
 */

#include "header.h"

using namespace std;

bool is_operand(char c){ // check if a character is operand operator
	if(c=='&' || c=='|' || c=='(' || c==')'){
		return false;
	}
	return true;
}

bool is_high(char a, char b){ // return true if precedence of character a is greater
	if(a=='&'){
		return true;
	}
	return false;
}

bool balanced_paranthesis(string s){ // check for balanced paranthesis
	int l = s.length();
	stack<char> st;
	for(int i=0;i<l;i++){
		if(s[i]=='{' || s[i]=='(' || s[i]=='['){ // if opening bracket push to stack
			st.push(s[i]);
		}
		else if(s[i]=='}'){ // if closing then top of stack must be opening of same type
			if(st.empty()){
				return false;
			}
			if(st.top()=='{'){
				st.pop();
			}
			else{
				return false;
			}
		}
		else if(s[i]==']'){
			if(st.empty()){
				return false;
			}
			if(st.top()=='['){
				st.pop();
			}
			else{
				return false;
			}
		}
		else if(s[i]==')'){
			if(st.empty()){

				return false;
			}
			if(s[i]==')'){
				st.pop();

			}
			else{

				return false;
			}
		}

	}
	if(st.empty()){
		return true; // at the end stack must be empty
	}
	else{

		return false;
	}
}

string in_to_post(string s){ // convert infix to postfix(where clause conditions)
	int l = s.length(); // all individual conditions have been mapped to a	character
	string infix = "";
	for(int i=0;i<l;i++){
		if(s[i]!=' '){
			infix = infix + s[i];
		}
	}
	//cout << infix << endl;
	string postfix = "";
	stack<char> st;
	l = infix.length();
	int i = 0;
	while(i<l){ // use the standard algorithm for infix to post fix conversion
		if(infix[i]=='('){
			st.push(infix[i]);
		}
		else if(is_operand(infix[i])){
			postfix = postfix + infix[i];
		}
		else if(infix[i]=='&'){ // precedence of and is greater than or
			st.push(infix[i]);
		}
		else if(infix[i]=='|'){

			while(!st.empty() && st.top()=='&'){
				postfix = postfix + st.top();
				st.pop();
			}

			st.push(infix[i]);
		}
		else if(infix[i]==')'){
			while(st.top()!='('){
				postfix = postfix + st.top();
				st.pop();
			}
			st.pop();
		}
		i++;
	}
	while(!st.empty()){ // after end of above loop empty the stack
		if(st.top()=='&' || st.top()=='|'){
			postfix = postfix + st.top();
		}
		st.pop();
	}

	return postfix;
}

bool nested_operand(char c){ // check if character is operand in a nested query
	if(c>='A' && c<='Z'){ // each operand of a nested query has been mapped to a character between A-Z
		return true;
	}
	return false; // each opeartor has been mapped to a character between a-z
}

bool high(string a, string b){ // check precedence of operators using the extern map
	if(precedence[a]>=precedence[b]){
		return true;
	}
	return false;
}

string infix_post(string s,map<char,string> m){ // convert infix to postfix
	int l = s.length(); // map m has the mapping of each operator representation to its type e.g. a-> select, b-> project etc.

	stack<char> st;
	string postfix = "";
	for(int i=0;i<l;i++){ // use standard algorithm for infix to postfix conversion
		if(nested_operand(s[i])){
			postfix = postfix + s[i];

		}
		else{
			if(s[i]=='('){
				st.push(s[i]);
			}
			else if(s[i]==')'){
				while(st.top()!='('){
					postfix = postfix + st.top();

					st.pop();
				}
				st.pop();
			}
			else{
				while(!st.empty() && st.top()!=')'){
					if(high(m[st.top()],m[s[i]])){ // precedence is checked from the extern map
						postfix = postfix + st.top();

						st.pop();
					}
					else{
						break;
					}
				}
				st.push(s[i]);
			}
		}

	}
	while(!st.empty()){
		postfix = postfix + st.top();

		st.pop();
	}
	return postfix; //return postfix
}



