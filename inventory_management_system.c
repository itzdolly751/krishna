#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PRODUCTS 100  // Maximum number of products

// Structure for products
struct Product {
    int id;
    char name[50];
    float price;
    int quantity;
};

// Global array to store products
struct Product inventory[MAX_PRODUCTS];
int productCount = 0;

// Function prototypes
void addProduct();
void displayInventory();
void sellProduct();
void calculateProfit();
int findProductIndexById(int productId);

int main() {
    int choice;

    while (1) {
        // Menu for user input
        printf("\nInventory Management System\n");
        printf("1. Add Product\n");
        printf("2. Display Inventory\n");
        printf("3. Sell Product\n");
        printf("4. Calculate Profit\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                displayInventory();
                break;
            case 3:
                sellProduct();
                break;
            case 4:
                calculateProfit();
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
    return 0;
}

// Function to add a product to the inventory
void addProduct() {
    if (productCount >= MAX_PRODUCTS) {
        printf("Inventory is full! Cannot add more products.\n");
        return;
    }

    struct Product newProduct;
    printf("\nEnter product details:\n");
    newProduct.id = productCount + 1;  // Assign unique ID
    printf("Product Name: ");
    getchar();  // To clear the newline left by scanf
    fgets(newProduct.name, sizeof(newProduct.name), stdin);
    newProduct.name[strcspn(newProduct.name, "\n")] = 0;  // Remove newline character

    printf("Price: ");
    scanf("%f", &newProduct.price);

    printf("Quantity: ");
    scanf("%d", &newProduct.quantity);

    // Add product to the inventory
    inventory[productCount] = newProduct;
    productCount++;

    printf("Product added successfully!\n");
}

// Function to display the current inventory
void displayInventory() {
    if (productCount == 0) {
        printf("No products available in the inventory.\n");
        return;
    }

    printf("\nInventory List:\n");
    printf("ID\tName\t\tPrice\tQuantity\n");
    for (int i = 0; i < productCount; i++) {
        printf("%d\t%s\t%.2f\t%d\n", inventory[i].id, inventory[i].name, inventory[i].price, inventory[i].quantity);
    }
}

// Function to sell a product
void sellProduct() {
    int productId, quantitySold;

    printf("\nEnter product ID to sell: ");
    scanf("%d", &productId);

    int index = findProductIndexById(productId);
    if (index == -1) {
        printf("Product not found!\n");
        return;
    }

    printf("Enter quantity to sell: ");
    scanf("%d", &quantitySold);

    if (inventory[index].quantity < quantitySold) {
        printf("Not enough stock available! Only %d items left.\n", inventory[index].quantity);
        return;
    }

    // Update stock and print sale details
    inventory[index].quantity -= quantitySold;
    printf("\nSold %d units of '%s'.\n", quantitySold, inventory[index].name);
    printf("Total sale value: %.2f\n", quantitySold * inventory[index].price);
}

// Function to calculate the profit from sales
void calculateProfit() {
    float totalRevenue = 0;
    float totalCost = 0;

    // Assuming the cost price is 70% of the selling price for profit calculation
    for (int i = 0; i < productCount; i++) {
        float costPrice = inventory[i].price * 0.7;  // Assume cost price is 70% of selling price
        totalRevenue += (inventory[i].price * (inventory[i].quantity));
        totalCost += (costPrice * (inventory[i].quantity));
    }

    float profit = totalRevenue - totalCost;
    printf("\nTotal Revenue: %.2f\n", totalRevenue);
    printf("Total Cost: %.2f\n", totalCost);
    printf("Profit: %.2f\n", profit);
}

// Function to find product by ID
int findProductIndexById(int productId) {
    for (int i = 0; i < productCount; i++) {
        if (inventory[i].id == productId) {
            return i;  // Return index of the product
        }
    }
    return -1;  // Product not found
}
