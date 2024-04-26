#include <iostream>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include <limits>

using namespace std;

class InMemoryDB {
public:
    //initiates a new transaction. Throws an exception if a transaction is already active
    void begin_transaction() {
        if (transactionInProgress) {
            throw runtime_error("Transaction already in progress.");
        }
        transactionInProgress = true;
    }

    /*stores a key-value pair within the current transaction
    throws an exception if no transaction is in progress*/
    void put(string key, int value) {
        if (!transactionInProgress) {
            throw runtime_error("No transaction in progress.");
        }
        transactionStore[key] = value;
    }

    /*retrieves the value associated with a key
    returns the maximum integer value if called within an active transaction 
    to indicate that the value is not yet accessible */
    
    //otherwise, returns the value from the global store or the maximum integer value if the key doesn't exist 
    int get(string key) {
        if (transactionInProgress) {
            return numeric_limits<int>::max(); 
        } else if (globalStore.count(key)) {
            return globalStore[key];
        } else {
            return numeric_limits<int>::max(); 
        }
    }

    /*applies the changes made within the current transaction to the permanent global store
     clears the transaction store and ends the transaction.*/
     
    //throws an exception if no transaction is in progress
    void commit() {
        if (!transactionInProgress) {
            throw runtime_error("No transaction in progress.");
        }
        for (auto &it : transactionStore) {
            globalStore[it.first] = it.second;
        }
        transactionStore.clear();
        transactionInProgress = false;
    }

    /*Discards all changes made within the current transaction by clearing the transaction store
    ends the transaction. 
    Throws an exception if no transaction is in progress*/
    void rollback() {
        if (!transactionInProgress) {
            throw runtime_error("No transaction in progress.");
        }
        transactionStore.clear();
        transactionInProgress = false;
    }

private:
    unordered_map<string, int> globalStore;  //stores committed key-value pairs
    unordered_map<string, int> transactionStore; //stores changes within the current transaction
    bool transactionInProgress = false; // indicates whether a transaction is active
};

int main() {
    
    InMemoryDB inmemoryDB;
    
    // Should return max int (substituted for null), because A doesn't exist in the DB yet
    cout << inmemoryDB.get("A") << endl;
    
    try{
        //Should throw an error because a transaction is not in progress
        inmemoryDB.put("A", 5);
    }catch (exception& e){
        cout << e.what() << endl;
    }

    // starts a new transaction
    inmemoryDB.begin_transaction();
    
    
    // Set's value of A to 5, but its not committed yet
    inmemoryDB.put("A", 5);
    
   
    // Should return null, because updates to A are not committed yet
    cout << inmemoryDB.get("A") << endl;
    
    
    // Update A's value to 6 within the transaction
    inmemoryDB.put("A", 6);
    
    // Commits the open transaction
    inmemoryDB.commit();
    
    
    // Should return 6, that was the last value of A to be committed
    cout << inmemoryDB.get("A") << endl;
    
    
    try{
        // Throws an error, because there is no open transaction
        inmemoryDB.commit();
    }catch (exception& e){
        cout << e.what() << endl;
    }

    try{
        // Throws an error because there is no ongoing transaction
        inmemoryDB.rollback();
    }catch (exception& e){
        cout << e.what() << endl;
    }
    
    
    // Should return null because B does not exist in the database
    cout << inmemoryDB.get("B") << endl;
    
    
    // Starts a new transaction
    inmemoryDB.begin_transaction();
    
    
    // Set key B's value to 10 within the transaction
    inmemoryDB.put("B", 10);
    
    // Rollback the transaction - revert any changes made to B
    inmemoryDB.rollback();
    
    // Should return null because changes to B were rolled back
    cout << inmemoryDB.get("B") << endl;

    
    return 0;
}
