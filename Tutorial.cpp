#include <iostream>
#include<string>
#include <list>
#include <iomanip>
using namespace std;

class Customer
{
public:
    string name;
    string address;
    Customer() { }
    Customer(const string name, string address)
    {
        this->name = name;
        this->address = address;
    }

    void setName(string newName) { this->name = newName; }
    string getName() { return this->name; }
    void setAdd(string newAdd) { this->address = newAdd; }
    string getAdd() { return this->address; }

};
class Item
{
private:
    int itemID;
    string itemName;
    double cost;
public:

    Item(const int itID, string itName, double inCost)
        : itemID(itID), itemName(itName), cost(inCost) {}

    int  getItemID() { return this->itemID; }
    string getItemName() { return this->itemName; }
    double getItemCost() { return this->cost; }
    void setItemId(int newID) { this->itemID = newID; }
    void setItemName(int newName) { this->itemName = newName; }
    void setItemCost(double newCost) { this->cost = newCost; }
};
class Order
{
private:
    Customer cust;
    Item item;
public:
    static int orderNumber;
    Order(Customer c, Item i)
        :cust(c), item(i) {}

    Customer getCustomer() { return this->cust; }
    Item getItem() { return this->item; }


};


class Shop {
private:
    static double totalSales;
    static list<Order>orderList;
    static list<Item>itemShelf;
    
    static void setItems() {
        itemShelf.push_back(Item(1001, "Coca-Cola", 2.5));
        itemShelf.push_back(Item(1002, "Fanta", 1.5));
        itemShelf.push_back(Item(1003, "Chocolate", 0.5));
    }
    static string doubleToMoney(double amount)
    {
        int totalPence = static_cast<int>(round(amount * 100));
        int costInPounds = totalPence / 100;
        int costInPence = totalPence % 100;
        string amnt = char(156) + to_string(costInPounds)
            + "." + to_string(costInPence);

        return amnt;
    }
    static void printReceipt(Item& item, double payment, double bal)
    {
        cout << "========================== \n"
            <<"Transaction completed. Reciept: \n"
            <<"=================================\n"
            << "Item bought: " << item.getItemName() << " \n"
            << "Cost of item: " << item.getItemCost() << "\n "
            << "Payment made: " << payment << "\n"
            << "You ballance: " << bal << "\n" 
            <<" Thanks for your patronage. "<< endl;
    }

    static bool confirmPayment(Item& item)
    {
        double userMoney = -1;
        cout << "Please enter the money: ";
        cin >> userMoney;

        while (cin.fail() || userMoney < 0)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Please enter a valid positive money value or enter 0 to exit: ";
            cin >> userMoney;

            if (userMoney == 0)
                return false;
        }

        while (userMoney < item.getItemCost())
        {
            cout << "Insufficient funds to buy " << item.getItemName() << "| the cost is " << item.getItemCost() << endl;
            cout << "Please try again, enter sufficient amount or enter 0 to exit: ";
            cin >> userMoney;

            if (userMoney == 0)
                return false;
        }

        Shop::totalSales += item.getItemCost();
        double customerBal = userMoney - item.getItemCost();
        printReceipt(item, userMoney, customerBal);
        return true;
    }


 public: 
    Shop()
    {
        setItems();
    }

    static void displayItems() {
        int customerDecision = -1;
        cout << "Welcome to imaginary item shop"
            << "see below the list of items we have in stock"
            << endl;

        cout << "===================================" << endl;
        cout << left << setw(10) << "Item ID"
            << setw(20) << "Item"
            << setw(10) << "Cost" << endl;
        cout << "===================================" << endl;
        for (Item& t : itemShelf)
        {
            
            cout << left << setw(10) << t.getItemID()
                << setw(20) << t.getItemName()
                << setw(10) << Shop::doubleToMoney(t.getItemCost())<< endl;
            cout << setfill(' ') << endl;
     
        }
        cout << "Please enter 1 if you want to make an order"
            << "or enter any other key to quit: ";
            
        cin >> customerDecision;
        if (customerDecision == 1)
        {
            if (Shop::makeOrder())
            {
                //ut<<confirmPayment(orderList.back().getItem());
               // cout << orderList.back().getItem().getItemName();
            }
            else
            {
                Shop::displayItems();
            }
        }
        else
        {
            cout << "Thank you for visiting imaginary shop.";
            return;
        }
    }

    static bool makeOrder()
    {
        string name;
        string add;
        int itemID = -1;
        Item* orderedItem = nullptr;
        bool orderResult = false;
        cout << "Please enter the id of item you want to order: ";
        cin >> itemID;

        //While loop test if the cin fails
        while (cin.fail())
        {
            // Clear the failbit
            cin.clear();

            // Ignore any invalid characters in the input buffer
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

        
            cout << "Please enter a valid input for item id: ";
            cin >> itemID;
       }
        for (Item& t : itemShelf)
        {
            if (t.getItemID() == itemID)
            {
                orderedItem = &t;
                orderResult = true;
                break;
            }
        }

        if (!orderResult)
        {
            cout << "Item selected is not in stock!!";
        }
        else
        {
            cout << "Pleae enter your name: ";
            cin >> name;
            cout << "Pleae enter your address: ";
            cin >> add;

            orderList.push_back(Order(Customer(name, add),
                *orderedItem));
          
        }
            
            return orderResult;
    }
    
};

int Order::orderNumber = 0;
list<Order> Shop::orderList;
list<Item> Shop::itemShelf;
double Shop::totalSales = 0;

int main()
{
    
   Shop::Shop();
    Shop::displayItems();
   // cout<< Shop::makeOrder();
    
    

    return 0;
}

