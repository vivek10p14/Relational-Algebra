# Relational-Algebra

The program has been in written in C++.

Author - Vivek Sourabh,CSE(Part-III), Roll No. 14075059

The program gives the implementation of the 6 basic Relational Algebra Functions-
	1). Select
	2). Project
	3). Rename
	4). Union
	5). Set Difference
	6). Cartesian Product

The above mentioned queries can also be nested together to create more complex funcionalities such as Join etc.

The complete folder needs to be copied into the home directory.
Then the following commands need to be run inside the folder :
	1). chmod a+x DBMS
	2). ./DBMS

Before starting the program one needs to set the variable "init_path" in the file initialize.cpp as the path where the complete DBMS named folder will be stored. This path will be taken as input from the user each time the program starts.

Once the path is set the user can type in the following commands -

1). show databases : This displays all the databases present

2). use db_name : Here db_name is the name of the database we want to use

3). show tables : Displays the name of all tables in the given database

4). desc tab_name : Shows structure of the table tab_name

5). create table tab_name ...... : This commands creates a table in the selected database by the name tab_name
				   Complete Syntax : create table table3 id int,name string
				   This craetes 2 files one for storing the data and one for storing the structure of the table
			   	   Only two datatypes are allowed namely int and string

6). insert into tab_name ...... : This commands inserts the given tuple in the table named tab_name
				  Complete Syntax : insert into table3 1,vivek

Description for basic relational functions are as follows :

1). Project : project id,name from table3
	      project * from table4

2). Union : project id,name from table3 union project id,name from table4

3). Set Difference : project id,name from table3 difference project id,name from table4

4). Product : project id,name from table3 product project dept from table4

5). Rename : rename id1,name1 table3

6). Select : select * where #([roll = 59] | [roll = 60]) & ([dept = CSE] | [dept = MECH])% from table4
	    In select the where clause must start with '#' and must end with '%'
	    Each individual condition must be enclosed within '[....]'
	    While '(...)' should be used properly for the nesting of conditions
	    The where clause expression is first converted to postfix and then evaluated
	    The comparators used in individual expressions are - =, !=, >, <, >=, <= .
	    Only and(&) and or(|) operators are allowed
	    Precedence amongst them is : and > or


Besides using these 6 basic types of queries user can also write nested queries to perform complex operations :

	A). Rules for writing nested queries :
		a). Each operator must be enclosed within '{.....}'
		b). Each operand must be enclosed within '<....>'
		c). Use '(.....)' properly to nest operations

	B). Evaluation of nested queries : 
		a). Each opeartor and operand is mapped to a specific character.
		b). Thus an infix expression is obtained.
		c). This is then converted to postfix and evaluated.

	C). Examples :
		a). Join using nesting - 

			{select name,roll,dept1 where #[roll = roll1]% from}(<table3>({product}({rename name1,roll1,dept1}<table4>))

							************************************
								name	roll	dept1
							************************************
								virat	58	CSE
								vivek	59	MECH
								vedant	57	META
								vedant	60	CSE

		b). {project * from}(<table3>{product}({rename name1,roll1}<table3>))

					************************************************
						name	roll	name1	roll1
					************************************************
						virat	58	virat	58
						virat	58	vivek	59
						virat	58	vedant	57
						virat	58	vedant	60
						vivek	59	virat	58
						vivek	59	vivek	59
						vivek	59	vedant	57
						vivek	59	vedant	60
						vedant	57	virat	58
						vedant	57	vivek	59
						vedant	57	vedant	57
						vedant	57	vedant	60
						vedant	60	virat	58
						vedant	60	vivek	59
						vedant	60	vedant	57
						vedant	60	vedant	60

Finally to quit the program the user need to type in "exit".



























