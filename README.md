# InMemoryDb
An in memory database with transaction support implemented with **C++ 20** (extra credit). The `optional<int>` is not used because it is part of C++ 17 standard.

##### Table of Contents
- [Specification](#Specification)  
- [How to run the code](#How-to-run-the-code) 
- [Personal Comments](#Personal-Comments) 

# Specification

**Class information:**
- The class uses two separate data structures to isolate the effects of transactions from the committed data.
- The get() method returns a special value (numeric\_limits<int>::max()) during a transaction to indicate that the data is not yet visible.

**Data Structure:**

-  **globalStore (unordered\_map<string,  int>):** This stores the committed key-value pairs, representing the persistent state of the database.
-  **transactionStore (unordered\_map<string,  int>):** This stores the changes made within the current transaction, isolated from the globalStore.
-  **transactionInProgress (bool):** A flag indicating whether a transaction is currently active.

**Functions:**

1.  **begin\_transaction()**:
   
	a.  **Purpose:** Starts a new transaction.

	b.  **Checks:** If a transaction is already in progress, it throws a runtime\_error.

	c.  **Action:** Sets the transactionInProgress flag to true.


2.  **put(string key, int value)**:
   
	a.  **Purpose:** Adds or updates a key-value pair within the current transaction.

	b.  **Checks:** If no transaction is in progress, it throws a runtime\_error.

	c.  **Action:** Stores the key-value pair in the transactionStore.


3.  **get(string key)**:

	a.  **Purpose:** Retrieves the value associated with a key.

	b.  **Logic:**
	1. If a transaction is in progress, it returns numeric\_limits<int>::max() (effectively 		representing "null" or "not found" as the actual value is not yet committed).
	2. Otherwise, it checks the globalStore and returns the value if the key exists, or numeric\_limits<int>::max() if not found.


4.  **commit()**:
   
    a.  **Purpose:** Applies the changes made within the current transaction to the persistent globalStore.
    
    b.  **Checks:** If no transaction is in progress, it throws a runtime\_error.
    
    c.  **Actions:**
    1. Copies all key-value pairs from the transactionStore to the globalStore.
    2. Clears the transactionStore.
    3. Sets transactionInProgress to false, ending the transaction.


6.  **rollback()**:
   
    a.  **Purpose:** Discards all changes made within the current transaction.
    
    b.  **Checks:** If no transaction is in progress, it throws a runtime\_error.
    
    c.  **Action:** Clears the transactionStore and sets transactionInProgress to false.


# How to run the code

### Option 1:
- Use online compiler to run the main.cpp: https://onecompiler.com/cpp/42bf5b4bz

### Option 2:
##### **Dependencies**
- A C++ compiler (e.g., g++, clang)

##### **Build and Run Instructions**
1. **Compile:** Open a terminal in the project directory and run the following command:

   - `g++ -o InMemoryDB main.cpp`

   - This will create an executable file named InMemoryDB.

2. **Run:** Execute the compiled program by typing:

   - `./InMemoryDB`

3. The program will output the results of the example usage demonstrated in the main() function.

 # Personal Comments

The instructions for the in-memory database with transaction support assignment are clear; however, some areas can be improved. The instructions have syntax errors and need to be corrected as needed. Another point is that the grading scheme favors the working code hugely. The README file just gets 2 points. It would be best if the grading scheme was a bit more balanced and provided partial credits based on the quality of the code, the documentation, and the extent to which the assignment was done to the instructions. To make this an official assignment, I think adding more clarity or examples to edge cases or error handling scenarios in the instructions would be good. Furthermore, grading could be expanded to include functional correctness to code organization, and readability.

