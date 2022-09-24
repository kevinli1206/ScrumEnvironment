// definitions for main_utilities.cpp
#include "main_utilities.hpp"
using namespace std;

// reads a number from a user, returns -1 if invalid input (not a number or not one of selectionsAvailable)
int readNumber(vector<int> selectionsAvailable) {
    string numStr;
    getline(cin, numStr);
    int inNum;
    // first check if input is even a number
    try {
        inNum = stoi(numStr);
    }
    catch (invalid_argument &e) {
        cout << "Invalid selection, please enter a number from the selections: ";
        return -1;
    }

    // now check if the number is part of the selections available
    for (int num : selectionsAvailable) {
        if (inNum == num) {
            return inNum;
        }
    }
    cout << "Invalid selection, please enter a number from the selections: ";
    return -1;
}

// initializes the startup procedure for the program
void startup(Container* &c) {
    cout << "Welcome to the Issue Tracking App." << endl;
    cout << "Begin by creating a new project (1) or loading an existing project (2): ";
    vector<int> selections{1, 2};
    int numberSelected = readNumber(selections);
    // keep reading until valid input
    while (numberSelected == -1) {
        numberSelected = readNumber(selections);
    }

    // create project option
    if (numberSelected == 1) {
        c->createProject();
        cout << endl;
    }
    // load existing project option
    if (numberSelected == 2) {
        c->loadProject();
        cout << "Project loaded successfully from project.txt" << endl << endl;
    }
}

// displays available options for members
void showMemberOptions() {
    // options unique to members here
    cout << "(1) Add an issue" << endl;
    cout << "(2) Update an issue" << endl;
    cout << "(3) View project details" << endl;
    cout << "(4) View area in project" << endl;

    // every role should have option to change user, save state, and exit
    cout << "(5) Change user" << endl;
    cout << "(6) Save current program state" << endl;
    cout << "(7) Exit program and save" << endl << endl;
    cout << "Select an option number: ";
}

// displays available options for leads
void showLeadOptions() {
    // options unique to leads here
    cout << "(1) Add an issue" << endl;
    cout << "(2) Update an issue" << endl;
    cout << "(3) Remove an issue" << endl;
    cout << "(4) Move an issue" << endl;
    cout << "(5) View project details" << endl;
    cout << "(6) View area in project" << endl;
    cout << "(7) Create a new sprint" << endl;
    cout << "(8) Update sprint details" << endl;
    cout << "(9) Add collaborators" << endl;

    // every role should have option to change user, save state, and exit
    cout << "(10) Change user" << endl;
    cout << "(11) Save current program state" << endl;
    cout << "(12) Exit program and save" << endl << endl;
    cout << "Select an option number: ";
}

// displays available options for owners
void showOwnerOptions() {
    // options unique to owners here
    cout << "(1) Add an issue" << endl;
    cout << "(2) Update an issue" << endl;
    cout << "(3) Remove an issue" << endl;
    cout << "(4) Move an issue" << endl;
    cout << "(5) View project details" << endl;
    cout << "(6) View area in project" << endl;
    cout << "(7) Create a new sprint" << endl;
    cout << "(8) Update sprint details" << endl;
    cout << "(9) Add collaborators" << endl;
    cout << "(10) Update project details" << endl;
    cout << "(11) Delete the project" << endl;

    // every role should have option to change user, save state, and exit
    cout << "(12) Change user" << endl;
    cout << "(13) Save current program state" << endl;
    cout << "(14) Exit program and save" << endl << endl;
    cout << "Select an option number: ";
}

// handle option selected for members, return 0 on success, 1 on exit
int handleMemberSelection(int selectNum, Container* &c) {
    cout << "(1) Add an issue" << endl;
    cout << "(2) Update an issue" << endl;
    cout << "(3) View project details" << endl;
    cout << "(4) View area in project" << endl;

    // every role should have option to change user, save state, and exit
    cout << "(5) Change user" << endl;
    cout << "(6) Save current program state" << endl;
    cout << "(7) Exit program and save" << endl << endl;
    switch(selectNum) {
        case 1:
            c->createIssue();
            break;
        case 2:
            c->updateIssue();
            break;
        case 3:
            c->viewProject();
            break;
        case 4:
            c->viewArea();
            break;
        case 5:
            c->changeUser();
            break;
        case 6:
            c->saveProject();
            break;
        case 7:
            c->saveProject();
            cout << "Exiting and saving program state to project.txt" << endl;
            return 1;
    }
    return 0;
}

// handle option selected for leads, return 0 on success, 1 on exit
int handleLeadSelection(int selectNum, Container* &c) {
    switch(selectNum) {
        case 1:
            c->createIssue();
            break;
        case 2:
            c->updateIssue();
            break;
        case 3:
            c->deleteIssue();
            break;
        case 4:
            c->moveIssue();
            break;
        case 5:
            c->viewProject();
            break;
        case 6:
            c->viewArea();
            break;
        case 7:
            c->createSprint();
            break;
        case 8:
            c->updateSprint();
            break;
        case 9:
            c->addUser();
            break;
        case 10:
            c->changeUser();
            break;
        case 11:
            c->saveProject();
            break;
        case 12:
            c->saveProject();
            cout << "Exiting and saving program state to project.txt" << endl;
            return 1;
    }
    return 0;
}

// handle option selected for owners, return 0 on success, 1 on exit
int handleOwnerSelection(int selectNum, Container* &c) {
    switch(selectNum) {
        case 1:
            c->createIssue();
            break;
        case 2:
            c->updateIssue();
            break;
        case 3:
            c->deleteIssue();
            break;
        case 4:
            c->moveIssue();
            break;
        case 5:
            c->viewProject();
            break;
        case 6:
            c->viewArea();
            break;
        case 7:
            c->createSprint();
            break;
        case 8:
            c->updateSprint();
            break;
        case 9:
            c->addUser();
            break;
        case 10:
            c->updateProject();
            break;
        case 11:
            c->deleteProject();
            return 1;
        case 12:
            c->changeUser();
            break;
        case 13:
            c->saveProject();
            break;
        case 14:
            c->saveProject();
            cout << "Exiting and saving program state to project.txt" << endl;
            return 1;
    }
    return 0;
}