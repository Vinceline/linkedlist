#include <iostream>
using namespace std;

struct node
{
	int data;
	struct node* next;
	struct node* prev;
};
//typecasting
typedef node* nodeptr;

nodeptr getnode(int value)
{
	//allocating new memory
	nodeptr newnode = new node;
	// if memory allocation was sucessful
	if (newnode != nullptr) {
		newnode->data = value;
		//initializing both pointers
		newnode->next = nullptr;
		newnode->prev = nullptr;
	}
	return newnode;
}
nodeptr create_list(int n)
{
	// first node is initialized to null
	nodeptr head = nullptr;
	// temp pointer
	nodeptr temp = nullptr;
	cout << "Please enter elements for " << n << " nodes" << endl;

	for (int i = 0; i < n; i++) {
		int value;
		cout << "please enter data value for node " << i + 1 << ":" << endl;
		cin >> value;

		// creating n nodes with values entered
		nodeptr newnode = getnode(value);

		//checking if first node is empty
		// which means list is empty
		if (head == nullptr) {
			//assigns head and temp to newnode
			head = newnode;
			temp = newnode;
		}
		// add new node to end of list if it isn't empty
		else {
			temp->next = newnode;
			newnode->prev = temp;
			temp = newnode;
		}
	}

	return head;
}
void display(nodeptr head) {
	// starting from first node
	nodeptr current = head;

	cout << "Linked List: ";
	// loop to print data of n nodes
	while (current != nullptr) {
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl;
}
void insert_beginning(nodeptr& head, int value)
{
	// Create a new node
	nodeptr newnode = getnode(value);

	// Link the new node to the current head
	newnode->next = head;
	if (head != nullptr) {
		//newnode is inserted at beginning
		head->prev = newnode;
	}

	// head/current node to point to new inserted node
	head = newnode;
}
void delete_end(nodeptr& head)
{
	// If the list is empty, can't delete
	if (head == nullptr) {
		cout << "Sorry, the list is empty." << endl;
		return;
	}

	// Traverse to the end before nullptr
	nodeptr current = head;
	while (current->next != nullptr) {
		current = current->next;
	}
	//node before last is now nullptr instead of the prev last node
	//deletes last node
	current->prev->next = nullptr;

	delete current;
}
//delete list to free memory
void delete_list(nodeptr head) {
	//iterating through each node in list and deleting untill nullptr is reached
	while (head != nullptr) {
		nodeptr current = head;
		head = head->next;
		//if there's a node after head, head->prev becomes null to become unlinked
		if (head != nullptr) {
			head->prev = nullptr;
		}
		delete current;
	}
}
int main()
{
	int value;
	int n;
	cout << "Please enter the number of nodes: ";
	cin >> n;
	if (cin.fail() || n <= 0)
	{
		cout << "sorry your input was invalid...exiting program." << endl;
		exit(1);
	}

	nodeptr head = create_list(n);
	display(head);

	int choice;
	cout << "please enter 1 to insert in beginning of the linked list" << endl;
	cout << "please press 2 to delete end of linked list" << endl;
	cout << "please press 3 to exit this program" << endl;
	cin >> choice;

	switch (choice) {
	case 1:
		cout << "please enter data value" << endl;
		cin >> value;
		insert_beginning(head, value);
		cout << "new list with beginning insertion: " << endl;
		display(head);
		break;
	case 2:
		delete_end(head);
		cout << "new list with end deletion: " << endl;
		display(head);
		break;
	case 3:
		exit(0);
	default:
		cout << "sorry, invalid input...exiting program.";
		break;
	}
	//calling delete function
	delete_list(head);
	return 0;
}