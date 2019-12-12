//
//  main.cpp
//  Estimator
//
//  Created by Matt Wheatley on 11/5/19.
//  Copyright © 2019 Matt Wheatley. All rights reserved.
//

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>


int menuSelection = 0;

// Functions
int straightBase(int menuSelection);
int coveBase(int menuSelection);
int treadRiser(int menuSelection);
int treadOnly(int menuSelection);
int slab(int menuSelection);
int calculateSQFT(int length, int width);
int calculateNumBasePieces(int length);
int calculateNumMixesCoveBase(int linealFeet);
int calculateNumMixesStraightBase(int linealFeet);
int optionalToeStrip(int numBasePieces);
int calculatePriceOfStrBase(int numBasePieces);
int calculatePriceOfCoveBase(int numBasePieces);
int printMenu();
void openScreen();
int calcEpoxy(int numMixes);
int priceFiller(int numMixes);
int priceGrout(int sqft);
int calculateTotal();



// Variables
int thickness = 0;
int length = 0;
int width = 0;
int sqft = 0;
int linealFeet = 0;
int numBasePieces = 0;
int baseLength = 4;
int numMixes = 0;
int fourInchStraightPoured = 108;
int fourInchCovePoured = 84;
int sixInchStraightPoured = 72;
int sixInchCovePoured = 54;
int baseHeight = 0;
double priceOfEpoxy = 25.50;
double priceOfFiller = 11.10;
double priceOfGrout = 23.50;
double priceOfChips = 25.00;
double priceOfToeStrip = 2.20;
double priceOfStraightBase = 10.96;
double priceOfCoveBase = 13.15;
double pricePerSQFT = 38.26;
double chipsTotal = 0.00;
double totalPriceOfToeStrip = 0.00;
int chipsRequired = 180;  // # per mix


// FUNCTION TO CREATE A USER PROGILE
void createProfile()
{
    std::string username;
    std::string password;
    std::ofstream newAccount("accounts.txt", std::ios::app);
    std::cout << "Enter new username:" << std::endl;
    std::cin >> username;
    std::cout << "Enter new password:" << std::endl;
    std::cin >> password;
    newAccount << username << ' ' << password << std::endl;
    newAccount.close();
    openScreen();
}




// FUNCTION TO LOGIN
void login()
{
    std::ifstream user("accounts.txt");
    std::string username;
    std::string password;
    std::string strUser;
    std::string strPassword;
    std::cout << "Enter username:" << std::endl;
    std::cin >> strUser;
    std::cout << "Enter password:" << std::endl;
    std::cin >> strPassword;
    while (user >> username >> password){
        if ((strUser == username) && (strPassword == password)){
            std::cout << "Login successful! Welcome " << username << "!" << std::endl;
            printMenu();
        }
        if ((strUser != username) && (strPassword != password))
        {
            std::cout << "Login failed. Goodbye" << std::endl;
            exit (0);
        }
    }
    
}




// OPEN MENU SCREEN TO ALLOW USER TO LOGIN OR CREATE A PROFILE
void openScreen()
{
    int choice = 0;
    std::cout << "1.) Login" << std::endl;
    std::cout << "2.) Create Account" << std::endl;
    std::cout << "3.) Quit" << std::endl;
    std::cout << "Enter your selection" << std::endl;
    std::cin >> choice;
    
    if (choice == 1){
        login();
    }
    else if (choice == 2){
        createProfile();
    }
    else if (choice == 3){
        std::cout << "Goodbye" << std::endl;
        exit(0);
    }
    else {
        std::cout << "Not a valid option. Try again." << std::endl;
        openScreen();
    }
    
}




// MAIN MENU TO CREATE ESTIMATES
int menu(int menuSelection)
{
    switch (menuSelection)
    {
        case 1:
            straightBase(menuSelection);
            break;
            
        case 2:
            coveBase(menuSelection);
            break;
            
        case 3:
            treadRiser(menuSelection);
            break;
            
        case 4:
            treadOnly(menuSelection);
            break;
            
        case 5:
            slab(menuSelection);
            break;
            
        case 6:
            std::cout << "Goodbye" << std::endl;
            break;
            
        default:
            std::cout << "Not a valid option. Please try again:" << std::endl;
    }
    return menuSelection;
}




// STRAIGHT BASE CALCULATIONS
int straightBase(int menuSelection)
{
    std::cout << "----------------------" << std::endl;
    std::cout << "Straight Base Quote\n";
    std::cout << "----------------------" << std::endl;
    calculateNumBasePieces(length);
    calculateNumMixesStraightBase(linealFeet);
    calcEpoxy(numMixes);
    priceFiller(numMixes);
    priceGrout(sqft);
    calculateTotal();
    return menuSelection;
}




// COVE BASE CALCULATIONS
int coveBase(int menuSelection)
{
    std::cout << "----------------------" << std::endl;
    std::cout << "Cove Base Quote\n";
    std::cout << "----------------------" << std::endl;
    calculateNumBasePieces(length);
    calculateNumMixesCoveBase(linealFeet);
    calcEpoxy(numMixes);
    priceFiller(numMixes);
    priceGrout(sqft);
    optionalToeStrip(numBasePieces);
    calculateTotal();
    return menuSelection;
}




// TREAD RISER COMBO CALCULATIONS
int treadRiser(int menuSelection)
{
    std::cout << "----------------------" << std::endl;
    std::cout << "Tread / Riser Combo Quote\n";
    std::cout << "----------------------" << std::endl;
    calculateSQFT(width, length);
    return menuSelection;
}




// TREAD ONLY CALCULATIONS
int treadOnly(int menuSelection)
{
    std::cout << "----------------------" << std::endl;
    std::cout << "Tread Only Quote\n";
    std::cout << "----------------------" << std::endl;
    calculateSQFT(width, length);
    return menuSelection;
}




// SLAB CALCULATIONS
int slab(int menuSelection)
{
    std::cout << "----------------------" << std::endl;
    std::cout << "Slab Quote\n";
    std::cout << "----------------------" << std::endl;
    calculateSQFT(width, length);
    return menuSelection;
}




// CALCULATE SQUARE FOOTAGE OF MATERIAL
int calculateSQFT(int width, int length)
{
    std::cout << "Enter length: ";
    std::cin >> length;
    std::cout << "Enter width: ";
    std::cin >> width;
    
    sqft = length * width;
    
    std::cout << "Total squarefootage: " << sqft << " sqft" << std::endl;
    return 0;
}




// CALCULATE THE TOTAL NUMBER OF BASE PIECES NEEDED FOR THE JOB
int calculateNumBasePieces(int length){
    std::cout << "Enter total length needed: ";
    std::cin >> linealFeet;
    numBasePieces = (linealFeet / baseLength) + 1;
    std::cout << "Number of pieces: " << numBasePieces << std::endl;
    return 0;
}




// CALCULATE THE NUMBER OF MIXES NEEDED FOR STRAIGHT BASE
int calculateNumMixesStraightBase(int linealFeet){
    std::cout << "What is the base height? (4 or 6) ";
    std::cin >> baseHeight;
    if (baseHeight == 4){
        numMixes = (linealFeet / fourInchStraightPoured) * 1.1 + 1;
        sqft = linealFeet * .33;
        std::cout << "Total square footage: " << sqft << std::endl;
        std::cout << "Number of mixes needed (with 10% extra): " << numMixes << std::endl;
        chipsRequired = numMixes * chipsRequired;
        std::cout << "Pounds of chips needed: " << chipsRequired << std::endl;
        chipsTotal = (chipsRequired / 50) * priceOfChips;
        std::cout << "Price of chips: $" << std::fixed << std::setprecision(2) << chipsTotal << std::endl;
    }
    else if(baseHeight == 6){
        numMixes = (linealFeet / sixInchStraightPoured) * 1.1 + 1;
        sqft = linealFeet * .5;
        std::cout << "Total square footage: " << sqft << std::endl;
        std::cout << "Number of mixes needed (with 10% extra): " << numMixes << std::endl;
        chipsRequired = numMixes * chipsRequired;
        std::cout << "Pounds of chips needed: " << chipsRequired << std::endl;
        chipsTotal = (chipsRequired / 50) * priceOfChips;
        std::cout << "Price of chips: $" << std::fixed << std::setprecision(2) << chipsTotal << std::endl;
    }
    else
    {
        std::cout << "That is not a valid option. Try again." << std::endl;
        calculateNumMixesStraightBase(linealFeet);
    }
    return 0;
}




// CALCULATE THE NUMBER OF MIXES NEEDED FOR COVE BASE
int calculateNumMixesCoveBase(int linealFeet){
    int sqft = 0;
    std::cout << "What is the base height? (4 or 6) ";
    std::cin >> baseHeight;
    if (baseHeight == 4){
        numMixes = (linealFeet / fourInchCovePoured) * 1.1 + 1;
        sqft = (linealFeet * .42) + 1;
        std::cout << "Total square footage: " << sqft << std::endl;
        std::cout << "Number of mixes needed (with 10% extra): " << numMixes << std::endl;
        chipsRequired = numMixes * chipsRequired;
        std::cout << "Pounds of chips needed: " << chipsRequired << std::endl;
        chipsTotal = (chipsRequired / 50) * priceOfChips;
        std::cout << "Price of chips: $" << std::fixed << std::setprecision(2) << chipsTotal << std::endl;
    }
    else if(baseHeight == 6){
        numMixes = (linealFeet / sixInchCovePoured) * 1.1 + 1;
        sqft = (linealFeet * .58333) + 1;
        std::cout << "Total square footage: " << sqft << std::endl;
        std::cout << "Number of mixes needed (with 10% extra): " << numMixes << std::endl;
        chipsRequired = numMixes * chipsRequired;
        std::cout << "Pounds of chips needed: " << chipsRequired << std::endl;
        chipsTotal = (chipsRequired / 50) * priceOfChips;
        std::cout << "Price of chips: $" << std::fixed << std::setprecision(2) << chipsTotal << std::endl;
    }
    else
    {
        std::cout << "That is not a valid option. Try again." << std::endl;
        calculateNumMixesCoveBase(linealFeet);
    }
    return 0;
}




// PRICE FILLER
int priceFiller(int numMixes) {
    priceOfFiller = priceOfFiller * numMixes;
    std::cout << "Number of bags of filler: " << numMixes << std::endl;
    std::cout << "Price of filler: $" << std::fixed << std::setprecision(2) << priceOfFiller << std::endl;
    return 0;
}




// DETERMINE IF THE STRAIGHT BASE WILL HAVE A TOE STRIP
int optionalToeStrip(int numBasePieces){
    char toeStrip = 'n';
    std::cout << "Will the cove base have toe strip?(Y/N) ";
    std::cin >> toeStrip;
    if((toeStrip == 'Y') || (toeStrip =='y')){
        totalPriceOfToeStrip = numBasePieces * priceOfToeStrip;
        std::cout << "The price of the toe strip will be: $" << totalPriceOfToeStrip << std::endl;
    }
    else if((toeStrip == 'N') || (toeStrip =='n')){
        std::cout << "There are no extra fees added to the cost for toe strip." << std::endl;
    }
    else{
        std::cout << "Not a valid option. Try again." << std::endl;
        optionalToeStrip(numBasePieces);
    }
    return 0;
}




// PRICE GROUT
int priceGrout(int sqft){
    int totalGrout = 0;
    totalGrout = (sqft / 1000) + 1;
    std::cout << "Total grout needed: " << totalGrout << std::endl;
    
    priceOfGrout = totalGrout * 23.50;
    
    std::cout << "Total price of grout: $" << priceOfGrout << std::endl;
    return 0;
}


// CALCULATE PRICE OF TREAD RISER





// CALCULATE TOTAL PRICE
int calculateTotal (){
    double total = 0;
    double costBeforeProfit = 0.00;
    double profit = 0.00;
    double tax = 0.06;
    std::cout << "" << std::endl;
    std::cout << "What is the profit percentage: ";
    std::cin >> profit;
    costBeforeProfit = (chipsTotal + priceOfEpoxy + priceOfFiller + priceOfGrout + totalPriceOfToeStrip);
    std::cout << " " << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << "       WRAP UP"         << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << "Cost before profit: $" << std::fixed << std::setprecision(2) << costBeforeProfit << std::endl;
    profit = costBeforeProfit * profit;
    std::cout << "Profit: $" << std::fixed << std::setprecision(2) << profit << std::endl;
    tax = (costBeforeProfit + profit) * tax;
    std::cout << "Tax: $" << std::fixed << std::setprecision(2) << tax << std::endl;
    total = costBeforeProfit + profit + tax;
    std::cout << "Total cost: $" << std::fixed << std::setprecision(2) << total << std::endl;
    std::cout << "----------------------\n" << std::endl;
    return 0;
}



// CALCULATE AMOUNT OF EPOXY NEEDED
int calcEpoxy (int numMixes){
    int totalEpoxy = 0;
    totalEpoxy = (numMixes * 6) + 1;
    priceOfEpoxy = priceOfEpoxy * totalEpoxy;
    std::cout << "Total number of gallons of epoxy: " << totalEpoxy << std::endl;
    std::cout << "Total price of epoxy: $" << std::fixed << std::setprecision(2) << priceOfEpoxy << std::endl;
    return 0;
}




// PRINT MAIN MENU
int printMenu()
{
    bool keepLooping = true;
    
    while (keepLooping)
    {
        std::cout << "*** ESTIMATOR ***" << std::endl;
        std::cout << "----------------------\n" << std::endl;
        std::cout << "Pick an option to quote from the menu below:" << std::endl;
        std::cout << "1. Quote straight base" << std::endl;
        std::cout << "2. Quote cove base" << std::endl;
        std::cout << "3. Quote tread/riser combo" << std::endl;
        std::cout << "4. Quote tread only" << std::endl;
        std::cout << "5. Quote slabs" << std::endl;
        std::cout << "6. Quit" << std::endl;
        std::cin >> menuSelection;
            
        menu(menuSelection);

        if (menuSelection < 1 || menuSelection > 6)
        {
            keepLooping = true;
        }
        else
        {
            keepLooping = false;
        }
    }
    return 0;
}





int main(){
        
openScreen();
    

}

