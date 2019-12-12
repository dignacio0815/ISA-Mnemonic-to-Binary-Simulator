// assembler.cpp
#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

string dec_to_binary(int dec);
string reg_to_bin(string reg);
int size = 0;

int main()
{   
    ifstream fin("sum.coria");      // the file the assembler will interpret
    ofstream fout("sum.bin");       // the file generated with 0s and 1s
    if(fin.fail())                  // always make sure the file was opened properly
    {
        cout << "File open failed\n";
        exit(0);
    }
    string opcode;                  // store the instruction in opcode
    int num;                        // if i need to store a number from the instruction
    string regis;                   // if i am reading a register. Note I have 8 registered
                                    // which i call: R1, R2, R3, R4, R5, R6, R7, and R8.
    while(fin >> opcode)            //  the first line of every instruction is instruction
    {
        if(opcode == "PUT")                 // process the PUT instruction
        {
            fout << "0011";                 // PUT is 0011 as described in my ISA
            fin >> num;                     // read in the decimal number
            fout << dec_to_binary(num);     // convert decimal to binary and place in file
            fin >> regis;                   // read in the register (i.e. R1, R2, R3, etc)
            fout << reg_to_bin(regis);      // this function will convert to appropriate address
            fout << endl;                   // line break
        }
        else if(opcode == "SUM")            // process the SUM instruction
        {
            fout << "0101";                 // SUM is 0101 as described in my ISA
            for(int i = 0; i < 3; i++)      // for loop that loops 3 times
            {   
                fin >> regis;               // read in the register
                fout << reg_to_bin(regis);  // this function will conver to appropriate address
            }
            fout << endl;                   // line break
        }
        else if(opcode == "OUT")            // process the OUT instruction
        {
            fout << "1111";                 // OUT is 111 as described in my ISA
            fin >> regis;                   // read in the register
            fout << reg_to_bin(regis);      // this function will conver to appropriate address
            fout << "000000";               // this is padding, since instruction have to be fixed
            fout << endl;                   // and use up 13 bits, per my ISA.
        }                                   
        else if(opcode == "ARRAY")          //process making the array
        {
            fout << "1010";
            fin >> num;                     // read in the decimal number
            fout << dec_to_binary(num);     // convert decimal to binary and place in file (size of array is max 63)
            fin >> regis;                   // read in the register (i.e. A1 or A2)
            fout << reg_to_bin(regis);      // this function will convert to appropriate address
            fout << endl;
        }
        else if(opcode == "SIZE") { // Allows user to input size of array
            fout << "1000"; 
            fin >> num;
            size = num;
            fout << dec_to_binary(num);
            fout << endl;
        }
        else if(opcode == "QOV") {
            fout << "1100";
            for(int i = 0; i <= size; i++) {
                fin >> regis;
                fout << reg_to_bin(regis);
            }
            fout << endl;
        }
        else if(opcode == "CLEAR") { // Allows user to clear all the registers
            fout << "0000" << endl;             
        }
        else if(opcode == "DIMSUM") { // Displays the sum of an array's contents
            fout << "1110";
            fin >> regis;
            fout << reg_to_bin(regis);
            fout << endl;
        }
        else if(opcode == "FNDNR") { // Find target in array / register and prompts user whether it is in it or not
            fout << "0001";
            fin >> num;
            fout << dec_to_binary(num);
            fin >> regis;
            fout << reg_to_bin(regis);
            fout << endl;
        }
        else { // this catches invalid instructions and kills program 
            cout << "ERROR: INSTRUCTION DOESN'T EXIST\n";
            exit(1);
        }
    }
    fin.close();
    fout.close();

    return 0;
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

string reg_to_bin(string reg)
{
    if(reg == "R1")         // basically a simple if.. else
        return "000";       // that will read in a register and
    else if(reg == "R2")    // return the appropriate address.
        return "001";
    else if(reg == "R3")
        return "010";
    else if(reg == "R4")
        return "011";
    else if(reg == "R5")
        return "100";
    else if(reg == "R6")
        return "101";
    else if(reg == "R7")
        return "110";
    else if(reg == "R8")
        return "111";
    else if(reg == "A1")    // special purpose register for array 1
        return "000";
    else if(reg == "A2")    // special purpose register for array 1
        return "111";
    else
    {
        cout << "Error\n";
        exit(2);           // kill the program if invalid register
    }                      // is addressed.
}