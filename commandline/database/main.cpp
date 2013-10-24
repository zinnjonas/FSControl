#include <iostream>

#include "fsDatabase.h"

using namespace std;

int main()
{

    fsDatabase* db = new fsDatabase("FSControl.db");

    char c = ' ';
    while ( c != 'q')
    {

        string name;
        string matr;
        double owe;
        double credit;

        cout << "gib die matr ein: ";
        cin >> matr;

        cout << "gib den namen ein: ";
        cin >> name;

        cout << "gib die schulden ein: ";
        cin >> owe;

        cout << "gib den credit ein: ";
        cin >> credit;

        db->addUser(matr, name, owe, credit);

        cout << "insert q for quit" << endl;
        cin >> c;
    }

    vector<vector<string> > result = db->query("SELECT matr FROM Students;");

    for(vector<vector<string> >::iterator it = result.begin(); it < result.end(); ++it)
    {
        vector<string> row = *it;
        cout << "Values: " << row.at(0)<< endl;
    }
    db->close();

    return 0;
}
