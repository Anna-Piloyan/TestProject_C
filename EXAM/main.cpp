#include"header.h"
namespace f = filesystem;
template<class T>
class Printer
{
public:
	static void print(vector<T> v)
	{
		cout << string(30, '-') << "\n";
		for (int i = 0; i < v.size(); i++)
		{
			cout << v[i] << endl;
		}
		cout << string(30, '-') << "\n";
	}
};

void St_Data::print() const
{
	Printer<Student>::print(st);
}

int main()
{
	St_Data students;
	Test test;
	Student st;
	Admin admin;
	char symbol;
	int choice;
	fstream fs;
	string st_name, st_surname, st_address, st_phone_number;
	string login, password, test_category, test_name;
	vector<string> folder;
	do
	{
		system("cls");
		cout << " \tHello User!\n\n";
		cout << " Do you want to SIGN iN?\n";
		cout << " YES press 'Y'\n";
		cout << " NO press 'N'\n";
		cout << " EXIT PROGRAMM press 'X'\n";
		cout << string(50, '-');
		cout << "\n Your choice: ";
		cin >> symbol;
		if (symbol == 'Y')
		{
			cout << " You enter as a: \n";
			cout << " Admin - PRESS '1'\n";
			cout << " Guest - PRESS '2'\n";
			cout << " Enter your choice: ";
			cin >> choice;
			switch (choice)
			{
			case 1:
			{
				if (File_Exists("admin.txt") == false)
				{
					cout << " Welcome Admin!\n";
					cout << " Set your login: ";
					cin >> login;
					admin.set_login(login);
					cout << " Set your password: ";
					cin >> password;
					admin.set_password(password);
					ofstream out("admin.txt");
					fs.open("admin.txt", fstream::in | fstream::out);
					if (fs.is_open())
						admin.guest_to_file(fs);
					else
						cout << " File was not opened!\n";
					fs.close();
					cout << " Registration completed successfully!\n";
					system("pause");
				}
				else
					cout << " Administrator already registered try to LOGIN!\n";
				system("pause");
				break;
			}
			case 2:
			{
				cout << " Registration: \n";
				cout << " Enter your name: ";
				cin >> st_name;
				cout << " Enter your surname: ";
				cin >> st_surname;
				cout << " Enter your street: ";
				cin >> st_address;
				cout << " Enter your phone_number (model: +38077555555) ";
				cin >> st_phone_number;
				st.set_user(st_name, st_surname, st_address, st_phone_number);
				do{
					cout << " Set login: ";
					cin >> login;
				} while (students.Check_Student_Login(login) == true);
				st.set_login(login);
				cout << " Set password: ";
				cin >> password;
				st.set_password(password);
				if (File_Exists("students.txt") == false)
				{
					ofstream out("students.txt");
				}
				fs.open("students.txt", fstream::in | fstream::out | fstream::app);
				if (fs.is_open())
					st.student_to_file(fs);
				else
					cout << " File was not opened!\n";
				fs.close();
				cout << " Registration completed successfully!\n";
				system("pause");
				break;
			}
			default:
			{
				if (choice > 2 || choice < 0){
					cout << " Wrong choice\n";
				}
				break;
			}
			}
		}
		else if (symbol == 'N')
		{
			cout << " LOGIN: ";
			cin >> login;
			cout << " PASSWORD: ";
			cin >> password;
			if (admin.Check_Admin_Password(password) == true && admin.Check_Admin_Login(login) == true)
			{
				do
				{
					system("cls");
					cout << " \tAdmin Menu:\n\n";
					cout << "1 - Load from file" << endl;
					cout << "2 - Create  Student" << endl;
					cout << "3 - Delete  Student" << endl;
					cout << "4 - Change Student Data" << endl;
					cout << "5 - Check Tests Results by Students" << endl;    // out to file
					cout << "6 - Add Category" << endl;
					cout << "7 - Add Test" << endl;
					cout << "8 - Add Question and variants of Answers" << endl;
					cout << "9 - Change Password" << endl;
					cout << "10 - Save & Login" << endl;

					students.print();
					cout << " Enter your choice: ";
					cin >> choice;
					switch (choice)
					{
					case 1:
					{
						fstream fs;
						fs.open("students.txt", fstream::in);
						if (fs.is_open()){
							students.load_from_file(fs);
						}
						fs.close();
						break;
					}
					case 2:
					{
						int amount_of_students;
						cout << " Enter amount of students you want add: ";
						cin >> amount_of_students;
						for (int i = 0; i < amount_of_students; i++)
						{
							cout << " New Student Registration: \n";
							cout << " Enter your name: ";
							cin >> st_name;                                        
							cout << " Enter your surname: ";
							cin >> st_surname;
							cout << " Enter your street: ";
							cin >> st_address;
							cout << " Enter your phone_number (model: +38077555555) ";
							cin >> st_phone_number;
							st.set_user(st_name, st_surname, st_address, st_phone_number);
							do {
								cout << " Set login: ";
								cin >> login;
							} while (students.Check_Student_Login(login) == true);                        
							st.set_login(login);
							cout << " Set password: ";
							cin >> password;
							st.set_password(password);
							students.add_student(st);
							cout << " Registration completed successfully!\n";
						}
						break;
					}
					case 3:
					{
						cout << " Enter Student's Surname you want to delete: \n";
						cout << " Surname: ";
						cin >> st_surname;
						students.delete_student(st_surname);
						cout << "\n Student was deleted!\n\n";
						break;
					}
					case 4:
					{
						cout << " Enter Name & Surname for student you want to change data: \n";
						cout << " Name: ";
						cin >> st_name;
						cout << " Surname: ";
						cin >> st_surname;
						int num;
						cout << " Press 1 - Change phone number. \n";
						cout << " Press 2 - Change address. \n";
						cout << " Enter choice: ";
						cin >> num;
						if (num == 1){
							cout << " Enter new phone number: ";
							cin >> st_phone_number;
							students.change_phone(st_name, st_surname, st_phone_number);
						}
						if (num == 2){
							cout << " Enter new address: ";
							cin.ignore();
							getline(cin, st_address);
							students.change_address(st_name, st_surname, st_address);
						}
						break;
					}
					case 5:
					{
						vector<string> files;
						string student_file, str;
						for (auto& e : f::directory_iterator("StudentsReport"))
						{
							files.push_back(e.path().string());
						}
						for (auto el : files)
						{
							cout << " " << el << endl;
						}
						cout << " Enter file name of student you want to see results: ";
						cin >> student_file;
						fs.open("StudentsReport\\" + student_file + ".txt", fstream::in);
						cout << " Chosen student report: \n" << print_student_report(fs) << endl;
						system("pause");
						break;
					}
					case 6:
					{
						Category c;
						cout << " Enter Test Category: ";
						cin.ignore();
						getline(cin, test_category);
						c.set_title(test_category);
						c.set_file(test_category + ".txt");
						c.write_cat_to_file(test_category);
						ofstream out(test_category + ".txt");
						cout << " New Category was set up!\n";
						system("pause");
						break;
					}
					case 7:
					{
						cout << " Enter Test Category where you want to add test: ";
						cin.ignore();
						getline(cin, test_category);
						cout << " Enter test name: ";
						cin >> test_name;                                
						test.set_test_name(test_name);
						test.set_file(test_name);
						if (File_Exists(test_name + ".txt") == false)
						{
							ofstream out(test_name + ".txt");
							test.write_test_name_to_cat_file(test_category, test_name);
						}
						else
							test.write_test_name_to_cat_file(test_category, test_name);
						cout << " New File for Test was set up!\n";
						system("pause");
						break;
					}
					case 8:
					{
						Questions questions;
						string q;
						int amount_of_q, amount_of_answers;
						char corr_answer;
						char answer[100];
						vector<string> var_an;
						cout << " Enter test name where to add questions: ";
						cin.ignore();
						getline(cin, test_name);
						cout << " Enter amount of questions: ";
						cin >> amount_of_q;
						cout << " Enter amount of answers: ";
						cin >> amount_of_answers;
						for (int i = 0; i < amount_of_q; i++)
						{
							cout << " Set correct answer: ";
							cin >> corr_answer;
							cout << " Enter Question: ";
							cin.ignore();
							getline(cin, q);
							for (int j = 0; j < amount_of_answers; j++)
							{
								cout << " Enter answer: ";
								cin.getline(answer, '100');
								var_an.push_back(answer);
							}
							questions.setData(q, var_an, corr_answer);
							fs.open(test_name + ".txt", fstream::app);
							if (fs.is_open())
								questions.question_to_file(fs);
							else
								cout << " File was not opened!\n";
							fs.close();
							var_an.clear();
						}
						cout << " New Questions were added!\n";
						system("pause");
						break;
					}
					case 9:
					{
						cout << " Enter new login: ";
						cin >> login;
						admin.set_login(login);
						cout << " Enter new password: ";
						cin >> password;
						admin.set_password(password);
						fs.open("admin.txt", fstream::binary | fstream::out);
						if (fs.is_open())
							admin.guest_to_file(fs);
						else
							cout << " File was not opened!\n";
						fs.close();
						cout << " Login and Password was changed!\n";
						system("pause");
						break;
					}

					default:
					{
						if (choice > 10 || choice <= 0){
							cout << " Wrong choice\n";
						}
						break;
					}
					}
				} while (choice != 10);
				
				fs.open("students.txt", fstream::out);
				if (fs.is_open())
					students.load_students_to_file(fs);
				else
					cout << " File was not opened!\n";
				fs.close();
			}
			else if (students.Check_Student_Login(login) == true && students.Check_Student_Password(password) == true)
			{
				string categ, category, file_with_tests;
				string filename;
				do
				{
					cout << " 1 - PASS THE TEST.\n";
					cout << " 2 - CHECK THE RESULT.\n";
					cout << " 3 - EXIT.\n";
					cout << " Enter your choice: ";
					cin >> choice;
					switch (choice)
					{
					case 1:
					{
						cout << " CHOOSE CATEGORY\n";
						fs.open("folder.txt", fstream::in);
						if (fs.is_open()){
							while (true)
							{
								fs >> categ;
								if (fs.eof()) break;
								folder.push_back(categ);
							}
							Printer<string>::print(folder);
							cout << " Enter category you choose: ";
							cin >> category;
							auto it = find(folder.begin(), folder.end(), category);
							if (it == folder.end())
								cout << " Category was not found!\n";
							else
								file_with_tests = *it;
						}
						else
							cout << " File was not opened!\n";
						fs.close();
						string test_name, test_n;
						vector<string> n_t;
						fs.open(file_with_tests + ".txt", fstream::in | fstream::out);
						if (fs.is_open()){
							while (!fs.eof())
							{
								fs >> test_n;
								if (fs.eof()) break;
								n_t.push_back(test_n);
							}
						}
						fs.close();
						Printer<string>::print(n_t);
						cout << " Enter test you want to pass: ";
						cin >> test_name;
						cout << " Pass The Test.\n";
						fs.open(test_name + ".txt", fstream::in | fstream::out);
						if (fs.is_open())
							test.test_from_file(fs);
						else
							cout << " File was not opened!\n";
						fs.close();
						char answer;
						int count_answ = 0;
						int q_c = 0;
						for (auto item : test.get_test()){
							cout << item << endl;
							cout << " Enter your answer: ";
							cin >> answer;
							st.set_passed_answers(answer);
							q_c++;
							if (answer == item.get_correct_answer())
							{
								count_answ++;
								cout << " SUPER!!!\n";
							}
						}
						cout << "\n";
						system("pause");
						st.set_percent(q_c, count_answ);
						st.set_mark(q_c, count_answ);
						cout << "\n Create file to save results: ";
						cin >> filename;
						st.set_file(filename);
						st.record_passed_to_file(filename, test_name);
						cout << " Your test was saved! \n\n";
						break;
					}
					case 2:
					{
						cout << " Enter your file name: ";
						cin >> filename;
						fs.open("StudentsReport\\" + filename + ".txt", fstream::in);
						cout << print_student_report(fs) << endl;
						break;
					}
					default:
					{
						if (choice > 3 || choice <= 0){
							cout << " Wrong choice\n";
						}
						break;
					}
					}
				} while (choice != 3);
			}
			else
			{
				cout << " Login or Password is wrong!\n";
				cout << " Try Again!\n";
				system("pause");
			}
		}

	} while (symbol != 'X');

	cout << " Thank you for checking! \n";
	fs.open("students.txt");
	if (fs.is_open())
	{
		fs.close();
	}


	return 0;
}



