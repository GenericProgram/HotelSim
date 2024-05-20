/*
Dean Leon
5/2/24
Hotel assingment for engr 103
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <ctype.h>

typedef struct { //create room struct
    int occupancy; // number of occupants (should not exceed 4)
    char names[4][32]; //create array of strings, 4 for 4 people, 32 is the character limit for names
} Room;

Room economy[10]; //create economy floor
Room business[10]; //create business floor
Room executive[10]; //create executive floor
    
bool running = true; //bool to keep user from escaping
int input; //number that the user inputs

/**
 * Function: isValidNumericalInput
 * -------------------------------
 * Checks if a given input is a valid numerical option within a specified range.
 *
 * Parameters:
 * - numberOfOptions: The total number of valid options. This is the upper limit of the range.
 * - input: The input to check.
 *
 * Returns:
 * - true if the input is a valid option (i.e., it is an integer between 1 and numberOfOptions, inclusive).
 * - false otherwise.
 *
 * Example:
 * If numberOfOptions is 5, then the function returns true for inputs 1, 2, 3, 4, and 5, and false for any other input.
 */
bool isValidNumericalInput(int numberOfOptions, int input){
    if(input > numberOfOptions || input < 1){
        return false;
    } else {
        return true;
    }
}


/**
 * Function: getIntegerInput
 * -------------------------
 * Reads a line of input from the user and checks if the entered string can be converted to an integer in the range.
 * If it cannot, it prompts the user to enter an integer again.
 * This continues until a valid integer in the range 1-10 is entered.
 *
 * Parameters:
 * - range: the range in which to allow inputs.
 *
 * Returns:
 * - The entered integer.
 */
int getIntegerInput(int range) {
    char buffer[256];
    int number;
    char *end;

    do {
        fgets(buffer, sizeof(buffer), stdin);
        number = strtol(buffer, &end, 10);
    } while (end == buffer || *end != '\n' || number < 1 || number > range);

    return number;
}

/**
 * Function: addGuest
 * -----------------------
 * Adds a guest to one of the three floor arrays. Also increments occupancy to prevent overbooking
 *
 * Parameters:
 * - name: The name of the guest given in a string array.
 * - floor: The floor the guest is added to.
 * - roomNumber: the specific room the guest is added to.
 * - occupancy: the occupancy room the guest is being added to.
 */
void addGuest(char name[32], int floor, int roomNumber, int occupancy){
    if(floor == 1){
        strcpy(economy[roomNumber].names[occupancy], name);
        economy[roomNumber].occupancy++;
    }
    if(floor == 2){
        strcpy(business[roomNumber].names[occupancy], name);
        business[roomNumber].occupancy++;
    }
    if(floor == 3){
        strcpy(executive[roomNumber].names[occupancy], name);
        executive[roomNumber].occupancy++;
    }
}

/**
 * Function: containsDigit
 * -----------------------
 * Checks if a string contains any digits.
 *
 * Parameters:
 * - str: A pointer to the string to check.
 *
 * Returns:
 * - 1 if the string contains a digit.
 * - 0 otherwise.
 */
int containsDigit(char *str) {
    while (*str) {
        if (isdigit(*str)) {
            return 1;
        }
        str++;
    }
    return 0;
}

/**
 * Function: getStringInput
 * ------------------------
 * Reads a line of input into a buffer and checks if the entered string contains any digits.
 * If it does, it prompts the user to enter a string again.
 * This continues until a valid string with no digits is entered.
 *
 * Parameters:
 * - buffer: A pointer to the buffer to store the input string.
 * - size: The size of the buffer.
 *
 * Returns:
 * - None. The entered string is stored in the buffer passed as a parameter. 
 * */
void getStringInput(char *buffer, int size) {
    do {
        fgets(buffer, size, stdin);

        // Remove trailing newline character
        buffer[strcspn(buffer, "\n")] = 0;
    } while (containsDigit(buffer));
}

/**
 * Function: printRooms
 * --------------------
 * Prints the room numbers and their occupancy status for a given floor.
 *
 * Parameters:
 * - floor: The floor number.
 *
 * Returns:
 * - None.
 *
 * Behavior:
 * - If the floor is 1, it prints the room numbers and occupancy status for the economy rooms.
 * - If the floor is 2, it prints the room numbers and occupancy status for the business rooms.
 * - If the floor is 3, it prints the room numbers and occupancy status for the executive rooms.
 * */
void printRooms(int floor){
    if(floor == 1){
        for(int i=0; i<10; i++){
            printf("%d. Room 10%d   Occupancy: %d\n",i+1,i,economy[i].occupancy);
        }
    }
    if(floor == 2){
        for(int i=0; i<10; i++){
            printf("%d. Room 20%d   Occupancy: %d\n",i+1,i,business[i].occupancy);
        }
    }
    if(floor == 3){
        for(int i=0; i<10; i++){
            printf("%d. Room 30%d   Occupancy: %d\n",i+1,i,executive[i].occupancy);
        }
    }
}

/**
 * Function: printMenu
 * -------------------
 * Prints a menu of options for the hotel management system and prompts the user to select an option.
 *
 * Parameters:
 * - None.
 *
 * Returns:
 * - None.
 *
 * Behavior:
 * - This function first prints a welcome message and a list of options.
 * - It then calls the getIntegerInput function to prompt the user to select an option. In this case 7 options are availible.
 * - The selected option is returned by the function.
 */
void printMenu(){
    printf("\nWelcome to your hotel! (Use numerical inputs when prompted and string inputs for guest names)\n");
    printf("1. Add guest\n2. Remove guest\n3. Quick info\n4. View room\n5. Add guest to random room\n6. Exit\n7. Testing tools (UNSTABLE)\n");
    input = getIntegerInput(7);
}

/**
 * Function: calculateIncome
 * -------------------------
 * Calculates and prints the total income from guests in economy, business, and executive rooms.
 *
 * Parameters:
 * - None.
 *
 * Returns:
 * - None. This is a void function that does not return a value.
 *
 * Behavior:
 * - This function calculates the total number of guests and the total income from each type of room.
 * - It then prints the total income and the income from each type of room.
 */
void calculateIncome(){
    int totalRev = 0; //total revenue
    int guestCount = 0; //total guestcount
    int tempCount = 0; //disposable counter used to count the revenue
    //revenue from each floor
    int economyRev = 0;
    int businessRev = 0; 
    int executiveRev= 0;
    //decalring all of these sepreratly looks stupid but trying to decleare them all at once resulted in an error.

    for(int i=0; i<10; i++){
        tempCount += economy[i].occupancy;
    }
    economyRev = tempCount * 80;
    guestCount = guestCount + tempCount;
    tempCount = 0;
    for(int i=0; i<10; i++){
        tempCount += business[i].occupancy;
    }
    businessRev = tempCount * 90;
    guestCount = guestCount + tempCount;
    tempCount = 0;
    for(int i=0; i<10; i++){
        tempCount += executive[i].occupancy;
    }
    guestCount = guestCount + tempCount;
    executiveRev = tempCount * 100;
    printf("Calculated income from your %d guests is: $%d\n", guestCount, executiveRev+economyRev+businessRev);
    printf("Money from economy: $%d\n", economyRev);
    printf("Money from business: $%d\n", businessRev);
    printf("Money from executive: $%d\n", executiveRev);
}

/**
 * Function: calculateGuestCount
 * -----------------------------
 * Calculates and returns the total number of guests in economy, business, and executive rooms.
 *
 * Parameters:
 * - None.
 *
 * Returns:
 * - The total number of guests as an integer.
 *
 * Behavior:
 * - This function calculates the total number of guests in each type of room by adding up the occupancy of each room.
 * - The total number of guests is then returned by the function.
 */
int calculateGuestCount(){ 
    int guestCount=0;

    for(int i=0; i<10; i++){
        guestCount += economy[i].occupancy;
    }
    for(int i=0; i<10; i++){
        guestCount += business[i].occupancy;
    }
    for(int i=0; i<10; i++){
        guestCount += executive[i].occupancy;
    }
    return guestCount;
}

/**
 * Function: removeGuest
 * ---------------------
 * Removes a guest from a specified room on a specified floor.
 *
 * Parameters:
 * - guestIndex: The index of the guest to remove.
 * - floor: The floor number.
 * - room: The room number.
 *
 * Returns:
 * - None. This is a void function that does not return a value.
 *
 * Behavior:
 * - If the floor is 1, it removes the guest from the specified room in the economy array.
 * - If the floor is 2, it removes the guest from the specified room in the business array.
 * - If the floor is 3, it removes the guest from the specified room in the executive array.
 */
void removeGuest(int guestIndex, int floor, int room) {
    if(floor == 1) {
        if(guestIndex == 4 && economy[room].occupancy == 4) { //if guest is index 4 and the occupancy is 4 we can just remove it and lower occupancy
            memset(economy[room].names[guestIndex], '\0', sizeof(economy[room].names[guestIndex]));        
            economy[room].occupancy--;
        } else { //however if we want to remove a guest that not the most recent addition we have to just take the guy in last and move him to the one we want to remove, effectively removing the target guest but also technically shortning the array
            strcpy(economy[room].names[guestIndex], economy[room].names[economy[room].occupancy-1]);
            economy[room].occupancy--;
        }
    }
    if(floor == 2) {
        if(guestIndex == 4 && business[room].occupancy == 4) {
            memset(business[room].names[guestIndex], '\0', sizeof(business[room].names[guestIndex]));        
            business[room].occupancy--;
        } else {
            strcpy(business[room].names[guestIndex], business[room].names[business[room].occupancy-1]);
            business[room].occupancy--;
        }
    }
    if(floor == 3) {
        if(guestIndex == 4 && executive[room].occupancy == 4) {
            memset(executive[room].names[guestIndex], '\0', sizeof(executive[room].names[guestIndex]));        
            executive[room].occupancy--;
        } else {
            strcpy(executive[room].names[guestIndex], executive[room].names[executive[room].occupancy-1]);
            executive[room].occupancy--;
        }
    }
}

/**
 * Function: printGuests
 * ---------------------
 * Prints the names of the guests in a specified room on a specified floor.
 *
 * Parameters:
 * - floor: The floor number.
 * - roomNumber: The room number.
 *
 * Returns:
 * - None. This is a void function that does not return a value.
 *
 * Behavior:
 * - If the floor is 1, it prints the names of the guests in the specified room in the economy array.
 * - If the floor is 2, it prints the names of the guests in the specified room in the business array.
 * - If the floor is 3, it prints the names of the guests in the specified room in the executive array.
 */
void printGuests(int floor, int roomNumber){
    if(floor == 1){
        for(int i=0; i<economy[input-1].occupancy; i++){
            printf("%d. %s", i + 1, economy[input-1].names[i], "\n");                        
        }
    }
    if(floor == 2){
        for(int i=0; i<business[input-1].occupancy; i++){
            printf("%d. %s", i + 1, business[input-1].names[i], "\n");                        
        }
    }
    if(floor == 3){
        for(int i=0; i<executive[input-1].occupancy; i++){
            printf("%d. %s", i + 1, executive[input-1].names[i], "\n");                        
        }
    }
}

/**
 * Function: addGuestRand
 * ----------------------
 * Adds a guest to a random room on a specified floor. If the floor is full, it moves to the next floor.
 *
 * Parameters:
 * - name: The name of the guest to add.
 * - targetFloor: The floor number where the guest wants be added.
 *
 * Returns:
 * - None. This is a void function that does not return a value.
 *
 * Behavior:
 * - If the target floor is 1, it tries to add the guest to a random room in the economy array. If the floor is full, it moves to floor 2.
 * - If the target floor is 2, it tries to add the guest to a random room in the business array. If the floor is full, it moves to floor 3.
 * - If the target floor is 3, it tries to add the guest to a random room in the executive array. If the floor is full, it moves to floor 1.
 * - If all floors are full, it prints a message saying that the hotel is full.
 */
void addGuestRand(char name[32], int targetFloor) {
    int floor1count = 0; 
    int floor2count = 0;
    int floor3count = 0;
    bool loop = true;
    
    if(targetFloor == 1){
        for(int i=0; i<10; i++){
            floor1count += economy[i].occupancy;
        }
        if(floor1count == 40) {
            printf("Floor 1 full, moving to floor 2\n");
            targetFloor = 2;
        } else {
            while(true){
                int randRoom = rand() % 10;
                if(economy[randRoom].occupancy < 4) {
                    strcpy(economy[randRoom].names[economy[randRoom].occupancy], name);
                    economy[randRoom].occupancy++;
                    printf("Guest located in room 10%d\n", randRoom);
                    break;
                }
            }
        }
    } if(targetFloor == 2){
        for(int i=0; i<10; i++){
            floor2count += business[i].occupancy;
        }
        if(floor2count == 40) {
            printf("Floor 2 full, moving to floor 3\n");
            targetFloor = 3;
        } else {
            while(true){
                int randRoom = rand() % 10;
                if(business[randRoom].occupancy < 4) {
                    strcpy(business[randRoom].names[business[randRoom].occupancy], name);
                    business[randRoom].occupancy++;
                    printf("Guest located in room 20%d\n", randRoom);
                    break;
                }
            }
        }
    } if(targetFloor == 3){
        for(int i=0; i<10; i++){
            floor3count += executive[i].occupancy;
        }
        if(floor3count == 40) {
            printf("Floor 3 full, moving to floor 1\n");
            targetFloor = 1;
            addGuestRand(name, 1); //recursion needed to allow guest to be added back
        } else {
            while(true){
                int randRoom = rand() % 10;
                if(executive[randRoom].occupancy < 4) {
                    strcpy(executive[randRoom].names[executive[randRoom].occupancy], name);
                    executive[randRoom].occupancy++;
                    printf("Guest located in room 30%d\n", randRoom);
                    break;
                }
            }
        }
    }
    if((floor1count+floor2count+floor3count) == 120){
        printf("The hotel is full!\n");
    }
}


int main() {
    //system("cls"); clear terminal for aesthetics uncomment if using vs code
    srand(time(NULL)); //seed random in main because it should only be called once
    char strInput[32]; //user input for strings
    for(int i=0; i<10;i++){ //set all floors to 0 occupancy
        economy[i].occupancy = 0;
        business[i].occupancy = 0;
        executive[i].occupancy = 0;
    }

    while(running){
        printMenu();
        switch(input) {
            case 1: //adding a guest
                printf("Choose floor for guest accomodation:\n1. Economy ($80/night)\n2. Business ($90/night)\n3. Executive ($100/night)\n");
                input = getIntegerInput(3); //get option for floor
                if(input == 1) {
                    printf("Choose room(1-10): \n"); //get option for room
                    printRooms(1); //print availbible rooms
                    input = getIntegerInput(10); //get user input on room
                    if(economy[input-1].occupancy == 4) {//check room availibility
                        printf("Room full, remove guest, then try again.");
                    } else {
                        fflush(stdin); //reset stdin so terminal properly waits for fgets()
                        printf("You chose Room 10%d\n", input-1);//confirm room
                        printf("Enter guest name (spaces, but no numbers): ");
                        getStringInput(strInput, sizeof(strInput)); //get guest name input, filtered for numbers
                        addGuest(strInput, 1, input-1, economy[input-1].occupancy); //use addguest to add the guest the room, input-1 because the array counts from 0 while input does not
                        //input = 0;
                    }
                }
                else if(input == 2) { //rinse and repeat for the other 2 floors, minimal differences in room numbers
                    printf("Choose room(1-10): \n");
                    printRooms(2);
                    input = getIntegerInput(10);
                    if(business[input-1].occupancy == 4) {
                        printf("Room full, remove guest, then try again.");
                    } else {
                        fflush(stdin);
                        printf("You chose Room 20%d\n", input-1);
                        printf("Enter guest name (spaces, but no numbers): ");
                        getStringInput(strInput, sizeof(strInput));
                        addGuest(strInput, 2, input-1, business[input-1].occupancy);
                        //input = 0;
                    }
                }
                 else if(input == 3) {
                    printf("Choose room(1-10): \n");
                    printRooms(3);
                    input = getIntegerInput(10);
                    if(executive[input-1].occupancy == 4) {
                        printf("Room full, remove guest, then try again.");
                    } else {
                        fflush(stdin);
                        printf("You chose Room 30%d\n", input-1);
                        printf("Enter guest name (spaces, but no numbers): ");
                        getStringInput(strInput, sizeof(strInput));
                        addGuest(strInput, 3, input-1, executive[input-1].occupancy);
                        //input = 0;
                    }
                }
                break;
            case 2: //removing guests
                printf("Which floor is the guest on?\n1. Economy\n2. Business\n3. Executive\n"); //indentify floor
                input = getIntegerInput(3); //get user input for floor
                if(input == 1) {
                    int roomNum; //get seperate roomNum int because it input will be changing
                    printRooms(1);//since we are on first floor, print floor 1
                    printf("Choose room to remove guest from: ");
                    input = getIntegerInput(10); //get room to remove
                    roomNum = input; //save room
                    if(economy[input-1].occupancy == 0) { //check if room is empty
                        printf("Room is empty, no guest found.\n");
                    } else {
                        int count;
                        for(int i=0; i<economy[input-1].occupancy; i++){ //print the guests inside the room
                            printf("%d. %s", i + 1, economy[input-1].names[i], "\n");
                            count = i + 1; //count needs to be a varible because rooms will have different occupancies
                        }
                        printf("Choose from list of guests: ");
                        input = getIntegerInput(count); //get user input on specific guest
                        removeGuest(input-1, 1, roomNum-1); //use remove guest, input-1 and roomNum-1 are subtracted because the arrays start at 0
                    }
                } else if(input == 2){ //repeat for other floors
                    int roomNum;
                    printRooms(2);
                    printf("Choose room to remove guest from: ");
                    input = getIntegerInput(10);
                    roomNum = input;
                    if(business[input-1].occupancy == 0) {
                        printf("Room is empty, no guest found.\n");
                    } else {
                        int count;
                        for(int i=0; i<business[input-1].occupancy; i++){
                            printf("%d. %s", i + 1, business[input-1].names[i], "\n");
                            count = i + 1;
                        }
                        printf("Choose from list of guests: ");
                        input = getIntegerInput(count);
                        removeGuest(input-1, 2, roomNum-1);
                    }
                } else if(input == 3) {
                    int roomNum;
                    printRooms(3);
                    printf("Choose room to remove guest from: ");
                    input = getIntegerInput(10);
                    roomNum = input;
                    if(executive[input-1].occupancy == 0) {
                        printf("Room is empty, no guest found.\n");
                    } else {
                        int count;
                        for(int i=0; i<executive[input-1].occupancy; i++){
                            printf("%d. %s", i + 1, executive[input-1].names[i], "\n");
                            count = i + 1;
                        }
                        printf("Choose from list of guests: ");
                        input = getIntegerInput(count);
                        removeGuest(input-1, 3, roomNum-1);
                    }
                }
                break;
            case 3: //quick info selection
                printf("Quick info menu: \n1. Calculate income\n2. Number of guests\n3. Guest finder 3000\n");
                input = getIntegerInput(3); //get user input
                if(input == 1){
                    calculateIncome(); //see calculateIncome documentation
                }
                else if(input == 2){
                    printf("Total number of guests: %d\n", calculateGuestCount()); //see calculateGuestCount documentation
                }
                else if(input == 3){ //guest finder 3000
                    bool guestFound = false; //decalre guest found bool, this is to identify whether a guest was found or not
                    printf("Enter the name of the guest to be located (case and space sensitive): "); //since we use strcmp, it needs to be exactly matching
                    fflush(stdin); //reset stdin so it properly waits for string input
                    getStringInput(strInput, sizeof(strInput)); //see getStringInput documentation
                    for(int i=0; i<10;i++){
                        for(int j = 0; j<4;j++) {
                            if(strcmp(economy[i].names[j], strInput) == 0) {
                                guestFound = true;
                                printf("%s found in Room 10%d\n", strInput, i);
                            }if(strcmp(business[i].names[j], strInput) == 0) {
                                guestFound = true;
                                printf("%s found in Room 20%d\n", strInput, i);
                            }if(strcmp(executive[i].names[j], strInput) == 0) {
                                guestFound = true;
                                printf("%s found in Room 30%d\n", strInput, i);
                            }
                        }
                    }
                    if(guestFound == false) {
                        printf("Guest by name: %s not found in hotel.", strInput); //if guest is not found, print to screen results
                    } 
                }
                break;
            case 4: //view room
                printf("Which floor is the guest on?\n1. Economy\n2. Business\n3. Executive\n");
                input = getIntegerInput(3); //identify rooms from user
                if(input == 1) {
                    printRooms(1); //print the rooms
                    printf("Choose room(1-10): \n");
                    input = getIntegerInput(10); //get input on which room the user wants
                    if(economy[input-1].occupancy == 0) {
                        printf("Room is empty.\n"); //check for the vacancy
                    } else {
                        printf("That room contains: \n"); //if found, then use print guests
                        printGuests(1, input-1); //again input-1 because arrays start at 0 and the input starts at 1
                    }
                } else if(input == 2) {
                    printRooms(2);
                    printf("Choose room(1-10): \n");
                    input = getIntegerInput(10);
                    if(business[input-1].occupancy == 0) {
                        printf("Room is empty.\n");
                    } else {
                        printf("That room contains: \n");
                        printGuests(2, input-1);
                    }
                } else if(input == 3) {
                    printRooms(3);
                    printf("Choose room(1-10): \n");
                    input = getIntegerInput(10);
                    if(executive[input-1].occupancy == 0) {
                        printf("Room is empty.\n");
                    } else {
                        printf("That room contains: \n");
                        printGuests(3, input-1);
                    }
                }
                break;
            case 5: //add guest to random room
                printf("Choose floor for guest accomodation:\n1. Economy ($80/night)\n2. Business ($90/night)\n3. Executive ($100/night)\n");
                input = getIntegerInput(3); //get floor
                fflush(stdin);
                printf("Enter guest name (spaces, but no numbers): ");
                getStringInput(strInput, sizeof(strInput)); 
                addGuestRand(strInput, input);
                break;
            case 6: //exit
                printf("Logging out...");
                return 0;   
            case 7: //testing tools, just adds guests by the name of "a" to all the rooms, it is possible to bug out the program using these so use with caution, should only be used for testing purposes
                printf("Testing tools menu\n1. Fill floor 1\n2. Fill floor 2\n3. Fill floor 3\n4. Back\nWARNING: USE OF THESE COMMANDS CAN RESULT IN UNINTENDED ERRORS FOR THE PROGRAM\n");
                input = getIntegerInput(4);
                if(input == 1) {
                    for(int j = 0; j<10;j++){
                        for(int k = 0;k<4;k++){
                            strcpy(economy[j].names[k], "Dean Leon");
                            economy[j].occupancy++;
                        }
                    }
                } else if(input ==2) {
                    for(int j = 0; j<10;j++){
                        for(int k = 0;k<4;k++){
                            strcpy(business[j].names[k], "Dean Leon");
                            business[j].occupancy++;
                        }
                    }
                } else if(input == 3) {
                    for(int j = 0; j<10;j++){
                        for(int k = 0;k<4;k++){
                            strcpy(executive[j].names[k], "Dean Leon");
                            executive[j].occupancy++;
                        }
                    }
                }          
            break;
        }        
    }
}