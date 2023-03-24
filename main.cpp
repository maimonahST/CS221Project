//
//  main.cpp
//  cs221Project
//
//  Created by Maimonah Altaweel on 09/08/1442 AH.
//

#include <iostream>
#include <fstream>
#include <ctime>
#include <string>


/*
        Maimonah Altaweel     2200002493
        Juri Alaqeel          2200004016
        Sara Alsubaie         2200005393
        Fay Alyemni           2200003926
*/

using namespace std;


// struct part

struct date{
    int day;
    int month;
    int year;
};

struct cars{
    int carId;
    string name;
    string brand;
    string color;
    date yearOfManufacture;
    double PricePerDay;
    int numOfbookedDays = 0;
    date NotAvilableDate[20];
};

struct booking{
    string costumerID;
    string bookingID; // generated atomaticaly
    int selectedCar; // carId
    date startDay;
    date endDay;
    int period ; // calculate the differance between start day and end day
    double price;// period * price of car
    date dateOfAdding;
    date lastUpdate;
    
};

struct costumer{
    string costumerID; //phoneNumber
    string costumerName;
    date dob;
    int numOfBooking;
    string bookingRecoredes[100];
    string dateOfadding;
    string lastUpdate;
    
};

// Functions prototype

void addNewCostumer(costumer *s, int &numOfItem,int size);
void addNewBooking(booking *b ,int &bookingNOI, cars *car,costumer *cost, int carNumOfItems , int index);// sara **
int searchByCostumerID(costumer * arr , int first , int last , string ID );
int searchByBookingID( booking * arr , int first , int last , string ID);
void disblayCarInfo(cars *car, int numOfitems);
void updateCostumerInfo( costumer *s, int index );
void deletebooking(booking * arr, int& bookingNOI, costumer *cost ,cars *car, int numOfCars, int &numOfB , int &BCindex, int index,  int Bindex);
void sortCustomers(costumer * arr, int numOfItem);
void inFiles( costumer * cost, int &numberOfItems, int size,  booking *BookingArr, int &bookingNumOf, cars * carsArr, int &carsNumOfItem );
void outFiles( costumer * cost, int &numberOfItems, int size,  booking *BookingArr, int &bookingNumOf, cars * carsArr, int &carsNumOfItem );
void displayDate (int d,int m,int y , date *dateArray);
void display( booking *b, int index );
void display( costumer *cost, int index );
void reportFile( costumer *cost , int index , int Func);



int main() {
   
    // declare varibables
    int size = 100 , bSize = 200, numberOfItems = 0, choice, index = 0 ,Bindex = 0 , numberOfBooking = 0 , numberOfcars = 0;
    
    bool Bflag = false ;
    
    string MainMenu = "\n\t--------Main Menu--------\n1.\t add new costumer\n2.\t Former customer\n3.\t Exit: \n\t------------------------\n";
    
    char *SubMenu = "\n\t--------SubMenu--------\n1.\tAdd new booking\n2.\tDisplay costumer information \n3.\tDisplay Booking information\n4.\tUpdate costumer information\n5.\tDelete Booking\n6.\tBack to main menu: \n\t------------------------\n";
    
    string ID;

    //create dynamic array
    costumer* cost = new costumer[size];
    booking* book = new booking[bSize];
    cars* car = new cars[11];
    
    // get information from files and save it in dynamic array
    inFiles(cost, numberOfItems, size, book, numberOfBooking, car, numberOfcars);
    
    // print Main menu
    cout << MainMenu;
    
    //get user choice
    cout << "Enter number from the menu: ";
    cin >> choice;
    
    
    do {
        switch (choice) {
            case 1: //add new costumer
                addNewCostumer(cost, numberOfItems, size);
                reportFile(cost, numberOfItems, 1);
                break;
                
            case 2: //Former customer
                // get costumer Id
                cout << "\t>>Enter costumer phone Number \n";
                cin >> ID;
                
                // sort costumer array before search
                sortCustomers(cost, numberOfItems);
                
                // search for the location of costumer
                index = searchByCostumerID(cost, 0, numberOfItems, ID);
                
                
                if ( index == -1 ) { // ID did not find
                    cout << "\nwrong phone number, try Again." ;
                    
                } else if ( index >= 0  ){
                    
                    // costumer Enter successfully
                    cout << "\nWelcome " << cost[index].costumerName << " ."<< endl;
                    reportFile(cost, index, 2);
                    
                    do{
                    // print sub menu
                    cout << SubMenu;
                    cout << "Enter number from the menu: ";
                    // get user choice
                    cin >> choice;
                        
                    switch (choice) {
                        case 1: // add new booking
                            addNewBooking(book, numberOfBooking, car, cost, numberOfcars, index);
                            
                            // write report
                            reportFile(cost, index, 3);
                            break;

                        case 2: // display costumer information
                            display(cost, index);
                            break;
                            
                        case 3: // display booking information
                            display(cost, index);
                            
                            // get booking Id
                            cout << "Enter Booking ID\n";
                            cin >> ID;
                            
                            // search for the location of booking
                            Bindex = searchByBookingID(book, 0, numberOfBooking, ID);

                            
                            if ( Bindex == -1 ) {
                                cout << "\nwrong ID, try Again." ;
                                
                            } else if ( Bindex >= 0  ){
                                
                                cout << "\nThe booking is found "<< endl;

                                // cheick if the booking is related to the costumer
                                for ( int i = 0 ; i < cost[index].numOfBooking || Bflag  ; i++ ){
                                    
                                    if ( book[Bindex].bookingID == cost[index].bookingRecoredes[i]){

                                        // to stop the for loop
                                        Bflag = false;
                                        
                                        // display the booking
                                        display(book, Bindex);
                                        
                                    }
                                }
                                
                                // if the booking dose not related to the costumer
                                if ( Bflag ){
                                    cout << "this costumer do not have booking with this Id ";
                                }
                                
                            } else  {
                                
                                cout << "Unexpected Error";
                            }
                            
                            break;

                        case 4: // update costumer information
                            updateCostumerInfo(cost, index);
                            
                            // write report
                            reportFile(cost, index, 4);
                            break;
                            
                        case 5: // Delete booking
                            
                            // get booking Id
                            cout << "Enter Booking ID\n";
                            cin >> ID;
                            
                            // search for the location of booking
                            Bindex = searchByBookingID(book, 0, numberOfBooking, ID);

                            
                            if ( Bindex == -1 ) {
                                cout << "\nwrong ID, try Again." ;
                                
                            } else if ( Bindex >= 0  ){
                                
                                cout << "\nThe booking is found "<< endl;

                                // cheick if the booking is related to the costumer
                                for ( int i = 0 ; i < cost[index].numOfBooking || Bflag  ; i++ ){
                                    
                                    if ( book[Bindex].bookingID == cost[index].bookingRecoredes[i]){
                                        // BCindex is the booking index in costumer array
                                        int BCindex = i;
                                        
                                        // to stop the for loop
                                        Bflag = false;
                                        
                                        // delete the booking
                                        deletebooking(book, numberOfBooking, cost, car, numberOfcars, numberOfBooking, BCindex, index, Bindex);
                                        
                                        // write report
                                        reportFile(cost, index, 5);
                                    }
                                }
                                
                                // if the booking dose not related to the costumer
                                if ( Bflag ){
                                    cout << "this costumer do not have booking with this Id ";
                                }
                                
                            } else  {
                                
                                cout << "Unexpected Error";
                            }
                    
                            break;
                            
                        case 6: // back to main menu
                            reportFile(cost, index, 6);
                            break;

                        default:
                            cout << "invalid input\n";
                            break;
                    }
                    }while (choice != 5);
                    
                } else if ( index == -2 ){
                    // costumer ID not found
                    cout << "item is not found\n";
                    
                } else {
                    cout << "Unexpected Error";
                }
                
                break;
                
            case 3: // close the program
                
                break;
            default:
                cout << "invalid input\n";
                break;
        }
        
        // print main menu Again
        cout << MainMenu;
        cin >> choice;
        
    }while (choice != 3);

    // save array data in files
    
    outFiles(cost, numberOfItems, size, book, numberOfBooking, car, numberOfcars);
    
    // delete the Dynamic array
    delete [] cost;
    cost = NULL;
    
    return 0;
}

// Functions Part

int searchByCostumerID( costumer * arr , int first , int last , string ID){
 
// binary search
    if ( first <= last ){
        int mid =  ( first + last )/ 2;
        
        if ( ID ==  arr[mid].costumerID){
            return mid;
        } else if ( ID < arr[mid].costumerID){
            return searchByCostumerID(arr, first , mid - 1 , ID);
        } else  {
            return searchByCostumerID(arr, mid + 1 , last , ID);
        }
        
    }
    
    return -1;
}


int searchByBookingID( booking * arr , int first , int last , string ID){
// binary search
    if ( first <= last ){
        
        int mid =  ( first + last )/ 2;
        if ( ID ==  arr[mid].bookingID){
            return mid;
        } else if ( ID < arr[mid].bookingID){
            return searchByBookingID(arr, first , mid - 1 , ID);
        } else {
            return searchByBookingID(arr, mid + 1 , last , ID);
        }
    }
        return -1 ;
}


void addNewCostumer(costumer *s, int &numOfItem,int size ){
    
    time_t now = time(0);
    tm* dt = localtime(&now);
    
    string id , Fname ,Sname ;
    int d , m , y;
    bool dateFlag = false;
    
    // cheack if the the array has space or not
    if ( size > numOfItem ){
        cout<<"____________________Adding new costumer____________________"<<endl;
        cout<<">> Enter costumer phone number (966XXXXXXXXX) :";
        cin>>id;
    
        if ( id.substr(0,3) == "966" && id.length() == 12){
            // cheack if there is any other contumer has the same Id before accept
            int idindex = searchByCostumerID(s, 0, numOfItem, id);
            
                if(idindex == -1){
                    
                    s[numOfItem].costumerID = id;
                    cout<<">> Enter costumer name ";
                    cin >> Fname >> Sname ;
                    s[numOfItem].costumerName = Fname +" "+Sname;
                    
                    do {
                        dateFlag = false;
                        
                    // get date of birth
                    cout<<">> Enter Date Of Birth for the costumer (day \ month \ year) ";
                    cin >> d >>  m >>  y ;
                        
                    // check if the date is correct
                    // check if the costumer is greater than 18 years
                    if ( d < 31 && d > 0 ){
                        s[numOfItem].dob.day = d;
                        
                    }else{
                        dateFlag = true;
                        cout << "\nday must be between 1 and 31\n";
                    }
                    
                    
                    if ( m  <= 12 && m >= 1){
                        s[numOfItem].dob.month = m;
                        
                    } else {
                        dateFlag = true;
                        cout << "\nMonth must be between 1 and 12\n";
                    }
                    
                    if ( y < (((dt->tm_year)+1900) - 18) && y > 0 ){
                        s[numOfItem].dob.year = y;
                    } else {
                        dateFlag = true;
                        cout << "\nAge must be greater than 18 years.\n";
                    }
                    
                    } while ( dateFlag );
                
                    // set numOfBooking = 0
                    s[numOfItem].numOfBooking = 0;
                    
                    // set dateOfadding ( date of today )
                    s[numOfItem].dateOfadding = to_string((dt->tm_mday));
                    s[numOfItem].dateOfadding += "\\";
                    s[numOfItem].dateOfadding += to_string((dt->tm_mon)+1);
                    s[numOfItem].dateOfadding += "\\";
                    s[numOfItem].dateOfadding += to_string((dt->tm_year)+1900);
                    
                    // set lastUpdate = dateOfadding;
                    s[numOfItem].lastUpdate = s[numOfItem].dateOfadding;
                    
                    // inrease numOfItem;
                    numOfItem++;
                    
                } else if(idindex >= 0){
                    cout<<">> This ID already exists\n";
                }else{
                    cout << "\nunexpected error";
                }
        } else{
            cout << "\nincorrect phone number, phone number must start with ( 966 ) and contain 12 number ";
        }
    } else {
        cout << "\nArray is fill";
    }
    }


void addNewBooking(booking *b ,int &bookingNOI, cars *car,costumer *cost, int carNumOfItems, int index){
    bool f= false;
    int sCar , dtoday,mtoday, ytoday;
    
    cout<<"\n____________________Adding new Booking____________________\n"<<endl;
    
    // add costumer id and generate bookig id automaticly
    b[bookingNOI].costumerID = cost[index].costumerID;
    
    // get last booking id
    if (bookingNOI != 0 ){
        int bID = stoi(b[bookingNOI-1].bookingID);
        
        // add one to bID and convert bID to string
        b[bookingNOI].bookingID = to_string(bID + 1);
    } else {
        b[bookingNOI].bookingID = "0";
    }
    
    // print Booking ID
    cout << "\n booking ID : "<< b[bookingNOI].bookingID << endl;
    
    // display car information
    disblayCarInfo(car, carNumOfItems);
    
    // select car
    cout << "\nEnter car Id :  ";
    cin >> sCar ;
    
    if ( sCar < 12 && sCar >= 0){
        b[bookingNOI].selectedCar = sCar;
    }else {
        cout << "invalid input\n";
    }
    
    
    // display available time
    time_t now = time(0);
    tm* dt = localtime(&now);
    
    // print Current Date
    cout << " Current Date: " <<(dt->tm_mday)<<"/"<< (dt->tm_mon)+1 <<"/"<< (dt->tm_year)+1900<< endl;
    date d[14];

    
    dtoday = (dt->tm_mday) , mtoday = (dt->tm_mon)+1, ytoday= (dt->tm_year)+1900;
    
    // fill calander array
    displayDate(dtoday, mtoday, ytoday, d);
    cout << "\n......\n";
    
    // display calander
    
    
    cout.precision(5);
    cout << showpoint;
    for ( int i = 0 ; i  < 14 ; i++){

        cout.width(10);
        cout << i+1 << ".\t" << d[i].day << "\\" <<  d[i].month << "\\" << d[i].year ;
        cout.width(10);
        
        if ( (i+1) % 3 == 0 && i != 0){
            cout << endl;
        }
        
    }
    
    cout << "\n......\n";
    
    
    do {
        int start = 0 , end = 0;
        // get start day and end day
        
        cout << "\nEnter start day and End day ";
        cin >> start >> end ;
        
        start-=1;
        end-=1;
        if ( start <= end && start >= 0 && start < 15 && end >= 0 && end < 15){
        // claculate period2
        b[bookingNOI].period = (end - start)+1;
        
        cout << "\n......\n";
        cout << "\tperiod = " <<  b[bookingNOI].period <<" Days"<< endl;
        int n = car[sCar].numOfbookedDays;
        
            // check if the date is available
        f = false;
        for ( int i = 0 ; i < n; i++){ // if not available
            
            if (car[sCar].NotAvilableDate[i].day == d[start].day && car[sCar].NotAvilableDate[i].month == d[start].month && car[sCar].NotAvilableDate[i].year == d[start].year){
                
                cout << "start date not available, try another date";
                f= true;
                break;
            }
            
            if (car[sCar].NotAvilableDate[i].day == d[end].day && car[sCar].NotAvilableDate[i].month == d[start].month && car[end].NotAvilableDate[i].year == d[end].year){
                
                cout << "end date not available, try another date";
                f = true;
                break;
                
            }
        }
        
            //
            int numOfrec = cost[index].numOfBooking;
            if ( f == false ){
                b[bookingNOI].startDay = d[start];
                b[bookingNOI].endDay = d[end];
                cost[index].bookingRecoredes[numOfrec] = b[bookingNOI].bookingID;
                
                
                
                for ( int j = 0 , s = start ; j < b[bookingNOI].period ;j++, s++){
                    car[sCar].NotAvilableDate[n+j].day = d[s].day;
                    car[sCar].NotAvilableDate[n+j].month = d[s].month;
                    car[sCar].NotAvilableDate[n+j].year = d[s].year;
                }
                car[sCar].numOfbookedDays += b[bookingNOI].period;
                
                b[bookingNOI].price = ( car[sCar].PricePerDay * b[bookingNOI].period );
                cout << "\tTotal cost is " << b[bookingNOI].price << "SR.\n";
                cout << "\n......\n";
                
                // set dateOfAdding and lastUpdate as date of today
                b[bookingNOI].dateOfAdding.day =dtoday;
                b[bookingNOI].dateOfAdding.month = mtoday;
                b[bookingNOI].dateOfAdding.year = ytoday;
                b[bookingNOI].lastUpdate = b[bookingNOI].dateOfAdding;
                
                // increas bookingNOI
                bookingNOI++;
                // increase numOfBooking
                cost[index].numOfBooking++;
            }
        } else {
            cout << "start day must be less than end day";
        }
    }while (f);
}


void displayDate ( int d, int m , int y , date dateArray[]){
    
    static int i = 0;

        if (d > 0 && d < 28)    //checking for day from 0 to 27
            d += 1;
        if (d == 28)
        {
            if (m == 2)    //checking for february
            {
                if ((y % 400 == 0) || (y % 100 != 0 || y % 4 == 0))    //leap year check in case of feb
                {
                    d = 29;
                }
                else
                {
                    d = 1;
                    m = 3;
                }
            }
            else    //when its not feb
                d += 1;
        }
        if (d == 29)    //last day check for feb
        {
            if (m == 2)
            {
                d = 1;
                m += 1;
            }
            else
                d += 1;
        }
        if (d == 30)    //last day check for april,june,September,November
        {
            if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12)
                d += 1;
            else
            {
                d = 1;
                m += 1;
            }
        }
        if (d == 31)    //last day of the month
        {
            d = 1;
            if (m == 12)    //checking for last day of the year
            {
                y += 1;
                m = 1;
            }
            else
                m += 1;
        }

    dateArray[i].day = d;
    dateArray[i].month = m;
    dateArray[i].year = y;
    
    i++;
    
    if ( i < 14) {
        displayDate(d, m, y, dateArray);
        
    } else {
        i = 0;
        return ;
    }
}

// display Booking information
void display(booking *b, int numOfBooking ) {
    cout<<"\n_________Disblay booking Information:____________\n";

    
        cout<<"\tcostumer ID: "<<b[numOfBooking].costumerID<<endl;
        cout<<"\tBooking ID: "<<b[numOfBooking].bookingID<<endl;
        cout<<"\tSelected Car ID: " << b[numOfBooking].selectedCar << endl ;
        cout<<"\tStart Day: " << b[numOfBooking].startDay.day <<"\\"<<b[numOfBooking].startDay.month <<"\\" << b[numOfBooking].startDay.year << endl;
        cout<<"\tEnd Day: " << b[numOfBooking].endDay.day <<"\\" <<b[numOfBooking].endDay.month <<"\\"<< b[numOfBooking].endDay.year << endl;
        cout<<"\tperiod: "<<b[numOfBooking].period<<endl;
        cout<<"\tThe price: "<<b[numOfBooking].price << "SR."<<endl;
    
    return;
}

// display costomer information
void display( costumer *cost, int index ){
    cout<<"\n_________Disblay costumer Information:____________\n";

    
    cout<<"\tID : "<< cost[index].costumerID <<endl;
    cout<<"\tName : "<< cost[index].costumerName <<endl;
    cout<<"\tDate of Birth: "<< cost[index].dob.day << "\\" << cost[index].dob.month << "\\" << cost[index].dob.year <<endl;
    cout<<"\t... Has "<< cost[index].numOfBooking << " Booking. ... "<<endl;
    
    for ( int i = 0 ; i < cost[index].numOfBooking ; i++){
        cout << cost[index].bookingRecoredes[i]<< "\t";
    }
    cout << "\n\t............................\n";
    cout<<"\tDate of adding : "<< cost[index].dateOfadding << endl;
    cout<<"\tLast update : "<< cost[index].lastUpdate <<endl;
    
    
}

void disblayCarInfo(cars *car, int numOfitems){

    cout<<"________ cars Information:________"<<endl;
    cout.precision(5);
    cout << showpoint;
    cout.width(5);
    cout << "ID" << " ";
    cout.width(20);
    cout << "name" << " ";
    cout.width(20);
    cout << "brand" << " ";
    cout.width(20);
    cout << "color" << " ";
    cout.width(15);
    cout << "year Of Manufacture" <<" ";
    cout.width(15);
    cout << "cost per day" << endl;
    
    
    for(int i=0;i<numOfitems;i++){

        
        cout.precision(3);
        cout << showpoint;
        cout.width(5);
        cout << car[i].carId << " ";
        cout.width(20);
        cout << car[i].name << " ";
        cout.width(20);
        cout << car[i].brand << " ";
        cout.width(20);
        cout << car[i].color << " ";
        cout.width(15);
        cout << car[i].yearOfManufacture.year << " ";
        cout.width(15);
        cout << car[i].PricePerDay << endl;
        
    }
}

void updateCostumerInfo(costumer *s, int index){
    int choice, d , m , y;
    bool dateFlag;
    
    time_t now = time(0);
    tm* dt = localtime(&now);
    
    
    cout<<"________update costumer Information:________"<<endl;
    cout << "1. update name\t2. update date of birth : " ;
    cin >> choice;

    string Fname , Sname;
    switch (choice) {
        case 1:
            cout<<"Enter costumer name ";
            cin >> Fname >> Sname ;
            s[index].costumerName = Fname +" "+Sname;
            
            // update lastUpdate date
            s[index].lastUpdate = to_string((dt->tm_mday));
            s[index].lastUpdate += "\\";
            s[index].lastUpdate += to_string((dt->tm_mon)+1);
            s[index].lastUpdate += "\\";
            s[index].lastUpdate += to_string((dt->tm_year)+1900);
            break;
            
        case 2:
            
            do {
                dateFlag = false;
                
            // get date of birth
            cout<<">> Enter Date Of Birth for the costumer (day \ month \ year) ";
            cin >> d >>  m >>  y ;
                
            // check if the date is correct
            // check if the costumer is greater than 18 years
            if ( d < 31 && d > 0 ){
                s[index].dob.day = d;
                
            }else{
                dateFlag = true;
                cout << "\nday must be between 1 and 31\n";
            }
            
            
            if ( m  <= 12 && m >= 1){
                s[index].dob.month = m;
                
            } else {
                dateFlag = true;
                cout << "\nMonth must be between 1 and 12\n";
            }
            
            if ( y < (((dt->tm_year)+1900) - 18) && y > 0 ){
                s[index].dob.year = y;
            } else {
                dateFlag = true;
                cout << "\nAge must be greater than 18 years.\n";
            }
            
            } while ( dateFlag );
            
            
            // update lastUpdate date
            s[index].lastUpdate = to_string((dt->tm_mday));
            s[index].lastUpdate += "\\";
            s[index].lastUpdate += to_string((dt->tm_mon)+1);
            s[index].lastUpdate += "\\";
            s[index].lastUpdate += to_string((dt->tm_year)+1900);
            
            break;
            
        default:
            cout <<"invalid input\n";
            break;
    }
cout<<"\n...Costumer inforamation has been updated successfully..."<<endl;
}

// sort costumer array by cosyumer ID number
void sortCustomers(costumer * arr, int numOfItem)
{
    costumer temp;
    for (int i = 0; i < numOfItem - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < numOfItem; j++)
        {
            if (arr[j].costumerID < arr[min].costumerID)
            {
                min = j;
            }
        }
        
        //swap
        temp = arr[min];
        arr[min] = arr[i];
        arr[i] = temp;
    }
}

void deletebooking(booking * arr, int& bookingNOI, costumer *cost ,cars *car, int numOfCars, int &numOfB , int &BCindex, int index,  int Bindex)
{
    // check ID
    if (Bindex < 0 || Bindex >= bookingNOI)
    {
        cout << "Invalid booking index" << endl;
        return;
    }
    
    // delete date in car array
    int scar = arr[Bindex].selectedCar;
    for ( int i = 0 ; i < car[scar].numOfbookedDays;i++){// search loop
        if ( arr[Bindex].startDay.day ==  car[scar].NotAvilableDate[i].day && arr[Bindex].startDay.month ==  car[scar].NotAvilableDate[i].month && arr[Bindex].startDay.year ==  car[scar].NotAvilableDate[i].year){
            
            // delete all dates between start and end day.
            for ( int j = 0 ; j < arr[Bindex].period ; j++){
                for ( int k = i ; k < car[scar].numOfbookedDays; k++){
                car[scar].NotAvilableDate[k].day = car[scar].NotAvilableDate[k+1].day;
                car[scar].NotAvilableDate[k].month = car[scar].NotAvilableDate[k+1].month;
                car[scar].NotAvilableDate[k].year = car[scar].NotAvilableDate[k+1].year;
            }
                car[scar].numOfbookedDays--;
            }
            break;
        }
    }

    
    // delete booking id from costumer

    for (int i = BCindex ; i <  cost[index].numOfBooking ; i++){
        cost[index].bookingRecoredes[i] = cost[index].bookingRecoredes[i+1];
    }
    cost[index].numOfBooking--;
    
    
    
    // detete the booking from book array
    for (int i = Bindex; i < bookingNOI; i++)
    {
        arr[i] = arr[i + 1];
    }
    bookingNOI--;
    
    cout << "\n...Booking inforamation has been deleted successfully..." << endl;
    return;
}


void inFiles( costumer * cost, int &numberOfItems, int size,  booking *BookingArr, int &bookingNumOf, cars * carsArr, int &carsNumOfItem ){
  
    
    // create input files for costumer array
    ifstream inCostFile;
    
    
    // create input files for booking array
    ifstream inBookFile;

    
    // create input files for cars array
    ifstream inCarsFile;
 
    // open files costumer
    inCostFile.open("cost.txt");
    
    
    // open files booking
    inBookFile.open("/Users/maimonah_s/Desktop/cs/CS221/cs221Project/cs221Project/Book.txt");
//    outBookFile.open("Book.txt");
//
//    outBookFile << 0 << "\n";
//
//    outBookFile.close();

    // open files cars
    inCarsFile.open("/Users/maimonah_s/Desktop/cs/CS221/cs221Project/cs221Project/Car.txt");
    
    
    int s ;
    if ( inCostFile.is_open() == true &&  inCostFile.eof() == false ){
        inCostFile >> s;

        for ( int i = 0 ; i < s  ; i++ ){
            inCostFile.ignore(1);
            getline(inCostFile,cost[i].costumerID,'#');
//            cout << "costumerID: " << cost[i].costumerID << endl;
            
            getline(inCostFile,cost[i].costumerName,'#');
//            cout << "costumerName: " << cost[i].costumerName << endl;
            
            inCostFile >> cost[i].dob.day >> cost[i].dob.month >> cost[i].dob.year;
//            cout << cost[i].dob.day << cost[i].dob.month <<  cost[i].dob.year;
            
            inCostFile.ignore(1);
            inCostFile >> cost[i].numOfBooking;
//            cout << "numOfBooking: " << cost[i].numOfBooking << endl;
            inCostFile.ignore(1);
            
            for ( int j = 0 ; j < cost[i].numOfBooking ;j++){
                
                getline(inCostFile,cost[i].bookingRecoredes[j], '#') ;
//                cout <<  cost[i].bookingRecoredes[j] << "\t";
            }
            inCostFile.ignore(1);
            getline(inCostFile,cost[i].dateOfadding,'#');
//            cout << "\ncost[i].dateOfadding: " << cost[i].dateOfadding << endl;
            getline(inCostFile,cost[i].lastUpdate,'#');
//            cout << "cost[i].lastUpdate: " << cost[i].lastUpdate << endl;
            
            numberOfItems++;

        }

        inCostFile.close();
        

        inBookFile >> s;
    
        
            for ( int i = bookingNumOf ; i < s  ; i++ ){
                inBookFile.ignore(1);
                getline(inBookFile,BookingArr[i].bookingID, '#');
//                cout << "\nBookingArr[i].bookingID " << BookingArr[i].bookingID;
                getline(inBookFile,BookingArr[i].costumerID, '#');
//                cout << "\nBookingArr[i].costumerID " << BookingArr[i].costumerID;
                inBookFile >> BookingArr[i].selectedCar;
//                cout << "\nBookingArr[i].selectedCar " << BookingArr[i].selectedCar;
                inBookFile.ignore(1);
                inBookFile >> BookingArr[i].startDay.day >> BookingArr[i].startDay.month >> BookingArr[i].startDay.year;
                inBookFile.ignore(1);
                inBookFile >> BookingArr[i].endDay.day >> BookingArr[i].endDay.month >> BookingArr[i].endDay.year;
                inBookFile.ignore(1);
                inBookFile >> BookingArr[i].period;
//                cout << "\nBookingArr[i].period " << BookingArr[i].period;
                inBookFile.ignore(1);
                inBookFile >> BookingArr[i].price;
//                cout << "\nBookingArr[i].price " << BookingArr[i].price;
                
                inBookFile.ignore(1);
                inBookFile >> BookingArr[i].dateOfAdding.day;
                inBookFile.ignore(1);
                inBookFile >> BookingArr[i].dateOfAdding.month;
                inBookFile.ignore(1);
                inBookFile >> BookingArr[i].dateOfAdding.year;
                
//                cout << "\ndateOfAdding " <<BookingArr[i].dateOfAdding.day << " "<<  BookingArr[i].dateOfAdding.month <<" "<<  BookingArr[i].dateOfAdding.year;

                inBookFile.ignore(1);
                inBookFile >>BookingArr[i].lastUpdate.day;
                inBookFile.ignore(1);
                inBookFile >> BookingArr[i].lastUpdate.month;
                inBookFile.ignore(1);
                inBookFile >>BookingArr[i].lastUpdate.year;
                inBookFile.ignore(1);
                
//                cout << "\nlastUpdate " << BookingArr[i].lastUpdate.day << " "<<  BookingArr[i].lastUpdate.month << " "<<  BookingArr[i].lastUpdate.year;
                bookingNumOf++;

            }
//        cout << "numberOfBooking....: " << bookingNumOf <<endl;
        inBookFile.close();
        string year, temp;
        s= 0;
            inCarsFile >> s;
//                cout << "\ns= " << s  <<endl;
//            cout <<  "Cars file is open succsessfully" << endl;
            for ( int i = 0 ; i < s   ; i++ ){
                carsArr[i].carId = i;
                inCarsFile.ignore(1);
                getline(inCarsFile, carsArr[i].name ,'#');
                getline(inCarsFile,carsArr[i].brand, '#');
                getline(inCarsFile,carsArr[i].color, '#');
//                cout << "\ncarsArr[i].colo: " << carsArr[i].color << endl;
                inCarsFile >> carsArr[i].yearOfManufacture.year ;
//                cout << "yearOfManufacture.year: " << carsArr[i].yearOfManufacture.year << endl;
                inCarsFile.ignore(1);
                inCarsFile >> carsArr[i].PricePerDay;
//                cout << "PricePerDay: " << carsArr[i].PricePerDay << endl;
                inCarsFile.ignore(1);
                inCarsFile >> carsArr[i].numOfbookedDays;
//                cout << "numOfbookedDays: " << carsArr[i].numOfbookedDays << endl;
                inCarsFile.ignore(1);
                for ( int j = 0  ; j < carsArr[i].numOfbookedDays ; j++ ){
                    inCarsFile >> carsArr[i].NotAvilableDate[j].day;
//                    cout << "\nNotAvilableDate[j].day: " <<carsArr[i].NotAvilableDate[j].day;
                    inCarsFile >> carsArr[i].NotAvilableDate[j].month;
//                    cout << "\tNotAvilableDate[j].month: " <<carsArr[i].NotAvilableDate[j].month;
                    inCarsFile >> carsArr[i].NotAvilableDate[j].year;
//                    cout << "\tNotAvilableDate[j].year: " <<carsArr[i].NotAvilableDate[j].year;
                    inCarsFile.ignore(1);
                }
                carsNumOfItem++;
            }
//        cout << "numberOfBooking: " << bookingNumOf <<endl;

        inCarsFile.close();
    }

}


void outFiles( costumer * cost, int &numberOfItems, int size,  booking *BookingArr, int &bookingNumOf, cars * carsArr, int &carsNumOfItem ){
  
    
    // create output file for costumer array
    ofstream outCostFile;

    // create output file for booking array
    ofstream outBookFile;
    
    // create output file for cars array
    ofstream outCarsFile;

    // open files costumer

    outCostFile.open("/Users/maimonah_s/Desktop/cs/CS221/cs221Project/cs221Project/cost.txt");
    
    // open files booking
    outBookFile.open("/Users/maimonah_s/Desktop/cs/CS221/cs221Project/cs221Project/Book.txt");
    
    // open files cars
    outCarsFile.open("/Users/maimonah_s/Desktop/cs/CS221/cs221Project/cs221Project/Car.txt");
    
//
//    cout << "numberOfItems++ " << numberOfItems;
    if ( outCostFile.is_open() == true && outBookFile.is_open() == true && outCarsFile.is_open() ==true ){
      
//        cout <<  "File is open succsessfully" << endl;
        outCostFile << numberOfItems;
        for ( int i = 0 ; i < numberOfItems  ; i++ ){
            
            outCostFile <<"\n";
            outCostFile << cost[i].costumerID << "#";
            outCostFile << cost[i].costumerName << "#";
            outCostFile << cost[i].dob.day << " " << cost[i].dob.month  << " " << cost[i].dob.year << "#";
            outCostFile << cost[i].numOfBooking << "#";
            for ( int j = 0 ; j < cost[i].numOfBooking ; j++ ){
                outCostFile << cost[i].bookingRecoredes[j] << "#";
            }
            outCostFile << "#";
            outCostFile << cost[i].dateOfadding << "#";
            outCostFile << cost[i].lastUpdate << "#";
            
        }
        
        outCostFile.close();
        outBookFile << bookingNumOf; //bookingNumOf;
//            cout <<  "Book file is open succsessfully" << endl;
            for ( int i = 0 ; i < bookingNumOf ; i++ ){
                outBookFile << "\n";
                outBookFile << BookingArr[i].bookingID << "#";
                outBookFile << BookingArr[i].costumerID << "#";
                outBookFile << BookingArr[i].selectedCar << "#";
                outBookFile << BookingArr[i].startDay.day << " " << BookingArr[i].startDay.month << " " << BookingArr[i].startDay.year << "#";
                outBookFile <<  BookingArr[i].endDay.day << " " << BookingArr[i].endDay.month << " " << BookingArr[i].endDay.year << "#";
                outBookFile << BookingArr[i].period << "#";
                outBookFile << BookingArr[i].price<< "#";
                outBookFile << BookingArr[i].dateOfAdding.day << "\\" <<BookingArr[i].dateOfAdding.month << "\\" <<BookingArr[i].dateOfAdding.year<< "#";
                outBookFile <<  BookingArr[i].lastUpdate.day << "\\" <<BookingArr[i].lastUpdate.month << "\\" <<BookingArr[i].lastUpdate.year<< "#";

            }
        
        outBookFile.close();
        outCarsFile << carsNumOfItem;
//            cout <<  "Cars file is open succsessfully" << endl;
            for ( int i = 0 ; i < carsNumOfItem    ; i++ ){
                outCarsFile <<"\n";
                outCarsFile <<  carsArr[i].name << "#";
                outCarsFile <<  carsArr[i].brand << "#";
                outCarsFile <<  carsArr[i].color << "#";
                outCarsFile <<  carsArr[i].yearOfManufacture.year << "#";
                outCarsFile <<  carsArr[i].PricePerDay << "#";
                outCarsFile <<  carsArr[i].numOfbookedDays << "#";

                for ( int j = 0  ; j < carsArr[i].numOfbookedDays ; j++ ){
                    outCarsFile << carsArr[i].NotAvilableDate[j].day <<" ";
                    outCarsFile << carsArr[i].NotAvilableDate[j].month << " ";
                    outCarsFile <<  carsArr[i].NotAvilableDate[j].year << "#";
                }

            }
        outCarsFile.close();
    }

}


void reportFile( costumer *cost , int index , int Func){
    
    
    time_t my_time = time(NULL);
    
    // create report file
    ofstream reportOutFile;
    
    //open report File
    reportOutFile.open("/Users/maimonah_s/Desktop/cs/CS221/cs221Project/cs221Project/Report.txt", ios::app);
    
    // write the report according to the operator
    if ( reportOutFile.is_open()){
        if ( Func == 1 ) { // add new costumer
            reportOutFile << "\nNew costumer added at :  " <<  ctime(&my_time) ;
            reportOutFile << "\nCostumer ID: " << cost[index-1].costumerID << endl ;
            reportOutFile << "\n........................" ;
        } else if ( Func == 2){ // entered to the system
            reportOutFile << "\nCostumer With ID " << cost[index].costumerID << " Entered at " <<  ctime(&my_time) << "\n";
        }else if ( Func == 3 ){ // add new booking
            reportOutFile << "\nAdded new booking successfully.";
        }else if ( Func == 4){ // update
            reportOutFile << "\nUpdated costumer information successfully." ;
        }else if ( Func == 5){ // delete
            reportOutFile << "\nDeleted Booking successfully." ;
        }else if ( Func == 6){ // log out
            reportOutFile << "\n\nCostumer With ID " << cost[index].costumerID << " Log out at " <<  ctime(&my_time);
            reportOutFile << "\n........................" ;
        }else {
            reportOutFile << "Error in data";
        }
    
    }
    reportOutFile.close();
    
}


