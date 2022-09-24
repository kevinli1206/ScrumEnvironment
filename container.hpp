// represents a container that holds all user info for a single project
// also handles retrieving information and updating the tracking app

#ifndef CONTAINER_H
#define CONTAINER_H

#include "user.hpp"
#include "project.hpp"
#include "sprint.hpp"
#include "issue.hpp"
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <istream>
#include <algorithm>

class Container
{
private:
    // the project this container keeps track of
    Project *currentProject;

    // users in this project
    std::vector<User *> users;

    // current user (which user is currently logged in)
    User *currentUser;

public:
    // default constructor
    Container()
    {
        currentProject = new Project();
        currentUser = new User();
    }

    // overloaded constructor
    Container(Project* currentProject, std::vector<User *> users, User *currentUser)
    {
        this->currentProject = currentProject;
        this->users = users;
        this->currentUser = currentUser;
    }

    // destructor
    ~Container()
    {
        delete currentProject;
        users.clear();
        delete currentUser;
    }

    // getters
    std::vector<User *> getUsers()
    {
        return users;
    }

    User *getCurrentUser()
    {
        return currentUser;
    }

    Project *getCurrentProject() 
    {
        return currentProject;
    }

    // setters
    void setUsers(std::vector<User *> users)
    {
        this->users = users;
    }

    void setCurrentUser(User *currentUser)
    {
        this->currentUser = currentUser;
    }

    // saves the current state of the project to file
    void saveProject();

    // loads a project from file
    void loadProject();

    // determines if a username exists in the container
    bool containsUsername(std::string userName);

    // retrieves a user in the container
    User *retrieveUser(std::string userName);

    // adds a user to the project
    void addUser();

    // signs a user in, if client not signed in already
    void signIn();

    // show all users
    void displayUsers();

    // changes users
    void changeUser();

    // updates properties of a user
    void updateUser();

    // removes a user from the project
    void removeUser();

    // views details of the project
    void viewProject();

    // views a specific area of the project (To Do, In Progress, Work Done)
    void viewArea();

    // creates a new issue
    void createIssue();

    // updates an existing issue
    void updateIssue();

    // moves an existing issue
    void moveIssue();

    // deletes an existing issue
    void deleteIssue();

    // creates the project
    void createProject();

    // deletes the project
    void deleteProject();

    // updates properties of the project
    void updateProject();

    // creates a new sprint
    void createSprint();

    // updates an existing sprint
    void updateSprint();
};

#endif
