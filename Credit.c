#include <stdio.h>
#include <cs50.h>

// Valida numero do cartao
int validate(long number) {
    long aux = number;
    int digit, sum = 0, flag;

    while (aux >= 100) {
        aux /= 10;
    }

    flag = aux;

    do {
        // Pega o último dígito e adiciona na soma
        digit = number % 10;
        sum = sum + digit;

        // Tira o último dígito
        number = number / 10;

        // Pega o penúltimo digito (agora último) e multiplica por 2
        digit = (number % 10) * 2;

        // Verifica se o número ficou maior que 10
        if (digit >= 10) {
            // Se sim, soma cada digito e adiciona na soma
            sum = sum + (digit % 10);
            digit = digit / 10;
            sum = sum + digit;
        } else {
            // Se não, somente acrescenta na soma
            sum = sum + digit;
        }

        number = number / 10;
    } while (number > 0);

    if (sum % 10 == 0) {
        return flag;
    } else {
        return 0;
    }
}

int main(void) {
    long number = get_long("Number: ");
    int flag;

    flag = validate(number);
  
    // Verifica qual a bandeira
    if (flag == 34 || flag == 37) {
        printf("AMEX\n");
    } else if (flag >= 51 && flag <= 55) {
        printf("MASTERCARD\n");
    } else if (flag / 10 == 4) {
        printf("VISA\n");
    } else {
        printf("Error %i\n", flag);
    }
}
