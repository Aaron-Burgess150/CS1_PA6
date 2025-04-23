# CS1_PA6
 Hash Tables

Main part of the PA6: Soccer Tournament Inventory
Background Story
The organizers of the Monster Country Soccer Tournament are launching a brand-new fan
merchandise program.
The tournament hosts thousands of enthusiastic fans and sells a wide variety of merchandise—
everything from jerseys and scarves to vuvuzelas and collectible stickers. To keep up with demand
and manage operations efficiently, the tournament organizers want to improve their merchandise
inventory tracking system. The items are purchased in bulk from suppliers at wholesale prices
and then resold to fans at fixed per-item prices.
For example, the merchandise team may purchase 1000 Argentina scarves for $1,500, and later
sell each scarf to fans for $10.
The tournament begins with a budget of $100,000 to purchase an initial inventory. Throughout a
simulation, the organizers may:
   • Buy new merchandise from suppliers
   • Sell merchandise to fans
   • Update the sale price of an item

After each update, the system will log inventory changes. At the end of the simulation, the
organizers would like to know the following:
   • How much money do they have left
   • A performance metric of the developed program that summarizes how efficiently items
     were accessed in the inventory
Since the organizers know you've been learning about hash tables in your Data Structures class,
they want you to build this system using a hash table with separate chaining (linked lists in
buckets).

Problem Description
Write a program that reads commands representing changes and queries to the soccer tournament's
merchandise inventory and prints out results when appropriate.
Supported Commands:
1. Buy supplies from a supplier.

2. Sell a quantity of an item to a fan.

3. Update the sale price of an item.

Complexity Metrics:
Your program should also compute the total complexity of all commands, where:
   • If the desired item already exists in the appropriate linked list:
     o Complexity = k, where the item is found at the kth node (1-based index).
   • If the item is not found and a new node must be created (buying a new type of
     merchandise):
     o Complexity = length of the linked list + 1 (i.e., position where the new item is
       inserted)

Financial Tracking:
You must also compute:
   • The total cash the tournament organizer has remaining after all commands.
   • The total complexity as defined above.

Hash Table Requirement:
You must use Hash Table with Separate Chaining, where each bucket contains a linked list of
merchandise items. Hashing should be based on the item name (e.g., "Brazil Jersey").
Input (Input must be from standard console input with scanf. Do not use file i/o)
The first line of input contains a single positive integer n (n ≤ 300,000), representing the number
of commands to process for managing the tournament's merchandise inventory.
Each of the following n lines contains one command, in one of the three formats described below:

• Command 1: Buying Merchandise from supplier
   buy <item> <quantity> <totalprice>
   o <item> is a lowercase single word alphabetic string (up to 29 characters) indicating
     the name of the merchandise being purchased from the supplier.
   o <quantity> is a positive integer specifying how many units are being bought.
   o <totalprice> is a positive integer (in dollars), indicating the total wholesale cost
     of the purchase.

• Command 2: Selling Merchandise to Fans
   sell <item> <quantity>
   o <item> is a lowercase single word alphabetic string (up to 29 characters) indicating the
     name of the item being sold.
   o <quantity> is a positive integer (maximum 1000), representing the number of units
     a fan wants to buy.
Note: If there are fewer than <quantity> units available in stock, sell all available units
instead. It is guaranteed that the item exists in inventory and has a defined sale price before any
sale occurs.

• Command 3: Updating the Sale Price
   change_price <item> <new_price>
   o <item> is a lowercase single word alphabetic string (up to 29 characters) representing a
     valid item currently in the inventory.
   o <new_price> is a positive integer (in dollars), indicating the new retail price per unit
     of the item. It is guaranteed that the item already exists in inventory before this
     command is issued.

Constraints & Guarantees
   • The tournament’s cash balance will never drop below $0.
   • No quantity or cash value will exceed the limits of a standard integer variable.
   • Items are always assigned a retail price before they are ever sold.

Output (Must be standrad console output. No file i/o)
For every buy or sell command (i.e., command types 1 and 2), output a single line in the following
format:
   <item> <quantity> <totalcash>
Where:
   • <item> is the name of the merchandise item being bought or sold,
   • <quantity> is the number of units remaining in inventory for that item after the
     transaction,
   • <total_cash> is the current cash balance remaining after the transaction is
     completed.

After all commands have been processed, print the following two lines:
1. The final cash balance of the tournament:
   <total_cash>

2. The total complexity of all operations (as previously defined based on linked list access
and insert positions in the hash table):
   <total_complexity>

Hash Function to Use
Please use the following hash function:
int hashfunction(char* word, int size) {
   int len = strlen(word);
   int hvalue = 0;
   for (int i=0; i<len; i++)
      hvalue = (1151*hvalue + (word[i]-'a'))%size;
   return hvalue;
}

Hash Table Insertion Details
When adding a new item to the hash table, always insert it at the front of the linked list for
its bucket. This placement directly affects the complexity cost your program calculates.
For example, if you add a new item like braziljersey with a buy command and then immediately
issue a sell command for it, the cost of the sell operation will be 1 — since braziljersey is at the
front of its linked list.

Structs to Use
Please use the following #define and two structs in your code. You are free to add more fields to
the sturcts if you wish. But you must not change the name or values of the given items shown
below:

#define MAXSTLEN 29
#define TABLESIZE 300007

typedef struct merchandise {
   char name[MAXSTLEN + 1]; // e.g., "braziljersey"
   int quantity; // stock available
   int price; // sale price per item
} merchandise;

typedef struct inventoryNode {
   merchandise* merchPtr;
   struct inventoryNode* next;
} inventoryNode;

typedef struct inventoryTable { //Hash table
   inventoryNode** lists;
   int size; // number of buckets (table size)
} inventoryTable;

Note: You are not allowed to change the above constants, struct and property names. When you
initialize your array of inventoryNode* for your hashTable (here it is inventoryTable), please
initialize the array dynamically to be the size TABLESIZE and set each list in the table to NULL.
The size component should simply be set to TABLESIZE as well.

Additional Implementation Requirements/Run Time Requirements
1. Use a hash table as previously described, using the hash function previously mentioned.

2. The run-time for processing each of the commands should be amortized O(1) time. The final
   number printed out will indicate the relative complexity for an input case.

3. A global variable may be used (but doesn't need to be) to keep track of the total complexity and
   total cash on hand.

4. Make sure to free all the memory

5. Your code must compile and execute on the codegrade system.

Some Hints:
- Hopefully you have read the whole problem carefully. Make sure you understand the sample
input and output clearly.
- You need to understand the separate chaining hashing which is pretty straight forward. I
hope you have attended the hash table lab and gone through the hash table pdf.
- There is a code hashTableSeparateChaining.c uploaded on webcourses that implements
an example of separate chaining hashing. That will be your base code to start. This whole
code was discussed during the lecture
- Do it step by step. First read inputs for all the commands, but process only insertion
command to check whether your insertion works properly and how it behaves if you have
same item.
- Then gradually work on the next commands and test your code at each step.
- As always, test your code with more test cases.
