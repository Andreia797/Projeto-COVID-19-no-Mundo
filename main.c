/*

  * Programa: LISTAS (CORONAV�RUS(COVID-19) NO MUNDO)
  * Data de cria��o: 06/06/2020
  * Participante: Andreia Gon�alves Semedo
  * Finalizado em: 03/07/2020

*/

//{Cabe�alho
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

typedef struct Covid19{
    char pais[100];
    int casos;
    int recuperados;
    int obitos;
    int casos_ativos;
}Covid19;

typedef struct No {
    Covid19 covid19;
    struct No *prox;
}No;

typedef struct Lista{
    No *inicio;
}Lista;

//}FIM Cabe�alho

//{Prototipos
void inserirDepois      (char*, Lista*, Covid19*);
void inserirInicio      (Lista* lista, Covid19*);
void inserirFinal       (Lista* lista, Covid19*);
void eliminarNo         (char*, Lista*);
void eliminaInicio      (Lista* lista);
void eliminaFinal       (Lista* lista);
void imprimirLista      (Lista *lista);
void destruirLista      (Lista *lista);
void imprimirNo         (Covid19*);
void calcularRecuperados(Lista*);
void processarAtivos    (Lista*);
void calcularMortos     (Lista*);
void calcularAtivos     (Lista*);
void calcularTotal      (Lista*);
void calcularTotal      (Lista*);
void salvarDados        (Lista*);
void motraOrganizado    (Lista*);
void destruirNo         (No*);
No*  criarNo            (Covid19*);
Covid19* buscar    (char*, Lista*);
Covid19* pedirDados(Covid19*);
char* lerPais      ();
//}FIM Prototipos


void infoCovid19() {
    system("COLOR F0");
    printf ("\n\n\tUNICV\n");
    printf("\t\t\tCORONAV�RUS(COVID-19) NO MUNDO\n\n");
    printf(
    "\n  A Organiza��o Mundial da Sa�de (OMS) declarou,em 30 de janeiro de 2020, que o surto da\n"
    " doen�a causada pelo novo coronav�rus (COVID-19) constitui uma Emerg�ncia de Sa�de P�blica de\n"
    "  Import�ncia Internacional � o mais alto n�vel de alerta da Organiza��o, conforme previsto no\n"
    " Regulamento Sanit�rio Internacional."
    "\n\n  Em 11 de mar�o de 2020, a COVID-19 foi caracterizada pela OMS como uma pandemia."
    );
    getchar();
}

//{Menu de utilidades
int menu() {
    int op=0;
    system("cls");
    system("COLOR 0F");
    printf ("\n\n\tUNICV\n");
    printf("\t\t\t\t\tCORONAV�RUS(COVID-19) NO MUNDO \n\n");
    printf("\t\t-------------------------------------------------------------------------------------\n\n");
    printf("\t\t  1 - IMFORM��O SOBRE CORONAV�RUS(COVID-19)                                            \n");
    printf("\t\t  2 - INSERIR N� NO INICIO DA LISTA                                                    \n");
    printf("\t\t  3 - INSERIR N� NO MEIO DA LISTA                                                      \n");
    printf("\t\t  4 - INSERIR N� NO FINAL DA LISTA                                                     \n");
    printf("\t\t  5 - IMPRIMIR A LISTA                                                                 \n");
    printf("\t\t  6 - PESQUISAR ELEMENTO ATRAV�Z DO NOME DO PA�S                                       \n");
    printf("\t\t  7 - CALCULAR TOTAL DE CASOS                                                          \n");
    printf("\t\t  8 - CALCULAR TOTAL DE MORTOS                                                         \n");
    printf("\t\t  9 - CALCULAR TOTAL DE RECUPERADOS                                                    \n");
    printf("\t\t 10 - IMPRIMIR POR ORDEM ASCENDENTE(COM MAIS CASOS DE COVID-19)                        \n");
    printf("\t\t 11 - CALCULAR CASOS ATIVOS DE CADA PA�S E ENVIA-LOS PARA O FECHEIRO (CasosAtivos.txt) \n");
    printf("\t\t 12 - ENVIAR TODOS OS N�S PARA O FECHEIRO(elementos.txt)                               \n");
    printf("\t\t 13 - REMOVER N� NO INICIO  DA LISTA                                                   \n");
    printf("\t\t 14 - REMOVER N� NO MEIO DA LISTA                                                      \n");
    printf("\t\t 15 - REMOVER UM N� NO FINAL DA LISTA                                                  \n");
    printf("\t\t 16 - REMOVER ELEMENTO DA LISTA                                                        \n");
    printf("\t\t  0 - SAIR                                                                             \n");
    printf ( "\n\tEscolha uma op��o: " );
    scanf ( "%d%*c", &op );
    return op;
}
//}FIM de Menu de utilidades

int main(){
//{Declara�oes
    setlocale(LC_ALL, "portuguese");
    Lista lista = {0};
    Covid19 *aux = (Covid19*)malloc(sizeof(Covid19));
    bool sair = false;

//}FIM das Declara��es

    while (!sair){
        switch (menu()) {
            case 1: system("cls"); infoCovid19();                                       break;
            case 2: system("cls"); inserirInicio(&lista, pedirDados(aux) );             break;
            case 3: system("cls"); inserirDepois( lerPais(), &lista, pedirDados(aux));  break;
            case 4: system("cls"); inserirFinal(&lista, pedirDados(aux));               break;
            case 5: system("cls"); imprimirLista(&lista); getchar();                    break;
            case 6: system("cls"); imprimirNo( buscar(lerPais(), &lista)); getchar();   break;
            case 7: system("cls"); calcularTotal(&lista); getchar();                    break;
            case 8: system("cls"); calcularRecuperados(&lista); getchar();              break;
            case 9: system("cls"); calcularMortos(&lista); getchar();                   break;
            case 10: motraOrganizado (&lista);                                          break;
            case 11: system("cls"); calcularAtivos(&lista); getchar();                  break;
            case 12: salvarDados(&lista);                                               break;
            case 13: eliminaInicio(&lista);                                             break;
            case 15: eliminaFinal(&lista);                                              break;
            case 16: system("cls"); eliminarNo( lerPais(), &lista);                     break;
            case 0: destruirLista(&lista); sair = true;                                 break;
            default:printf("\t\t\t -> Op��o Invalida");getchar();                       break;
        }
    }
    free(aux);
    return 0;
}

//{Fun��es

//Fun��o que cria um n�
No* criarNo(Covid19 * c){
    //Criamos um n�
    No* novo = (No*)malloc(sizeof(No));

    //Comprovamos se temos n�
    if( novo == NULL ){
        //Se o n� n�o se reservou retornamos a NULL
        return NULL;
    }else{
        //Se o n� se criou lhe passamos os dados recebidos como par�metro
        strcpy(novo->covid19.pais, c->pais);
        novo->covid19.casos = c->casos;
        novo->covid19.recuperados = c->recuperados;
        novo->covid19.obitos = c->obitos;
        novo->covid19.casos_ativos = c->casos_ativos;
        novo->prox = NULL; //� importante apontar a NULL j� que esse n� pode chegar a ser o �ltimo
        return novo;
    }
}

//Fun��o que destrui um n� liberando sua memoria
void destruirNo(No *no){
    free(no);
}

//Fun��o que insere um novo n� no inicio da lista
void inserirInicio(Lista* lista, Covid19* c){
    //Criamos um novo n� com seus dados
    No *novo = criarNo(c);
    //Inserimos ao principio
    novo->prox = lista->inicio;
    lista->inicio = novo;
}

//Fun��o que insere um novo n� no final da lista
void inserirFinal(Lista* lista, Covid19* c){
    //Si n�o existe lista inserimos ao principio.
    if( lista->inicio == NULL ){
        inserirInicio(lista, c);
    }else{
        //Se a lista existe caimos aqui... ent�o inserimos no final.

        //Criamos um novo n�.
        No *novo = criarNo(c);

        //percorremos a lista at� o fim.
        No *ptr = lista->inicio;
        while(ptr->prox){
            ptr = ptr->prox;
        }
        //Inserimos o novo n� no final.
        ptr->prox = novo;
    }
}

//Fun��o que insere um n� posterior a outro indicado por par�metros
void inserirDepois(char *str, Lista* lista, Covid19* c){
    //Criamos um novo n�.
    No *novo = criarNo(c);

    //Si n�o temos n� ou string
    if(novo == NULL && str == NULL){
        //Se falhar um devemos liberar o outro(Todos dados reservados dinamicamente devem ser liberados)
        if(str != NULL) free(str);
        if(novo != NULL) free(novo);
        return;
    }else{
        //Si existe string e n�o existe lista, inserimos ao principio.
        if (lista->inicio == NULL) {
            inserirInicio(&(*lista), c);
        } else {
            //Si existir ambos(Lista e string.)... ent�o recorremos a lista at� o n� buscado(ou at� o fim si n�o existir o n�).
            No* ptr = lista->inicio;

            while ( (strcmp(ptr->covid19.pais, str) != 0) && ptr->prox) {
                ptr = ptr->prox;
            }
            printf("%s", ptr->covid19.pais);
            getchar();
            //inserimos o n�
            novo->prox = ptr->prox;
            ptr->prox = novo;

            free(str); //ao terminar a string liberamos
        }
    }
}

//Fun��o que busca um n� e o retorna
Covid19* buscar( char *str, Lista* lista){

    //Se n�o temos lista
    if( lista->inicio == NULL ){
        return NULL;
    }else{

        //Se temos lista caimos aqui e procedemos a buscar.
        No *ptr = lista->inicio;

        //Passamos por todos os n�s at� encontrar o n� buscado
           int posicao = 0;
        while ( (strcmp(ptr->covid19.pais, str) != 0) && ptr->prox) {
            ptr = ptr->prox;
            posicao++;
        }

        //Se encontrou retornamos o n� para ser imprimido
        if( strcmp(ptr->covid19.pais, str) == 0 ){
            return &ptr->covid19;
        }else{
            //Se n�o encontrou retornamos NULL para poder fazer comprova��es.
            return NULL;
        }
    }
}

//Fun��o que imprime um n� na tela
void imprimirNo(Covid19 *c){

    //Se n�o temos n� informamos e saimos, pois n�o h� nada que imprimir
    if (c == NULL) {
        system("cls");
        puts("N� n�o encontrado");
        return;
    } else {

        //Se o n� foi recebido corretamente no par�metros ent�o imprimimos
        printf (
            "Pa�s:....... %s\n"
            "Casos:...... %d\n"
            "Recuperados. %d\n"
            "Obtos:...... %d\n"
            "Ativos:..... %d\n",
            c->pais,
            c->casos,
            c->recuperados,
            c->obitos,
            c->casos_ativos
        );
        puts("**************************\n");
    }
}

//Elimina um n� ao principio da lista
void eliminaInicio(Lista* lista){
    //Si existe uma lista com pelomenos um n� ele ser� eliminado.
    if(lista->inicio != NULL){
        No *primeiroNo = lista->inicio;
        lista->inicio = lista->inicio->prox;
        //Eliminamos o n� inicial
        destruirNo(primeiroNo);
    }
}

//Elimina um n� no final da lista
void eliminaFinal(Lista* lista){

    //Se existe um ou mais n�s na lista.
    if(lista->inicio){

        //Se existe mais de um elemento na lista.
        if (lista->inicio->prox) {
            //percorremos a lista at� o penultimo n�.
            No* ptr = lista->inicio;
            while (ptr->prox->prox) {
                ptr = ptr->prox;
            }
            //Destruimos o ultimo
            No* no = ptr->prox;  //primeiro guardamos a posi��o do ultimo
            ptr->prox = NULL;   //fazemos o penultimo n� apontar a NULL(Penultimo passa a ser �ltimo)
            destruirNo (no);   //Destruimos o ultimo que guardamos(Anterior �ltimo)
        }else{

            //Se existe um �nico n� na lista destruimos esse n�
            No* ptr = lista->inicio; //primeiro guardamos a posi��o do ultimo
            lista->inicio = NULL;   //fazemos a lista apontar a NULL. A Lista fica vaazia j� que s� tinha um n�(Passo importante para reaproveitar a lista).
            destruirNo(ptr);       //Desttruimos o �nico n� que havia
        }
    }
}

//Libera a lista inteira
void destruirLista(Lista *lista){
    //Se n�o h� lista informamos que n�o h� nada que destruir.
    if(lista->inicio == NULL){
        puts("N�o h� dados para destruir");
        getchar();
        return;
    }else{

        //Se temos lista caimos aqui
        No *ptr = lista->inicio;

        //Se a lista conter um s� n� o destruimos.
        if(lista->inicio->prox == NULL){
            lista->inicio = ptr->prox;
            destruirNo(ptr);
        }else{
            //Se tiver mais de um n� destruiremos a lista
            int nElementos = 0; //Contador de n�s liberados
            while(lista->inicio != NULL){
                eliminaInicio(lista); //Eliminamos sempre o primeiro n�, fazendo o seguinte passar a ser o primeiro, j� que posteriormente ser� destruido na sequencia.
                nElementos++; //Contando os n�s liberados
            }
            //Informando quantos n�s foram liberados
            printf("Eliminado/s %d elementos\n", nElementos);
        }
    }
}

//Fun��o que procura um n� na lista e o elimina
void eliminarNo(char *str, Lista* lista){

    //Se n�o temos nenhum n� na lista
    if(lista->inicio == NULL){
        //informamos que n�o h� nada que liberar
        puts("N�o a dados na lista");
        system("pause");
        return;
    }else{

        //Se existe um ou mais n�s na lista
        No *ptr = lista->inicio;

        //Se � o primeiro n�
       if ( strcmp(lista->inicio->covid19.pais , str) == 0 ){
            ptr = lista->inicio;
            lista->inicio = lista->inicio->prox;
            destruirNo(ptr); //destruimos o primeiro n�
            free(ptr);

        }else{
            //Se � um n� posterior ao primeiro n� que queremos destruir.
            int posicao = 0; //Variavel que anotar� em que posi��o estava o n�

            //Percorremos a lista buscando um por um o n�
            No *anterior;
            while ( (strcmp (ptr->covid19.pais, str) != 0) && ptr->prox) {
                anterior = ptr;  //Sempre guardamos o n� atual como n� anterior para n�o perder a referen�a j� que posteriormente necesitamos estabelecer  o prox do n� anterior como NULL j� que passar� a ser o �ltimo.
                ptr = ptr->prox;
                posicao++;
            }
            posicao++;

            //Informamos qual n� ser� eliminado da lista
            system("cls");
            printf("Vai proceder a Elimina��o de %s da lista. Se encontra na posi��o %d da lista\n\nInfo:\n\n", ptr->covid19.pais, posicao);

            puts("N� anterior");
            imprimirNo(&anterior->covid19); //n� anterior
            puts("N� buscado");
            imprimirNo(&ptr->covid19);      //n� a eliminar

            if( ptr->prox != NULL ){
                puts("N� seguinte");
                imprimirNo(&ptr->prox->covid19);      //n� seguinte(Se unir� ao n� pr� anterior j� que o anterior � o buscado e ser� eliminado)
            }else{
                puts("N� seguinte\n(->NULL)\n\n");      //Se depois do n� buscado n�o h� mais n�s ent�o esse � o ultimo n� da lista, e como ser� eliminado, o anterior passar� a ser o ultimo, e seu pr�ximo passar� a ser NULL... neste caso s� avisamos.
            }
            system("pause");
            system("cls");

            anterior->prox = ptr->prox;     //Unindo o prox n� do buscado ao anterior
            free(ptr);                      //Eliminando n� buscado
        }
    }
}

//Fun��o que imprime um a um todos os n�s da lista
void imprimirLista(Lista *lista){
    if(lista->inicio == NULL){
        puts("Lista vazia\n");
        return;
    }else{
        No *ptr = lista->inicio;

        imprimirNo(&ptr->covid19);
        while(ptr->prox){
            ptr = ptr->prox;
            imprimirNo(&ptr->covid19);
        }
    }
}

Covid19* pedirDados(Covid19 *c){ //Terminar de implementar
    printf("Digite  o nome do Pa�s: "); scanf("%[^\n]%*c", c->pais);
    printf("Informe o n�mero de casos: "); scanf("%d*c", &c->casos);
    printf("Informe o n�mero de Recuperados: "); scanf("%d*c", &c->recuperados);
    printf("Informe o n�mero de obtos: "); scanf("%d*c", &c->obitos);
    c->casos_ativos = 0;
    return c;
}

//Fun��o que reserva uma string dinamicamente, l� um nome de um pa�s e retorna a string(Tem que ser liberada a string posteriormente com free)
char* lerPais(){
    //Reserva uma string din�micamente de um tamanho de cem chars
    char* str = malloc(sizeof(char)*100);

    //Se n�o se reservou retornamos falso para poder fazer comprova�oes posteriores
    if( str == NULL ){
        return NULL;
    }else{

        //Caso tenha sido reservado corretamente a string pedimos os dados e a retornamos.
        printf("Indique o Pa�s:");
        scanf("%[^\n]%*c", str);
        return str;
    }
}

//Fun��o que calcula o numero total de todos os casos em cada um dos n�s
void calcularTotal(Lista *lista){

    //Se n�o h� lista informamos.
    if(lista->inicio == NULL){
        puts("N�o ha dados para mostrar");
        return;
    }else{

        //Somamos todos os casos da lista
        No *ptr = lista->inicio;
        int somatoria = 0;
        somatoria += ptr->covid19.casos;
        while( ptr->prox ){
            ptr = ptr->prox;
            somatoria += ptr->covid19.casos;
        }

        //Informamos
        printf("O n�mero de casos � de %d em todo o mundo.\n", somatoria);
    }
}

//Fun��o que calcula o numero total de todos os recuperados em cada um dos n�s
void calcularRecuperados(Lista *lista){

    //Se n�o h� lista informamos.
    if(lista->inicio == NULL){
        puts("N�o ha dados para mostrar");
        return;
    }else{

        //Somamos todos os recuerados da lista
        No *ptr = lista->inicio;
        int somatoria = 0;
        somatoria += ptr->covid19.recuperados;
        while( ptr->prox ){
            ptr = ptr->prox;
            somatoria += ptr->covid19.recuperados;
        }
        //Informamos
        printf("O n�mero de recuperados � de %d em todo o mundo.\n", somatoria);
    }
}

//Fun��o que calcula o numero total de todos os falecidos a causa do coronavirus em cada um dos paises(n�s)
void calcularMortos(Lista *lista){

    //Se n�o h� lista informamos.
    if(lista->inicio == NULL){
        puts("N�o ha dados para mostrar");
        return;
    }else{
        //Somamos todos os falecidos da lista
        No *ptr = lista->inicio;
        int somatoria = 0;
        somatoria += ptr->covid19.obitos;
        while( ptr->prox ){
            ptr = ptr->prox;
            somatoria += ptr->covid19.obitos;
        }
        //Informamos
        printf("O n�mero de mortos em todo o mundo � de %d.\n", somatoria);
    }
}

//Calcula o numero de ativos de cada um dos n�s(usando a fun��o processarAtivos) e o envia para o arquivo "CasosAtivos.txt"
void calcularAtivos(Lista *lista){
    //Se a lista esta vazia n�o h� nada que calcular
    if(lista->inicio == NULL){
        puts("Lista vazia\n");
        return;
    }else{
        //Tentamos criar um arquivo em modo escritura
        FILE *file = fopen("CasosAtivos.txt", "w");
        if(file == NULL){
            perror("Erro ao abrir arquivo CasosAtivos.txt:");
            system("pause");
            return;
        }else{
            //Se o arquivo se criou e temos uma lista, calculamos os ativos de cada n� da lista e enviamos para o arquivo.
            No* ptr = lista->inicio;

            processarAtivos(lista);//preenchendo o campo casos_ativos de cada n�

            //Enviando para o arquivo a lista
            while (ptr->prox) {
                fprintf (file, "%s %d\n", ptr->covid19.pais, ptr->covid19.casos_ativos);
                ptr = ptr->prox;
            }
            fprintf (file, "%s %d\n", ptr->covid19.pais, ptr->covid19.casos_ativos);
            fclose(file);
        }
    }
}

//Fun��o que faz o processo de calculo do numero de casos ativos de todos os n�s da lista.
void processarAtivos(Lista *lista){
    if(lista->inicio == NULL){
        puts("Lista vazia\n");
        return;
    }else{

        No* ptr = lista->inicio;
        int calculo = 0;

        //Para cada um dos n�s da lista fazemos o calculo de casos ativos e salvamos na variavel membro chamada "casos_ativos"
        while (ptr->prox) {
            calculo = ptr->covid19.casos - (ptr->covid19.obitos + ptr->covid19.recuperados);
            ptr->covid19.casos_ativos = calculo;

            ptr = ptr->prox;
        }
        calculo = ptr->covid19.casos - (ptr->covid19.obitos + ptr->covid19.recuperados);
        ptr->covid19.casos_ativos = calculo;
    }
}


void salvarDados(Lista *lista){
        if(lista->inicio == NULL){
        puts("Lista vazia\n");
        return;
    }else{
        FILE *file = fopen("Elementos.txt", "w");
        if(file == NULL){
            perror("Erro ao abrir arquivo CasosAtivos.txt:");
            system("pause");
            return;
        }else{
            No* ptr = lista->inicio;

            while (ptr->prox) {
                fprintf (
                    file,
                    "Pais:....... %s\n"
                    "Casos:...... %d\n"
                    "Recuperados. %d\n"
                    "Obtos:...... %d\n"
                    "Ativos:..... %d\n"
                    "**************************\n",
                    ptr->covid19.pais,
                    ptr->covid19.casos,
                    ptr->covid19.recuperados,
                    ptr->covid19.obitos,
                    ptr->covid19.casos_ativos
                );
                ptr = ptr->prox;
            }
            fprintf (
                file,
                "Pais:....... %s\n"
                "Casos:...... %d\n"
                "Recuperados. %d\n"
                "Obtos:...... %d\n"
                "Ativos:..... %d\n"
                "**************************\n",
                ptr->covid19.pais,
                ptr->covid19.casos,
                ptr->covid19.recuperados,
                ptr->covid19.obitos,
                ptr->covid19.casos_ativos
            );
            fclose(file);
        }
    }
}

//Fun��o que cria uma c�pia da lista original, de forma organizada de maior a menor e mostra ela pela tela.
void motraOrganizado(Lista* lista){ //Modo buscar

    //Se n�o temos lista retornamos
    if( lista->inicio == NULL ){
        return;
    }else{
        //Se h� lista caimos aqui.

        /*  A estrategia � criar uma c�pia da lista original de forma organizada, mostrar e destruir a
            lista. Permanecendo com a original intacta.
        */

        No *ptr = lista->inicio;

        //Copiamos a lista em outra chamada org(organizada)
        Lista org = {0};
        while( ptr->prox ){
            inserirFinal(&org, &ptr->covid19);
            ptr = ptr->prox;
        }
        inserirFinal(&org, &ptr->covid19);

        //Calculamos o numero de ativos na lista org
        calcularAtivos(&org);

        //organizamosa a lista org
        No *a = org.inicio;
        No *b = org.inicio;

        /*  Comparamos o numero de casos_ativos do n� atual, com todos os outros casos_ativos dos
            outros n�s da lista. Se o numero de casos_ativos do n� atual � maior que, o n� que foi
            comparado, invertemos as posi�oes e o que tenha menos casos ativos fica primeiro.
            Repetimos tudo isso para cada um dos n�s

        */
        while( a->prox ){
            while( b->prox ){
                if( a->covid19.casos_ativos > b->covid19.casos_ativos ){
                    Covid19 aux;
                    memcpy( &aux, &a->covid19, sizeof(Covid19));
                    memcpy(&a->covid19, &b->covid19, sizeof(Covid19));
                    memcpy(&b->covid19, &aux, sizeof(Covid19));
                }
                b = b->prox;
            }
            if( a->covid19.casos_ativos > b->covid19.casos_ativos ){
                Covid19 aux;
                memcpy( &aux, &a->covid19, sizeof(Covid19));
                memcpy(&a->covid19, &b->covid19, sizeof(Covid19));
                memcpy(&b->covid19, &aux, sizeof(Covid19));
            }
            a = a->prox;
            b = a->prox;
        }

        //imprimimos
        system ("cls");
        imprimirLista(&org);

        //Destruimos a copia da lista(org)
        destruirLista(&org);

        system ("pause");
        system("cls");
    }
}

//}FIM Fun��es



