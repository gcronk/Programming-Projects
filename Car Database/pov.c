/* Developer: Grady Cronkite
 * This code functions be reading information from two separate input files and storing data into two linked lists using
 * structures from pov.h. This code then creates functions based on the prototypes found in pov.h and prints the data about
 * various cars as well as sorting the cars based on factors such as price and year.
 * GetModel was provided by provided my Professor Gang Qu
 * 4/11/24 GetVehicle function was implemented. find_year and find_model helper functions were written.
 * 4/13/24 PrintVehicle, PrintVehicles, PrintAllCheaper, and PrintAllExpensive were completed
 *         VehicleYear function was started but not completed
 * 4/15/24 VehicleYear was completed. End of Phase 1
 * 4/28/24 search_and_buy function started
 * 5/3/24 search_and_buy function completed
 * 5/4/24 compare_and_sell function started
 * 5/5/24 compare_and_sell function completed
 *





*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <ctype.h>
#include "pov.h"

const char Color[12][10] = {"Red", "Blue", "White", "Silver", "Orange", "Yellow",
                            "Black", "Lime", "Green", "Oliver", "Purple", "Gray"};
// 12 different colors of the vehicles

const int upper_mile[6] = {5000, 10000, 50000, 100000, 500000, 100000000};
const int lower_mile[7] = {0, 5001, 10001, 50001, 100001, 500001};
const float upper_price[5] = {500.00, 1000.00, 10000.00, 50000.00, 100000000};
const float lower_price[5] = {0.00, 500.01, 1000.01, 10000.01, 50000.01, };
int trans = 0;

int find_year(VEHICLE *p);

void copy_nodes(VEHICLE *p, VEHICLE *q);

char* find_model(VEHICLE *p, MODEL *q);

char **models_available(VEHICLE *p);


MODEL * GetModel(FILE *fp)
{ static MODEL *manu;
  int No_manu = 0;		// number of models in input file fp 

  int i, j, k;
  char ch;
  MODEL *tmp, *cur;

  tmp = NEW(MODEL);
  if (tmp == NULL) return NULL;

  i = 0;
  while(fscanf(fp, "%c", &ch)!= EOF)
  { tmp->code[0] = ch;
    fscanf(fp, "%c%c", &(tmp->code[1]), &(tmp->code[2])); 
				// &tmp.code[2] should work as well
    tmp->code[3] = '\0';

    fscanf(fp, "%c", &ch);	// skip the space after code
    j = 0;			// gent model name[]
    do
    { fscanf(fp, "%c", &ch);
      tmp->name[j] = ch;
      j++;
    }while(ch!='\n');
    tmp->name[j-1] = '\0';
    tmp->info = NULL;		// last MODEL in the list
    if (i==0) manu = tmp;	// manu is the head of the list
    else cur->info = tmp;
    cur = tmp;			// stay at the current tail of the list

    i++;
    tmp = NEW(MODEL);
    if (tmp == NULL) return NULL;
  }

  return manu;
}

VEHICLE * GetVehicle (FILE *fp)
{ static VEHICLE *manu;
    int No_manu = 0;		// number of models in input file fp

    int i, j;
    char ch;
    char* miles;        //pointer to store characters of mileage
    char* pprice;       //pointer to store characters of price
    VEHICLE *tmp, *cur;

    tmp = NEW(VEHICLE);     //allocates memory to the list
    if (tmp == NULL) return NULL;

    i = 0;
    while(fscanf(fp, "%c", &ch)!= EOF)
    /* Gets the VIN Number */
    { tmp->VIN[0] = ch;     //get VIN number
        for(j = 1; j<17; j++){
            fscanf(fp, "%c", &(tmp->VIN[j]));  //records characters 1-16
        }

        tmp->VIN[17] = '\0';

        /* Gets the Color */
        fscanf(fp, "%c", &ch);	// skip the space after code
        j = 0;			// gent model name[]
        do
        { fscanf(fp, "%c", &ch);    //copies each chars into the color string
            tmp->color[j] = ch;
            j++;
        }while(ch != ';');
        tmp->color[j-1] = '\0';

        /* Gets the Mileage */
        j=0;
        miles = NEW(char);  //allocates memory to the miles pointer
        do
        { fscanf(fp, "%c", &ch);    //the miles pointer will record all chars that represent the mileage in the file
            miles[j] = ch;
            j++;
            miles = (char*) realloc(miles,(1+j)*sizeof(char));
        }while(ch != ';');
        tmp->mileage = strtol(miles,&miles,10); //converts string to int

        fscanf(fp, "%c", &ch);	// skip the $

        /* Gets the Price */
        j=0;
        pprice = NEW(char);     //allocates memory to the pprice pointer
        do
        { fscanf(fp, "%c", &ch);        //the pointer records the chars that represent the price in the file
           pprice[j] = ch;
           j++;
           pprice = (char*) realloc(pprice,(1+j)*sizeof(char));
        }while(ch != '\n');

	tmp->price = strtof(pprice, NULL);      //converts string to float


        tmp->info = NULL;		// last MODEL in the list
        if (i==0) manu = tmp;	// manu is the head of the list
        else cur->info = tmp;
        cur = tmp;			// stay at the current tail of the list

        i++;
        tmp = NEW(VEHICLE);     //allocates more memory to list
        if (tmp == NULL) return NULL;
    }

    return manu;
}

void PrintVehicle (VEHICLE *vehicle, FILE *file){       //prints out data about the first vehicle in the list
    // print the information of the given vehicle
    // on the screen and to the given file using
    // the following format
    // 1999 Red Dodge car, 180495 miles, 2750.00

    //printf("%d %s %s, %d miles, %f", find_year(vehicle), vehicle->color, find_model(vehicle, model), vehicle->mileage, vehicle->price);
    printf("%s %-10s%8d   %8.2f\n", vehicle->VIN, vehicle->color,vehicle->mileage, vehicle->price);
    fprintf(file,"%s %-10s%8d   %8.2f\n", vehicle->VIN, vehicle->color,vehicle->mileage, vehicle->price);

}

void PrintAllVehicles (VEHICLE *vehicle, FILE *file) {      //prints out data about all vehicles
// same as PrintVehicle(), but instead of print-
// ing only one VEHICLE, this function prints
// all the VEHICLES on the list where the head
// VEHICLE is passed to the function as the
// first parameter.

  while (vehicle != NULL){  //while nodes remain in the vehicle list
    //printf("%d %s %s, %d miles, %f", find_year(vehicle), vehicle->color, find_model(vehicle, model),vehicle->mileage, vehicle->price);

    printf("%s %-10s%8d   %8.2f\n", vehicle->VIN, vehicle->color,vehicle->mileage, vehicle->price);
    fprintf(file,"%s %-10s%8d   %8.2f\n", vehicle->VIN, vehicle->color,vehicle->mileage, vehicle->price);
    vehicle = vehicle->info;    //moves to next node in list
  }

}

void PrintAllCheaper (VEHICLE *vehicle, FILE *fp, float c){ //prints all cars cheaper than or equal to c
// vehicle is the head VEHICLE of a list of VEHICLEs,
// fp is the output file
// c is the price
// print the information of vehicles that cost
// c or less, both on the screen and to file fp.

  while (vehicle != NULL)   //while nodes remain in the vehicle list
  {
    //printf("%d %s %s, %d miles, %f", find_year(vehicle), vehicle->color, find_model(vehicle, model),vehicle->mileage, vehicle->price);
    if ((vehicle->price)<=c){   //if the price of the car is less than or equal to c
      printf("%s %-10s%8d   %8.2f\n", vehicle->VIN, vehicle->color,vehicle->mileage, vehicle->price);   //prints
      fprintf(fp,"%s %-10s%8d   %8.2f\n", vehicle->VIN, vehicle->color,vehicle->mileage, vehicle->price);  //prints to output file
    }
      vehicle = vehicle->info;      //moves to next node of vehicle list
  }

}

 void PrintAllExpensive (VEHICLE *vehicle, FILE *fp, float c){  //prints all cars more expensive than or equal to c
 // same as above, but find vehicles whose price
 // is higher or equal to c

   while (vehicle != NULL)  //while nodes remain in the vehicle list
  {
    //printf("%d %s %s, %d miles, %f", find_year(vehicle), vehicle->color, find_model(vehicle, model),vehicle->mileage, vehicle->price);
    if ((vehicle->price)>=c){   //if the price of the car is greater than or equal to c
      printf("%s %-10s%8d   %8.2f\n", vehicle->VIN, vehicle->color,vehicle->mileage, vehicle->price);   //prints
      fprintf(fp,"%s %-10s%8d   %8.2f\n", vehicle->VIN, vehicle->color,vehicle->mileage, vehicle->price);   //prints to output file
    }
    vehicle = vehicle->info;    //moves to next node of vehicle list
  }

}


VEHICLE * VehicleYear (VEHICLE *p, int k) {     //creates linked list containing all vehicles from a specified year
// check VEHICLE p or a list of VEHICLEs with p
// as the head for one that was made in the
// given year k (between 1995 and 2024).
// The return value is a pointer to the list of
// VEHICLEs that are made in year k.
// If not found, return NULL

    int i = 0;
    static VEHICLE *head;     //head of new list
    VEHICLE *cur, *tmp;       //links to different parts of the list

    if (k > 2024 || k < 1995) {  //checks that k is a valid year
        return NULL;
    }

    tmp = NEW(VEHICLE);   //allocates memory for the new list
    if (tmp == NULL) {
        return NULL;
    }

    while (p != NULL) {    //this will run until the end of the list p
        if (find_year(p) == k) {     //if the year of the car in the current node of list p is equal to k...
            strcpy((tmp->VIN), (p->VIN));   //then the data stored in the node of copied...
            strcpy((tmp->color), (p->color));       //into a node of the new list
            tmp->mileage = p->mileage;
            tmp->price = p->price;
            tmp->info = NULL;
            if (i == 0) {       //if this is the first node it should be where the head points
                head = tmp;

            } else {    //in every other node, set info equal to the next node
                cur->info = tmp;
            }
            cur = tmp;  //more cur to the current last node
            i++;
            tmp = NEW(VEHICLE); //allocate more memory fo the next node
            if (tmp == NULL) {
                return NULL;
            }
        }
        p = p->info;    //move to the next node of the p list
    }

    return head;    //return the head
}

void search_and_buy(FILE *out) {
    // user will search the POV database (that is,
    // All_Vehicles linked list) and decide whether
    // she will buy	a vehicle or not. You should
    // design your own interface.
    // 1. User will not buy more than one vehicle.
    // 2. intermediate search results need to be
    // printed both on the screen and output file.
    // 3. If user decides to buy, the vehicle must
    // be removed from the All_Vehicle list and
    // the transaction needs to be recorded in the
    // output file
    // 4. It is recommended to define new (small)
    // functions and use them to improve the
    // readability of this function
    // 5. You can define new structures if needed

    int choice, price, manu, col, mile, year;
    int j, b = 0, i, purch, k;
    char **models_list;
    VEHICLE *sorted_vehicles, //a new linked list that will hold a copy of All_Vehicles
        *sorted_tmp, *sorted_cur, *delete, *temp;
    VEHICLE *NAV = All_Vehicles;
    sorted_tmp = NEW(VEHICLE);      //allocates memory to the new list
    //sorted_vehicles will be an exact copy of All_Vehicles that can be slowly whittled away at
    while (NAV != NULL) {   //copies every node of All_Vehicles into sorted_vehicles
        copy_nodes(sorted_tmp, NAV);
        if (b == 0) sorted_vehicles = sorted_tmp;       //b indicates if it is the first node of the list or not
        else sorted_cur->info = sorted_tmp;
        sorted_cur = sorted_tmp;
        b++;
        sorted_tmp = NEW(VEHICLE);
        NAV = NAV->info;    //moves to next node
    }
    sorted_cur->info=NULL;  //sets end of sorted list to NULL

    //printf("check\n");
    //models_list=models_available(sorted_vehicles);
    //for (i=0;i<20;i++) {
    //    printf("%s", models_list[i]);
    //}

    while (1) {     //this list will run endlessly until the list is reduced to 5 options or less
        i=0;
        printf("What would you like to search for?\n(0)Year, (1) Manufacturer, (2)Color, (3)Mileage, or (4)Price\n");   //prompts the user for a choice
        scanf("%d", &choice);
        if (choice == 0) { //Show year Options
            printf("Enter the year\n"); //prompts user for year
            scanf("%d", &year);
            while ((find_year(sorted_vehicles) != year) && (sorted_vehicles->info != NULL)) {   //tests first node of the list
                delete = sorted_vehicles;       //removes vehicle from list if it does not conform to the criteria
                sorted_vehicles = sorted_vehicles->info;
                free(delete);   //frees memory
                delete = sorted_vehicles;
            }
            if (find_year(sorted_vehicles) != year){    //if none of the vehicles fit the criteria the user chose, the user will be informed and returned to the main menu
                printf("No vehicles fitting that description could be found\n    returning to main menu...\n\n");
                return;
            }
            sorted_cur = sorted_vehicles;   //sets pointer back to beginning of list
            sorted_tmp = sorted_cur->info;
            while (sorted_tmp != NULL) {
                if (find_year(sorted_tmp) != year) {    //if the vehicle was NOT made in the specified year
                    delete = sorted_tmp;        //removes vehicle from list if it does not conform to the criteria
                    sorted_tmp = sorted_tmp->info;
                    sorted_cur->info = sorted_tmp;
                    free(delete);   //frees memory
                } else {    //if the vehicle WAS made in the specified year
                    sorted_cur = sorted_cur->info;
                    sorted_tmp = sorted_cur->info;
                }
            }
        }

        if (choice == 1) {   //show manufacturer options
            char name[40];  //records the name inputted
            char mod[40];
            int c, g;
            MODEL *nav;
            nav = All_Models;   //pointer to the head of All_Models
            sorted_tmp = sorted_vehicles;

            printf("\n");
            printf("what manufacturer would you like?\n");  //prompts user for manufacturer
            //printf("(type in a manufacturer name such 'Ford truck' or type 'more' for a list of options)\n");

            for (g = 0; g < 83; g++) {  //prints out a list of available models for user to use
                printf("(%d) %-s\t ", g, nav->name);
                nav = nav->info;
            }
            printf("\n");
            scanf("%d", &c);    //records the integer next to a manufacturer name and uses that to find the name

            nav = All_Models;
            for (j = 0; j<c;j++){   //moves to cth node of model list
                nav = nav->info;
            }
            strcpy(name,nav->name);     //sets name equal to nav->name
            //printf("<%s>", name);
            //printf("<%s>", find_model(sorted_vehicles, All_Models));

            while ((strcmp(name, find_model(sorted_vehicles, All_Models)) != 0) && (sorted_vehicles->info != NULL)) {   //tests first node of the list
                delete = sorted_vehicles;   //deletes node
                sorted_vehicles = sorted_vehicles->info;
                free(delete);   //frees memory
                delete = sorted_vehicles;
            }
            if (strcmp(name, find_model(sorted_vehicles, All_Models)) != 0){    //returns to main menu if no more vehicles available
                printf("No vehicles fitting that description could be found\n    returning to main menu...\n\n");
                return;
            }
            sorted_cur = sorted_vehicles;   //sets pointer back to beginning of list
            sorted_tmp = sorted_cur->info;
            while (sorted_tmp != NULL) {
                if (strcmp(name, find_model(sorted_tmp, All_Models)) != 0) {    //if the vehicle WAS NOT of the specific model
                    delete = sorted_tmp;        //deletes node
                    sorted_tmp = sorted_tmp->info;
                    sorted_cur->info = sorted_tmp;
                    free(delete);   //frees memory
                } else {    //if the vehicle WAS of the specific model
                    sorted_cur = sorted_cur->info;
                    sorted_tmp = sorted_cur->info;
                }
            }

        }
        if (choice == 2) {  //show color options
            printf("choose a color: "); //prompts for color
            for (j = 0; j < 12; j++) {  //prints out all color options
                printf("(%d) %s, ", j, Color[j]);

            }
            printf("\n");
            scanf("%d", &col);

            while ((strcmp(sorted_vehicles->color, Color[col])!=0) && (sorted_vehicles->info != NULL)) {   //tests first node of the list
                delete = sorted_vehicles;   //removes vehicle from list if it does not conform to the criteria
                sorted_vehicles = sorted_vehicles->info;
                free(delete);   //frees memory
                delete = sorted_vehicles;
            }
            if (strcmp(sorted_vehicles->color, Color[col])!=0){     //if no vehicles remain, return to main menu
                printf("No vehicles fitting that description could be found\n    returning to main menu...\n\n");
                return;
            }

            sorted_cur = sorted_vehicles;   //sets pointer back to beginning of list
            sorted_tmp = sorted_cur->info;

            while (sorted_tmp != NULL) {
                if (strcmp(sorted_tmp->color, Color[col])!=0) { //if the vehicle is NOT the specified color
                    delete = sorted_tmp;
                    sorted_tmp = sorted_tmp->info;
                    sorted_cur->info = sorted_tmp;
                    free(delete);
                } else {    //if the vehicle is the specified color
                    sorted_cur = sorted_cur->info;
                    sorted_tmp = sorted_cur->info;
                }

            }

        }
        if (choice == 3) { // shows mileage options
            printf("choose desired mileage: ");     //prompts user for mileage choice
            printf("(0) %d-%d, (1) %d-%d, (2) %d-%d, (3) %d-%d, (4) %d-%d, (5) >%d\n", lower_mile[0], upper_mile[0],
                   lower_mile[1], upper_mile[1], lower_mile[2], upper_mile[2], lower_mile[3], upper_mile[3],
                   lower_mile[4], upper_mile[4], lower_mile[5]);    //printf out all mileage ranges
            scanf("%d", &mile);
            while (((sorted_vehicles->mileage < lower_mile[mile]) || (sorted_vehicles->mileage > upper_mile[mile])) && (sorted_vehicles->info != NULL)) {
                delete = sorted_vehicles;       //tests first node of the list and deletes node if it does not fit with criteria
                sorted_vehicles = sorted_vehicles->info;
                free(delete);   //frees memory
                delete = sorted_vehicles;
            }
            if ((sorted_vehicles->mileage < lower_mile[mile]) || (sorted_vehicles->mileage > upper_mile[mile])){ //returns to main menu if no more vehicles available
                printf("No vehicles fitting that description could be found\n    returning to main menu...\n\n");
                return;
            }

            sorted_cur = sorted_vehicles;   //sets pointer back to beginning of list
            sorted_tmp = sorted_cur->info;
            while (sorted_tmp != NULL) {
                if (!((sorted_tmp->mileage >= lower_mile[mile]) && (sorted_tmp->mileage <= upper_mile[mile]))) {
                    //if vehicles is NOT within mileage range
                    delete = sorted_tmp; //deletes node
                    sorted_tmp = sorted_tmp->info;
                    sorted_cur->info = sorted_tmp;
                    free(delete);   //frees memory
                }
                else {      //if the vehicle WAS of the specific model
                    sorted_cur = sorted_cur->info;
                    sorted_tmp = sorted_cur->info;
                }
            }

        }
        if (choice == 4) { //shows price options
            printf("choose desired price: ");   //prompts user to input a price
            printf("(0) $%.2f-%.2f, (1) $%.2f-%.2f, (2) $%.2f-%.2f, (3) $%.2f-%.2f, (4) >$%.2f\n", lower_price[0], upper_price[0],
                   lower_price[1], upper_price[1], lower_price[2], upper_price[2], lower_price[3], upper_price[3],
                   lower_price[4]);     //prints out price ranges
            scanf("%d", &price);
            while (((sorted_vehicles->price < lower_price[price]) || (sorted_vehicles->price > upper_price[price])) && (sorted_vehicles->info != NULL)) {   //tests first node of the list
                delete = sorted_vehicles;   //deletes node
                sorted_vehicles = sorted_vehicles->info;
                free(delete);   //frees memory
                delete = sorted_vehicles;
            }
            if ((sorted_vehicles->price < lower_price[price]) || (sorted_vehicles->price > upper_price[price])){
                //returns to main menu if no more vehicles available
                printf("No vehicles fitting that description could be found\n    returning to main menu...\n\n");
                return;
            }

            sorted_cur = sorted_vehicles;
            sorted_tmp = sorted_cur->info;
            while (sorted_tmp != NULL) {
                if (!((sorted_tmp->price >= lower_price[price]) && (sorted_tmp->price <= upper_price[price]))) {
                    //if the vehicle's price is NOT within the range
                    delete = sorted_tmp;
                    sorted_tmp = sorted_tmp->info;
                    sorted_cur->info = sorted_tmp;
                    free(delete);
                }
                else {  //if the vehicle's price IS within the range
                    sorted_cur = sorted_cur->info;
                    sorted_tmp = sorted_cur->info;
                }
            }
        }

        sorted_tmp = sorted_vehicles;
        printf("\n");

        while (sorted_tmp != NULL) {    //goes through the list and prints each vehicle's information in the correct format
            // printf everything in this format... 1999 Red Dodge car, 180495 miles, 2750.00
            printf("%d %-8s %-22s%7d miles, %9.2f\n", find_year(sorted_tmp), sorted_tmp->color,
                   find_model(sorted_tmp, All_Models), sorted_tmp->mileage, sorted_tmp->price);
            sorted_tmp = sorted_tmp->info;
            i++;
        }

        if (i<=5){  //if only 5 or less vehicles are left in the list...
            printf("\nWhich vehicle would you like to purchase?\n");
            for (k=1;k<=i;k++){     //printf out available vehicles and prompts user
                printf("%d, ", k);
            }
            printf("or 0 (none)\n");
            scanf("%d", &purch);
            if (purch == 0){    //if the user inputs 0 return to main menu
                return;
            }

            else{   //if user inputs another number
                trans++;    //increment the number of transactions
                i = 1;
                sorted_tmp=sorted_vehicles;
                while ((i < purch) && (sorted_tmp->info!=NULL)){    //points to the purch'th node of the list
                    sorted_tmp=sorted_tmp->info;
                    i++;
                }
                fprintf(out, "Transaction %d: %d %s sold at $%.2f\n",trans, find_year(sorted_tmp), find_model(sorted_tmp, All_Models), sorted_tmp->price);
                //prints transaction into output file
                NAV = All_Vehicles;
                temp = All_Vehicles->info;

                while (NAV!=NULL){  //deletes node of purchased vehicle from list
                    if (strcmp(temp->VIN, sorted_tmp->VIN)==0){
                        delete = temp;
                        temp = temp->info;
                        NAV->info = temp;
                        free(delete);
                        break;
                    }
                    else {
                        NAV = NAV->info;
                        temp = NAV->info;
                    }
                }

                return;

            }
        }

    }
}



void compare_and_sell(FILE *out) {
    // similar to the above function, this function
    // enables user to compare vehicles in the POV
    // database that are similar to the vehicle
    // that the user owns and decides whether she
    // wants to sell it to the POV database or not.
    int year, mileage, i, b=0, purch, k, approval;
    char VIN[17];   //holds vin number
    float offer;    //holds user price offer
    char c;
    char model[40], color[12];  //holds model and color respectively
    MODEL *mod;
    printf("welcome to the compare/sell feature\n");
    printf("Please enter the following information about the car you wish to sell\n");  //prompts user for multiple inputs
    printf("year of made: ");   //prompts user for year
    scanf("%d", &year);
    while (getchar() != '\n');

    printf("manufacturer: ");   //prompts user for manufacturer
    fgets(model, 40, stdin);

    for (i = 0; i < 40; i++) {  //replaces new line character in model with null character
        if (model[i] == '\n') {
            model[i] = '\0';
        }
    }
    printf("mileage: ");    //prompts user for mileage
    scanf("%d", &mileage);

    printf("You have entered: %d, %s, %d\n", year, model, mileage); //prints the info the user previously inputted

    VEHICLE *sorted_vehicles, *sorted_tmp, *sorted_cur, *delete, *temp, *new;
    VEHICLE *NAV = All_Vehicles, *vehicle_tail;
    sorted_tmp = NEW(VEHICLE);
    //sorted_vehicles will be an exact copy of All_Vehicles that can be slowly whittled away at
    while (NAV != NULL) {   //creates a copy of the All_Vehicles linked list
        copy_nodes(sorted_tmp, NAV);
        if (b == 0) sorted_vehicles = sorted_tmp;   //if we are at the first node
        else sorted_cur->info = sorted_tmp;
        sorted_cur = sorted_tmp;
        b++;
        sorted_tmp = NEW(VEHICLE);
        if(NAV->info==NULL){
            vehicle_tail = NAV; //creates pointer to the tail of the original list
        }
        NAV = NAV->info;

    }
    sorted_cur->info = NULL; //sets end of new list to NULL

    /*
    sorted_tmp=sorted_vehicles;
    for (i=0;i<20;i++){
        printf("%d %-8s %-22s%7d miles,$%9.2f\n", find_year(sorted_tmp), sorted_tmp->color,
               find_model(sorted_tmp, All_Models), sorted_tmp->mileage, sorted_tmp->price);
        sorted_tmp=sorted_tmp->info;
    }
    */
    while (!(((find_year(sorted_vehicles) == year) && (strcmp(model, find_model(sorted_vehicles, All_Models)) == 0)) ||
            ((find_year(sorted_vehicles) == year) &&
             ((sorted_vehicles->mileage >= mileage - 5000) && (sorted_vehicles->mileage <= mileage + 5000))) ||
            ((strcmp(model, find_model(sorted_vehicles, All_Models)) == 0) &&
            ((sorted_vehicles->mileage >= mileage - 5000) && (sorted_vehicles->mileage <= mileage + 5000)))) &&
           (sorted_vehicles->info != NULL)) {   //ok I know this is a very long statement, but it essentially checks if a vehicle does not match at least two of the criteria listed and deletes the node
        delete = sorted_vehicles;
        sorted_vehicles = sorted_vehicles->info;
        free(delete);   //frees memory
        delete = sorted_vehicles;
    }
    if (!(((find_year(sorted_vehicles) == year) && (strcmp(model, find_model(sorted_vehicles, All_Models)) == 0)) ||
          ((find_year(sorted_vehicles) == year) &&
           ((sorted_vehicles->mileage >= mileage - 5000) && (sorted_vehicles->mileage <= mileage + 5000))) ||
          ((strcmp(model, find_model(sorted_vehicles, All_Models)) == 0) &&
           ((sorted_vehicles->mileage >= mileage - 5000) && (sorted_vehicles->mileage <= mileage + 5000))))) {
            //if there are no vehicles in the list, return to main menu
        printf("No vehicles fitting that description could be found\n    returning to main menu...\n\n");
        return;
    }
    sorted_cur = sorted_vehicles;
    sorted_tmp = sorted_cur->info;
    while (sorted_tmp != NULL) {
        if (!(((find_year(sorted_tmp) == year) && (strcmp(model, find_model(sorted_tmp, All_Models)) == 0)) ||
              ((find_year(sorted_tmp) == year) &&
               ((sorted_tmp->mileage >= mileage - 5000) && (sorted_tmp->mileage <= mileage + 5000))) ||
              ((strcmp(model, find_model(sorted_tmp, All_Models)) == 0) &&
               ((sorted_tmp->mileage >= mileage - 5000) && (sorted_tmp->mileage <= mileage + 5000))))) {
            //if the criteria IS NOT met it deletes the node
            delete = sorted_tmp;
            sorted_tmp = sorted_tmp->info;
            sorted_cur->info = sorted_tmp;
            free(delete);
        } else {    //if the criteria IS met
            sorted_cur = sorted_cur->info;
            sorted_tmp = sorted_cur->info;
        }
    }
    sorted_tmp = sorted_vehicles;
    printf("\n");


    while (sorted_tmp != NULL) {    //prints out vehicles similar to user's car
        // printf everything in this format... 1999 Red Dodge car, 180495 miles, 2750.00
        printf("%d %-8s %-22s%7d miles, %9.2f\n", find_year(sorted_tmp), sorted_tmp->color,
               find_model(sorted_tmp, All_Models), sorted_tmp->mileage, sorted_tmp->price);
        sorted_tmp = sorted_tmp->info;
    }

    printf("\nHow much would you like for your car?\n$");//prompts user for a requested price
    scanf("%f", &offer);
    approval=0;
    sorted_tmp=sorted_vehicles;
    while (sorted_tmp!=NULL) {  //checks if the price is less than any of the similar vehicles. if the price in lower, the purchase is approved
        if(sorted_tmp->price >= offer){
            approval = 1;   //purchase is approved
            break;
        }
    }
    if (approval == 1) {    //purchase was approved
        trans++; //increments the number of transactions
        printf("That you for your business\n");
        printf("Transaction %d: %d %s bought at $%.2f\n", trans, year, model, offer);
        fprintf(out, "Transaction %d: %d %s bought at $%.2f\n", trans, year, model, offer);
        NAV = All_Vehicles;
        temp = All_Vehicles->info;

    }
    else{   //purchase was not approved
        printf("Your asking price is too high\n");
        return;
    }
    printf("what color is the car?\n"); //prompts the user for the car's color
    scanf("%s", color);
    printf("what is the car's VIN number\n"); //prompts the user for the car's VIN number
    scanf("%s", VIN);
    new = NEW(VEHICLE); //allocates memory for a new node
    for(i=0; i<17;i++){     //copies all important info the user has inputted about their car into the new node
        new->VIN[i] = VIN[i];
    }
    strcpy(new->color, color);
    new->mileage=mileage;
    new->price=offer;
    new->info=NULL;
    vehicle_tail->info = new;
    vehicle_tail = new; //adds node of new vehicle to the end of the All_Vehicles linked list
    //mod=All_Models;

    //while ( mod!= NULL){
    //    if(strcmp(mod->name, model)==0){
    //        new->VIN[0] = mod->code[0];
    //        new->VIN[1] = mod->code[1];
    //        new->VIN[2] = mod->code[2];
    //        break;
    //    }
    //    mod = mod -> info;
    //}



}


char *find_model(VEHICLE *p, MODEL *q){     //find the model of a vehicle based on the first 3 digits of the VIN number
    static char model[40];
    while (q != NULL){
        if((p->VIN[0] == q->code[0]) && (p->VIN[1] == q->code[1]) && (p->VIN[2] == q->code[2])){
            strcpy(model, q->name);
            return model;
        }
        q=q -> info;
    }
    return model;
}

/*
char **models_available(VEHICLE *p){        //a failed function that I spent far too long trying to make work
    char **a_models = malloc(1*sizeof(char*));
    if (a_models == NULL) {
        printf("Memory reallocation failed!\n");
        exit(-1);
    }
    char model[40];
    int i,k = 1, g=0, model_index=0;
    a_models[model_index] = malloc(40*sizeof(char));
    if (a_models[model_index] == NULL) {
        printf("Memory reallocation failed!\n");
        exit(-1);
    }
    strcpy(a_models[model_index], find_model(p,All_Models));
    p=p->info;
    while (p!=NULL){
        strcpy(model, find_model(p, All_Models));
        for (i=0;i<k;i++){
            if (strcmp(model, a_models[i]) == 0){
                g++;
                break;
            }
        }
        if (g==0) {
            strcpy(a_models[model_index], model);

            model_index++;
            //a_models = NULL;
            //a_models = realloc(a_models, (model_index+1) * sizeof(char *));
            char **temp = realloc(a_models, (model_index+1) * sizeof(char *));
            if (temp == NULL) {
                printf("Memory reallocation failed!\n");
                exit(-1);
            }
            a_models = temp;
            //a_models[model_index]=NULL;
            a_models[model_index] = malloc(40 * sizeof(char));
            if (a_models[model_index] == NULL) {
                printf("Memory reallocation failed!\n");
                exit(-1);
            }
            strcpy(a_models[model_index], model);
            k++;
        }
        p=p->info;
    }
    return a_models;
}
 */

void copy_nodes(VEHICLE *p, VEHICLE *q){        //copies all the important data held by the node from one to another
    int i;
    for (i=0; i < 18; i++) {
        p->VIN[i] = q->VIN[i];
    }
    for (i=0; i < 10; i++) {
        p->color[i] = q->color[i];
    }
    p->mileage = q->mileage;
    p->price = q-> price;
}


int find_year(VEHICLE *p){  //helper function to find the year that corresponds to the 10th character of a car's VIN number
    int num;

    switch (p ->VIN[10]){
        case 'S':
            num = 1995;
            return num;

        case 'T':
            num = 1996;
            return num;

        case 'V':
            num = 1997;
            return num;

        case 'W':
            num = 1998;
            return num;

        case 'X':
            num = 1999;
            return num;

        case 'Y':
            num = 2000;
            return num;

        case '1':
            num = 2001;
            return num;

        case '2':
            num = 2002;
            return num;

        case '3':
            num = 2003;
            return num;

        case '4':
            num = 2004;
            return num;

        case '5':
            num = 2005;
            return num;
        case '6':
            num = 2006;
            return num;

        case '7':
            num = 2007;
            return num;
        case '8':
            num = 2008;
            return num;
        case '9':
            num = 2009;
            return num;
        case 'A':
            num = 2010;
            return num;
        case 'B':
            num = 2011;
            return num;
        case 'C':
            num = 2012;
            return num;
        case 'D':
            num = 2013;
            return num;
        case 'E':
            num = 2014;
            return num;
        case 'F':
            num = 2015;
            return num;
        case 'G':
            num = 2016;
            return num;
        case 'H':
            num = 2017;
            return num;
        case 'J':
            num = 2018;
            return num;
        case 'K':
            num = 2019;
            return num;
        case 'L':
            num = 2020;
            return num;
        case 'M':
            num = 2021;
            return num;
        case 'N':
            num = 2022;
            return num;
        case 'P':
            num = 2023;
            return num;
        case 'R':
            num = 2024;
            return num;
        default:
            break;
    }
    return 0;
}

