#include "project.hpp"
#include <string>
using namespace std;

Project::Project()
{
    name = "";
}

Project::Project(string n, vector<Issue *> t, vector<Sprint *> s, vector<Issue *> d, vector<User *> u) : name(n), toDo(t), inProgress(s), workDone(d), collaborators(u)
{
}

std::vector<Issue *> Project::getToDo()
{
    return this->toDo;
}

std::vector<Sprint *> Project::getInProgress()
{
    return this->inProgress;
}

std::vector<Issue *> Project::getWorkDone()
{
    return this->workDone;
}

std::string Project::getName()
{
    return this->name;
}

std::vector<User *> Project::getUsers()
{
    return this->collaborators;
}

Issue *Project::getIssue(int id)
{
    // checks To Do
    for (auto issue : toDo)
        if (issue->getId() == id)
            return issue;
    // checks In Progress
    for (auto sprint : inProgress)
        for (auto issue : sprint->getIssues())
            if (issue->getId() == id)
                return issue;
    // checks Work Done
    for (auto issue : workDone)
        if (issue->getId() == id)
            return issue;
    // returns null pointer if not found
    return nullptr;
}

void Project::moveIssue(int id)
{
    string area;
    while (true)
    {
        cout << "Enter area to move to (To Do, In Progress, Work Done): ";
        getline(cin, area);
        Issue* i = getIssue(id);
        if (area == "To Do")
        {
            deleteIssue(id);
            toDo.push_back(i);
            break;
        }
        else if (area == "In Progress")
        {
            deleteIssue(id);
            try {
                inProgress.at(0)->addIssue(i);
            }
            catch (out_of_range &e) {
                cout << "No sprint exists!" << endl;
            }
            break;
        }
        else if (area == "Work Done")
        {
            deleteIssue(id);
            workDone.push_back(i);
            break;
        }
        else if (area == "q")
        {
            break;
        }
        else
        {
            cout << "Invalid area, please try again." << endl;
        }
    }
}

void Project::deleteIssue(int id)
{
    // checks To Do
    for (auto issue : toDo)
        if (issue->getId() == id)
            toDo.erase(remove(toDo.begin(), toDo.end(), issue), toDo.end());
    // checks In Progress
    for (auto sprint : inProgress)
        for (auto issue : sprint->getIssues())
            if (issue->getId() == id)
                sprint->removeIssue(issue);
    // checks Work Done
    for (auto issue : workDone)
        if (issue->getId() == id)
            workDone.erase(remove(workDone.begin(), workDone.end(), issue), workDone.end());
}

void Project::setName(std::string s)
{
    this->name = s;
}

void Project::addSprint(Sprint *s)
{
    this->inProgress.push_back(s);
}

void Project::addIssue(Issue *i)
{
    this->toDo.push_back(i);
}

void Project::addCollaborator(User *u)
{
    this->collaborators.push_back(u);
}

void Project::removeCollaborator(User *u)
{
    this->collaborators.erase(remove(this->collaborators.begin(), this->collaborators.end(), u), this->collaborators.end());
}

void Project::updateCollaborator(std::string oldName, std::string newName, std::string newRole)
{
    for (auto collab : this->collaborators)
    {
        if (collab->getUsername() == oldName)
        {
            collab->setUsername(newName);
            if (newRole == "Member")
            {
                collab->setUserType(MEMBER);
            }
            else if (newRole == "Lead")
            {
                collab->setUserType(LEAD);
            }
            else if (newRole == "Owner")
            {
                collab->setUserType(OWNER);
            }
            else
            {
                cout << "Unknown type. Error." << endl;
            }
        }
    }
}

void Project::displayIssueID()
{
    cout << "Displaying Issue ID's - To Do:" << endl;
    for (auto issue : getToDo())
    {
        cout << issue->getId() << " - " << issue->getType() << endl;
    }
    cout << endl;

    cout << "Displaying Issue ID's - In Progress:" << endl;
    for (auto sprint : getInProgress())
    {
        for (auto issue : sprint->getIssues())
        {
            cout << issue->getId() << endl;
        }
    }

    cout << "Displaying Issue ID's - Work Done:" << endl;
    for (auto issue : getWorkDone())
    {
        cout << issue->getId() << " - " << issue->getType() << endl;
    }
    cout << endl;
}

void Project::displayProject()
{
    std::cout << this->toString() << std::endl;
}

std::string Project::toString()
{
    std::string toBeReturned = "Name: " + name + "\n";
    toBeReturned.append("To Do\n");
    for (auto issue : toDo)
        toBeReturned.append(issue->toString());
    toBeReturned.append("In Progress\n");
    for (auto sprint : inProgress)
        toBeReturned.append(sprint->toString());
    toBeReturned.append("Work Done\n");
    for (auto issue : workDone)
        toBeReturned.append(issue->toString());
    for (auto u : collaborators)
    {
        toBeReturned.append("User: \nName: ");
        toBeReturned.append(u->getUsername());
        toBeReturned.append("\nType: ");
        toBeReturned.append(std::to_string(u->getUserType()));
        toBeReturned.append("\n");
    }
    return toBeReturned;
}