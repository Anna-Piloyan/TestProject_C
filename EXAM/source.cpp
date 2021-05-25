#include"header.h"


string encrypt(string password)
{
	char key = 'P';
	string output = password;

	for (int i = 0; i < password.size(); i++)
	{

		output[i] = password[i] ^ key;
	}
	return output;
}

bool File_Exists(string file)
{
	ifstream ifs(file);
	if (ifs.is_open())
	{
		return true;
	}
	else
	{
		return false;
	}
}

Category::Category() {}
Category::Category(string title, string file) : title(title), file(file) {}

void Category::set_title(string title)
{
	this->title = title;
}

void Category::set_file(string file)
{
	this->file = file;
}

string Category::get_title() const
{
	return this->title;
}

string Category::get_file() const
{
	return this->file;
}

void Category::write_cat_to_file(string test_category)
{
	fstream fs;
	fs.open("folder.txt", fstream::app | fstream::binary);
	if (!fs.is_open())
	{
		cout << " File was not opened!\n";
	}
	else
	{
		fs << test_category;
	}
	fs.close();
}

/*void Category::read_category(fstream& fs)
{
	while (!fs.eof())
	{
		fs >> title;
	}
}*/

Questions::Questions() {}
Questions::Questions(string q, vector<string> var_answers, char c_a)
	: question(q), var_answers(var_answers), correct_answer(c_a) {}

void Questions::setData(string q, vector<string> var_answers, char c_a)
{
	this->question = q;
	this->var_answers = var_answers;
	this->correct_answer = c_a;
}

string Questions::get_question() const
{
	return question;
}

vector<string> Questions::get_var_answers() const
{
	return var_answers;
}

char Questions::get_correct_answer() const
{
	return correct_answer;
}

void Questions::question_to_file(fstream& fs)
{
	fs << question << endl;
	for (int i = 0; i < 3; i++)
	{
		fs << var_answers[i] << "\n";
	}
	fs << correct_answer << endl;
}

void Questions::question_from_file(fstream& fs)
{
	var_answers.clear();
	string answer;
	getline(fs, question);
	for (int i = 0; i < 3; i++)
	{
		getline(fs, answer);
		var_answers.push_back(answer);
	}
	fs.get(correct_answer);
	fs.ignore();
}

void Questions::question_print() const
{
	cout << question << endl;
	for (auto item : var_answers)
	{
		cout << item << endl;
	}
	cout << correct_answer << endl;
}

Test::Test() {}
Test::Test(string test_name, vector<Questions> q, string file) : test_name(test_name), test(test), file(file) {}

void Test::set_test_name(string test_name)
{
	this->test_name = test_name;
}

void Test::set_file(string file)
{
	this->file = file;
}

vector<Questions> Test::get_test() const
{
	return this->test;
}

string Test::get_test_name() const
{
	return test_name;
}

void Test::test_from_file(fstream& fs)
{
	//getline(fs, test_name, '\n');
	while (!fs.eof())
	{
		Questions q;
		q.question_from_file(fs);
		if (fs.eof()) break;
		test.push_back(q);
	}
}

void Test::write_test_name_to_cat_file(string test_category, string test_name)
{
	stringstream ss;
	fstream fs;
	fs.open(test_category + ".txt", fstream::app);
	if (!fs.is_open())
	{
		cout << " File was not opened!\n";
	}
	else
	{
		fs << "\n" << test_name << "\n";
	}
	fs.close();
}

ostream& operator << (ostream& os, Questions& q)
{
	os << q.get_question() << endl;
	for (auto item : q.get_var_answers())
	{
		os << item << endl;
	}
	os << q.get_correct_answer() << endl;
	return os;
}

Guest::Guest() {}
Guest::Guest(string login, string password) : login(login), password(password) {}

void Guest::set_login(string login)
{
	this->login = login;
}

void Guest::set_password(string password)
{
	this->password = password;
}

string Guest::get_login() const
{
	return this->login;
}

string Guest::get_password() const
{
	return this->password;
}

void Guest::guest_to_file(fstream& fs)
{
	fs << login << " ";
	fs << encrypt(password) << "\n";
}

void Guest::guest_from_file(fstream& fs)
{
	fs >> login;
	string tmp = "";
	fs >> tmp;
	set_password(encrypt(tmp));
}

Admin::Admin() {}
Admin::Admin(string login, string password) : Guest(login, password) {}

bool Admin::Check_Admin_Password(string password)
{
	fstream fs;
	fs.open("admin.txt", fstream::in | fstream::out);
	if (fs.is_open())
	{
		guest_from_file(fs);
	}
	if (get_password() == password) {
		return true;
	}
	else
		return false;
}

bool Admin::Check_Admin_Login(string login)
{
	fstream fs;
	fs.open("admin.txt", fstream::in | fstream::out);
	if (fs.is_open())
	{
		guest_from_file(fs);
	}
	if (get_login() == login) {
		return true;
	}
	else
		return false;
}

Student::Student() : st_mark(0), percent_correct_answers(0) {}
Student::Student(string login, string password, string name, string surname, string street, string phone_number, int st_mark, int percent_correct_answers, vector<char> passed_answers, string file)
		: Guest(login, password)
{
	this->surname = surname;
	this->name = name;
	this->street = street;
	this->phone_number = phone_number;
	this->st_mark = st_mark;
	this->passed_answers = passed_answers;
	this->file = file;
	this->percent_correct_answers = percent_correct_answers;
}

void Student::set_user(string name, string surname, string street, string phone_number)
{
	this->surname = surname;
	this->name = name;
	this->street = street;
	this->phone_number = phone_number;
}

void Student::set_student_phone(string phone_number)
{
	this->phone_number = phone_number;
}

void Student::set_street(string street)
{
	this->street = street;
}

void Student::set_passed_answers(char a)
{
	passed_answers.push_back(a);
}

void Student::set_mark(int q_c, int a_c)
{
	this->st_mark = 12 * a_c / q_c;
}

void Student::set_percent(int q_c, int a_c)
{
	this->percent_correct_answers = a_c * 100 / q_c;
}

void Student::set_file(string file)
{
	this->file = file + ".txt";
}

void Student::record_passed_to_file(string file, string test_name)
{
	ofstream fs;
	fs.open("StudentsReport\\" + file + ".txt", ofstream::out | ofstream::app);
	if (fs.is_open())
	{
		fs << "\nTEST: " << test_name << "\n";
		for (int i = 0; i < passed_answers.size(); i++)
		{
			fs << passed_answers[i] << " ";
		}
		fs << "\nPercent of correct answers for test: " << percent_correct_answers;
		fs << "\nMark for test: " << st_mark << "\n";
	}
	else
	{
		cout << " File was not opened!\n";
	}
	fs.close();
}

int Student::get_percent() const
{
	return this->percent_correct_answers;
}

int Student::get_mark() const
{
	return this->st_mark;
}

string Student::get_file() const
{
	return this->file;
}

/*vector<char> Student::get_passed_answers()
{
	return passed_answers;
}*/

string Student::get_surname() const
{
	return this->surname;
}

string Student::get_name() const
{
	return this->name;
}

string Student::get_street() const
{
	return this->street;
}

string Student::get_phone_number() const
{
	return this->phone_number;
}

void Student::student_to_file(fstream& fs)
{
	fs << name << " ";
	fs << surname << " ";
	fs << street << " ";
	fs << phone_number << " ";
	guest_to_file(fs);
}

void Student::student_from_file(fstream& fs)
{
	fs >> name;
	fs >> surname;
	fs >> street;
	fs >> phone_number;
	guest_from_file(fs);
}

bool Student::operator == (string surname)
{
	return this->surname == surname;
}

void St_Data::load_from_file(fstream& fs)
{
	while (true)
	{
		Student tmp;
		tmp.student_from_file(fs);
		if (fs.eof()) break;
		st.push_back(tmp);
	}
}

bool St_Data::Check_Student_Password(string password)
{
	for (int i = 0; i < encrypt(password).size(); i++)
	{
		if (st[i].get_password() == password) {
			return true;
		}
	}
	return false;
}

bool St_Data::Check_Student_Login(string login)
{
	fstream fs;
	fs.open("students.txt", fstream::in | fstream::out);
	if (fs.is_open())
	{
		load_from_file(fs);
	}
	fs.close();
	for (int i = 0; i < st.size(); i++)
	{
		if (st[i].get_login() == login) {
			return true;
		}
	}
	return false;
}

void St_Data::load_students_to_file(fstream& fs)
{
	for (int i = 0; i < st.size(); i++)
	{
		st[i].student_to_file(fs);
	}
}

void St_Data::delete_student(string surname)
{
	auto it = remove(st.begin(), st.end(), surname);
	st.erase(it, st.end());
}

void St_Data::change_phone(string name, string surname, string phone_number)
{
	auto it = find_if(st.begin(), st.end(), [name, surname](const Student& student)
		{
			return student.get_name() == name && student.get_surname() == surname;
		});
	if (it == st.end())
	{
		cout << " Not found!\n";
	}
	else
	{
		it->set_student_phone(phone_number);
	}
}

void St_Data::change_address(string name, string surname, string street)
{
	auto it = find_if(st.begin(), st.end(), [name, surname](const Student& student)
		{
			return student.get_name() == name && student.get_surname() == surname;
		});
	if (it == st.end())
	{
		cout << " Not found!\n";
	}
	else
	{
		it->set_street(street);
	}
}

//void St_Data::print() const
//{
//	Printer<Student>::print(st);
//}

void St_Data::add_student(Student& user)
{
	st.push_back(user);
}

ostream& operator << (ostream& os, Student& user)
{
	os << " " << user.get_name() << " " << user.get_surname() << " | " << user.get_street() << " | " << user.get_phone_number() << endl;
	os << " Login: " << user.get_login() << " Password: " << user.get_password();
	return os;
}

string print_student_report(fstream& fs)
{
	string str;
	if (fs.is_open())
	{
		getline(fs, str, '\0');
	}
	else
	{
		cout << " File was not opened!\n";
	}
	fs.close();
	return str;
}