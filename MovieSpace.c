#include <stdio.h>
#include <windows.h>
#include <conio.h>

#define NUM_SEATS 100
#define MAX_MOVIES 3

#define BLOCK_A_END 30
#define BLOCK_A_PRICE 200
#define BLOCK_B_PRICE 100
#define BLOCK_B_START 31

void setcolour(int colour) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
}

// Function to check if a seat is already booked
int isSeatBooked(int seats[], int seat) {
    return seats[seat - 1];
}

// Function to mark a seat as booked
void bookSeat(int seats[], int seat) {
    seats[seat - 1] = 1;
}

// Function to print the seat layout with seat numbers and booking status
void printSeatsInterface(int seats[], int startSeat, int endSeat) {
    
    for (int seat = startSeat; seat <= endSeat; seat++) {
        if (isSeatBooked(seats, seat)) {
            printf(" *\t ");
        } else {
            printf("%2d\t ", seat);
        }

        if (seat % 10 == 0) {
            printf("\n\n");
        }
    }
    printf("\n");
}

int main() {
    // Initialize the seats array (0 for unbooked, 1 for booked)
    int seats[MAX_MOVIES][NUM_SEATS] = {0};

    // Open files to store booking status for each movie
    FILE *files[MAX_MOVIES];

    // File names for each movie
    char movieFiles[MAX_MOVIES][20] = {"msdhoni_status.txt", "jersy_status.txt", "pushpa_status.txt"};

    for (int i = 0; i < MAX_MOVIES; i++) {
        files[i] = fopen(movieFiles[i], "r");

        if (files[i] != NULL) {
            // Read booking status from the file
            for (int seat = 1; seat <= NUM_SEATS; seat++) {
                fscanf(files[i], "%d", &seats[i][seat - 1]);
            }
            fclose(files[i]);
        }
    }

    // Movie selection
    setcolour(10);
    printf("\t\t\t Welcome to Movie Space\n");
    printf("\t\t\t=============================\n");
    printf("SELECT A MOVIE : \n");
    printf("1. M.S.DHONI\n");
    printf("2. JERSY\n");
    printf("3. PUSHPA\n");
    printf("Enter the number of the movie you want to watch: ");
    int movieChoice;
    scanf("%d", &movieChoice);

    if (movieChoice < 1 || movieChoice > MAX_MOVIES) {
        printf("Invalid movie selection. Exiting...\n");
        return 1;
    }

    char *movieName;

    switch (movieChoice) {
        case 1:
            movieName = "M.S.DHONI";
            break;
        case 2:
            movieName = "JERSY";
            break;
        case 3:
            movieName = "PUSHPA";
            break;
        default:
            movieName = "INVALID CHOICE";
            break;
    }

    // Display seat interface before booking
    printf("\n Seats Interface Before Booking:\n");
    printf("BLOCK A\n");
    printSeatsInterface(seats[movieChoice - 1], 1, BLOCK_A_END);
    
    printf("BLOCK B\n");
    printSeatsInterface(seats[movieChoice - 1], BLOCK_B_START, NUM_SEATS);
    
    // Booking seats
    int ns;
    printf("\n Enter the number of seats you want to book: ");
    scanf("%d", &ns);

    if (ns < 1 || ns > NUM_SEATS) {
        printf("Invalid booking. Exiting...\n");
        return 1;
    }

    printf("Enter the seat numbers you want to book:\n");

    // Calculate block prices for this booking session
    int totalBlockAPrice = 0;
    int totalBlockBPrice = 0;

    for (int i = 1; i <= ns; i++) {
        int sn;
        printf("Seat %d: ", i);
        scanf("%d", &sn);

        if (sn >= 1 && sn <= NUM_SEATS) {
            if (isSeatBooked(seats[movieChoice - 1], sn)) {
                printf("Seat number %d is already booked! Please select another seat.\n", sn);
                i--; // Decrement i to retry booking for the same seat
            } else {
                bookSeat(seats[movieChoice - 1], sn);

                // Update the block prices for this booking
                if (sn <= BLOCK_A_END) {
                    totalBlockAPrice += BLOCK_A_PRICE;
                } else {
                    totalBlockBPrice += BLOCK_B_PRICE;
                }
            }
        } else {
            printf("Invalid seat number %d\n", sn);
            i--; // Decrement i to retry booking for an invalid seat
        }
    }

    // Display the total price for this booking session
    printf("\nTotal Amount for Block A: %d\n", totalBlockAPrice);
    printf("Total Amount for Block B: %d\n", totalBlockBPrice);
    printf("Total Amount for booked seats: %d\n", totalBlockAPrice + totalBlockBPrice);

    if (ns > 0) {
        printf("Your seat(s) have been booked successfully! Enjoy the movie %s.\n", movieName);
    } else {
        printf("No seats were booked. Thank you for using Movie Space.\n");
    }

    // Display seat interface after booking
    printf("\n4. Seats Interface After Booking:\n");
    printf("BLOCK A\n");
    printSeatsInterface(seats[movieChoice - 1], 1, BLOCK_A_END);
    printf("BLOCK B\n");
    printSeatsInterface(seats[movieChoice - 1], BLOCK_B_START, NUM_SEATS);

    // Save booking status to the file
    files[movieChoice - 1] = fopen(movieFiles[movieChoice - 1], "w");
    for (int seat = 1; seat <= NUM_SEATS; seat++) {
        fprintf(files[movieChoice - 1], "%d\n", seats[movieChoice - 1][seat - 1]);
    }
    fclose(files[movieChoice - 1]);

    // colours list
    // 0:block
    // 1:blue
    // 2:green
    // 3:cyan
    // 4:red
    // 5:purple
    // 6:yellow
    // 7:default white
    // 8:grey
    // 9:bright blue
    // 10:bright green
    // 11:brighr cyan
    // 12:bright redgi
    // 13:pink/magenta

    return 0;
}
