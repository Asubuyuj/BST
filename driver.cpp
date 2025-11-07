#include <iostream>
#include <fstream>
#include <queue>
#include <iomanip>
#include <string>
#include <cmath>
#include "BST.h"

using namespace std;

// Function prototypes
void displayHeader();
void displayMenu();
void readFromFile(BST<int>& tree, const string& filename);
void demonstrateQueueConversion(BST<int>& tree);
void displayQueueContents(queue<int>& q);
void displayStatistics(BST<int>& tree);
void pauseScreen();

int main() {
    BST<int> bst;
    string filename = "numbers.txt";
    int choice;
    bool dataLoaded = false;
    
    displayHeader();
    
    do {
        displayMenu();
        cout << "Enter your choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                cout << "\n>>> LOADING DATA FROM FILE <<<\n";
                cout << "================================\n";
                readFromFile(bst, filename);
                dataLoaded = true;
                pauseScreen();
                break;
            }
            
            case 2: {
                if (!dataLoaded) {
                    cout << "\n[ERROR] Please load data first (Option 1)!\n";
                    pauseScreen();
                    break;
                }
                cout << "\n>>> DISPLAYING BST STRUCTURE <<<\n";
                bst.display();
                pauseScreen();
                break;
            }
            
            case 3: {
                if (!dataLoaded) {
                    cout << "\n[ERROR] Please load data first (Option 1)!\n";
                    pauseScreen();
                    break;
                }
                displayStatistics(bst);
                pauseScreen();
                break;
            }
            
            case 4: {
                if (!dataLoaded) {
                    cout << "\n[ERROR] Please load data first (Option 1)!\n";
                    pauseScreen();
                    break;
                }
                demonstrateQueueConversion(bst);
                pauseScreen();
                break;
            }
            
            case 5: {
                cout << "\n========================================\n";
                cout << "Thank you for using the BST Queue Converter!\n";
                cout << "Program terminated successfully.\n";
                cout << "========================================\n";
                break;
            }
            
            default: {
                cout << "\n[ERROR] Invalid choice! Please select 1-5.\n";
                pauseScreen();
                break;
            }
        }
        
    } while(choice != 5);
    
    return 0;
}

// Display program header
void displayHeader() {
    cout << "\n";
    cout << "  --------------------------------------------------------\n";
    cout << "|                                                          |\n";
    cout << "|         BINARY SEARCH TREE TO QUEUE CONVERTER            |\n";
    cout << "|         CS301 - Assignment 7: Queue Converter            |\n";
    cout << "|                                                          |\n";
    cout << "|                                                          |\n";
    cout << "  --------------------------------------------------------\n";
    cout << "\n";
}

// Display menu
void displayMenu() {
    cout << "\n";
    cout << " ----------------------------------------\n";
    cout << "|           MAIN MENU                    |\n";
    cout << "|----------------------------------------|\n";
    cout << "|  1. Load Data from File                |\n";
    cout << "|  2. Display BST Structure              |\n";
    cout << "|  3. Display BST Statistics             |\n";
    cout << "|  4. Convert BST to Queue (Inorder)     |\n";
    cout << "|  5. Exit Program                       |\n";
    cout << " ----------------------------------------\n";
    cout << "\n";
}

// Read numbers from file and insert into BST
void readFromFile(BST<int>& tree, const string& filename) {
    ifstream inFile(filename);
    
    if (!inFile) {
        cerr << "[ERROR] Could not open file: " << filename << endl;
        cerr << "Please ensure the file exists in the program directory.\n";
        return;
    }
    
    int value;
    int count = 0;
    
    cout << "Reading values from '" << filename << "'...\n\n";
    cout << "Values being inserted:\n";
    cout << "----------------------\n";
    
    while (inFile >> value) {
        tree.insert(value);
        cout << setw(4) << value << " ";
        count++;
        
        // Format output: 10 numbers per line
        if (count % 10 == 0) {
            cout << "\n";
        }
    }
    
    cout << "\n\n[SUCCESS] Loaded " << count << " values into BST!\n";
    inFile.close();
}

// Demonstrate BST to Queue conversion with inorder traversal
void demonstrateQueueConversion(BST<int>& tree) {
    cout << "\n>>> BST TO QUEUE CONVERSION <<<\n";
    cout << "================================\n\n";
    
    queue<int> q;
    
    cout << "Step 1: Performing INORDER traversal of BST...\n";
    cout << "        (Left -> Root -> Right)\n\n";
    
    tree.inorderToQueue(q);
    
    cout << "[SUCCESS] Values stored in queue in ASCENDING order!\n";
    cout << "Queue size: " << q.size() << " elements\n\n";
    
    cout << "Step 2: Dequeuing values to verify ordering...\n";
    cout << "================================================\n\n";
    
    displayQueueContents(q);
    
    cout << "\n[VERIFICATION] All values dequeued in ascending order!\n";
    cout << "The queue is now empty: " << (q.empty() ? "YES" : "NO") << "\n";
}

// Display and dequeue all elements from queue
void displayQueueContents(queue<int>& q) {
    int count = 0;
    int previous = -999999;
    bool isAscending = true;
    
    cout << "Dequeued Values (10 per line):\n";
    cout << "------------------------------\n";
    
    while (!q.empty()) {
        int value = q.front();
        q.pop();
        
        cout << setw(4) << value << " ";
        count++;
        
        // Verify ascending order
        if (value < previous) {
            isAscending = false;
        }
        previous = value;
        
        if (count % 10 == 0) {
            cout << "\n";
        }
    }
    
    cout << "\n\n";
    cout << "Total dequeued: " << count << " values\n";
    cout << "Order verified: " << (isAscending ? "ASCENDING ✓" : "ERROR ✗") << "\n";
}

// Display BST statistics
void displayStatistics(BST<int>& tree) {
    cout << "\n>>> BST STATISTICS <<<\n";
    cout << "======================\n\n";
    cout << "Total Nodes:    " << tree.size() << "\n";
    cout << "Tree Height:    " << tree.height() << "\n";
    cout << "Is Empty:       " << (tree.isEmpty() ? "YES" : "NO") << "\n";
    
    // Calculate balance factor estimate
    int optimalHeight = (int)(log2(tree.size()) + 1);
    cout << "Optimal Height: " << optimalHeight << "\n";
    cout << "Balance Factor: " << (tree.height() - optimalHeight) << "\n";
    cout << "\n(Lower balance factor indicates better tree balance)\n";
}

// Pause screen for user input
void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(1000, '\n');
    cin.get();
}