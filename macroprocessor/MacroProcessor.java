import java.io.*;
import java.util.*;

public class MacroProcessor {

    // Data structure for MNT (Macro Name Table)
    public static class MNTEntry {
        String macroName;
        int mdtIndex;

        MNTEntry(String macroName, int mdtIndex) {
            this.macroName = macroName;
            this.mdtIndex = mdtIndex;
        }
    }

    // Data structure for MDT (Macro Definition Table)
    public static class MDTEntry {
        String line;

        MDTEntry(String line) {
            this.line = line;
        }
    }

    // Pass1: Processes the input file, generates MNT, MDT, and intermediate code
    public static class Pass1 {

        private List<MNTEntry> MNT = new ArrayList<>();
        private List<MDTEntry> MDT = new ArrayList<>();
        private List<String> intermediateCode = new ArrayList<>();

        public void processFile(String inputFile) throws IOException {
            BufferedReader br = new BufferedReader(new FileReader(inputFile));
            String line;
            boolean insideMacro = false;
            String macroName = "";
            int mdtIndex = 0;

            while ((line = br.readLine()) != null) {
                line = line.trim();

                // Handle macro definition
                if (line.startsWith("MACRO")) {
                    insideMacro = true;
                    macroName = line.split("\\s+")[1];
                    MNT.add(new MNTEntry(macroName, mdtIndex));
                    continue;
                }

                // Handle end of macro definition
                if (line.startsWith("MEND")) {
                    insideMacro = false;
                    continue;
                }

                // If inside macro, add line to MDT
                if (insideMacro) {
                    MDT.add(new MDTEntry(line));
                    mdtIndex++;
                } else {
                    // If outside macros, add line to intermediate code
                    intermediateCode.add(line);
                }
            }

            br.close();

            // Write MNT, MDT and intermediate code to files
            writeMNT("MNT.txt");
            writeMDT("MDT.txt");
            writeIntermediateCode("IntermediateCode.txt");
        }

        private void writeMNT(String filename) throws IOException {
            BufferedWriter writer = new BufferedWriter(new FileWriter(filename));
            for (MNTEntry entry : MNT) {
                writer.write(entry.macroName + " " + entry.mdtIndex + "\n");
            }
            writer.close();
        }

        private void writeMDT(String filename) throws IOException {
            BufferedWriter writer = new BufferedWriter(new FileWriter(filename));
            for (MDTEntry entry : MDT) {
                writer.write(entry.line + "\n");
            }
            writer.close();
        }

        private void writeIntermediateCode(String filename) throws IOException {
            BufferedWriter writer = new BufferedWriter(new FileWriter(filename));
            for (String line : intermediateCode) {
                writer.write(line + "\n");
            }
            writer.close();
        }
    }

    // Pass2: Expands macros and generates the final code
    public static class Pass2 {

        private List<String> intermediateCode = new ArrayList<>();
        private List<MNTEntry> MNT = new ArrayList<>();
        private List<MDTEntry> MDT = new ArrayList<>();

        public void readTables() throws IOException {
            // Read MNT
            BufferedReader br = new BufferedReader(new FileReader("MNT.txt"));
            String line;
            while ((line = br.readLine()) != null) {
                String[] parts = line.split("\\s+");
                MNT.add(new MNTEntry(parts[0], Integer.parseInt(parts[1])));
            }
            br.close();

            // Read MDT
            br = new BufferedReader(new FileReader("MDT.txt"));
            while ((line = br.readLine()) != null) {
                MDT.add(new MDTEntry(line));
            }
            br.close();

            // Read Intermediate Code
            br = new BufferedReader(new FileReader("IntermediateCode.txt"));
            while ((line = br.readLine()) != null) {
                intermediateCode.add(line);
            }
            br.close();
        }

        public void expandMacros() throws IOException {
            BufferedWriter bw = new BufferedWriter(new FileWriter("Output.txt"));

            for (String line : intermediateCode) {
                String[] parts = line.split("\\s+");
                boolean isMacroCall = false;
                for (MNTEntry mntEntry : MNT) {
                    if (mntEntry.macroName.equals(parts[0])) {
                        // Replace macro call with the macro body from MDT
                        isMacroCall = true;
                        int mdtIndex = mntEntry.mdtIndex;
                        expandMacro(mdtIndex, parts, bw);
                        break;
                    }
                }
                if (!isMacroCall) {
                    bw.write(line + "\n");
                }
            }
            bw.close();
        }

        private void expandMacro(int mdtIndex, String[] parameters, BufferedWriter bw) throws IOException {
            for (int i = mdtIndex; i < MDT.size(); i++) {
                String macroLine = MDT.get(i).line;
                if (macroLine.equals("MEND")) {
                    break;
                }
                // Replace parameters with actual values (if any)
                for (int j = 0; j < parameters.length; j++) {
                    macroLine = macroLine.replaceAll("\\$" + (j + 1), parameters[j]);
                }
                bw.write(macroLine + "\n");
            }
        }
    }

    // Main function to run both passes
    public static void main(String[] args) {
        try {
            // Pass I: Generate MNT, MDT, Intermediate Code
            Pass1 pass1 = new Pass1();
            pass1.processFile("input.asm");

            // Pass II: Expand Macros and generate final code
            Pass2 pass2 = new Pass2();
            pass2.readTables();
            pass2.expandMacros();

            System.out.println("Macro expansion completed successfully!");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
/*
The `MacroProcessor` class you've provided is a two-pass macro processor that handles macro expansion. Here's an overview of what it does:

### Overview:
- **Pass 1**:
  - This phase processes the input assembly file (`input.asm`), identifies macros, stores macro names and their corresponding macro definition table (MDT) indices in the Macro Name Table (MNT), and stores the macro definition lines in the MDT.
  - It generates three output files: `MNT.txt`, `MDT.txt`, and `IntermediateCode.txt`.

- **Pass 2**:
  - This phase reads the MNT, MDT, and intermediate code from the files generated by Pass 1.
  - It identifies macro calls in the intermediate code and expands them by replacing the macro call with the corresponding macro definition from the MDT.
  - The expanded code is then written to `Output.txt`.

### Key Concepts:
1. **MNT (Macro Name Table)**: This table stores the macro name and its corresponding index in the MDT.
2. **MDT (Macro Definition Table)**: This table stores the lines of the macro definitions.
3. **Intermediate Code**: This is the original source code after macros are removed. It contains the macro calls to be expanded in Pass 2.

### Explanation of Methods:

1. **Pass 1 Methods**:
   - **`processFile(String inputFile)`**: 
     - This method processes the input file line by line.
     - When it encounters `MACRO`, it starts storing the macro definition lines in the MDT.
     - When it encounters `MEND`, it ends the macro definition.
     - It adds each line outside of a macro to the intermediate code.

   - **`writeMNT(String filename)`**, **`writeMDT(String filename)`**, **`writeIntermediateCode(String filename)`**:
     - These methods write the MNT, MDT, and intermediate code to files.

2. **Pass 2 Methods**:
   - **`readTables()`**: 
     - This method reads the MNT, MDT, and intermediate code from their respective files.
   
   - **`expandMacros()`**: 
     - This method goes through the intermediate code and expands any macro calls by replacing them with the lines from the MDT.
     - The actual parameter values (if any) are substituted in the macro body.
   
   - **`expandMacro(int mdtIndex, String[] parameters, BufferedWriter bw)`**: 
     - This method handles the replacement of parameters in a macro definition and writes the expanded code to the output file.

3. **Main Method**:
   - This method runs both passes: first, it calls Pass 1 to process the input file and generate MNT, MDT, and intermediate code files; then it calls Pass 2 to read these files and expand the macros.

### Suggestions for Improvement:

1. **Error Handling**:
   - Add more detailed error handling for cases such as file not found, invalid macro calls, or incorrect macro definitions.
   
2. **Command-line Arguments**:
   - Instead of hardcoding file names, consider using command-line arguments for input and output files to make it more flexible. This would allow you to specify input and output files dynamically when running the program.

3. **Macro Parameter Validation**:
   - Ensure that the macro parameters in the input are passed correctly, especially when handling parameter substitution. You might want to validate if the number of parameters passed in the macro call matches the number of parameters defined in the macro.

4. **Handling Nested Macros**:
   - Consider handling nested macros. If a macro calls another macro, your current logic might not process it correctly. This can be done by recursively expanding macros.

5. **Optimize String Replacements**:
   - The `expandMacro` method uses `String.replaceAll`, which might be less efficient for larger input files. Using a more optimized string replacement strategy, such as using `StringBuilder` or regex patterns tailored for this use case, might improve performance.

6. **File Paths**:
   - Instead of hardcoding paths, use relative paths or let the user specify the paths for the input/output files. This would make the code more adaptable across different environments.

### Example Usage:
1. **Input File (`input.asm`)**:
   ```
   MACRO PRINT
       PRINT $1
   MEND

   PRINT Hello, World!
   ```

2. **Output Files**:
   - **MNT.txt**:
     ```
     PRINT 0
     ```
   - **MDT.txt**:
     ```
     PRINT $1
     MEND
     ```
   - **IntermediateCode.txt**:
     ```
     PRINT Hello, World!
     ```
   - **Output.txt** (After Macro Expansion):
     ```
     Hello, World!
     ```

Let me know if you need further assistance or if you'd like me to help implement any of these suggestions!
*/
