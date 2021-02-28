#include <stdio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>
#include <time.h>

char campoUSER[9][9], campoSYS[9][9];

int espacos_brancos = 0, dicas = 0;

/*
    Tabela ASCII

    'B' = 66
    '-' = 196
    '*' = 42
    '(espaço)' = 32
    'x' = 120
*/

/* Função que preenche as matrizes*/
void PreencherMatriz(){

    int i, j;

    for (i = 0; i < 10; i++){
        for (j = 0; j < 10; j++)
        {
            campoUSER[i][j] = 196;
            campoSYS[i][j] = 32;
        }
    }
    return;
}

/* Função que gera as bombas em posições aleatórias*/
void GerarBombas(){
    
    int i, fileira, coluna;

    srand(time(NULL));  /* Gerando seeds para a rand();*/

    /* campoSYS[0][0] = 42; Sempre tem uma bomba na posição 0 0, pra casos de teste*/

    /* Preenchendo a matriz com as bombas*/
    for (i = 0; i < 9; i++)
    {   
        fileira = rand() % 9;
        coluna = rand() % 9;
            
        if (campoSYS[fileira][coluna] == 42)
        {
            campoSYS[fileira+1][coluna] = 42;
        }
        else
        {
            campoSYS[fileira][coluna] = 42; 
        } 
    }
}

/* Função que gera as dicas (números) onde podem estar as bombas */
void Dica(){
    
    int i, j, contarBombas = 0;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (campoSYS[i - 1][j - 1] == 42 && ((i - 1) >= 0 && (j - 1) >= 0))
            {
                contarBombas++;
            }
            if (campoSYS[i - 1][j] == 42 && (i - 1) >= 0)
            {
                contarBombas++;
            }
            if (campoSYS[i - 1][j + 1] == 42 && ((i - 1) >= 0 && (j + 1) <= 8))
            {
                contarBombas++;
            }
            if (campoSYS[i][j + 1] == 42 && (j + 1) <= 8)
            {
                contarBombas++;
            }
            if (campoSYS[i + 1][j + 1] == 42 && ((i + 1) <= 8 && (j +1) <= 8))
            {
                contarBombas++;
            }
            if (campoSYS[i+ 1][j] == 42 && (i + 1) <= 8)
            {
                contarBombas++;
            }
            if (campoSYS[i + 1][j - 1] == 42 && ((i + 1) <= 8 && (j - 1) >= 0))
            {
                contarBombas++;
            }
            if (campoSYS[i][j - 1] == 42 && (j - 1) >= 0)
            {
                contarBombas++;
            }
            if (contarBombas == 0 && campoSYS[i][j] != 42)
            {
                campoSYS[i][j] = 32;
                espacos_brancos++;
            }
            else if (campoSYS[i][j] != 42)
            {
                campoSYS[i][j] = contarBombas +'0';
                dicas++;
            }

            contarBombas = 0;
        }
    }
    return;
}

/* Função para revelar para o usuário as bombas */
void RevelarBombaas(){

    int i, j;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if (campoSYS[i][j] == 42)
            {
                campoUSER[i][j] = 42;
            }
        }
    }
    return;
}

/* Função que revela as dicas e onde não tem bomba*/
void RevelarCampo(int linha, int coluna){

    int i, j;

    if (campoSYS[linha][coluna] == 32)
    {
        campoUSER[linha][coluna] = 32;
        campoSYS[linha][coluna] = 120;

        for (i = linha -1; i <= linha+1; i++)
        {
            if (i == linha)
            {
                for (j = coluna-1; j <= coluna+1; j++)
                {
                    if (campoSYS[i][j] == 32 && j>= 0 && j <= 8)
                    {
                        RevelarCampo(i,j);
                    }
                    else if (campoSYS[i][j] != 120 && campoSYS[i][j] != 42 && j >= 0 && j <= 8 && (49 <= campoSYS[i][coluna] <= 57))
                    {
                        campoUSER[i][j] = campoSYS[i][j];
                        campoSYS[i][j] = 120;
                    }
                }
            }
            else
            {
                if (campoSYS[i][coluna] == 32 && i >= 0 && i <= 8)
                {
                    RevelarCampo(i, coluna);
                }
                else if (campoSYS[i][coluna] != 120 && campoSYS[i][coluna] != 42 && (49 <= campoSYS[i][coluna] <= 57) && i >= 0 && i <= 8)
                {
                    campoUSER[i][coluna] = campoSYS[i][coluna];
                    campoSYS[i][coluna] = 120;   
                }
            }
        }
       return; 
    }
    else if (campoSYS[linha][coluna] != 120 && campoSYS[linha][coluna] != 42)
    {
        campoUSER[linha][coluna] = campoSYS[linha][coluna];
        campoSYS[linha][coluna] = 120;
        return;
    }
}

int Vitoria(){

    int i, j, aux = 0;

    for (i = 0; i < 9; i++)
    {
        for (j = 0; j < 9; j++)
        {
            if ((campoUSER[i][j] >= 49 && campoUSER[i][j] <= 57) || campoUSER[i][j] == 32)
            {
                aux++;
            }
        }
    }
    return aux;
}

/* Função que verifica a jogada do usuário*/
int Jogada(int linha, int coluna){

    int vit = 0;

    if (campoSYS[linha][coluna] == 42)
    {
        RevelarBombaas();
        Imprimir(campoUSER);
        printf("\n-----------------------------");
        printf("\n      VOCE PERDEU!\n");
        printf("-----------------------------\n"); 
        return 1;
    }
    else if (campoSYS[linha][coluna] != 42)
    {
        RevelarCampo(linha,coluna);
        vit = Vitoria();
        if(vit == (espacos_brancos + dicas)){

            Imprimir(campoUSER);

            printf("\n-----------------------------");
            printf("\n    PARABENS! VOCE GANHOU!\n");
            printf("-----------------------------\n");
            return 1;

        }else
        {
            return 0;
        }
        
    }
}

/* Função que imprimi o campo na tela*/
void Imprimir(char campo[9][9]){

    int i, j;

    printf("     |0|1|2|3|4|5|6|7|8|\n");

    for (i = 0; i < 9; i++) {
        printf(" |%d| ", i);
        for (j = 0; j < 9; j++)
        {
            printf(" %c", campo[i][j]);
        }
        printf("  |%d| ", i);
        printf("\n");
    }
    printf("     |0|1|2|3|4|5|6|7|8|\n");
    return;
}

int main() {

    int linha, coluna, vida = 0, aux = 0;

    PreencherMatriz();
    GerarBombas();
    Dica();

    while (vida == 0)
    {
        Imprimir(campoUSER);
        
        printf("\nDigite sua jogada <linha> <coluna>: ");
        scanf("%d %d", &linha, &coluna);
        system("cls"); /* Comando para limpar o console*/
        vida = Jogada(linha, coluna);
    }
    
    return 0;
}