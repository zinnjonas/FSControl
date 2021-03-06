/*
 * =====================================================================================
 *
 *       Filename:  test.cpp
 *
 *    Description:  sqllite test
 *
 *        Version:  1.0
 *        Created:  14.06.2013 14:45:29
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>
#include <string>
#include <sqlite3.h>

using namespace std;

int main()
{
       // Als erstes legen wir einen sqlite3-Zeiger an
       sqlite3* Database;
       // und instantiieren ein Objekt von string auf dem Stack
       string Path;
           
        // Danach fragen wir den Benutzer nach dem Pfad zur Datenbankdatei
        cout << "Pfad zur Datenbankdatei: ";
        cin >> Path;
        // Nun können wir die Datenbank öffnen!
        if(sqlite3_open(Path.c_str(), &Database) != SQLITE_OK)
        {
	        // Es ist ein Fehler aufgetreten!
		cout << "Fehler beim Öffnen: " << sqlite3_errmsg(Database) << endl;
	        // Programm beenden
	        return 1;
	}
	// Es hat alles geklappt, die Datenbank wurde geöffnet
	cout << "Datenbank erfolgreich geöffnet!" << endl;
	
	// Jetzt können wir die Datenbank wieder schließen
	sqlite3_close(Database);
	                                                                   
	cout << "Datenbank geschlossen!" << endl;
	                                                              
	// Programm beenden
	return 0;   
}

