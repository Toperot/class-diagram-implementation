#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <sstream>

using namespace std;

//coded by Kristoffer Ludovice

const int MAX_PRODUCTS = 100;
const int MAX_CART_ITEMS = 100;
const int MAX_ORDERS = 100;

class Product {
public:
    int productID;
    string name;
    float price;

    Product(int id = 0, string n = "", float p = 0.0) : productID(id), name(n), price(p) {}

    float getPrice() const 
	{
        return price;
    }
};

class ShoppingCart {
private:
    Product products[MAX_CART_ITEMS];
    int quantities[MAX_CART_ITEMS];
    int itemCount;

public:
    ShoppingCart() : itemCount(0) {}

    void addProduct(const Product& product, int quantity) 
	{
        for (int i = 0; i < itemCount; ++i) 
		{
            if (products[i].productID == product.productID) 
			{
                quantities[i] += quantity;
                return;
            }
        }
        if (itemCount < MAX_CART_ITEMS) 
		{
            products[itemCount] = product;
            quantities[itemCount] = quantity;
            itemCount++;
        }
		else 
		{
            cout << "Cart is full, cannot add more items.\n";
        }
    }

    float getTotalPrice() const 
	{
        float total = 0.0;
        for (int i = 0; i < itemCount; ++i) 
		{
            total += products[i].getPrice() * quantities[i];
        }
        return total;
    }

    void displayItems() const 
	{
        if (itemCount == 0) 
		{
            cout << "Your shopping cart is empty.\n";
            return;
        }
        cout << left << setw(12) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << setw(10) << "Quantity" << endl;
        cout << "--------------------------------------------------------\n";
        for (int i = 0; i < itemCount; ++i) 
		{
            cout << left << setw(12) << products[i].productID
                 << setw(20) << products[i].name
                 << setw(9) << fixed << setprecision(2) << products[i].price
                 << setw(10) << quantities[i] << endl;
        }
    }

    void clearCart() 
	{
        itemCount = 0;
    }

	string getCartDetails() const 
	{
	    ostringstream oss;
	    for (int i = 0; i < itemCount; ++i) 
		{
	        oss << left << setw(12) << to_string(products[i].productID) 
	            << setw(20) << products[i].name 
	            << setw(9) << fixed << setprecision(2) << products[i].price
	            << setw(10) << to_string(quantities[i]) << "\n";
	    }
	    return oss.str();
	}



};

class Order {
public:
    int orderID;
    string status;
    float totalAmount;
    string orderDetails;

    Order(int id = 0, string s = "", float amount = 0.0, string details = "") 
        : orderID(id), status(s), totalAmount(amount), orderDetails(details) {}

    void displayOrder() const 
	{
        cout << "Order ID: " << orderID << ", Status: " << status << ", Total Amount: ₱" << totalAmount << endl;
    }

    string getOrderSummary() const 
	{
        return "Order ID: " + to_string(orderID) + ", Total Amount: " + to_string(totalAmount) + "\nDetails:\n" + orderDetails;
    }
};

Product products[MAX_PRODUCTS];
int productCount;
Order orders[MAX_ORDERS];
int orderCount = 0;

void initializeProducts() 
{
    products[0] = Product(1, "Green Tea", 55.00);
    products[1] = Product(2, "Chocolates", 199.99);
    products[2] = Product(3, "Candles", 39.99);
    products[3] = Product(4, "Cooking Oil", 99.99);
    products[4] = Product(5, "Ceramic Mug", 159.99);
    products[5] = Product(6, "Protien Powder", 99.99);
    products[6] = Product(7, "Face Cleanser", 249.99);
    products[7] = Product(8, "Eco Bag", 69.99);
    products[8] = Product(9, "Coffee", 89.99);
    products[9] = Product(10, "Vicks Inhaler", 129.99);
    productCount = 10;
}

void displayProducts() 
{
    cout << left << setw(12) << "Product ID" << setw(20) << "Name" << setw(10) << "Price" << endl;
    cout << "--------------------------------------------\n";
    for (int i = 0; i < productCount; ++i) 
	{
        cout << left << setw(12) << products[i].productID
             << setw(20) << products[i].name
             << fixed << setprecision(2) << setw(9) << products[i].price << endl;
    }
}

void viewProducts(ShoppingCart& cart) 
{
    char choice = 'y';
    while (choice == 'y') 
	{
        displayProducts();

        int id;
        cout << "Enter the ID of the product you want to add to the shopping cart: ";
        while (!(cin >> id) || id <= 0)
		{
            cout << "Invalid input. Please enter a positive integer for the product ID: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        int qty;
        cout << "Enter quantity: ";
        while (!(cin >> qty) || qty <= 0) 
		{
            cout << "Invalid input. Please enter a positive integer for the quantity: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        bool found = false;
        for (int i = 0; i < productCount; ++i) 
		{
            if (products[i].productID == id) 
			{
                cart.addProduct(products[i], qty);
                cout << "Product added successfully!\n";
                cout << endl;
                found = true;
                break;
            }
        }
        if (!found) 
		{
            cout << "Product not found!\n";
        }

        cout << "Do you want to add another product? (y/n): ";
        cin >> choice;
        cout << endl << endl;
        while (choice != 'y' && choice != 'n') 
		{
            cout << "Invalid choice. Please enter 'y' to continue or 'n' to exit: ";
            cin >> choice;
        }
    }
}


void viewShoppingCart(ShoppingCart& cart) 
{
    cart.displayItems();
    cout << "\nDo you want to check out all the products? (Y/N): ";
    char choice;
    cin >> choice;
    if (choice == 'Y' || choice == 'y') 
	{
        cout << "You have successfully checked out the products!\n";
        float total = cart.getTotalPrice();
        cout << "Total Amount: $" << fixed << setprecision(2) << total << endl;
		cout << endl;
		
        if (orderCount < MAX_ORDERS) 
		{
            static int orderID = 1;
            string orderDetails = cart.getCartDetails();
            orders[orderCount++] = Order(orderID++, "Completed", total, orderDetails);
            cart.clearCart();
        } 
		else 
		{
            cout << "Order limit reached, cannot store more orders.\n";
        }
    }
}

void viewOrders() 
{
    if (orderCount == 0) 
	{
        cout << "No orders have been placed yet.\n";
    } 
	else 
	{
        for (int i = 0; i < orderCount; ++i) 
		{
            cout << "Order ID: " << orders[i].orderID << endl;
            cout << "Total Amount: $" << fixed << setprecision(2) << orders[i].totalAmount << endl;
            cout << "Order Details:\n";
            cout << left << setw(12) << "Product ID" 
                 << setw(20) << "Name" 
                 << setw(10) << "Price" 
                 << setw(10) << "Quantity" << endl;
            cout << "--------------------------------------------------------\n";

            istringstream iss(orders[i].orderDetails);
            string line;
            while (getline(iss, line)) 
			{
                cout << line << endl;
            }
            cout << endl;
        }
        system("pause");
    }
}

int main() 
{
    initializeProducts();
    ShoppingCart shoppingCart;
    int choice;

    while (true) 
	{
		cout << "-------------------\n";
		cout << "MAPOGI ONLINE STORE\n";
		cout << "-------------------\n\n";
        cout << "\n1. View Products\n";
        cout << "2. View Shopping Cart\n";
        cout << "3. View Orders\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
		cout << endl << endl;
		
        switch (choice) 
		{
            case 1:
                viewProducts(shoppingCart);
                break;
            case 2:
                viewShoppingCart(shoppingCart);
                break;
            case 3:
                viewOrders();
                break;
            case 4:
                return 0;
            default:
                cout << "Invalid choice, please try again.\n";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}
