#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include <filesystem>
#include <direct.h>
#include<algorithm>
using namespace std;


string encrypt(string password);
bool File_Exists(string file);

class Category
{
	string title;
	string file;
public:
	Category();
	Category(string title, string file);
	void set_title(string title);
	void set_file(string file);
	string get_title() const;
	string get_file() const;
	void write_cat_to_file(string test_category);
	//void read_category(fstream& fs)
};

class Questions
{
	string question;
	vector<string> var_answers;
	char correct_answer;
public:
	Questions();
	Questions(string q, vector<string> var_answers, char c_a);
	void setData(string q, vector<string> var_answers, char c_a);
	string get_question() const;
	vector<string> get_var_answers() const;
	char get_correct_answer() const;
	void question_to_file(fstream& fs);
	void question_from_file(fstream& fs);
	void question_print() const;
};

class Test
{
	string test_name;
	vector<Questions> test;
	string file;
public:
	Test();
	Test(string test_name, vector<Questions> q, string file);
	void set_test_name(string test_name);
	void set_file(string file);
	vector<Questions> get_test() const;
	string get_test_name() const;
	void test_from_file(fstream& fs);
	void write_test_name_to_cat_file(string test_category, string test_name);
};

class Guest
{
	string login;
	string password;
public:
	Guest();
	Guest(string login, string password);
	void set_login(string login);
	void set_password(string password);
	string get_login() const;
	string get_password() const;
	void guest_to_file(fstream& fs);
	void guest_from_file(fstream& fs);
};

class Admin : public Guest
{
public:
	Admin();
	Admin(string login, string password);
	bool Check_Admin_Password(string password);
	bool Check_Admin_Login(string login);
};

class Student : public Guest
{
	string name;
	string surname;
	string street;
	string phone_number;
	int st_mark;
	int percent_correct_answers;
	vector<char> passed_answers;
	string file;

public:
	Student();
	Student(string login, string password, string name, string surname, string street, string phone_number,
		int st_mark, int percent_correct_answers, vector<char> passed_answers, string file);
	void set_user(string name, string surname, string street, string phone_number);
	void set_student_phone(string phone_number);
	void set_street(string street);
	void set_passed_answers(char a);
	void set_mark(int q_c, int a_c);
	void set_percent(int q_c, int a_c);
	void set_file(string file);
	void record_passed_to_file(string file, string test_name);
	int get_percent() const;
	int get_mark() const;
	string get_file() const;
	//vector<char> get_passed_answers()
	string get_surname() const;
	string get_name() const;
	string get_street() const;
	string get_phone_number() const;
	void student_to_file(fstream& fs);
	void student_from_file(fstream& fs);
	bool operator == (string surname);
};

class St_Data
{
	vector<Student> st;
public:
	void load_from_file(fstream& fs);
	bool Check_Student_Password(string password);
	bool Check_Student_Login(string login);
	void load_students_to_file(fstream& fs);
	void delete_student(string surname);
	void change_phone(string name, string surname, string phone_number);
	void change_address(string name, string surname, string street);
	void print() const;
	void add_student(Student& user);
};

ostream& operator << (ostream& os, Student& user);
ostream& operator << (ostream& os, Questions& q);
string print_student_report(fstream& fs);



