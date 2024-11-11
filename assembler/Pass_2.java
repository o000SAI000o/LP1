import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.util.ArrayList;

class TableRow {
    String symbol;
    int address;
    int index;

    public TableRow(String symbol, int address) {
        this.symbol = symbol;
        this.address = address;
    }

    public TableRow(String symbol, int address, int index) {
        this.symbol = symbol;
        this.address = address;
        this.index = index;
    }

    public int getIndex() {
        return index;
    }

    public void setIndex(int index) {
        this.index = index;
    }

    public String getSymbol() {
        return symbol;
    }

    public void setSymbol(String symbol) {
        this.symbol = symbol;
    }

    public int getAddress() {
        return address;
    }

    public void setAddress(int address) {
        this.address = address;
    }
}

public class Pass_2 {
    ArrayList<TableRow> SYMTAB, LITTAB;

    public Pass_2() {
        SYMTAB = new ArrayList<>();
        LITTAB = new ArrayList<>();
    }

    public static void main(String[] args) {
        Pass_2 pass2 = new Pass_2();

        try {
            pass2.generateCode("C:\\Users\\Vishwajeet\\OneDrive\\Desktop\\IC.txt");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    // Read SYMTAB and LITTAB from files
    public void readtables() {
        BufferedReader br;
        String line;
        try {
            // Reading the SYMTAB from desktop
            br = new BufferedReader(new FileReader("C:\\Users\\Vishwajeet\\OneDrive\\Desktop\\SYMTAB.txt"));
            while ((line = br.readLine()) != null) {
                String[] parts = line.split("\\s+");
                SYMTAB.add(new TableRow(parts[1], Integer.parseInt(parts[2]), Integer.parseInt(parts[0])));
            }
            br.close();

            // Reading the LITTAB from desktop
            br = new BufferedReader(new FileReader("C:\\Users\\Vishwajeet\\OneDrive\\Desktop\\LITTAB.txt"));
            while ((line = br.readLine()) != null) {
                String[] parts = line.split("\\s+");
                LITTAB.add(new TableRow(parts[1], Integer.parseInt(parts[2]), Integer.parseInt(parts[0])));
            }
            br.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public void generateCode(String filename) throws Exception {
        readtables(); // Read SYMTAB and LITTAB

        BufferedReader br = new BufferedReader(new FileReader(filename));
        BufferedWriter bw = new BufferedWriter(new FileWriter("C:\\Users\\Vishwajeet\\OneDrive\\Desktop\\PASS2.txt"));

        String line, code;
        while ((line = br.readLine()) != null) {
            String[] parts = line.split("\\s+");

            if (parts[0].contains("AD") || parts[0].contains("DL,02")) {
                // Skip AD or DL instructions
                bw.write("\n");
                continue;
            } else if (parts.length == 2) {
                if (parts[0].contains("DL")) {
                    parts[0] = parts[0].replaceAll("[^0-9]", "");
                    if (Integer.parseInt(parts[0]) == 1) {
                        // Process literal constants
                        int constant = Integer.parseInt(parts[1].replaceAll("[^0-9]", ""));
                        code = "00\t0\t" + String.format("%03d", constant) + "\n";
                        bw.write(code);
                    }
                } else if (parts[0].contains("IS")) {
                    // Process instructions (IS)
                    int opcode = Integer.parseInt(parts[0].replaceAll("[^0-9]", ""));
                    if (opcode == 10) {
                        if (parts[1].contains("S")) {
                            int symIndex = Integer.parseInt(parts[1].replaceAll("[^0-9]", ""));
                            code = String.format("%02d", opcode) + "\t0\t"
                                    + String.format("%03d", SYMTAB.get(symIndex - 1).getAddress()) + "\n";
                            bw.write(code);
                        } else if (parts[1].contains("L")) {
                            int symIndex = Integer.parseInt(parts[1].replaceAll("[^0-9]", ""));
                            code = String.format("%02d", opcode) + "\t0\t"
                                    + String.format("%03d", LITTAB.get(symIndex - 1).getAddress()) + "\n";
                            bw.write(code);
                        }
                    }
                }
            } else if (parts.length == 1 && parts[0].contains("IS")) {
                // Process instructions with only opcode
                int opcode = Integer.parseInt(parts[0].replaceAll("[^0-9]", ""));
                code = String.format("%02d", opcode) + "\t0\t" + String.format("%03d", 0) + "\n";
                bw.write(code);
            } else if (parts[0].contains("IS") && parts.length == 3) {
                // Process other IS instructions with operands
                int opcode = Integer.parseInt(parts[0].replaceAll("[^0-9]", ""));
                int regcode = Integer.parseInt(parts[1]);

                if (parts[2].contains("S")) {
                    int symIndex = Integer.parseInt(parts[2].replaceAll("[^0-9]", ""));
                    code = String.format("%02d", opcode) + "\t" + regcode + "\t"
                            + String.format("%03d", SYMTAB.get(symIndex - 1).getAddress()) + "\n";
                    bw.write(code);
                } else if (parts[2].contains("L")) {
                    int symIndex = Integer.parseInt(parts[2].replaceAll("[^0-9]", ""));
                    code = String.format("%02d", opcode) + "\t" + regcode + "\t"
                            + String.format("%03d", LITTAB.get(symIndex - 1).getAddress()) + "\n";
                    bw.write(code);
                }
            }
        }

        bw.close();
        br.close();
    }
}
/*
Your code for `Pass_2` appears to be well-structured for reading the symbol table (`SYMTAB`) and literal table (`LITTAB`) from files, processing the intermediate code, and generating output to a file (`PASS2.txt`). Here’s a breakdown of what the code does and some suggestions for potential improvements:

### What the Code Does:
1. **Class `TableRow`**: Represents a table row with three fields: `symbol`, `address`, and `index`. It also provides getter and setter methods for each field.
   
2. **Class `Pass_2`**:
   - **Attributes**: Two `ArrayLists` to hold the symbol table (`SYMTAB`) and literal table (`LITTAB`).
   - **Method `readtables()`**: Reads `SYMTAB.txt` and `LITTAB.txt` from the desktop and stores them in `SYMTAB` and `LITTAB`, respectively. It reads each line and splits it by spaces to populate the `TableRow` objects.
   - **Method `generateCode()`**: Processes the intermediate code file (`IC.txt`), writes the processed code to `PASS2.txt`, and handles the various instructions (AD, DL, IS) in different ways.
     - It skips AD and DL instructions (`DL,02`).
     - Processes IS instructions (machine code) and writes them in the desired format.
   
3. **Main Method**: Initializes the `Pass_2` object and calls the `generateCode` method to start the processing.

### Potential Improvements and Points to Check:
- **Exception Handling**: 
    - Currently, your code catches exceptions generically and prints the error message. You might want to add more specific error handling (e.g., handling missing files or parsing errors more gracefully).
    
- **File Paths**:
    - You have hardcoded file paths in your code, which can create portability issues. Consider passing the file paths as arguments or using relative paths instead of absolute paths. For example, you can use `Paths.get("Desktop", "SYMTAB.txt")` for more flexibility.
    
- **Input File Format**:
    - Your code assumes a specific format of the input files. If the file structure is different, it could lead to parsing errors. Ensure that `SYMTAB.txt` and `LITTAB.txt` follow the expected format strictly (i.e., space-separated values with correct indices).

- **Data Integrity**:
    - If the index values in the input files are inconsistent or incorrect (e.g., referring to non-existing symbols or literals), the code might crash when accessing `SYMTAB` or `LITTAB`. You should handle potential `IndexOutOfBoundsException` or check for valid indices before accessing them.
    
### Example File Format Expectations:
1. **SYMTAB.txt**:
    ```
    1 SYMBOL1 1000
    2 SYMBOL2 2000
    ```

2. **LITTAB.txt**:
    ```
    1 LITERAL1 3000
    2 LITERAL2 4000
    ```

3. **IC.txt (Intermediate Code)**:
    ```
    IS10 S1
    IS20 L1
    DL,01 1000
    IS30 S2
    ```

### Suggestions for Modifications:
- **Command-Line Arguments for File Paths**: If you want to avoid hardcoded paths, allow file paths to be passed as command-line arguments.
  ```java
  public static void main(String[] args) {
      if (args.length != 3) {
          System.out.println("Please provide file paths for IC.txt, SYMTAB.txt, and LITTAB.txt");
          return;
      }
      String icFile = args[0];
      String symtabFile = args[1];
      String littabFile = args[2];
      Pass_2 pass2 = new Pass_2();
      pass2.generateCode(icFile, symtabFile, littabFile);
  }
  ```

- **Improving Code Readability**: You could make the `generateCode()` method more readable by breaking down the logic into smaller helper methods. For example, separate the handling of different instruction types (AD, DL, IS) into separate methods.

---

Let me know if you'd like help with any further modifications or improvements!
*/
