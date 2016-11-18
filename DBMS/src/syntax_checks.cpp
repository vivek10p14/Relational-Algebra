/*
 * syntax_checks.cpp
 *
 *  Created on: 11-Oct-2016
 *      Author: vivek10p14
 */

#include "header.h"

using namespace std;


bool check_db(){
	if(curr_database.length()==0){
		cout << "Select a Database" << endl; // if length of extern variable is 0 then no database has been selected
		return false;
	}
	else{
		return true;
	}
}

bool proper_create_syntax(vector<string> v, char* path){
	if(v.size()<5){ // there need to be atleast 5 words in the query
		return false;
	}
	if(v[1]!="table"){
		cout << "Use Syntax: create table tab_name !!" << endl; // second word must be table
		return false;
	}
	string tab_name = v[2]; // third word gives table name
	if(keywords[tab_name]==1){
		cout << "Keyword cannot be a table name" << endl; // check table name is not a keyword
	}
	if((v.size()-3)%2!=0){
		cout << "Check Syntax" << endl; // length of remaining query must be divisible by 2  i.e. attribute name, type pairs
		return false;
	}
	tr1::unordered_map<string,int> attr_names; // store all attribute names in map to ensure no name is repeated
	for(int i=4;i<=v.size()-1;i=i+2){
		if(keywords[v[i-1]]==0){
			attr_names[v[i-1]] = 1;
		}
		else{
			cout << "Keyword cannot be used as column name" << endl;
			return false;
		}
		if(v[i]!="int" && v[i]!="string"){
			cout << "Data type error !!!" << endl; // data type must be either int or string
			return false;
		}

	}
	if(attr_names.size()!=(v.size()-3)/2){
		cout << "Column names cannot repeat !!" << endl;
		return false;
	}

	ifstream file;
	file.open(path);
	if(file.peek()==ifstream::traits_type::eof()){
		file.close();
		return true;
	}
	if(file.is_open()){
		char output[1000];
		while(!file.eof()){
			file >> output;
			if(output==tab_name){
				cout << "Table Name Exists !!!" << endl; // check if table name is valid i.e has not appeared before
				file.close();
				return false;
			}
		}
		file.close();
		return true;
	}
	else{
		cout << "Unexpected Error !!!" << endl;
		return false;
	}

	return true;
}

bool desc_table_syntax(vector<string> v, char* path){ // desc tab_name
	if(v[0]!="desc"){
		cout << "Syntax Error !!!" << endl; // first word must be desc
		return false;
	}
	if(v.size()!=2){
		cout << "Syntax Error !!!" << endl; // size of query must be 2
		return false;
	}

	string tab_name = v[1]; // second word represents query name

	ifstream file;
	file.open(path);
	if(file.peek()==ifstream::traits_type::eof()){ // check if table exists
		file.close();
		cout << "Table Does not Exist" << endl;
		return false;
	}
	if(file.is_open()){
		char output[1000];

		while(!file.eof()){
			file >> output;

			if(output==tab_name){
				cout << "************" << endl;
				cout << tab_name << endl; // if table is found print it and return true
				cout << "************" << endl;
				file.close();
				return true;
			}
		}
		file.close();
		return false;
	}
	else{
		cout << "Unexpected Error !!!" << endl; // error if unable to open file
		return false;
	}

	return false;

}

bool insert_syntax(vector<string> v){

	if(v[0]!="insert" || v[1]!="into"){ // first 2 words must be insert into
		cout << "Syntax Error !!!" << endl;
		cout << "Use: insert into tab_name....." << endl;
		return false;
	}

	string tab_name = v[2]; // then 3rd word must be the table name

	if(!table_in_database(tab_name)){
		cout << "Check Table Name" << endl; // check if table exists in table
		return false;
	}

	string path = "";
	path = init_path + curr_database + '/' + "desc_" + tab_name + ".txt"; // open desc file to match datatypes
	char* path_char = string_to_array(path);

	vector<string> attr_types;

	ifstream file1;

	file1.open(path_char);


	if(file1.peek()==ifstream::traits_type::eof()){
		cout << "Problem in table definition" << endl; // give error if desc file is empty
		file1.close();
		return false;
	}

	if(!file1.is_open()){
		cout << "Unexpected Error in accessing table !!!" << endl; // error if unable to access file
		return false;
	}

	char output[1000];
	int count = 0;

	while(!file1.eof()){
		if(file1.peek()==ifstream::traits_type::eof()){
			file1.close();
			break;
		}
		file1 >> output;
		count++;
		if(count%2==0){
			attr_types.push_back(array_to_string(output)); // get all attribute types
		}
	}
	file1.close();

	int num_of_attr = count/2;

	if(num_of_attr!=v.size()-3){
		cout << "Mismatch in Number of attributes!!!!" << endl; // number of attributes must be of query_size-3
		return false;
	}

	int attr_ind = 0;
	for(int i=3;i<v.size();i++){
		if(attr_types[attr_ind]=="int"){ // if attribute type is int the value must be convertible to int
			if(!poss_string_to_int(v[i])){ // for string type accept everything
				cout << "Attribute types don't match" << endl; // if mismatch occurs give error
				return false;
			}
		}
		attr_ind++;
	}


	return true;
}

bool project_syntax(vector<string> v){
	if(v[0]!="project"){
		cout << "Syntax Error !!!" << endl; // first word must be project
		return false;
	}

	vector<string> attr;
	int index_of_from = -5;

	for(int i=1;i<v.size();i++){ // get attribute list to be projected
		if(v[i]!="from"){
			attr.push_back(v[i]);
		}
		else{
			index_of_from = i;
			break;
		}
	}

	if(index_of_from!=v.size()-2){
		cout << "Syntax Error" << endl; // after from only one word should be seen i.e. the table name
		return false;
	}

	string tab_name = v[v.size()-1]; // get table name

	if(!table_in_database(tab_name)){
		cout << "Check Table Name !!!" << endl; // see if table exists in database
		return false;
	}

	if(attr.size()==0){
		cout << "No Attribute to project" << endl; // check if attribute list is empty
		return false;
	}

	string path = init_path + curr_database + '/' + "desc_" + tab_name + ".txt"; // open description file
	char* path_char = string_to_array(path);

	ifstream file;
	file.open(path_char);

	if(file.peek()==ifstream::traits_type::eof()){
		cout << "Table Definition Error !!!" << endl;
		file.close();
		return false;
	}
	if(!file.is_open()){
		cout << "Unexpected Error !!!" << endl;
		return false;
	}

	int count = 0;
	tr1::unordered_map<string,int> attr_names;
	char output[1000];
	while(!file.eof()){
		file >> output;
		count++; // store all attribute names in a map
		if(count%2==1){
			attr_names[output] = 1;
		}
	}
	file.close();
	if(attr.size()==1 && attr[0]=="*"){ // if list = * select the complete list
		return true;
	}

	cout << endl;
	for(int i=0;i<attr.size();i++){
		if(attr_names[attr[i]]!=1){
			cout << "Attribute not found !!!!!" << endl; // all attribute names must exist in the table
			return false;
		}
	}

	return true;
}

bool proper_union(vector<string> v){
	vector<string> project1,project2;
	int pivot = 0;
	for(int i=0;i<v.size();i++){ // separate the project queries
		if(v[i]=="union"){
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
	if(!project_syntax(project1) || !project_syntax(project2)){ // both project queries must be proper
		cout << "Check Syntax !!!" << endl;
		return false;
	}
	return true;
}

bool proper_diff(vector<string> v){
	vector<string> project1,project2;
	int pivot = 0;
	for(int i=0;i<v.size();i++){
		if(v[i]=="difference"){  // separate the project queries
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
	if(!project_syntax(project1) || !project_syntax(project2)){ // both project queries must be proper
		cout << "Check Syntax !!!" << endl;
		return false;
	}
	return true;
}


bool proper_product(vector<string> v){
	vector<string> project1,project2;
	int pivot = 0;
	for(int i=0;i<v.size();i++){ // separate the project queries
		if(v[i]=="product"){
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
	if(!project_syntax(project1) || !project_syntax(project2)){ // both project queries must be proper
		cout << "Check Syntax !!!" << endl;
		return false;
	}
	return true;
}

bool proper_rename(vector<string> v){
	if(v[0]!="rename"){
		cout << "Use Syntax: Rename name table_name !!!" << endl;
		return false;
	}
	string tab_name = v[v.size()-1];

	if(!table_in_database(tab_name)){
		cout << "Table Not Found" << endl; // table name must exist
		return false;
	}
	for(int i=1;i<v.size()-1;i++){
		if(keywords.count(v[i])==1){
			cout << "Renaming Not Possible !!!!" << endl; // none of the names should be keywords
			return false;
		}
	}

	return true;

}

bool proper_select(vector<string> v){
	if(v[0]!="select"){
		cout << "Use syntax: select attr where exp from tab_name !!!" << endl; // first word must be select
		return false;
	}
	string tab_name = v[v.size()-1]; // get table name
	if(!table_in_database(tab_name)){
		cout << "Table Not found !!!" << endl; // check if table exists in data
		return false;
	}
	if(v[v.size()-2]!="from"){
		cout << "Syntax Error !!!" << endl; // from must be the second last word the last being table name
		return false;
	}
	vector<string> attr_list; // store attribute list
	for(int i=1;i<v.size();i++){
		if(v[i]=="where"){
			break;
		}
		else{
			attr_list.push_back(v[i]);
		}
	}
	if(attr_list.size()==1 && attr_list[0]=="*"){ // if * show complete table
		return true;
	}
	table* temp = load_table(tab_name); // load table into memory
	vector<string> attr = (temp->tot_index);
	delete temp;

	sort(attr_list.begin(),attr_list.end()); // sort both required list and the complete list
	sort(attr.begin(),attr.end());

	vector<string> common;

	set_intersection(attr_list.begin(),attr_list.end(),attr.begin(),attr.end(),back_inserter(common)); // find intersection

	sort(common.begin(),common.end()); // sort it

	if(attr_list==common){ // intersection must be equal to attribute list
		return true;
	}
	else{
		cout << "Attribute not found !!!" << endl;
		return false;
	}


}

bool condition_checks(struct table* temp, map<char, string> m){ // check for valid conditions in where clause
	vector<string> v=(temp->tot_index);

	for(map<char, string>::iterator it = m.begin();it!=m.end();++it){

		vector<string> breakup = string_to_vector(it->second);
		if(breakup.size()!=3){ // each condition must have 3 components
			return false;
		}
		if(breakup[1]!="=" && breakup[1]!="!=" && breakup[1]!="<" && breakup[1]!=">" && breakup[1]!="<=" && breakup[1]!=">="){
			return false; // check for all valid comparators
		}
		bool find1,find2; // check if both lhs and rha are attributes
		if(find(v.begin(),v.end(),breakup[0])!=v.end()){
			find1 = true;
		}
		else{
			find1 = false;
		}
		if(find(v.begin(),v.end(),breakup[2])!=v.end()){
			find2 = true;
		}
		else{
			find2 = false;
		}

		if(find1 && find2){ // if both are attributes then their data types must be same
			if((temp->mint).count(breakup[0])!=(temp->mint).count(breakup[2])){
				cout << "Mismatch in where clause !!!" << endl;
				return false;
			}
		}
		else if(find1 && (temp->mint).count(breakup[0])==1){// if one is attribute the other must be compatible
			if(!poss_string_to_int(breakup[2])){
				return false;
			}
		}
		else if(find2 && (temp->mint).count(breakup[2])==1){ // if one is attribute the other must be compatible
			if(!poss_string_to_int(breakup[0])){
				return false;
			}
		}
	}
	return true;

}
































