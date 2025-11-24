#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "stock.dat"
#define MAX_NAME_LEN 100
#define MAX_COMPANY_LEN 100

// ------------------ STRUCT DEFINITION ------------------
typedef struct {
    int id;
    char name[MAX_NAME_LEN];
    char company[MAX_COMPANY_LEN];
    int price;
    int quantity;
} Product;

// ------------------ FUNCTION DECLARATIONS ------------------
void addProduct();
void viewProducts();
void searchProduct();
void updateProduct();
void deleteProduct();
int idExists(int id);
void saveProduct(Product p);
void loadProducts(Product products[], int *count);
void writeAllProducts(Product products[], int count);

// ------------------ MAIN MENU ------------------
int main() {
    int choice;
    do {
        printf("\n==============================\n");
        printf(" STOCK MANAGEMENT SYSTEM\n");
        printf("==============================\n");
        printf("1. Add New Product\n");
        printf("2. View All Products\n");
        printf("3. Search Product\n");
        printf("4. Update Product\n");
        printf("5. Delete Product\n");
        printf("6. Exit\n");
        printf("------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear newline

        switch (choice) {
            case 1: addProduct(); break;
            case 2: viewProducts(); break;
            case 3: searchProduct(); break;
            case 4: updateProduct(); break;
            case 5: deleteProduct(); break;
            case 6: printf("Exiting program. Goodbye!\n"); break;
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}

// ------------------ ADD PRODUCT ------------------
void addProduct() {
    Product p;
    printf("\n--- Add New Product ---\n");
    printf("Enter Product ID: ");
    scanf("%d", &p.id);
    getchar();

    if (idExists(p.id)) {
        printf("Error: Product ID already exists!\n");
        return;
    }

    printf("Enter Product Name: ");
    fgets(p.name, sizeof(p.name), stdin);
    p.name[strcspn(p.name, "\n")] = '\0';

    printf("Enter Company Name: ");
    fgets(p.company, sizeof(p.company), stdin);
    p.company[strcspn(p.company, "\n")] = '\0';

    printf("Enter Price: ");
    scanf("%d", &p.price);
    getchar();

    printf("Enter Quantity: ");
    scanf("%d", &p.quantity);
    getchar();

    saveProduct(p);
    printf("Product added successfully!\n");
}

// ------------------ SAVE PRODUCT TO FILE ------------------
void saveProduct(Product p) {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (!fp) {
        perror("Error opening file");
        return;
    }
    fwrite(&p, sizeof(Product), 1, fp);
    fclose(fp);
}

// ------------------ CHECK IF ID EXISTS ------------------
int idExists(int id) {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) return 0;

    Product p;
    while (fread(&p, sizeof(Product), 1, fp)) {
        if (p.id == id) {
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}

// ------------------ VIEW ALL PRODUCTS ------------------
void viewProducts() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found.\n");
        return;
    }

    Product p;
    printf("\n%-10s %-20s %-20s %-10s %-10s\n",
           "ID", "Name", "Company", "Price", "Qty");
    printf("---------------------------------------------------------------------\n");

    while (fread(&p, sizeof(Product), 1, fp)) {
        printf("%-10d %-20s %-20s %-10d %-10d\n",
               p.id, p.name, p.company, p.price, p.quantity);
    }
    fclose(fp);
}

// ------------------ SEARCH PRODUCT ------------------
void searchProduct() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) {
        printf("No records found.\n");
        return;
    }

    int id, found = 0;
    Product p;

    printf("\nEnter Product ID to search: ");
    scanf("%d", &id);
    getchar();

    while (fread(&p, sizeof(Product), 1, fp)) {
        if (p.id == id) {
            printf("\nProduct Found:\n");
            printf("ID: %d\nName: %s\nCompany: %s\nPrice: %d\nQuantity: %d\n",
                   p.id, p.name, p.company, p.price, p.quantity);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("No product found with ID %d.\n", id);

    fclose(fp);
}

// ------------------ UPDATE PRODUCT ------------------
void updateProduct() {
    Product products[100];
    int count = 0, id, found = 0;

    loadProducts(products, &count);

    printf("\nEnter Product ID to update: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (products[i].id == id) {
            found = 1;
            printf("Enter new company name: ");
            fgets(products[i].company, sizeof(products[i].company), stdin);
            products[i].company[strcspn(products[i].company, "\n")] = '\0';
            printf("Enter new price: ");
            scanf("%d", &products[i].price);
            getchar();
            printf("Enter new quantity: ");
            scanf("%d", &products[i].quantity);
            getchar();
            break;
        }
    }

    if (found) {
        writeAllProducts(products, count);
        printf("Product record updated successfully.\n");
    } else {
        printf("Product ID not found.\n");
    }
}

// ------------------ DELETE PRODUCT ------------------
void deleteProduct() {
    Product products[100];
    int count = 0, id, found = 0;

    loadProducts(products, &count);

    printf("\nEnter Product ID to delete: ");
    scanf("%d", &id);
    getchar();

    for (int i = 0; i < count; i++) {
        if (products[i].id == id) {
            found = 1;
            printf("Are you sure you want to delete %s (ID %d)? (y/n): ", products[i].name, id);
            char confirm = getchar();
            getchar();
            if (confirm == 'y' || confirm == 'Y') {
                for (int j = i; j < count - 1; j++)
                    products[j] = products[j + 1];
                count--;
                writeAllProducts(products, count);
                printf("Record deleted successfully.\n");
            } else {
                printf("Deletion cancelled.\n");
            }
            break;
        }
    }

    if (!found)
        printf("Product ID not found.\n");
}

// ------------------ LOAD & WRITE ALL PRODUCTS ------------------
void loadProducts(Product products[], int *count) {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (!fp) return;
    *count = 0;
    while (fread(&products[*count], sizeof(Product), 1, fp))
        (*count)++;
    fclose(fp);
}

void writeAllProducts(Product products[], int count) {
    FILE *fp = fopen(FILE_NAME, "wb");
    if (!fp) {
        perror("Error opening file");
        return;
    }
    fwrite(products, sizeof(Product), count, fp);
    fclose(fp);
}
