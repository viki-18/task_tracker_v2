#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <mysql.h>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include "User.h"
#include "Tasktracker.h"
#include "Task.h"
using namespace std;
int qstate;

#define max(a, b) (((a) > (b) ? (a) : (b))

Task add_task(int tt_id) {
	string na;
	string de;
	string st;
	string est;
	time_t dead = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	cout << "Task name: ";
	cin.ignore(); // Ignore newline character from previous input
	getline(cin, na);

	cout << "Task details: ";
	getline(cin, de);

	cout << "Task stage: ";
	getline(cin, st);

	cout << "Enter a deadline (YYYY-MM-DD HH:MM:SS): ";

	tm timeInfo = {};
	string userInput;
	getline(cin, userInput);
	istringstream ss(userInput);

	ss >> std::get_time(&timeInfo, "%Y-%m-%d %H:%M:%S");

	if (ss.fail()) {
		cerr << "Invalid datetime format. Please use YYYY-MM-DD HH:MM:SS." << endl;
	}
	else {
		dead = std::chrono::system_clock::to_time_t(std::chrono::system_clock::from_time_t(std::mktime(&timeInfo)));
		cout << "Entered datetime: " << std::put_time(&timeInfo, "%Y-%m-%d %H:%M:%S") << endl;
	}

	cout << "Task estimate time(hours): ";
	cin >> est;

	return Task(tt_id, na, de, st, dead, est);
}

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
		User this_user = User();
		Tasktracker this_tt = Tasktracker();


		do {
			cout << "\nPress 0 to register or 1 to login";
			cout << "\noption ="; cin >> user_option;
			cout << "\nusername: "; cin >> username;
			cout << "\npassword: "; cin >> password;
			this_user = User(username, password);

			switch (user_option) {
				case 0:
					query = this_user.post();
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
					q = query.c_str();
					qstate = mysql_query(conn, q);
					if (!qstate) {
						res = mysql_store_result(conn);
						if(row = mysql_fetch_row(res)) {
							this_user = User(stoi(row[0]), (string)row[1], (string)row[2]);  //stoi - string of int 
							cout << this_user.getid();
							cout << "login successfully";
						}
					}
					else {
						cout << "login failed: " << mysql_error(conn) << endl;
					}

					if (user_option == 0) {
						this_tt = Tasktracker(this_user.getid(), "Your task tracker");
						query = this_tt.post();
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

		query = this_tt.get(this_user.getid());
		cout << query <<endl;
		q = query.c_str();
		qstate = mysql_query(conn, q);
		if (!qstate) {
			res = mysql_store_result(conn);
			if (row = mysql_fetch_row(res)) {
				this_tt = Tasktracker(stoi(row[0]), stoi(row[1]), (string)row[2]);  //stoi - string of int 
				cout << this_tt.tostring() << endl;
				cout << "task tracker get successfully";
			}
		} else {
			cout << "task tracker get failed: " << mysql_error(conn) << endl;
		}

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
			Task this_task = Task();
			int TTid = this_tt.getid();
			string searched_name;
			string new_stage;

			cin >> opt;
			switch (opt) {
			case 0: 
				break;
			
			case 1:
				this_task = add_task(TTid);
				query = this_task.post();
				q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate) {
					cout << "task added successfully";
				}
				else {
					cout << "task added failed: " << mysql_error(conn) << endl;
				}
				break;
			
			case 2:
				query = this_tt.getall(TTid);
				q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate) {
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res)) {
						printf("Name: %s, Stage: %s, Deadline: %s, Estimate time: %s \n\n", row[2], row[3], row[4], row[5]);
					}
				}
				else {
					cout << "task tracker display failed: " << mysql_error(conn) << endl;
				}
				break;
			
			case 3:
				cout << "Task searched name: "; cin >> searched_name;
				query = this_task.get(searched_name);
				q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate) {
					res = mysql_store_result(conn);
					if (row = mysql_fetch_row(res)) {
						printf("Name: %s, Stage: %s, Deadline: %s, Estimate time: %s \n\n", row[2], row[3], row[4], row[5]);
					}
				}
				else {
					cout << "task search failed: " << mysql_error(conn) << endl;
				}
				break;
			
			case 4:
				cout << "Task delete name: "; cin >> searched_name;
				query = this_task.erase(searched_name);
				q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate) {
					cout << "task delete successfully";
				}
				else {
					cout << "task delete failed: " << mysql_error(conn) << endl;
				}
				break;
			
			case 5:
				query = this_tt.getbydd(TTid);
				q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate) {
					res = mysql_store_result(conn);
					while (row = mysql_fetch_row(res)) {
						printf("Name: %s, Stage: %s, Deadline: %s, Estimate time: %s \n\n", row[2], row[3], row[4], row[5]);
					}
				}
				else {
					cout << "task tracker display failed: " << mysql_error(conn) << endl;
				}
				break;

			case 6:
				cout << "Task update stage name: "; cin >> searched_name;
				cout << "\nNew stage: "; cin >> new_stage;
				query = this_task.update_stage(searched_name, new_stage);
				q = query.c_str();
				qstate = mysql_query(conn, q);
				if (!qstate) {
					cout << "task update stage successfully";
				}
				else {
					cout << "task update stage failed: " << mysql_error(conn) << endl;
				}
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