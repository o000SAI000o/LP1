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
