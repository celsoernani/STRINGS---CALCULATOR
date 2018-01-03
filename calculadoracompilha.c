#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

typedef struct{
    char* conteudo;
    int topo;
}Pilha; //declarando a pilha

void verificapilha(Pilha* pilha,char item){
    if(pilha->topo ==  100 ){
        printf("PILHA CHEIA!");
        return;
    }
    pilha->topo++;
    pilha->conteudo[pilha->topo - 1] = item;
} //verificando se a pilha já esta no seu tamanho maximo que no caso é 100, CASO NAO O TOPO É AUEMTNADO E O ITEM É ADICIONADO

char verificapilha1(Pilha* pilha){
    if(pilha->topo <= 0){
        printf("PILHA VAZIA");
        return '\0';
    }
    return pilha->conteudo[pilha->topo];
} //verificando se a pilha já esta vazia, CASO NAO, O CONTEUDO VAI PARA O TOPO


int expressao1(char* expressao){
    int num1,num2,i,j;
    int saida;
    char expguard[10],expguard1[10];
    char op;
    int negativo1 = 0 , negativo2 = 0;
    i = 0;
    if(expressao[i] == '-'){
        negativo1 = 1;
        i++;
    }//se o primeiro caractere da insta for negativo ele identica e, assim contando para a resolução da expressao
    j = 0;
                    //lendo os caracteres da expresssao
                    while(isdigit(expressao[i])){
                            expguard[j] = expressao[i];
                                i++;
                                j++;
                                }

    num1 = atoi(expguard); //convertendo string em inteiro
                    if(negativo1){
                        num1 = - num1;
                                 } //tirando o menos caso o primeiro caractere for negativo

                    op = expressao[i];
                        i++; // pegndo o primeiro operador


                        if(expressao[i] == '-'){
                            negativo2 = 1;
                                i++;
                                    }

                                    j = 0;// zerando o contador J



                    while(isdigit(expressao[i])){
                        expguard1[j] = expressao[i];
                                i++;
                                j++;
                                }//lendo os caracteres da expresssao
    num2 = atoi(expguard1);//convertendo string em inteiro


    if(negativo2){
        num2 = - num2;
    } // mesma operação acima


    // operadores ! para operar a primeira operação caso só tenha duas operações
    if(op == '+'){
        saida = num1 + num2;
    }
    else if(op == '-'){
        saida = num1 - num2;
    }
    else if(op == '*'){
        saida = num1 * num2;
    }
    else{
        saida = num1 / num2;
    }
    return saida;
}

//contando a quantidade de numeros sem ser contar com os operadores
int quantnumeros(char* expressao){
    int i = 0;
     int numeros = 0;
    while(expressao[i] != '\0'){
        if(isdigit(expressao[i])){
            while(isdigit(expressao[i])){
                i++;
            }
            numeros++;
        }
        i++;
    }
    return numeros;
}


//achando o penultimo numero para que posso operar as expressões
// se a quantidade for menor que dois ele retorna i que é quantidade de operadores
int achandoNumero(char* expressao){
    int n = quantnumeros(expressao);
    int qt =0;
    int i =0;
    while(expressao[i] != '\0'){
        if(isdigit(expressao[i])){
            while(isdigit(expressao[i])){
                i++;
            }
            qt++;
            if(n - qt <= 2){
                return i;
            }
        }
        i++;
    }
}

int resolverexpressao(char* expressao){ // a função de resolver expressao recebe a propria , e sai operando dois por dois cada vez que acha um operador
    char saidadefitiva[10];
    int i;
    int numeros = achandoNumero(expressao);
    Pilha p; // declarando a variavel auxiiar p para empilhamento
    p.topo = 0; // topo recebendo 0
    p.conteudo = (char*)malloc((strlen(expressao) - numeros) * sizeof(char));  //alocando memoria suficiente
    p.conteudo[(strlen(expressao) - numeros) - 1] = '\0';
    if(quantnumeros(expressao) > 2){
                for(i = numeros + 1; i < strlen(expressao); i++){ // for para resolção de toda a expressao, percorrendo toda a string
                    verificapilha(&p,expressao[i]);
                            } // verificando se a pilha esta de tamanho cheio
        itoa(expressao1(p.conteudo),saidadefitiva,10);
        char nova_expressao[32]; // nova expressao depois de resolver as primeiras que são as ultimas. e assim até que todos os operadores sejam operados.
        for(i = 0; i <= numeros; i++){
            nova_expressao[i] = expressao[i];
        } //fazendo isso até o final concluir toda a expressao
        nova_expressao[i] = '\0';
        strcat(nova_expressao,saidadefitiva); // contatenando as strings a cada laço do for
        nova_expressao[strlen(nova_expressao) + 1] = '\0';
        resolverexpressao(nova_expressao);
    }
    else{
        return expressao1(expressao);
    }
}


int main(){
    int i;
    char entrada[32]; // entrada
    Pilha pilha; //criando a pilha axiliar
    pilha.topo = 0;
    printf("EXPRESSÃO: ");
    fflush(stdin);
    fgets(entrada,32,stdin);
 //LENDO A ENTRADA
    if(entrada[strlen(entrada) - 1] == '\n'){
        entrada[strlen(entrada) - 1] = '\0';
    } // VERIFICANDO SE A PILHA ESTA LOTADA
    pilha.conteudo = (char*)malloc((strlen(entrada) + 1) * sizeof(char));
    pilha.conteudo[strlen(entrada)] = '\0';// ALOCANDO MEMORIA SUFICNETE
    for(i = 0; i < strlen(entrada); i++){
        verificapilha(&pilha,entrada[i]);
    }
    printf("\n\n R: %d\n\n",resolverexpressao(pilha.conteudo));
    free(pilha.conteudo);// LIVRANDO MEMORIA
    return 0;
}
