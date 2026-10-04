#include <iostream>
#include <string>
using namespace std;

// Item Node in Doubly Linked List
struct ItemNode {
    string itemName;
    string itemCode;
    double price;
    int quantity;
    ItemNode* prev;
    ItemNode* next;

    ItemNode(string name, string code, double p, int qty) {
        itemName = name;
        itemCode = code;
        price = p;
        quantity = qty;
        prev = nullptr;
        next = nullptr;
    }
};

// Section Node in Doubly Linked List
struct SectionNode {
    string sectionName;
    ItemNode* itemHead;
    ItemNode* itemTail;
    SectionNode* prev;
    SectionNode* next;

    SectionNode(string name) {
        sectionName = name;
        itemHead = nullptr;
        itemTail = nullptr;
        prev = nullptr;
        next = nullptr;
    }

    ~SectionNode() {
        ItemNode* curr = itemHead;
        while (curr != nullptr) {
            ItemNode* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }
};

// Store Node in Doubly Linked List
struct StoreNode {
    string storeName;
    string city;
    SectionNode* sectionHead;
    SectionNode* sectionTail;
    StoreNode* prev;
    StoreNode* next;

    StoreNode(string name, string c) {
        storeName = name;
        city = c;
        sectionHead = nullptr;
        sectionTail = nullptr;
        prev = nullptr;
        next = nullptr;
    }

    ~StoreNode() {
        SectionNode* curr = sectionHead;
        while (curr != nullptr) {
            SectionNode* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }
};

// Main Inventory Management System class using hierarchical Doubly Linked Lists
class InventorySystem {
private:
    StoreNode* storeHead;
    StoreNode* storeTail;

    // Helper: Find store node by name
    StoreNode* findStore(string storeName) {
        StoreNode* curr = storeHead;
        while (curr != nullptr) {
            if (curr->storeName == storeName) return curr;
            curr = curr->next;
        }
        return nullptr;
    }

    // Helper: Find section node inside store
    SectionNode* findSection(StoreNode* store, string sectionName) {
        if (!store) return nullptr;
        SectionNode* curr = store->sectionHead;
        while (curr != nullptr) {
            if (curr->sectionName == sectionName) return curr;
            curr = curr->next;
        }
        return nullptr;
    }

public:
    InventorySystem() {
        storeHead = nullptr;
        storeTail = nullptr;
    }

    ~InventorySystem() {
        StoreNode* curr = storeHead;
        while (curr != nullptr) {
            StoreNode* nextNode = curr->next;
            delete curr;
            curr = nextNode;
        }
    }

    // Add a new store to the system
    void addStore(string storeName, string city) {
        StoreNode* newStore = new StoreNode(storeName, city);
        if (!storeHead) {
            storeHead = storeTail = newStore;
        } else {
            storeTail->next = newStore;
            newStore->prev = storeTail;
            storeTail = newStore;
        }
        cout << "Store \"" << storeName << "\" (" << city << ") added successfully." << endl;
    }

    // 1. Add a new section in a store (e.g. Toys, Grocery, Fruits)
    void addSection(string storeName, string sectionName) {
        StoreNode* store = findStore(storeName);
        if (!store) {
            cout << "Error: Store \"" << storeName << "\" not found!" << endl;
            return;
        }

        if (findSection(store, sectionName)) {
            cout << "Section \"" << sectionName << "\" already exists in store \"" << storeName << "\"." << endl;
            return;
        }

        SectionNode* newSection = new SectionNode(sectionName);
        if (!store->sectionHead) {
            store->sectionHead = store->sectionTail = newSection;
        } else {
            store->sectionTail->next = newSection;
            newSection->prev = store->sectionTail;
            store->sectionTail = newSection;
        }
        cout << "Section \"" << sectionName << "\" added to store \"" << storeName << "\"." << endl;
    }

    // 2. Store an item in a particular section of a particular store
    void addItem(string storeName, string sectionName, string itemName, string itemCode, double price, int qty) {
        StoreNode* store = findStore(storeName);
        if (!store) {
            cout << "Error: Store \"" << storeName << "\" not found!" << endl;
            return;
        }

        SectionNode* section = findSection(store, sectionName);
        if (!section) {
            cout << "Error: Section \"" << sectionName << "\" not found in store \"" << storeName << "\"!" << endl;
            return;
        }

        ItemNode* newItem = new ItemNode(itemName, itemCode, price, qty);
        if (!section->itemHead) {
            section->itemHead = section->itemTail = newItem;
        } else {
            section->itemTail->next = newItem;
            newItem->prev = section->itemTail;
            section->itemTail = newItem;
        }
        cout << "Item \"" << itemName << "\" stored in Section [" << sectionName << "] of Store [" << storeName << "]." << endl;
    }

    // 3. Remove an item in a particular section of a particular store
    void removeItem(string storeName, string sectionName, string itemCode) {
        StoreNode* store = findStore(storeName);
        if (!store) {
            cout << "Error: Store \"" << storeName << "\" not found!" << endl;
            return;
        }

        SectionNode* section = findSection(store, sectionName);
        if (!section) {
            cout << "Error: Section \"" << sectionName << "\" not found in store \"" << storeName << "\"!" << endl;
            return;
        }

        ItemNode* curr = section->itemHead;
        while (curr != nullptr && curr->itemCode != itemCode) {
            curr = curr->next;
        }

        if (!curr) {
            cout << "Error: Item code \"" << itemCode << "\" not found in Section [" << sectionName << "]." << endl;
            return;
        }

        if (curr == section->itemHead) {
            section->itemHead = section->itemHead->next;
            if (section->itemHead) section->itemHead->prev = nullptr;
            else section->itemTail = nullptr;
        } else if (curr == section->itemTail) {
            section->itemTail = section->itemTail->prev;
            if (section->itemTail) section->itemTail->next = nullptr;
            else section->itemHead = nullptr;
        } else {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }

        cout << "Item \"" << curr->itemName << "\" (Code: " << itemCode << ") removed from Section [" << sectionName << "]." << endl;
        delete curr;
    }

    // 4. Display the list of all items of a particular section of a store
    void displaySectionItems(string storeName, string sectionName) {
        StoreNode* store = findStore(storeName);
        if (!store) {
            cout << "Store not found." << endl;
            return;
        }
        SectionNode* section = findSection(store, sectionName);
        if (!section) {
            cout << "Section not found." << endl;
            return;
        }

        cout << "\n=== Items in Section [" << sectionName << "] of Store [" << storeName << "] ===" << endl;
        ItemNode* item = section->itemHead;
        if (!item) {
            cout << "No items in this section." << endl;
            return;
        }

        while (item != nullptr) {
            cout << "- " << item->itemName << " (Code: " << item->itemCode 
                 << ") | Price: $" << item->price << " | Qty: " << item->quantity << endl;
            item = item->next;
        }
    }

    // 5. Display the list of items for a given store (across all sections)
    void displayStoreItems(string storeName) {
        StoreNode* store = findStore(storeName);
        if (!store) {
            cout << "Store not found." << endl;
            return;
        }

        cout << "\n==================================================" << endl;
        cout << "   COMPLETE INVENTORY CATALOG FOR STORE: " << storeName << " (" << store->city << ")" << endl;
        cout << "==================================================" << endl;

        SectionNode* section = store->sectionHead;
        if (!section) {
            cout << "No sections registered in this store." << endl;
            return;
        }

        while (section != nullptr) {
            cout << "\n--- Section: " << section->sectionName << " ---" << endl;
            ItemNode* item = section->itemHead;
            if (!item) {
                cout << "  (No items in section)" << endl;
            } else {
                while (item != nullptr) {
                    cout << "  * " << item->itemName << " [Code: " << item->itemCode 
                         << "] - $" << item->price << " (Qty: " << item->quantity << ")" << endl;
                    item = item->next;
                }
            }
            section = section->next;
        }
    }
};

int main() {
    InventorySystem sys;

    // Add Store
    sys.addStore("Metro Supercenter", "New York");

    // Add Sections
    sys.addSection("Metro Supercenter", "Fruits");
    sys.addSection("Metro Supercenter", "Grocery");
    sys.addSection("Metro Supercenter", "Toys");

    // Add Items
    sys.addItem("Metro Supercenter", "Fruits", "Organic Apples", "FR-001", 3.99, 100);
    sys.addItem("Metro Supercenter", "Fruits", "Fresh Bananas", "FR-002", 1.49, 150);
    sys.addItem("Metro Supercenter", "Grocery", "Whole Milk 1L", "GR-101", 2.89, 60);
    sys.addItem("Metro Supercenter", "Grocery", "Whole Wheat Bread", "GR-102", 2.49, 40);
    sys.addItem("Metro Supercenter", "Toys", "Lego Starship", "TY-501", 49.99, 15);

    // Display section items
    sys.displaySectionItems("Metro Supercenter", "Fruits");

    // Display full store inventory
    sys.displayStoreItems("Metro Supercenter");

    // Remove an item
    cout << "\n--- Removing Item FR-002 ---" << endl;
    sys.removeItem("Metro Supercenter", "Fruits", "FR-002");

    // Display updated section
    sys.displaySectionItems("Metro Supercenter", "Fruits");

    return 0;
}
