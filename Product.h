//
// Created by Jokarc on 2021/5/25.
//

#ifndef USERANDPRODUCT_TEST_PRODUCT_H
#define USERANDPRODUCT_TEST_PRODUCT_H
#include "User.h"
class Product {
protected:
    bool isDiscount;
    int num;
    double price;
    double discount;
    string name;
    string productDescription;
    string owner;

public:
    virtual double getPrice(){
        return 0;
    }
    bool IsDiscount() {return isDiscount;}
    string ShowProductDescription() {return productDescription;}
    string ShowOwner() {return owner;}
    string ShowName() {return name;}
    int ShowNum() {return num;}
    int productResNum() {return num;}
    void setInfo(string name_, double price_, int num_, double discount_, string productDescription_, string owner_) {
        name = name_;
        price = price_;
        num = num_;
        productDescription = productDescription_;
        owner = owner_;
    }
    bool operator<(const Product& y) const {
        return price < y.price;
    }
};
class Book:public Product {
public:
    virtual double getPrice(){
        return price;
    }
};
class Clothes:public Product {
public:
    virtual double getPrice(){
        return price;
    }
};
class Food:public Product {
public:
    virtual double getPrice(){
        return price;
    }
};
#endif //USERANDPRODUCT_TEST_PRODUCT_H
