#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>



// Global variables for guest information
int guestStayLengths[10000];
int guestnumber[10000];
int guestRoomChoices[10000];
char guestBoardTypes[10000][3];
char guestBookingIDs[10000][80];
bool guestNewspapers[10000];
int guestAge[10000];
int guestNumberOfChildren[10000];
char guestFirstName[10000][15];
int guestCount = 0;

char firstName[50];
char surName[50];
float adults;
float children;
int stayLength;
int roomChoice;
char boardType[3];
char bookingID[80];
bool newspaper;
bool namecheck;
bool roomsAvailable[6] = {true, true, true, true, true, true};
int roomPrices[6] = {100, 100, 85, 75, 75, 50};
int boardPrices[3] = {20, 15, 5};

/* --- nameCheck, daysInMonth, confirmOrQuit, getBoardPrice, etc. remain unchanged --- */
//TODO Add check out function once complete


int nameCheck(const char *s ) { //validation for name
    int k=0;
    if (strlen(s) >16 || strlen(s) <=2) {
        printf(" The name you entered is either too long or too short \n");
        k++;
    }

    for(int i=0;i<strlen(s);i++) {
        if ((s[i] <65 )||(s[i] <97 && s[i]>90)||( s[i]>122)  ) {
           k++;
        }
    }

    if (k>0) {
        printf(" The name can't have any unusual characters\n");
    return 0;}
    else if (k==0){return 1;}
}

int daysInMonth(int month) {
    switch (month) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: return 31;
        case 4: case 6: case 9: case 11: return 30;
        case 2: return 28;
        default: return 0;
    }
}

int confirmOrQuit(const char* question) {
    char c;
    do {
        printf("%s (Y/N, Q to quit): ", question);
        fflush(stdin);
        scanf(" %c", &c);
        c = toupper(c);
    }while (c != 'Y' && c != 'N' && c != 'Q');
    if (c == 'Q') {return -1;}
    if (c == 'N') {return 0;}
    if (c == 'Y') {return 1;}
    else { return 2;}
}

int getBoardPrice(const char* type) {
    if (strcmp(type, "FB") == 0) return boardPrices[0];
    if (strcmp(type, "HB") == 0) return boardPrices[1];
    if (strcmp(type, "BB") == 0) return boardPrices[2];
    return 0;
}



void checkin() {
    int day, month, year;

    printf("************ Welcome to Kapa Hotel Check-in **********\n");
    printf("You can quit at any question by pressing 'Q'.\n");

    while (true) {
        int p=0;
        do {
            printf("Enter main guest's first name: ");
            scanf("%s", firstName);
            p= nameCheck(firstName );
        }while(p != 1);

        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) {
        strcpy(guestFirstName[guestCount], firstName);
            break;
        }
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        int q=0;
       do {
           printf("Enter main guest's surname: ");
           scanf("%s", surName);
            q= nameCheck(surName);
       }while (q != 1);
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        printf("Enter main guest's DOB (DD/MM/YYYY): ");
        if (scanf("%d/%d/%d", &day, &month, &year) != 3) {
            printf("Invalid format.\n");
            while (getchar() != '\n');
            continue;
        }
        if (month < 1 || month > 12 || day < 1 || day > daysInMonth(month)) {
            printf("Invalid date.\n");
            continue;
        }
        if (year>2007) {
            printf("children can't sign up please bring an adult and enter their DOB.\n");
            continue;

        }
        if (year<1925) {
            printf("You can't be more than 100 years old, that is not possible.\n");
            continue;
        }
        guestAge[guestCount] = 2025-year;
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;

    }


    while (true) {
        do {
            printf("Enter number of adults (16+): ");
            fflush(stdin);
            scanf("%f", &adults);
            printf("Enter number of children (15 or under): ");
            fflush(stdin);
            scanf("%f", &children);
            if (children > 0 && adults < 1) {
                printf("Children must be accompanied by at least one adult.\n");
            }
            if ((adults + children) > 4) {
                printf("Maximum guests allowed is 4.\n");
            }
        }while ((adults != 1 && adults != 2 && adults != 3 && adults != 4) || ( children != 1 && children != 2 && children != 3 && children != 4) || (adults + children) > 4 || (adults+children) < 1);


        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

     guestNumberOfChildren[guestCount]=children;
    while (true) {
        do{
            printf("Enter number of days to stay (max 15): ");
            fflush(stdin);
            scanf("%d", &stayLength);
            if (stayLength < 1 || stayLength > 15) {
               printf("Invalid stay length.\n");
            }
        }while (stayLength != 1 && stayLength != 2 && stayLength != 3 && stayLength != 4 && stayLength != 5 && stayLength != 6 && stayLength != 7 && stayLength != 8 && stayLength != 9 && stayLength != 10 && stayLength != 11 && stayLength != 12 && stayLength != 13 && stayLength != 14 && stayLength != 15 );

        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        printf("Enter board type (HB/FB/BB): ");
        scanf("%s", boardType);
        if (strcmp(boardType, "HB") != 0 &&
            strcmp(boardType, "FB") != 0 &&
            strcmp(boardType, "BB") != 0) {
            printf("Invalid board type.\n");
            continue;
        }
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        do{
            printf("\nAvailable rooms:\n");
            for (int i = 0; i < 6; i++)
                printf("Room %d - GBP%d - %s\n", i + 1, roomPrices[i], roomsAvailable[i] ? "Available" : "Occupied");

            printf("Choose room number: ");
            fflush(stdin);
            scanf("%d", &roomChoice);
            if (roomChoice != 1 && roomChoice != 2 && roomChoice != 3 && roomChoice != 4 && roomChoice != 5 && roomChoice != 6 && !roomsAvailable [roomChoice-1]) {
                printf("Room unavailable or invalid.\n");
            }

        }while(roomChoice != 1 && roomChoice != 2 && roomChoice != 3 && roomChoice != 4 && roomChoice != 5 && roomChoice != 6 && !roomsAvailable [roomChoice-1]);


       /*
            continue;
        }*/

        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    while (true) {
        printf("Do you want a newspaper? (Y/N): ");
        char c;
        scanf(" %c", &c);
        if (toupper(c) == 'Q') return;
        newspaper = (toupper(c) == 'Y');
        int d= (confirmOrQuit("Is this correct?"));
        if (d == 1) break;
        if (d == 0) continue;
        if (d == -1) return;
    }

    roomsAvailable[roomChoice - 1] = false;
    //generate user's bookingID by concatenating random number and surname
    int r;
    srand(time(NULL));
    r = rand() % 100;
    strcpy(bookingID, surName);
    snprintf(bookingID, sizeof(bookingID), "%s%d", surName, r);

    printf("\nBooking Summary:\n");
    printf("Guest: %s %s\n", firstName, surName);
    printf("Adults: %d, Children: %d\n", adults, children);
    printf("Stay: %d days\n", stayLength);
    printf("Board type: %s (GDP%d per person per day)\n", boardType, getBoardPrice(boardType));
    printf("Room: %d (GDP%d)\n", roomChoice, roomPrices[roomChoice - 1]);
    printf("Newspaper: %d\n", newspaper );
    printf("Booking ID: %s\n", bookingID);

    printf("\nGuest stay info has been stored under booking ID: %s\n", bookingID);
    printf("\n************* Check-in Complete ***********\n");
}

void storeInfo() { //write all of the check in data to the global vars
    guestStayLengths[guestCount] = stayLength;
    guestRoomChoices[guestCount] = roomChoice;
    strcpy(guestBoardTypes[guestCount], boardType);
    strcpy(guestBookingIDs[guestCount], bookingID);
    guestNewspapers[guestCount] = newspaper;
    guestnumber[guestCount] = children + adults;
    guestCount++;


}

void findAndPrintByID() {
    char searchID[80];
    printf("\nEnter Booking ID to search: ");
    scanf("%s", searchID);

    for (int i = 0; i < guestCount; i++) {
        if (strcmp(guestBookingIDs[i], searchID) == 0) {

            printf("\n=== Guest Found ===\n");
            printf("Booking ID: %s\n", guestBookingIDs[i]);
            printf("Room: %d\n", guestRoomChoices[i]);
            printf("Stay Length: %d days\n", guestStayLengths[i]);
            printf("number of guests: %d \n", guestnumber[i]);
            printf("Board Type: %s\n", guestBoardTypes[i]);
            printf("Newspaper: %d\n", guestNewspapers[i]);
            printf("====================\n");
            return;
        }
    }

    printf("\nNo guest found with Booking ID: %s\n", searchID);
}



//table system to determine availability
int endor7 = 0;
int naboo7 = 0;
int tatooine7 = 0;
int endor9 = 0;
int naboo9 = 0;
int tatooine9 = 0;

char bookTable(int numOfGuests); //function - user to enter choice of table
void processTableChoice(int numOfGuests); //procedure - determine if user's table can be booked

void dinnerSystem() {
    while (1) {
        printf("************* Dinner table booking ***********\n");

        int flag = 0;
        char bookingID[30];

        printf("\n Please enter your Booking ID: ");
        scanf("%s", bookingID);

        for (int i = 0; i < guestCount; i++) {
            if (strcmp(bookingID, guestBookingIDs[i]) == 0) {
                flag = 1;

                if (strcmp(guestBoardTypes[i], "FB") == 0 || strcmp(guestBoardTypes[i], "HB") == 0) {
                    processTableChoice(guestnumber[i]);
                }
                else {
                    printf("Sorry, you can only book a table if your board is FB or HB\n");
                }
            }
        }
        if (flag == 0) {
            printf("ERROR: Unable to book table as guest does not exist\n");
        }

        return;
    }
}

void processTableChoice(int numOfGuests) {
    char tableChoice;
    tableChoice = bookTable(numOfGuests);

    switch (tableChoice) {
        case 'A': endor7 = 1; printf("Your table has successfully been booked - Endor at 7PM\n"); break;
        case 'B': naboo7 = 1; printf("Your table has successfully been booked - Naboo at 7PM\n"); break;
        case 'C': tatooine7 = 1; printf("Your table has successfully been booked - Tatooine at 7PM\n"); break;
        case 'D': endor9 = 1; printf("Your table has successfully been booked - Endor at 9PM\n"); break;
        case 'E': naboo9 = 1; printf("Your table has successfully been booked - Naboo at 9PM\n"); break;
        case 'F': tatooine9 = 1; printf("Your table has successfully been booked - Tatooine at 9PM\n"); break;

        case 'X':
            printf("Sorry, this table is unavailable.\n");
            char option;
            printf("Would you like to choose a different table? (Y/N) : ");
            fflush(stdin);
            scanf(" %c", &option);
            if (toupper(option) == 'Y') { processTableChoice(numOfGuests); }//call the subroutine again so user can book
            break;

        case 'Z':
            break;

        case 0:
            printf("Sorry, there are no available tables today.\n");
    }
}

char bookTable(int numOfGuests) {
    if (numOfGuests <=4) {

        if (endor7 && naboo7 && tatooine7 && endor9 && naboo9 && tatooine9) return 0;

        char choice;
        do {
            printf("The available tables today are listed as below: \n");
            if (!endor7) printf("A) Endor at 7pm\n");
            if (!naboo7) printf("B) Naboo at 7pm\n");
            if (!tatooine7) printf("C) Tatooine at 7pm\n");
            if (!endor9) printf("D) Endor at 9pm\n");
            if (!naboo9) printf("E) Naboo at 9pm\n");
            if (!tatooine9) printf("F) Tatooine at 9pm\n");

            printf("Enter your choice of table (Enter letter): ");
            fflush(stdin);
            scanf("%c", &choice);
            char confirm;
            printf("Is this correct? (Y/N, Q to quit): ");
            fflush(stdin);
            scanf("%c", &confirm);
            if (toupper(confirm) == 'N') {
                choice = 'X'; //dummy value given so the do-while loop repeats
            }
            else if (toupper(confirm) == 'Q') {
                choice = 'Z'; //dummy value given so the user can exit dinner subprogram instantly
            }

            choice = toupper(choice);

            if (choice != 'A' && choice != 'B' && choice != 'C' && choice != 'D' && choice != 'E' && choice != 'F' && choice != 'X' && choice != 'Z') {
                printf("Please enter a VALID option from the given list.\n");
            }
        } while(choice!='A'&&choice!='B'&&choice!='C'&&choice!='D'&&choice!='E'&&choice!='F' && choice != 'Z');

        //dummy values given to choice if user tries to book an occupied table
        if (choice=='A' && endor7) return 'X';
        if (choice=='B' && naboo7) return 'X';
        if (choice=='C' && tatooine7) return 'X';
        if (choice=='D' && endor9) return 'X';
        if (choice=='E' && naboo9) return 'X';
        if (choice=='F' && tatooine9) return 'X';
        if (choice=='Z') {
            return 'Z';
        }

        return choice;
    }
    else {
        printf("Sorry, there is not a free table for your party\n");
        return 'X';
    }
}
///// check out part
float roomCost(int roomNum);
float boardCost();
float newspaperCost();
void finalBill( float roomTotal, float boardTotal, float newspaper);
void resetRoom();
int random;
void removeInfo(int Random);
void checkout() {
    char searchID[80];
    printf("\nEnter Booking ID to search: ");
    scanf("%s", searchID);
    bool found = false;

    for (int i = 0; i < guestCount; i++) {
        if (strcmp(searchID, guestBookingIDs[i]) == 0) {

            // Found matching guest
            found = true;
            random = i;

            float room = roomCost(guestRoomChoices[random] - 1);
            float board = boardCost();
            float news = newspaperCost();

            finalBill(room, board, news);
            resetRoom();
            removeInfo(random);
        }
    }

    if (!found) {
        printf("Your ID is entered wrong or doesn't exist\n");
    }


}



// Subroutine to calculate cost of room, discount for over 65's
float roomCost(int roomNum){
    float total=0;
    int stayLength = guestStayLengths[random];

    if (roomNum==0 || roomNum==1) {
        total = 100*stayLength;
    }
    else if (roomNum==2) {
        total = 85*stayLength;
    }
    else if (roomNum==3 || roomNum==4) {
        total = 75*stayLength;
    }
    else if (roomNum==5) {
        total = 50*stayLength;
    }
    else {
        printf("error");
    }

    if (guestAge[random]>=65) {
        total = total*(9.0/10.0);
    }
    return total;
}

// Subroutine to calculate board/cost of meals, discount for children
float boardCost() {
    float total=0;
    char boardType[3];
    float discount=0;


    if (strcmp(guestBoardTypes[random],"FB")==0) {
        total = 20 * guestStayLengths[random] * guestnumber[random];
         discount = 10 * guestNumberOfChildren[random] * guestStayLengths[random];
        total = total-discount;
    }
    else if (strcmp(guestBoardTypes[random],"HB")==0) {
        total = 15 *  guestStayLengths[random] * guestnumber[random];
        discount = 7.5 * guestNumberOfChildren[random] * guestStayLengths[random];
        total = total-discount;
    }
    else if (strcmp(guestBoardTypes[random],"BB")==0) {
        total = 5 *  guestStayLengths[random] * guestnumber[random];
        discount = 2.5 * guestNumberOfChildren[random] * guestStayLengths[random];
        total = total-discount;
    }


    return total;
}

// Subroutine for newspaper cost
float newspaperCost() {
   if (guestNewspapers[random] == 1) {
       float cost = 5.5;
       return cost;
   }
    else {
    return 0;
    }
}
// Subroutine outputs the final bill
void finalBill(float roomTotal, float boardTotal, float newspaper) {

    printf("\nBill for %s ", guestBookingIDs[random]);
    printf("\nBill for guest name :%s ",  guestFirstName[random]);
    printf("\nRoom total: GDP%.2f", roomTotal);
    printf("\nBoard total: GDP%.2f", boardTotal);
    printf("\nNewspaper total: GDP%.2f", newspaper);

    printf("\n\nOverall total: GDP%.2f",roomTotal + boardTotal + newspaper);


}

void resetRoom() {
    roomsAvailable[guestRoomChoices[random] - 1] = true;
}
void removeInfo(int Random) {
    char deletedID[80];
    strcpy(deletedID, guestBookingIDs[Random]);   // save before clearing

    guestStayLengths[Random] = 0;
    guestRoomChoices[Random] = 0;
    strcpy(guestBoardTypes[Random], "");
    strcpy(guestBookingIDs[Random], "");
    strcpy(guestFirstName[Random], "");
    guestNewspapers[Random] = false;
    guestnumber[Random] = 0;
    guestAge[Random] = 0;
    guestNumberOfChildren[Random] = 0;

    printf("\nGuest stay info has been deleted: %s\n", deletedID);
}

int main() {

        while (true) {
            char choice;
int k=0;
            printf("*********** Welcome to Kapa Hotel Main Menu ***********\n");
            printf("Do you want to Check In (C), Check Out (O), Dinner (D), Check info(I)? ");
            scanf(" %c", &choice);
            choice = toupper(choice);
            if (choice == 'C') {
                for (int i = 0; i < 6; i++) {
                    if (roomsAvailable[i] == false) {
                        k++;
                    }
                }
                  if (k==6) {
                      printf("We are full sorry");
                  }
                else {
                   checkin();
                    storeInfo();

                }

            }

             else if (choice == 'O') {
                checkout();
            }
            else if (choice == 'D') {
                dinnerSystem();   // <-- This is where the dinner program is now called
            }
            else if (choice == 'I') {
                findAndPrintByID();
            }

            else {
                printf("Invalid option.\n");
            }
        }

    return 0;
}
