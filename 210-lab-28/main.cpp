// 210 | Lab 28 | Neil Orton
// IDE Used: Xcode
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

void merge_lists(list<Goat> &trip, string [], string []);    // merge list prorotype
void fill_list(list<Goat> &trip, string [], string []);    // fill list prorotype
void reverse_list(list<Goat> &trip);    // reverse list prorotype
void clear_list(list<Goat> &trip);    // clear list prorotype
void sort_list(list<Goat> &trip);    // sort list prorotype
void replace_data(list<Goat> &trip);    // replace element prorotype
void get_unique(list<Goat> &trip);    // get unique prorotype
void find_Goat(list<Goat> trip);    // find element in list prorotype

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
    
    // Goat Manager 3002 Engine
    int sel = main_menu();
    while (sel != CHOICES) {    // while loop to run the main menu oprions
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
                merge_lists(trip, names, colors);    // case 4: merge list is run
                break;
            case 5:
                fill_list(trip, names, colors);    // case 5: fill list is run
                break;
            case 6:
                reverse_list(trip);    // case 6: reverse list is run
                break;
            case 7:
                clear_list(trip);    // case 7: clear list is run
                break;
            case 8:
                sort_list(trip);    // case 8: sort list is run
                break;
            case 9:
                replace_data(trip);    // case 9: replace element run
                break;
            case 10:
                get_unique(trip);    // case 10: get unique list is run
                break;
            case 11:
                find_Goat(trip);    // case 11: find element in list list is run
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
    cout << "*** GOAT MANAGER 3002 ***\n";
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
    
    for (int i = 0; i < trip.size(); i++) {    // new list of goats made
      int age = rand() % MAX_AGE;
      string nm = nms[rand() % SZ_NAMES];
      string cl = cls[rand() % SZ_COLORS];
      Goat tmp(nm, age, cl);
    trip2.push_back(tmp);
    }
    
    cout << "List to merge\n";    // new list printed
    int i = 1;
    for (auto gt : trip2) {
        cout << "\t"
        << "[" << i++ << "] "
        << gt.get_name()
        << " (" << gt.get_age()
        << ", " << gt.get_color() << ")\n";
    }
    list<Goat> mergedList(trip.size() + trip2.size());    // merged list size initialized
    
    cout << "Merging list...\n";
    merge(trip.begin(), trip.end(), trip2.begin(), trip2.end(), mergedList.begin());    // lists merged
    trip = mergedList;    // Goat list assigned to the merged list
    cout << "Merging complete\n";
    display_trip(trip);    // newly merged list displayed
}

void fill_list(list<Goat> &trip, string nms[], string cls[]) {
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);    // temporary Goat object constructed

    cout << "Filling list with new Goat...\n";
    fill(trip.begin(), trip.end(), tmp);     // list filled with temporary Goat object
    cout << "Complete\n";
    display_trip(trip);    // filled list displayed
}

void reverse_list(list<Goat> &trip) {
    cout << "Reversing list...\n";
    reverse(trip.begin(), trip.end());    // list reversed via reverse algorithm function
    cout << "Complete\n";
    display_trip(trip);    // reversed list displayed
}

void clear_list(list<Goat> &trip) {
        cout << "Clearing...\n";
        trip.clear();    // list cleared via clear algorithm function
        cout << "List of Goats is now " << trip.size() << endl;
        cout << "----------------------------" << endl;
}

void sort_list(list<Goat> &trip) {
    cout << "Sorting...\n";
    trip.sort();    // list sorteded via sort algorithm function
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
    
    cout << "Enter Goat data you want to replace\n";    // user enters the name, age, and color of Goat they want to replace
    cout << "Name: ";
    cin >> name1;
    cout << "Age: ";
    cin >> age1;
    cout << "Color: ";
    cin >> color1;
    
    cout << "Enter Goat data you want to add\n";    // user enters the name, age, and color of Goat they want to add
    cout << "Name: ";
    cin >> name2;
    cout << "Age: ";
    cin >> age2;
    cout << "Color: ";
    cin >> color2;
    
    Goat goat1(name1, age1, color1);    // Goat objects constructed with inputs as arguments
    Goat gaot2(name2, age2, color2);
    replace(trip.begin(), trip.end(), goat1, gaot2);    // replace function replaces the respective Goat in the list
    display_trip(trip);
}

void get_unique(list<Goat> &trip) {
    sort_list(trip);
    cout << "Removing duplicate values...\n";
        auto newEnd = unique(trip.begin(), trip.end());    // unique checks duplicates
        trip.erase(newEnd, trip.end());    // erase removes duplicates
    cout << "Complete\n";
        display_trip(trip);
}

void find_Goat(list<Goat> trip) {
    int age;
    string name;
    string color;

    cout << "Name to search: ";    // user enters the name, age, and color of Goat they want to search
    cin >> name;
    cout << "Age to search: ";
    cin >> age;
    cout << "Color to search: ";
    cin >> color;
    Goat tmp(name, age, color);    // Goat objects constructed with inputs as arguments

    auto it = find(trip.begin(), trip.end(), tmp);    // iterator moves to tmp Goat object
    if (it != trip.end()) {
        cout << "Found the Goat: " << it->get_name() << " (" << it->get_age() << ", " << it->get_color() << ")"<< endl;    // Goat object outputted if found
    } else {
        cout << "Goat not found\n";    // messae if Goat object is not found
    }
    cout << "----------------------------" << endl;
}
