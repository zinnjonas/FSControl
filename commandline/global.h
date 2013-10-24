#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <string>

using namespace std;

struct user_s{
    int id;
    string name;
    string matr;
    string email;
    int credit;
};

typedef struct user_s User;

struct product_s{
    int id;
    string name;
    string barcode;
    int price;
};

typedef struct product_s Product;

#endif // GLOBAL_H_

