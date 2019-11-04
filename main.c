#include <stdio.h>
#include <stdlib.h>
#include "gerenciaClientes.h"
#include "banco.h"

void menu();
void opcoesMenu();
int entradaDadosCliente();
int entradaDadosConta();
int entradaNumeroConta(char menuEscolha);
int operacaoTransferencia();

int main()
{
    clientes = calloc(20, sizeof(TCliente));
    contas = calloc(1, sizeof(TConta));

    menu();
    return 0;
}

/// FUNCOES MENU
void menu()
{
    char menuEscolha;
    int result = 0;

    opcoesMenu();

    do
    {
        printf("0 - Repetir opcoes\n");
        printf("Escolha uma opcao: ");
        scanf(" %c", &menuEscolha);
        printf("\n");

        switch(menuEscolha)
        {
        case '1':
            result = entradaDadosCliente();
            break;

        case '2':
            result = entradaDadosConta();
            break;

        case '3':
            listarContas();
            break;

        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
            result = entradaNumeroConta(menuEscolha);
            break;

        case '9':
            printf("Programa encerrado...\n");
            break;

        case '0':
            opcoesMenu();
            break;

        default:
            printf("ERRO - Opcao invalida, escolha novamente...\n");
            break;
        }

        if(menuEscolha != '9' && menuEscolha != '0')
        {
            if(result)
            {
                printf("\nOperacao realizada com sucesso");
            }
            else
            {
                printf("\nFalha ao tentar realizar o processo");
            }
        }

        printf("\n======================================\n");
    }
    while(menuEscolha != '9');
}

void opcoesMenu()
{
    printf("=== MENU DO BANCO ===\n");
    printf("1 - Cadastrar Cliente\n");
    printf("2 - Cadastrar Conta\n");
    printf("3 - Listar Conta\n");
    printf("4 - Pesquisar Conta\n");
    printf("5 - Depositar\n");
    printf("6 - Debitar (Sacar)\n");
    printf("7 - Transferir\n");
    printf("8 - Remover Conta\n");
    printf("9 - Sair\n");
}

/// FUNCOES CLIENTE
int entradaDadosCliente()
{
    TCliente cliente;
    getchar();

    printf("NOME: ");
    fgets(cliente.nome,30,stdin);

    do
    {
        printf("CPF: ");
        fgets(cliente.cpf,11,stdin);
    }
    while(existeCPF(cliente.cpf));

    printf("TELEFONE: ");
    fgets(cliente.telefone,11,stdin);

    return adicionarCliente(cliente);
}

/// FUNCOES CONTA
int entradaDadosConta()
{
    if(clientes == NULL)
    {
        printf("Nenhum cliente cadastrado");
        return 0;
    }

    TConta conta;
    char contaEspecial;
    getchar();

    conta.numero = numeroConta++;
    conta.ativa = 1;
    conta.dataAbertura = dataAtualLocal();

    printf("CONTA ESPECIAL (S/N): ");
    scanf(" %c", &contaEspecial);
    if(contaEspecial == 'S' || contaEspecial == 's')
    {
        conta.contaEspecial = 1;
        conta.limite = 1000;
    }
    else
    {
        conta.contaEspecial = 0;
        conta.limite = 0;
    }

    conta.cliente = getCliente();

    do
    {
        printf("SALDO: ");
        scanf("%f", &conta.saldo);
    }
    while(conta.saldo <= 0);

    return adicionarConta(conta);
}

int entradaNumeroConta(char menuEscolha)
{
    if(menuEscolha == '7')
    {
        return operacaoTransferencia();
    }

    int numero;
    TConta conta;
    float novoSaldo;

    printf("Numero Conta: ");
    scanf("%i", &numero);

    switch(menuEscolha)
    {
    case '4':
        return pesquisarConta(numero);

    case '5':
        conta = getConta(numero);

        if(getPosicaoConta(numero) >= 0)
        {
            novoSaldo = depositar(conta);

            if(novoSaldo > 0)
            {
                contas[getPosicaoConta(numero)].saldo = novoSaldo;
                return 1;
            }
        }

        return 0;

    case '6':
        conta = getConta(numero);

        if(getPosicaoConta(numero) >= 0)
        {
            novoSaldo = debitar(conta);

            if(novoSaldo > 0)
            {
                contas[getPosicaoConta(numero)].saldo = novoSaldo;
                return 1;
            }
        }

        return 0;

    case '8':
        return removerConta(numero);
    }
}

int operacaoTransferencia()
{
    TConta origem, destino;
    int numeroOrigem, numeroDestino;
    float novoSaldoOrigem, novoSaldoDestino;

    printf("Numero Conta Origem: ");
    scanf("%i", &numeroOrigem);

    printf("Numero Conta Destino: ");
    scanf("%i", &numeroDestino);

    origem = getConta(numeroOrigem);
    destino = getConta(numeroDestino);
    if(getPosicaoConta(numeroOrigem) >= 0 && getPosicaoConta(numeroDestino) >= 0)
    {
        int result = 0;
        result = transferir(origem, destino, &novoSaldoOrigem, &novoSaldoDestino);

        if(result != 0)
        {
            contas[getPosicaoConta(numeroOrigem)].saldo = novoSaldoOrigem;
            contas[getPosicaoConta(numeroDestino)].saldo = novoSaldoDestino;
        }

        return result;
    }

    return 0;
}
