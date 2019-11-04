#ifndef CLIENTE_H
#define CLIENTE_H

typedef struct Cliente
{
    char nome[30];
    char cpf[11];
    char telefone[11];
} TCliente;

int totalClientes = 0;
TCliente *clientes;

void imprimirCliente(TCliente cliente)
{
    printf("Nome: %s", cliente.nome);
    printf("CPF: %s", cliente.cpf);
    printf("Telefone: %s", cliente.telefone);
}

#endif
