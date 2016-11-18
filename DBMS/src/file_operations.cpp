/*
 * file_operations.cpp
 *
 *  Created on: 13-Oct-2016
 *      Author: vivek10p14
 */

#include "header.h"

using namespace std;

bool table_in_database(string s){ // check if table exists in current working database
	ifstream file;
	string path = init_path + curr_database + '/' + "tables.txt"; // get path to the tables file
	char* path_char = string_to_array(path);

	file.open(path_char);

	if(file.peek()==ifstream::traits_type::eof()){ // if file is empty return false
		cout << "Table Not Found !!!" << endl;
		file.close();
		return false;
	}

	if(!file.is_open()){
		cout << "Unexpected Error !!!" << endl;
		return false;
	}
	char output[1000];
	int check = 0;
	while(!file.eof()){ // else check if table name is present in file
		file >> output;
		if(output==s){
			check = 1;
			file.close();
			break;
		}
	}

	file.close();

	if(check==0){
		cout << "Table not Found !!!!" << endl;
		return false;
	}


	return true;
}


struct table* load_table(string name){ //load table form file to memory so that operations can be performed on them
	table* tab = new table(); // table where the data will be stored

	ifstream file,file1;
	string path = init_path + curr_database + '/' + name + ".txt"; //path to table where data is stored
	string desc_path = init_path + curr_database + '/' + "desc_" + name + ".txt"; // path to file where description of table is stored
	char* path_char = string_to_array(path);
	char* desc_path_char = string_to_array(desc_path);

	file1.open(desc_path_char);

	vector<string> attr_types;

	if(file1.peek()==ifstream::traits_type::eof()){
		cout << "Table Definition Error !!!" << endl;
		file1.close();
		return NULL;
	}
	if(!file1.is_open()){
		cout <<"Unexpected Error !!!" << endl;
		return NULL;
	}
	char output[1000];
	while(!file1.eof()){
		file1 >> output;
		attr_types.push_back(array_to_string(output));
		if(file1.peek()==ifstream::traits_type::eof()){
			break;
		}
	}
	file1.close();
	attr_types.pop_back(); // get all attribute name and type pairs in a vector

	int tuple_len = attr_types.size()/2; // number of attributes is size of above list divided by 2

	int int_index = 1;
	int string_index = 1;
	int index = 1;
	vector<int> aux_int;
	vector<string> aux_string;
	for(int i=0;i<attr_types.size();i++){
		if(i%2==0){ // each even index contains attribute names

			(tab->attr_index)[attr_types[i]] = index;
			(tab->tot_index).push_back(attr_types[i]);
			index++;
		}
		else{ // each odd index contains attribute types
			if(attr_types[i]=="int"){
				(tab->mint)[attr_types[i-1]] = int_index;
				int_index++;
				(tab->vint).push_back(aux_int);
			} // the table structure is built accordingly
			else{
				(tab->mstring)[attr_types[i-1]] = string_index;
				string_index++;
				(tab->vstring).push_back(aux_string);
			}
		}
	}

	file.open(path_char); // open file where the data is stored
	if(file.peek()==ifstream::traits_type::eof()){
		file.close();
		return NULL;
	}
	if(!file.is_open()){
		cout << "Unexpected Error !!!" << endl;
		return NULL;
	}
	vector<string> table_tuples;
	while(!file.eof()){
		if(file.peek()==ifstream::traits_type::eof()){
			break;
		}
		file >> output;
		table_tuples.push_back(array_to_string(output)); // read the data and push it into a vector

	}
	file.close();



	int aindex = 0;
	string index_name;
	table_tuples.pop_back();
	int total = table_tuples.size(); // find number of tuples in data

	for(int i=0;i<total;i++){
		aindex = i%(index-1); // get index of each value in a tuple

		index_name = (tab->tot_index)[aindex];
		if((tab->mint).count(index_name)!=0){ // check type of the attribute
			(tab->vint)[(tab->mint)[index_name]-1].push_back(string_to_int(table_tuples[i]));
		} // put the value in appropriate place
		else{
			(tab->vstring)[(tab->mstring)[index_name]-1].push_back(table_tuples[i]);
		}
	}

	return tab; // return the table built

}















