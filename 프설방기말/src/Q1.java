import java.io.BufferedReader;
import java.io.FileReader;

public class Q1 {
    public static void main(String[] args) {
        try {
            BufferedReader infile = new BufferedReader(new FileReader("test"));
            while (infile.ready()) {
                System.out.println(infile.readLine());
            }
            infile.close();
        }catch(Exception e){
            System.out.println("Error!!");
        }
    }
}
