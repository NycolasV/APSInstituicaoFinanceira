#include <conio.h>
#include "cliente.h"

int adicionarCliente(TCliente cliente)
{
    /**
    clientes[totalClientes] = cliente;
    totalClientes++;
    clientes = (TCliente *) realloc(clientes, sizeof(TCliente));

    if(clientes != NULL)
    {
        listarClientes();
        return 1;
    }
    return 0;
    */

    clientes[totalClientes] = cliente;
    totalClientes++;
    listarClientes();
    return 1;
}

void listarClientes()
{
    printf("\nQuantidade de clientes: %d \n\n", totalClientes);

    int i;
    for(i = 0; i < totalClientes; i++)
    {
        imprimirCliente(clientes[i]);
        printf("------------------------\n");
    }
}

TCliente getCliente()
{
    int i;
    char cpf[11];

    getchar();
    do
    {
        printf("CPF DO CLIENTE: ");
        fgets(cpf,11,stdin);

        for(i = 0; i < totalClientes; i++)
        {
            if(strcmp(cpf, clientes[i].cpf) == 0)
            {
                return clientes[i];
            }
        }

        printf("\nCPF informado nao existe, tente novamente\n");
    }
    while(1);
}

int existeCPF(char cpf[11])
{
    int i;
    for(i = 0; i < totalClientes; i++)
    {
        if(strcmp(cpf, clientes[i].cpf) == 0)
        {
            printf("\nCPF ja existe, insira outro \n");
            return 1;
        }
    }

    return 0;
}
