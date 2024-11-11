import java.util.Scanner;
import java.util.StringTokenizer;
import java.io.*;

public class Pass1 {
    static Scanner in = new Scanner(System.in);
    static String is[] = { "STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
    static String ad[] = { "START","END","ORIGIN","EQU","LTORG"};
    static String dl[] = { "DC" , "DS" };
    static String cc[] = { "LT","LE","EQ","GT","GE","ANY"};
    static int symCounter = 0;
    static int litCounter = 0;
    static String sym[][] = new String[100][2];
    static String lit[][] = new String[100][2];

    public static void main(String args[]) throws Exception {
        int location = 0;
        int litCount = 0;

        File file = new File("input.asm");
        File file1 = new File("output.asm");
        BufferedReader reader = new BufferedReader(new FileReader(file));
        BufferedWriter writer = new BufferedWriter(new FileWriter(file1));

        String st;
        String ans;
        String buffer = "";

        while ((st = reader.readLine()) != null) {
            StringTokenizer tokenizer = new StringTokenizer(st);
            ans = "";
            boolean instructionFlag = false;

            while (tokenizer.hasMoreTokens()) {
                String token = tokenizer.nextToken();

                if (token.equals("START")) {
                    location = Integer.parseInt(tokenizer.nextToken());
                    ans = "(AD,01)(C," + location + ")";
                    break;
                } else if (searchInArray(token, is)) {
                    ans += "(IS," + getIndex(token, is) + ")";
                    instructionFlag = true;
                    location += 1;
                } else if (searchInArray(token, ad)) {
                    handleADToken(token, tokenizer, location, litCount, ans);
                } else if (searchInArray(token, dl)) {
                    if (token.equals("DC")) {
                        ans += "(DL,1)(C," + tokenizer.nextToken() + ")";
                    } else if (token.equals("DS")) {
                        ans += "(DL,2)(C," + tokenizer.nextToken() + ")";
                    }
                    location += 1;
                } else if (token.startsWith("=")) {
                    lit[litCounter][0] = token;
                    ans += "(L," + (litCounter + 1) + ")";
                    litCounter++;
                    litCount++;
                } else {
                    handleSymbol(token, instructionFlag, location, ans);
                }
            }
            ans += "\n";
            buffer += ans;
        }

        System.out.println(buffer + "\n");

        System.out.println("Symbol Table:");
        for (int i = 0; i < symCounter; i++) {
            System.out.println(sym[i][0] + "\t" + sym[i][1]);
        }

        System.out.println("Literal Table:");
        for (int i = 0; i < litCounter; i++) {
            System.out.println(lit[i][0] + "\t" + lit[i][1]);
        }

        writer.write(buffer);
        reader.close();
        writer.close();
    }

    private static void handleADToken(String token, StringTokenizer tokenizer, int location, int litCount, String result) {
        if (token.equals("LTORG") || token.equals("END")) {
            while (litCount > 0) {
                String literalValue = lit[litCounter - litCount][0];
                
                if (literalValue.length() > 2 && literalValue.startsWith("=") && literalValue.endsWith("'")) {
                    lit[litCounter - litCount][1] = String.valueOf(location++);
                    String innerValue = literalValue.substring(2, literalValue.length() - 1);
                    result += "(DL,01)(C," + innerValue + ")\n";
                } else {
                    System.err.println("Warning: Invalid literal format - " + literalValue);
                }
                litCount--;
            }
        } else if (token.equals("ORIGIN")) {
            String originExpression = tokenizer.nextToken();
            String[] parts = originExpression.split("\\+");
            int originLocation = Integer.parseInt(sym[getSymbolIndex(parts[0])][1]);
            location = originLocation + Integer.parseInt(parts[1]);
            result += "(AD,03)(S," + (getSymbolIndex(parts[0]) + 1) + ")" + parts[1];
        }
    }

    private static void handleSymbol(String token, boolean instructionFlag, int location, String result) {
        if (!searchSymbol(token) && !instructionFlag) {
            sym[symCounter][0] = token;
            sym[symCounter++][1] = Integer.toString(location);
            result += "(S," + (symCounter) + ")";
        } else if (!searchSymbol(token) && instructionFlag) {
            sym[symCounter++][0] = token;
            result += "(S," + symCounter + ")";
        } else {
            int index = getSymbolIndex(token);
            if (index != -1) {
                result += "(S," + (index + 1) + ")";
            }
        }
    }

    private static boolean searchInArray(String token, String[] array) {
        for (String element : array) {
            if (element.equals(token)) {
                return true;
            }
        }
        return false;
    }

    private static int getIndex(String token, String[] array) {
        for (int i = 0; i < array.length; i++) {
            if (array[i].equals(token)) {
                return i;
            }
        }
        return -1;
    }

    private static boolean searchSymbol(String token) {
        for (int i = 0; i < symCounter; i++) {
            if (sym[i][0].equals(token)) {
                return true;
            }
        }
        return false;
    }

    private static int getSymbolIndex(String token) {
        for (int i = 0; i < symCounter; i++) {
            if (sym[i][0].equals(token)) {
                return i;
            }
        }
        return -1;
    }
}
/*
The `Pass1` Java program is part of a two-pass assembler simulation for processing assembly language programs. The program specifically focuses on **Pass 1**, where the goal is to parse and convert the assembly code into an intermediate representation. The result includes generating the **symbol table**, **literal table**, and generating an intermediate code that contains the symbolic addresses of instructions.

### **Key Components of the Program:**

1. **Instruction Set, Addressing Modes, and Data Types:**
   - **Instructions (`is`)**: Defines a set of valid instructions like "STOP", "ADD", "SUB", etc.
   - **Addressing Directives (`ad`)**: Defines directives like "START", "END", "ORIGIN", etc.
   - **Data Directives (`dl`)**: Defines data storage instructions like "DC" (Define Constant) and "DS" (Define Storage).
   - **Condition Codes (`cc`)**: Condition codes like "LT", "LE", "EQ", etc. for conditional branching.

2. **Data Structures:**
   - **Symbol Table (`sym`)**: Stores symbols (variables, labels) and their respective memory locations.
   - **Literal Table (`lit`)**: Stores literals (constant values) and their respective memory locations.

3. **File I/O:**
   - The program reads an assembly source file (`input.asm`) and writes the intermediate code to an output file (`output.asm`).

4. **Main Function Logic:**
   - **Reading the input file**: The program reads the assembly code line by line.
   - **Tokenization**: Each line is tokenized using the `StringTokenizer` class.
   - **Handling different tokens**:
     - **Instructions**: These are identified from the instruction set (`is[]`).
     - **Addressing Directives**: Tokens like "START", "END", "ORIGIN" are processed with special handling for each.
     - **Data Definitions**: Tokens like "DC" and "DS" are handled for data constants and storage.
     - **Literals**: Literals (e.g., `=X'5'`) are recognized, added to the literal table, and assigned a memory location.
     - **Symbols**: Symbols (e.g., labels) are added to the symbol table if they aren't already present.

5. **Symbol Handling:**
   - **Symbol Insertion**: New symbols are added to the symbol table with their memory locations.
   - **Symbol Lookup**: The program checks if a symbol already exists in the symbol table.

6. **Literal Handling:**
   - **LTORG Directive**: This directive is used to process all literals encountered so far and assign them memory locations.
   - **Literal Format**: The program validates and processes literals in the format `=X'...'` and assigns them memory addresses.

### **Functions in the Program:**

1. **`handleADToken()`**: Handles the directives like "LTORG", "END", and "ORIGIN".
2. **`handleSymbol()`**: Processes symbols, checking if they are already in the symbol table, and assigns memory addresses.
3. **`searchInArray()`**: Searches for a token in a given array (for example, instruction set or addressing directives).
4. **`getIndex()`**: Returns the index of a token in an array.
5. **`searchSymbol()`**: Checks if a symbol exists in the symbol table.
6. **`getSymbolIndex()`**: Gets the index of a symbol in the symbol table.

### **Key Points in Pass 1 Logic:**

- **Location Counter**: The location counter (`location`) keeps track of the memory addresses during the assembly process. It is incremented as instructions and data are processed.
- **Symbol Table Population**: Whenever a new symbol is encountered, it is added to the symbol table along with its location.
- **Literal Table Population**: When literals (constants) are found (such as `=X'5'`), they are stored in the literal table.
- **Intermediate Code Generation**: The intermediate code is generated by replacing instructions and operands with their respective symbolic references (e.g., `(IS,01)` for `ADD`).

### **Example Input (`input.asm`):**

```
START 100
X DC 5
Y DS 1
ADD X
ORIGIN X+5
LTORG
END
```

### **Example Output (`output.asm`):**

```
(AD,01)(C,100)
(DC,1)(C,5)
(DS,2)(C,1)
(IS,03)
(S,1)
(AD,03)(S,1)5
(DL,01)(C,X'5')
(IS,01)
(S,2)
```

### **Symbol Table:**

```
X    100
Y    102
```

### **Literal Table:**

```
X'5'  103
```

### **Improvement Ideas:**
- **Error Handling**: The program should handle more cases (e.g., invalid tokens or incorrect syntax) gracefully.
- **Optimization**: Refactor repeated code, such as searching in arrays and symbol tables, into more efficient data structures like `HashMap`.
- **Support for more instructions**: Extend the `is[]`, `ad[]`, and `dl[]` arrays for more instructions and directives.

### **Conclusion:**
This program simulates **Pass 1** of an assembler, reading assembly code, identifying instructions, and generating intermediate code. It maintains symbol and literal tables, which are essential for the second pass where actual machine code is generated.
*/
