#ifndef FSDATABASE_H_
#define FSDATABASE_H_

#include "database.h"
#include "global.h"
#include <sstream>
#include <iomanip>

class fsDatabase : public Database
{
    public:

        fsDatabase();
        fsDatabase(string filename);
        virtual ~fsDatabase();

        void add_user(string matr,string name = "", string email = "",int credit = 0);
        void add_user(User user);
        void add_product(string name, string barcode, int price);
        void add_product(Product product);

};


#endif // FSDATABASE_H_
