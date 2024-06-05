#include <iostream>
#include <string>
#include <vector>
#include <sstream>

class Interpreter {
private:
    std::vector<int> addressList;

public:
    Interpreter() {
        // Inicializa a lista de endereços
        addressList.resize(300);
    }

    // Função para interpretar o código
    void interpret(const std::vector<std::string>& code) {
        // Itera sobre cada linha de código
        for (const auto& line : code) {
            // Separa a linha de código em palavras
            std::istringstream iss(line);
            std::string word;
            iss >> word;

            // Verifica se é uma instrução print
            if (word == "print") {
                int value;
                iss >> value;
                // Verifica se o endereço é válido
                if (value > 0 && value < 300) {
                    // Imprime o valor no endereço correspondente
                    std::cout << "Valor no endereço " << value << ": " << addressList[value] << std::endl;
                } else {
                    std::cout << "Endereço inválido: " << value << std::endl;
                }
            }
            // Outras instruções podem ser adicionadas aqui
            // a main(Z)
            //reconhecer outras funçoes de A a Y
        }
    }

    // Função para atribuir um valor a um endereço
    void assignValue(int address, int value) {
        if (address > 0 && address < 300) {
            addressList[address] = value;
        } else {
            std::cout << "Endereço inválido: " << address << std::endl;
        }
    }
};

int main() {
    // Cria um objeto do interpretador
    Interpreter interpreter;

    // Solicita que o usuário insira todas as linhas de código de uma vez
    std::cout << "Insira to código abaixo:\n";
    std::vector<std::string> code;
    std::string line;
    while (std::getline(std::cin, line)) {
        if (line == "~") // Condição para parar de ler
            break;
        code.push_back(line);
    }

    // Atribui valores aos endereços
    for (int i = 0; i < 10; ++i) {
        interpreter.assignValue(i, i * 10); // Exemplo: atribui 0, 10, 20, ..., 90 aos primeiros 10 endereços
    }

    // Interpreta o código inserido pelo usuário
    interpreter.interpret(code);

    return 0;
}
