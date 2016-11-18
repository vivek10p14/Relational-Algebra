/*
 * initialize.cpp
 *
 *  Created on: 11-Oct-2016
 *      Author: vivek10p14
 */

#include "header.h"

using namespace std;

tr1::unordered_map<string, int> keywords; // extern variables
tr1::unordered_map<string, int> precedence;
string init_path;

void initialize(){
	keywords["select"] = 1; // strore keywords in map
	keywords["project"] = 1;
	keywords["rename"] = 1;
	keywords["set_diff"] = 1;
	keywords["cart_product"] = 1;
	keywords["union"] = 1;
	keywords["and"] = 1;
	keywords["or"] = 1;
	keywords["from"] = 1;
	keywords["where"] = 1;
	keywords["int"] = 1;
	keywords["string"] = 1;
	precedence["rename"] = 6; //store precedence values in map
	precedence["union"] = 5;
	precedence["difference"] = 4;
	precedence["product"] = 3;
	precedence["select"] = 2;
	precedence["project"] = 1;

	string s;
	cout << "Enter path to DBMS folder -> ";
	cin >> s;


	init_path = s; // set initial path

}




