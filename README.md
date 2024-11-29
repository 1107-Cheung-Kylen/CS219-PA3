# CS219 Programming Assignment 3
### Kylen Cheung

*Forked from previous programming assignment*

## Running the Code
1. Compile using `make` command
2. Run by executing `cs219_program` in terminal

## Result & Working Process
### Explanation
The program reads the provided text file, storing the operation as a string. Depending on the operation, the program will store (as a string) the first value as the destination for the result `(destination)`, the first operand `(operand1)`, and the second operand `(operand2)`, if necessary. In the CMP and TST functions, since they do not have a destination, the program does not store a destination and instead only stores the first `(operand1)` and second operands `(operand2)`. The program creates the 8 general purpose registers by creating an array of 8 registers with item type `uint32_t`. The operation is converted to uppercase using `toupper`, ensuring both lowercase and uppercase operations are accepted. 

The program includes different functions for functionalities used throughout. To store values in the register, a function `setRegisterArray` is used to set a value to a specific register in the array. To retrieve values stored in the register, a function `getRegisterValue` is used to return the specific value stored in a register in the array. Both functions use `switch` statements to check if the register being stored/retrieved from is the correct one. 

In the `MOV` operation, the register and value to store are retrieved, and value is copied into the correct register. In operations with a destination and two registers, the program stores the destination and retrieves the values in the registers, applying the appropriate operation, and storing the result into the destination register. In operations with a destination, register, and numerical value, the program stores the destination and numerical value, and retrieves the value in the register. The operation is applied based on the numerical value, and the result is stored in the register. In operations with no destination and two operands, the program retrieves the values stored in the registers, and applies the mathematical equivalent of the operation.

In operations which also sets flags, the flags are set through a `boolean` function to determine if there is a negative, zero, carry, or overflow (NZCV flags). Some operations do not set all flags, such as the `ANDS` operation. If the operation does not require a flag change, the previous flags are kept until an operation requesting a flag change is processed. The program reads through each line in the given file to find the result of all the operations.

### Example
In the text file, the first operation is an `MOV` function. The program reads the `MOV` function, which only has a destination `(destination)` and one operand `(operand1)`. The register array is set using the function `setRegisterArray`, which takes the destination, the value to set, and a pointer to the array of registers. The destination is converted into an integer value using the `convertRegister` function, which removes the "R" from the destination, returning only the integer. A switch statement uses the converted integer value to find which register in the array should be set. When the integer value in the switch statement matches the converted value, the switch statement sets the number in that specific register to the value passed in, completing the `MOV` function. 