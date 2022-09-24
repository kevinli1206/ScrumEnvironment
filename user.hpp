// represents a generic base class for a user in the TrackingApp system

#ifndef USER_H
#define USER_H

#include <string>
#define MEMBER 0
#define LEAD 1
#define OWNER 2

class User {
    private:
        // username of user for logging in
        std::string userName;
        // a user is one of: member, lead, owner
        int userType;

    public:
        // default constructor
        User() {
            userName = "";
            userType = MEMBER;
        }

        // overloaded constructor
        User(std::string userName, int userType) {
            this->userName = userName;
            this->userType = userType;
        }

        // getters
        std::string getUsername() {
            return userName;
        }
        int getUserType() {
            return userType;
        }

        // setters
        void setUsername(std::string userName) {
            this->userName = userName;
        }
        void setUserType(int userType) {
            this->userType = userType;
        }
};

#endif