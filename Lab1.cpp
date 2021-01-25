#include <iostream>
#include <string>
#include <fstream>
#include <Windows.h>

using namespace std;

class Person;

void CreateFileInProject(string);
void ReadFile(string);
int HASH_func(const string);
void find_to_person();
Person* bin_search(string, int, int);


const int arr_size = 510;
int arr_count[arr_size];
Person* arr_pers[arr_size];

class Person
{
	string FIO;
	string DATA;
	int index;
	Person* next_pers;
	Person* prev_pers;

public:
	Person(){
		index = 0;
		next_pers = nullptr;
		prev_pers = nullptr;
	}
	string get_FIO(){ return this->FIO; }
	void set_FIO(string FIO){ this->FIO = FIO; }
	void set_DATA(string DATA){ this->DATA = DATA; }

	void set_index(int index){ this->index = index; }
	void out_Person(){
		cout << "ФИО - " << FIO << endl;
		cout << "Данные - " << DATA << endl;
		cout << "index - " << index << endl << endl << endl;
	}

	void enlarge_next(){
		this->index++;
		if (this->next_pers != nullptr)
		{
			(*next_pers).enlarge_next();
		}
	}
	void insert_pers(Person*);
	Person* if_left(Person* val_pers);
	void out_list(){
		if (this->next_pers == nullptr)
		{
			this->out_Person();
		}
		else
		{
			this->out_Person();
			this->next_pers->out_list();
		}
	}
	Person* ret_under_index(int value){
		if (this->index == value)
		{
			return this;
		}
		else
		{
			if (this->next_pers == nullptr)
			{
				return nullptr;
			}
			else
			{
				this->next_pers->ret_under_index(value);
			}
		}

	}
};

bool operator > (Person &first_pers, Person &second_pers){
	string FIO1 = first_pers.get_FIO(), FIO2 = second_pers.get_FIO();
	int count = 0;

	if (FIO2.length() > FIO1.length())
	{
		count = FIO1.length();
	}
	else
	{
		count = FIO2.length();
	}

	for (int i = 0; i < count; i++)
	{
		if (FIO1[i] > FIO2[i])
		{
			return true;
		}
		else if (FIO1[i] < FIO2[i])
		{
			return false;
		}
	}

	if (count == FIO2.length())
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool operator < (Person &first_pers, Person &second_pers){
	string FIO1 = first_pers.get_FIO(), FIO2 = second_pers.get_FIO();
	int count = 0;

	if (FIO2.length() > FIO1.length())
	{
		count = FIO1.length();
	}
	else
	{
		count = FIO2.length();
	}

	for (int i = 0; i < count; i++)
	{
		if (FIO1[i] > FIO2[i])
		{
			return false;
		}
		else if (FIO1[i] < FIO2[i])
		{
			return true;
		}
	}

	if (count == FIO2.length())
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool operator == (Person &first_pers, Person &second_pers){
	string FIO1 = first_pers.get_FIO(), FIO2 = second_pers.get_FIO();

	if (FIO1.length() != FIO2.length())
	{
		return false;
	}

	for (int i = 0; i < FIO1.length(); i++)
	{
		if (FIO1[i] != FIO2[i])
		{
			return false;
		}
	}
	return true;
}

void Person::insert_pers(Person* value){

	if ((value->prev_pers == nullptr) && (*this < *value))
	{
		this->index = value->index;
		arr_pers[HASH_func(this->FIO)] = this;
		value->prev_pers = this;
		this->next_pers = value;
		(*value).enlarge_next();
	}
	else if ((value->prev_pers == nullptr) && (value->next_pers == nullptr))
	{
		value->next_pers = this;
		this->prev_pers = value;
		this->index = value->index;
		this->enlarge_next();
	}
	else if ((value->next_pers == nullptr) && (*this > *value))
	{
		this->next_pers = value->next_pers;
		this->prev_pers = value;
		value->next_pers = this;
		this->index = value->index;
		this->enlarge_next();
	}
	else
	{
		value->prev_pers->next_pers = this;
		this->prev_pers = value->prev_pers;
		this->next_pers = value;
		value->prev_pers = this;
		this->index = value->index;
		(*value).enlarge_next();
	}
}

Person* Person::if_left(Person* val_pers){
	if ((this->next_pers == nullptr) || (*val_pers < *this))
	{
		return this;
	}
	else
	{
		(*(this->next_pers)).if_left(val_pers);
	}
}

void main(){
	setlocale(LC_ALL, "rus");
	string path = "File with data.txt";
	for (int i = 0; i < arr_size; i++)
	{
		arr_count[i] = 0;
	}
	for (int i = 0; i < arr_size; i++)
	{
		arr_pers[i] = nullptr;
	}
	unsigned int change;
	for (bool flag = true; flag;)
	{
		cout << "Чтобы создать пустой файл в папке проекта введите: 1 \n(После этого необходимо открыть файл и заполнить его следующим образом\nФИО:Данные:ФИО:Данные:)" << endl;
		cout << "Чтобы загрузить данные из файла введите: 2" << endl;
		cout << "Чтобы найти человека, введите: 3" << endl;
		cout << "Чтобы выйти введите любой другой символ." << endl;
		cin >> change;
		switch (change)
		{
		case 1:
			CreateFileInProject(path);
			system("pause");
			exit(1);
		case 2:
			ReadFile(path);
			break;
		case 3:
			find_to_person();
			break;
		default:
			flag = false;
			break;
		}
	}
	setlocale(LC_ALL, "rus");
	system("pause");
}

void CreateFileInProject(string path){
	ofstream FILE;
	FILE.open(path, ofstream::app);
	cout << "Файл создан в папку проекта, после закрытия программы запишите туда данные." << endl;
	FILE.close();
}

int HASH_func(const string FIO){
	return (unsigned char)FIO[0] + (unsigned char)FIO[1];
}

void input_pers(Person* value){
	if (arr_pers[HASH_func((*value).get_FIO())] == nullptr)
	{
		arr_pers[HASH_func((*value).get_FIO())] = value;
		(*value).enlarge_next();
	}
	else
	{
		(*value).insert_pers(arr_pers[HASH_func((*value).get_FIO())]->if_left(value));
	}
}

void ReadFile(string path){
	ifstream FILE;
	FILE.open(path);
	if (!FILE.is_open())
	{
		cout << "Ошибка загрузки базы." << endl;
	}
	else{
		bool flag = true;
		char temp_ch;
		string FIO, DATA;
		while (FILE.get(temp_ch))
		{
			if (flag)
			{
				if (temp_ch == ':')
				{
					flag = false;
				}
				else
				{
					FIO += temp_ch;
				}

			}
			else
			{
				if (temp_ch == ':')
				{
					flag = true;
					arr_count[HASH_func(FIO)]++;
					Person* pers = new Person;
					pers->set_FIO(FIO);
					pers->set_DATA(DATA);
					input_pers(pers);

					FIO.clear();
					DATA.clear();
				}
				else
				{
					DATA += temp_ch;
				}
			}
		}
	}
	cout << "База загружена" << endl << endl << endl;
	FILE.close();
}

void find_to_person(){

	string FIO;
	cout << "Введите ФИО: " << endl;
	SetConsoleCP(1251);
	cin.clear();
	cin.sync();
	getline(cin, FIO);
	SetConsoleCP(866);
	if (!FIO.empty())
	{
		int end_arr = 1, beg_arr = 1;
		end_arr = arr_count[HASH_func(FIO)];
		if (arr_count[HASH_func(FIO)] == 0 || bin_search(FIO, beg_arr, end_arr) == nullptr)
		{
			cout << "Этого человека нет в базе." << endl << endl << endl;
		}
		else
		{
			bin_search(FIO, beg_arr, end_arr)->out_Person();
		}
	}
}

Person* bin_search(string FIO, int begin_pers, int end_pers){

	int mid = (begin_pers + end_pers) / 2;
	Person persik;
	persik.set_FIO(FIO);
	Person* temp_ptr = arr_pers[HASH_func(FIO)]->ret_under_index(mid);
	if (temp_ptr == nullptr)
	{
		cout << "Ошиюка поиска элемента" << endl;
	}
	else
	{
		if (persik == *(temp_ptr))
		{
			return temp_ptr;
		}
		else if ((persik < *(temp_ptr)) && begin_pers != end_pers)
		{
			return bin_search(FIO, begin_pers, mid);
		}
		else if ((persik > *(temp_ptr)) && begin_pers != end_pers)
		{
			return bin_search(FIO, mid + 1, end_pers);
		}
		else
		{
			return nullptr;
		}

	}
}