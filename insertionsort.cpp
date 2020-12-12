/*
Author: Priya Gillan
Sorting using LinkedLists
*/

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//structure of the node defined below
struct Node;

//add node to LinkedLikst
void addNode(Node **head, long nodeData);

//method for insertion sort
void insertionSort(Node **headRef, ofstream &outFile);

//inserts the nodes back in order
void sortedInsert(Node **headRef, Node *newNode);

//prints to file
void printToFile(Node *headRef, ofstream &outFile);

//print LinkedList to command line
void print(Node *node);

//main method
int main(int argc, char** argv){

    //initializing new node
    Node *head = NULL;

    //file to be opened in the terminal
    char *filename = argv[1];

    //file for program to create to print to ints
    char *outFileName = argv[2];

    //name of the file to open to read ints
    ifstream infile;

    //open output file
    ofstream outfile;

    //opens the file
    infile.open(filename);

    //opens output file
    outfile.open(outFileName);

    //holds the values of numbers that are in the program
    long fileContents;

    //making sure the file is open
    if(!infile.is_open()){
        cout<<"File could not be open."<<endl;
    }
    //execute this code if the files was found
    else{
        while (infile >> fileContents){
            //adds nodes to list
            addNode(&head, fileContents);
        }
        //calls the insertion sort method
        insertionSort(&head, outfile);
    }
};

//definition of the node structure
struct Node{
    long data;
    Node *prev;
    Node *next; 
};

//method that adds nodes to linked list
void addNode(Node **headRef, long nodeData){

    //create new node
    Node *newNode;
    newNode = new Node;

    //data of the new node
    newNode->data = nodeData;

    //if the size is zero then new node is head and tail
    if((*headRef) == 0){
        (*headRef) = newNode;
    }

    //add the new node to the list
    else{
        (*headRef)->next = newNode;
        newNode->prev = (*headRef);
        (*headRef) = newNode;
    }
}

//method for insertion sort
void insertionSort(Node **headRef, ofstream &outFile){

    //creating temporary node
    Node *temp = NULL;

    //setting a current node to point to the head
    Node *current = (*headRef);

    //if the head isn't null
    while(current != NULL){

        //assigning value to next node
        Node *nextNode = current->prev;

        //detaching node from list
        current->prev = NULL;
        current->next = NULL;

        //sending node to sortedInsert
        sortedInsert(&temp, current);

        //current is now the next node
        current = nextNode;
    }

    //head is now the temporary node
    (*headRef) = temp;

    //print the sorted linked list
    printToFile(*headRef, outFile);
}

//function that places nodes in order
void sortedInsert(Node **headRef, Node *newNode){

    //creating a temp node
    Node *temp;

    //if there is no head make the new node head
    if(*headRef == NULL){
        *headRef = newNode;
    }

    //if head is greater than new node
    else if((*headRef)->data >= newNode->data){

        //add new node after the head
        newNode->next =*headRef;
        newNode->next->prev = newNode;
        *headRef = newNode;
    }
    else{

        //temp node eqauls head
        temp = *headRef;

        //if head->next has a value and the next value is less than head
        while(temp->next != NULL && temp->next->data <newNode->data){

            //make temp next value
            temp = temp->next;
        }

        newNode->next = temp->next;

        //add new node to list
        if(temp->next != NULL) {
            newNode->next->prev = newNode;
        }

        //making sure the references to the new node are correct
        temp->next = newNode;
        newNode->prev = temp;
    }
}

//prints to file
void printToFile(Node *headRef, ofstream &outFile){
    //temporary node pointing to head
    struct Node *temp = headRef;

    //otherwise prints the data at each node
    while (temp != NULL){
        outFile<<temp->data<<endl;
        temp = temp->next;
    }
    outFile.close();
}

//function that prints the linked list to command line (THIS WAS USED FOR TESTING)
void print(Node *head){

    //temporary node pointing to head
    struct Node *temp = head;

    //making sure the list isn't empty
    if(temp == NULL){
        cout<<"List is empty."<<endl;
        
    }

    //otherwise prints the data at each node
    else{
        while (temp != NULL){
        cout<<temp->data<<endl;
        temp = temp->next;
        }
    }
    
}
