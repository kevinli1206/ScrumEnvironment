#ifndef ISSUE_H
#define ISSUE_H

#include <string>
#include <ctime>

class Issue {
    private:
        int id;
        std::string type;
        int priority;
        time_t dateCreated;
        time_t dateDue;
    public:
        // default constructor
        Issue();
        // overloaded constructor
        Issue(int, std::string, int, time_t, time_t);
        // destructor
        ~Issue() {
            
        }
        // getters
        int getId();
        std::string getType();
        int getPriority();
        time_t getDateCreated();
        time_t getDateDue();
        double getCompletionPercentage();
        // setters
        void setID(int);
        void setType(std::string);
        void setPriority(int);
        void setDateCreated(time_t);
        void setDateDue(time_t);
        // others
        void displayIssue();
        std::string toString();
};

#endif
