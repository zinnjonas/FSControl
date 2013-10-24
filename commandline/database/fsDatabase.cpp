#include "fsDatabase.h"

fsDatabase::fsDatabase() : Database()
{

}

fsDatabase::fsDatabase(string filename) : Database(filename)
{
    open(filename);
}

fsDatabase::~fsDatabase()
{
    close();
}

void fsDatabase::add_user(string matr,string name, string email, int credit)
{
    stringstream command;
    command << "INSERT INTO Students(matr,name,email,credit) VALUES(\""
    << matr
    << "\",\""
    << name
    << "\",\""
    << email
    << "\","
    << credit
    << ");";

    query(command.str());
}

void fsDatabase::add_user(User user)
{
    add_user(user.matr,user.name, user.email, user.credit);
}

void fsDatabase::add_product(string name, string barcode, int price)
{
    stringstream command;
    command << "INSERT INTO Products(name,barcode,price) VALUES(\""
    << name
    <<  "\","
    <<  barcode
    <<  ","
    <<  price
    <<  ");";

    query(command.str());
}

void fsDatabase::add_product(Product product)
{
    add_product(product.name, product.barcode, product.price);
}
