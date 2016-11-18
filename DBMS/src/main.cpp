/*
 * main.cpp
 *
 *  Created on: 10-Oct-2016
 *      Author: vivek10p14
 */

#include "header.h"

using namespace std;

int main(){

	initialize(); // initialize the code by setting the extern vaiables

	int k = 0;

	string s;

	while(1){
		cout << "DB->";
		getline(cin,s); // take input
		string aux = "";
		int l = s.length();
		for(int i=0;i<l;i++){ // get first word of input
			if(s[i]==' '){
				break;
			}
			else{
				aux = aux + s[i];
			}
		}
		vector<string> v = string_to_vector(s); // convert the input to vector of strings
		if(s[0]=='(' || s[0]=='{'){ // condition for being a nested query
			try{
				table* tab = nested(s);
				print_table(tab);
				if(tab){
					delete tab;
				}
			}
			catch(const exception& ex){
				cout << "Query could not execute !!!" << endl;
			}
		}
		else if(find(v.begin(),v.end(),"product")!=v.end()){ // condition for product query
			try{
				table* tab = product(s);
				print_table(tab);
				if(tab){
					delete tab;
				}
			}
			catch(const exception& ex){
				cout << "Query Could not execute !!!" << endl;
			}
		}
		else if(find(v.begin(),v.end(),"union")!=v.end()){ // condition for union query
			try{
				table* tab = set_union(s);
				print_table(tab);
				if(tab){
					delete tab;
				}
			}
			catch(const exception& ex){
				cout << "Query Could not execute !!!" << endl;
			}
		}
		else if(find(v.begin(),v.end(),"difference")!=v.end()){ // condition for set difference
			try{
				table* tab = set_difference(s);
				print_table(tab);
				if(tab){
					delete tab;
				}
			}
			catch(const exception& ex){
				cout << "Query Could not execute !!!" << endl;
			}
		}
		else if(s=="show databases"){ // show databases
			try{
				show_databases();
			}
			catch(const exception& ex){
				cout << "Query could not execute !!!" << endl;
			}
		}
		else if(s=="show tables"){ // show tables
			try{
				show_tables();
			}
			catch(const exception& ex){
				cout << "Query Could not execute !!!" << endl;
			}
		}
		else if(aux=="use"){ // select database
			try{
				use_db(v[1]);
			}
			catch(const exception& ex){
				cout << "Query Could not execute !!!" << endl;
			}
		}
		else if(aux=="create"){ // create database or table
			if(s[7]=='d'){ // create database
				try{
					vector<string> q = string_to_vector(s);
					create_database(v[2]);
				}
				catch(const exception& ex){
					cout << "Query Could not execute !!!" << endl;
				}
			}
			else{ // create table
				try{
					create_table(s);
				}
				catch(const exception& ex){
					cout << "Query Could not execute !!!" << endl;
				}
			}
		}
		else if(aux=="desc"){ // decribe table
			try{
				desc_table(s);
			}
			catch(const exception& ex){
				cout << "Query Could not execute !!!" << endl;
			}
		}
		else if(aux=="select"){ // condition for select query
			try{
				table* tab = select(s);
				print_table(tab);
				if(tab){
					delete tab;
				}
			}
			catch(const exception& ex){
				cout << "Query Could not execute !!!" << endl;
			}
		}
		else if(aux=="project"){ // condition for project query
			try{
				table* tab = project(s);
				print_table(tab);
				if(tab){
					delete tab;
				}
			}
			catch(const exception& ex){
				cout << "Query Could not execute !!!" << endl;
			}
		}
		else if(aux=="rename"){ // condition for rename query
			try{
				table* tab = rename(s);
				print_table(tab);
				if(tab){
					delete tab;
				}
			}
			catch(const exception& ex){
				cout << "Query Could not execute !!!" << endl;
			}
		}
		else if(s=="exit"){ // if input is exit return form main program
			cout << "BYE !!!" << endl;
			return 0;
		}
		else if(aux=="insert"){ // condition for insert into table query
			try{
				insert(s);
			}
			catch(const exception& ex){
				cout << "Query Could not execute !!!" << endl;
			}
		}
		else{ // if none of the conditions is met classify the query as unrecognized
			if(k==0){
				cout << "Server Started" << endl;
				k++;
			}
			else{
				cout << "Query not recognized !!!" << endl;
			}
		}

	}


	return 0;
}


