#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Temp {
    string UserName, Email, Password;
    string fileUserName, fileEmail, filePassword;
    fstream file;

public:
    void login();
    void signUp();
    void forgot();
    void menu(); //reiniciar o menu apçoess cada acao
} Obj;

int main() {
    Obj.menu();
    return 0;
}

void Temp::menu() {
    char escolha;

    do {
        cout << "\n----------------------------------";
        cout << "\n 1. Entrar na conta";
        cout << "\n 2. Registrar-se";
        cout << "\n 3. Esqueci a senha";
        cout << "\n 4. Sair";
        cout << "\n----------------------------------";
        cout << "\n Qual sera a opcao escolhida :: ";
        cin >> escolha;

        switch (escolha) {
        case '1':
            login();
            break;
        case '2':
            signUp();
            break;
        case '3':
            forgot();
            break;
        case '4':
            cout << "Saindo do sistema...\n";
            return;
        default:
            cout << "Opcao invalida! Tente novamente.\n";
        }

    } while (escolha != '4'); // menu at� o usu�rio sair
}

void Temp::signUp() {
    cout << "\n------------ REGISTRO ------------\n";
    cout << "Registre seu nome: ";
    cin.ignore();
    getline(cin, UserName);
    cout << "Registre seu Email: ";
    getline(cin, Email);
    cout << "Registre sua Senha: ";
    getline(cin, Password);

    file.open("LoginData.txt", ios::out | ios::app);
    if (!file) {
        cout << "Erro ao abrir o arquivo para escrita.\n";
        return;
    }

    file << UserName << "*" << Email << "*" << Password << "\n";
    file.close();
    cout << "Registro realizado com sucesso!\n";
}

void Temp::login() {
    string searchName, searchPassword;
    cout << "\n------------ ENTRAR ------------\n";
    cout << "Coloque o seu Login: ";
    cin.ignore();
    getline(cin, searchName);
    cout << "Coloque a sua senha: ";
    getline(cin, searchPassword);

    file.open("LoginData.txt", ios::in);
    if (!file) {
        cout << "Nao foi possivel abrir o arquivo!\n";
        return;
    }

    bool found = false;

    while (getline(file, fileUserName, '*') &&
           getline(file, fileEmail, '*') &&
           getline(file, filePassword)) {

        // Remova espacos extras para evitar falhas de compara��o
        fileUserName.erase(fileUserName.find_last_not_of(" \n\r\t") + 1);
        filePassword.erase(filePassword.find_last_not_of(" \n\r\t") + 1);

        if (fileUserName == searchName && filePassword == searchPassword) {
            cout << "Login Bem Sucedido\n";
            cout << "SEJA BEM-VINDO, " << fileUserName << "!\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Login ou senha incorretos!\n";
    }

    file.close();
}

void Temp::forgot() {
    string searchName, searchEmail;
    cout << "\n-------- RECUPERAR SENHA --------\n";
    cout << "Qual o seu nome de usuario? ";
    cin.ignore();
    getline(cin, searchName);
    cout << "Qual o seu email? ";
    getline(cin, searchEmail);

    file.open("LoginData.txt", ios::in);
    if (!file) {
        cout << "Nao foi possivel abrir o arquivo!\n";
        return;
    }

    bool found = false;

    while (getline(file, fileUserName, '*') &&
           getline(file, fileEmail, '*') &&
           getline(file, filePassword)) {


        fileUserName.erase(fileUserName.find_last_not_of(" \n\r\t") + 1);
        fileEmail.erase(fileEmail.find_last_not_of(" \n\r\t") + 1);

        if (fileUserName == searchName && fileEmail == searchEmail) {
            cout << "Conta encontrada!\n";
            cout << "Sua senha é: " << filePassword << "\n";
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Usuario ou email nao encontrados!\n";
    }

    file.close();
}
