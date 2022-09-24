#include "issue.hpp"
#include "project.hpp"
#include "container.hpp"
#include "main_utilities.hpp"
#include <iostream>

using namespace std;

int main()
{
    Container *c = new Container();
    // startup the program asking to create/load project
    startup(c);

    while (true) {
        cout << "-----------------------------------------------------------------" << endl;
        User* currentUser = c->getCurrentUser();
        string role;
        if (currentUser->getUserType() == MEMBER) {
            role = "Member";
        }
        else if (currentUser->getUserType() == LEAD) {
            role = "Lead";
        }
        else if (currentUser->getUserType() == OWNER) {
            role = "Owner";
        }
        cout << "Currently logged in as: " << currentUser->getUsername() << " (" << role << ")" << endl;
        cout << "Working on project: " << (c->getCurrentProject())->getName() << endl << endl;

        cout << "Options:" << endl;
        // different roles have different options available to them 
        if (role == "Member") {
            showMemberOptions();
            vector<int> selections{1, 2, 3, 4, 5, 6, 7};
            int optionSelected = readNumber(selections);
            // keep reading until valid input
            while (optionSelected == -1) {
                optionSelected = readNumber(selections);
            }

            // given an option selected for a member, handle the selection
            if (handleMemberSelection(optionSelected, c) == 1) {
                // exit
                cout << "-----------------------------------------------------------------" << endl;
                break;
            }
        }
        else if (role == "Lead") {
            showLeadOptions();
            vector<int> selections{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
            int optionSelected = readNumber(selections);
            // keep reading until valid input
            while (optionSelected == -1) {
                optionSelected = readNumber(selections);
            }

            // given an option selected for a lead, handle the selection
            if (handleLeadSelection(optionSelected, c) == 1) {
                // exit
                cout << "-----------------------------------------------------------------" << endl;
                break;
            }
        }
        else if (role == "Owner") {
            showOwnerOptions();
            vector<int> selections{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
            int optionSelected = readNumber(selections);
            // keep reading until valid input
            while (optionSelected == -1) {
                optionSelected = readNumber(selections);
            }

            // given an option selected for an owner, handle the selection
            if (handleOwnerSelection(optionSelected, c) == 1) {
                // exit
                cout << "-----------------------------------------------------------------" << endl;
                break;
            }
        }
    } 

    // free up memory for user pointers and project pointers
    for (auto i : (c->getCurrentProject())->getToDo()) {
        delete i;
    }
    for (auto i : (c->getCurrentProject())->getWorkDone()) {
        delete i;
    }
    for (auto s : (c->getCurrentProject())->getInProgress()) {
        for (auto i : s->getIssues()) {
            delete i;
        }
    }
    for (auto user : (c->getCurrentProject())->getUsers()) {
        delete user;
    }
    delete c;
}