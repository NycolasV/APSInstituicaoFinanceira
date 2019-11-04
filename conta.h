#ifndef CONTA_H
#define CONTA_H
#include "cliente.h"

typedef struct Data
{
    int dia;
    int mes;
    int ano;
} TData;

typedef struct Conta
{
    int numero;
    TCliente cliente;
    TData dataAbertura;
    float saldo;
    int contaEspecial;
    float limite;
    int ativa;
} TConta;

int numeroConta = 0;
int totalContas = 0;
int qntdContas = 0;
TConta *contas;

int possuiSaldo(float valor, float saldo);
int possuiSaldoEspecial(float valor, float saldo, float limite);

void imprimirConta(TConta conta)
{
    printf("Numero: %d \n", conta.numero);
    printf("Nome Cliente: %s", conta.cliente.nome);
    printf("CPF Cliente: %s", conta.cliente.cpf);
    printf("Data abertura: %i/%i/%i \n", conta.dataAbertura.dia, conta.dataAbertura.mes, conta.dataAbertura.ano);
    printf("Saldo: %.2f \n", conta.saldo);

    if(conta.contaEspecial)
    {
        printf("Limite: %.2f \n", conta.limite);
    }
}

float depositar(TConta conta)
{
    float valor;

    printf("Valor a ser depositado: ");
    scanf("%f", &valor);

    if(valor > 0)
    {
        conta.saldo += valor;
        printf("Novo saldo: %.2f", conta.saldo);
        return conta.saldo;
    }

    printf("Valor incorreto");
    return 0;
}

float debitar(TConta conta)
{
    float valor;

    printf("Valor a ser retirado: ");
    scanf("%f", &valor);

    if(conta.contaEspecial)
    {
        if(possuiSaldoEspecial(valor, conta.saldo, conta.limite))
        {
            conta.saldo -= valor;
            printf("Conta com limite, novo saldo: %.2f", conta.saldo);
            return conta.saldo;
        }
    }

    if(possuiSaldo(valor, conta.saldo))
    {
        conta.saldo -= valor;
        printf("Novo saldo: %.2f", conta.saldo);
        return conta.saldo;
    }

    printf("Saldo insuficiente ou Entrada incorreta");
    return 0;
}

int transferir(TConta origem, TConta destino, float *novoSaldoOrigem, float *novoSaldoDestino)
{
    float quantia;

    printf("Quantia a ser transferida: ");
    scanf("%f", &quantia);

    if(origem.contaEspecial)
    {
        if(possuiSaldoEspecial(quantia, origem.saldo, origem.limite))
        {
            origem.saldo -= quantia;
            destino.saldo += quantia;

            *novoSaldoOrigem = origem.saldo;
            *novoSaldoDestino = destino.saldo;

            printf("Conta com limite, novo saldo: %.2f", *novoSaldoOrigem);
            return 1;
        }

        return 0;
    }

    if(possuiSaldo(quantia, origem.saldo))
    {
        origem.saldo -= quantia;
        destino.saldo += quantia;

        *novoSaldoOrigem = origem.saldo;
        *novoSaldoDestino = destino.saldo;

        printf("Novo saldo: %.2f", *novoSaldoOrigem);
        return 1;
    }

    printf("Saldo insuficiente ou Entrada incorreta");
    return 0;
}

int possuiSaldo(float valor, float saldo)
{
    if(valor > 0 && (saldo -= valor) > 0)
    {
        return 1;
    }

    return 0;
}

int possuiSaldoEspecial(float valor, float saldo, float limite)
{
    limite -= (2*limite);

    if(valor > 0 && (saldo -= valor) > limite)
    {
        return 1;
    }

    return 0;
}

#endif
