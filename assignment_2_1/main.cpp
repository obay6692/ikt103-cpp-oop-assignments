#include <iostream>
#include <algorithm>
#include <stdint.h>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

struct customer{
    uint32_t id;
    string name;
    string address;
};

struct product{
    uint32_t id;
    string name;
    uint32_t price;
};

struct order{
    uint32_t id;
    uint32_t customer_id;
    uint32_t product_id;
    uint32_t amount;
};

class DataReader{
public:
    vector<customer> getCustomers();
    vector<product> getProducts();
    vector<order> getOrders();
    uint32_t amountOrderedPerProduct(uint32_t product_id);
    uint32_t moneySpentPerCustomer(uint32_t customer_id);
    uint32_t moneySpentPerProduct(uint32_t product_id);
private:
    vector<customer> customers;
    string customer_file = "customers.csv";
    vector<product> products;
    string product_file = "products.csv";
    vector<order> orders;
    string order_file = "orders.csv";
};

vector<customer> DataReader::getCustomers(){
    ifstream file(customer_file);
    string line;
    getline(file, line);
    while(getline(file, line)){
        line.erase(std::remove(line.begin(), line.end(), '\"'), line.end());
        customer c;
        stringstream ss(line);
        string id, name, address;
        getline(ss, id, ',');
        c.id = stoi(id);
        getline(ss, name, ',');
        c.name = name;
        getline(ss, address, ',');
        c.address = address;
        customers.push_back(c);
    }
    return customers;
}

vector<product> DataReader::getProducts(){
    ifstream file(product_file);
    string line;
    getline(file, line);
    while(getline(file, line)){
        line.erase(remove(line.begin(), line.end(), '\"'), line.end());
        product p;
        stringstream ss(line);
        string id, name, price;
        getline(ss, id, ',');
        p.id = stoi(id);
        getline(ss, name, ',');
        p.name = name;
        getline(ss, price, ',');
        p.price = stoi(price);
        products.push_back(p);
    }
    return products;
}

vector<order> DataReader::getOrders(){
    ifstream file(order_file);
    string line;
    getline(file, line);
    while(getline(file, line)){
        order o;
        line.erase(remove(line.begin(), line.end(), '\"'), line.end());
        stringstream ss(line);
        string id, customer_id, product_id, amount;
        getline(ss, id, ',');
        o.id = stoi(id);
        getline(ss, customer_id, ',');
        o.customer_id = stoi(customer_id);
        getline(ss, product_id, ',');
        o.product_id = stoi(product_id);
        getline(ss, amount, ',');
        o.amount = stoi(amount);
        orders.push_back(o);
    }
    return orders;
}

uint32_t DataReader::amountOrderedPerProduct(uint32_t product_id){
    uint32_t amount = 0;
    for(int i = 0; i < orders.size(); i++){
        if(orders[i].product_id == product_id){
            amount += orders[i].amount;
        }
    }
    return amount;
}

uint32_t DataReader::moneySpentPerCustomer(uint32_t customer_id){
    uint32_t money = 0;
    for(int i = 0; i < orders.size(); i++){
        if(orders[i].customer_id == customer_id){
            for(int j = 0; j < products.size(); j++){
                if(orders[i].product_id == products[j].id){
                    money += orders[i].amount * products[j].price;
                }
            }
        }
    }
    return money;
}

uint32_t DataReader::moneySpentPerProduct(uint32_t product_id){
    uint32_t money = 0;
    for(int i = 0; i < orders.size(); i++){
        if(orders[i].product_id == product_id){
            for(int j = 0; j < products.size(); j++){
                if(orders[i].product_id == products[j].id){
                    money += orders[i].amount * products[j].price;
                }
            }
        }
    }
    return money;
}

int main(){
    DataReader dr;
    // Get customers
    vector<customer> customers = dr.getCustomers();
    // Get products
    vector<product> products = dr.getProducts();
    // Get orders
    vector<order> orders = dr.getOrders();

    // Print customers
    for(int i = 0; i < customers.size(); i++){
        cout << "Customer: " << customers[i].name << ", " << customers[i].address << endl;
    }

    // Print products
    for(int i = 0; i < products.size(); i++){
        cout << "Product: " << products[i].name << ", " << products[i].price << endl;
    }

    // total amount ordered per product
    for(int i = 0; i < products.size(); i++){
        cout << products[i].name << " amount: " << dr.amountOrderedPerProduct(products[i].id) << endl;
    }

    // total money spent per product
    for(int i = 0; i < products.size(); i++){
        cout << products[i].name << " gross income: " << dr.moneySpentPerProduct(products[i].id) << endl;
    }

    // total money spent per customer
    for(int i = 0; i < customers.size(); i++){
        cout << customers[i].name << " money spent: " << dr.moneySpentPerCustomer(customers[i].id) << endl;
    }

    return 0;
}