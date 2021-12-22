// TRABALHO DE PAULO EDUARDO RAMOS DE ARAUJO E RENAN DE CALDAS PEREIRA BONA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#define JOGOS 2
#define MAX 6

//structs
typedef struct
{
    char apelido[11];
    int totalpontos[JOGOS]; // 0 - jogo da velha === 1 - dados
    int partida[JOGOS]; // 0 - jogo da velha === 1 - dados
} tjogador;
typedef struct
{
    int quant; // quantidade de jgoadores na competição
    int jogador[MAX]; // indice dos jogadores na competição, max 6
    int pontos[MAX][JOGOS]; // pontos ganho na competição
} tcompeticao;

// FUNÇÕES
/*ESTÁ FUNÇÃO É UMA ANIMAÇÃO DE BONEQUINHO PULANDO*/
void comemoracao()
{
    int animacao, animacao2;
    for(animacao=0; animacao<7; animacao++)
    {
        for(animacao2=0; animacao2<5; animacao2++)
        {
            system("cls");
            printf("  O    O    O    O    O\n /|\\  /|\\  /|\\  /|\\  /|\\\n / \\  / \\  / \\  / \\  / \\\n");
        }
        for(animacao2=0; animacao2<5; animacao2++)
        {
            system("cls");
            printf(" _O_ _O_ _O_ _O_ _O_\n  |   |   |   |   | \n / \\\ / \\\ / \\\ / \\\ / \\\n");
        }
        for(animacao2=0; animacao2<5; animacao2++)
        {
            system("cls");
            printf(" \\O/ \\O/ \\O/ \\O/ \\O/\n  |   |   |   |   | \n / \\ / \\ / \\ / \\ / \\\n");
        }
    }
    system("cls");
    printf(" \\O/ \\O/ \\O/ \\O/ \\O/\n  |   |   |   |   | \n / \\ / \\ / \\ / \\ / \\\n");

}
/*Esta função são apenas uma sequencia de asteriscos para enfeite*/
void asteriscos()
{
    int a;
    for(a=0; a<25; a++)
    {
        printf("*");
    }
}
/*Esta função serve para adicionar novos jogadores, usando a struct já feita e o cont
para saber quantos jogadores já foram cadastrados e qual o número do novo jogador..*/
int newplay(tjogador jogadores[], int numplay)
{
    // variáveis da função
    char presave[11];
    int tester1, again;
    do
    {
        again = 5000;
        system("clear || cls");
        printf("Digite o seu Nome/Apelido ( 10 caracteres no máximo ):.... ");
        scanf("%s", &presave);

        tester1 = repetido(jogadores, presave);

        if(tester1 >= 1)
        {
            printf("\nJogador já cadastrado, deseja cadastrar outro player?");
            do
            {
                printf("\nPara tentar novamente digite 1, e para sair digite 2:..... ");
                scanf("%d", &again);
            }
            while(again != 1 && again != 2);

            if(again == 2)
            {
                return numplay;
            }
        }
    }
    while(again == 1);

    strcpy(jogadores[numplay].apelido, presave);
    jogadores[numplay].partida[0] = 0;
    jogadores[numplay].partida[1] = 0;
    jogadores[numplay].totalpontos[0] = 0;
    jogadores[numplay].totalpontos[1] = 0;

    numplay ++;

    system("clear || cls");
    printf("*************************************\nNovo Jogador Cadastrado!!\n*************************************\n\n\n");
    system("pause");
    return numplay;
}
/*Esta função serve para verificar se certo nome de jogador já existe ultizando uma string preselecionada e a struct jogadores..*/
int repetido(tjogador jogadores[], char tester[])
{
    int j, flagzinha = 0;
    for(j=0; j<100; j++)
    {
        if(strcmpi(jogadores[j].apelido, tester) == 0)
            flagzinha++;
    }
    return flagzinha;
}
/*Esta função serve para alterar o nome, ela primeiro usa a função procurar play para descobrir o número do jogador na struct e
e depois salva o novo nome em um auxiliar, após a verificação se o novo nome é igual a um pre existente, na função repetido, é aderido copiado
a string aux na string apelido.*/
void alterarnome(tjogador jogadores[])
{
    // Variáveis
    char player[11], aux[11];
    int playnumber, verif = 0, confirm, already;
    // ------------
    do
    {
        already = 0;
        system("clear || cls");
        asteriscos();
        printf("\nALTERAÇÃO DE PLAYER\n");
        asteriscos();
        printf("\nPara alterar um jogador, digite seu Nome/Apelido.....:  ");
        scanf("%s", &player);

        playnumber = procurarplay(jogadores, player);
        if(playnumber == -5)
        {
            printf("\nJogador Não existe, deseja procurar outro?");
            do
            {
                printf("\nDigite 1 para procurar outro e 2 para voltar ao menú....:  ");
                scanf("%d", &already);
                if(already != 1 && already != 2)
                    printf("\nValor inválido..");
            }
            while(already != 1 && already != 2);
        }
    }
    while(already == 1);
    if(already == 2)
        return;
    do
    {
        verif = 0;
        system("cls || pause");
        printf("\nDigite o novo nome de jogador.....:  ");
        scanf("%s", &aux);

        verif = repetido(jogadores, aux);

        if(verif >= 1)
        {
            printf("\nNome já está em uso, digite outro..");
        }
        else
        {
            printf("\nDeseja alterar seu nick de --> %s <-- para --> %s <-- ?", jogadores[playnumber].apelido, aux);
            do
            {
                printf("\nDigite 1 para confirmar e 2 para escolher outro....:  ");
                scanf("%d", &confirm);
                if(confirm != 1 && confirm != 2)
                {
                    printf("\nVocê digitou um valor inválido..");
                }
            }
            while(confirm != 1 && confirm != 2);
            if(confirm == 1)
                strcpy(jogadores[playnumber].apelido, aux);
            else
                verif = 1;
        }

    }
    while(verif >= 1);

    system("cls || clear");
    asteriscos();
    printf("\nALTERAÇÃO FEITA COM SUCESSO!!!\n");
    asteriscos();
    printf("\n\n");
    system("pause");
}
/*Esta função serve para saber o número do player de acordo com uma string preselecionada e retorna o valor da posição do jogador e se não existir o player vai
retornar -5.*/
int procurarplay(tjogador jogadores[], char nickdoplayer[])
{
    int i;
    for(i=0; i<100; i++)
    {
        if(strcmpi(jogadores[i].apelido, nickdoplayer) == 0)
            return i;
    }
    return -5;

}
/*Essa função é apenas o menú de alterar jogador, levando para outras 2 funções..*/
void alterarjogador(tjogador jogadores[])
{
    int menu1;
    //=--------------------
    do
    {
        system("cls || clear");
        asteriscos();
        printf("\nMENU DE ALTERAÇÃO DE JOGADOR!!");
        printf("\n1- Alterar nome/apelido\n2- Resetar pontuacao\n0- Sair\n");
        asteriscos();
        printf("\nDigite um número para navegar no menú...:  ");
        scanf("%d", &menu1);

        switch(menu1)
        {
        case 1:
            alterarnome(jogadores);
            break;
        case 2:
            resetscore(jogadores);
            break;
        case 0:
            return;
            break;
        }
    }
    while(1);
}
/*Essa função reseta os pontos dos jogdaores, primeira ela ultiliza a função procurarplay para pegar o número do jogador de acordo com o
nome e se o jogador for encontrado ( playerid > 0) ela reseta seus pontos.*/
void resetscore(tjogador jogadores[])
{
    //variáveis
    char playreset [10];
    int aux1=0, aux2=0, playerid;
    // ---------------
    do
    {
        aux1 = 0;
        system("cls || clear");
        asteriscos();
        printf("\nRESETAR PONTUAÇÃO DO JOGADOR!!\n");
        asteriscos();
        printf("\nQual jogador deseja resetar a pontuação?\n");
        scanf("%s", &playreset);

        playerid = procurarplay(jogadores, playreset); //se existir um usuário o valor retornado é > que 0 e se não existir retorna -5

        if(playerid == -5) // condicional para executar se não existir
        {
            printf("\nJogador não existe, deseja digitar novamente?[1 - sim, 2 - não]....: ");
            do
            {
                scanf("%d", &aux1);
                if(aux1 != 1 && aux1 != 2)
                    printf("Número inválido, digite novamente....:  ");
            }
            while(aux1 != 1 && aux1 != 2);
        }
    }
    while(aux1 == 1);

    if(aux1 != 2)
    {
        do
        {
            aux2 = 0;
            system("cls || clear");
            printf("Tem certeza que quer resetar a pontuação do jogador --> %s <--?[1-sim, 2-não]....:  ", jogadores[playerid].apelido);
            scanf("%d", &aux2);
            if(aux2 != 1 && aux2 != 2)
                printf("Resposta Inválida.");
        }
        while(aux2 != 1 && aux2 != 2);

        if(aux2 == 1)
        {
            jogadores[playerid].partida[0] = 0;
            jogadores[playerid].partida[1] = 0;
            jogadores[playerid].totalpontos[0] = 0;
            jogadores[playerid].totalpontos[1] = 0;
        }
        else
        {
            system("cls || clear");
            printf("\nRetornando para o menú de alterações...\n\n");
            system("pause");
            return;
        }
        system("cls || clear");
        asteriscos();
        printf("\nALTERAÇÕES FEITAS COM SUCESSO!!\n");
        asteriscos();
        printf("\n\n");
    }
    if(aux2 == 2)
    {
        system("cls || clear");
        printf("\nRetornando para o menú de alterações...\n\n");
    }
    system("pause");
    return;
}
/*Essa função dá a lista de todos jogadores cadastrados e fornecendo seu ID e pontos.. é ultilizado um comando de repetição para isso..*/
void listar(tjogador jogadores[], int maxcadastrado)
{
    // variáveis
    int i;
    //-----------------
    system("cls || clear");
    asteriscos();
    printf("\nLISTA DE TODOS OS JOGADORES.\n");
    asteriscos();

    for(i=0; i<maxcadastrado; i++)
    {
        printf("\n-------------------------------------");
        printf("\nJogador de ID =-=-=-=-= %d", i);
        printf("\nPlayer Name::::::::::::::::::::::::::::::::::::::::: %s", jogadores[i].apelido);
        printf("\nTotal de pontos no Jogo da Velha:::::::::::::::::::: %d", jogadores[i].totalpontos[0]);
        printf("\nTotal de pontos no Jogo dos Dados::::::::::::::::::: %d", jogadores[i].totalpontos[1]);
        printf("\nTotal de jogos realizados em Jogo da Velha:::::::::: %d", jogadores[i].partida[0]);
        printf("\nTotal de jogos realizados em Jogo dos Dados::::::::: %d", jogadores[i].partida[1]);

    }
    printf("\n\n");
    system("pause");
    return;
}
/*Essa função é apenas o menu da competição ( o nome cblol é uma homenagem )*/
int menucblol(tcompeticao cblol, tjogador jogadores[],int menu3)
{
    system("cls || clear");
    asteriscos();
    printf("\n   MENU DE JOGOS\n 1 - Jogo da Velha[Max 2 jogadores]\n 2 - Jogo do 21 com dados\n 3 – Mostrar pontos\n 0 – Sair\n");
    asteriscos();
    do
    {
        printf("\nDigite um número para navegar no menú...:  ");
        scanf("%d", &menu3);
        if(menu3 <0 || menu3 >3)
            printf("\nNúmero invalido...");
    }
    while(menu3 <0 || menu3 >3);

    return menu3;
}
int verificarvencedor(char matriz[3][3], char peca)
{
    int i, j, flag = 0;
    char tabule;
    tabule = peca;
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(matriz[i][j] == tabule)
            {
                flag++;
            }
        }
        if(flag == 3)
        {
            return 1;
        }
        flag = 0;
    }
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(matriz[j][i] == tabule)
            {
                flag++;
            }
        }
        if(flag == 3)
        {
            return 1;
        }

        flag = 0;
    }
    for(i = 0; i < 3; i++)
    {
        if(matriz[i][i] == tabule)
        {
            flag++;
        }
        if(flag == 3)
        {
            return 1;
        }
    }
    for(i = 3; i > 3; i--)
    {
        if(matriz[i][i] == tabule)
        {
            flag++;
        }
        if(flag == 3)
        {
            return 1;
        }
    }
    for(i = 0; i < 3; i++)
    {
        for(j = 0; j < 3; j++)
        {
            if(matriz[j][i] != ' ')
            {
                flag++;
            }
        }
        if(flag == 9)
        {
            return -1;
        }
    }
    return 0;
}
int jogodavelha(tcompeticao cblol, tjogador jogadores[])
{
    // variáveis
    char peca1, peca2;
    int iniciar, venc;
    char matriz[3][3];
    // -----------------
    system("cls || clear");
    asteriscos();
    printf("\nJOGO DA VELHA\n");
    asteriscos();
    do
    {
        fflush(stdin);
        printf("\n--> %s <-- Escolha sua peça[x ou o]...:  ", jogadores[cblol.jogador[0]].apelido);
        scanf("%c", &peca1);
        if(peca1 != 'x' && peca1 != 'X' && peca1 != 'o' && peca1 != 'O');
    }
    while(peca1 != 'x' && peca1 != 'X' && peca1 != 'o' && peca1 != 'O');

    if(peca1 == 'x')
        peca1 = 'X';
    if(peca1 == 'o')
        peca1 = 'O';

    if(peca1 == 'X')
        peca2 = 'O';
    else
        peca2 = 'X';

    do
    {
        printf("\nQuem iniciará o game?[1 - %s |||||| 2 - %s]...:", jogadores[cblol.jogador[0]].apelido, jogadores[cblol.jogador[1]].apelido);
        scanf("%d", &iniciar);
        if(iniciar != 1 && iniciar != 2)
            printf("\nNúmero inválido!!");
    }
    while(iniciar != 1 && iniciar != 2);

    system("cls || clear");
    asteriscos();
    asteriscos();
    printf("\nO JOGO JÁ VAI COMEÇAR!!!\n");
    asteriscos();
    asteriscos();
    printf("\n\n");
    system("pause");

    system("cls || clear");
    inicializarjogo(matriz);
    mostrarjogo(matriz);
    system("pause");

    if(iniciar == 1)
    {
        do
        {

            realizarjogada(matriz, 1, peca1);
            venc = verificarvencedor(matriz, peca1);
            mostrarjogo(matriz);
            if(venc == 1)
            {
                printf("JOGADOR 1 VENCEU:\n");
                return 1;
            }
            if(venc == -1)
            {
                printf("DEU VELHA");
                return 0;
            }
            realizarjogada(matriz, 2, peca2);
            venc = verificarvencedor(matriz, peca2);
            mostrarjogo(matriz);
            if(venc == 1)
            {
                printf("JOGADOR 2 VENCEU:\n");
                return 2;
            }
            if(venc == -1)
            {
                printf("DEU VELHA");
                return 0;
            }


            venc = 0;
        }
        while(1);
    }
    else
    {
        do
        {

            realizarjogada(matriz, 2, peca2);
            venc = verificarvencedor(matriz, peca2);
            mostrarjogo(matriz);
            if(venc == 1)
            {
                printf("JOGADOR 2 VENCEU:\n");
                return 2;
            }
            if(venc == -1)
            {
                printf("DEU VELHA");
                return 0;
            }
            realizarjogada(matriz, 1, peca1);
            venc = verificarvencedor(matriz, peca1);
            mostrarjogo(matriz);
            if(venc == 1)
            {
                printf("JOGADOR 1 VENCEU:\n");
                return 1;
            }
            if(venc == -1)
            {
                printf("DEU VELHA");
                return 0;
            }


            venc = 0;
        }
        while(1);
    }
    return 50;
    /*OBS.. JOGADOR 1 TEM A PECA1 E JOGADOR 2 TEM A PECA2, QUEM VAI INICIAR TEM NO INT INICIAR*/
}
/*Objetivo: inicializar a matriz com todos os elementos iguais ao caracter ‘ ‘ (um “espaço” está entre as aspas), para indicar “casa livre” */
void inicializarjogo(char matriz[3][3])
{
    //variáveis
    int i, j;
    //------------
    for(i=0; i<3; i++)
    {
        for(j=0; j<3; j++)
        {
            matriz[i][j] = ' ';
        }
    }
}
//Objetivo: Realizar uma jogada do usuário
void realizarjogada(char matriz[3][3], int jogador, char peca)
{
    int linha, coluna, aux;
    do
    {
        aux = 0;
        printf("--> %d <-- Escolha a linha e a coluna para jogar[1 - 2 - 3].", jogador);
        do
        {
            printf("\nLinha...: ");
            scanf("%d", &linha);
            if(linha < 1 || linha > 3)
                printf("\nNúmero inválido, escolha um número dentre estes: [ 1 - 2 - 3 ]");
        }
        while(linha < 1 || linha > 3);
        do
        {
            printf("\nColuna...: ");
            scanf("%d", &coluna);
            if(coluna < 1 || coluna > 3)
                printf("\nNúmero inválido, escolha um número dentre estes: [ 1 - 2 - 3 ]");
        }
        while(coluna < 1 || coluna > 3);

        if(matriz[linha - 1][coluna - 1] != ' ')
        {
            printf("\nO local já foi escolhido, escolha outro..");
            aux = 1;
            system("pause");
        }
        else
            matriz[linha - 1][coluna - 1] = peca;
        system("pause");
    }
    while(aux == 1);

}
void mostrarjogo(char matriz[3][3])
{
    system("cls || clear");
    printf("\t\t\t       1       2       3 \n");
    printf("\t\t\t           ||     ||               \n");
    printf("\t\t\t  1    %c   ||  %c  ||   %c            \n", matriz[0][0], matriz[0][1], matriz[0][2]);
    printf("\t\t\t           ||     ||               \n");
    printf("\t\t\t    ========================    \n");
    printf("\t\t\t           ||     ||               \n");
    printf("\t\t\t  2    %c   ||  %c  ||   %c            \n", matriz[1][0], matriz[1][1], matriz[1][2]);
    printf("\t\t\t           ||     ||               \n ");
    printf("\t\t\t    ========================      \n");
    printf("\t\t\t           ||     ||               \n");
    printf("\t\t\t  3    %c   ||  %c  ||   %c            \n", matriz[2][0], matriz[2][1], matriz[2][2]);
    printf("\t\t\t           ||     ||               \n");
}
int jogo21(int pont[], tjogador jogadores[], tcompeticao cblol)
{
    int dadoB[3], dadoV[3], jogar, i, jogada, list;

    for(i=0; i<3; i++)
    {
        dadoB[i] = 0;
        dadoV[i] = 0;
    }
    for(i = 0; i< cblol.quant; i++)
    {
        pont[i] = 0;    //todos os jogadores comecam com 0 pontos na soma dos dados
    }

    for(jogada=0; jogada<3; jogada++)
    {
        system("cls || clear");
        for(i=0; i<cblol.quant; i++)
        {
            printf("\n %s: Jogar dados (1) ou passa a vez (2)?\n", jogadores[cblol.jogador[i]].apelido);
            do
            {
                scanf("%d", &jogar);
                if(jogar != 1 && jogar != 2)
                {
                    printf("Valor inválido.\n");
                }
            }
            while(jogar != 1 && jogar != 2);
            if(jogar == 1)
            {
                srand(time(NULL));
                dadoB[i] = rand() % 6 + 1;
                dadoV[i] = rand() % 6 + 1;
                pont[i] += (dadoB[i] + 2*(dadoV[i]) );
            }
            else
            {
                dadoB[i] = 0;
                dadoV[i] = 0;
            }
        }
        printf("Final da %d Rodada", jogada+1);
        for(list = 0; list < cblol.quant; list++)   //jogadores[cblol.jogador[0]].apelido
        {
            printf("\n %s : soma dos dados = %d ", jogadores[cblol.jogador[list]].apelido, pont[list]);
        }
        printf("\n\n");
        system("pause");
    }
}
// FIM DAS FUNÇÕES----------------------------------------------------
int main()
{

    // variáveis
    int result[MAX], flag = 0, pmaisproximo = -100;
    int pont[MAX];
    int menu, playerid = 0, menu3, cblolplayer, j, playerid3;
    int i, playerid1, linha324, do320, retornovelha;
    char auxname[11];
    tjogador jogadores[100]; // configuração de cad ajogador
    tcompeticao cblol; // variável das competições
    char matriz[3][3];

    // Menu
    setlocale(LC_ALL, "Portuguese");
    do
    {
        system("cls || clear");
        printf("******************************************");
        printf("\n1 - Cadastrar jogador.");
        printf("\n2 - Alterar jogador.");
        printf("\n3 - Listar jogadores.");
        printf("\n4 - Iniciar competição.");
        printf("\n0 - Sair.");
        printf("\n******************************************");
        printf("\nPara navegar, digite um número:  ");
        scanf("%d", &menu);

        switch(menu)
        {
        case 1:
            if(playerid > 99)
                printf("Servidores Cheios, já foram cadastrados 100 jogadores.");
            else
                playerid = newplay(jogadores, playerid);
            break;
        case 2:
            alterarjogador(jogadores);
            break;
        case 3:
            listar(jogadores, playerid);
            break;
        case 4:
            /*AQUI COMEÇA O INICIO DA COMPETIÇÃO, PRIMEIRO PERGUNTA QUANTOS JOGADORES TEM E DEPOIS PEDE O NOME DE CADA COMPETIDOR*/
            do
            {
                system("cls || clear");
                comemoracao();
                asteriscos();
                printf("\nO TORNEIO VAI COMEÇAR..\n");
                asteriscos();
                printf("\nPara iniciar uma competição informe quantos jogadores terão [min 2 -- max %d]....:  ", MAX);
                scanf("%d", &cblol.quant);
                if(cblol.quant < 2 || cblol.quant > MAX)
                    printf("\nNúmero inválido, lembre-se [min 2 -- max %d]!!", MAX);
            }
            while(cblol.quant < 2 || cblol.quant > MAX);

            for(i=0; i<cblol.quant; i++)
            {
                do
                {
                    playerid1 = 0;
                    linha324 = 0;
                    printf("\nQual nome/apelido do competidor de número %d....:  ", i+1);
                    scanf("%s", &auxname);
                    playerid1 = procurarplay(jogadores, auxname);

                    if(playerid1 == -5)
                    {
                        do
                        {
                            printf("\nJogador não existe, deseja digitar novamente?[1- sim, 2-não]");
                            scanf("%d", &linha324);
                            if(linha324 != 1 && linha324 != 2)
                                printf("\nNúmero inválido, lembre-se [1- sim, 2-não]!!");
                        }
                        while(linha324 != 1 && linha324 != 2);
                        if(linha324 == 2)
                        {
                            return 0;
                        }
                    }
                    else
                    {
                        cblol.jogador[i] = playerid1;
                        cblol.pontos[i][1] = 0;
                        cblol.pontos[i][2] = 0;
                    }
                }
                while(linha324 == 1);
            }
            system("cls || clear");
            asteriscos();
            asteriscos();
            printf("\nCOMPETIÇÃO INICIADA COM SUCESSO!!\n");
            asteriscos();
            asteriscos();
            printf("\n\n");
            system("pause");

            /*AQUI É O MENU DA COMPETIÇÃO*/
            do
            {
                menu3 = menucblol(cblol, jogadores, 0);
                if(menu3 == 1)
                {
                    if(cblol.quant == 2)
                    {
                        retornovelha = jogodavelha(cblol, jogadores);
                        jogadores[cblol.jogador[0]].partida[0]++;
                        jogadores[cblol.jogador[1]].partida[0]++;
                        if(retornovelha == 1)
                        {
                            system("cls");
                            printf("%s FOI O GANHADOR.\n", jogadores[cblol.jogador[0]].apelido);
                            jogadores[cblol.jogador[0]].totalpontos[0]++;
                            cblol.pontos[0][0]++;
                            system("pause");
                        }
                        else if(retornovelha == 2)
                        {
                            system("cls");
                            printf("%s FOI O GANHADOR.\n", jogadores[cblol.jogador[1]].apelido);
                            cblol.pontos[1][0]++;
                            jogadores[cblol.jogador[1]].totalpontos[0]++;
                            system("pause");
                        }
                        else
                        {
                            system("cls");
                            printf("Infelizmente deu velha, tente de novo.\n");
                            system("pause");

                        }

                    }
                    else
                    {

                        system("cls || clear");
                        printf("\nTem mais jogadores que o permitido..\n");
                        system("pause");
                    }
                }
                else if(menu3 == 2)
                {
                    //Jogo 21 dados

                    jogo21(pont, jogadores, cblol);
                    // VERIFICAR GANHADOR
                    for(i=0; i<cblol.quant; i++)            //a pontuacao mais proxima de 21 e so encontrar aquele q ao subtrair de 21, ficou mais proximo de 0
                    {
                        result[i] = 21 - pont[i];
                        if(result[i] == 0)
                        {
                            system("cls || clear");
                            printf("%s ganhou.\n", jogadores[cblol.jogador[i]].apelido);
                            jogadores[cblol.jogador[i]].totalpontos[1]++;
                            flag = 1;       //se ao menos um fizer 21 ja nao entra no if abaixo
                        }
                    }
                    if(flag == 0)
                    {
                        for(i = 0; i<cblol.quant; i++)
                        {
                            if(result[i] > 0)
                            {
                                flag = 1;                       //se todos os jogadores tiverem passado de 21, flag = 1
                                if(pmaisproximo<result[i])
                                {
                                    pmaisproximo = result[i];       //assim achamos o valor mais proximo de 21
                                }
                            }
                        }
                        for(i=0; i< cblol.quant; i++)
                        {
                            if(result[i] == pmaisproximo)           //o jogador, ou os jogadores que tiverem mais proximos de 21 vencerao
                            {
                                system("cls || clear");
                                printf("%s ganhou.\n", jogadores[cblol.jogador[i]].apelido);
                                jogadores[cblol.jogador[i]].totalpontos[1]++;
                                for(j=0; j<cblol.quant; j++)
                                {
                                    jogadores[cblol.jogador[j]].partida[1]++;
                                }
                                cblol.pontos[i][1]++;
                            }
                        }
                        if(flag == 0)                   //se entrou dentro da flag 0 e n mudou para a flag 1, significa q todos fizeram mais de 21, logo ninguem ganhou
                        {
                            printf("\nSEM VENCEDORES!!!\n\n");
                        }
                    }
                    system("pause");
                //----------------------------------------------
                }
                else if(menu3 == 3)
                {
                    /*AQUI É A LISTA DOS PONTOS DE CADA JOGADOR, SEU ID E SEU NOME.. OBS.: NÃO COLOQUEI EM UMA FUNÇÃO
                    BECUSE POR ALGUM MOTIVO, QUE SÓ DEUS SABE, DEU ERRO..*/
                    system("cls || clear");
                    asteriscos();
                    asteriscos();
                    printf("\nPONTUAÇÃO!!\n");
                    asteriscos();
                    asteriscos();

                    for(i=0; i<cblol.quant; i++)
                    {
                        printf("\n-------------------------------------");
                        printf("\nNúmero do jogador[ID] =-=-=-=-=-=-= %d", cblol.jogador[i]);
                        printf("\nNome do jogador ::::::::::::::::::::::::::::::::::::::::: %s", jogadores[cblol.jogador[i]].apelido);
                        printf("\nPontos no Jogo da Velha ::::::::::::::::::::::::::::::::: %d", cblol.pontos[i][0]);
                        printf("\nPontos no Jogo dos Dados :::::::::::::::::::::::::::::::: %d", cblol.pontos[i][1]);
                    }
                    printf("\n\n");
                    system("pause");
                }
                else
                    break;
            }
            while(1);
            break;
        case 0:
            return 0;
            break;
        }
    }
    while(1);
    return 0;
}
