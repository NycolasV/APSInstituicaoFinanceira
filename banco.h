#include <time.h>
#include "conta.h"

int adicionarConta(TConta conta)
{
    contas[totalContas] = conta;
    totalContas++;
    qntdContas++;
    contas = (TConta *) realloc(contas, sizeof(TConta));

    if(contas != NULL)
    {
        return 1;
    }
    return 0;
}

void listarContas()
{
    printf("Quantidade de contas: %d \n\n", qntdContas);

    int i;
    for(i = 0; i < totalContas; i++)
    {
        if(contas[i].ativa && !contas[i].contaEspecial)
        {
            imprimirConta(contas[i]);
            printf("------------------------\n");
        }
    }

    for(i = 0; i < totalContas; i++)
    {
        if(contas[i].ativa && contas[i].contaEspecial)
        {
            imprimirConta(contas[i]);
            printf("------------------------\n");
        }
    }
}

int pesquisarConta(int numero)
{
    int i;
    for(i = 0; i < totalContas; i++)
    {
        if(contas[i].ativa && contas[i].numero == numero)
        {
            imprimirConta(contas[i]);
            return 1;
        }
    }

    printf("Conta informada nao existe");
    return 0;
}

TConta getConta(int numero)
{
    int i;
    for(i = 0; i < totalContas; i++)
    {
        if(contas[i].ativa && contas[i].numero == numero)
        {
            return contas[i];
        }
    }

    printf("Conta informada nao existe");
}

int getPosicaoConta(int numero)
{
    int i;
    for(i = 0; i < totalContas; i++)
    {
        if(contas[i].ativa && contas[i].numero == numero)
        {
            return i;
        }
    }

    return -1;
}

int removerConta(int numero)
{
    int i;
    for(i = 0; i < totalContas; i++)
    {
        if(contas[i].ativa && contas[i].numero == numero)
        {
            if(contas[i].saldo != 0){
                printf("Conta nao pode ser excluida, ha saldo de %.2f", contas[i].saldo);
                return 0;
            }

            contas[i].ativa = 0;
            qntdContas--;
            return 1;
        }
    }

    printf("Conta informada nao existe");
    return 0;
}

TData dataAtualLocal()
{
    TData dataAtual;

    time_t dataTempo;
    time(&dataTempo);

    struct tm*data = localtime(&dataTempo);

    dataAtual.dia = data->tm_mday;
    dataAtual.mes = data->tm_mon + 1;
    dataAtual.ano = data->tm_year + 1900;

    return dataAtual;
}
