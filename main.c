#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//structs
typedef struct cliente CLIENTE;
struct cliente{
    char nome[256];
    char cpf[12];
    int numero_da_conta;
    float saldo;
};

//structs

//funções

void menuPrincipal(){ //primeira tela do programa
    int opcao;
    do{
        printf("1 - Cadastro de cliente\n");
        printf("2 - Ver contas\n");
        printf("3 - Deposito\n");
        printf("4 - Saque\n");
        printf("5 - Apagar registro\n");
        printf("6 - Sair\n");
        printf("escolha uma opcao: ");
        scanf("%d", &opcao);

        switch(opcao){
        case 1:
            cadastroCliente(); //cadastrar cliente
            break;
        case 2:
            verificar(); //verificado usado apenas para controlar se esta funcionando ou nao as coisas no arquivo
            break;
        case 3:
            deposito(); //depositar dinheiro
            break;
        case 4:
            saque(); //sacar dinheiro
            break;
        case 5:
            apagarRegistro();
            break;
        default:
            printf("Opcao invalida!\n");
            getch();
            system("cls");
        case 6: //fechar programa
            printf("Obrigado por sua visita!");
        }
    }while(opcao != 6);
}

void apagarRegistro(){
    FILE* dadosCliente;
    dadosCliente = fopen("dadosCliente.txt", "w+b");
    system("cls");
}

void saque(){ //sacar dinheiro
 CLIENTE cliente;
    FILE* dadosCliente;
    float saque;
    char nome[50];
    dadosCliente = fopen("dadosCliente.txt", "rb");
    if(dadosCliente == NULL){
        printf("Problemas na abertura do arquivo\n");
    }else{
        fflush(stdin);
        printf("Digite o nome a pesquisar: ");
        gets(nome);
        int cont=0;
        while(fread(&cliente, sizeof(CLIENTE), 1, dadosCliente) == 1){
            if(strcmp(nome, cliente.nome) == 0){
                printf("Nome: %s\n", cliente.nome);
                printf("CPF: %s \n", cliente.cpf);
                printf("Saldo: %.2f\n", cliente.saldo);
                printf("Gostaria de sacar quanto?\n");
                scanf("%f", &saque);
                    if(saque > cliente.saldo){
                        printf("Voce nao tem tudo isso de dinheiro");
                    }else{
                        dadosCliente = fopen("dadosCliente.txt", "r+b");
                        fseek(dadosCliente, cont*sizeof(CLIENTE), SEEK_SET);
                        cliente.saldo = cliente.saldo - saque;
                        fwrite(&cliente, sizeof(CLIENTE),1, dadosCliente);
                        printf("Seu saldo atual e: %.2f", cliente.saldo);
                        fflush(stdin);
                        fclose(dadosCliente);
                    }
            }
            cont++;
        }
    }
    fclose(dadosCliente);
    getch();
    system("cls");
}


void deposito(){ //depositar dinheiro
    CLIENTE cliente;
    FILE* dadosCliente;
    float deposito;
    char nome[50];
    dadosCliente = fopen("dadosCliente.txt", "rb");
    if(dadosCliente == NULL){
        printf("Problemas na abertura do arquivo\n");
    }else{
        fflush(stdin);
        printf("Digite o nome a pesquisar: ");
        gets(nome);
        int cont=0;
        while(fread(&cliente, sizeof(CLIENTE), 1, dadosCliente) == 1){
            if(strcmp(nome, cliente.nome) == 0){
                printf("Nome: %s\n", cliente.nome);
                printf("CPF: %s \n", cliente.cpf);
                printf("Saldo: %.2f\n", cliente.saldo);
                dadosCliente = fopen("dadosCliente.txt", "r+b");
                fseek(dadosCliente, cont*sizeof(CLIENTE), SEEK_SET);
                printf("Gostaria de depositar quanto?\n");
                scanf("%f", &deposito);
                cliente.saldo = cliente.saldo + deposito;
                fwrite(&cliente, sizeof(CLIENTE),1, dadosCliente);
                printf("Seu saldo atual e: %.2f", cliente.saldo);
                fflush(stdin);
                fclose(dadosCliente);
            }
            cont++;
        }
    }
    fclose(dadosCliente);
    getch();
    system("cls");

};

void cadastroCliente(){ //cadastro do cliente
    FILE * dadosCliente;
    CLIENTE cliente;
    fflush(stdin);
    dadosCliente = fopen("dadosCliente.txt", "ab");
    if(dadosCliente == NULL){
        printf("Problemas na abertura do arquivo\n");
    }else{
        fflush(stdin);
        printf("Digite o nome: ");
        scanf("%s", &cliente.nome);

        fflush(stdin);
        printf("Digite o cpf: ");
        scanf("%s", cliente.cpf);

        fflush(stdin);
        printf("Quanto de saldo deseja colocar?");
        scanf("%f", &cliente.saldo);

        fflush(stdin);
        cliente.numero_da_conta = rand() % 1000;
        printf("Numero da conta: %d\n", cliente.numero_da_conta);

        fwrite(&cliente, sizeof(CLIENTE),1, dadosCliente);
        fclose(dadosCliente);
        printf("Aperte qualquer tecla para continuar");
        getch();
        system("cls");
    }
}

void verificar(){ //para teste
    system("cls");
    FILE * dadosCliente;
    fflush(stdin);
    CLIENTE cliente;
    dadosCliente = fopen("dadosCliente.txt", "rb");
    if(dadosCliente == NULL){
        printf("Problemas na abertura do arquivo\n");
    }else{
        while(fread(&cliente, sizeof(CLIENTE),1, dadosCliente)== 1){
            printf("Nome: %s", cliente.nome);
            printf("\nCPF: %s", cliente.cpf);
            printf("\nSaldo: %.2f", cliente.saldo);
            printf("\nNumero da conta: %d", cliente.numero_da_conta);
            printf("\n-------------------------------------------------\n");
        }
    }
    fclose(dadosCliente);
    getch();
    system("cls");
}
//funções


int main()
{
    menuPrincipal();

    return 0;
};

