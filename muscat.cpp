#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct track{
	string title;
	string artist;
	string genre;
	int tempo;
	string time_sig;
	string key_sig;
	int id;
};


void ask(const char* prompt, string* response){
	cout << prompt << endl;
	//cin >> *response;
	getline(cin,*response);
	if(response->compare("`") == 0)
		throw 1;
}

void add(struct track** list, int id){
	string info[6];
	ask("(1/6) What is the title of the track you wish to add?", &info[0]);
	ask("(2/6) Who is the artist of the track you wish to add?", &info[1]);
	ask("(3/6) What is the genre of the track you wish to add?", &info[2]);
	ask("(4/6) What is the tempo of the track you wish to add?", &info[3]);
	ask("(5/6) What is the time signature of the track you wish to add?", &info[4]);
	ask("(6/6) What is the key signature of the track you wish to add?", &info[5]);
	struct track* entry = new track;
	entry->title = info[0];
	entry->artist = info[1];
	entry->genre = info[2];
	entry->tempo = stoi(info[3]);
	entry->time_sig = info[4];
	entry->key_sig = info[5];
	entry->id = id;	
	for(int i = 0; i < 50; i++)
		if(list[i] == nullptr){
			list[i] = entry;
			break;
		}
}

void destroy(struct track** list, int ct){
	string input;
	ask("(1/2) What is the ID of the track you wish to delete?", &input);
	int id = stoi(input);
	for(int i = 0; i < ct; i++){
		if(list[i] == nullptr)
			ct++;
		else
			if(list[i]->id == id){
				char question[200];
				string confirmation;	
				sprintf(question, "(2/2) Are you sure you want to delete %s by %s ((y)es/(n)o)?", (list[i]->title).c_str(), (list[i]->artist).c_str());
				ask(question, &confirmation);
				if(confirmation.compare("y") == 0 || confirmation.compare("yes") == 0){
					delete list[i];
					list[i] = nullptr;
				} else
					throw 1;
				break;
			}
	}
}



int main(){
	fstream f = fstream();
	f.open("./cyanyoshida.txt");
	char line[300];
	f.getline(line, 200);
	string password;
	for(int i = 0;; i++){
		cout << "Enter password:" << endl;
		cin >> password;
		if(password.compare(line) == 0)
			break;
		cout << "Incorrect password" << endl;
		if(i == 2){
			cout << "Too many incorrect attempts" << endl;
			exit(1);
		}
	}
	struct track* list[50];
	for(int i = 0; i < 50; i++)
		list[i] = nullptr;
	int ct = 0;
	while(f.peek() != EOF){
		f.getline(line,200);
		list[ct] = new track;
		list[ct]->title = strtok(line,"|");
		list[ct]->artist = strtok(NULL,"|");
		list[ct]->genre = strtok(NULL,"|");
		list[ct]->tempo = atoi(strtok(NULL,"|"));
		list[ct]->time_sig = strtok(NULL,"|");
		list[ct]->key_sig = strtok(NULL,"|");
		list[ct]->id = ct;
		ct++;	
	}
	int id = ct;
	string input;
	while(1){
		int temp = ct;
		cout << endl << endl << endl << endl << endl;
		for(int i = 0; i < temp; i++){
			if(list[i] == nullptr)
				temp++;
			else
				cout << list[i]->title << ", " << list[i]->artist << ", " << list[i]->genre << ", " << list[i]->tempo << ", " << list[i]->time_sig << ", " << list[i]->key_sig << ", " << list[i]->id << endl;
		}
		cout << endl;
		cout << "Catalog your tracks!" << endl;	
		try{
			ask("commands: (a)dd, (d)elete, (`) to cancel at any time", &input);
			if(input.compare("a") == 0 || input.compare("add") == 0){
				add(list,id);
				ct++;
				id++;
			}else if(input.compare("d") == 0 || input.compare("delete") == 0){
				destroy(list, ct);
				ct--;
			}else
				cout << "Invalid command" << endl;
		}catch(...){
			cout << "Task cancelled" << endl;
		}
	}
}
