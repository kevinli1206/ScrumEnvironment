#include "sprint.hpp"
#include <iostream>

// Sprint constructor
Sprint::Sprint() {
    this->dateCreated = time(0);
}

// Sprint constructor
Sprint::Sprint(int d, std::vector<Issue*> i, time_t t) : deadline(d), issues(i), dateCreated(t) {
}

// Spring destructor
Sprint::~Sprint() {
    delete[] this;
}

// get the deadline of a sprint
int Sprint::getDeadline() {
    return this->deadline;
}

// get the date created of a sprint
time_t Sprint::getDateCreated() {
    return this->dateCreated;
}

// get the issues of a sprint
std::vector<Issue*> Sprint::getIssues() {
    return this->issues;
}

// set the deadline of a sprint
void Sprint::setDeadline(int d) {
    this->deadline = d;
}

// set the deadline of a sprint
void Sprint::setIssues(std::vector<Issue*> i) {
    this->issues = i;
}

// set the deadline of a sprint
void Sprint::setDateCreated(time_t dc) {
    this->dateCreated = dc;
}

// add an issue to the sprint
void Sprint::addIssue(Issue* i) {
    this->issues.push_back(i);
}

// removes an issue from a sprint
void Sprint::removeIssue(Issue* i) {
    issues.erase(remove(issues.begin(), issues.end(), i), issues.end());
}

// check to see if the current sprint is finished
bool Sprint::isFinished() {
    return time(0) >= this->dateCreated + deadline;
}

// display information about a Sprint
void Sprint::displaySprint() {
    std::cout << toString() << std::endl;
}

std::string Sprint::toString() {
    std::string toBeReturned = "SPRINT\n";
    toBeReturned.append("Date Created: " + std::to_string(dateCreated));
    toBeReturned.append("\n");
    toBeReturned.append("Deadline: " + std::to_string(deadline));
    toBeReturned.append("\n");
    toBeReturned.append("Issues: ");
    toBeReturned.append("\n");
    for (int i = 0; i < issues.size(); i++) {
        toBeReturned.append(issues.at(i)->toString());
    }
    std::string status;
    if (isFinished()) {
        status = "Finished";
    }
    else {
        status = "In-Progress";
    }
    toBeReturned.append("Status: " + status);
    toBeReturned.append("\n");
    return toBeReturned;
}
