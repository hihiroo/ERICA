
class BankAccount {
    private int balance;
    public BankAccount(int m) {
        if (m >= 0) balance = m;
        else balance = 0;
    }
    public int getBalance() { return balance; }
    public boolean withdraw(int amount) {
        if (amount < 0) return false;
        else if (amount > balance) return false;
        else { balance -= amount; return true; }
    }
}
class BankManager {
    private BankAccount[] accounts;
    public BankManager(int initial_size) {
        accounts = new BankAccount[initial_size];
    }
    public void addAccount(BankAccount account) {
        for(int i=0; i<accounts.length; i++){
            if(accounts[i] == null){
                accounts[i] = account;
                return;
            }
        }
        BankAccount[] newAccout = new BankAccount[accounts.length+1];
        newAccout[accounts.length] = account;
        accounts = newAccout;
        return;
    }
    public void takeMaintenanceFee() {
        for(int i=0; i<accounts.length; i++){
            if(accounts[i] == null) continue;
            if(accounts[i].withdraw(1000) == false){
                accounts[i] = null;
            }
        }
        return;
    }
    public int countAccounts() {
        int cnt = 0;
        for(int i=0; i<accounts.length; i++)
            if(accounts[i] != null) cnt++;
         return cnt;
    }
}
public class Q6 {
    public static void main(String[] args) {
        BankManager bm = new BankManager(10);
        BankAccount b1 = new BankAccount(100);
        BankAccount b2 = new BankAccount(1100);
        BankAccount b3 = new BankAccount(3000);
        BankAccount b4 = new BankAccount(4000);
        bm.addAccount(b1); bm.addAccount(b2);
        bm.addAccount(b3); bm.addAccount(b4);
        bm.takeMaintenanceFee();
        System.out.println(bm.countAccounts()); // 3
        bm.takeMaintenanceFee();
        System.out.println(bm.countAccounts()); // 2
    }
}
