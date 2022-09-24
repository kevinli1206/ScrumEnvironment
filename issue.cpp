#include "issue.hpp"
#include <iostream>
#include <string>
#include <ctime>

Issue::Issue()
{
    static int _id = 0;
    this->id = _id++;            // generates a unique id
    this->dateCreated = time(0);
    this->type = "a";
}

Issue::Issue(int i, std::string t, int p, time_t dc, time_t dd) : 
id(i), type(t), priority(p), dateCreated(dc), dateDue(dd) {
}

int Issue::getId() {
    return id;
}

std::string Issue::getType()
{
    return this->type;
}

int Issue::getPriority()
{
    return this->priority;
}

time_t Issue::getDateCreated()
{
    return this->dateCreated;
}

time_t Issue::getDateDue()
{
    return this->dateDue;
}

double Issue::getCompletionPercentage()
{
    time_t now = time(0);
    return difftime(now, dateCreated) / difftime(dateDue, dateCreated) * 100;
}

void Issue::setID(int id) {
    this->id = id;
}

void Issue::setType(std::string t)
{
    this->type = t;
}

void Issue::setPriority(int p)
{
    this->priority = p;
}

void Issue::setDateCreated(time_t dc)
{
    this->dateCreated = dc;
}

void Issue::setDateDue(time_t dd)
{
    this->dateDue = dd;
}

void Issue::displayIssue()
{
    std::cout << toString() << std::endl;
}

std::string Issue::toString() {
    std::string toBeReturned = "ISSUE\n";
    toBeReturned.append("ID: " + std::to_string(id));
    toBeReturned.append("\n");
    toBeReturned.append("Type: " + type);
    toBeReturned.append("\n");
    toBeReturned.append("Priority: " + std::to_string(priority));
    toBeReturned.append("\n");
    toBeReturned.append("Date Created: " + std::string(ctime(&dateCreated)));
    // ctime already has a new line character
    // toBeReturned.append("\n");
    toBeReturned.append("Date Due: " + std::string(ctime(&dateDue)));
    // toBeReturned.append("\n");
    toBeReturned.append("Completion Percentage: " + std::to_string(getCompletionPercentage()) + "%");
    toBeReturned.append("\n");
    return toBeReturned;
}