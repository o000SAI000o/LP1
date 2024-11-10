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
