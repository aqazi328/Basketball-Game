#include <fstream>
#include <iostream>
#include <time.h>
using namespace std;

class Player
{
public:
	int number;
	int age;
	int minutes;

	bool isOnCourt;

	//Player *next;
	//Player *prev;

	Player() {
		this->number = -1;
		this->age = -1;
		this->minutes = -1;
		this->isOnCourt = false;

	}

	Player(int number, int age, int minutes, bool isOnCourt)
	{
		this->number = number;
		this->age = age;
		this->minutes = minutes;
		this->isOnCourt = isOnCourt;
	}
};

class Bench : public Player
{
public:
	Bench* head;
	Bench* tail;
	char status;
	bool right; //determines if player should come from right/left side of bench

	Bench* next;
	Bench* prev;

	Bench()
	{
		this->head = NULL;
		this->tail = NULL;
		right = true;
	}

	Bench(Player* player)
	{
		this->number = player->number;
		this->age = player->age;
		this->minutes = player->minutes;
		this->status = 'B';
	}

	void returnToBench(Player* s)
	{
		if (right)
			addLast(s);
		else
			addFirst(s);
	}

	void addFirst(Player* s) {
		Bench* t = new Bench(s);
		Bench* cu = head;
		t->prev = NULL;
		t->next = cu;
		cu->prev = t;
		head = t;
	}

	void addLast(Player* s) {
		Bench* t = new Bench(s);
		Bench* cu = head;
		while (cu->next) {
			cu = cu->next;
		}
		t->prev = cu;
		t->next = NULL;
		cu->next = t;
		tail = t;
	}

	void add(Player* x)
	{
		Bench* y = new Bench(x);

		if (head == NULL)
		{
			head = y;
			tail = y;
			y->prev = NULL;
			return;
		}

		y->prev = tail;
		tail->next = y;
		tail = y;
	}

	void remove(int playerNumber) // DEB -- todo fix any leaks (delete[] where new was used)
	{
		Bench* tmp = head;
		Bench* previous = NULL;

		while (tmp != NULL)
		{
			if (tmp->number == playerNumber)
			{
				// found player
//                printf("found player\n");
				if (tmp == head)
				{
					if (tail == head) // or tail == head? is same thing?
					{
						head = NULL;
						tail = NULL;
					}
					else {

						//tail->next = head->next;
						head = head->next;
					}
				}
				else {
					previous->next = tmp->next;

					if (tmp == tail)
						tail = previous;
				}

				break;
			}
			previous = tmp;
			tmp = tmp->next;
		}
	}

	Player* getReplacement() {
		Bench* cu = head;
		if (right) {           //picks from end of list
			while (cu->next) {
				cu = cu->next;
			}
			cu = cu->prev;
			right = false;      //next time will pick from beginning of list
			return cu;
		}
		else
		{
			cu = cu->next;
			right = true;           //next time will pick from end of list
			return cu;
		}
	}



	void getFirst() {                   //age, number, minut
		Bench* cu = head;
		cout << cu->age << " " << cu->number << " " << cu->minutes << endl;
	}

	void getLast() {
		Bench* cu = head;
		while (cu) {
			cu = cu->next;
		}
		cout << cu->age << " " << cu->number << " " << cu->minutes << endl;
	}


	Bench* get(int index)
	{
		if (head == NULL)
			return NULL;
		Bench * tmp = head;
		int counter = 0;
		while (tmp != NULL) {
			if (counter == index) {
				return tmp;
			}
			tmp = tmp->next;
			++counter;
		}

		return NULL;
	}

	void swap(Bench * x, Bench * y)
	{
		int tempNumber = x->number;
		int tempAge = x->age;
		int tempMinutes = x->minutes;

		x->number = y->number;
		x->age = y->age;
		x->minutes = y->minutes;

		y->number = tempNumber;
		y->age = tempAge;
		y->minutes = tempMinutes;
	}

	void sort(string sortBy) {
		for (int i = 0; i < 12 - 1; i++)
			for (int j = 0; j < 12 - 1; j++) {
				Bench* x = get(j);
				Bench* y = get(j + 1);

				if (sortBy == "number" && x->number > y->number) {
					swap(x, y);
				}
				if (sortBy == "minutes" && x->minutes > y->minutes) {
					swap(x, y);
				}
				if (sortBy == "age" && x->age > y->age) {
					swap(x, y);
				}
			}
	}

	void print()
	{
		cout << "This is the bench: ";
		Bench* tmp = head;
		while (tmp != NULL) {
			cout << tmp->number;
			if (tmp->next != NULL)
				cout << " --> ";
			tmp = tmp->next;
		}
		cout << endl;
	}

	void report1(ofstream* outfile)
	{
		//ofstream outfile;
		//outfile.open("report1.txt");  // change string to fileName

		sort("number");
		cout << "Number" << "\t" << "Minutes Played" << endl;
		*outfile << "Number" << "\t" << "Minutes Played" << endl;
		Bench* tmp = head;
		while (tmp != NULL) {
			cout << tmp->number << "\t" << "\t" << tmp->minutes << endl;
			*outfile << tmp->number << "\t" << "\t" << tmp->minutes << endl;

			tmp = tmp->next;
		}
		cout << endl;
		*outfile << endl;
		//outfile.close();
	}

	void report2(ofstream *outfile)
	{
		sort("age");
		cout << "Age" << "\t" << "Number" << "\t" << "Minutes Played" << endl;
		*outfile << "Age" << "\t" << "Number" << "\t" << "Minutes Played" << endl;
		Bench* tmp = head;
		while (tmp != NULL) {
			cout << tmp->age << "\t" << tmp->number << "\t" << "\t" << tmp->minutes << endl;
			*outfile << tmp->age << "\t" << tmp->number << "\t" << "\t" << tmp->minutes << endl;
			tmp = tmp->next;
		}
		cout << endl;
		*outfile << endl;
		//outfile->close();
	}
};

class Court : public Player
{
public:
	Court* head;
	Court* tail;
	char status;
	int size;

	Court* next;
	Court* prev;

	Court()
	{
		this->head = NULL;
		this->tail = NULL;
		this->size = 0;
		this->next = NULL;
	}

	Court(Player* player)
	{
		this->number = player->number;
		this->age = player->age;
		this->minutes = player->minutes;
		this->status = 'C';
	}

	void add(Player* x)
	{
		Court* y = new Court(x);

		if (size >= 5)
			return;
		++size;

		if (head == NULL)
		{
			head = y;
			y->next = head;
			y->status = 'C';
			tail = y;
			return;
		}

		Court* tmp = head;
		Court* prev = NULL;

		while (true)
		{
			if (y->number < tmp->number)
			{
				if (tmp == head)
				{
					y->next = tmp;
					while (tmp->next != head)
					{
						tmp = tmp->next;
					}
					tail = tmp;
					tmp->next = y;
					head = y;
				}
				else
				{
					prev->next = y;
					y->next = tmp;
				}
				break;
			}

			prev = tmp;
			tmp = tmp->next;

			if (tmp == head)
			{
				prev->next = y;
				y->next = tmp;
				tail = y;
				break;
			}
		}
	}

	Court* get(int index)
	{
		if (head == NULL)
			return NULL;
		if (index < 0 || index >= size)
			return NULL;

		Court * tmp = head;
		int counter = 0;
		while (tmp != NULL) {
			if (counter == index)
				return tmp;

			tmp = tmp->next;
			++counter;
		}

		return NULL;
	}

	void addMinute()
	{
		Court* tmp = head;

		while (tmp != NULL) {
			tmp->minutes++;
			if (tmp->next == head)
				break;
			tmp = tmp->next;
		}
	}

	Court* getOldest()
	{
		Court* tmp = head;
		Court* oldest = NULL;
		int highestAge = 0;

		while (tmp != NULL) {
			if (tmp->age > highestAge) {
				oldest = tmp;
				highestAge = oldest->age;
			}

			if (tmp->next == head)
				break;
			tmp = tmp->next;
		}
		return oldest;
	}

	void remove(int playerNumber)
	{
		Court* tmp = head;
		Court* previous = NULL;

		if (size == 0)
			return;

		while (tmp != NULL)
		{
			if (tmp->number == playerNumber)
			{
				if (tmp == head)
				{
					if (size == 1)
					{
						head = NULL;
						tail = NULL;
					}
					else {

						tail->next = head->next;
						head = head->next;
					}
				}
				else {
					previous->next = tmp->next;

					if (tmp == tail)
						tail = previous;
				}
				size--;

				break;
			}

			if (tmp->next == head)
				break;

			previous = tmp;
			tmp = tmp->next;
		}
	}

	void returnToBench(Bench * b)
	{
		Court* tmp = head;

		while (head != NULL) {
			b->add(tmp);
			remove(tmp->number);
			//print();

			tmp = tmp->next;
		}

	}


	void print()
	{
		cout << "This is the court: ";

		Court* tmp = head;

		while (tmp != NULL) {
			cout << tmp->number;
			if (tmp->next != head)
				cout << " --> ";
			else
				break;
			tmp = tmp->next;
		}

		cout << endl;
	}

	void sort(string sortBy)
	{
		for (int i = 0; i < size - 1; i++)
			for (int j = 0; j < size - 1; j++) {
				Court* x = get(j);
				Court* y = get(j + 1);

				if (sortBy == "number" && x->number > y->number) {
					int tmp = x->number;
					x->number = y->number;
					y->number = tmp;
				}
				if (sortBy == "minutes" && x->minutes > y->minutes) {
					int tmp = x->minutes;
					x->minutes = y->minutes;
					y->minutes = tmp;
				}
				if (sortBy == "age" && x->age > y->age) {
					int tmp = x->age;
					x->age = y->age;
					y->age = tmp;
				}
			}
	}
};

int main(int argc, char** argv)
{
	Player* lockerRoom[12];
	Court court;
	Bench bench;


	ifstream inputfile;
	string fileName;

	if (argc >= 2)
		fileName = argv[1];
	else
		fileName = "input1.txt";

	inputfile.open(fileName);  // change string to fileName

	int i = 0;
	int number, age;
	while (!inputfile.eof()) {
		inputfile >> number >> age;
		lockerRoom[i] = new Player(number, age, 0, false);  //number, age, minutes, oncourt?
		i++;
	}
	ofstream outputfile;

	//random selector
	const int amount = 5; //amount of random numbers
	const int max = 12; //maximum value (of course, this must be at least the same as AMOUNT)
	int selection[amount];
	srand(time(NULL));
	for (int i = 0; i < amount; i++)
	{
		bool check;
		int n;
		do {
			n = rand() % max;
			check = true;
			for (int j = 0; j < i; j++)
				if (n == selection[j]) {
					check = false;
					break;
				}
		} while (!check);
		selection[i] = n;

		court.add(lockerRoom[n]);
		lockerRoom[n]->isOnCourt = true;
	}

	// Add the remaining players to the bench // DEB
	for (int i = 0; i < 12; i++) { // DEB
		if (lockerRoom[i]->isOnCourt == false) {
			bench.add(lockerRoom[i]);
		}
	}

	// Game play - DEB
	for (int quarter = 1; quarter <= 4; quarter++)
		for (int minutes = 0; minutes < 12; minutes++)
		{
			court.addMinute();
			Player* oldest = court.getOldest();
			if (oldest != NULL)
			{
				if (oldest->minutes > oldest->age * 0.10)
				{
					court.remove(oldest->number);
					Player* replacement = bench.getReplacement();
					bench.remove(replacement->number);
					court.add(replacement);
					bench.returnToBench(oldest);
				}
			}
		}
	// court players return to bench
	court.returnToBench(&bench);

	ofstream *outfile = new ofstream();
	string outName = fileName + "reports.txt";
	outfile->open(outName);  // change string to fileName

	cout << "REPORT 1" << endl << endl;
	*outfile << "REPORT 1" << endl << endl;
	bench.report1(outfile);

	cout << endl << "REPORT 2" << endl << endl;
	*outfile << endl << "REPORT 2" << endl << endl;
	bench.report2(outfile);

	outfile->close();

	for (int x = 0; x < 12; x++) {
		delete lockerRoom[x];
	}
	return 0;
}