/*
 * table_operations.cpp
 *
 *  Created on: 10-Oct-2016
 *      Author: vivek10p14
 */

#include "header.h"

using namespace std;

void show_tables(){

	if(curr_database.length()==0){
		cout << "Select a database !!!" << endl; // check if databases are selected
		return;
	}
	else{
			ifstream file;
			string path = init_path;
			path = path + curr_database;
			path = path + "/tables.txt";
			char* final_path = string_to_array(path);
			file.open(final_path); // open tables.txt for the selected database
			if(file.peek()==ifstream::traits_type::eof()){
				cout << "Nothing to Display" << endl;
				return;
			}
			vector<string> names;
			if(file.is_open()){
				char output[100];
				while(!file.eof()){
					if(file.peek()==ifstream::traits_type::eof()){
						return;
					}
					file >> output;
					names.push_back(array_to_string(output)); // push all in vector
				}
				file.close();
				names.pop_back();
				for(int i=0;i<names.size();i++){
					cout << names[i] << endl;
				}
				return;
			}
			else{
				cout << "Unexpected Error !!!" << endl;
				return;
			}
	}

}

void create_table(string s){
	if(!check_db){
		cout << "Select a database !!!" << endl; // check if database is selected
		return;
	}

	vector<string> v = string_to_vector(s); // convert string to vector

	string tables_path = init_path + curr_database + '/' + "tables.txt";  // path to tables file
	char* tables_path_char= string_to_array(tables_path);

	if(!proper_create_syntax(v,tables_path_char)){ // check syntax of select statement
		cout << "Check Syntax" << endl;
		return;
	}

	string path = init_path + curr_database + '/' + v[2] + ".txt"; // create file for storing data
	char* path_char = string_to_array(path);

	fstream new_file;
	fstream name_file;
	fstream desc_file;

	name_file.open(tables_path_char,ios::app);
	name_file << v[2] << endl;
	name_file.close();

	string desc = "desc_" + v[2];

	string desc_path = init_path + curr_database + '/' + desc + ".txt"; // create file for storing table description
	char* desc_char = string_to_array(desc_path);

	new_file.open(path_char,ios::app);
	new_file.close();

	desc_file.open(desc_char,ios::app);

	for(int i=4;i<=v.size()-1;i=i+2){
		desc_file << v[i-1] << "\t" << v[i] << endl; // store file description attribute name an datatype
	}

	desc_file.close();

}

void desc_table(string s){
	if(!check_db){
		return; // check if database is selected
	}

	vector<string> v = string_to_vector(s);

	string tables_path = init_path + curr_database + '/' + "tables.txt"; // path to tables.txt
	char* tables_path_char = string_to_array(tables_path);

	if(!desc_table_syntax(v, tables_path_char)){ // check for proper describe syntax
		cout << "Check for syntax" << endl;
	}

	ifstream file;

	string file_path = init_path + curr_database + '/' + "desc_" + v[1] + ".txt"; //path to description file
	char* file_path_char = string_to_array(file_path);

	file.open(file_path_char); // open description file

	char output[1000];
	int k = 0;
	if(file.is_open()){
		while(!file.eof()){
			file >> output; // print the components of the file
			k++;
			if(file.peek()==ifstream::traits_type::eof()){
				file.close();
				return;
			}
			cout << output;
			cout << '\t';
			if(k==2){
				cout << endl;
				k = 0;
			}
		}
		cout << "************" << endl;
	}
	else{
		cout << "Unexpected Error !!!" << endl;
		return;
	}
	return;
}

void insert(string s){
	if(!check_db){
		cout << "Select a Database !!" << endl; // check if database is selected
		return;
	}

	vector<string> v = string_to_vector(s);

	if(!insert_syntax(v)){
		cout << "Check Syntax" << endl; // check for proper insert syntax
		return;
	}

	string path = init_path + curr_database + '/' + v[2] + ".txt"; // path to file where data is stored
	char* path_char = string_to_array(path);

	fstream file;
	file.open(path_char,ios::app);
	if(!file.is_open()){
		cout << "Unexpected Error !!!" << endl;
		return;
	}
	for(int i=3;i<v.size();i++){ // write data to file
		file << v[i];
		if(i!=v.size()-1){
			file << '\t';
		}
	}
	file << endl;

	file.close();

	cout << "Insertion Complete !!!" << endl;

	return;

}

struct table* remove_redundancy(struct table* temp){
	if(temp==NULL){
		cout << "Empty Table !!!" << endl; // check if table is NULL
		return NULL;
	}
	table* tab = new table(); // create a new table with similar structure
	tab->mint = temp->mint;
	tab->mstring = temp->mstring;
	tab->attr_index = temp->attr_index;
	tab->tot_index = temp->tot_index;


	vector<string> aux_string;
	vector<int> aux_int;

	for(int i=0;i<(temp->mint).size();i++){
		(tab->vint).push_back(aux_int);
	}
	for(int i=0;i<(temp->mstring).size();i++){
		(tab->vstring).push_back(aux_string);
	}

	int tuples = 0; // find number of tuples
	if((temp->mint).size()!=0){
		tuples = (temp->vint)[0].size();
	}
	else if((temp->mstring).size()!=0){
		tuples = (temp->vstring)[0].size();
	}
	else{
		cout << "Empty Table" << endl;
		return NULL;
	}

	vector<string> v;
	map< vector<string> ,int> aux; // map to store each tuple seen upto i'th iteration

	for(int i=0;i<tuples;i++){
		for(int j=0;j<(temp->mint).size();j++){ // go to each attribute in each tuple and store it's value in a vector

			v.push_back(int_to_string((temp->vint)[j][i]));
		}
		for(int j=0;j<(temp->mstring).size();j++){

			v.push_back((temp->vstring)[j][i]);
		}
		if(aux[v]==0){ // if such a vector has not been seen before then insert it in the new table
			aux[v] = 1;
			int k = (temp->mint).size();
			for(int j=0;j<k;j++){
				(tab->vint)[j].push_back(string_to_int(v[j]));
			}
			for(int j=k;j<k+(temp->mstring).size();j++){
				(tab->vstring)[j-k].push_back(v[j]);
			}
		}
		v.clear();

	}

	return tab;

}

void print_table(struct table* temp){
	if(temp==NULL){
		cout << "Nothing to print !!!!" << endl; // if input is null print nothing
		return;
	}
	string s = "******"; // pattern to be printed when a  table is printed
	string print = "";
	int l = (temp->tot_index).size();
	for(int i=0;i<2*l;i++){
		print = print + s;
	}
	cout << print << endl;
	for(int i=0;i<l;i++){
		cout << (temp->tot_index)[i]; // print all attribute names
		if(i!=l-1){
			cout << '\t';
		}
	}
	cout << endl;
	cout << print << endl;



	int len_records = 0; // find number of tuples
	if((temp->mint).size()!=0){
		len_records = (temp->vint)[0].size();
	}
	else if((temp->mstring).size()!=0){
		len_records = (temp->vstring)[0].size();
	}
	else{
		cout << "Empty Table" << endl;
		return;
	}

	vector<string> col = (temp->tot_index);


	for(int i=0;i<len_records;i++){

		for(int j=0;j<col.size();j++){

			if((temp->mint).count(col[j])==0){

				cout << (temp->vstring)[(temp->mstring)[col[j]]-1][i]; // print each tuple in order of the attributes in tot_index
				if(j!=col.size()-1){
					cout << '\t';
				}
			}
			else{

				cout << (temp->vint)[(temp->mint)[col[j]]-1][i];
				if(j!=col.size()-1){
					cout << '\t';
				}

			}

		}
		cout << endl;
	}
	cout << endl;


	return;
}






