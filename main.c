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
struct Vinyl vinyls[5]= {
    {"Abbey Road", "The Beatles", "Rock", 599.90, 3, {12, 3, 2024}},
    {"Back in Black", "AC/DC", "Rock", 549.00, 5, {5, 1, 2024}},
    {"Thriller", "Michael Jackson", "Pop", 499.00, 2, {20, 2, 2024}},
    {"Random Access Memories", "Daft Punk", "Electronic", 650.00, 1, {10, 4, 2024}},
    {"Nevermind", "Nirvana", "Grunge", 530.00, 4, {18, 3, 2024}}
};
int countVinyls= MAX_VINYLS;

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

void allVinyls() {
    printf("\n==============================\n");
    printf("Vinyls:");
    printf("\n==============================\n");

    for (int i = 0; i < countVinyls; i++) {
        printf(
           "%d | %s | %s | %s | %.2f | %d | %d.%d.%d\n",
           i+1,
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

void vinylFuns(int index) {
    char choice;
    printf("\nOptions for selected vinyl:\n");
    printf("1 - Show detail\n");
    printf("2 - Edit vinyl\n");
    printf("3 - Delete vinyl\n");
    printf("X - Back to mennu\n");
    printf("Choice: ");

    scanf(" %c", &choice);

}

void searchByName() {
    char searchName[30];
    int found = 0;

    printf("Enter vinyl name: ");
    scanf(" %[^\n]", searchName);

    for (int i = 0; i < countVinyls; i++) {
        if (strcmp(vinyls[i].name, searchName) == 0){
            printf("\033[32mVinyl found [name: %s]\033[0m\n", vinyls[i].name);
            vinylFuns(i);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\033[31mVinyl not found\033[0m\n");
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
                printf("\n[Search vinyl by name]\n");
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
