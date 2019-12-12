# ISA-Mnemonic-to-Binary-Simulator
Architecture/Summary:
Create a mnemonic code of MARIE instructions in a text file (sum.coria) which would be read by the assembler file (assembler.cpp) to transform the mnemonic code into binary code which is stored in a text file (sum.bin). The binary code is read by the simulator file (simulator.cpp) which will be executed to show the results in the console.



| Opcode | Key |                       Summary                        |       Example         |
|  PUT   |0011 |Input an integer into a register                      |PUT 1 R1               |
|  SUM   |0101 |Add the values into the registers and stored into the desired register  |SUM R1 R2 R3           |
|  OUT   |1111 | Outputs the value of the desired register            |OUT R3                 |
| ARRAY  |1010 |Make an array                                         |ARRAY 5 A1             |
|CLEAR   |0000 |Clear all registers                                   |CLEAR                  |
|SIZE    |1000 |Allows user to input size of an array                 |SIZE 5                 |
|QOV     |1100 |Input integers for actual registers of an array       |QOV R1 R2 R3 R4 R5 R6  |
|DIMSUM  |1110 |Displays the sum of an array                          |DIMSUM R6              |
|FNDNR   |0001 |Checks to see if a certain integer is inside an array |FNDNR 5 R6             |
|SUBT    |1011 |Subtracts two registers and stores it into a register |SUBT R5 R4 R3          |




PUT Opcode: 
When inputting values, make sure to have an integer followed by a register. For example, PUT 1 R1 would make R1 equal to the integer 1.

SUM Opcode:
Adds the integer values stored within two registers and inputs that into its own register. For example, SUM R1 R2 R3 will get the sum of R1 and R2, and then the sum will be stored in R3.

ARRAY Opcode:
It creates an array of a desired size into a register. When using the ARRAY opcode the size will be determined based on the SIZE opcode and the values that are inserted in the array will be based on what values will be inserted while using the QOV opcode.

CLEAR Opcode:
Clears all registers and associated containers that hold any integers within the simulator. For example when you want to want to get rid of all the data the CLEAR opcode will reset the binary values back to 0. 

SIZE Opcode:
Allows user to input the size of an array. Allows the user to determine how big the array will be and it will correspond with the QOV opcode that allows the user to enter the same amount of values.

QOV Opcode:
Allows the QOV or quantity of values - being an array - to be inserted with registers that are associated with some sort of integer. When inputting a size of five for the array QOV will allow the user to enter five values using the register and store them.  

DIMSUM Opcode:
Displays the sum of the array generated from using the QOV opcode. Depending on the size of QOV, DIMSUM will get all of the registers, add them all together, store the sum in a new register, and then return the value of the sum.

FNDNR Opcode:
Allows user to input an integer and search an array that was generated from using the QOV opcode. When the user wants to find a value in the array it will use this opcode and will try to traverse the array and try to see if the desired value is in the array or not. 

SUBT Opcode:
Allows users to input 3 registers. The first two registers, for example, R1 and R2 will take their associated integer values and store them into some inputted register.



  
