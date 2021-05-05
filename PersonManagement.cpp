/******************************************************************************
05/05/21
*******************************************************************************/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

// Struct declaration
struct Person{  
    
    string personName,
           personDOB;
           
    long personSSN,
         fatherSSN,
         motherSSN;
    
    char personGender;
    
    float personHeight,
          personWeight;
    
    Person* next;                                         
};
// End struct declaration

// Function prototypes
void show_welcomeMsg();

void show_goodbyeMsg();

int user_input();                                   // Utility -- user input

bool menu_loop(bool, Person*);                      // Main menu

Person* populate_Person(string);                    // Initial dataset

struct Person* swap_Person(struct Person*,          // Utility -- swap nodes
                           struct Person*);

int get_nodeCount(Person*);                         // Utility

void print_PersonNodes(Person*);                    // Utility

Person* sort_bySSN(struct Person**);                // Option 1

Person* delete_Person(Person**);                    // Option 2

Person* input_newPerson(Person**);                  // Option 3

Person* add_bulkPerson(Person**);                   // Option 4

void edit_PersonData(Person*);                      // Option 5

void display_Eligibility(Person*);                  // Option 6

Person* cardiovascularDetermining(Person*);         // Option 7

float get_BMI(Person*);                             // Gets BMI

void sort_BMI(Person*);                             // Sorts BMI

Person* option_eight(Person*);

void display_Parents(Person*);                      // Option 9

Person* option_ten(Person*);

Person* option_eleven(Person*);

Person* option_twelve(Person*);
// End function prototypes

// Driver
int main() {
    
    // Hello
    show_welcomeMsg();
    
    // Var declarations
    bool quit = false;                  // Control flow
    
    string fileName = "persondata.txt"; // Modularize filename for both file 
                                        // function calls; initialize to file 1
                                        // Change to "supplement.txt" in #4 call
    // End var declarations
    
    // Initialize Struct 
    Person* head = new Person;  // Independent person
    head -> next = NULL;
    // End Struct initialization
    
    // Populate Struct w/ start file -- first "module" before calling menu
    head = populate_Person(fileName);

    // Initial list sort
    sort_bySSN(&head);
    
    // Initial List Print            
    print_PersonNodes(head);
    
    // Main menu loop
    while (quit == false && cin) {
        
        quit = menu_loop(quit, head);  //  Exit on flag
    }
    
    // Goodbye
    show_goodbyeMsg();
    
    return 0;
}    

// Function definitions

// Utility function to get person count
// Parameters: Person* (head)
// Returns: Int (# of nodes)
int get_nodeCount(Person* head) {
    
    Person* temp = head;
    
    int nodeCount = 0;
    
    while(temp != NULL) {
        
        nodeCount++;
        temp = temp -> next;
    }
    
    return nodeCount;
}

// Utility function to swap for sorting
// Parameters: Person* node
// Returns: Second Person* node as defined when called
struct Person* swap_Person(struct Person* nodeOne, struct Person* nodeTwo) {
    
    struct Person* temp = nodeTwo -> next;
    
    nodeTwo -> next = nodeOne;
    
    nodeOne -> next = temp;

    return nodeTwo;
}


// Find and print Parents of a person
// Parameters: Pointer to head of person struct
// Returns: Void
void display_Parents(Person* head)
{
    Person* targetPerson{head};
    Person* current{head};
    
    string currentLine{0};
    long searchSSN{0};
    
    cin.ignore();
    
    cout << "\nEnter the SSN of a person to find their Mother and Father " << endl;
    getline(cin,currentLine);
    
    searchSSN = stol(currentLine);
    
    
    while(current->next != NULL) // Associate entered SSN with actual person Node
    {
        if(searchSSN == current->personSSN)
        {
            std::cout<< "\nSSN entered matches " << current->personName << "\n\n";
            break;
        }
             
        
        current = current->next;
    }
    
    targetPerson = current;
    
    current = head; // Reset to the begining of the person list
    
    std::cout<< targetPerson->personName << " Parents: \n";
    
    while(current->next != NULL) // Compare target person's Mother SSN to the SSN of everyone else
    {
        if(targetPerson->motherSSN == current->personSSN)
        {
            std::cout<< "Mother: " << current->personName << '\n';
            break;
        }
        
        current = current->next;
    }
    
    if(current->next == NULL)
        std::cout<< " Mother is not on the list\n\n";
    
    current = head; // Reset to the begining of the person list
    
    while(current->next != NULL) // Compare target person's father SSN to the SSN of everyone else
    {
        if(targetPerson->fatherSSN == current->personSSN)
        {
            std::cout<< "Father: " << current->personName << "\n\n";
            break;
        }
    
        current = current->next;
    }
    
    if(current->next == NULL)
        std::cout<< "Father is not on the list\n\n";
    
}


// Instantiate new person from user input and insert into sorted list
// Parameters: Person** (reference pointer to head)
// Returns: Person* (head)
Person* input_newPerson(Person** head) {
    
    string currentLine;
        
    cin.ignore();
        
    int count = 0;
        
    Person* userPerson = new Person;

    cout << "Please enter the new person's name: " << endl;
        
    getline(cin, currentLine);
    userPerson -> personName = currentLine;
        
    cout << "Please enter the new person's SSN: " << endl;
        
    getline(cin, currentLine);
    userPerson -> personSSN = stol(currentLine); 
        
    cout << "Please enter the new person's gender: " << endl;
        
    getline(cin, currentLine);
    userPerson -> personGender = currentLine[0]; 
        
    cout << "Please enter the new person's DOB: " << endl;
        
    getline(cin, currentLine);
    userPerson -> personDOB = currentLine; 
    
    cout << "Please enter the new person's height: " << endl;

    getline(cin, currentLine);
    userPerson -> personHeight = stof(currentLine);
    
    cout << "Please enter the new person's weight: " << endl;
    
    getline(cin, currentLine);
    userPerson -> personWeight = stof(currentLine);
    
    cout << "Please enter the new person's father's SSN: " << endl;
    
    getline(cin, currentLine);
    userPerson -> fatherSSN = stol(currentLine);
    
    cout << "Please enter the new person's mother's SSN: " << endl;
    
    getline(cin, currentLine);
    userPerson -> motherSSN = stol(currentLine);
    
    Person* current = *head;
        
    struct Person** headPointer;
                
    headPointer = head;
    
    while (current -> next != NULL) {
        
        if (current -> personSSN < userPerson -> personSSN) {

            if (current -> next -> personSSN > userPerson -> personSSN) {
                
                Person* prev = current;
            
                userPerson -> next = prev -> next;
            
                prev -> next = userPerson;
                
                break;
            }    
   
        } else {
            
            userPerson -> next = (*headPointer);
            
            (*headPointer) = userPerson;
            
            break;
        }
            
        current = current -> next;
    }
        
    if (current -> next == NULL) {
                
        userPerson -> next = NULL;
                    
        current -> next = userPerson;
    }
    
    cout << "Addition operation successful!" << endl;
    
    cout << "Person " << userPerson -> personSSN << " added." << endl;
    
    cout << "Updating database..." << endl;
            
    return *head;
}

// Sort ascending by SSN w/ bubblesort -- recursive call to swap_Person
// Parameters: Reference pointer to head of person struct
// Returns: Person*
Person* sort_bySSN(struct Person** head) {
    
    struct Person** headPointer;
    
    int PersonCount = get_nodeCount(*head);
    
    bool sorted = false,
         done = false;
    
    for (int i = 0; i <= PersonCount; i++) {
        
        headPointer = head;
        
        for (int j = 0; j < (PersonCount - i - 1); j++) {
            
            struct Person* nodeOne = *headPointer;
            
            struct Person* nodeTwo = nodeOne -> next;
            
            if (nodeOne -> personSSN > nodeTwo -> personSSN) {
                
                *headPointer = swap_Person(nodeOne, nodeTwo);
                
                sorted = true;
                done = true;
            }
            
            headPointer = &(*headPointer) -> next;
        }
        
        if (done == false) {
            
            sorted = true;
        }
    }
      
    return *head;
}

// Display all persons eligible for social security
// Parameters: Pointer to head of person struct
// Returns: Void
void display_Eligibility(Person* head)
{
    Person* current{head};

    std::cout<< "\nEligible for social security: \n";

    while(current->next != NULL)
    {
        if( 2021 - stoi(current->personDOB.substr(0,4)) >= 65 )
        {
            std::cout<< current->personName << ": Age: " << 2021 - stoi(current->personDOB.substr(0,4)) << '\n';
        }
        
        current = current->next;
    }
}

// Edit Person  Name, Height and Weight for that SSN
// Parameters: Pointer to head of person struct
// Returns: Void
void edit_PersonData(Person* head)
{
    Person* current{head};
    
    long targetSSN{0};
    
    string currentLine;
    string newdata{""};
    
    cin.ignore();
    
    std::cout<< "Enter the SSN of the person to be edited: ";
    getline(cin,currentLine);
    
    targetSSN = stol(currentLine);
    
    
    while(current->next != NULL)
    {
        if(current->personSSN == targetSSN)
        {
            std::cout<< "SSN entered matches " << current->personName << '\n';
            std::cout<< "Editing commenced. Press 0 to keep original data\n";
            
            std::cout<< "Enter new Name: ";    
            getline(cin,newdata);
            if(newdata[0] != '0')
                current->personName = newdata;
            else
                std::cout<< "Retaining original data.\n";
            
            std::cout<< "Enter new Height: "; 
            getline(cin,newdata);
             if(newdata[0] != '0')
                current->personHeight = stof(newdata);
            else
                std::cout<< "Retaining original data.\n";
           
            
            std::cout<< "Enter new Weight: "; 
            getline(cin,newdata);
             if(newdata[0] != '0')
                current->personWeight= stof(newdata);
            else
                std::cout<< "Retaining original data.\n";
           
        }
        
        current = current->next;
    }
    
    std::cout<< "Editing Completed.\n";
    
}

// Print person Nodes
// Parameters: Pointer to head of person struct
// Returns: Void
void print_PersonNodes(Person* head) {

    Person* current = head;
    
    cout << endl;

    cout << "Here is the linked list of persons: " << endl << endl;

    while (current != NULL) {
        
        cout << current -> personName << " | "
             << current -> personSSN << " | "
             << current -> personGender << " | "
             << current -> personDOB << " | "
             << current -> personHeight << " | "
             << current -> personWeight << " | "
             << current -> fatherSSN << " | "
             << current -> motherSSN << " | "
             << endl;
        
        current = current -> next;
    }
    
    cout << endl; 
} 

// Welcome
// Parameters: None
// Returns: Void
void show_welcomeMsg() {                                                                
    cout << "Welcome to the Person Struct Linked List Manager!" 
         << endl << endl;
}

// Get user input
// Parameters: none
// Returns: Int
int user_input() {
    
    int inp = 0;
    
    while (cin >> inp) {
        
        return inp;
    } 
}

// Delete person from list, with user input SSN as key
// Parameters: Person** (Reference Person* -- call w/ &Person)
// Returns: Person*
Person* delete_Person(Person** head) {
    
    bool keyFound = false;
    
    string currentLine;
    
    cin.ignore();

    cout << "Enter the SSN of the person to be deleted: " << endl;
    
    getline(cin, currentLine);
    
    long key = stol(currentLine);
    
    Person* temp = *head;
    
    Person* prev = NULL;
    
    if (temp != NULL && temp -> personSSN == key) {

        *head = temp -> next;
        
        delete temp;
        
    } else {
        
        while (temp != NULL && temp -> personSSN != key) {
            
            prev = temp;
            
            temp = temp -> next;
            
            keyFound = true;
        }
    }
    
    if (temp == NULL) {
        
        cout << "Indicated SSN not found!" << endl;
        
        keyFound = false;
        
        cin.ignore();
        
        return *head;
    }    
    
    prev -> next = temp -> next;
        
    delete temp;
    
    cout << "Deletion operation successful!" << endl;
    
    cout << "Person " << temp -> personSSN << " deleted." << endl;
    
    cout << "Updating database..." << endl;
    
    return *head;
}

// Switchboard for menu options 
// Parameters: Bool, pointer to head of person struct
// Returns: Bool
bool menu_loop(bool quit, Person* head) {
    
    int choice = 0;
    
    bool dontQuitMenu = true;
    
    cout << "Menu Options: " << endl; 
    cout << "1: Display List By Ascending SSN" << endl;
    cout << "2: Delete Existing Person" << endl;
    cout << "3: Add New Person" << endl;
    cout << "4: Add New Persons From Supplemental File" << endl;
    cout << "5: Edit Person Data" << endl;
    cout << "6: Display all persons eligible for social security" << endl;
    cout << "7: Display all people at high risk for cardiovascular disease." << endl;
    cout << "8: " << endl;
    cout << "9: Display the parents of a person" << endl;
    cout << "10: " << endl;
    cout << "11: " << endl;
    cout << "12: " << endl;
         
    while (cin && dontQuitMenu == true) {
        
        cout << "Enter option 1-12, or enter -1 to show menu again. "
            << "Enter anything else to exit." << endl;    
        
        choice = user_input(); 
    
        switch (choice) {
        
            case -1:

                cout << "Menu options: " << endl;
                cout << "1: Display List By Ascending SSN" << endl;
                cout << "2: Delete Existing Person" << endl;
                cout << "3: Add New Person" << endl;
                cout << "4: Add New Persons From Supplemental File" << endl;
                cout << "5: Edit Person data" << endl;
                cout << "6: Display all persons eligible for social security" << endl;
                cout << "7: Display all people at high risk for cardiovascular disease." << endl;
                cout << "8: " << endl;
                cout << "9: Display the parents of a person" << endl;
                cout << "10: " << endl;
                cout << "11: " << endl;
                cout << "12: " << endl;
            
                break;
            
            case 1:
            
                cout << "Option 1: Display List By Ascending SSN" << endl;
                
                sort_bySSN(&head);
                
                print_PersonNodes(head);
            
                break;
        
            case 2:
            
                cout << "Option 2: Delete Existing Person" << endl;
                
                cin.clear();
                
                print_PersonNodes(head);
                
                head = delete_Person(&head);
                
                print_PersonNodes(head);
                
                break;
        
            case 3:
            
                cout << "Option 3: Add New Person" << endl;
            
                input_newPerson(&head);
                
                print_PersonNodes(head);

                break;
        
            case 4:
            
                cout << "Option 4: Add New Persons From Supplemental File" << endl;

                head = add_bulkPerson(&head);
    
                sort_bySSN(&head);
                
                print_PersonNodes(head);
            
                break;
        
            case 5:
            
                cout << "Option 5" << endl;
            
                print_PersonNodes(head);
                
                edit_PersonData(head); 
                
                print_PersonNodes(head);
            
                break;
        
            case 6:
            
                cout << " Option 6: Display all persons eligible for social security" << endl;
            
                display_Eligibility(head);
            
                break;
        
            case 7:
            
                cout << "7: Display all people at high risk for cardiovascular disease." << endl;
            
                head = option_seven(head);
            
                break;
            
            case 8:
            
                cout << "Option 8" << endl;
            
                head = option_eight(head);
            
                break;
            
            case 9:
            
                cout << "Option 9: Display the parents of a person" << endl;
            
                display_Parents(head);
            
                break;
            
            case 10:
            
                cout << "Option 10" << endl;
            
                head = option_ten(head);
            
                break;
            
            case 11:
            
                cout << "Option 11" << endl;
            
                head = option_eleven(head);
            
                break;
            
            case 12:
            
                cout << "Option 12" << endl;
            
                head = option_twelve(head);
            
                break;

            default:
            
                cout << "Terminating." << endl;
            
                return dontQuitMenu;
        }
    
    }
    return dontQuitMenu;
}    

// Populate persons from file and return person count
// Parameters: String -- initial file of 20 people (persondata.txt)
// Returns: Person*
Person* populate_Person(string fileName) {
    
    Person* head = new Person;
    head -> next = NULL;
    
    Person* current = head;
    Person* newPerson;
    
    ifstream dataFile;
    dataFile.open(fileName);
    
    string currentLine;
    
    while (!dataFile.eof()) {  
        
        getline(dataFile, currentLine);
        current -> personName = currentLine;
        
        getline(dataFile, currentLine);
        current -> personSSN = stol(currentLine); 
        
        getline(dataFile, currentLine);
        current -> personGender = currentLine[0]; 
        
        getline(dataFile, currentLine);
        current -> personDOB = currentLine; 

        getline(dataFile, currentLine);
        current -> personHeight = stof(currentLine);
        
        getline(dataFile, currentLine);
        current -> personWeight = stof(currentLine);
        
        getline(dataFile, currentLine);
        current -> fatherSSN = stol(currentLine);
        
        getline(dataFile, currentLine);
        current -> motherSSN = stol(currentLine);            
        
        newPerson = new Person;         
        current -> next = newPerson;    
        current = newPerson;
    }
    
    dataFile.close();
    
    current = head;
    
    Person* prevPerson;
    
    while (current -> next != NULL) {    
        
        prevPerson = current;
        
        current = current -> next;
    }
    
    prevPerson -> next = NULL;
    
    delete newPerson;
    
    newPerson -> next = NULL;
    
    current = head;
    
    cout << head -> personName << endl;
    cout << current -> personName << endl;
    
    return head;
}

// Populate persons from file and return person count
// Parameters: Person** (reference pointer to head)
// Returns: Person*
Person* add_bulkPerson(Person** head) {
    
    string suppLine;
          string fileName = "supplement.txt";
    
    Person* current = *head; 

    while (current -> next != NULL) {
        current = current -> next;
    } 
    
    ifstream dataFile;
    dataFile.open(fileName);

    while (!dataFile.eof()) { 
        
        Person* newPerson = new Person;
        current -> next = newPerson;    
        current = newPerson;
        
        getline(dataFile, suppLine);
        current -> personName = suppLine;
        
        getline(dataFile, suppLine);
        current -> personSSN = stol(suppLine);
                
        getline(dataFile, suppLine);
        current -> personGender = suppLine[0]; 
        
        getline(dataFile, suppLine);
        current -> personDOB = suppLine; 
    
        getline(dataFile, suppLine);
        current -> personHeight = stof(suppLine);

        getline(dataFile, suppLine);
        current -> personWeight = stof(suppLine);
    
        getline(dataFile, suppLine);
        current -> fatherSSN = stol(suppLine);

        getline(dataFile, suppLine);
        current -> motherSSN = stol(suppLine);
    }
    
    dataFile.close();
    
    current = *head;
  
    cout << "Bulk addition operation successful!" << endl;
    
    cout << "Updating database..." << endl;
    
    return *head;
}

Person* cardiovascularDetermining(Person* head) {
   Person* current = head;
   int person1;
   int BMI;
   
   
  while (current->next != NULL)
   {
   
   if(BMI >= 27)
        {
            cout << current->personName << ": BMI: " << get_BMI(head) << " is at risk for cardiovascular disease." << '\n';
            current = current->next;
        }
   }
}

float get_BMI(Person* head) 
{
    int person1;
    int BMI;
    Person* current = head;
    
    while(current->next != NULL)
    {
     cout << current->personName << " has "
    	  << ((current->personWeight) * 0.45) / (((current->personHeight) * 0.0254) * ((current->personHeight) * 0.0254))
	      << " as their BMI." << endl;
	  
	  current = current->next;
    }
}

void sort_BMI(Person* head)
{
    Person* index = NULL;
    Person* current = head;
    Person* tmp = current;
    get_BMI(head);

    while (current->next = NULL)
    {

         // Node index will point to node next to current
        index = current->next;

        while (index != NULL)
        {
            // if current nod's data is greater then index's node data
            if (current->data < index->data)
            {
                tmp = index->data;
                current->data = tmp;
            }
            index = index->next;
        }

        current = current->next;
    }

    return;
}

// Option 8
// Parameters: Pointer to head of person struct
// Returns: Pointer to head of person struct
Person* option_eight(Person* head) {
    
    cout << "Fnct 8" << endl;
    
    return head;
}

// Option 9
// Parameters: Pointer to head of person struct
// Returns: Pointer to head of person struct
Person* option_nine(Person* head) {
    
    cout << "Fnct 9" << endl;
    
    return head;
}

// Option 10
// Parameters: Pointer to head of person struct
// Returns: Pointer to head of person struct
Person* option_ten(Person* head) {
    
    cout << "Fnct 10" << endl;
    
    return head;
}

// Option 11
// Parameters: Pointer to head of person struct
// Returns: Pointer to head of person struct
Person* option_eleven(Person* head) {
    
    cout << "Fnct 11" << endl;
    
    return head;
}

// Option 12
// Parameters: Pointer to head of person struct
// Returns: Pointer to head of person struct
Person* option_twelve(Person* head) {
    
    cout << "Fnct 12" << endl;
    
    return head;
}

// Goodbye
// Parameters: None
// Returns: Void
void show_goodbyeMsg() {                                                              
	cout << endl << "Thank you for using the Person Struct Linked List " 
	     << "Manager!" << endl;
}
