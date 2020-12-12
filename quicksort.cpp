/*
Author: Priya Gillan
file for quicksort using vectors
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//method for quicksort
void quicksort(vector<long> &vect, int left, int right, ofstream &outFile);

//method for insertion sort
void insertionsort(vector<long> &vect, int left, int right);

//quicksort helper method
void quicksortHelper(vector<long> &vect, int left, int right, ofstream &outFile);

//method to swap values
void swap(vector<long> &vect, int a, int b);

//method to print to file
void printToFile(vector<long> vect, ofstream &outFile);

//main function
int main(int argc, char** argv){

    //intialize vector
    vector<long> v;
        
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

    long fileContents;
    //making sure the file is open
    if(!infile.is_open()){
        cout<<"File could not be open."<<endl;
    }
    //execute this code if the files was found
    else{
        //put numbers from file into vector
        while (infile >> fileContents){
            v.push_back(fileContents);
        }

        //calling quicksort method
        quicksortHelper(v, 0, v.size()-1, outfile);
    }
};

//method for quicksort
void quicksort(vector<long> &vect, int left, int right, ofstream &outFile){
    //vaiable for left partition
    int iterLeft;

    //variable for right partition
    int iterRight;

    //pivot value
    long pivot;

    //cutoff 50 do insertion sort
    if(left+50 > right){
        insertionsort(vect, left, right);
    }
    //otherwise perform quicksort
    else{

        //determining mid value
        int mid = (right+left)/2;

        //if left is less than mid switch the values
        if(vect[left]>vect[mid]){
            swap(vect, left, mid);
        }

        //if mid is greater than right then swap the values
        if(vect[mid]>vect[right]){
            swap(vect, mid, right);
        }

        //if mid is less than left swap the values
        if(vect[mid]<vect[left]){
            swap(vect, mid, left);
        }
        swap(vect, mid, right-1);

        //determining the pivot value
        pivot = vect[right-1];

        //start the left partition iteration 
        iterLeft = left;

        //start the left partition iteration 
        iterRight = right-1;

        //while true and the break the loop condition is still true
        while(true){

            //iterate through the left partition
            while(vect[++iterLeft]< pivot);

            //iterate through the right partition
            while(vect[--iterRight]> pivot);

            //if the left partition is greater than the right one break the loop
            if(iterLeft >= iterRight){
                break;
            }

            //else condition
            swap(vect, iterLeft, iterRight);
        }
        
        swap(vect, iterLeft, right-1);

        //call quicksort recursively
        quicksort(vect, left, iterLeft-1, outFile);
        quicksort(vect, iterLeft+1, right, outFile);
    } 
}        

//method for insertion sort
void insertionsort(vector<long> &vect, int left, int right){

    //iterating through the vector
    for(int iter = left +1; iter < right+1; iter++){

        //temp value at the current value
        long temp = vect[iter];

        int tempIter = iter-1;

        while(tempIter >= 0 && vect[tempIter]> temp){
            vect[tempIter+1] = vect[tempIter];
            tempIter--;
        }
        vect[tempIter + 1] = temp;
    }
}

//quicksort helper method
void quicksortHelper(vector<long> &vect, int left, int right, ofstream &outFile){
    //call quicksort method
    quicksort(vect, left, right, outFile);

    //print to file
    printToFile(vect, outFile);
}

//swap function
void swap(vector<long> &vect, int value1, int value2){
    //temp value to keep track of one number
    int temp = vect[value1];
    vect[value1] = vect[value2];
    vect[value2] = temp;
}

//prints to file
void printToFile(vector<long> vect, ofstream &outFile){

    //otherwise prints the data at each node
    for(int iter = 0; iter<vect.size(); iter++){
        outFile<<vect[iter]<<endl;
    }
    //close output file
    outFile.close();
}

