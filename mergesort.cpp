/*
Author: Priya Gillan
file for merge sort using vectors
*/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//merge function for merge sort
void merge(vector<long> &vect, vector<long> &temp, int size, int left, int mid);

//merge sort function
void mergeSort(vector<long> &vect, int size, ofstream &outFile);

//method that prints to file
void printToFile(vector<long> vect, ofstream &outFile);

//main function
int main(int argc, char** argv){

    //initialize vector
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
        //add contents of file to vector
        while (infile >> fileContents){
            v.push_back(fileContents);
        }
        //call the merge sort function
        mergeSort(v, v.size(), outfile);
    }
};

//merge function for merge sort
void merge(vector<long> &vect, vector<long> &temp, int size, int left, int mid){
    
    //declaring variable for right
    int right = mid + mid - left;

    //variable that keeps tack of left for original vector
    int leftVect = left;

    //variable that keeps track of mid
    int midTrack = mid;

    //variable that keeps track of left for temp vector
    int leftTemp = left;

    //assigning right to size if right is greater than size
    if(right > size){
        right = size;
    }

    //while the left index is less than the right and the 
    //mid is less than the right
    while(leftVect<mid && midTrack<right){

        //add value to the temp vector is the value at mid is greater than 
        if(vect[leftVect]<vect[midTrack]){
            temp[leftTemp++] = vect[leftVect++];
        }
        //otherwise the temp vector is equal to the mid
        else{
            temp[leftTemp++] = vect[midTrack++];
        }
    }

    //while the left of the vector is less than mid
    while(leftVect<mid){
        temp[leftTemp++] = vect[leftVect++];
    }

    //while mid is less than the right
    while(midTrack<right){
        temp[leftTemp++] = vect[midTrack++];
    }

    //copy values from temp back to the original vector
    for(int iter = left; iter<right; iter++){
        vect[iter] = temp[iter];
    }
}

//merge sort function
void mergeSort(vector<long> &vect, int size, ofstream &outfile){
    
    //setting up temporaty vector
    vector<long> temp(vect.size());

    //interating through the vector changing the subsize each time
    for(int subsize = 1; subsize < size; subsize *= 2){
        for(int left = 0, mid = subsize; mid < size; left = mid + subsize, mid = left + subsize){
            //call merge function
            merge(vect, temp, size, left, mid);

        }
    }
    //clear values of temp
    temp.clear();

    //once done sorting print to file
    printToFile(vect, outfile);
}

//prints to file
void printToFile(vector<long> vect, ofstream &outFile){

    //otherwise prints the data at each node
    for(int iter = 0; iter<vect.size(); iter++){
        outFile<<vect[iter]<<endl;
    }
    //close the file
    outFile.close();
}

