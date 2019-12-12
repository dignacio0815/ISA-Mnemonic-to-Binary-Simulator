// simulator.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <map>
#include <vector>
#include <cassert>

using namespace std;

int bin_to_dec(string bin);
string dec_to_binary(int dec);


int main()
{   
    ifstream fin("sum.bin");                 // the file with binary code (0s and 1s)

    if(fin.fail())                          // make sure file opened okay
    {
        cout << "File open failed\n";
        exit(0);
    }

    string instruction;                     // hold the entire binary instruction
    string opcode;                          // hold the binary opcode (4 bits)
    size_t sizeOfArray = 0;                 // size of the array at any given time one is created
    int total = 0;                          // sum of contents of newly inserted array
    string currentRegis = "";               // location of register
    vector<string> findVal;                 // vector to keep track of contents of an array
    
    map<string, int> reg_map;               // a map from strings to ints used for registers
    map<string, vector<int> > ary_map;        // a map from strings to vector<int> used for arrays
    vector<string>  memory;                 // load instructions in vector to represent memory
    
    reg_map["000"] = 0;                     //r1                
    reg_map["001"] = 0;                     //r2
    reg_map["010"] = 0;                     //r3
    reg_map["011"] = 0;                     //r4
    reg_map["100"] = 0;                     //r5
    reg_map["101"] = 0;                     //r6
    reg_map["110"] = 0;                     //r7
    reg_map["111"] = 0;                     //r8

    while(fin >> instruction)                       // read in the entire line of instruction (13 bits)
    {         
        memory.push_back(instruction);              // place it into our memory vector
    }

    fin.close();                                    // program is loaded.

    for(unsigned i = 0; i < memory.size(); i++)    // for loop to iterate through vector of instructions
    {             
        instruction = memory.at(i);            
        opcode = instruction.substr(0,4);           // take the first 4 bits of the instruction

        if(opcode == "0011") //PUT                  // if the first 4 bits are PUT
        {
            string n = instruction.substr(4,6);     // read the 6 bits related to numerical value
            int val = bin_to_dec(n);                // convert binary to decimal

            string regis = instruction.substr(10,3);    // find the 3 bits related to the register
            reg_map[regis] = val;                       // use those 3 bits as location to store value
        }
        else if(opcode == "0101") //SUM                 // SUM instruction is followed by three registers
        {   
            string regisA = instruction.substr(4,3);    // bits 4-6 are the first register
            string regisB = instruction.substr(7,3);    // bits 7-9 are the second register
            string regisC = instruction.substr(10,3);   // bits 10-12 are the last register
            int sum_result = reg_map[regisA] + reg_map[regisB]; // add the first two registers
            reg_map[regisC] = sum_result;                       // place the result in the third register
        }
        else if(opcode == "1111") //OUT                 // print to screen
        {
            string regis = instruction.substr(4,3);     // find which register to print
            cout << reg_map[regis] << endl;             // use those 3 bits with map to find value.
        }
        else if(opcode == "1010") //MAKE THE ARRAY
        {
            string n = instruction.substr(4,6);         // read the 6 bits related to size of array
            int val = bin_to_dec(n);                    // convert binary to decimal
            string regis = instruction.substr(10,3);    // find the 3 bits related to the array
            ary_map[regis] = vector<int>(val);                         
        }
        else if(opcode == "0000") { //opcode for clear all 
            reg_map["000"] = 0;
            reg_map["001"] = 0;
            reg_map["010"] = 0;
            reg_map["011"] = 0;
            reg_map["100"] = 0;
            reg_map["101"] = 0;
            reg_map["110"] = 0;
            reg_map["111"] = 0;
            findVal.clear();
            cout << "Registers have been cleared" << endl;
        } 
        else if(opcode == "1100") { // QOV, add values of registers into 1 desired register
            int input;
            int increment = 0;
            for(size_t i = 0; i < sizeOfArray; i++) {
                cout << "Please enter a number: ";
                cin >> input; 
                total += input;
                findVal.push_back(dec_to_binary(input)); 
                reg_map[instruction.substr(4 + increment, increment + 3)] = input; // input each different value into the array
                increment+=3;
            }
            currentRegis = instruction.substr(instruction.length() - 3, instruction.length());
            reg_map[currentRegis] = total;
            findVal.push_back(currentRegis);
            total = 0;
        }
        else if(opcode == "1000") {
            fin >> opcode; 
            sizeOfArray = bin_to_dec(instruction.substr(4, instruction.length()));
        }
        else if(opcode == "1110") {
            fin >> instruction; 
            string registerVal = instruction.substr(4, instruction.length());
            cout << "Total of inputted values: " << reg_map[registerVal] << endl;
        }
        else if(opcode == "0001") {
            bool flag = false;
            fin >> instruction;
            int match = bin_to_dec(instruction.substr(4, instruction.length() - 7));
            if(findVal.back() == instruction.substr(instruction.length() - 3, instruction.length())) {
                for(size_t i = 0; i < findVal.size() - 1; i++) {
                    if(bin_to_dec(findVal[i]) == match) {
                        flag = true;
                        break;
                    }
                }
            }
            if(flag) cout << "Your target number: " << match << " is inside array" << endl;
            else cout << "Your target number has not been found" << endl;
        }
    }
    return 0;
}

int bin_to_dec(string bin) 
{
    int num = 0;
    for (int i = 0; i < bin.length(); i++) 
        if (bin[i] == '1')
            num += pow(2, bin.length() - 1 - i);
    
    return num;
}

string dec_to_binary(int dec)
{
    string bin = "";

    if(dec == 0)
        return "0000000";

    while(dec != 0)     
    {
        bin = to_string(dec % 2) + bin; 
        dec /= 2; 
    }

    while(bin.size() < 6)   // have to make sure that
        bin = "0" + bin;    // each number uses 6 bits

    return bin;
}