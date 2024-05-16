#include <iomanip> // for input/output manipulation
#include <string> // for string
#include <fstream> // for file handling
#include <cmath> // for math functions

#include "Discount.h" // Include the header file that contains the declaration of the Discount class.
#include "Employee.h" // Include the header file that contains the declaration of the Employee class.

const int MAX_BAKERY_ITEMS = Constant::MAX_BAKERY_ITEMS; // Maximum number of bakery items.
const int MAX_INGREDIENTS_INVENTORY = Constant::MAX_INGREDIENTS_INVENTORY; // Maximum number of ingredients in the inventory.

/**
 * @file Employee.cpp
 * @brief Implementation file for the Employee class.
 */

/**
 * @class Employee
 * @brief Represents an employee of the bakery.
 */

/**
 * @brief Default constructor for the Employee class.
 * 
 * This constructor initializes the employee ID, name, role, and password to empty strings.
 * 
 */
Employee::Employee() {
  employeeID = "";
  name = "";
  role = "";
  password = "";
}

/**
 * @brief Constructs an Employee object with the given employee ID, name, role, and password.
 * 
 * @param employeeID The ID of the employee.
 * @param name The name of the employee.
 * @param role The role of the employee.
 * @param password The password of the employee.
 * 
 * @return None.
 */
Employee::Employee(string employeeID, string name, string role, string password) {
  // Check if the employee ID is empty.
  if (employeeID == "") {
    cout << "Employee ID cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if the name is empty.
  if (name == "") {
    cout << "Name cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if the role is empty.
  if (role == "") {
    cout << "Position cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }

  // Check if the password is empty.
  if (password == "") {
    cout << "Password cannot be empty." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
    return;
  }
  
  // Set the employee ID, name, role, and password.
  this->employeeID = employeeID;
  this->name = name;
  this->role = role;
  this->password = password;

  // Initialize the supervisor, baker, and cashier pointers according to the role.
  if (role == "Supervisor") {
    supervisor = new Supervisor(employeeID, name);
  } else if (role == "Baker") {
    baker = new Baker(employeeID, name);
  } else {
    cashier = new Cashier(employeeID, name);
  }

  // cout << role << " '" << name << "' has been added." << endl;
}

/**
 * @brief Displays the details of the employee.
 * 
 * @param None.
 * @return None.
 */
void Employee::displayEmployeeDetails() const {
  cout << "Employee ID: " << employeeID << endl;
  cout << "Name: " << name << endl;
  cout << "Position: " << role << endl;
}

/**
 * @brief Logs in the employee with the given employee ID and password.
 * 
 * @param employeeID The ID of the employee.
 * @param password The password of the employee.
 * 
 * @return True if the login is successful, false otherwise.
 */
bool Employee::login(string employeeID, string password) {
  cout << "Logging in..." << endl;

  // Check if the employee ID and password match.
  if (this->employeeID == employeeID && this->password == password) {
    cout << "Login successful !" << endl;
    return true;
  } else {
    cout << "Login failed." << endl;
    return false;
  }
}

/**
 * @brief Sets the ingredient cost of each bakery item to the corresponding ingredient cost in the inventory.
 * 
 * This function iterates through each bakery item and its ingredients, and checks if the ingredient exists in the inventory.
 * If a match is found, the ingredient cost of the bakery item is set to the corresponding ingredient cost in the inventory.
 * 
 * @param None.
 * @return None.
 */
void Employee::setIngredientCostToInventoryIngredientCost() {
  cout << role << " - Setting ingredient cost to inventory ingredient cost..." << endl;

  // Iterate through each bakery item.
  for (int i = 0; i < bakeryItems[0].getBakeryItemCount(); i++) {
    // Iterate through each ingredient of the bakery item.
    for (int j = 0; j < bakeryItems[i].getIngredientCount(); j++) {
      // Iterate through each ingredient in the inventory.
      for (int k = 0; k < ingredientInventory[0].getIngredientInventoryCount(); k++) {
        // Check if the ingredient in the bakery item matches the ingredient in the inventory.
        if(bakeryItems[i].getIngredient(j)->getName() == ingredientInventory[k].getIngredient().getName()) {
          // cout << "Ingredient " << bakeryItems[i].getIngredient(j)->getName() << "'s cost of " << bakeryItems[i].getBakeryItemName() << " has been set to RM " << ingredientInventory->getIngredientInventoryCost(k) << endl;

          // Set the ingredient cost of the bakery item to the corresponding ingredient cost in the inventory.
          bakeryItems[i].getIngredient(j)->setCostPerUnit(ingredientInventory->getIngredientInventoryCost(k));
        }
      }
    }
  }
}

/**
 * @brief Starts the bakery operation.
 * 
 * @param date The date of the bakery operation.
 * @return void
 */
void Employee::startBakery(string date) {
  cout << "Bakery start operating now." << endl;
  cout << endl;

  orderNo = 0;
  
  // Fetch the total balance from files/balanceSheet.csv last row last column
  ifstream balanceSheetFile; // Input file stream for the balance sheet file
  balanceSheetFile.open("files/balanceSheet.csv"); // Open the balance sheet file in input mode
  string line; // String to store each line of the file
  string lastLine; // String to store the last line of the file
  while (getline(balanceSheetFile, line)) {
    lastLine = line;
  }
  balanceSheetFile.close();

  // Extract data from last line
  string dateString = lastLine.substr(0, lastLine.find(","));
  string debitString = lastLine.substr(lastLine.find(",") + 1, lastLine.find(",", lastLine.find(",") + 1) - lastLine.find(",") - 1);
  string creditString = lastLine.substr(lastLine.find(",", lastLine.find(",") + 1) + 1, lastLine.find(",", lastLine.find(",", lastLine.find(",") + 1) + 1) - lastLine.find(",", lastLine.find(",") + 1) - 1);
  string balanceString = lastLine.substr(lastLine.find(",", lastLine.find(",", lastLine.find(",") + 1) + 1) + 1);

  // Check if dateString is the same as today's date
  // If it is, set totalDebit, totalCredit, totalBalance to the values in the last line
  // If it is not, set totalDebit, totalCredit to 0
  if (dateString == date) {
    // Set total debit and total credit
    totalDebit = stod(debitString);
    totalCredit = stod(creditString);

    // Delete last line from balanceSheet.csv
    ifstream balanceSheetFile;
    balanceSheetFile.open("files/balanceSheet.csv");
    string tempLines;
    string line;
    while (getline(balanceSheetFile, line)) {
      if (line != lastLine) {
        tempLines += line + "\n";
      }
    }
    balanceSheetFile.close();

    ofstream balanceSheetFileWrite;
    balanceSheetFileWrite.open("files/balanceSheet.csv");
    // Remove last \n from tempLines
    tempLines = tempLines.substr(0, tempLines.length() - 1);
    balanceSheetFileWrite << tempLines;
    balanceSheetFileWrite.close();

    // Read balance from balanceSheet.csv
    // Extract data from last line after confirming last line is previous date
    balanceSheetFile.open("files/balanceSheet.csv");
    while (getline(balanceSheetFile, line)) {
      lastLine = line;
    }
    balanceSheetFile.close();

    balanceString = lastLine.substr(lastLine.find(",", lastLine.find(",", lastLine.find(",") + 1) + 1) + 1);

    // Startup balance
    if (balanceString == "balance") {
      balanceString = "5000.0";
    }

  } else {
    totalDebit = 0;
    totalCredit = 0;
  }

  // Set total balance
  totalBalance = stod(balanceString);
  cout << "Starting balance: RM " << balanceString << endl;
  cout << "Starting debit: RM " << totalDebit << endl;
  cout << "Starting credit: RM " << totalCredit << endl;
  cout << endl;

  // Fetch ingredient inventory from files/ingredientInventory.csv
  ifstream ingredientInventoryFile; // Input file stream for the ingredient inventory file
  ingredientInventoryFile.open("files/ingredientInventory.csv"); // Open the ingredient inventory file in input mode
  cout << endl;

  cout << "Reading ingredient inventory file..." << endl;
  string ingredientInventoryLine; // String to store each line of the file
  string ingredInvName; // String to store the name of the ingredient in the inventory
  double ingredInvCost; // Double to store the cost of the ingredient in the inventory
  double ingredInvWeight; // Double to store the weight of the ingredient in the inventory
  int ingredInvPiece; // Integer to store the piece of the ingredient in the inventory
  bool ingredInvCountable; // Boolean to store the countable status of the ingredient in the inventory
  int ingredInvCount = 0; // Integer to store the count of ingredients in the inventory

  getline(ingredientInventoryFile, ingredientInventoryLine); // skip first line (header)
  while (getline(ingredientInventoryFile, ingredInvName, ',')) {
    getline(ingredientInventoryFile, ingredientInventoryLine, ',');
    ingredInvCost = stod(ingredientInventoryLine);
    getline(ingredientInventoryFile, ingredientInventoryLine, ',');
    ingredInvWeight = stod(ingredientInventoryLine);
    getline(ingredientInventoryFile, ingredientInventoryLine, ',');
    ingredInvPiece = stoi(ingredientInventoryLine);
    getline(ingredientInventoryFile, ingredientInventoryLine);
    ingredInvCountable = (ingredientInventoryLine == "true");

    // check if ingredient name is empty
    if (ingredInvName != "") {
      // cout << "Ingredient '" << ingredInvName << "' has been added." << endl;
      // check if ingredient is countable or not
      if (ingredInvCountable) {
        ingredientInventory[ingredInvCount] = IngredientInventory(ingredInvName, ingredInvCost, ingredInvPiece);
      } else {
        ingredientInventory[ingredInvCount] = IngredientInventory(ingredInvName, ingredInvCost, ingredInvWeight);
      }

      // increment ingredient inventory count
      ingredInvCount++;
    }
  }
  ingredientInventoryFile.close();
  cout << "Ingredient inventory count: " << ingredInvCount << endl;

  // Set bakery items to the bakery items array
  bakeryItems->setBakeryItems(bakeryItems);

  // Array of ingredients for each bakery item
  Ingredient * ingredients;

  // Fetch bakery items (cake)
  // Read from file/cake.csv
  ifstream cakeFile; // Input file stream for the bakery item file
  cakeFile.open("files/cake.csv"); // Open the bakery item file in input mode
  cout << endl;

  cout << "Reading cake file..." << endl;
  string cakeLine; // String to store each line of the file
  string cakeName; // String to store the name of the cake
  string cakeDescription; // String to store the description of the cake
  double cakePricePerUnit; // Double to store the price per unit of the cake
  string cakeIngredients; // String to store the ingredients of the cake
  string cakeRecipe; // String to store the recipe of the cake
  bool cakeDisabled; // Boolean to store the disabled status of the cake
  int cakeTotalWeight; // Integer to store the total weight of the cake
  int ingredientCount; // Integer to store the count of ingredients
  int bakeryItemCount = 0; // Integer to store the count of bakery items
  string temp; // Temporary string to store the ingredients

  getline(cakeFile, cakeLine); // skip first line (header)
  while (!cakeFile.eof()) {
    ingredientCount = 0; // Reset the ingredient count

    // name
    getline(cakeFile, cakeName, ',');

    // description
    getline(cakeFile, cakeLine, '"');
    getline(cakeFile, cakeDescription, '"');

    // price per unit
    getline(cakeFile, cakeLine, ',');
    getline(cakeFile, cakeLine, ',');
    cakePricePerUnit = stod(cakeLine);

    // ingredients
    getline(cakeFile, cakeLine, '"');
    getline(cakeFile, cakeLine, '"');

    // count number of ingredients
    for (int i = 0; i < cakeLine.length(); i++) {
      if (cakeLine[i] == ';') {
        ingredientCount++;
      }
    }

    // create ingredients array
    ingredients = new Ingredient[ingredientCount]; // Array of ingredients for the bakery item
    int ingredientIndex = 0; // Index of the ingredient
    
    // iterate through ingredients
    for (int i = 0; i < cakeLine.length(); i++) {
      // check if it is the end of an ingredient
      if (cakeLine[i] == ';') {
        string ingredientName = temp.substr(0, temp.find(",")); // Extract the name of the ingredient

        string ingredientWeightString = temp.substr(temp.find(",") + 1); // Extract the weight of the ingredient
        double ingredientWeight = stod(ingredientWeightString); // Convert the weight to a double

        // check if ingredient is countable or not
        bool countable = false; // Flag of boolean to store if the ingredient is countable
        // check if ingredientWeightString has decimal
        if (ingredientWeightString.find(".") != string::npos) {
          countable = false;
        } else {
          countable = true;
        }

        string ingredientPieceString = temp.substr(temp.find(",") + 1); // Extract the piece of the ingredient
        int ingredientPiece = stoi(ingredientPieceString); // Convert the piece to an integer

        // check if ingredient is countable or not
        if (countable) {
          ingredients[ingredientIndex] = Ingredient(ingredientName, 0, ingredientPiece);
        } else {
          ingredients[ingredientIndex] = Ingredient(ingredientName, 0, ingredientWeight);
        }

        // increment ingredient index
        ingredientIndex++;
        temp = "";
      } else {
        temp += cakeLine[i];
      }
    }

    // recipe
    getline(cakeFile, cakeLine, '"');
    getline(cakeFile, cakeRecipe, '"');
    
    // disabled
    getline(cakeFile, cakeLine, ',');
    getline(cakeFile, cakeLine, ',');
    cakeDisabled = (cakeLine == "true");

    // total weight
    getline(cakeFile, cakeLine);
    cakeTotalWeight = stoi(cakeLine);

    // add to bakery items
    bakeryItems[bakeryItemCount++] = BakeryItem(cakeName, "Cake", cakeDescription, cakePricePerUnit, ingredients, ingredientCount, cakeRecipe, cakeDisabled, cakeTotalWeight);
  }

  int cakeCount = bakeryItemCount; // Integer to store the count of cakes
  cakeFile.close();
  cout << "Cake count: " << cakeCount << endl;

  // Fetch bakery items (cookie)
  // Read from file/cookie.csv
  ifstream cookieFile; // Input file stream for the cookie file
  cookieFile.open("files/cookie.csv"); // Open the cookie file in input mode
  cout << endl;

  cout << "Reading cookie file..." << endl;
  string cookieLine; // String to store each line of the file
  string cookieName; // String to store the name of the cookie
  string cookieDescription; // String to store the description of the cookie
  double cookiePricePerUnit; // Double to store the price per unit of the cookie
  string cookieIngredients; // String to store the ingredients of the cookie
  string cookieRecipe; // String to store the recipe of the cookie
  bool cookieDisabled; // Boolean to store the disabled status of the cookie

  getline(cookieFile, cookieLine); // skip first line (header)
  while (!cookieFile.eof()) {
    ingredientCount = 0; // Reset the ingredient count

    // name
    getline(cookieFile, cookieName, ',');

    // description
    getline(cookieFile, cookieLine, '"');
    getline(cookieFile, cookieDescription, '"');

    // price per unit
    getline(cookieFile, cookieLine, ',');
    getline(cookieFile, cookieLine, ',');
    cookiePricePerUnit = stod(cookieLine);

    // ingredients
    getline(cookieFile, cookieLine, '"');
    getline(cookieFile, cookieLine, '"');

    for (int i = 0; i < cookieLine.length(); i++) {
      if (cookieLine[i] == ';') {
        ingredientCount++;
      }
    }

    // create ingredients array
    ingredients = new Ingredient[ingredientCount];
    int ingredientIndex = 0;
    
    // iterate through ingredients
    for (int i = 0; i < cookieLine.length(); i++) {
      // check if it is the end of an ingredient
      if (cookieLine[i] == ';') {
        string ingredientName = temp.substr(0, temp.find(",")); // Extract the name of the ingredient

        string ingredientWeightString = temp.substr(temp.find(",") + 1); // Extract the weight of the ingredient
        double ingredientWeight = stod(ingredientWeightString); // Convert the weight to a double

        // check if ingredient is countable or not
        bool countable = false; // Flag of boolean to store if the ingredient is countable
        if ((int)ingredientWeight == ingredientWeight) {
          countable = true;
        }

        string ingredientPieceString = temp.substr(temp.find(",") + 1);
        int ingredientPiece = stoi(ingredientPieceString);

        // check if ingredient is countable or not
        if (countable) {
          ingredients[ingredientIndex] = Ingredient(ingredientName, 0, ingredientPiece);
        } else {
          ingredients[ingredientIndex] = Ingredient(ingredientName, 0, ingredientWeight);
        }

        // increment ingredient index
        ingredientIndex++;
        temp = "";
      } else {
        temp += cookieLine[i];
      }
    }

    // recipe
    getline(cookieFile, cookieLine, '"');
    getline(cookieFile, cookieRecipe, '"');
    
    // disabled
    getline(cookieFile, cookieLine, ',');
    getline(cookieFile, cookieLine);
    cookieDisabled = (cookieLine == "true");

    // add to bakery items
    bakeryItems[bakeryItemCount++] = BakeryItem(cookieName, "Cookie", cookieDescription, cookiePricePerUnit, ingredients, ingredientCount, cookieRecipe, cookieDisabled);
  }
  int cookieCount = bakeryItemCount - cakeCount; // Integer to store the count of cookies
  cookieFile.close();
  cout << "Cookie count: " << cookieCount << endl;

  // Array of discounts
  discounts = new Discount[Constant::MAX_DISCOUNTS];

  // Read from file/discount.csv
  ifstream discountFile; // Input file stream for the discount file
  discountFile.open("files/discount.csv", ios::in); // Open the discount file in input mode
  cout << endl;

  cout << "Reading discount file..." << endl;
  string discountLine; // String to store each line of the file
  string discountName; // String to store the name of the discount
  double discountMinimumPurchase; // Double to store the minimum purchase required for the discount
  double discountPercentage; // Double to store the percentage of the discount
  string discountDescription; // String to store the description of the discount
  bool discountDisabled; // Boolean to store the disabled status of the discount
  int discountCount = 0; // Integer to store the count of discounts

  getline(discountFile, discountLine); // skip first line (header)
  while (getline(discountFile, discountName, ',')) {
    getline(discountFile, discountLine, ',');
    discountMinimumPurchase = stod(discountLine);
    getline(discountFile, discountLine, ',');
    discountPercentage = stod(discountLine);
    getline(discountFile, discountDescription, ',');
    getline(discountFile, discountLine);
    discountDisabled = (discountLine == "true");

    // check if discount name is empty
    if (discountName != "") {
      // cout << "Discount '" << discountName << "' has been added." << endl;

      // add to discounts
      discounts[discountCount] = Discount(discountName, discountMinimumPurchase, discountPercentage, discountDescription, discountDisabled);

      // increment discount count
      discountCount++;
    }
  }
  cout << "Discount count: " << discountCount << endl;
  discountFile.close();
  cout << endl;

  // Start bakery operation
  if (supervisor != nullptr) {
    supervisor->startBakery();
  } else if (baker != nullptr) {
    baker->startBakery();
  } else if (cashier != nullptr) {
    cashier->startBakery();
  } else {
    cout << "Not a valid role to start the bakery." << endl;
    exit(EXIT_FAILURE); // Exit the program with an error code.
  }

  cout << endl;

  // Set ingredient cost of each bakery item to the corresponding ingredient cost in the inventory
  this->setIngredientCostToInventoryIngredientCost();
  cout << endl;

  cout << "Selling " << bakeryItems[0].getBakeryItemCount() << " items today." << endl;
}

/**
 * @brief Accesses the menu list for the employee.
 * 
 * This function displays the menu list for the employee's role.
 * It prints the bakery items available in the menu.
 * 
 * @param None
 * 
 * @return None
 */
void Employee::accessMenuList() const {
  cout << role << " - Accessing menu list..." << endl;

  // Display the bakery items available in the menu.
  cout << "+----------------------------------------+" << endl;
  cout << "|              Bakery Menu               |" << endl;
  cout << "+----------------------------------------+" << endl;
  for (int i = 0; i < bakeryItems[0].getBakeryItemCount(); i++) {
      cout << "| " << i+1 << ". " << setw(30) << left << bakeryItems[i].getBakeryItemName() << "      |" << endl;
  }
  cout << "+----------------------------------------+" << endl;
}

/**
 * @brief Accesses the menu item details for the employee.
 * 
 * This function displays the details of the menu item at the given index.
 * It prints the name, category, description, price per unit, and recipe of the menu item.
 * 
 * @param index The index of the menu item in the bakery items array.
 * 
 * @return None
 */
void Employee::accessMenuItem(int index) {
  cout << role << " - Accessing menu details..." << endl;

  // Display the details of the menu item at the given index.
  accessMenuDetails(bakeryItems+index);
}


/**
 * @brief Accesses the discount list for the employee.
 * 
 * This function prints the discount list for the employee's role.
 * 
 * @param None.
 * 
 * @return None.
 */
void Employee::accessDiscountList() const {
  cout << role << " - Accessing discount list..." << endl;

  // Display the discounts available.
  // Print table header
  cout << "+-----+--------------------------------------------+" << endl;
  cout << "| No. | Discount Name                              |" << endl;
  cout << "+-----+--------------------------------------------+" << endl;

  // Print discounts
  for (int i = 0; i < discounts[0].getDiscountCount(); i++) {
    cout << "| " << setw(3) << i+1 << " | " << setw(43) << left << discounts[i].getName() << "|" << endl;
  }

  cout << "+-----+--------------------------------------------+" << endl;
}

/**
 * @brief Accesses the discount details for the employee.
 * 
 * This function displays the details of the discount at the given index.
 * It prints the name, amount, description, and active status of the discount.
 * 
 * @param index The index of the discount in the discounts array.
 * 
 * @return None.
 */
void Employee::accessDiscountDetails(int index) const {
  cout << role << " - Accessing discount details..." << endl;
  cout << "Name: " << discounts[index].getName() << endl;
  cout << "Amount: " << discounts[index].getDiscountPercentage() << "%" << endl;
  cout << "Description: " << discounts[index].getDescription() << endl;
  cout << "Active: " << (!discounts[index].getDisabled() ? "Yes" : "No") << endl;
}

/**
 * @brief Get the number of available discounts according to the total purchase price.
 * 
 * @return int 
 */
int Employee::getAvailableDiscountCount() const {
  bool isDiscountAvailable = false; // Flag to check if a discount is available.
  int count = 0; // Counter for the number of available discounts.
  for (int i = 0; i < discounts->getDiscountCount(); i++) {
    // Check if the total purchase price is greater than or equal to the minimum purchase required for the discount.
    if (cashier->getCart()->calculateTotalPrice() >= discounts[i].getMinimumPurchase()) {
      isDiscountAvailable = true;

      // Increment the count of available discounts.
      count++;
    }
  }
  return count;
}

/**
 * @brief Show the total debit of the bakery.
 * 
 * @param None.
 * @return None.
 * 
 */
void Employee::showTotalDebit() const {
  // cout << role << " - Showing total debit..." << endl;
  cout << "Total debit: RM " << totalDebit << endl;
}

/**
 * @brief Show the total credit of the bakery.
 * 
 * @param None.
 * @return None.
 * 
 */
void Employee::showTotalCredit() const {
  // cout << role << " - Showing total credit..." << endl;
  cout << "Total credit: RM " << totalCredit << endl;
}

/**
 * @brief Show the total profit per day of the bakery.
 * 
 * @param None.
 * @return None.
 * 
 */
void Employee::showTotalProfitPerDay() const {
  // cout << role << " - Showing total profit per day..." << endl;
  totalProfitPerDay = totalDebit - totalCredit;
  cout << "Total profit per day: RM " << totalProfitPerDay << endl;
}

/**
 * @brief Show the total balance of the bakery.
 * 
 * @param None.
 * @return None.
 * 
 */
void Employee::showTotalBalance() const {
  // cout << role << " - Showing total balance..." << endl;
  // since bakery is not closed, totalProfitPerDay is not added to totalBalance
  cout << "Total balance: RM " << totalBalance + totalProfitPerDay << endl;
}

/**
 * @brief Close the bakery operation on the specified date.
 * 
 * @param date The date on which the bakery operation will close.
 * @note The date format is "YYYY-MM-DD".
 * @return None.
 * 
 */
void Employee::closeBakery(string date) {
  cout << "Bakery closing now." << endl;

  // close bakery operation
  if (supervisor != nullptr) {
    supervisor->closeBakery();
  } else if (baker != nullptr) {
    baker->closeBakery();
  } else if (cashier != nullptr) {
    cashier->closeBakery();
  } else {
    cout << "Not a valid role to close the bakery." << endl;
    exit(EXIT_FAILURE);
  }

  // Display summary of the day
  cout << "Summary of the day:" << endl;
  cout << "Total debit: RM " << totalDebit << endl;
  cout << "Total credit: RM " << totalCredit << endl;
  totalProfitPerDay = totalDebit - totalCredit;
  cout << "Total profit per day: RM " << totalProfitPerDay << endl;
  totalBalance += totalProfitPerDay;
  cout << "Total balance: RM " << totalBalance << endl;

  // Append to balanceSheet.csv
  ofstream balanceSheetFile;
  balanceSheetFile.open("files/balanceSheet.csv", ios::app);
  balanceSheetFile << setprecision(2) << fixed;
  balanceSheetFile << "\n" << date << "," << totalDebit << "," << totalCredit << "," << totalBalance;
  balanceSheetFile.close();
}

/**
 * @brief Display the ingredient inventory list.
 * 
 * @param None.
 * @return None.
 * 
 */
void Employee::displayIngredientInventoryList() const {
  // Check if the employee is a supervisor or a baker.
  if (supervisor != nullptr || baker != nullptr) {
    cout << role << " - Displaying ingredient inventory list..." << endl;

    // Display the ingredient inventory list.
    ingredientInventory->displayIngredientInventoryList();
  } else {
    cout << "Only supervisor or baker can display ingredient inventory list." << endl;
  }
}

/**
 * @brief Access the ingredient inventory details at the specified index.
 * 
 * @param index The index of the ingredient in the ingredient inventory.
 * @return None.
 * 
 */
void Employee::accessIngredientInventoryDetails(int index) const {
  // Check if the employee is a supervisor or a baker.
  if (supervisor != nullptr || baker != nullptr) {
    cout << role << " - Accessing ingredient inventory details..." << endl;

    // Access the ingredient inventory details at the specified index.
    ingredientInventory->accessIngredientInventoryDetails(index); 
  } else {
    cout << "Only supervisor or baker can access ingredient inventory details." << endl;
  }
}

/**
 * @brief Check the ingredient inventory.
 * 
 * @param None.
 * @return None.
 * 
 */
void Employee::checkIngredientInventory() const {
  // Check if the employee is a supervisor or a baker.
  if (supervisor != nullptr || baker != nullptr) {
    cout << role << " - Checking ingredient inventory..." << endl;

    // Check the ingredient inventory.
    ingredientInventory->checkIngredientInventory();
  } else {
    cout << "Only supervisor or baker can check ingredient inventory." << endl;
  }
}

/**
 * @brief Accesses the ingredient inventory file and performs a search based on the specified field and value.
 * 
 * @param index The index of the ingredient in the inventory file.
 * @param field The field to search for in the inventory file.
 * @param value The value to match in the specified field.
 * 
 * @return None.
 */
void Employee::accessIngredientInventoryFile(int index, string field, string value) {
  ifstream ingredientInventoryFile; // Input file stream for the ingredient inventory file.
  ingredientInventoryFile.open("files/IngredientInventory.csv", ios::in); // Open the ingredient inventory file in input mode.
  string line; // String to store each line of the file.
  string newFileLines; // String to store the new file lines after modification.

  string name; // String to store the name of the ingredient.
  string costPerUnit; // String to store the cost per unit of the ingredient.
  string weight; // String to store the weight of the ingredient.
  string piece; // String to store the piece of the ingredient.
  string countable; // String to store the countable status of the ingredient.

  getline(ingredientInventoryFile, line); // Skip the first line (header
  newFileLines += line + "\n"; // Append the first line to the new file lines.
  while (!ingredientInventoryFile.eof()) {
    getline(ingredientInventoryFile, name, ',');
    getline(ingredientInventoryFile, costPerUnit, ',');
    getline(ingredientInventoryFile, weight, ',');
    getline(ingredientInventoryFile, piece, ',');
    getline(ingredientInventoryFile, countable);

    // Check if the name matches the ingredient name at the specified index.
    if (name == ingredientInventory->getIngredientInventoryName(index)) {
      // cout << endl << endl << "editing: " << name << "," << field << "," << value << endl << endl;
      // here printing the ingredient inventory @WenHao1223
      cout << name << "," << field << "," << value << endl;
      if (field == "name") {
        name = value;
      } else if (field == "costPerUnit") {
        costPerUnit = value;
      } else if (field == "weight") {
        weight = value;
      } else if (field == "piece") {
        piece = value;
      } else if (field == "countable") {
        countable = value;
      } else if (field == "deleteAll") {
        continue;
      } else {
        cout << "Invalid field." << endl;
        return;
      }
    }

    // Append the new line to the new file lines.
    newFileLines += name + "," + costPerUnit + "," + weight + "," + piece + "," + countable + "\n";
  }

  // Remove last line
  newFileLines = newFileLines.substr(0, newFileLines.length()-1);
  ingredientInventoryFile.close();

  // Write the new file lines to the ingredient inventory file.
  ofstream newIngredientInventoryFile; // Output file stream for the new ingredient inventory file.
  newIngredientInventoryFile.open("files/IngredientInventory.csv"); // Open the ingredient inventory file in output mode.
  newIngredientInventoryFile << newFileLines; // Write the new file lines to the ingredient inventory file.
  newIngredientInventoryFile.close(); // Close the ingredient inventory file.
}

/**
 * @brief Restocks the ingredient inventory.
 * 
 * @param index The index of the ingredient in the inventory.
 * @param quantity The quantity to restock.
 * 
 * @return None.
 */
void Employee::restockIngredientInventory(int index, double quantity) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Restocking ingredient inventory..." << endl;

    // Check if the quantity is negative.
    if (quantity < 0) {
      cout << "Quantity cannot be negative." << endl;
      return;
    }

    // Restock the ingredient inventory.
    double totalCost = ingredientInventory->restockIngredientInventory(index, quantity); // Calculate the total cost of restocking the ingredient.

    // file handling of ingredient inventory file
    // check if ingredient is countable or not
    if ((ingredientInventory+index)->getIngredient().getCountable()) {
      accessIngredientInventoryFile(index, "piece", to_string(ingredientInventory->getIngredientInventoryPiece(index)));
    } else {
      accessIngredientInventoryFile(index, "weight", to_string((int)(ingredientInventory->getIngredientInventoryWeight(index))));
    }

    cout << "Cost of restock: RM " << totalCost << endl;

    // update total credit
    totalCredit += totalCost;

    // cout << "Total credit: RM " << totalCredit << endl;
  } else {
    cout << "Only supervisor can restock ingredient inventory." << endl;
  }
}

/**
 * @brief Changes the ingredient cost per unit in the ingredient inventory.
 * 
 * @param index The index of the ingredient in the inventory.
 * @param cost The cost per unit to change.
 * 
 * @return None.
 */
void Employee::changeIngredientCost(int index, double cost) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Changing ingredient cost per unit..." << endl;

    // Check if the cost is negative.
    if (cost < 0) {
      cout << "Cost cannot be negative." << endl;
      return;
    }

    // Change the ingredient cost per unit in the ingredient inventory.
    ingredientInventory->changeIngredientCost(index, cost);

    // File handling of ingredient inventory file
    accessIngredientInventoryFile(index, "costPerUnit", to_string(cost));

    // Update all bakery items ingredient cost
    this->setIngredientCostToInventoryIngredientCost();
  } else {
    cout << "Only supervisor can change ingredient cost per unit." << endl;
  }
};

/**
 * @brief Adds a new inventory ingredient with weight to the ingredient inventory.
 * 
 * @param name The name of the ingredient.
 * @param cost The cost per unit of the ingredient.
 * @param weight The weight of the ingredient.
 * 
 * @return None.
 */
void Employee::addNewInventoryIngredientWeight(string name, double cost, double weight) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Adding new inventory ingredient (weight)..." << endl;

    // name cannot be empty
    if (name == "") {
      cout << "Name cannot be empty." << endl;
      return;
    }

    // cost cannot be negative
    if (cost < 0) {
      cout << "Cost cannot be negative." << endl;
      return;
    }

    // weight cannot be negative
    if (weight < 0) {
      cout << "Weight cannot be negative." << endl;
      return;
    }

    // File handling of ingredient inventory file inside function to add new inventory ingredient with weight
    ingredientInventory->addNewInventoryIngredientWeight(name, cost, weight);
  } else {
    cout << "Only supervisor can add new inventory ingredient." << endl;
  }
}

/**
 * @brief Adds a new inventory ingredient with piece to the ingredient inventory.
 * 
 * @param name The name of the ingredient.
 * @param cost The cost per unit of the ingredient.
 * @param piece The piece of the ingredient.
 * 
 * @return None.
 */
void Employee::addNewInventoryIngredientPiece(string name, double cost, int piece) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Adding new inventory ingredient (piece)..." << endl;

    // name cannot be empty
    if (name == "") {
      cout << "Name cannot be empty." << endl;
      return;
    }

    // cost cannot be negative
    if (cost < 0) {
      cout << "Cost cannot be negative." << endl;
      return;
    }

    // piece cannot be negative
    if (piece < 0) {
      cout << "Piece cannot be negative." << endl;
      return;
    }

    // File handling of ingredient inventory file inside function to add new inventory ingredient with piece
    ingredientInventory->addNewInventoryIngredientPiece(name, cost, piece);
  } else {
    cout << "Only supervisor can add new inventory ingredient." << endl;
  }
}


/**
 * @brief Get the All Inventory Ingredient Name
 * 
 * This function gets the name of all the inventory ingredients.
 * 
 * @param None.
 * @return None.
 * 
 */
void Employee::getAllInventoryIngredientName() const {
  cout << "Getting all ingredient inventory names..." << endl;

  // Iterate through all the inventory ingredients.
  for (int i = 0; i < ingredientInventory->getIngredientInventoryCount(); i++) {
    // Get the name of all the inventory ingredients.
    cout << i+1 << ". " << ingredientInventory->getIngredientInventoryName(i) << endl;
  }
}

/**
 * @brief Create a Bakery Item object
 * 
 * This function creates a new bakery item object either a cake or a cookie.
 * 
 * @param None.
 * @return None.
 * 
 */
void Employee::createBakeryItem() {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Creating bakery item..." << endl;

    // Create bakery items from user input
    string bakeryItemName; // String to store the name of the bakery item
    string bakeryItemCategory = ""; // String to store the category of the bakery item
    string bakeryItemDescription; // String to store the description of the bakery item
    double bakeryItemPricePerUnit; // Double to store the price per unit of the bakery item
    int numberOfIngredients; // Integer to store the number of ingredients
    Ingredient * ingredient; // Pointer to an array of ingredients
    string recipe; // String to store the recipe of the bakery item
    int totalWeight = 0; // Integer to store the total weight of the cake

    cin.ignore();

    // input bakery item details
    // input bakery item name
    do {
      cout << "Enter item name: ";
      getline(cin, bakeryItemName);
    } while (bakeryItemName == "");

    // Check if item is existing
    for (int i = 0; i < bakeryItems->getBakeryItemCount(); i++) {
      // Check if the bakery item name is the same as the existing bakery item name
      if (bakeryItemName == bakeryItems[i].getBakeryItemName()) {
        cout << "Item already exists." << endl;
        return;
      }
    }

    // input bakery item category
    // category must be either Cookie or Cake
    do {
      cout << "Enter category (Cookie / Cake): ";
      cin >> bakeryItemCategory;
    } while (bakeryItemCategory != "Cookie" && bakeryItemCategory != "Cake");

    cin.ignore();

    // input bakery item description
    // description cannot be empty
    do {
      cout << "Enter description: ";
      getline(cin, bakeryItemDescription);
    } while (bakeryItemDescription == "");

    // input price per unit
    // price per unit cannot be negative
    do {
      cout << "Enter price per unit: RM ";
      cin >> bakeryItemPricePerUnit;
    } while (bakeryItemPricePerUnit < 0);

    cin.ignore();

    // input total weight for cake
    // total weight cannot be negative
    // only for cake
    if (bakeryItemCategory == "Cake") {
      do {
        cout << "Enter total weight in gram(s): ";
        cin >> totalWeight;
      } while (totalWeight <= 0);
    }

    // input number of ingredients
    // number of ingredients must be more than 0
    do {
      cout << "Enter number of ingredients: ";
      cin >> numberOfIngredients;
    } while (numberOfIngredients <= 0);

    // create ingredients array
    ingredient = new Ingredient[numberOfIngredients]; // Array of ingredients for the bakery item

    // input ingredient details for each ingredient
    // input ingredient name, cost, weight/piece, and recipe
    for (int i = 0; i < numberOfIngredients; i++) {
      string ingredientName; // String to store the name of the ingredient
      double ingredientCost = 0; // Double to store the cost of the ingredient
      double ingredientWeight; // Double to store the weight of the ingredient
      int ingredientPiece; // Integer to store the piece of the ingredient
      bool countable; // Boolean to store if the ingredient is countable

      char countableInput; // Char to store the countable input

      cout << "--- Ingredient " << i+1 << " ---" << endl;

      cin.ignore();

      // input ingredient name
      // ingredient name cannot be empty
      do {
        cout << "Enter ingredient name: ";
        getline(cin, ingredientName);
      } while (ingredientName == "");


      // Find ingredient name from ingredient inventory, if found, use the cost
      // if not found, ask user to input cost
      // Iterate through all the inventory ingredients.
      for (int j = 0; j < ingredientInventory->getIngredientInventoryCount(); j++) {
        // Check if the ingredient name is the same as the existing ingredient name
        if (ingredientName ==  ingredientInventory->getIngredientInventoryName(j)) {
          cout << ingredientName << " found in inventory." << endl;
          cout << "Cost: RM " << ingredientInventory->getIngredientInventoryCost(j);

          // check if ingredient is countable or not
          if (ingredientInventory[j].getIngredient().getCountable()) {
            cout << " / piece(s)." << endl;
          } else {
            cout << " / gram(s)." << endl;
          }

          // use the cost from inventory
          ingredientCost = ingredientInventory->getIngredientInventoryCost(j);

          // ask user to input weight/piece
          // check if ingredient is countable or not
          if (ingredientInventory[j].getIngredient().getCountable()) {
            // input ingredient piece
            // ingredient piece must be more than 0
            do {
              cout << "Enter ingredient piece: ";
              cin >> ingredientPiece;
            } while (ingredientPiece <= 0);

            // set ingredient details
            ingredient[i] = Ingredient(ingredientName, ingredientCost, ingredientPiece); // Create a new ingredient object
          } else {
            // input ingredient weight
            // ingredient weight must be more than 0
            do {
              cout << "Enter ingredient weight in gram(s): ";
              cin >> ingredientWeight;
            } while (ingredientWeight <= 0);

            // set ingredient details
            ingredient[i] = Ingredient(ingredientName, ingredientCost, ingredientWeight); // Create a new ingredient object
          }
        }
      }

      // If ingredient name not found in inventory, ask user to input cost
      if (ingredientCost == 0) {
        // input ingredient cost
        // ingredient cost cannot be negative
        do {
          cout << "Enter ingredient cost per Unit: RM ";
          cin >> ingredientCost;
        } while (ingredientCost < 0);

        // ask user is the ingredient in piece or weight
        // countable must be either 0 or 1
        do {
          cout << "Enter ingredient piece or weight (0 for weight, 1 for piece): ";
          cin >> countableInput;
        } while (countableInput != '0' && countableInput != '1');

        // check if ingredient is countable or not
        // if countable, input ingredient piece
        countable = (countableInput == '1');

        // set ingredient details
        // if countable, input ingredient piece
        if (countable) {
          // input ingredient piece
          // ingredient piece must be more than 0
          do {
            cout << "Enter ingredient piece: ";
            cin >> ingredientPiece;
          } while (ingredientPiece <= 0);

          // set ingredient details
          ingredient[i] = Ingredient(ingredientName, ingredientCost, ingredientPiece); // Create a new ingredient object

          // add new ingredient to ingredient inventory
          ingredientInventory->addNewInventoryIngredientPiece(ingredientName, ingredientCost, ingredientPiece);
        } else {
          // input ingredient weight
          // ingredient weight must be more than 0
          do {
            cout << "Enter ingredient weight in gram(s): ";
            cin >> ingredientWeight;
          } while (ingredientWeight <= 0);

          // set ingredient details
          ingredient[i] = Ingredient(ingredientName, ingredientCost, ingredientWeight); // Create a new ingredient object

          // add new ingredient to ingredient inventory
          ingredientInventory->addNewInventoryIngredientWeight(ingredientName, ingredientCost, ingredientWeight);
        }
      }
    }

    // enable user to type multiline recipe
    cin.ignore();

    // input recipe
    // recipe cannot be empty
    do {
      recipe = "";
      cout << "Enter recipe (press CTRL+Z then Enter on Windows, or CTRL+D on Unix, to exit): " << endl;

      string line; // String to store each line of the recipe

      // Read the recipe line by line
      while (getline(cin, line)) {
        // check if end of file
        if (cin.eof()) {
          break;
        }
        recipe += line + "\n"; // Append the line to the recipe
      }

      cin.clear(); // Clear the input stream
    } while (recipe == "");

    // Confirm to create bakery item
    char confirm; // Char to store the confirmation input

    // confirm must be either Y or N
    do {
      cout << "Confirm to create bakery item? (Y/N): ";
      cin >> confirm;
    } while (confirm != 'Y' && confirm != 'y' && confirm != 'N' && confirm != 'n');

    // check if user wants to create bakery item
    if (confirm == 'N' || confirm == 'n') {
      cout << "Bakery item creation cancelled." << endl;
      return;
    }

    // create bakery item
    bakeryItems[bakeryItems->getBakeryItemCount()] = BakeryItem(bakeryItemName, bakeryItemCategory, bakeryItemDescription, bakeryItemPricePerUnit, ingredient, numberOfIngredients, recipe, totalWeight); // Create a new bakery item object

    // check if bakery item is cake or cookie
    if (bakeryItemCategory == "Cake") {
      // append to cake.csv
      ofstream cakeFile; // Output file stream for the cake file
      cakeFile.open("files/cake.csv", ios::app); // Open the cake file in append mode
      cakeFile << "\n" << bakeryItemName << ",\"" << bakeryItemDescription << "\"," << bakeryItemPricePerUnit << ",\"";

      // write ingredients to file with format: name,weight/piece
      // Iterate through all the ingredients.
      for (int i = 0; i < numberOfIngredients; i++) {
        cakeFile << ingredient[i].getName() << ",";
        // check if ingredient is countable or not
        if (ingredient[i].getCountable()) {
          cakeFile << ingredient[i].getPiece();
        } else {
          cakeFile << ingredient[i].getWeight();
        }
        // check if last ingredient
        if (i != numberOfIngredients - 1) {
          cakeFile << ";";
        }
      }

      // Replace \n with \\n using .find and .replace
      auto pos = recipe.find("\n");

      // Iterate through all the positions of \n in the recipe.
      while (pos != string::npos) {
        recipe.replace(pos, 1, "\\n");
        pos = recipe.find("\n", pos + 2);
      }

      // Check if the last character of the recipe is a newline character.
      if (recipe[recipe.length()-1] == '\n') {
        recipe = recipe.substr(0, recipe.length()-1);
      }

      cakeFile << "\",\"" << recipe << "\"," << (bakeryItems->getBakeryItemCount() == 0 ? "false" : "true") << "," << totalWeight;
      cakeFile.close();
    } else {
      // append to cookie.csv
      ofstream cookieFile; // Output file stream for the cookie file
      cookieFile.open("files/cookie.csv", ios::app); // Open the cookie file in append mode
      cookieFile << "\n" << bakeryItemName << ",\"" << bakeryItemDescription << "\"," << bakeryItemPricePerUnit << ",\"";

      // write ingredients to file with format: name,weight/piece
      // Iterate through all the ingredients.
      for (int i = 0; i < numberOfIngredients; i++) {
        cookieFile << ingredient[i].getName() << ",";

        // check if ingredient is countable or not
        if (ingredient[i].getCountable()) {
          cookieFile << ingredient[i].getPiece();
        } else {
          cookieFile << ingredient[i].getWeight();
        }

        // check if last ingredient
        if (i != numberOfIngredients - 1) {
          cookieFile << ";";
        }
      }

      // Replace \n with \\n using .find and .replace
      auto pos = recipe.find("\n");

      // Iterate through all the positions of \n in the recipe.
      while (pos != string::npos) {
        recipe.replace(pos, 1, "\\n");
        pos = recipe.find("\n", pos + 2);
      }

      // Check if the last character of the recipe is a newline character.
      if (recipe[recipe.length()-1] == '\n') {
        recipe = recipe.substr(0, recipe.length()-1);
      }
      cookieFile << "\",\"" << recipe << "\"," << (bakeryItems->getBakeryItemCount() == 0 ? "false" : "true");
      cookieFile.close();
    }
  } else {
    cout << "Only supervisor can create bakery item." << endl;
  }
}

/**
 * @brief Accesses the bakery item file and performs a search based on the specified field and value.
 * 
 * @param index The index of the bakery item in the bakery items array.
 * @param field The field to search for in the bakery item file.
 * @param value The value to match in the specified field.
 * 
 * @return None.
 */
void Employee::accessBakeryItemFile (int index, string field, string value) {
  // Open the bakery item file in input mode.
  ifstream bakeryItemFile; // Input file stream for the bakery item file.

  // Check if the bakery item is a cake or a cookie.
  if (bakeryItems[index].getBakeryItemCategory() == "Cake") {
    bakeryItemFile.open("files/cake.csv", ios::in);
  } else {
    bakeryItemFile.open("files/cookie.csv", ios::in);
  }

  string line; // String to store each line of the file.
  string newFileLines; // String to store the new file lines after modification.

  string name; // String to store the name of the bakery item.
  string description; // String to store the description of the bakery item.
  string pricePerUnit; // String to store the price per unit of the bakery item.
  string ingredients; // String to store the ingredients of the bakery item.
  string recipe; // String to store the recipe of the bakery item.
  string disabled; // String to store the disabled status of the bakery item.
  string totalWeight; // String to store the total weight of the cake

  // Check if the bakery item file is found.
  if (!bakeryItemFile) {
    cout << "File not found." << endl;
    return;
  } else {
    getline(bakeryItemFile, line); // skip first line (header)
    newFileLines += line + "\n"; // append first line (header)
  }

  // Read the bakery item file line by line.
  while (!bakeryItemFile.eof()) {
    // name
    getline(bakeryItemFile, name, ',');

    // description
    getline(bakeryItemFile, line, '"');
    getline(bakeryItemFile, description, '"');

    // price per unit
    getline(bakeryItemFile, line, ',');
    getline(bakeryItemFile, pricePerUnit, ',');

    // ingredients
    getline(bakeryItemFile, line, '"');
    getline(bakeryItemFile, ingredients, '"');

    // recipe
    getline(bakeryItemFile, line, '"');
    getline(bakeryItemFile, recipe, '"');
    
    // Check if the bakery item is a cake.
    if (bakeryItems[index].getBakeryItemCategory() == "Cake") {
      // disabled
      getline(bakeryItemFile, line, ',');
      getline(bakeryItemFile, disabled, ',');

      // total weight
      getline(bakeryItemFile, totalWeight);
    } else {
      // disabled
      getline(bakeryItemFile, disabled);
    }

    // Check if the name matches the bakery item name at the specified index.
    if (name == bakeryItems[index].getBakeryItemName()) {
      if (field == "pricePerUnit") {
        pricePerUnit = value;
      } else if (field == "disabled") {
        disabled = value;
      } else if (field == "deleteAll") {
        continue;
      } else {
        cout << "Invalid field." << endl;
        return;
      }
    }

    // Append the new line to the new file lines.
    newFileLines += name + ",\"" + description + "\"," + pricePerUnit + ",\"" + ingredients + "\",\"" + recipe + "\"," + disabled + "," + totalWeight + "\n";
  }

  // Remove last line
  newFileLines = newFileLines.substr(0, newFileLines.length()-1);
  bakeryItemFile.close();

  // Write the new file lines to the bakery item file.
  ofstream newBakeryItemFile; // Output file stream for the new bakery item file.

  // Check if the bakery item is a cake or a cookie.
  if (bakeryItems[index].getBakeryItemCategory() == "Cake") {
    newBakeryItemFile.open("files/cake.csv");
  } else {
    newBakeryItemFile.open("files/cookie.csv");
  }
  newBakeryItemFile << newFileLines;
  newBakeryItemFile.close();
}

/**
 * @brief Withdraws a bakery item from the bakery.
 * 
 * @param index The index of the bakery item in the bakery items array.
 * @return None.
 */
void Employee::withdrawBakeryItem (int index) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Withdrawing " << bakeryItems[index].getBakeryItemName() << "..." << endl;

    // Disable the bakery item.
    bakeryItems[index].setDisabled(true);

    // file handling of bakery item file - cake.csv / cookie.csv
    accessBakeryItemFile(index, "disabled", "true");

    cout << bakeryItems[index].getBakeryItemName() << " has been withdrawn." << endl;
  } else {
    cout << "Only supervisor can withdraw bakery item." << endl;
  }
}

/**
 * @brief Enable a bakery item in the bakery.
 * 
 * @param index The index of the bakery item in the bakery items array.
 * @return None.
 */
void Employee::enableBakeryItem (int index) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Enabling " << bakeryItems[index].getBakeryItemName() << "..." << endl;

    // Enable the bakery item.
    bakeryItems[index].setDisabled(false);

    // file handling of bakery item file - cake.csv / cookie.csv
    accessBakeryItemFile(index, "disabled", "false");

    cout << bakeryItems[index].getBakeryItemName() << " has been enabled." << endl;
  } else {
    cout << "Only supervisor can enable bakery item." << endl;
  }
}

/**
 * @brief Change the bakery item price based on the index.
 * 
 * @param index The index of the bakery item.
 * @param newPrice The new price of the bakery item.
 */
void Employee::changeBakeryItemPrice(int index, double newPrice) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Changing " << bakeryItems[index].getBakeryItemName() << " price..." << endl;
    bakeryItems[index].setPricePerUnit(newPrice);

    // file handling of bakery item file - cake.csv / cookie.csv
    accessBakeryItemFile(index, "pricePerUnit", to_string(newPrice));

    cout << setprecision(2) << fixed;
    cout << bakeryItems[index].getBakeryItemName() << " price has been changed to RM " << newPrice << "." << endl;
  } else {
    cout << "Only supervisor can change bakery item price." << endl;
  }
}

/**
 * @brief Calculates the cost of a bakery item at the specified index.
 * 
 * This function calculates the cost of a bakery item based on the index provided.
 * The index should be a valid index within the bakery item list.
 * 
 * @param index The index of the bakery item.
 * 
 * @return None.
 */
void Employee::calculateBakeryItemCost(int index) const {
  cout << role << " - Calculating " << bakeryItems[index].getBakeryItemName() << " cost..." << endl;
  cout << setprecision(2) << fixed;
  cout << "Total cost: RM " << bakeryItems[index].calculateCost() << endl;
}

/**
 * @brief Calculates the profit of a bakery item at the specified index.
 * 
 * This function calculates the profit of a bakery item based on the index provided.
 * The index should be a valid index within the bakery item list.
 * 
 * @param index The index of the bakery item.
 * 
 * @return None.
 */
void Employee::calculateBakeryItemProfit(int index) const {
  cout << role << " - Calculating " << bakeryItems[index].getBakeryItemName() << " profit..." << endl;
  cout << setprecision(2) << fixed;
  cout << "Total profit: RM " << bakeryItems[index].calculateProfit() << endl;
}

/**
 * @brief Compares the cost and profit of a bakery item at the specified index.
 * 
 * This function compares the cost and profit of a bakery item based on the index provided.
 * The index should be a valid index within the bakery item list.
 * 
 * @param index The index of the bakery item.
 * 
 * @return None.
 */
void Employee::compareCostVsProfit(int index) const {
  cout << role << " - Comparing " << bakeryItems[index].getBakeryItemName() << " cost vs profit..." << endl;
  cout << setprecision(2) << fixed;
  cout << "Total cost: RM " << bakeryItems[index].calculateCost() << endl;
  cout << "Total profit: RM " << bakeryItems[index].calculateProfit() << endl;

  cout << setprecision(2) << fixed;

  // profit percentage = (profit / cost) * 100
  cout << "Profit percentage: " << (bakeryItems[index].calculateProfit() / bakeryItems[index].calculateCost()) * 100 << "%" << endl;
}

/**
 * @brief Compares the cost and price of a bakery item at the specified index.
 * 
 * This function compares the cost and price of a bakery item based on the index provided.
 * The index should be a valid index within the bakery item list.
 * 
 * @param index The index of the bakery item.
 * 
 * @return None.
 */
void Employee::compareCostVsPrice(int index) const {
  cout << role << " - Comparing " << bakeryItems[index].getBakeryItemName() << " cost vs price..." << endl;
  cout << setprecision(2) << fixed;
  cout << "Total cost: RM " << bakeryItems[index].calculateCost() << endl;
  cout << "Price per unit: RM " << bakeryItems[index].getPricePerUnit() << endl;

  cout << setprecision(2) << fixed;

  // price percentage = (price / cost) * 100
  cout << "Price percentage: " << (bakeryItems[index].getPricePerUnit() / bakeryItems[index].calculateCost()) * 100 << "%" << endl;
}

/**
 * @brief Creates a new employee with the given details.
 * 
 * @param employees An array of Employee objects.
 * @param employeeID The ID of the employee.
 * @param name The name of the employee.
 * @param role The role of the employee.
 * @param password The password of the employee.
 * 
 * @return None.
 */
void Employee::createNewEmployee(Employee * employees, string employeeID, string name, string role, string password) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << this->role << " - Creating new employee..." << endl;

    // check if name is empty
    if (name == "") {
      cout << "Name cannot be empty." << endl;
      return;
    }

    // check if employee id is empty
    if (employeeID == "") {
      cout << "Employee ID cannot be empty." << endl;
      return;
    }

    // check if role is empty
    if (role == "") {
      cout << "Role cannot be empty." << endl;
      return;
    }

    // check if password is empty
    if (password == "") {
      cout << "Password cannot be empty." << endl;
      return;
    }

    // check if employee id is unique
    bool employeeCreated = false; // Flag of boolean to store if the employee is created
    for (int i = 0; i < Constant::MAX_EMPLOYEES; i++) {
      // employee id is not unique
      if (employees[i].employeeID == employeeID) {
        cout << "Warning: Employee ID is not unique." << endl;
        return;
      }

      // store employee details in the first empty slot
      if (employees[i].employeeID == "") {
        cout << role << " " << name << " created successfully." << endl;

        employees[i].employeeID = employeeID;
        employees[i].name = name;
        employees[i].role = role;
        employees[i].password = password;

        // file handling of employee data file
        ofstream employeeDataFile; // Output file stream for the employee data file
        employeeDataFile.open("files/employeeData.csv", ios::app); // Open the employee data file in append mode
        employeeDataFile << "\n" << employeeID << "," << name << "," << role << "," << password; // Append the employee details to the file
        employeeDataFile.close(); // Close the employee data file

        // create employee object based on role
        if (role == "Supervisor") {
          employees[i].supervisor = new Supervisor(employeeID, name);
        } else if (role == "Baker") {
          employees[i].baker = new Baker(employeeID, name);
        } else {
          employees[i].cashier = new Cashier(employeeID, name);
        }

        employeeCreated = true; // Set the employee created flag to true

        // display new employee details
        cout << endl;
        employees[i].displayEmployeeDetails();
        break;
      }
    }

    // maximum number of employees reached
    if (!employeeCreated) {
      cout << "Warning: Maximum number of employees reached." << endl;
    }

  } else {
    cout << "Only supervisor can create new employee." << endl;
  }
}

/**
 * @brief Accesses the employee data file and performs a search based on the specified field and value.
 * 
 * @param index The index of the employee in the employees array.
 * @param field The field to search for in the employee data file.
 * @param value The value to match in the specified field.
 * 
 * @return None.
 */
void Employee::accessEmployeeDataFile (int index, string field, string value) {
  // Open the employee data file in input mode.
  ifstream employeeDataFile; // Input file stream for the employee data file
  employeeDataFile.open("files/employeeData.csv", ios::in); // Open the employee data file in input mode

  string line; // String to store each line of the file
  string newFileLines; // String to store the new file lines after modification
  int lineCount = 0; // Integer to store the line count

  string employeeID; // String to store the ID of the employee
  string name; // String to store the name of the employee
  string role; // String to store the role of the employee
  string password; // String to store the password of the employee

  // Check if the employee data file is found.
  if (!employeeDataFile) {
    cout << "files/employeeData.csv not found." << endl;
    return;
  } else {
    getline(employeeDataFile, line); // skip first line (header)
    newFileLines += line + "\n"; // append first line (header)
  }

  // Read the employee data file line by line.
  while (!employeeDataFile.eof()) {
    getline(employeeDataFile, employeeID, ',');
    getline(employeeDataFile, name, ',');
    getline(employeeDataFile, role, ',');
    getline(employeeDataFile, password);

    // Check if the employee ID matches the employee ID at the specified index.
    if (lineCount == index) {
      if (field == "name") {
        name = value;
      } else if (field == "role") {
        role = value;
      } else if (field == "password") {
        password = value;
      } else if (field == "deleteAll") {
        lineCount++;
        continue;
      } else {
        cout << "Invalid field." << endl;
        return;
      }
    }

    // Increment the line count
    lineCount++;

    // Append the new line to the new file lines.
    newFileLines += employeeID + "," + name + "," + role + "," + password + "\n";
  }

  // Remove last new line break
  newFileLines = newFileLines.substr(0, newFileLines.length()-1);
  employeeDataFile.close();

  // Write the new file lines to the employee data file.
  ofstream newEmployeeDataFile; // Output file stream for the new employee data file
  newEmployeeDataFile.open("files/employeeData.csv"); // Open the employee data file
  newEmployeeDataFile << newFileLines; // Write the new file lines to the employee data file
  newEmployeeDataFile.close(); // Close the employee data file
}

/**
 * @brief Change the employee name based on the index.
 * 
 * @param employees An array of Employee objects.
 * @param index The index of the employee.
 * @param name The new name of the employee.
 * 
 * @return None.
 */
void Employee::changeEmployeeRole (Employee employees [], int index, string role) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << this->role << " - Changing employee role..." << endl;

    // check if role is empty
    if (role == "") {
      cout << "Role cannot be empty." << endl;
      return;
    }

    // check if employee id is empty
    if (employees[index].employeeID == "") {
      cout << "Employee ID cannot be empty." << endl;
      return;
    }

    // check if name is empty
    if (employees[index].name == "") {
      cout << "Name cannot be empty." << endl;
      return;
    }

    // cannot change own role
    if (employeeID == employees[index].employeeID) {
      cout << "Warning: Cannot change own role." << endl;
      return;
    }

    // cannot change supervisor role
    if (employees[index].role == "Supervisor") {
      cout << "Warning: Cannot change supervisor role." << endl;
      return;
    }

    // role is the same
    if (employees[index].role == role) {
      cout << employees[index].name << "'s role is already " << role << "." << endl;
      return;
    }

    employees[index].role = role;

    // file handling of employee data file
    accessEmployeeDataFile(index, "role", role);

    cout << employees[index].name << "'s role has been changed to " << role << "." << endl;
  } else {
    cout << "Only supervisor can change employee role." << endl;
  }
}

/**
 * @brief Display all employee details in the employee list.
 * 
 * This function displays all the employee details in the employee list.
 * 
 * @param employees An array of Employee objects.
 * 
 * @return None.
 * 
 */
void Employee::displayAllEmployeeDetails(Employee employees []) const {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Displaying all employee details..." << endl;

    // Display the employee details in a table format.
    // Display the header of the table.
    cout << "+---+--------------------+--------------------+--------------------+" << endl;
    cout << "| " << left << setw(2) << "No" << "| ";
    cout << left << setw(19) << "Name" << "| ";
    cout << left << setw(19) << "Position" << "| ";
    cout << left << setw(19) << "Employee ID" << "|" << endl;
    cout << "+---+--------------------+--------------------+--------------------+" << endl;

    // Iterate through all the employees.
    for (int i = 0; i < Constant::MAX_EMPLOYEES; i++) {
      // check if employee id is not empty
      // display employee details in the table
      if (employees[i].employeeID != "") {
        cout << "| " << left << setw(2) << i+1 << "| ";
        cout << left << setw(19) << employees[i].name << "| ";
        cout << left << setw(19) << employees[i].role << "| ";
        cout << left << setw(19) << employees[i].employeeID << "|" << endl;
      }
    }
    cout << "+---+--------------------+--------------------+--------------------+" << endl;
  } else {
    cout << "Only supervisor can display all employee details." << endl;
  }
}

/**
 * @brief Delete the employee at the specified index.
 * 
 * This function deletes the employee based on the index provided.
 * The index should be a valid index within the employee list.
 * 
 * @param employees An array of Employee objects.
 * @param index The index of the employee.
 * 
 * @return None.
 */
void Employee::deleteEmployee(Employee employees [], int index) { 
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Deleting employee..." << endl;

    // check if employee id is empty
    if (employees[index].employeeID == "") {
      cout << "Employee ID cannot be empty." << endl;
      return;
    }

    // check if name is empty
    if (employees[index].name == "") {
      cout << "Name cannot be empty." << endl;
      return;
    }

    // cannot delete own account
    if (employeeID == employees[index].employeeID) {
      cout << "Warning: Cannot delete own account." << endl;
      return;
    }

    // cannot delete supervisor account
    if (employees[index].role == "Supervisor") {
      cout << "Warning: Cannot delete supervisor account." << endl;
      return;
    }

    // file handling of employee data file
    accessEmployeeDataFile(index, "deleteAll", "");

    cout << employees[index].role << " " << employees[index].name << " has been deleted." << endl;

    // delete employee object
    employees[index].name = "";
    employees[index].role = "";
    employees[index].employeeID = "";
    employees[index].supervisor = nullptr;
    employees[index].baker = nullptr;
    employees[index].cashier = nullptr;
  } else {
    cout << "Only supervisor can delete employee." << endl;
  }
}

/**
 * @brief Access the discount file and perform a search based on the specified field and value.
 * 
 * @param index The index of the discount in the discount file.
 * @param field The field to search for in the discount file.
 * @param value The value to match in the specified field.
 * 
 * @return None.
 */
void Employee::addNewDiscount() {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Adding new discount..." << endl;

    // Create discounts from user input
    string discountName; // String to store the name of the discount
    double minimumPurchase; // Double to store the minimum purchase amount
    double discountPercentage; // Double to store the discount percentage
    string discountDescription; // String to store the description of the discount
    bool disabled; // Boolean to store the disabled status of the discount

    // check if discount name is empty
    do {
      cin.ignore();
      cout << "Enter discount name: ";
      getline(cin, discountName);
    } while (discountName == "");

    // check if discount name exists
    // iterate through all discounts
    for (int i = 0; i < Constant::MAX_DISCOUNTS; i++) {
      // check if discount name exists
      if (discounts[i].getName() == discountName) {
        cout << "Discount name already exists." << endl;
        return;
      }
    }

    // input minimum purchase amount
    // minimum purchase amount must be more than 0
    do {
      cout << "Enter minimum purchase amount: RM ";
      cin >> minimumPurchase;
    } while (minimumPurchase < 0);

    // input discount percentage
    // discount percentage must be more than 0
    do {
      cout << "Enter discount percentage (%): ";
      cin >> discountPercentage;
    } while (discountPercentage < 0);

    cin.ignore();

    // input discount description
    // discount description must not be empty
    do {
      cout << "Enter discount description: ";
      getline(cin, discountDescription);
    } while (discountDescription == "");

    char available; // Char to store the availability of the discount

    // check if the discount is available
    // the discount is available if the user enters Y or y
    do {
      cout << "Is the discount available now? (Y/N): ";
      cin >> available;
      disabled = (available == 'N' || available == 'n');
    } while (available != 'Y' && available != 'y' && available != 'N' && available != 'n');

    // Set the disabled status based on the availability
    disabled = (available == 'N' || available == 'n');

    // iterate through all discounts
    for (int i = 0; i < Constant::MAX_DISCOUNTS; i++) {
      // check if discount name is empty
      if (discounts[i].getName() == "") {
        // store new discount in the first empty slot
        discounts[i] = Discount(discountName, minimumPurchase, discountPercentage, discountDescription, disabled);
        cout << "Discount '" << discountName << "' has been added successful!" << endl;

        // add new discount to files/discount.csv
        ofstream discountFile; // Output file stream for the discount file
        discountFile.open("files/discount.csv", ios::app); // Open the discount file in append mode
        discountFile << endl << discountName << "," << minimumPurchase << "," << discountPercentage << "," << discountDescription << "," << (disabled ? "false" : "true"); // Append the discount details to the file
        discountFile.close(); // Close the discount file

        return;
      }
    }

    cout << "Warning: Maximum number of discounts reached." << endl;
  } else {
    cout << "Only supervisor can add new discount." << endl;
  }
}

/**
 * @brief Access the discount file and perform a search based on the specified field and value.
 * 
 * @param index The index of the discount in the discount file.
 * @param field The field to search for in the discount file.
 * @param value The value to match in the specified field.
 * 
 * @return None.
 */
void Employee::accessDiscountFile(int index, string field, string value) {
  // Open the discount file in input mode.
  ifstream discountFile; // Input file stream for the discount file
  discountFile.open("files/discount.csv", ios::in); // Open the discount file in input mode
  string line; // String to store each line of the file
  string newFileLines; // String to store the new file lines after modification

  string name; // String to store the name of the discount
  string minimumPurchase; // String to store the minimum purchase amount
  string discountPercentage; // String to store the discount percentage
  string description; // String to store the description of the discount
  string disabled; // String to store the disabled status of the discount

  // Check if the discount file is found.
  // If the file is not found, display a message and return.
  if (!discountFile) {
    cout << "File not found." << endl;
    return;
  }

  // Read the discount file line by line.
  while (!discountFile.eof()) {
    getline(discountFile, name, ',');
    getline(discountFile, minimumPurchase, ',');
    getline(discountFile, discountPercentage, ',');
    getline(discountFile, description, ',');
    getline(discountFile, disabled);

    // cout << name << "," << minimumPurchase << "," << discountPercentage << "," << description << "," << disabled << endl;

    // Check if the name matches the discount name at the specified index.
    // Check if the field is name, minimumPurchase, discountPercentage, description, or disabled.
    if (name == discounts[index].getName()) {
      if (field == "name") {
        name = value;
      } else if (field == "minimumPurchase") {
        minimumPurchase = value;
      } else if (field == "discountPercentage") {
        discountPercentage = value;
      } else if (field == "description") {
        description = value;
      } else if (field == "disabled") {
        disabled = value;
      } else if (field == "deleteAll") {
        continue;
      } else {
        cout << "Invalid field." << endl;
        return;
      }
    }

    // Append the new line to the new file lines.
    newFileLines += name + "," + minimumPurchase + "," + discountPercentage + "," + description + "," + disabled + "\n";
  }

  // Remove last line
  newFileLines = newFileLines.substr(0, newFileLines.length()-1);
  discountFile.close();

  // Write the new file lines to the discount file.
  ofstream newDiscountFile; // Output file stream for the new discount file
  newDiscountFile.open("files/discount.csv"); // Open the discount file
  newDiscountFile << newFileLines; // Write the new file lines to the discount file
  newDiscountFile.close(); // Close the discount file
}

/**
 * @brief Edit the discount name at the specified index.
 * 
 * This function edits the discount name based on the index provided.
 * The index should be a valid index within the discount list.
 * 
 * @param index The index of the discount.
 * @param name The new name of the discount.
 * 
 * @return None.
 */
void Employee::editDiscountName(int index, string newName) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Editing discount name..." << endl;

    // edit name in files/discount.csv
    accessDiscountFile(index, "name", newName);
    discounts[index].setName(newName);
    cout << "New name has been updated for discount '" << discounts[index].getName() << "'." << endl;
  } else {
    cout << "Only supervisor can edit discount name." << endl;
  }
}

/**
 * @brief Edit the discount minimum purchase at the specified index.
 * 
 * This function edits the discount minimum purchase based on the index provided.
 * The index should be a valid index within the discount list.
 * 
 * @param index The index of the discount.
 * @param newMinimumPurchase The new minimum purchase of the discount.
 * 
 * @return None.
 */
void Employee::editDiscountMinimumPurchase(int index, double newMinimumPurchase) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Editing minimum purchase..." << endl;

    // edit minimum purchase in files/discount.csv
    accessDiscountFile(index, "minimumPurchase", to_string(newMinimumPurchase));

    discounts[index].setMinimumPurchase(newMinimumPurchase);
    cout << "Minimum purchase has been updated for discount '" << discounts[index].getName() << "'." << endl;
  } else {
    cout << "Only supervisor can edit minimum purchase." << endl;
  }
}

/**
 * @brief Edit the discount percentage at the specified index.
 * 
 * This function edits the discount percentage based on the index provided.
 * The index should be a valid index within the discount list.
 * 
 * @param index The index of the discount.
 * @param newPercentage The new percentage of the discount.
 * 
 * @return None.
 */
void Employee::editDiscountPercentage(int index, double newPercentage) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Editing discount percentage..." << endl;

    // edit percentage in files/discount.csv
    accessDiscountFile(index, "discountPercentage", to_string(newPercentage));

    discounts[index].setDiscountPercentage(newPercentage);
    cout << "Percentage has been updated for discount '" << discounts[index].getName() << "'." << endl;
  } else {
    cout << "Only supervisor can edit discount percentage." << endl;
  }
}

/**
 * @brief Edit the discount description at the specified index.
 * 
 * This function edits the discount description based on the index provided.
 * The index should be a valid index within the discount list.
 * 
 * @param index The index of the discount.
 * @param newDescription The new description of the discount.
 * 
 * @return None.
 */
void Employee::editDiscountDescription(int index, string newDescription) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Editing discount description..." << endl;

    // edit description in files/discount.csv
    accessDiscountFile(index, "description", newDescription);

    discounts[index].setDescription(newDescription);
    cout << "Description has been updated for '" << discounts[index].getName() << "'." << endl;
  } else {
    cout << "Only supervisor can edit discount description." << endl;
  }
}

/**
 * @brief Disable the discount at the specified index.
 * 
 * This function disables the discount based on the index provided.
 * The index should be a valid index within the discount list.
 * 
 * @param index The index of the discount.
 * 
 * @return None.
 */
void Employee::disableDiscount(int index) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Disabling discount..." << endl;

    // edit disabled in files/discount.csv
    accessDiscountFile(index, "disabled", "true");

    discounts[index].setDisabled(true);
    cout << "'" << discounts[index].getName() << "' has been disabled." << endl;
  } else {
    cout << "Only supervisor can disable discount." << endl;
  }
}

/**
 * @brief Enable the discount at the specified index.
 * 
 * This function enables the discount based on the index provided.
 * The index should be a valid index within the discount list.
 * 
 * @param index The index of the discount.
 * 
 * @return None.
 */
void Employee::enableDiscount(int index) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Enabling discount..." << endl;

    // edit disabled in files/discount.csv
    accessDiscountFile(index, "disabled", "false");

    discounts[index].setDisabled(false);
    cout << "'" << discounts[index].getName() << "' has been enabled." << endl;
  } else {
    cout << "Only supervisor can enable discount." << endl;
  }
}

/**
 * @brief Delete the discount at the specified index.
 * 
 * This function deletes the discount based on the index provided.
 * The index should be a valid index within the discount list.
 * 
 * @param index The index of the discount.
 * 
 * @return None.
 */
void Employee::deleteDiscount(int index) {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << role << " - Deleting discount..." << endl;

    // delete discount in files/discount.csv
    accessDiscountFile(index, "deleteAll", "");

    cout << "Discount '" << discounts[index].getName() << "' has been deleted." << endl;
    discounts[index].setName("");
    discounts[index].setMinimumPurchase(0);
    discounts[index].setDiscountPercentage(0);
    discounts[index].setDescription("");
    discounts[index].setDisabled(false);

  } else {
    cout << "Only supervisor can delete discount." << endl;
  }
}

/**
 * @brief Display the balance sheet of the bakery.
 * 
 * @param None.
 * @return None.
 */
void Employee::displayBalanceSheet() const {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    // cout << role << " - Displaying balance sheet..." << endl;

    // Display the balance sheet in a table format.
    ifstream balanceSheetFile; // Input file stream for the balance sheet file
    balanceSheetFile.open("files/balanceSheet.csv", ios::in); // Open the balance sheet file in input mode
    string line; // String to store each line of the file

    // Check if the balance sheet file is found.
    // If the file is not found, display a message and return.
    if (!balanceSheetFile) {
      cout << "Balance sheet not found." << endl;
      return;
    }

    // Display the header of the table.
    cout << endl;
    cout << "*****************************Balance Sheet***************************\n";
    cout << "+----------------+----------------+----------------+----------------+" << endl;
    cout << "| " << left << setw(15) << "Date" << "| ";
    cout << left << setw(15) << "Total Debit" << "| ";
    cout << left << setw(15) << "Total Credit" << "| ";
    cout << left << setw(15) << "Total Balance" << "|" << endl;
    cout << "+----------------+----------------+----------------+----------------+" << endl;

    getline(balanceSheetFile, line); // skip first line

    // Read the balance sheet file line by line.
    while (!balanceSheetFile.eof()) {
      getline(balanceSheetFile, line, ',');
      cout << "| " << left << setw(15) << line << "| ";
      getline(balanceSheetFile, line, ',');
      cout << left << setw(15) << line << "| ";
      getline(balanceSheetFile, line, ',');
      cout << left << setw(15) << line << "| ";
      getline(balanceSheetFile, line);
      cout << left << setw(15) << line << "|" << endl;
    }
    cout << "+----------------+----------------+----------------+----------------+" << endl;
    balanceSheetFile.close();
  } else {
    cout << "Only supervisor can display balance sheet." << endl;
  }
}

/**
 * @brief Access the transaction history file and perform a search based on the specified date.
 * 
 * @param date The date to search for in the transaction history file.
 * 
 * @return None.
 */
void Employee::accessTransactionHistory (string date) const {
  // Check if the employee is a supervisor.
  if (supervisor != nullptr) {
    cout << endl;
    cout << role << " - Accessing " + date + " transaction history ..." << endl;

    ifstream transactionHistoryFile; // Input file stream for the transaction history file
    transactionHistoryFile.open("files/transactions/transaction-"+date+".csv", ios::in); // Open the transaction history file in input mode

    // Check if the transaction history file is found.
    if (!transactionHistoryFile) {
      cout << "Transaction history for " + date + " not found." << endl;
      return;
    }

    string line; // String to store each line of the file

    // Display the transaction history in a table format.
    // Display the header of the table.
    cout << "+-----------+----------------+----------------+---------------------------------------------------+-----------+----------------+----------------+----------------+" << endl;
    cout << "| " << left << setw(10) << "Order ID" << "| ";
    cout << left << setw(15) << "Time" << "| ";
    cout << left << setw(15) << "Cashier ID" << "| ";
    cout << left << setw(50) << "Items Bought" << "| ";
    cout << left << setw(10) << "Quantity" << "| ";
    cout << left << setw(15) << "Payment Method" << "| ";
    cout << left << setw(15) << "Dine In" << "| ";
    cout << left << setw(15) << "Total Price" << "|" << endl;
    cout << "+-----------+----------------+----------------+---------------------------------------------------+-----------+----------------+----------------+----------------+" << endl;

    getline(transactionHistoryFile, line); // skip first line (header)

    // Read the transaction history file line by line.
    while (!transactionHistoryFile.eof()) {
      // orderID
      getline(transactionHistoryFile, line, ',');
      cout << "| " << left << setw(10) << line << "| ";
      
      // dateTime
      getline(transactionHistoryFile, line, ' '); // remove date
      getline(transactionHistoryFile, line, ',');
      cout << left << setw(15) << line << "| ";
      
      // cashierID
      getline(transactionHistoryFile, line, ',');
      cout << left << setw(15) << line << "| ";
      
      // itemsBought
      getline(transactionHistoryFile, line, '"'); // remove first double quote
      getline(transactionHistoryFile, line, '"'); // get items bought
      cout << left << setw(50) << line << "| ";
      getline(transactionHistoryFile, line, ','); // remove trailing comma after double quote
      
      // quantity
      getline(transactionHistoryFile, line, '"'); // remove first double quote
      getline(transactionHistoryFile, line, '"'); // get quantity
      cout << left << setw(10) << line << "| ";
      getline(transactionHistoryFile, line, ','); // remove trailing comma after double quote
      
      // paymentMethod
      getline(transactionHistoryFile, line, ',');
      cout << left << setw(15) << line << "| ";
      
      // dineIn
      getline(transactionHistoryFile, line, ',');
      cout << left << setw(15) << line << "| ";
      
      // totalPrice
      getline(transactionHistoryFile, line);
      cout << left << setw(15) << line << "|" << endl;
  }
    cout << "+-----------+----------------+----------------+---------------------------------------------------+-----------+----------------+----------------+----------------+" << endl;
    transactionHistoryFile.close();
    
  } else {
    cout << "Only supervisor can access transaction history." << endl;
  }
}

/**
 * @note The following functions are accessible by the baker only.
 * 
 */
void Employee::bakeNewBakeryItem(int index, int quantity) {
  // Check if the employee is a baker.
  if (baker != nullptr) {
    cout << endl;
    cout << role << " - Baking " << quantity << "x " << bakeryItems[index].getBakeryItemName() << "..." << endl;

    // check if bakery item is disabled
    if (bakeryItems[index].getDisabled()) {
      cout << "Warning: " << bakeryItems[index].getBakeryItemName() << " is withdrawn." << endl;
      return;
    }

    // check if ingredient is enough
    bool foundIngredient; // Flag of boolean to check if the ingredient is found in the inventory
    int * ingredientInventoryIndex = new int[MAX_INGREDIENTS]; // Array of integers to store the index of the ingredient in the inventory

    // iterate through all ingredients
    for (int i = 0; i < bakeryItems[index].getIngredientCount(); i++) {
      foundIngredient = false; // Set the found ingredient flag to false

      // iterate through all ingredient inventory
      for (int j = 0; j < ingredientInventory->getIngredientInventoryCount(); j++) {
        // check if ingredient is found in inventory
        if (bakeryItems[index].getIngredient(i)->getName() == ingredientInventory->getIngredientInventoryName(j)) {
          // cout << "Ingredient " << bakeryItems[index].getIngredient(i)->getName() << " found in inventory." << endl;

          // check if ingredient is countable
          if ((ingredientInventory+j)->getIngredient().getCountable()) {
            // check if ingredient is enough
            if (bakeryItems[index].getIngredient(i)->getPiece() * quantity > ingredientInventory->getIngredientInventoryPiece(j)) {
              cout << "===========================================" << endl;
              cout << "Not enough ingredient '" << bakeryItems[index].getIngredient(i)->getName() << "' in inventory." << endl;
              cout << "Available: " << ingredientInventory->getIngredientInventoryPiece(j) << " piece(s)." << endl;
              cout << "Require " << bakeryItems[index].getIngredient(i)->getPiece() * quantity << " piece(s)." << endl;
              cout << "===========================================" << endl;
              return;
            } else {
              // cout << "Enough " << bakeryItems[index].getIngredient(i)->getName() << " in inventory." << endl;
              ingredientInventoryIndex[i] = j;
              foundIngredient = true;
              break; // Exit the loop
            }
          } else {
            // check if ingredient is enough
            if (bakeryItems[index].getIngredient(i)->getWeight() * quantity > ingredientInventory->getIngredientInventoryWeight(j)) {
              cout << "===========================================" << endl;
              cout << "Not enough ingredient '" << bakeryItems[index].getIngredient(i)->getName() << "' in inventory." << endl;
              cout << "Available: " << ingredientInventory->getIngredientInventoryWeight(j) << " gram(s)." << endl;
              cout << "Require " << bakeryItems[index].getIngredient(i)->getWeight() * quantity << " gram(s)." << endl;
              cout << "===========================================" << endl;
              return;
            } else {
              // cout << "Enough " << bakeryItems[index].getIngredient(i)->getName() << " in inventory." << endl;
              ingredientInventoryIndex[i] = j;
              foundIngredient = true;
              break; // Exit the loop
            }
          }
        }
      }

      // check if ingredient is not found in inventory
      if (!foundIngredient) {
        cout << "===========================================" << endl;
        cout << "Warning: Ingredient '" << bakeryItems[index].getIngredient(i)->getName() << "' not found in inventory." << endl;
        cout << "Please restock ingredient '" << bakeryItems[index].getIngredient(i)->getName() << "' before baking." << endl;
        cout << "===========================================" << endl;
        return;
      }

      // Deduct ingredients from inventory
      // Deduct the ingredient based on the quantity
      if (i == bakeryItems[index].getIngredientCount() - 1) {
      cout << endl;
      cout << "==========Ingredient Inventory==========" << endl;
        // iterate through all ingredients
        for (int i = 0; i < bakeryItems[index].getIngredientCount(); i++) {
          // check if ingredient is countable
          if (bakeryItems[index].getIngredient(i)->getCountable()) {
            // cout << bakeryItems[index].getIngredient(i)->getPiece() * quantity << " pieces of ingredient " << bakeryItems[index].getIngredient(i)->getName() << " has been used." << endl;
            cout << endl;
            cout << "Original piece: " << ingredientInventory->getIngredientInventoryPiece(ingredientInventoryIndex[i]) << " pieces." << endl;
            cout << "Remaining: " << ingredientInventory->getIngredientInventoryPiece(ingredientInventoryIndex[i]) - bakeryItems[index].getIngredient(i)->getPiece() * quantity << " pieces." << endl;
            // deduct ingredient piece
            // ingredient piece = ingredient piece - bakery item ingredient piece * quantity
            ingredientInventory->setIngredientInventoryPiece(ingredientInventoryIndex[i], ingredientInventory->getIngredientInventoryPiece(ingredientInventoryIndex[i]) - bakeryItems[index].getIngredient(i)->getPiece() * quantity);
            // cout << bakeryItems[index].getIngredient(i)->getPiece() * quantity << " pieces of ingredient " << bakeryItems[index].getIngredient(i)->getName() << " has been used." << endl;

            // get index of ingredient in inventory
            int j;
            for (j = 0; j < ingredientInventory->getIngredientInventoryCount(); j++) {
              if (bakeryItems[index].getIngredient(i)->getName() == ingredientInventory->getIngredientInventoryName(j)) {
                ingredientInventoryIndex[i] = j;
                break;
              }
            }

            // file handling of ingredient inventory file
            accessIngredientInventoryFile(j, "piece", to_string(ingredientInventory->getIngredientInventoryPiece(ingredientInventoryIndex[i])));

            // cout << "Remaining: " << ingredientInventory->getIngredientInventoryPiece(ingredientInventoryIndex[i]) << " pieces." << endl;
          } else {
            // cout << bakeryItems[index].getIngredient(i)->getWeight() * quantity << " gram(s) of ingredient " << bakeryItems[index].getIngredient(i)->getName() << " has been used." << endl;
            cout << endl;
            cout << "Original weight: " << ingredientInventory->getIngredientInventoryWeight(ingredientInventoryIndex[i]) << " gram(s)." << endl;
            cout << "Remaining: " << ingredientInventory->getIngredientInventoryWeight(ingredientInventoryIndex[i]) - bakeryItems[index].getIngredient(i)->getWeight() * quantity << " gram(s)." << endl;
            // deduct ingredient weight
            // ingredient weight = ingredient weight - bakery item ingredient weight * quantity
            ingredientInventory->setIngredientInventoryWeight(ingredientInventoryIndex[i], ingredientInventory->getIngredientInventoryWeight(ingredientInventoryIndex[i]) - bakeryItems[index].getIngredient(i)->getWeight() * quantity);
            // cout << bakeryItems[index].getIngredient(i)->getWeight() * quantity << " gram(s) of ingredient " << bakeryItems[index].getIngredient(i)->getName() << " has been used." << endl;

            // get index of ingredient in inventory
            int j;
            for (j = 0; j < ingredientInventory->getIngredientInventoryCount(); j++) {
              if (bakeryItems[index].getIngredient(i)->getName() == ingredientInventory->getIngredientInventoryName(j)) {
                ingredientInventoryIndex[i] = j;
                break;
              }
            }

            // file handling of ingredient inventory file
            accessIngredientInventoryFile(j, "weight", to_string(ingredientInventory->getIngredientInventoryWeight(ingredientInventoryIndex[i])));

            // cout << "Remaining: " << ingredientInventory->getIngredientInventoryWeight(ingredientInventoryIndex[i]) << " gram(s)." << endl;
          }
        }
      }

      // Add bakery item quantity
      // bakery item quantity = bakery item quantity + quantity
      bakeryItems[index].setBakeryItemQuantity(bakeryItems[index].getBakeryItemQuantity() + quantity);

    }
    cout << "======================================" << endl;
    cout << quantity << "x bakery item " << bakeryItems[index].getBakeryItemName() << " has been baked." << endl;
  } else {
    cout << "Only baker can bake bakery item." << endl;
  }
}

/**
 * @brief Add a bakery item to the cart.
 * 
 * This function adds a bakery item to the cart based on the index and quantity provided.
 * The index should be a valid index within the bakery item list.
 * 
 * @param index The index of the bakery item.
 * @param quantity The quantity of the bakery item.
 * 
 * @return None.
*/
void Employee::addBakeryItemToCart (int index, int quantity) {
  cout << role << " - Adding " << quantity << "x " << bakeryItems[index].getBakeryItemName() << " to cart..." << endl;

  // Check if the employee is a cashier.
  if (cashier != nullptr) {
    // check if bakery item is disabled
    if (bakeryItems[index].getDisabled()) {
      cout << "Warning: " << bakeryItems[index].getBakeryItemName() << " is withdrawn." << endl;
      return;
    }

    // check if bakery item is enough
    if (bakeryItems[index].getBakeryItemQuantity() < quantity) {
      cout << "Warning: Not enough " << bakeryItems[index].getBakeryItemName() << " in inventory." << endl;
      cout << "Available: " << bakeryItems[index].getBakeryItemQuantity() << " item(s)." << endl;
      // cout << "Require " << quantity << " item(s)." << endl;
      return;
    }

    // add bakery item to cart
    cashier->getCart()->addBakeryItemToCart(bakeryItems[index], quantity);
    cout << quantity << "x " << bakeryItems[index].getBakeryItemName() << " has been added to cart." << endl;
  } else {
    cout << "Only cashier can add bakery item to cart." << endl;
  }
}

/**
 * @brief Add a cake by weight to the cart.
 * 
 * This function adds a cake by weight to the cart based on the index and weight provided.
 * The index should be a valid index within the bakery item list.
 * 
 * @param index The index of the bakery item.
 * @param weight The weight of the cake.
 * 
 * @return None.
*/
void Employee::addCakeByWeightToCart(int index, int weight) {
  cout << role << " - Adding " << weight << "g " << bakeryItems[index].getBakeryItemName() << " to cart..." << endl;

  // Check if the employee is a cashier.
  if (cashier != nullptr) {
    // check if bakery item is disabled
    if (bakeryItems[index].getDisabled()) {
      cout << "Warning: " << bakeryItems[index].getBakeryItemName() << " is withdrawn." << endl;
      return;
    }

    // check if bakery item is cake
    if (bakeryItems[index].getBakeryItemCategory() != "Cake") {
      cout << "Warning: " << bakeryItems[index].getBakeryItemName() << " is not a cake." << endl;
      return;
    }

    // check if bakery item is enough
    if (bakeryItems[index].getBakeryItemQuantity() * bakeryItems[index].getCake()->getTotalWeight() < weight) {
      cout << "Warning: Not enough " << bakeryItems[index].getBakeryItemName() << " in inventory." << endl;
      cout << "Available: " << bakeryItems[index].getBakeryItemQuantity() << " gram(s)." << endl;
      // cout << "Require " << weight << " gram(s)." << endl;
      return;
    }

    // add cake by weight to cart
    cashier->getCart()->addCakeByWeightToCart(bakeryItems[index], weight);
    cout << weight << "g " << bakeryItems[index].getBakeryItemName() << " has been added to cart." << endl;
  } else {
    cout << "Only cashier can add cake by weight to cart." << endl;
  }
}

/**
 * @brief Display the cart details of the cashier.
 * 
 * This function displays the cart details of the cashier.
 * 
 * @param None.
 * @return None.
 * 
 */
void Employee::displayCartDetails () const {
  // Check if the employee is a cashier.
  if (cashier != nullptr) {
    cout << "Cashier " << name << " (" << employeeID << ") - Displaying cart details..." << endl;

    // display cart details
    cashier->getCart()->displayCartDetails();
  } else {
    cout << "Only cashier can display cart details." << endl;
  }
}

/**
 * @brief Calculate the total cost of the cart.
 * 
 * This function calculates the total cost of the cart.
 * 
 * @param None.
 * @return None.
 * 
 */
void Employee::calculateCartTotalCost () const {
  // Check if the employee is a cashier.
  if (cashier != nullptr) {
    cout << "Cashier " << name << " (" << employeeID << ") - Calculating total cost..." << endl;
    cout << setprecision(2) << fixed;
    cout << "Total cost: RM " << cashier->getCart()->calculateTotalCost() << endl;
  } else {
    cout << "Only cashier can calculate total cost." << endl;
  }
}

/**
 * @brief Calculate the total price of the cart.
 * 
 * This function calculates the total price of the cart.
 * 
 * @param None.
 * @return None.
 * 
 */
void Employee::calculateCartTotalPrice () const {
  // Check if the employee is a cashier.
  if (cashier != nullptr) {
    cout << "Cashier " << name << " (" << employeeID << ") - Calculating total price..." << endl;
    cout << setprecision(2) << fixed;
    cout << "Total price: RM " << cashier->getCart()->calculateTotalPrice() << endl;
  } else {
    cout << "Only cashier can calculate total price." << endl;
  }
}

/**
 * @brief Calculate the total profit of the cart.
 * 
 * This function calculates the total profit of the cart.
 * 
 * @param None.
 * @return None.
 * 
 */
void Employee::calculateCartTotalProfit () const {
  // Check if the employee is a cashier.
  if (cashier != nullptr) {
    cout << "Cashier " << name << " (" << employeeID << ") - Calculating total profit..." << endl;
    cout << setprecision(2) << fixed;
    cout << "Total profit: RM " << cashier->getCart()->calculateTotalProfit() << endl;
  } else {
    cout << "Only cashier can calculate total profit." << endl;
  }
}

/**
 * @brief Get the cart item count.
 * 
 * This function gets the cart item count.
 * 
 * @param None.
 * @return None.
 * 
 */
void Employee::getCartItemCount() const {
  // Check if the employee is a cashier.
  if (cashier != nullptr) {
    cout << "Cashier " << name << " (" << employeeID << ") - Getting cart item count..." << endl;
    cout << "Cart item count: " << cashier->getCart()->getCartItemCount() << endl;
  } else {
    cout << "Only cashier can get cart item count." << endl;
  }
}

/**
 * @brief Remove a bakery item from the cart.
 * 
 * This function removes a bakery item from the cart based on the index provided.
 * The index should be a valid index within the cart.
 * 
 * @param index The index of the bakery item in the cart.
 * @return None.
 */
void Employee::removeBakeryItemFromCart (int index) {
  // Check if the employee is a cashier.
  if (cashier != nullptr) {
    cout << "Removing " << cashier->getCart()->getBakeryItems()[index].getBakeryItemName() << " from cart..." << endl;

    // remove bakery item from cart
    cashier->getCart()->removeBakeryItemFromCart(index);

    // display message
    cout << cashier->getCart()->getBakeryItems()[index].getBakeryItemName() << " removed from cart." << endl;
  } else {
    cout << "Only cashier can remove bakery item from cart." << endl;
  }
}

/**
 * @brief Update the quantity of a bakery item in the cart.
 * 
 * This function updates the quantity of a bakery item in the cart based on the index and quantity provided.
 * The index should be a valid index within the cart.
 * 
 * @param index The index of the bakery item in the cart.
 * @param quantity The quantity of the bakery item.
 * @return None.
 */
void Employee::updateBakeryItemQuantityInCart(int index, int quantity) {
  // Check if the employee is a cashier.
  if (cashier != nullptr) {
    cout << "Editing " << cashier->getCart()->getBakeryItems()[index].getBakeryItemName() << " quantity in cart..." << endl;

    // update bakery item quantity in cart
    cashier->getCart()->updateBakeryItemQuantity(index, quantity);

    // display message
    cout << cashier->getCart()->getBakeryItems()[index].getBakeryItemName() << " quantity in cart has been changed to " << quantity << "." << endl;
  } else {
    cout << "Only cashier can edit bakery item quantity in cart." << endl;
  }
}

/**
 * @brief Clear the cart.
 * 
 * This function clears the cart.
 * 
 * @param None.
 * @return None.
 */
void Employee::clearCart() {
  // Check if the employee is a cashier.
  if (cashier != nullptr) {
    cout << "Clearing cart..." << endl;

    // clear cart
    cashier->getCart()->clearCart();
    cout << "Cart has been cleared." << endl;
  } else {
    cout << "Only cashier can clear cart." << endl;
  }
}

/**
 * @brief Show available discounts based on cart total price.
 * 
 * This function shows the available discounts based on the cart total price.
 * 
 * @param None.
 * @return None.
 */
void Employee::showDiscountBasedOnCartTotalPrice() const {
  // Check if the employee is a cashier.
  if (cashier != nullptr) {
    cout << "Cashier " << name << " (" << employeeID << ") - Showing available discount based on cart total price..." << endl;

    // show discount based on cart total price
    bool isDiscountAvailable = false; // Flag of boolean to check if discount is available

    // iterate through all discounts
    for (int i = 0; i < discounts->getDiscountCount(); i++) {
      // check if cart total price is more than minimum purchase
      if (cashier->getCart()->calculateTotalPrice() >= discounts[i].getMinimumPurchase()) {
        cout << i+1 << ". " << discounts[i].getName() << endl;
        isDiscountAvailable = true; // Set the discount available flag to true
      }
    }

    // check if no discount available
    if (!isDiscountAvailable) {
      cout << "- Purchase doesn't qualify for discount. -" << endl;
    }

    // check if no discount available
    if (discounts->getDiscountCount() == 0) {
      cout << "No discount available." << endl;
    }
  } else {
    cout << "Only cashier can show discount based on cart total price." << endl;
  }
}

/**
 * @brief Apply the discount based on the choice.
 * 
 * This function applies the discount based on the choice provided.
 * The choice should be a valid choice within the available discounts.
 * 
 * @param choice The choice of the discount.
 * @return None.
 */
void Employee::applyDiscount(int choice) {
  // Find the index corresponding to the choice according to option in showDiscountBasedOnCartTotalPrice()
  bool isDiscountAvailable = false; // Flag of boolean to check if discount is available

  Discount* availableDiscounts[discounts->getDiscountCount()]; // Array of pointers to store the available discounts
  int count = 0; // Variable to store the count of available discounts

  // iterate through all discounts
  for (int i = 0; i < discounts->getDiscountCount(); i++) {
    // check if cart total price is more than minimum purchase
    if (cashier->getCart()->calculateTotalPrice() >= discounts[i].getMinimumPurchase()) {
      isDiscountAvailable = true; // Set the discount available flag to true
      // check if count is less than discount count
      if (count < discounts->getDiscountCount()) {
        availableDiscounts[count++] = &discounts[i]; // Store the discount in the available discounts array
      }
    }
  }

  // check if choice is more than count
  if (choice > count) {
    cout << "Invalid choice." << endl;
    return;
  }

  // apply discount
  if (cashier != nullptr) {
    cout << "Applying discount..." << endl;
    // check if cart total price is more than minimum purchase
    if (cashier->getCart()->calculateTotalPrice() >= availableDiscounts[choice - 1]->getMinimumPurchase()) {
      cout << "Discount applied: " << availableDiscounts[choice - 1]->getName() << endl;
      cout << "Discount amount: " << availableDiscounts[choice - 1]->getDiscountPercentage() << "%" << endl;

      // set total discount
      // total discount = total price * discount percentage
      cashier->getCart()->setTotalDiscount(cashier->getCart()->calculateTotalPrice() * (availableDiscounts[choice - 1]->getDiscountPercentage() / 100));
      cout << "Discount amount: RM " << cashier->getCart()->getTotalDiscount() << endl;
    } else {
      cout << "Warning: Purchase doesn't qualify for discount." << endl;
    }
    cout << endl;
  } else {
    cout << "Only cashier can apply discount." << endl;
  }
}

/**
 * @brief Get the available discount based on the choice.
 * 
 * This function gets the available discount based on the choice provided.
 * The choice should be a valid choice within the available discounts.
 * 
 * @param choice The choice of the discount.
 * @return The available discount based on the choice.
 */
Discount * Employee::getAvailableDiscount (int choice) const {
  // find the index corresponding to the choice according to option in showDiscountBasedOnCartTotalPrice()
  bool isDiscountAvailable = false; // Flag of boolean to check if discount is available
  Discount* availableDiscounts[discounts->getDiscountCount()]; // Array of pointers to store the available discounts
  int count = 0; // Variable to store the count of available discounts

  // iterate through all discounts
  for (int i = 0; i < discounts->getDiscountCount(); i++) {
    // check if cart total price is more than minimum purchase
    if (cashier->getCart()->calculateTotalPrice() >= discounts[i].getMinimumPurchase()) {
      isDiscountAvailable = true; // Set the discount available flag to true
      // check if count is less than discount count
      if (count < discounts->getDiscountCount()) {
        availableDiscounts[count++] = &discounts[i]; // Store the discount in the available discounts array
      }
    }
  }

  // check if choice is more than count
  if (choice > count) {
    return nullptr;
  }

  // check if the employee is a cashier
  if (cashier != nullptr) {
    // apply discount
    // check if cart total price is more than minimum purchase
    if (cashier->getCart()->calculateTotalPrice() >= availableDiscounts[choice - 1]->getMinimumPurchase()) {
      return availableDiscounts[choice - 1]; // Return the available discount based on the choice
    } else {
      return nullptr;
    }
  } else {
    return nullptr;
  }
}

/**
 * @brief Calculate the discounted total price of the cart.
 * 
 * This function calculates the discounted total price of the cart.
 * 
 * @param None.
 * @return The discounted total price of the cart.
 */
double Employee::calculateDiscountedTotalPrice () const {
  // Check if the employee is a cashier.
  if (cashier != nullptr) {
    cout << "Calculating discounted price..." << endl;
    cout << setprecision(2) << fixed;

    // calculate discounted price
    // discounted price = total price - total discount
    cout << "Discounted price: RM " << cashier->getCart()->calculateTotalPrice() - cashier->getCart()->getTotalDiscount() << endl;

    // return discounted price
    return cashier->getCart()->calculateTotalPrice() - cashier->getCart()->getTotalDiscount();
  } else {
    cout << "Only cashier can calculate discounted price." << endl;
    return 0;
  }
}

/**
 * @brief Checkout the cart.
 * 
 * This function checks out the cart.
 * 
 * @param dateTime The date and time of the checkout.
 * @note The date and time format is "YYYY-MM-DD HH:MM:SS".
 * 
 * @return None.
 */
void Employee::checkout(string dateTime) {
  // Check if the employee is a cashier.
  if (cashier != nullptr) {
    cout << "Checking out..." << endl;

    // Deduct bakery items in cart from bakery
    // iterate through all bakery items in cart
    for (int i = 0; i < cashier->getCart()->getCartItemCount(); i++) {
      // iterate through all bakery items
      for (int j = 0; j < bakeryItems->getBakeryItemCount(); j++) {
        // check if bakery item is found
        if (cashier->getCart()->getBakeryItems()[i].getBakeryItemName() == bakeryItems[j].getBakeryItemName()) {
          cout << endl;
          cout << "Checking out " << cashier->getCart()->getQuantity()[i] << "x " << cashier->getCart()->getBakeryItems()[i].getBakeryItemName() << "..." << endl;

          // check if bakery item is enough
          if (bakeryItems[j].getBakeryItemQuantity() < cashier->getCart()->getQuantity()[i]) {
            cout << "Warning: Not enough " << bakeryItems[j].getBakeryItemName() << " in bakery." << endl;
            cout << "Available: " << bakeryItems[j].getBakeryItemQuantity() << " bakery item(s)." << endl;
            cout << "Require " << cashier->getCart()->getQuantity()[i] << " bakery item(s)." << endl;

            // ask user to skip buying
            char skip; // Variable to store the skip choice

            // input skip choice
            // skip choice is either Y or N (case-insensitive)
            do {
              cout << "Do you want to skip buying this item? (Y/N): ";
              cin >> skip;
            } while (skip != 'Y' && skip != 'y' && skip != 'N' && skip != 'n');

            // check if skip is Y or y
            if (skip == 'Y' || skip == 'y') {
              // remove this item from cart
              cashier->getCart()->removeBakeryItemFromCart(i);

              // deduct bakery item quantity from bakery
              cout << bakeryItems[j].getBakeryItemQuantity() << "x " << bakeryItems[j].getBakeryItemName() << " has been removed from cart." << endl;
              continue;
            } else {
              cout << "Please inform supervisor to restock bakery item " << bakeryItems[j].getBakeryItemName() << " before checkout." << endl;
              return;
            }
          }

          cout << "Total price: RM " << cashier->getCart()->calculateTotalPrice() << endl;

          // deduct bakery item quantity from bakery
          // bakery item quantity = bakery item quantity - cart quantity
          bakeryItems[j].setBakeryItemQuantity(bakeryItems[j].getBakeryItemQuantity() - cashier->getCart()->getQuantity()[i]);
          cout << cashier->getCart()->getQuantity()[i] << "x " << cashier->getCart()->getBakeryItems()[i].getBakeryItemName() << " has been deducted from bakery." << endl;
        }
      }
    }

    // increment order number
    orderNo++;

    cout << "Order No: " << orderNo << endl;

    // Confirm cart
    cout << "Please reconfirm your cart: " << endl;
    this->displayCartDetails(); // Display the cart details
    cout << endl;

    // exit from empty cart
    if (cashier->getCart()->getCartItemCount() == 0) {
      cout << "Cart is empty. Please add bakery items to cart before checkout." << endl;
      return;
    }

    // Confirm checkout
    char proceed; // Variable to store the proceed choice

    // input proceed choice
    // proceed choice is either Y or N (case-insensitive)
    do {
      cout << "Do you want to proceed? (Y/N): ";
      cin >> proceed;
    } while (proceed != 'Y' && proceed != 'y' && proceed != 'N' && proceed != 'n');

    // check if proceed is N or n
    if (proceed == 'N' || proceed == 'n') {
      cout << "Checkout has been cancelled." << endl;
      return;
    }

    // Apply discount
    this->showDiscountBasedOnCartTotalPrice();
    cout << endl;

    int choice; // Variable to store the discount choice

    // input discount choice
    // discount choice is between 0 and available discount count
    do {
      cout << "Enter discount choice (0 to skip): ";
      cin >> choice;

      // check if choice is valid
      if (!(choice <= 0 || choice > this->getAvailableDiscountCount())) {
        cout << endl;
        this->applyDiscount(choice);
      }
    } while (choice < 0 || choice > this->getAvailableDiscountCount());

    // Calculate total price
    double totalPrice = this->calculateDiscountedTotalPrice();
    totalPrice = round(totalPrice * 100) / 100; // Round the total price to 2 decimal places
    cout << endl;
    cout << "Total price: RM " << totalPrice << endl;
    cout << endl;

    // Update total debit
    // total price is after discount
    // total debit = total debit + total price
    totalDebit += totalPrice;

    // Finish transaction
    // Payment method
    cout << "Payment method: " << endl;
    cout << "1 - Cash" << endl;
    cout << "2 - Credit Card" << endl;
    cout << "3 - Debit Card" << endl;
    cout << "4 - TnG" << endl;
    
    char paymentMethod; // Variable to store the payment method

    // input payment method
    // payment method is between 1 and 4
    do {
      cout << "Enter payment method: ";
      cin >> paymentMethod;
    } while (paymentMethod < '1' || paymentMethod > '4');
    cout << endl;

    // Dine in / Take away
    char dineIn; // Variable to store the dine in choice

    // input dine in choice
    // dine in choice is either Y or N (case-insensitive)
    do {
      cout << "Dine in? (Y/N): ";
      cin >> dineIn;
    } while (dineIn != 'Y' && dineIn != 'N' && dineIn != 'y' && dineIn != 'n');
    cout << endl;

    // Store transaction details to csv file
    // Generate receipt txt file
    ofstream transactionFile; // Variable to store the transaction file
    transactionFile.open("files/transactions/transaction-" + dateTime.substr(0, 4) + dateTime.substr(5, 2) + dateTime.substr(8, 2) + ".csv", ios::app); // Open the transaction file

    // input file stored in files/transactions/transaction-[YYYYMMDD].csv
    ifstream transactionFileCheck("files/transactions/transaction-" + dateTime.substr(0, 4) + dateTime.substr(5, 2) + dateTime.substr(8, 2) + ".csv");
    // check if file is empty
    if (transactionFileCheck.peek() == ifstream::traits_type::eof()) {
      // set header
      transactionFile << "orderID,dateTime,cashierID,itemsBought,paymentMethod,dineIn,totalPrice";
    } else {
      // set orderNo to the last orderNo in the file
      string line; // Variable to store the line
      while (!transactionFileCheck.eof()) {
        getline(transactionFileCheck, line);
      }

      // if orderID column is not a number (due to reading from header row), default is 0
      if (line.substr(0, line.find(',')) == "orderID") {
        orderNo = 1;
      } else {
        orderNo = stoi(line.substr(0, line.find(','))) + 1;
      }
    }
    transactionFileCheck.close();

    // store transaction details to csv file
    transactionFile << endl << orderNo << "," << dateTime << "," << employeeID << ",\"";
    // iterate through all bakery items in cart
    for (int i = 0; i < cashier->getCart()->getCartItemCount(); i++) {
      transactionFile << cashier->getCart()->getBakeryItems()[i].getBakeryItemName();
      // check if it is the last item
      if (i != cashier->getCart()->getCartItemCount() - 1) {
        transactionFile << ",";
      }
    }
    transactionFile << "\",\"" << cashier->getCart()->getQuantity()[0];
    // iterate through all quantities in cart
    for (int i = 1; i < cashier->getCart()->getCartItemCount(); i++) {
      transactionFile << "," << cashier->getCart()->getQuantity()[i];
    }
    transactionFile << "\"," <<
      (paymentMethod == '1' ? "Cash" : paymentMethod == '2' ? "Credit Card" : paymentMethod == '3' ? "Debit Card" : "TnG")
      << "," << (dineIn == 'Y' ? "true" : "false") << "," << totalPrice;
    transactionFile.close();

    // Receipt
    // generate receipt txt file
    // store in files/receipts/[YYYYMMDD]/receipt-[YYYYMMDD]-[orderID].txt
    string receiptFileName = "files/receipts/receipt-" + dateTime.substr(0, 4) + dateTime.substr(5, 2) + dateTime.substr(8, 2) + "-" + to_string(orderNo) + ".txt"; // Variable to store the receipt file name

    cout << "Generating receipt..." << endl;
    cout << "Filename: " << receiptFileName << endl;
    cout << endl;

    // write to receipt file
    ofstream receiptFile(receiptFileName); // Variable to store the receipt file
    receiptFile << "Eid Delights Bakery" << endl;
    receiptFile << "43-3-12, Persiaran Midlands," << endl;
    receiptFile << "Taman Midlands," << endl;
    receiptFile << "10500 Penang" << endl;
    receiptFile << "Tel : 011 2345 6789" << endl;
    receiptFile << endl;
    receiptFile << (dineIn == 'Y' ? "Dine In" : "Take Away") << endl;
    receiptFile << "--------------------------------------------------------------------" << endl;
    receiptFile << "Current Invoice" << endl;
    receiptFile << "R.No: " << orderNo << endl;
    receiptFile << "Date: " << dateTime << endl;
    receiptFile << "Transaction by: " << employeeID << endl;
    receiptFile << endl;

    receiptFile << left << setw(3) << "No" << setw(35) << "Description" << setw(20) << "Quantity" << "Price (RM)" << endl;

    // iterate through all bakery items in cart
    for (int i = 0; i < cashier->getCart()->getCartItemCount(); i++) {
        receiptFile << left << setw(3) << to_string(i+1) + ". ";
        receiptFile << left << setw(35) << cashier->getCart()->getBakeryItems()[i].getBakeryItemName();
        receiptFile << left << setw(20) << cashier->getCart()->getQuantity()[i];
        receiptFile << cashier->getCart()->getBakeryItems()[i].getPricePerUnit() *  cashier->getCart()->getQuantity()[i] << endl;
    }

    receiptFile << endl;
    receiptFile << "---------------------------------------------------------------------" << endl;
    string subtotal = "Subtotal (" + to_string(cashier->getCart()->getCartItemCount()) + ")"; // Variable to store the subtotal
    receiptFile << left << setw(60) << subtotal;
    receiptFile << totalPrice << endl;
    receiptFile << "---------------------------------------------------------------------" << endl;
    receiptFile << left << setw(60) << "Discount Summary" << "Amount" << endl;
    // check if discount is applied
    if (choice != 0) {
      receiptFile << left << setw(40) << "Discount Name" << getAvailableDiscount(choice)->getName() << endl;
      receiptFile << setprecision(2) << fixed;
      receiptFile << left << setw(60) << "Total Discount" << cashier->getCart()->getTotalDiscount() << endl;
    }
    receiptFile << "---------------------------------------------------------------------" << endl;
    receiptFile << left << setw(60) << "Total" << totalPrice << endl;
    string paymentMethodStr = (paymentMethod == '1' ? "Cash" : paymentMethod == '2' ? "Credit Card" : paymentMethod == '3' ? "Debit Card" : "TnG"); // Variable to store the payment method
    receiptFile << left << setw(60) << "Payment Method" << paymentMethodStr << endl;
    receiptFile << "---------------------------------------------------------------------" << endl;
    receiptFile << "Thank you for your purchase at our bakery!" << endl;
    receiptFile << "See you again soon." << endl;
    receiptFile.close();
    
    cout << "Thank you for your purchase at our bakery!" << endl;
    cout << "See you again soon." << endl << endl;

    // clear cart
    cashier->getCart()->clearCart();
  } else {
    cout << "Only cashier can checkout." << endl;
  }
}

/**
 * @brief Show the receipt based on the date and order number.
 * 
 * This function shows the receipt based on the date and order number provided.
 * 
 * @param date The date of the receipt.
 * @param orderNo The order number of the receipt.
 * @return None.
 */
void Employee::showReceipt(string date, int orderNo) const {
  if (cashier != nullptr || supervisor != nullptr) {
    // read from files/receipts/receipt-[YYYYMMDD]-[orderID].txt
    string receiptFileName = "files/receipts/" + date + "/receipt-" + date + "-" + to_string(orderNo) + ".txt"; // Variable to store the receipt file name
    cout << "Showing receipt..." << endl;
    cout << "Filename: " << receiptFileName << endl;
    cout << endl << endl;

    // read from receipt file
    ifstream receiptFile(receiptFileName); // Variable to store the receipt file
    // check if file is opened
    if (receiptFile) {
      string line; // Variable to store the line
      // read line by line
      while (getline(receiptFile, line)) {
        cout << line << endl;
      }
      receiptFile.close();
    } else {
      cout << "Unable to open file." << endl;
    }

    cout << endl << "**************************************";
    cout << endl;
  } else {
    cout << "Only supervisor or cashier can show receipt." << endl;
    return;
  }
}

/**
  * @brief Move the cart from this cashier to another cashier.
  * 
  * This function moves the cart from this cashier to another cashier.
  * 
  * @param cashier 
  */
void Employee::moveCartFromThisCashierToAnotherCashier(Employee * c) {
  // Check if the employee is a cashier.
  if (this->cashier != nullptr) {
    cout << "Moving cart from " << name << "..." << endl;

    // check if c is a cashier
    if (c->cashier == nullptr) {
      cout << "Only cashier can move cart around." << endl;
      return;
    }

    // move cart from this cashier to another cashier
    // using overloaded assignment operator
    *c->cashier = *this->cashier;

    // clear cart
    this->cashier->getCart()->clearCart();

    cout << "Cart has been moved from this cashier to another cashier." << endl;
  } else {
    cout << "Only cashier can move cart from this cashier to another cashier." << endl;
  }

}

/**
  * @brief Accessor for the employee ID.
  * @return The employee ID.
  */
string Employee::getEmployeeID() const {
  return employeeID;
}

/**
  * @brief Accessor for the name.
  * @return The name.
  */
string Employee::getName() const {
  return name;
}

/**
  * @brief Accessor for the role.
  * @return The role.
  */
string Employee::getRole() const {
  return role;
}

/**
  * @brief Accessor for the order number.
  * @return The order number.
  */
int Employee::getOrderNo() const {
  return orderNo;
}

/**
  * @brief Accessor for the total balance.
  * @return The total balance.
  */
double Employee::getTotalCredit() const {
  return totalCredit;
}

/**
  * @brief Accessor for the total debit.
  * @return The total debit.
  */
double Employee::getTotalDebit() const {
  return totalDebit;
}

/**
 * @brief Accessor for the total number of discount available.
 * 
 * This function counts the total number of discounts available in the bakery.
 * 
 * @return int 
 */
int Employee::getAllDiscountCount() const {
  return discounts->getDiscountCount();
}

/**
  * @brief Accessor for the total number of ingredient inventory.
  * 
  * This function counts the total number of ingredient inventory available in the bakery.
  * 
  * @return int 
  */
int Employee::getAllIngredientInventoryCount() const {
  return ingredientInventory->getIngredientInventoryCount();
}

/**
  * @brief Accessor for the total number of bakery items.
  * 
  * This function counts the total number of bakery items available in the bakery.
  * 
  * @return int 
  */
int Employee::getAllBakeryItemCount() const {
  return bakeryItems->getBakeryItemCount();
}

/**
  * @brief Mutator for the employee ID.
  * @param employeeID The employee ID to set.
  */
void Employee::setEmployeeID(string employeeID) {
  this->employeeID = employeeID;
}

/**
  * @brief Mutator for the name.
  * @param name The name to set.
  */
void Employee::setName(string name) {
  this->name = name;
}

/**
  * @brief Mutator for the role.
  * @param role The role to set.
  */
void Employee::setRole(string role) {
  this->role = role;

  if (role == "Supervisor") {
    this->supervisor = new Supervisor(employeeID, name);
  } else if (role == "Baker") {
    this->baker = new Baker(employeeID, name);
  } else if (role == "Cashier") {
    this->cashier = new Cashier(employeeID, name);
  }
}

/**
  * @brief Mutator for the password.
  * @param password The password to set.
  */
void Employee::setPassword (string password) {
  this->password = password;
}

/**
  * @brief Destructor for the Employee class.
  */
Employee::~Employee() {
  // free memory
  delete discounts;
  delete supervisor;
  delete baker;
  delete cashier;
}

// Static member initialization
IngredientInventory * Employee::ingredientInventory = new IngredientInventory[MAX_INGREDIENTS_INVENTORY]; // Initialize the ingredient inventory
BakeryItem * Employee::bakeryItems = new BakeryItem[MAX_BAKERY_ITEMS]; // Initialize the bakery items
Discount * Employee::discounts = nullptr; // Initialize the discounts
int Employee::orderNo = 0; // Initialize the order number
double Employee::totalBalance = 5000; // Initialize the total balance
double Employee::totalCredit = 0; // Initialize the total credit
double Employee::totalDebit = 0; // Initialize the total debit
double Employee::totalProfitPerDay = 0; // Initialize the total profit per day