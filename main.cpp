#include<iostream>

#include <fstream>

using namespace std;

// Global Variables 
int Num_P, Num_R;
int * work = new int[Num_R];
bool * finish = new bool[Num_P];

// Function Prototypes
void ReadFile(int ** allocation, int ** max, int ** need, int * available, int * resource, int * total_allocation);
bool safe(int ** allocation, int ** need, int * available);



//--------- Main function ---------
int main() {
    // To get the values for number of Resources and Processes to initialize arrays for input file.
    fstream readFile;
    readFile.open("Pgm3 Input.txt");

    readFile >> Num_R;

    int skipLine[Num_R];
    for (int j = 0; j < Num_R; j++)
        readFile >> skipLine[j];

    readFile >> Num_P;

    readFile.close();

    int processes[Num_P];
    for (int i = 0; i < Num_P; i++) {
        processes[i] = i;
    }

    int ** allocation = new int * [Num_P]; //2D Dynamic Array for Allocation Matrix
    for (int i = 0; i < Num_P; ++i)
        allocation[i] = new int[Num_R];

    int ** max = new int * [Num_P]; //2D Dynamic Array for Max Matrix
    for (int i = 0; i < Num_P; ++i)
        max[i] = new int[Num_R];

    int ** need = new int * [Num_P]; //2D Dynamic Array for Need Matrix
    for (int i = 0; i < Num_P; ++i)
        need[i] = new int[Num_R];

    int * available = new int[Num_R]; //1D Dynamic Array for Available Vector

    int * resource = new int[Num_R]; //1D Dynamic Array for Resource Vector

    int * total_allocation = new int[Num_R];

    ReadFile(allocation, max, need, available, resource, total_allocation); // Function call to parse input file
    safe(allocation, need, available); // Function call to check system state


    delete[] allocation;
    delete[] max;
    delete[] need;
    delete[] available;
    delete[] resource;

    return 0;
}



void ReadFile(int ** allocation, int ** max, int ** need, int * available, int * resource, int * total_allocation) //---------pass by refrance for
{


    fstream readFile;
    readFile.open("Pgm3 Input.txt");

    readFile >> Num_R;

    for (int j = 0; j < Num_R; j++) {
        readFile >> resource[j];
    }

    readFile >> Num_P;

    for (int i = 0; i < Num_P; i++) {
        for (int j = 0; j < Num_R; j++)
            readFile >> max[i][j];
    }


    for (int i = 0; i < Num_P; i++) {
        for (int j = 0; j < Num_R; j++)
            readFile >> allocation[i][j];
    }

    for (int i = 0; i < Num_P; i++) {
        for (int j = 0; j < Num_R; j++)
            need[i][j] = max[i][j] - allocation[i][j]; //calculation of need matrix (max matrix - allocation matrix)
    }


    for (int j = 0; j < Num_R; j++)
        for (int i = 0; i < Num_P; i++) {
            total_allocation[j] += allocation[i][j]; // calculating total allocation for available array calculation
        }
    for (int j = 0; j < Num_R; j++) {
        available[j] = resource[j] - total_allocation[j]; //calculation of available matrix (resource array - total allocation array)
    }

    readFile.close();
}



bool safe(int ** allocation, int ** need, int * available) {
    bool safeFlag = true, needSmallar = true;
    for (int j = 0; j < Num_R; j++) //initializing the array work as available to prevent overwrite
        work[j] = available[j];

    for (int i = 0; i < Num_P; i++) { //check if the system safe or not
        needSmallar = true;
        if (finish[i] == false) {
            for (int j = 0; j < Num_R; j++) {
                if (need[i][j] > work[j]) {
                    needSmallar = false;
                    safeFlag = false;
                    break;
                }
            }

            if (needSmallar == true) {
                for (int j = 0; j < Num_R; j++) {
                    work[j] = work[j] + allocation[i][j];
                    finish[i] = true;
                }
            }
        }
    }

    safeFlag = true;
    for (int i = 0; i < Num_P; i++) {
        needSmallar = true;
        if (finish[i] == false) {
            for (int j = 0; j < Num_R; j++) {
                if (need[i][j] > work[j]) {
                    needSmallar = false;
                    safeFlag = false;
                    break;
                }
            }

            if (needSmallar == true) {
                for (int j = 0; j < Num_R; j++) {
                    work[j] = work[j] + allocation[i][j];
                    finish[i] = true;
                }
            }
        }
    }

    if (safeFlag == 0) {
        cout << endl << endl << "The System is in an UNSAFE STATE. " << endl << endl;
    } else {
        cout << endl << endl << "The System is in a SAFE STATE. " << endl << endl;
    }


    return safeFlag;
}
