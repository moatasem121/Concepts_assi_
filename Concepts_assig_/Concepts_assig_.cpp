#include <iostream>    // For input/output operations (cout, cin)
#include <string>      // For using the string class to store lexemes
#include <cctype>      // For character classification functions (isalpha, isdigit, isspace)

using namespace std;   // Allows use of standard library names without std:: prefix

// Character classes: Categories for classifying input characters
const int LETTER = 0;    // Represents alphabetic characters (a-z, A-Z)
const int DIGIT = 1;     // Represents numeric digits (0-9)
const int UNKNOWN = 99;   // Represents any other character (operators, parentheses, etc.)

// Token codes: Numeric identifiers for different token types
const int INT_LIT = 10;     // Integer literal (e.g., 47)
const int IDENT = 11;       // Identifier (e.g., sum, total)
const int ASSIGN_OP = 20;   // Assignment operator (=) - not used in this version
const int ADD_OP = 21;      // Addition operator (+)
const int SUB_OP = 22;      // Subtraction operator (-)
const int MULT_OP = 23;     // Multiplication operator (*)
const int DIV_OP = 24;      // Division operator (/)
const int LEFT_PAREN = 25;  // Left parenthesis (()
const int RIGHT_PAREN = 26; // Right parenthesis ())

// Global variables: Shared across functions for tracking state
int charClass;       // Current character's class (LETTER, DIGIT, UNKNOWN, or EOF)
string lexeme;       // Current token being built (e.g., "sum", "47")
char nextChar;       // Next character read from input
int lexLen;          // Length of the current lexeme
int token;           // Not used in this version, but could store current token
int nextToken;       // The type of the next token (e.g., INT_LIT, ADD_OP)

// Function declarations: Tell the compiler these functions exist
void addChar();      // Adds nextChar to lexeme
void getChar();      // Gets the next character from input
void getNonBlank();  // Skips whitespace until a non-space character
int lex();           // Main lexical analysis function
int lookup(char ch); // Identifies tokens for operators and parentheses

// Main function: Entry point of the program
int main() {
    cout << "Enter an arithmetic expression (e.g., (sum + 47) / total): "; // Prompt user
    getChar();  // Get the first character from input
    do {
        lex();  // Process each token until end of input
    } while (nextToken != EOF && nextChar != '\n'); // Stop at newline or EOF
    return 0;  // Exit program successfully
}

// Lookup function: Identifies tokens for single-character operators and parentheses
int lookup(char ch) {
    switch (ch) {  // Check the character
    case '(':  // Left parenthesis
        addChar();         // Add '(' to lexeme
        nextToken = LEFT_PAREN;  // Set token type
        break;
    case ')':  // Right parenthesis
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':  // Addition operator
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':  // Subtraction operator
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':  // Multiplication operator
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':  // Division operator
        addChar();
        nextToken = DIV_OP;
        break;
    default:   // Any other character (treated as end of input in this case)
        addChar();
        nextToken = EOF;  // Set to EOF to indicate end
        break;
    }
    return nextToken;  // Return the identified token type
}

// AddChar function: Adds the current character to the lexeme string
void addChar() {
    if (lexLen <= 98) {  // Check if lexeme isn't too long (max 98 + null terminator)
        lexeme += nextChar;  // Append character to string
        lexLen++;            // Increment length counter
    }
    else {
        cout << "Error - lexeme is too long" << endl;  // Error if exceeds limit
    }
}

// GetChar function: Reads the next character from input and classifies it
void getChar() {
    if (cin.get(nextChar)) {  // Read a character from cin, returns true if successful
        if (isalpha(nextChar))      // Check if it's a letter
            charClass = LETTER;
        else if (isdigit(nextChar)) // Check if it's a digit
            charClass = DIGIT;
        else                        // Anything else (operators, spaces, etc.)
            charClass = UNKNOWN;
    }
    else {  // If no more characters (e.g., end of input)
        charClass = EOF;  // Set class to EOF
    }
}

// GetNonBlank function: Skips whitespace until a non-space character is found
void getNonBlank() {
    while (isspace(nextChar) && nextChar != '\n')  // Skip spaces/tabs but not newline
        getChar();  // Get next character
}

// Lex function: Main lexical analyzer that identifies tokens
int lex() {
    lexLen = 0;      // Reset lexeme length
    lexeme = "";     // Clear lexeme string
    getNonBlank();   // Skip any leading whitespace

    if (nextChar == '\n') {  // If we hit newline, end processing
        nextToken = EOF;     // Set token to EOF
        lexeme = "EOF";      // Set lexeme to "EOF"
    }
    else {  // Otherwise, process the character
        switch (charClass) {  // Based on character class
        case LETTER:  // Identifier (e.g., "sum")
            addChar();       // Add first letter
            getChar();       // Get next character
            while (charClass == LETTER || charClass == DIGIT) {  // Continue if alphanumeric
                addChar();
                getChar();
            }
            nextToken = IDENT;  // Set token type to identifier
            break;

        case DIGIT:  // Integer literal (e.g., "47")
            addChar();       // Add first digit
            getChar();       // Get next character
            while (charClass == DIGIT) {  // Continue if still digits
                addChar();
                getChar();
            }
            nextToken = INT_LIT;  // Set token type to integer literal
            break;

        case UNKNOWN:  // Operators or parentheses
            lookup(nextChar);  // Identify the specific token
            getChar();         // Get next character
            break;

        case EOF:  // End of input
            nextToken = EOF;
            lexeme = "EOF";
            break;
        }
    }

    // Print the token and lexeme
    cout << "Next token is: " << nextToken
        << ", Next lexeme is " << lexeme << endl;
    return nextToken;  // Return the token type
} 