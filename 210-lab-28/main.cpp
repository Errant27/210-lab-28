#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <random>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25, CHOICES = 12;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

void merge_lists(list<Goat> &trip, string [], string []);
void fill_list(list<Goat> &trip, string [], string []);
void reverse_list(list<Goat> &trip);
void clear_list(list<Goat> &trip);
void sort_list(list<Goat> &trip);
void replace_data(list<Goat> &trip);
void get_unique(list<Goat> &trip);
void find_Goat(list<Goat> trip);



int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != CHOICES) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 4:
                merge_lists(trip, names, colors);
                break;
            case 5:
                fill_list(trip, names, colors);
                break;
            case 6:
                reverse_list(trip);
                break;
            case 7:
                clear_list(trip);
                break;
            case 8:
                sort_list(trip);
                break;
            case 9:
                replace_data(trip);
                break;
            case 10:
                get_unique(trip);
                break;
            case 11:
                find_Goat(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    
    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] Display goats\n";
    cout << "[4] Merge List\n";
    cout << "[5] Fill List\n";
    cout << "[6] Reverse List\n";
    cout << "[7] Clear List\n";
    cout << "[8] Sort List\n";
    cout << "[9] Replace Goat on List\n";
    cout << "[10] Get Unique valuest\n";
    cout << "[11] Search Goat in List\n";
    cout << "[12] Quit\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > CHOICES) {
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    cout << "----------------------------" << endl;
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
    cout << "----------------------------" << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
    cout << "----------------------------" << endl;
}

void display_trip(list<Goat> trip) {
    int i = 1;
    for (auto gt : trip)
        cout << "\t" << "[" << i++ << "] " << gt.get_name() << " (" << gt.get_age() << ", " << gt.get_color() << ")\n";
    cout << "----------------------------" << endl;
}

int select_goat(list<Goat> trip) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trip);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trip.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}

void merge_lists(list<Goat> &trip, string nms[], string cls[]) {
    list<Goat> trip2;
    
    for (int i = 0; i < trip.size(); i++) {
      int age = rand() % MAX_AGE;
      string nm = nms[rand() % SZ_NAMES];
      string cl = cls[rand() % SZ_COLORS];
      Goat tmp(nm, age, cl);
    trip2.push_back(tmp);
    }
    
    cout << "List to merge\n";
    int i = 1;
    for (auto gt : trip2) {
        cout << "\t"
        << "[" << i++ << "] "
        << gt.get_name()
        << " (" << gt.get_age()
        << ", " << gt.get_color() << ")\n";
    }
    list<Goat> mergedList(trip.size() + trip2.size());
    
    cout << "Merging list...\n";
    merge(trip.begin(), trip.end(), trip2.begin(), trip2.end(), mergedList.begin());
    trip = mergedList;
    cout << "Merging complete\n";
    display_trip(trip);
}

void fill_list(list<Goat> &trip, string nms[], string cls[]) {
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);

    cout << "Filling list with new Goat...\n";
    fill(trip.begin(), trip.end(), tmp);
    cout << "Complete\n";
    display_trip(trip);
}

void reverse_list(list<Goat> &trip) {
    cout << "Reversing list...\n";
    reverse(trip.begin(), trip.end());
    cout << "Complete\n";
    display_trip(trip);
}

void clear_list(list<Goat> &trip) {
        cout << "Clearing...\n";
        trip.clear();
        cout << "List of Goats is now " << trip.size() << endl;
        cout << "----------------------------" << endl;
}

void sort_list(list<Goat> &trip) {
    cout << "Sorting...\n";
    trip.sort();
    cout << "Complete\n";
    display_trip(trip);
}

void replace_data(list<Goat> &trip) {
    string name1;
    string name2;
    int age1;
    int age2;
    string color1;
    string color2;
    
    cout << "Enter Goat data you want to replace\n";
    cout << "Name: ";
    cin >> name1;
    cout << "Age: ";
    cin >> age1;
    cout << "Color: ";
    cin >> color1;
    
    cout << "Enter Goat data you want to add\n";
    cout << "Name: ";
    cin >> name2;
    cout << "Age: ";
    cin >> age2;
    cout << "Color: ";
    cin >> color2;
    
    Goat goat1(name1, age1, color1);
    Goat gaot2(name2, age2, color2);
    replace(trip.begin(), trip.end(), goat1, gaot2);
    display_trip(trip);
}

void get_unique(list<Goat> &trip) {
    sort_list(trip);
    cout << "Removing duplicate values...\n";
        auto newEnd = unique(trip.begin(), trip.end());
        trip.erase(newEnd, trip.end());
    cout << "Complete\n";
        display_trip(trip);
}

void find_Goat(list<Goat> trip) {
    int age;
    string name;
    string color;

    cout << "Name to search: ";
    cin >> name;
    cout << "Age to search: ";
    cin >> age;
    cout << "Color to search: ";
    cin >> color;
    Goat tmp(name, age, color);

    auto it = find(trip.begin(), trip.end(), tmp);
    if (it != trip.end()) {
        cout << "Found the Goat: " << it->get_name() << " (" << it->get_age() << ", " << it->get_color() << ")"<< endl;
    } else {
        cout << "Goat not found\n";
    }
    cout << "----------------------------" << endl;
}
