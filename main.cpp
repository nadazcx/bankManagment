#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>

using namespace  std;

void createNewAccount(){

    string firstName,lastName,birthDate;

    fstream record,infile;
    record.open ("D:\\CS\\project\\bank\\datat.txt", ios::app );
    infile.open("D:\\CS\\project\\bank\\numbeOfAccounts.txt",ios::in | ios::out);
    if(!record.is_open()&& !infile.is_open()){
        cout<<"Error opening file";
        exit(0);
    }
    int num;
    string line;
    if (getline(infile, line)) {
        char firstChar = line[0];
        int number= static_cast<int>(firstChar) - 48;
        num=number;            // ...
    }
    else {
        cout<< "File is empty";
        exit(1);
    }
    cout<<"To create a new account \n";
    cout<<"Please enter you first name:";
    cin>>firstName;
    cout<<"Please enter you last name:";
    cin>>lastName;
    cout<<"Please enter your birth date following this format dd/mm/yyyy: ";
    cin>>birthDate;
    ++num;
  infile.close()   ;
  infile.open("D:\\CS\\project\\bank\\numbeOfAccounts.txt",ios::out);
    infile<<num;

    record<<num<<" "<<firstName<<" "<<lastName<<" "<<birthDate<<" "<<0<<endl;

    record.close();
    infile.close();
}

int accountExist(int i){
    ifstream  infile;
    infile.open("D:\\CS\\project\\bank\\datat.txt");
    if(!infile.is_open()){
        cout<<"Error opening file";
        exit(1);
    }
    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        string clientAccount;
        if (iss >> clientAccount ) {
            int num = stoi(clientAccount);
            if (num == i) {
                return 1;

            }
        }

    }

return 0;
}

void showRecord() {
    int accNum;
    cout << "Please enter the account number to show the record: ";
    cin >> accNum;

    ifstream infile("D:\\CS\\project\\bank\\datat.txt");
    if (!infile.is_open()) {
        cout<< "Error opening file" << endl;
        exit(0);
    }

    string line;
    bool accountFound = false;
    while (getline(infile, line)) {
        istringstream iss(line);
        string clientAccount, firstName, lastName, birthDate, balance;
        if (iss >> clientAccount >> firstName >> lastName >> birthDate >> balance) {
            int num = stoi(clientAccount);
            if (num == accNum) {
                cout << clientAccount << " " << firstName << " " << lastName << " " << birthDate << " " << balance << endl;
                accountFound = true;
                infile.close();
                break;
            }
        }
    }
    if (!accountFound) {
        cout << "Account not found"<<endl;
        infile.close();

    }
}

void transact(){
    int accNumber,choice;
    ifstream input;
    ofstream output;
    cout<<"Enter account number : ";
    cin>>accNumber;
    if (accountExist(accNumber)) {
        input.open("D:\\CS\\project\\bank\\datat.txt");
        output.open("D:\\CS\\project\\bank\\datat_temp.txt");
        if (!output.is_open() || !input.is_open()) {
            cout << "Error opening file";
            exit(1);
        }
        int amount;
        cout << " To Deposit Money click 1" <<endl;
        cout << "To withdraw Money click 2" << endl;
        cin >> choice;
        if (choice == 1) {
            cout << " Enter the amount of money you want to deposit: ";
            cin >> amount;
        }
        else if (choice == 2) {
            cout << " Enter the amount of money you want to withdraw: ";
            cin >> amount;
        }
        else {
            cout << "Invalid choice";
            exit(1);
        }
        string line;
        bool found = false;
        while (getline(input, line)) {
            char firstChar = line[0];
            int num = static_cast<int>(firstChar) - 48;
            if (num == accNumber) {
                found = true;
                std::istringstream iss(line);
                string clientAccount, firstName, lastName, birthDate;
                int balance;
                iss >> clientAccount >> firstName >> lastName >> birthDate >> balance;
                if (choice == 1) {
                    balance += amount;
                    cout<<"Deposit done successfully";
                }
                else {
                    if (balance < amount) {
                        cout << "Insufficient funds" << endl;
                        output.close();
                        input.close();
                        remove("D:\\CS\\project\\bank\\datat_temp");

                        exit(1);
                    }
                    balance -= amount;
                }
                output << num << " " << firstName << " " << lastName << " " << birthDate << " " << balance << endl;
            }
            else {
                output << line << endl;
            }
        }
        if (!found) {
            cout << "Account not found";
            exit(1);
        }
        input.close();
        output.close();
        remove("D:\\CS\\project\\bank\\datat.txt");
        rename("D:\\CS\\project\\bank\\datat_temp", "D:\\CS\\project\\bank\\datat.txt");
    }
    else {
        cout << "Account does not exist";
    }
}

void deposit() {
    int accNum, accNumDeposit;
    ifstream input;
    ofstream output;
    cout << "Enter account number: ";
    cin >> accNum;

    if (accountExist(accNum)) {
        cout << "Enter the account number that you want to deposit to: ";
        cin >> accNumDeposit;
        if (accountExist(accNumDeposit)) {
            input.open("D:\\CS\\project\\bank\\datat.txt");
            output.open("D:\\CS\\project\\bank\\datat_temp.txt");
            if (!input.is_open() || !output.is_open()) {
                cout << "Error opening the file" << endl;
                exit(0);
            }
            int amount;
            cout << "Enter the amount you want to deposit: ";
            cin >> amount;
            cout<<endl;
            string line;
            bool found = false;
            while (getline(input, line)) {
                char firstChar = line[0];
                int num = static_cast<int>(firstChar) - 48;
                if (num == accNum) {
                    found = true;
                    std::istringstream iss(line);
                    string clientAccount, firstName, lastName, birthDate;
                    int balance;
                    iss >> clientAccount >> firstName >> lastName >> birthDate >> balance;
                    if(balance<amount){
                        cout<<"The account currently has insufficient funds to complete the transaction."<<endl;
                        input.close();
                        output.close();
                        remove("D:\\CS\\project\\bank\\datat_temp.txt");
                        ::exit(0);
                    }

                    balance -= amount;
                    output << num << " " << firstName << " " << lastName << " " << birthDate << " " << balance << endl;
                } else {
                    output << line << endl;
                }
            }
            if (!found) {
                cout << "Account not found" << endl;
            }
            input.close();
            output.close();
            remove("D:\\CS\\project\\bank\\datat.txt");
            rename("D:\\CS\\project\\bank\\datat_temp.txt", "D:\\CS\\project\\bank\\datat.txt");

            input.open("D:\\CS\\project\\bank\\datat.txt");
            output.open("D:\\CS\\project\\bank\\datat_temp.txt");
            if (!input.is_open() || !output.is_open()) {
                cout << "Error opening the file" << endl;
                exit(0);
            }
            found = false;
            while (getline(input, line)) {
                char firstChar = line[0];
                int num = static_cast<int>(firstChar) - 48;
                if (num == accNumDeposit) {
                    found = true;
                    std::istringstream iss(line);
                    string clientAccount, firstName, lastName, birthDate;
                    int balance;
                    iss >> clientAccount >> firstName >> lastName >> birthDate >> balance;
                    balance += amount;
                    output << num << " " << firstName << " " << lastName << " " << birthDate << " " << balance << endl;
                } else {
                    output << line << endl;
                }
            }
            if (!found) {
                cout << "Destination account not found" << endl;
            }
            input.close();
            output.close();
            remove("D:\\CS\\project\\bank\\datat.txt");
            rename("D:\\CS\\project\\bank\\datat_temp.txt", "D:\\CS\\project\\bank\\datat.txt");

            cout << "Deposit successful" << endl;
        } else {
            cout << "Destination account does not exist" << endl;
        }
    } else {
        cout << "Account does not exist";
    }
}

void removeAccount(){
    bool found=false;
    int accNumber;
    ifstream input;
    ofstream output;
    cout<<"Enter account number : ";
    cin>>accNumber;
    if (accountExist(accNumber)) {
        input.open("D:\\CS\\project\\bank\\datat.txt");
        output.open("D:\\CS\\project\\bank\\datat_temp.txt");
        if (!output.is_open() || !input.is_open()) {
            cout << "Error opening file";
            exit(1);
        }
        int choice;
        cout<<"Are you sure you want to delete the account 0 | 1  :";
        cin>>choice;

        if (choice == 1) {
            string line;
            while (getline(input, line)) {
                char firstChar = line[0];
                int num = static_cast<int>(firstChar) - 48;
                if (num != accNumber) {
                    output << line << endl;
                    }
            }

            input.close();
            output.close();
            remove("D:\\CS\\project\\bank\\datat.txt");
            rename("D:\\CS\\project\\bank\\datat_temp.txt", "D:\\CS\\project\\bank\\datat.txt");
            cout<<"Account removed successfully";
            ::exit(1);
        }
        else if (choice == 0){
            cout<<"Operation cancelled";
            input.close();
            output.close();
            remove("D:\\CS\\project\\bank\\datat_temp.txt");





        }
        else {
            cout << "Invalid choice";
            input.close();
            output.close();
            remove("D:\\CS\\project\\bank\\datat_temp.txt");
            ::exit(1);
            exit(1);
        }

        }
        if (!found) {
            cout << "Account not found";
            input.close();
            output.close();
            remove("D:\\CS\\project\\bank\\datat_temp.txt");

    }

}

void menu(){
    int choice;
    cout<<"*** Account Information System"<<endl;
    cout<<"Select One option Below"<<endl;
    cout<<"   1--> Add New account "<<endl;
    cout<<"   2--> Show account information's "<<endl;
    cout<<"   3--> Deposit or Withdrawal funds  "<<endl;
    cout<<"   4--> Deposit funds into another individual's account.>"<<endl;
    cout<<"   5--> Delete existing account"<<endl;
    cout<<"Enter Choice  : ";
    cin>>choice;
    switch (choice) {
        case 1:createNewAccount();break;
        case 2:showRecord();break;
        case 3:transact();break;
        case 4: deposit();break;
        case 5:removeAccount();break;
        default:cout<<"Invalid choice";break;


    }



}

int main() {
  menu();



    return 0;


}
