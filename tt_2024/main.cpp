#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<mysql.h>
#include"User.h"
#include"Tasktracker.h"
#include"Task.h"
using namespace std;
int qstate;

#define max(a, b) (((a) > (b) ? (a) : (b))



int main() {

	// connecting to mysql server
	MYSQL* conn;
	MYSQL_ROW row;
	MYSQL_RES *res;
	conn = mysql_init(0);
	conn = mysql_real_connect(conn, "localhost", "root", "toby", "tt_db", 3306, NULL, 0);
	//-----------------------
	
	if (conn) {
		puts("Succesful connection to database!");


		// app section
		string username, password;
		int user_option;
		int opt = 0;
		string query;
		const char *q;

		do {
			cout << "\nPress 0 to register or 1 to login";
			cout << "\noption ="; cin >> user_option;
			cout << "\nusername: "; cin >> username;
			cout << "\npassword: "; cin >> password;
			User this_user = User(username, password);

			switch (user_option) {
				case 0:
					query = this_user.post();
					cout << query;
					q = query.c_str();
					qstate = mysql_query(conn, q);
					if (!qstate) {
						cout << "register successfully";
					}
					else {
						cout << "register failed: " << mysql_error(conn) << endl;
					}
				case 1:
					query = this_user.get();
					cout << query;
					q = query.c_str();
					qstate = mysql_query(conn, q);
					if (!qstate) {
						res = mysql_store_result(conn);
						if(row = mysql_fetch_row(res)) {
							this_user = User(stoi(row[0]), (string)row[1], (string)row[2]);  //stoi - string of int 
							cout << "login successfully";
						}
					}
					else {
						cout << "login failed: " << mysql_error(conn) << endl;
					}
					if (user_option == 0) {
						Tasktracker this_tt = Tasktracker(this_user.getid(), "Your task tracker");
						query = this_tt.post();
						cout << query;
						q = query.c_str();
						qstate = mysql_query(conn, q);
						if (!qstate) {
							cout << "tasktracker created successfully";
						}
						else {
							cout << "tasktracker created failed: " << mysql_error(conn) << endl;
						}
					}
					break;
				default:
					break;
			}
		} while (user_option != 0 && user_option != 1);

		do {

			cout << "\nMenu: ";
			cout << "\n1. Add task : ";
			cout << "\n2. Display task list: ";
			cout << "\n3. Search for a task based on name  : ";
			cout << "\n4. Delete task based on name : ";
			cout << "\n5. Display tasks based on priority : ";
			cout << "\n6. Update the stage of a task based on name : ";
			cout << "\n0. Exit.";
			cout << "------------------------------";
			cout << "\nOption: ";	
			cin >> opt;
			switch (opt) {
			case 0: 
				break;
			
			case 1:

				break;
			
			case 2:
				break;
			
			case 3:
				break;
			
			case 4:
				break;
			
			case 5:
				break;

			case 6:
				/*query = "SELECT * FROM test";
				q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate) {
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res)) {
						printf("ID: %s, Name: %s, Value: %s\n", row[0], row[1], row[2]);
					}
				}
				else {
					opt = 0;
					cout << "query failed: " << mysql_error(conn) << endl;
				}*/
				break;

			default:
				break;
			}
		} while (opt);
	}
	else {
		puts("Connection to database has failed!");
	}


	

	return 0;
}