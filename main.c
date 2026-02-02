#include <stdio.h>
#include <string.h>
#define NAME_LEN 30
#define GENRE_LEN 30
#define INTERPRETER_LEN 30
#define MAX_VINYLS 5


struct Vinyl {
    char name[NAME_LEN];
    char interpreter[INTERPRETER_LEN];
    char genre[GENRE_LEN];
    double price;
    int count;

    struct {
        int day;
        int month;
        int year;
    } date;
};

struct Vinyl vinyls[5] = {
    {"Abbey Road", "The Beatles", "Rock", 599.90, 3, {12, 3, 2024}},
    {"Back in Black", "AC/DC", "Rock", 549.00, 5, {5, 1, 2024}},
    {"Thriller", "Michael Jackson", "Pop", 499.00, 2, {20, 2, 2024}},
    {"Random Access Memories", "Daft Punk", "Electronic", 650.00, 1, {10, 4, 2024}},
    {"Nevermind", "Nirvana", "Grunge", 530.00, 4, {18, 3, 2024}}
};
int countVinyls = MAX_VINYLS;

void shopPrint() {
    printf("\n==============================\n");
    printf("Welcome in ");
    printf("\033[1;34mVinyl Records Store\033[0m!");
    printf("\n==============================\n");
}

void menuPrint() {
    printf("\nOptions:\n");
    printf("1 - All records\n");
    printf("2 - Search vinyl by name\n");
    printf("3 - Search vinyl by price\n");
    printf("X - Exit\n");
}

void editVinyl(int i) {
    printf("New price[Old:%d]: ",vinyls[i].price);
    scanf("%lf", &vinyls[i].price);

    printf("New count[Old:%d]: ",vinyls[i].count);
    scanf("%d", &vinyls[i].count);

    printf("\033[31mVinyl updated\033[0m\n");
}

void allVinyls() {
    printf("\n==============================\n");
    printf("Vinyls:");
    printf("\n==============================\n");

    for (int i = 0; i < countVinyls; i++) {
        printf(
            "%d | %s | %s | %s | %.2f | %d | %d.%d.%d\n",
            i + 1,
            vinyls[i].name,
            vinyls[i].interpreter,
            vinyls[i].genre,
            vinyls[i].price,
            vinyls[i].count,
            vinyls[i].date.day,
            vinyls[i].date.month,
            vinyls[i].date.year
        );
    }
}

void vinylDetail(int i) {
    printf("\n===== VINYL DETAIL =====\n");
    printf("Name: \033[1;31m%s\033[0m\n", vinyls[i].name);
    printf("Interpreter: \033[1;31m%s\033[0m\n", vinyls[i].interpreter);
    printf("Genre: \033[1;31m%s\033[0m\n", vinyls[i].genre);
    printf("Price: \033[1;34m%.2f\033[0m\n", vinyls[i].price);
    printf("Count: \033[1;34m%d\033[0m\n", vinyls[i].count);
    printf("Date: \033[1;32m%d.%d.%d\033[0m\n",
           vinyls[i].date.day,
           vinyls[i].date.month,
           vinyls[i].date.year);

}

void deleteVinyl(int i) {
    for (int x = i; x < countVinyls - 1; x++) {
        vinyls[x] = vinyls[x + 1];
    }
    countVinyls--;
    printf("\033[31mVinyl deleted\033[0m\n");
}
void vinylFuns(int i) {
    char choice;
    int off = 1;
    printf("\nOptions for selected vinyl:\n");
    printf("1 - Show detail\n");
    printf("2 - Edit vinyl\n");
    printf("3 - Delete vinyl\n");
    printf("X - Back to mennu\n");


    while (off != 0) {
        printf("Choice: ");
        scanf(" %c", &choice);
        switch (choice) {
            case '1':
                vinylDetail(i);
                break;
            case '2':
                editVinyl(i);
                break;
            case '3':
                deleteVinyl(i);
                break;
            case 'X':
                off = 0;
                printf("\nBack\n");
            default:
                printf("\033[31m\nInvalid input\033[0m\n");
        }
    }
}

void searchByName() {
    char searchName[30];
    int found = 0;
    printf("\n==============================\n");
    printf("Search vinyl by name");
    printf("\n==============================\n");
    printf("Enter vinyl name: ");
    scanf(" %[^\n]", searchName);

    for (int i = 0; i < countVinyls; i++) {
        if (strcmp(vinyls[i].name, searchName) == 0) {
            printf("\033[32mVinyl [name: %s]\033[0m\n", vinyls[i].name);
            vinylFuns(i);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\033[31mVinyl not found\033[0m\n");
    }
}
void searchByPrice() {
    double min;
    double max;
    int found = 0;

    printf("Min price: ");
    scanf("%lf", &min);
    printf("Max price: ");
    scanf("%lf", &max);

    for (int i = 0; i < countVinyls; i++) {
        if (vinyls[i].price >= min && vinyls[i].price <= max) {
            printf("\n[%d] %s : %.2f\n", i, vinyls[i].name, vinyls[i].price);
            found = 1;
        }
    }

    if (!found) {
        printf("\033[31mNo vinyls\033[0m\n");
    }
}

void menu() {
    int off = 1;
    char choice;

    while (off != 0) {
        shopPrint();
        menuPrint();
        printf("Your choice: ");
        scanf(" %c", &choice);
        switch (choice) {
            case '1':
                allVinyls();
                break;
            case '2':
                searchByName();
                break;
            case '3':
                printf("\n[Search vinyl by price]\n");
                break;
            case 'X':
                off = 0;
                printf("Exiting...\n");
                break;
            default:
                printf("\033[31m\nInvalid input\033[0m\n");
        }
    }
}

int main(void) {
    menu();
    return 0;
}
