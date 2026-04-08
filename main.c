#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define NAME_LEN 30
#define GENRE_LEN 30
#define INTERPRETER_LEN 30

// Hladiny DPH podle zadání
float DPH_levels[] = {1.0, 1.10, 1.21};

struct Vinyl {
    char name[NAME_LEN];
    char interpreter[INTERPRETER_LEN];
    char genre[GENRE_LEN];
    char ean[15];          // Přidáno dle zadání
    double buyPrice;       // Nákupní cena
    double sellPrice;      // Prodejní cena bez DPH
    int amount;            // Počet kusů
    int dph_index;         // Index pro pole DPH_levels
    struct {
        int day;
        int month;
        int year;
    } date;
};

// Dynamické pole
struct Vinyl *stock = NULL;
int countVinyls = 0;

void shopPrint() {
    printf("\n==============================\n");
    printf("Welcome in \033[1;34mVinyl Records Store\033[0m!");
    printf("\n==============================\n");
}

void menuPrint() {
    printf("\nOptions:\n");
    printf("1 - All records (Sklad)\n");
    printf("2 - Add new vinyl\n");
    printf("3 - Search & Manage vinyl\n");
    printf("X - Exit\n");
}

void vinylDetail(int i) {
    double priceWithDPH = stock[i].sellPrice * DPH_levels[stock[i].dph_index];
    printf("\n===== VINYL DETAIL =====\n");
    printf("Name:        \033[1;31m%s\033[0m\n", stock[i].name);
    printf("EAN:         %s\n", stock[i].ean);
    printf("Buy Price:   %.2f\n", stock[i].buyPrice);
    printf("Sell Price:  %.2f (bez DPH)\n", stock[i].sellPrice);
    printf("Sell Price:  \033[1;32m%.2f (s DPH)\033[0m\n", priceWithDPH);
    printf("Amount:      %d ks\n", stock[i].amount);
    printf("Date added:  %d.%d.%d\n", stock[i].date.day, stock[i].date.month, stock[i].date.year);
}

void editVinyl(int i) {
    printf("New sell price [Old: %.2f]: ", stock[i].sellPrice);
    scanf("%lf", &stock[i].sellPrice);
    printf("New amount [Old: %d]: ", stock[i].amount);
    scanf("%d", &stock[i].amount);
    printf("\033[32mVinyl updated\033[0m\n");
}

void deleteVinyl(int i) {
    for (int x = i; x < countVinyls - 1; x++) {
        stock[x] = stock[x + 1];
    }
    stock = realloc(stock, countVinyls-1 * sizeof(struct Vinyl));
    countVinyls--;
    printf("\033[31mVinyl deleted from stock\033[0m\n");
}

void vinylFuns(int i) {
    char choice;
    int back = 0;
    while (!back) {
        printf("\nActions for [%s]:\n", stock[i].name);
        printf("1 - Show detail\n2 - Edit vinyl\n3 - Delete vinyl\nX - Back\nChoice: ");
        scanf(" %c", &choice);
        switch (choice) {
            case '1': vinylDetail(i); break;
            case '2': editVinyl(i); break;
            case '3': deleteVinyl(i); back = 1; break;
            case 'X': case 'x': back = 1; break;
            default: printf("Invalid choice\n");
        }
    }
}

void addVinyl() {
    struct Vinyl *temp = realloc(stock, (countVinyls + 1) * sizeof(struct Vinyl));
    if (temp == NULL) {
        printf("Problem in memmory\n");
        return;
    }
    stock = temp;

    struct Vinyl *p = &stock[countVinyls];

    printf("Name: ");
    scanf(" %[^\n]", p->name);
    printf("Interpreter: ");
    scanf(" %[^\n]", p->interpreter);
    printf("EAN: ");
    scanf("%s", p->ean);
    printf("Buy Price: ");
    scanf("%lf", &p->buyPrice);
    printf("Sell Price (no DPH): ");
    scanf("%lf", &p->sellPrice);
    printf("Amount: ");
    scanf("%d", &p->amount);
    printf("DPH Level (0=0%%, 1=10%%, 2=21%%): ");
    scanf("%d", &p->dph_index);
    printf("Date (day month year): ");
    scanf("%d %d %d", &p->date.day, &p->date.month, &p->date.year);

    countVinyls++;
    printf("\033[32mVinyl added to stock.\033[0m\n");
}

void allVinyls() {
    printf("\n%-3s | %-15s | %-10s | %-10s | %-5s\n", "ID", "Name", "Price(DPH)", "Price(clean)", "Amount");
    printf("----------------------------------------------------------\n");
    for (int i = 0; i < countVinyls; i++) {
        double dphPrice = stock[i].sellPrice * DPH_levels[stock[i].dph_index];
        printf("%d | %-15s | %-10.2f | %-10.2f | %-5d\n",
                i + 1, stock[i].name, dphPrice, stock[i].sellPrice, stock[i].amount);
    }
}

void searchByName() {
    char searchName[NAME_LEN];
    printf("Enter vinyl name to search: ");
    scanf(" %[^\n]", searchName);
    for (int i = 0; i < countVinyls; i++) {
        if (strcmp(stock[i].name, searchName) == 0) {
            vinylFuns(i);
            return;
        }
    }
    printf("\033[31mVinyl not found\033[0m\n");
}

void menu() {
    char choice;
    while (1) {
        shopPrint();
        menuPrint();
        printf("Your choice: ");
        scanf(" %c", &choice);

        switch (choice) {
            case '1':
                allVinyls();
                break;
            case '2':
                addVinyl();
                break;
            case '3':
                searchByName();
                break;
            case 'X':case 'x':
                free(stock);
                printf("Exiting...\n");
                return;
            default: printf("\033[31mInvalid input\033[0m\n");
        }
    }
}

int main(void) {
    menu();
    return 0;
}