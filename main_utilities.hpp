// utility functions for main
#include <vector>
#include <iostream>
#include "user.hpp"
#include "issue.hpp"
#include "project.hpp"
#include "container.hpp"

// reads a number from a user, returns -1 if invalid input (not a number or not one of selectionsAvailable)
int readNumber(std::vector<int> selectionsAvailable);

// initializes the startup procedure for the program
void startup(Container* &c);

// displays available options for members
void showMemberOptions();

// displays available options for leads
void showLeadOptions();

// displays available options for owners
void showOwnerOptions();

// handle option selected for members, return 0 on success, 1 on exit
int handleMemberSelection(int selectNum, Container* &c);

// handle option selected for leads, return 0 on success, 1 on exit
int handleLeadSelection(int selectNum, Container* &c);

// handle option selected for owners, return 0 on success, 1 on exit
int handleOwnerSelection(int selectNum, Container* &c);
