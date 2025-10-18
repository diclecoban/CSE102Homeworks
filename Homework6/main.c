#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTS 100
#define MAX_LINE_LENGTH 100
#define MAX_BRAND_LEN 9

typedef struct {
    int pID;
    char type;
    char name[9];
    char brand[6];
    double price;
} Product;

struct StockEntry {
    int sID;
    int pID;
    char branch[16];
    int current_stock;
};

struct Product {
    int pID;
    char type;
    char name[50];
    char brand[50];
    float price;
};

int Menu();
int FileOperations();
int QueryProducts();
int CheckStockStatus();
int StockControlBrand();
int ExportReport();
void delete_product(int delete_id);
void update_product(int pID, char feature, char *new_value);
void add_stock_entry();
void filter_products(FILE *products_file);
int compare_strings(char str1[], char str2[]);
int match_string(char *str1, char *str2);
int str_to_int(char *str);
int array_to_int(char arr[]);
                  
int main()
{
    Menu();
}

int Menu()
{
    int option;
    
    printf(" 1- File Operations\n 2- Query products\n 3- Check stock status\n 4- Stock control by brand\n 5- Export report\n");
    
    printf("Please select an option to continue: ");
    scanf("%d", &option);
    
    
    
    switch (option)
    {
        case 1:
            FileOperations();
            break;
        case 2:
            QueryProducts();
            break;
        case 3:
            CheckStockStatus();
            break;
        case 4:
            StockControlBrand();
            break;
        case 5:
          //  ExportReport();
            break;
        default:
            break;
    }
    
    return 0;
    
}

int FileOperations()
{
    int option;
    printf(" 1-Add a new product\n 2-Delete a product\n 3-Update a product\n 4-Add feature to products\n 5-Add a new stock entry\n 6-Delete a stock entry\n 7-Update a stock entry\n 8-Back to Main Menu\n");
    printf("Please select an option: ");
    scanf("%d", &option);
    
    FILE *fp;
    FILE *stocks_file;
    int delete_id;
    int update_id;
    char feature[9];
    char new_value[9];
    char line[100];
    int new_feature_index = -1;
    int i = 0;
    

    
    switch (option)
    {
        case 1:
            
            fp = fopen("products.txt", "r");
            if (fp == NULL)
            {
                printf("Error opening file");
                return 1;
            }

            // Find the highest pID value in the file
            int highest_pID = 0;
            char line[100];
            while (fgets(line, sizeof(line), fp) != NULL)
            {
                int pID;
                sscanf(line, "%d,%*[^,],%*[^,],%*[^,],%*lf", &pID);
                
                if (pID > highest_pID)
                {
                    highest_pID = pID;
                }
            }

            // Close the file
            fclose(fp);

            // Increment the pID for the new product
            int new_pID = highest_pID + 1;

            // Prompt the user for the product details
            Product new_product;
            new_product.pID = new_pID;
            printf("Type (D/F/C/O): ");
            scanf(" %c", &new_product.type);
            printf("Name (max 8 chars): ");
            scanf("%8s", new_product.name);
            printf("Brand (max 5 chars): ");
            scanf("%5s", new_product.brand);
            printf("Price: ");
            scanf("%lf", &new_product.price);

            // Open the file for appending
            fp = fopen("products.txt", "a");
            if (fp == NULL) {
                printf("Error opening file");
                return 1;
            }

            // Write the new product to the file
            fprintf(fp, "%d,%c,%s,%s,%.2lf\n", new_pID, new_product.type, new_product.name, new_product.brand, new_product.price);

            // Close the file
            fclose(fp);

            printf("Product added successfully.\n");

            printf("Going to File Operations Menu...\n");
            printf("\n");
            
            FileOperations();
            
            break;
       case 2:
            
    printf("Enter the pID of the product to delete: ");
    scanf("%d", &delete_id);

    delete_product(delete_id);
            
            printf("Going to File Operations Menu...\n");
            printf("\n");
            
            FileOperations();
            
    
    break;

        case 3:
    
            printf("Enter the pID of the product to update: ");
                           scanf("%d", &update_id);

                           printf("Enter the name of the feature to update: ");
                           scanf("%s", feature);

                           printf("Enter the new value for the feature: ");
                           scanf("%s", new_value);

                           update_product(update_id, feature[0], new_value);
            
            printf("Going back to File Operations Menu...\n");
            FileOperations();
            
            break;
        case 4:
            printf("Going back to File Operations Menu...\n");
            FileOperations();
            break;
        case 5:
            
            stocks_file = fopen("stocks.txt", "ab");
               struct StockEntry new_stock;
            add_stock_entry();
                fclose(stocks_file);
            
            printf("Going back to File Operations Menu...\n");
            FileOperations();
            break;
        case 6:
            printf("Going back to File Operations Menu...\n");
            FileOperations();
            break;
        case 7:
            printf("Going back to File Operations Menu...\n");
            FileOperations();
            break;
        case 8:
            Menu();
            break;
        default:
            break;
    }
    
    return 0;
    
}

void delete_product(int delete_id)
{
    FILE *products_file = fopen("products.txt", "r");
    if (products_file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    int id_count = 0;
    Product products[100]; // maximum number of products
    char line[100]; // maximum line length
    while (fgets(line, sizeof(line), products_file) != NULL)
    {
        Product p;
        sscanf(line, "%d,%c,%8[^,],%5[^,],%lf",
               &p.pID, &p.type, p.name, p.brand, &p.price);
        if (p.pID != delete_id)
        {
            products[id_count++] = p;
        }
    }
    fclose(products_file);

    // shift up remaining products
    products_file = fopen("products.txt", "w");
    
    if (products_file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }
    for (int i = 0; i < id_count; i++)
    {
        Product p = products[i];
        fprintf(products_file, "%d,%c,%s,%s,%.2lf\n",
                i+1, p.type, p.name, p.brand, p.price);
    }
    
    fclose(products_file);

    printf("Product with pID %d has been deleted.\n", delete_id);
}

void update_product(int pID, char feature, char *new_value)
{
    
    double new_price;
    
    FILE *fp = fopen("products.txt", "r+");
    
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    Product products[MAX_PRODUCTS];
    int count = 0;

    // Read all products from file into memory
    while (fscanf(fp, "%d,%c,%8[^,],%5[^,],%lf\n",
                  &products[count].pID,
                  &products[count].type,
                  products[count].name,
                  products[count].brand,
                  &products[count].price) == 5)
    {
        if (products[count].pID == pID)
        {
            switch (feature) {
                case 'T':
                case 't':
                    products[count].type = new_value[0];
                    break;
                case 'N':
                case 'n':
                    for (int i = 0; i < 9; i++)
                    {
                        products[count].name[i] = new_value[i];
                        
                        if (new_value[i] == '\0')
                        {
                            break;
                        }
                    }
                    break;
                case 'B':
                case 'b':
                    for (int i = 0; i < 6; i++)
                    {
                        products[count].brand[i] = new_value[i];
                        
                        if (new_value[i] == '\0')
                        {
                            break;
                        }
                    }
                    break;
                case 'P':
                case 'p':
                    if (sscanf(new_value, "%lf", &new_price) != 1)
                    {
                        printf("Invalid input. Please enter a valid price.\n");
                        return;
                    }
                    products[count].price = new_price;
                    break;
                default:
                    printf("Invalid feature. Try again.\n");
                    fclose(fp);
                    return;
            }
        }
        count++;
    }

    // Write all products back to file
    rewind(fp);
    
    for (int i = 0; i < count; i++)
    {
        fprintf(fp, "%d,%c,%s,%s,%.2lf\n",
                products[i].pID,
                products[i].type,
                products[i].name,
                products[i].brand,
                products[i].price);
    }

    fclose(fp);
    printf("Product with pID %d has been updated.\n", pID);
}

void add_stock_entry()
{
    // Prompt user for stock entry details
    int pID, current_stock;
    char branch[16];
    printf("Enter pID: ");
    scanf("%d", &pID);
    printf("Enter branch name (max 15 characters): ");
    scanf("%15s", branch);
    printf("Enter current stock: ");
    scanf("%d", &current_stock);

    // Read the last sID in the file to determine the new sID
    int last_sID = 0;
    FILE *stocks_file = fopen("stocks.txt", "rb");
    
    if (stocks_file != NULL)
    {
        fseek(stocks_file, -sizeof(int), SEEK_END);
        
        if (fread(&last_sID, sizeof(int), 1, stocks_file) != 1)
        {
            // No entries in the file, start sID at 1
            last_sID = 0;
        }
        fclose(stocks_file);
    }
    
    else
    {
        // Failed to open file
        printf("Error: Could not open stocks file!\n");
        return;
    }

    // Increment sID for the new entry
    int new_sID = last_sID + 1;

    // Create a new stock entry struct
    struct StockEntry new_stock =
    {
        .sID = new_sID,
        .pID = pID,
        .current_stock = current_stock
    };
    strncpy(new_stock.branch, branch, 15);
    new_stock.branch[15] = '\0';

    // Append the new stock entry to the file
    stocks_file = fopen("stocks.txt", "ab");
    
    if (stocks_file != NULL)
    {
        fwrite(&new_stock, sizeof(struct StockEntry), 1, stocks_file);
        fclose(stocks_file);
        printf("Stock entry added successfully!\n");
    }
    
    else
    {
        // Failed to open file
        printf("Error: Could not open stocks file!\n");
        return;
    }
}

int QueryProducts()
{
    int op;
    char c;
    FILE *products_file;
    
    printf(" 1. List all products\n 2. Filter products by brand, type, price, or a user-defined feature\n 3. Back to main menu.\n");
    printf("Please enter an option: ");
    scanf("%d", &op);
    
    switch (op)
    {
        case 1:

            products_file = fopen("products.txt", "r");
            
            if (products_file == NULL)
            {
                printf("Could not open file\n");
                return 1;
            }

            printf("\n");
            
            while (!feof(products_file))
            {
                c = fgetc(products_file);
                putchar(c);
            }

            fclose(products_file);
            
            printf("\n");
            printf("\nGoing to the Query Products Menu...\n");
            QueryProducts();
            
            break;
        case 2:
        products_file = fopen("products.txt", "r");
                if (products_file == NULL)
                {
                    printf("Error opening file.\n");
                    return 1;
                }
            
            char search_feature[20];
            printf("Enter search feature (type, name, brand, or price): ");
            scanf("%19s", search_feature);
            char search_word[50];
            printf("Enter search word: ");
            scanf("%49s", search_word);

            // Read and print lines that match the search
            rewind(products_file); // Go back to the beginning of the file
            char line[100];
            fgets(line, sizeof(line), products_file); // Skip the header line
            int match_found = 0;
            while (fgets(line, sizeof(line), products_file) != NULL)
            {
                char line_copy[sizeof(line)];
                strcpy(line_copy, line);  // make a copy of the line

                char *pID_str = strtok(line, ",");
                char *type = strtok(NULL, ",");
                char *name = strtok(NULL, ",");
                char *brand = strtok(NULL, ",");
                char *price_str = strtok(NULL, ",");
                
                if (strcmp(search_feature, "type") == 0 && strstr(type, search_word) != NULL)
                {
                    printf("%s\n", line_copy);  // print the copy instead of the original line
                    match_found = 1;
                }
                
                else if (strcmp(search_feature, "name") == 0 && strstr(name, search_word) != NULL)
                {
                    printf("%s\n", line_copy);
                    match_found = 1;
                }
                
                else if (strcmp(search_feature, "brand") == 0 && strstr(brand, search_word) != NULL)
                {
                    printf("%s\n", line_copy);
                    match_found = 1;
                }
                
                else if (strcmp(search_feature, "price") == 0)
                {
                    double price = atof(price_str);
                    double search_price = atof(search_word);
                    
                    if (price == search_price)
                    {
                        printf("%s\n", line_copy);
                        match_found = 1;
                    }
                }
            }
            if (!match_found)
            {
                printf("No matches found.\n");
            }
                // Close the file
                fclose(products_file);
            
            printf("\nGoing to the Query Products Menu...\n");
            QueryProducts();
            break;
        case 3:
            Menu();
            
            break;
        default:
            break;
    }
    return 0;
}

int CheckStockStatus()
{
    FILE *stock_file;
    char line[100];
    int sID, pID, current_stock;
    char branch[20];
    int op;
    printf("  1-Query the stock of a given product in a specified branch by using the product ID and branch name\n  2-list the stock of all products in a specified branch\n  3-list the out-of-stock products in a specified branch\n  4-Returns to the Main Menu\n");
    
    printf("Please select an option: ");
    scanf("%d", &op);
    
    switch (op)
    {
        case 1:
            
            stock_file = fopen("stocks.txt", "r");
            if (stock_file == NULL)
                {
                    printf("Error opening file.\n");
                    return 1;
                }
            
            char search_product[10];
            printf("Enter product ID: ");
            scanf("%9s", search_product);

            char search_branch[20];
            printf("Enter branch name: ");
            scanf("%19s", search_branch);

            // Read and print the stock of the specified product in the specified branch
            
            rewind(stock_file); // Go back to the beginning of the file
            
            char line[100];
            fgets(line, sizeof(line), stock_file); // Skip the header line
            int match_found = 0;
            while (fgets(line, sizeof(line), stock_file) != NULL)
            {
                char line_copy[sizeof(line)];
                strcpy(line_copy, line);  // make a copy of the line

                char *sID_str = strtok(line, ",");
                char *pID_str = strtok(NULL, ",");
                char *branch = strtok(NULL, ",");
                char *current_stock_str = strtok(NULL, ",");
                if (strcmp(pID_str, search_product) == 0 && strcmp(branch, search_branch) == 0)
                {
                    printf("Product %s has %s stock in branch %s.\n", search_product, current_stock_str, search_branch);
                    match_found = 1;
                    break;
                }
            }
            if (!match_found)
            {
                printf("No stock found for product %s in branch %s.\n", search_product, search_branch);
            }

            // Close the file
            fclose(stock_file);
            break;
        case 2:

            stock_file = fopen("stocks.txt", "r");
            
            if (stock_file == NULL)
            {
                printf("Error opening file.\n");
                return 1;
            }

            printf("sID\tpID\tbranch\t  current_stock\n");
            printf("---------------------------------------\n");

            
            while (fgets(line, MAX_LINE_LENGTH, stock_file) != NULL)
            {
                sscanf(line, "%d,%d,%[^,],%d", &sID, &pID, branch, &current_stock);
                printf("%d\t%d\t%-10s\t%d\n", sID, pID, branch, current_stock);
            }

            fclose(stock_file);
            
            printf("\nGoing to the Check Stock Status Menu...\n");
            CheckStockStatus();
            
            break;
        case 3:
            
            stock_file = fopen("stocks.txt", "r");
            if (!stock_file)
            {
                    printf("Error opening file.\n");
                    return 1;
                }
            char branch[10];
             printf("Enter branch name: ");
             scanf("%9s", branch);

             int pid, stock;
             char branch_read[10];
             int out_of_stock_count = 0;

             printf("Out-of-stock products in branch %s:", branch);

             while (fscanf(stock_file, "%*d,%d,%9[^,],%*[^,],%d\n", &pid, branch_read, &stock) == 3)
             {
                 int i;
                 for (i = 0; branch[i] != '\0' && branch_read[i] != '\0'; i++)
                 {
                     if (branch[i] != branch_read[i]) {
                         break;
                     }
                 }

                 if (branch[i] == '\0' && branch_read[i] == '\0' && stock == 0)
                 {
                     printf("- Product %d\n", pid);
                     out_of_stock_count++;
                 }
             }

             if (out_of_stock_count == 0)
             {
                 printf("None.\n");
             }

             fclose(stock_file);
            break;
        case 4:
            Menu();
            break;
        default:
            break;
    }
    return 0;
}

int StockControlBrand()
{
    FILE *stocks_file;
    char brand[MAX_BRAND_LEN + 1];
    printf("Enter brand name: ");
    scanf("%9s", brand);
    
    stocks_file = fopen("stocks.txt", "r");
    if (!stocks_file)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // count number of products for the given brand
    int num_products = 0;
    char line[100];
    while (fgets(line, sizeof(line), stocks_file))
    {
        char token[100];
        int token_index = 0;
        int line_index = 0;
        
        while (line[line_index] != ',')
        {
            token[token_index] = line[line_index];
            token_index++;
            line_index++;
        }
        token[token_index] = '\0';
        if (compare_strings(token, brand) == 0)
        {
            num_products++;
        }
    }
    rewind(stocks_file);

    // allocate memory for the product array
    int product_array[num_products][3];
    int i = 0;

    // read and store the products for the given brand
    while (fgets(line, sizeof(line), stocks_file))
    {
        char token[100];
        int token_index = 0;
        int line_index = 0;
        while (line[line_index] != ',')
        {
            token[token_index] = line[line_index];
            token_index++;
            line_index++;
        }
        token[token_index] = '\0';
        if (compare_strings(token, brand) == 0)
        {
            // store pID, price, and current stock
            token_index = 0;
            line_index++;
            while (line[line_index] != ',')
            {
                token[token_index] = line[line_index];
                token_index++;
                line_index++;
            }
            token[token_index] = '\0';
            product_array[i][0] = array_to_int(token);  // pID
            token_index = 0;
            line_index++;
            
            while (line[line_index] != ',')
            {
                token[token_index] = line[line_index];
                token_index++;
                line_index++;
            }
            token[token_index] = '\0';
            product_array[i][1] = array_to_int(token);  // price
            token_index = 0;
            line_index++;
            while (line[line_index] != '\n')
            {
                token[token_index] = line[line_index];
                token_index++;
                line_index++;
            }
            token[token_index] = '\0';
            product_array[i][2] = array_to_int(token);  // current stock
            i++;
        }
    }

    // print the product array
    printf("pID\tprice\tstock\n");
    for (i = 0; i < num_products; i++)
    {
        printf("%d\t%d\t%d\n", product_array[i][0], product_array[i][1], product_array[i][2]);
    }

    fclose(stocks_file);

    return 0;
}

int compare_strings(char str1[], char str2[])
{
    int i = 0;
    
    while (str1[i] != '\0' || str2[i] != '\0')
    {
        
        if (str1[i] != str2[i])
        {
            return 1;
        }
        
        i++;
    }
    return 0;
}

int match_string(char *str1, char *str2)
{
    int i = 0;
    while (str1[i] == str2[i])
    {
        
        if (str1[i] == '\0')
        {
            
            return 1;
        }
        i++;
    }
    return 0;
}

// function to convert string to integer
int str_to_int(char *str)
{
    int num = 0;
    int i = 0;
    while (str[i] != '\0')
    {
        num = num * 10 + (str[i] - '0');
        i++;
    }
    
    return num;
    
}

int array_to_int(char arr[])
{
    int result = 0;
    int i = 0;
    int sign = 1;

    // Check for negative sign
    
    if (arr[0] == '-')
    {
        sign = -1;
        i = 1;
    }

    // Iterate over digits and build integer value
    while (arr[i] != '\0')
    {
        int digit = arr[i] - '0';
        result = result * 10 + digit;
        i++;
        
    }

    return sign * result;
}
