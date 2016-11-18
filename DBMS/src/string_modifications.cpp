/*
 * string_modifications.cpp
 *
 *  Created on: 10-Oct-2016
 *      Author: vivek10p14
 */

#include "header.h"

char* string_to_array(string s){
	char* ans = new char[s.length()+1]; // convert string to character array
	strcpy(ans,s.c_str());
	return ans;
}

string array_to_string(char* s){
	string ans = ""; // convert character array to string
	int l = strlen(s);
	for(int i=0;i<l;i++){
		ans = ans + s[i];
	}
	return ans;
}



vector<string> string_to_vector(string s){
	vector<string> v; // convert string to vector form
	int l = s.length();
	string aux = "";
	for(int i=0;i<l;i++){
		if(s[i]==' ' || s[i]==','){ // get all word separated by comma or space and push it to vector
			if(aux!=""){
				v.push_back(aux);
			}
			aux = "";
		}
		else{
			aux = aux + s[i];
		}
	}
	if(aux!=""){
		v.push_back(aux);
	}

	return v;
}

bool poss_string_to_int(string s){
	int l = s.length(); // check if string can be a potential intger
	if(s[0]=='-'){ // all characters must be between 0-9 first character can be '-'
		for(int i=1;i<l;i++){
			if(s[i]>='0' && s[i]<='9'){
				int q = 1;
			}
			else{
				return false;
			}
		}
	}
	else{
		for(int i=0;i<l;i++){
			if(s[i]>='0' && s[i]<='9'){
				int q = 1;
			}
			else{
				return false;
			}
		}
	}



	return true;
}

int string_to_int(string s){ // convert string to integer
	int k = 0;
	int l = s.length();
	if(s[0]=='-'){
		k++;
	}
	int sum = 0;
	for(int i=k;i<l;i++){
		sum = sum*10 + (s[i]-'0');
	}
	if(k==1){
		sum = 0 - sum;
	}
	return sum;
}

string int_to_string(int x){ // convert integer to string using stringstream
	stringstream ss;
	ss << x;
	string a = ss.str();
	return a;
}

string vector_to_string(vector<string> v){  // convert vector to string by combining components
	// join components using space
	string ans = "";
	for(int i=0;i<v.size();i++){
		ans = ans + v[i];
		if(i!=v.size()-1){
			ans = ans + ' ';
		}
	}
	return ans;
}



