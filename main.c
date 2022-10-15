#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const char* const error_msg_decimal = "Error! That set of number is not a decimal number.\n";
const char* const error_msg_binary = "Error! That set of number is not a binary number.\n";
const char* const error_msg_hex = "Error! That set of number is not a hexadecimal number.\n";
const char* const error_msg_unsupported_system = "Error! The number system is not supported.\n";

const char* const msg_prompt_number = "Please enter a set of number:\n";
const char* const msg_prompt_current_number_system = "Please enter the current number system:\n";
const char* const msg_prompt_number_system_to_convert = "Please enter the number system you want the set of number be converted to:\n";
const char* const msg_Output = "Output=";

const char *decimal = "0123456789";
const char *binary = "01";
const char *hex = "0123456789ABCDEF";

bool check_number(char number[], const char *test);
bool check_number(char number[], const char *test) {

    
    bool is_valid;
    if (number[strspn(number,test)] == '\0') {
        is_valid = true;
    }
    else
        is_valid = false;
    return is_valid;
}

int stringToInteger(char string[]);
int stringToInteger(char string[]) {
    int result = 0;
    for (int i = 0; string[i] != '\0'; ++i) {
        if (string[i] > '9' || string[i] < '0')
            return -1;
        result = result*10 +string[i] - '0';

    }
    return result; 
}

int binaryToDecimal(char number[]);
int binaryToDecimal(char number[]) {
    int binary_num = stringToInteger(number);   // 2^n bit algrothim
    int sum = 0;
    int base = 1;
    int temp = binary_num;
    while(temp) {
        int last_digit = temp % 10;
        temp = temp / 10;                     //cast away least significant bit

        sum += last_digit*base;              
        base = base*2;                           // increacing 2^n power starting from 0
    }
    return sum;
}


int hexToDecimal(char string[]);
int hexToDecimal(char string[]) {
    int sum = 0;
    int base = 1;
    for (int i = strlen(string)-1; i >=0; i--) {
        int ascii_value = (char)string[i];
        if (ascii_value >=48 && ascii_value < 65) {        //handle 0123456789
            int digit_value = ascii_value - 48;
            sum += digit_value*base;
            base = base*16;
        }
        else if (ascii_value >=65) {                      //handle ABCDEF
            int digit_value = ascii_value - 55;
            sum += digit_value*base;
            base = base*16;
        }
    }
    return sum;
}

int main(){
    printf("%s", msg_prompt_number);
    
    /**
     * @brief 
     * Get user input for number to be convert
     */

    // TODO:
    char input_number[100] = {};

    printf(">");
    scanf("%s", &input_number);

    printf("%s", msg_prompt_current_number_system);

    /**
     * @brief 
     * Get user input for current number system
     */
    int current_system;
    printf(">");

    scanf("%d", &current_system);
    //check validity of number wrt systems
    if (current_system == 10) {
        if (!check_number(input_number, decimal)) {
            printf("%s", error_msg_decimal); goto end;  //jump
            
        }
    }
    else if (current_system == 2) {
        if (!check_number(input_number, binary)) {
            printf("%s", error_msg_binary); goto end;
        }
    }
    else if (current_system == 16) {
        if (!check_number(input_number, hex)) {
            printf("%s", error_msg_hex); goto end;
        }
    }
    else {
        printf("%s", error_msg_unsupported_system); goto end;
    }

    // TODO:
    printf("%s", msg_prompt_number_system_to_convert);

    /**
     * @brief 
     * Get user input for the number system for conversion.
     * Print converted number in format of "Output=12", e.g Output=ABCDEF
     * No space should be inserted in the asnwer "Output=XXX".
     * In case of wrong number system for conversion, please use the above error msgs.
     */

    // TODO:
    int convert_to;
    printf(">");
    scanf("%d", &convert_to);
    if (current_system == 10 && convert_to == 2) {               //decimal to binary
        printf("Output=");                                     //hardcodeing

        int decimal_num = stringToInteger(input_number);
        int i = 0;
        int binary_array[32]; 
        while (decimal_num > 0) {                  //for creating the binary number 
            binary_array[i] = decimal_num % 2;
            decimal_num = decimal_num / 2;
            i++;
        }
        //print binary array in reverse
        for (int j = i -1; j >=0; j--)
            printf("%d", binary_array[j]);
    }
    else if (current_system == 10 && convert_to == 16) {
        printf("Output=");
        int decimal_num = stringToInteger(input_number);
        char hex_array[100];
        int i = 0;
        while (decimal_num != 0) {
            int temp = 0;           //used for remainder
            temp = decimal_num % 16;
            if (temp < 10) {
                int ascii_value = temp + 48;
                hex_array[i] = (char)ascii_value;  //ascii of 0 begin at 48
                i++;
            }
            else {
                int ascii_value = temp + 55;
                hex_array[i] = (char)(ascii_value);   //ascii of A begins at 65
                i++;
            }
            decimal_num = decimal_num / 16;
        }
        for (int j = i-1; j >=0; j--) {
            printf("%c", hex_array[j]);
        }
    }
    else if (current_system == 2 && convert_to == 10) {
        printf("Output:");
        int decimal_num = binaryToDecimal(input_number);
        printf("%d", decimal_num);
    }
    else if (current_system == 2 && convert_to == 16) {  //Copy and paste from above, with some edits. 
        printf("Output:");
        int decimal_num = binaryToDecimal(input_number);
        char hex_array[100];
        int i = 0;
        while (decimal_num != 0) {
            int temp = 0;           //used for remainder
            temp = decimal_num % 16;
            if (temp < 10) {
                int ascii_value = temp + 48;
                hex_array[i] = (char)ascii_value;  //ascii of 0 begin at 48
                i++;
            }
            else {
                int ascii_value = temp + 55;
                hex_array[i] = (char)(ascii_value);   //ascii of A begins at 65
                i++;
            }
            decimal_num = decimal_num / 16;
        }
        for (int j = i-1; j >=0; j--) {
            printf("%c", hex_array[j]);
        }
    }
    else if (current_system == 16 && convert_to == 10) {
        printf("Output:");
        long decimal_num = hexToDecimal(input_number);
        printf("%ld", decimal_num);
    }

    else if (current_system == 16 && convert_to == 2) {      //didn't come up with a decimal to binary coz returning array of char to complicated for me atm
        printf("Output:");                                   //so just copy and paste!
        int decimal_num = hexToDecimal(input_number);
        int i = 0;
        int binary_array[32];
        while (decimal_num > 0) {
            binary_array[i] = decimal_num % 2;
            decimal_num = decimal_num / 2;
            i++;
        }
        for (int j = i -1; j >=0; j--)
            printf("%d", binary_array[j]);
    }
    end:                                  //terminate process if invalid system
    return 0;
}