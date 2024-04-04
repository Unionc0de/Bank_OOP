#include <iostream>
#include <string>
#define random(min,max) (min + rand() % (max - min + 1))
using namespace std;
const char NUMBERS[] = { '0','1','2','3','4','5','6','7','8','9' };
const string firstNameArr[] = {"Arnold","Vadim","Berta","Fritz","Govno","Impotent","Burytka","Pedya","Bebra","Comar"};
const string lastNameArr[] = {"Borisov","Kukuhin","Drizhenko","Suprimov","Tadzhichka","Glinomes"
,"Pnev","Mitko","Cumshotov","Magdesyan"};
class Client;
class Bank;



class Client {
    friend class Bank;//Теперь в классе банк все поля клиента стали public
private:
    static int lastId;

    string firstName;
    string lastName;
    unsigned short age;//Без отрицательных значений 
    string bankAcc;
    double balance = 0;
    int id;

public:
    Client() {}
    
    Client(string fName, string lName,int age,string bankAcc) {
        this->firstName = fName;
        this->lastName = lName;
        this->age = age;
        
        int newId = generateId();
        this->id = newId;

        this->bankAcc = bankAcc;
    }

    void setFirstName(string fName) {
        this->firstName = fName;
    }

    void setLastName(string lName) {
        this->lastName = lName;
    }

    void setAge(int age) {
        this->age = age;
    }

    void showInfo() {
        cout << "First name: " << this->firstName << endl;
        cout << "Last name: " << this->lastName << endl;
        cout << "Age: " << this->age << endl;
        cout << "ID: " << this->id << endl;
        cout << "Bank account: " << this->bankAcc << endl;
        //cout << "Balance" << this->balance << endl;
        cout << "\n\n";
    }
    
    string getFirstName() {
        return this->firstName;
    }

     string getLastName() {
         return this->lastName;
     }

     string getName() {
         return this->firstName, this->lastName;
     }

     int getAge() {
         return this->age;
     }

     string getBankAccount() {
         return this->bankAcc;
     }

     double  getBalance() {
         return this->balance;
     }

     //int lastId(int id) {
     //    return this->id;
     //}
private:
     static int generateId() {
         return lastId++;
     }

};

class Bank {
private:
    Client** clients = new Client*[0];
public:
    string name;
    int size = 0;
    Bank() {

    }

    Bank(string bankName) {
        this->name = bankName;
    }

    void createClient(string fName, string lName, int age) {
        string newBankAcc = createBankAcc();
        Client* cl1 = new Client(fName, lName, age, newBankAcc);
        addClient(cl1);
    }

    void showClients() {
        for (int i = 0; i < size; i++)
        {
            cout << "Client " << i << endl;
            cout << this->clients[i] << endl;
        }
    }
private:
    bool checkBankAcc(string newBankAcc) {
        for (int i = 0; i < size; i++) {
            if (newBankAcc == this->clients[i]->getBankAccount()) {
                return false;
            }
        }
        return true;
    }

    string createBankAcc() {
        bool flag = true;
        string bankAccount = "";
        
        while (flag){
            for (int i = 0; i < 8; i++)
            {
                bankAccount += NUMBERS[random(0, 9)];
            }
            if (checkBankAcc(bankAccount)) {
                flag = false;
                return bankAccount;
            }

        }
    }

    void addClient(Client* cl1) {
        Client** buf = new Client*[size + 1];
        
        for (int i = 0; i < size; i++)
        {
            buf[i] = this->clients[i];
        }

        buf[size] = cl1;

        delete[] this->clients;
        buf = this->clients;
        this->size++;
    }
};

int Client::lastId = 1;

int main()
{
    setlocale(LC_ALL, "rus");
    srand(time(NULL));
    
   /* string newBankAcc = "12345678";
    Client* cl1 = new Client(firstNameArr[random(0, 9)], lastNameArr[random(0, 9)],random(18,70), newBankAcc);
    cl1->showInfo();*/

    /*Client* cl2 = new Client(firstNameArr[random(0, 9)], lastNameArr[random(0, 9)], random(18, 70));
    cl2->showInfo();

    Client* cl3 = new Client(firstNameArr[random(0, 9)], lastNameArr[random(0, 9)], random(18, 70));
    cl3->showInfo();*/

    Bank* bank = new Bank("Union bank 554");

    bank->createClient(firstNameArr[random(0, 9)], lastNameArr[random(0, 9)], random(18, 70));
    bank->createClient(firstNameArr[random(0, 9)], lastNameArr[random(0, 9)], random(18, 70));
    bank->createClient(firstNameArr[random(0, 9)], lastNameArr[random(0, 9)], random(18, 70));

    bank->showClients();

}