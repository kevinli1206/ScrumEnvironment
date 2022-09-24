// definitions for container.hpp
#include "container.hpp"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <istream>
using namespace std;

// write project information to a file
void Container::saveProject()
{

    // the file to write to
    ofstream file("project.txt");

    // add the project name
    file << currentProject->toString() << endl;

    // users
    file << "USERS" << endl;

    // user info
    for (auto user : users)
    {
        file << "USER" << endl;
        file << "Name: " << user->getUsername() << endl;
        file << "Type: " << user->getUserType() << endl;
    }

    file << "Current User: " << currentUser->getUsername() << endl;

    // close the file
    file.close();
}

void Container::loadProject()
{
    cout << "HELLOP" << endl;
    ifstream file("project.txt");

    string name;
    getline(file, name);
    name = name.substr(name.find("Name: ") + 6);
    vector<Issue *> toDo;
    string nextString;
    getline(file, nextString);
    getline(file, nextString);
    if (nextString == "ISSUE")
    {
        string curr;
        int i, p;
        string t;
        time_t a, b;
        while (getline(file, curr) && curr != "In Progress")
        {
            if (curr.substr(0, 2) == "ID")
            {
                i = stoi(curr.substr(3));
            }
            else if (curr.substr(0, 4) == "Type")
            {
                t = curr.substr(6);
            }
            else if (curr.substr(0, 8) == "Priority")
            {
                p = stoi(curr.substr(9));
            }
            else if (curr.substr(0, 6) == "Date C")
            {
                a = time(0);
            }
            else if (curr.substr(0, 6) == "Date D")
            {
                b = time(0) + 100;
            }
            else if (curr.substr(0, 5) == "ISSUE")
            {
                toDo.push_back(new Issue(i, t, p, a, b));
            }
        }
        Issue *is = new Issue(i, t, p, a, b);
        toDo.push_back(is);
    }
    vector<Sprint *> s;
    getline(file, nextString);
    if (nextString == "SPRINT")
    {
        string curr;
        time_t a;
        int d;
        vector<Issue *> is;
        while (getline(file, curr) && curr != "Work Done")
        {
            if (curr.substr(0, 6) == "Date C")
            {
                a = time(0);
            }
            else if (curr.substr(0, 8) == "Deadline")
            {
                d = stoi(curr.substr(10));
            }
            else if (curr.substr(0, 6) == "Issues")
            {
                getline(file, curr);
                if (nextString == "ISSUE")
                {
                    string curr;
                    int i, p;
                    string t;
                    time_t a, b;
                    while (getline(file, curr) && curr.substr(0, 6) != "Status")
                    {
                        if (curr.substr(0, 2) == "ID")
                        {
                            i = stoi(curr.substr(3));
                        }
                        else if (curr.substr(0, 4) == "Type")
                        {
                            t = curr.substr(6);
                        }
                        else if (curr.substr(0, 8) == "Priority")
                        {
                            p = stoi(curr.substr(9));
                        }
                        else if (curr.substr(0, 6) == "Date C")
                        {
                            a = time(0);
                        }
                        else if (curr.substr(0, 6) == "Date D")
                        {
                            b = time(0) + 100;
                        }
                        else if (curr.substr(0, 5) == "ISSUE")
                        {
                            is.push_back(new Issue(i, t, p, a, b));
                        }
                    }
                    is.push_back(new Issue(i, t, p, a, b));
                }
            }
        }
        s.push_back(new Sprint(d, is, a));
        nextString = curr;
    }
    vector<Issue *> done;
    if (nextString == "Work Done")
    {
        string curr;
        int i, p;
        string t;
        time_t a, b;
        while (getline(file, curr) && curr != "USERS")
        {
            if (curr.substr(0, 2) == "ID")
            {
                i = stoi(curr.substr(3));
            }
            else if (curr.substr(0, 4) == "Type")
            {
                t = curr.substr(6);
            }
            else if (curr.substr(0, 8) == "Priority")
            {
                p = stoi(curr.substr(9));
            }
            else if (curr.substr(0, 6) == "Date C")
            {
                a = time(0);
            }
            else if (curr.substr(0, 6) == "Date D")
            {
                b = time(0) + 100;
            }
            else if (curr.substr(0, 5) == "ISSUE")
            {
                done.push_back(new Issue(i, t, p, a, b));
            }
        }
        done.push_back(new Issue(i, t, p, a, b));
        nextString = curr;
    }
    vector<User *> u;
    if (nextString == "USERS")
    {
        string curr;
        getline(file, curr);
        int i;
        string n;
        while (getline(file, curr))
        {
            if (curr.substr(0, 4) == "Name")
            {
                n = curr.substr(6);
            }
            else if (curr.substr(0, 4) == "Type")
            {
                i = stoi(curr.substr(6));
            }
            else if (curr.substr(0, 5) == "USER")
            {
                u.push_back(new User(n, i));
            }
        }
        u.push_back(new User(n, i));
    }
    cout << "HELLO" << endl;
    this->currentProject = new Project(name, toDo, s, done, u);
    this->users = u;
    //delete this->currentUser;
    this->currentUser = this->users.at(0);
}

// determines if a username exists in the container
bool Container::containsUsername(string userName)
{
    bool usernameExists = false;
    for (auto user : users)
    {
        if (user->getUsername() == userName)
        {
            usernameExists = true;
            break;
        }
    }
    return usernameExists;
}

// retrieves a user in the container, assume the username passed is in system
User *Container::retrieveUser(std::string userName)
{
    for (auto user : users)
    {
        if (user->getUsername() == userName)
        {
            return user;
        }
    }
    // this point should never be reached
    return nullptr;
}

// adds a user to the project
void Container::addUser()
{
    string userName;

    // members cannot add users, must also be signed in
    if (currentUser->getUsername() == "")
    {
        cout << "Invalid action. Not signed in." << endl;
        return;
    }
    if (currentUser->getUserType() == MEMBER)
    {
        cout << "Members are not allowed to add users." << endl;
        return;
    }

    // valid username check
    while (true)
    {
        cout << "Enter username: ";
        getline(cin, userName);

        // check if username already exists in the system
        bool usernameExists = containsUsername(userName);
        if (!usernameExists)
        {
            break;
        }
        else
        {
            cout << "Username already taken, please try another username." << endl;
        }
    }

    string role;
    // valid role check
    while (true)
    {
        cout << "Enter user's role (Member, Lead, Owner): ";
        getline(cin, role);
        if ((role == "Member") || (role == "Lead") || (role == "Owner"))
        {
            // additional check: only one owner can exist
            bool owner_assigned = false;
            for (auto user : users)
            {
                if (user->getUserType() == OWNER)
                {
                    owner_assigned = true;
                    break;
                }
            }
            if ((owner_assigned) && (role == "Owner"))
            {
                cout << "Owner already exists. Please assign a different role." << endl;
            }
            else
            {
                break;
            }
        }
        else
        {
            cout << "Invalid role, please try again." << endl;
        }
    }

    // add user to list of users
    if (role == "Member")
    {
        User *user = new User(userName, MEMBER);
        users.push_back(user);
        currentProject->addCollaborator(user);
    }
    else if (role == "Lead")
    {
        User *user = new User(userName, LEAD);
        users.push_back(user);
        currentProject->addCollaborator(user);
    }
    else
    {
        User *user = new User(userName, OWNER);
        users.push_back(user);
        currentProject->addCollaborator(user);
    }

    cout << role << " " << userName << " successfully added." << endl;
}

// signs a user in, if client not signed in already
void Container::signIn()
{
    // first check if user is already signed in
    if (currentUser->getUsername() != "")
    {
        cout << "Already signed in as: " << currentUser->getUsername() << endl;
    }
    // basic signin, just enter username
    else
    {
        bool userExists;
        string username;

        cout << "Enter username to login: ";
        getline(cin, username);
        userExists = containsUsername(username);
        // if user exists then login
        if (userExists)
        {
            cout << "Logged in as: " << username << endl;
            delete currentUser;
            currentUser = retrieveUser(username);
        }
        else
        {
            cout << "The username " << username << " does not exist in the system, please try again." << endl;
        }
    }
}

// show all users
void Container::displayUsers()
{
    cout << "All users:" << endl;
    for (auto user : users)
    {
        if (user->getUserType() == MEMBER)
        {
            cout << user->getUsername() << " (Member)" << endl;
        }
        else if (user->getUserType() == LEAD)
        {
            cout << user->getUsername() << " (Lead)" << endl;
        }
        else
        {
            cout << user->getUsername() << " (Owner)" << endl;
        }
    }
    cout << endl;
}

// changes users
void Container::changeUser()
{
    string username;
    while (true)
    {
        displayUsers();

        cout << "Enter username of user to change to: ";
        getline(cin, username);
        // check if username already exists in the system
        bool userExists = containsUsername(username);
        if (userExists)
        {
            delete currentUser;
            currentUser = retrieveUser(username);
            cout << "Changed user to " << currentUser->getUsername() << "." << endl;
            break;
        }
        else
        {
            cout << "The username " << username << " does not exist in the system, please try again." << endl;
        }
    }
}

// updates properties of a user
void Container::updateUser()
{
    // members cannot update users, must also be signed in
    if (currentUser->getUsername() == "")
    {
        cout << "Invalid action. Not signed in." << endl;
        return;
    }
    if (currentUser->getUserType() == MEMBER)
    {
        cout << "Members are not allowed to update users." << endl;
        return;
    }

    string username;
    User *updateUser;
    while (true)
    {
        cout << "Enter username of user to update: ";
        getline(cin, username);
        // check if username already exists in the system
        bool userExists = containsUsername(username);
        if (userExists)
        {
            updateUser = retrieveUser(username);
            cout << "The user " << updateUser->getUsername() << " will be updated." << endl;
            break;
        }
        else
        {
            cout << "The username " << username << " does not exist in the system, please try again." << endl;
        }
    }
    // valid username check
    string newName;
    while (true)
    {
        cout << "Enter new username: ";
        getline(cin, newName);

        // check if username already exists in the system
        bool validUsername = !containsUsername(newName);
        if (validUsername)
        {
            updateUser->setUsername(newName);

            break;
        }
        else
        {
            cout << "Username already taken, please try another username." << endl;
        }
    }
    string newRole;

    // valid role check
    while (true)
    {
        cout << "Enter new role (Member, Lead, Owner): ";
        getline(cin, newRole);
        if ((newRole == "Member") || (newRole == "Lead") || (newRole == "Owner"))
        {
            // additional check: only one owner can exist
            bool owner_assigned = false;
            for (auto user : users)
            {
                if (user->getUserType() == OWNER)
                {
                    owner_assigned = true;
                    break;
                }
            }
            if ((owner_assigned) && (newRole == "Owner"))
            {
                cout << "Owner already exists. Please assign a different role." << endl;
            }
            else
            {
                break;
            }
        }
        else
        {
            cout << "Invalid role, please try again." << endl;
        }
    }

    // updates user role
    if (newRole == "Member")
    {
        updateUser->setUserType(MEMBER);
    }
    else if (newRole == "Lead")
    {
        updateUser->setUserType(LEAD);
    }
    else
    {
        updateUser->setUserType(OWNER);
    }

    currentProject->updateCollaborator(username, newName, newRole);

    cout << "Updated to user " << newName << " with role " << newRole << endl;
}

// removes a user from the project
void Container::removeUser()
{
    // members cannot remove users, must also be signed in
    if (currentUser->getUsername() == "")
    {
        cout << "Invalid action. Not signed in." << endl;
        return;
    }
    if (currentUser->getUserType() == MEMBER)
    {
        cout << "Members are not allowed to remove users." << endl;
        return;
    }

    string username;
    User *removeUser;
    while (true)
    {
        cout << "Enter username of user to remove: ";
        getline(cin, username);
        // check if username already exists in the system
        bool userExists = containsUsername(username);
        if (userExists)
        {
            removeUser = retrieveUser(username);
            users.erase(remove(users.begin(), users.end(), removeUser), users.end());
            currentProject->removeCollaborator(removeUser);
            cout << "The user " << removeUser->getUsername() << " is removed." << endl;
            break;
        }
        else
        {
            cout << "The username " << username << " does not exist in the system, please try again." << endl;
        }
    }
}

// views details of the project
void Container::viewProject()
{
    currentProject->displayProject();
}

// views a specific area of the project (To Do, In Progress, Work Done)
void Container::viewArea()
{
    string area;
    while (true)
    {
        cout << "Enter specific area (To Do, In Progress, Work Done): ";
        getline(cin, area);
        if (area == "To Do")
        {
            vector<Issue *> toDo = currentProject->getToDo();
            for (auto issue : toDo)
                issue->displayIssue();
            break;
        }
        else if (area == "In Progress")
        {
            vector<Sprint *> inProgress = currentProject->getInProgress();
            for (auto sprint : inProgress)
                sprint->displaySprint();
            break;
        }
        else if (area == "Work Done")
        {
            vector<Issue *> workDone = currentProject->getWorkDone();
            for (auto issue : workDone)
                issue->displayIssue();
            break;
        }
        else
        {
            cout << "Invalid area, please try again." << endl;
        }
    }
}

// creates a new issue
void Container::createIssue()
{
    Issue *i = new Issue();

    // assign unique ID
    string ID;
    while (true)
    {
        cout << "Enter ID: ";
        getline(cin, ID);
        try
        {
            int id = stoi(ID);
            i->setID(id);

            bool id_exists = false;
            // check if ID already exists
            for (auto issue : currentProject->getToDo())
            {
                if (issue->getId() == id)
                {
                    id_exists = true;
                }
            }

            for (auto sprint : currentProject->getInProgress())
            {
                for (auto issue : sprint->getIssues())
                {
                    if (issue->getId() == id)
                    {
                        id_exists = true;
                    }
                }
            }

            if (id_exists)
            {
                cout << "ID already exists, please try again." << endl;
            }
            else
            {
                break;
            }
        }
        catch (invalid_argument &e)
        {
            cout << "Invalid ID, please try again." << endl;
        }
    }

    // assign type
    string type;
    cout << "Enter type: ";
    getline(cin, type);
    i->setType(type);

    // assign priority
    string str_prio;
    int priority;
    while (true)
    {
        cout << "Enter priority (numerical scale): ";
        getline(cin, str_prio);

        try
        {
            priority = stoi(str_prio);
            if (priority < 0)
            {
                cout << "Cannot have negative priority, please try again." << endl;
            }
            else
            {
                i->setPriority(priority);
                break;
            }
        }
        catch (invalid_argument &e)
        {
            cout << "Invalid priority, please try again." << endl;
        }
    }

    // assign date due
    string str_date;
    int dateDue;
    while (true)
    {
        cout << "Enter deadline (in seconds): ";
        getline(cin, str_date);

        try
        {
            dateDue = stoi(str_date);
            if (dateDue < 0)
            {
                cout << "Cannot have negative deadline, please try again." << endl;
            }
            else
            {
                i->setDateDue(i->getDateCreated() + dateDue);
                break;
            }
        }
        catch (invalid_argument &e)
        {
            cout << "Invalid deadline, please try again." << endl;
        }
    }

    // adds issue to current project
    cout << "Created ISSUE " << i->getId() << endl;
    currentProject->addIssue(i);
}

// updates an existing issue
void Container::updateIssue()
{
    // display current issues for user to select
    currentProject->displayIssueID();

    // prompt user to select an issue by ID
    string inputID;
    while (true)
    {
        cout << "Enter the ID of the issue to update: ";
        getline(cin, inputID);
        try
        {
            Issue *i = currentProject->getIssue(stoi(inputID));

            // check if issue actually exists
            if (i != nullptr)
            {
                // assign type
                string type;
                cout << "Enter type: ";
                getline(cin, type);
                i->setType(type);

                // assign priority
                string str_prio;
                int priority;
                while (true)
                {
                    cout << "Enter priority (numerical scale): ";
                    getline(cin, str_prio);

                    try
                    {
                        priority = stoi(str_prio);
                        if (priority < 0)
                        {
                            cout << "Cannot have negative priority, please try again." << endl;
                        }
                        else
                        {
                            i->setPriority(priority);
                            return;
                        }
                    }
                    catch (invalid_argument &e)
                    {
                        cout << "Invalid priority, please try again." << endl;
                    }
                }
            }
            else
            {
                cout << "Issue with ID " << inputID << " does not exist." << endl;
            }
        }
        catch (invalid_argument &e)
        {
            cout << "Invalid ID, please try again." << endl;
        }
    }
}

// moves an existing issue
void Container::moveIssue()
{
    // display current issues for user to select
    currentProject->displayIssueID();

    // prompt user to select an issue by ID
    string inputID;
    while (true)
    {
        cout << "Enter the ID of the issue to move: ";
        getline(cin, inputID);
        try
        {
            Issue *i = currentProject->getIssue(stoi(inputID));
            if (i != nullptr)
            {
                currentProject->moveIssue(stoi(inputID));
                return;
            }
            else
            {
                cout << "Issue with ID " << inputID << " does not exist." << endl;
            }
        }
        catch (invalid_argument &e)
        {
            cout << "Invalid input ID, please try again." << endl;
        }
    }
}

// deletes an existing issue
void Container::deleteIssue()
{
    // display current issues for user to select
    currentProject->displayIssueID();

    // prompt user to select an issue by ID
    string inputID;
    while (true)
    {
        cout << "Enter the ID of the issue to delete: ";
        getline(cin, inputID);
        try
        {
            Issue *i = currentProject->getIssue(stoi(inputID));
            if (i != nullptr)
            {
                currentProject->deleteIssue(stoi(inputID));
                break;
            }
            else
            {
                cout << "Issue with ID " << inputID << " does not exist." << endl;
            }
        }
        catch (invalid_argument &e)
        {
            cout << "Invalid input ID, please try again." << endl;
        }
    }
}

// creates the project
void Container::createProject()
{

    // project name entry
    string name;
    cout << "Enter the name of the project: ";
    getline(cin, name);
    currentProject->setName(name);

    // owner initializes the project
    string ownerName;
    cout << "Enter your username as the owner of this project: ";
    getline(cin, ownerName);
    User *owner = new User(ownerName, OWNER);
    users.push_back(owner);

    cout << "Welcome " << ownerName << "." << endl;
    // login as the owner
    delete currentUser;
    currentUser = owner;
}

// deletes the project
void Container::deleteProject()
{
    if (currentUser->getUserType() == OWNER)
    {
        cout << "Deleting Project " << currentProject->getName() << endl;
        delete currentProject;
    }
}

// updates properties of the project
void Container::updateProject()
{
    // members cannot update project, must also be signed in
    if (currentUser->getUsername() == "")
    {
        cout << "Invalid action. Not signed in." << endl;
        return;
    }
    if (currentUser->getUserType() == MEMBER)
    {
        cout << "Members are not allowed to update projects." << endl;
        return;
    }
    // project name entry
    string name;
    cout << "Enter the new name of the project: ";
    getline(cin, name);
    currentProject->setName(name);
}

// creates a new sprint
void Container::createSprint()
{
    // members cannot create sprint, must also be signed in
    if (currentUser->getUsername() == "")
    {
        cout << "Invalid action. Not signed in." << endl;
        return;
    }
    if (currentUser->getUserType() == MEMBER)
    {
        cout << "Members are not allowed to create sprints." << endl;
        return;
    }

    Sprint *s = new Sprint();
    // assign date due
    int deadline;
    cout << "Enter deadline (in seconds): ";
    cin >> deadline;
    cin.ignore();
    s->setDeadline(deadline);
    // adds issue to current project
    cout << "Created SPRINT " << endl;
    currentProject->addSprint(s);
}

// updates an existing sprint
void Container::updateSprint()
{
    // members cannot update sprint, must also be signed in
    if (currentUser->getUsername() == "")
    {
        cout << "Invalid action. Not signed in." << endl;
        return;
    }
    if (currentUser->getUserType() == MEMBER)
    {
        cout << "Members are not allowed to create sprints." << endl;
        return;
    }

    /* // update deadline
    int deadline;
    cout << "Enter new deadline (in seconds): ";
    cin >> deadline;
    cin.ignore();
    s->setDeadline(deadline); */
    Sprint *s = currentProject->getInProgress().at(0);

    if (s->isFinished())
    {
        vector<Issue *> issues = s->getIssues();
        for (auto i : issues)
        {
            // if issue is not completed
            if (i->getDateDue() >= time(0))
            {
                // remove from In Progress
                issues.erase(remove(issues.begin(), issues.end(), i), issues.end());
                // add to To Do
                currentProject->getToDo().push_back(i);
            }
            else
            {
                // remove from In Progress
                issues.erase(remove(issues.begin(), issues.end(), i), issues.end());
                // add to To Do
                currentProject->getWorkDone().push_back(i);
            }
        }
    }
}