#ifndef PROJECT_H
#define PROJECT_H

#include "issue.hpp"
#include "sprint.hpp"
#include "user.hpp"
#include <string>
#include <vector>
#include <algorithm>

class Project
{
private:
    std::string name;
    std::vector<Issue *> toDo;
    std::vector<Sprint *> inProgress;
    std::vector<Issue *> workDone;
    std::vector<User *> collaborators;

public:
    // default constructor
    Project();

    // overloaded constructor
    Project(std::string, std::vector<Issue *>, std::vector <Sprint *>, std::vector<Issue *>, std::vector<User *>);
    // destructor
    ~Project()
    {
        toDo.clear();
        inProgress.clear();
        workDone.clear();
        collaborators.clear();
    }
    // getters
    std::string getName();
    std::vector<Issue *> getToDo();
    std::vector<Sprint *> getInProgress();
    std::vector<Issue *> getWorkDone();
    std::vector<User *> getUsers();
    // handles issue based on id
    Issue* getIssue(int id);
    void moveIssue(int id);
    void deleteIssue(int id);
    // setters
    void setName(std::string);
    void addSprint(Sprint *);
    void addIssue(Issue *);
    void addCollaborator(User *);
    void removeCollaborator(User *);
    void updateCollaborator(std::string oldName, std::string newName, std::string newRole);
    // display a list of issue IDs to do and in progress
    void displayIssueID();
    // display information about a Project
    void displayProject();
    std::string toString();
};

#endif