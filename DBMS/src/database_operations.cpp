/*
 * database_operations.cpp
 *
 *  Created on: 10-Oct-2016
 *      Author: vivek10p14
 */

#include "header.h"

using namespace std;

string curr_database; // extern variable

void show_databases(){

	ifstream file;
	file.open("databases.txt"); // open file to store database name
	if(file.peek()==ifstream::traits_type::eof()){ // check if file is empty
		cout << "Nothing to Display" << endl;
		return;
	}
	vector<string> names;
	if(file.is_open()){ //if file is open read from file
		char output[100];
		while(!file.eof()){
			if(file.peek()==ifstream::traits_type::eof()){ // check for end of file
				file.close();
				return;
			}
			file >> output;
			names.push_back(array_to_string(output));
		}
		file.close();
		names.pop_back();
		for(int i=0;i<names.size();i++){
			cout << names[i] << endl;
		}
		return;
	}
	else{
		cout << "Unexpected Error !!!" << endl; // error if cannot open file
		return;
	}


}

void create_database(string s){ // creation of database

	char* s_arr = string_to_array(s); //conevrt string to array as mkdir takes character array as input
	int check = mkdir(s_arr, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); // make directory with all permissions

	if(check!=0){ // mkdir returns 0 if the operation is successful
		cout << "Could not create database." << endl;
		return;
	}
	else{
		fstream file; // if database is created create a file called tables.txt to store values of all tables contained in it
		string ss = init_path + "databases.txt";
		char* ss_char = string_to_array(ss);
		file.open(ss_char, ios::app); // open file
		file << s << endl; // write in file
		file.close();
		string path = init_path;
		path = path + s;
		path = path + "/tables.txt";
		char* final_path = string_to_array(path);
		//cout << final_path << endl;
		file.open(final_path,ios::app);
		file.close();
		cout << "Database created successfully !!!" << endl;
	}

}

void use_db(string s){

	int flag = 1;
	ifstream file;
		file.open("databases.txt"); // open databases.txt which contains names of all databases
		if(file.peek()==ifstream::traits_type::eof()){ // check if file is empty
			cout << "No database found !!!" << endl;
			return;
		}
		if(file.is_open()){ // check if database exists
			char output[100];
			while(!file.eof()){
				file >> output;
				if(output==s){
					flag = 0;
					break;
				}
			}
			file.close();
		}
		else{
			cout << "Unexpected Error !!!" << endl;
		}

		if(flag==1){
			cout << "No database by given exists !!!" << endl;
		}
		else{
			curr_database = s; // if database exists change value of extern variable to it
			cout << "Database Changed" << endl;
		}

	return;


}



