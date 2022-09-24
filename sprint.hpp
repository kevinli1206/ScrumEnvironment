#ifndef SPRINT_H
#define SPRINT_H

#include "issue.hpp"
#include <iostream>
#include <vector>
#include <algorithm>

// to represent a Sprint
class Sprint {
    private:
        int deadline;
        std::vector<Issue*> issues;
        time_t dateCreated;
    public:
        // default constructor
        Sprint();

        // overloaded constructor
        Sprint(int, std::vector<Issue*>, time_t);

        // destructor
        ~Sprint();

        // add an issue to a sprint
        void addIssue(Issue*);
        // removes an issue from a sprint
        void removeIssue(Issue*);
    
        // getters
        int getDeadline();
        std::vector<Issue*> getIssues();
        time_t getDateCreated();
    
        // setters
        void setDeadline(int d);
        void setIssues(std::vector<Issue*> i);
        void setDateCreated(time_t dc);

        // check to see if the sprint is finished
        bool isFinished();

        // display information about a Sprint
        void displaySprint();
        std::string toString();
};

#endif
