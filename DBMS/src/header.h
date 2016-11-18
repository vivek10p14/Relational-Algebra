/*
 * header.h
 *
 *  Created on: 09-Oct-2016
 *      Author: Vivek Sourabh
 */

#ifndef HEADER_H_
#define HEADER_H_

#include <iostream> // included libraries
#include <string.h>
#include <vector>
#include <tr1/unordered_map>
#include <string.h>
#include <fstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <cstdlib>
#include <sstream>
#include <map>
#include <algorithm>

using namespace std;

extern string curr_database; //store the value of current database

extern tr1::unordered_map<string,int> keywords; //store keywords that are being used

extern tr1::unordered_map<string, int> precedence; //store precedence of relational operators for postfix conversion

extern string init_path; // store path to working directory

struct table{ //the structure that is being used to store the table

	vector< vector<int> > vint; //vector of vector of integers to store the integer values
	vector< vector<string> > vstring; //vector of vector of strings to store the string values
	tr1::unordered_map<string, int> mint; //map to store index of integer attributes
	tr1::unordered_map<string, int> mstring; //map to store index of string attributes
	tr1::unordered_map<string, int> attr_index; // map to store index of all the attributes
	vector<string> tot_index; // vector to store attribute names

};

void create_database(string s); //function to create database

char* string_to_array(string s); // function to convert string to character array

string array_to_string(char* s); // function to convert character array to string

bool poss_string_to_int(string s); // function to check if a string can be converted to integer

void show_databases(); // function to display all databases

void use_db(string s); // change the present working database

void show_tables(); // show list of tables present in the current database

void create_table(string s); // function to create table

vector<string> string_to_vector(string s); // convert string to vector of strings with individual words

bool proper_create_syntax(vector<string> v, char* path); // check syntax of create statement

void initialize(); // to set initial variables

bool check_db(); // check if a database has been selected

void desc_table(string s); // see description of table

bool desc_table_syntax(vector<string> v, char* path); // check syntax of describe table

void insert(string s); // insert values into table

bool insert_syntax(vector<string> v); // check syntax for insert statement

struct table* project(string s); // function to project from a table

struct table* project(vector<string> v, struct table* t); // function to project from a table

bool project_syntax(vector<string> s); // check syntax of project function

bool table_in_database(string s); // check if a given table exists in the present database

struct table* load_table(string tab_name); // load table from file to memory

int string_to_int(string s); // convert string to integer

string int_to_string(int x); // convert integer to string

struct table* remove_redundancy(struct table* temp); // remove redundancy from table

void print_table(struct table* temp); // print a given table

struct table* set_union(string s); // perform union operation

struct table* set_union(struct table* table1, struct table* table2); // perform union operation

struct table* set_difference(string s); // perform set difference operation

struct table* set_difference(struct table* table1, struct table* table2); // perform set difference operation

bool proper_union(vector<string> v); // check syntax of union statement

bool proper_diff(vector<string> v); // check syntax of set difference operation

string vector_to_string(vector<string> v); // concatenate elements of vector to string

struct table* product(string s); // perform cartesian product

struct table* product(struct table* table1, struct table* table2); // perform cartesian product

bool proper_product(vector<string> v); // check syntax of product

struct table* rename(string s); // rename operation

struct table* rename(vector<string> attr, struct table* tab); // renmae operation

bool proper_rename(vector<string> v); // check syntax of rename operation

struct table* select(string s); // select operation

struct table* select(vector<string> attr, string exp, struct table* tab); //select operation

bool proper_select(vector<string> s); // check syntax of select operation

string in_to_post(string s); // convert infix to postfix for where clause

bool is_high(char a, char b); // check precedence for where clause

bool is_operand(char c); // check id character c is an operand

bool balanced_paranthesis(string s); // check for balanced paranthesis in a string

struct table* select_ans(struct table* temp, map<char, string> m, string s);// evaluate the where of a select statement

bool eval_condition(struct table* temp, int x, string s); // evaluate an individual condition of where clause

bool eval_postfix(struct table* temp, int x, map<char, string>, string s); // evaluate the postfix expression of the where clause

bool condition_checks(struct table* temp, map<char, string>); // check if conditions of where clause are proper

struct table* nested(string s); // solve nested queries

string infix_post(string s, map<char,string> m); // infix to postfix conversion for nested queries;

bool nested_operand(char c); // check if character is an operand in a nested query

bool high(string a, string b); // check precedence in a nested query

struct table* nested_eval(string postfix, map<char, string> m1, map<char, string> m2, map<char, string> m3); // evaluate a nested query

#endif /* HEADER_H_ */
