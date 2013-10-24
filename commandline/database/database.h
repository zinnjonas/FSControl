#ifndef DATABASE_H_
#define DATABASE_H_

#include <sqlite3.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

class Database
{
    public:

        Database();
        Database(string filename);
        virtual ~Database();

        bool open(string filename);


        vector<vector<string> > query(string query);

        void close();

    protected:

        sqlite3* database;
};

#endif // DATABASE_H_
