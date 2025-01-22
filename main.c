/*

  * Programa: LISTAS (CORONAVÍRUS(COVID-19) NO MUNDO)
  * Data de criação: 06/06/2020
  * Participante: Andreia Gonçalves Semedo
  * Finalizado em: 03/07/2020

*/

//{Cabeçalho
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

//}FIM Cabeçalho

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
    printf("\t\t\tCORONAVÍRUS(COVID-19) NO MUNDO\n\n");
    printf(
    "\n  A Organização Mundial da Saúde (OMS) declarou,em 30 de janeiro de 2020, que o surto da\n"
    " doença causada pelo novo coronavírus (COVID-19) constitui uma Emergência de Saúde Pública de\n"
    "  Importância Internacional – o mais alto nível de alerta da Organização, conforme previsto no\n"
    " Regulamento Sanitário Internacional."
    "\n\n  Em 11 de março de 2020, a COVID-19 foi caracterizada pela OMS como uma pandemia."
    );
    getchar();
}

//{Menu de utilidades
int menu() {
    int op=0;
    system("cls");
    system("COLOR 0F");
    printf ("\n\n\tUNICV\n");
    printf("\t\t\t\t\tCORONAVÍRUS(COVID-19) NO MUNDO \n\n");
    printf("\t\t-------------------------------------------------------------------------------------\n\n");
    printf("\t\t  1 - IMFORMÇÃO SOBRE CORONAVÍRUS(COVID-19)                                            \n");
    printf("\t\t  2 - INSERIR NÓ NO INICIO DA LISTA                                                    \n");
    printf("\t\t  3 - INSERIR NÓ NO MEIO DA LISTA                                                      \n");
    printf("\t\t  4 - INSERIR NÓ NO FINAL DA LISTA                                                     \n");
    printf("\t\t  5 - IMPRIMIR A LISTA                                                                 \n");
    printf("\t\t  6 - PESQUISAR ELEMENTO ATRAVÉZ DO NOME DO PAÍS                                       \n");
    printf("\t\t  7 - CALCULAR TOTAL DE CASOS                                                          \n");
    printf("\t\t  8 - CALCULAR TOTAL DE MORTOS                                                         \n");
    printf("\t\t  9 - CALCULAR TOTAL DE RECUPERADOS                                                    \n");
    printf("\t\t 10 - IMPRIMIR POR ORDEM ASCENDENTE(COM MAIS CASOS DE COVID-19)                        \n");
    printf("\t\t 11 - CALCULAR CASOS ATIVOS DE CADA PAÍS E ENVIA-LOS PARA O FECHEIRO (CasosAtivos.txt) \n");
    printf("\t\t 12 - ENVIAR TODOS OS NÓS PARA O FECHEIRO(elementos.txt)                               \n");
    printf("\t\t 13 - REMOVER NÓ NO INICIO  DA LISTA                                                   \n");
    printf("\t\t 14 - REMOVER NÓ NO MEIO DA LISTA                                                      \n");
    printf("\t\t 15 - REMOVER UM NÓ NO FINAL DA LISTA                                                  \n");
    printf("\t\t 16 - REMOVER ELEMENTO DA LISTA                                                        \n");
    printf("\t\t  0 - SAIR                                                                             \n");
    printf ( "\n\tEscolha uma opção: " );
    scanf ( "%d%*c", &op );
    return op;
}
//}FIM de Menu de utilidades

int main(){
//{Declaraçoes
    setlocale(LC_ALL, "portuguese");
    Lista lista = {0};
    Covid19 *aux = (Covid19*)malloc(sizeof(Covid19));
    bool sair = false;

//}FIM das Declaraçães

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
            default:printf("\t\t\t -> Opção Invalida");getchar();                       break;
        }
    }
    free(aux);
    return 0;
}

//{Funções

//Função que cria um nó
No* criarNo(Covid19 * c){
    //Criamos um nó
    No* novo = (No*)malloc(sizeof(No));

    //Comprovamos se temos nó
    if( novo == NULL ){
        //Se o nó não se reservou retornamos a NULL
        return NULL;
    }else{
        //Se o nó se criou lhe passamos os dados recebidos como parâmetro
        strcpy(novo->covid19.pais, c->pais);
        novo->covid19.casos = c->casos;
        novo->covid19.recuperados = c->recuperados;
        novo->covid19.obitos = c->obitos;
        novo->covid19.casos_ativos = c->casos_ativos;
        novo->prox = NULL; //É importante apontar a NULL já que esse nó pode chegar a ser o último
        return novo;
    }
}

//Função que destrui um nó liberando sua memoria
void destruirNo(No *no){
    free(no);
}

//Função que insere um novo nó no inicio da lista
void inserirInicio(Lista* lista, Covid19* c){
    //Criamos um novo nó com seus dados
    No *novo = criarNo(c);
    //Inserimos ao principio
    novo->prox = lista->inicio;
    lista->inicio = novo;
}

//Função que insere um novo nó no final da lista
void inserirFinal(Lista* lista, Covid19* c){
    //Si não existe lista inserimos ao principio.
    if( lista->inicio == NULL ){
        inserirInicio(lista, c);
    }else{
        //Se a lista existe caimos aqui... então inserimos no final.

        //Criamos um novo nó.
        No *novo = criarNo(c);

        //percorremos a lista até o fim.
        No *ptr = lista->inicio;
        while(ptr->prox){
            ptr = ptr->prox;
        }
        //Inserimos o novo nó no final.
        ptr->prox = novo;
    }
}

//Função que insere um nó posterior a outro indicado por parâmetros
void inserirDepois(char *str, Lista* lista, Covid19* c){
    //Criamos um novo nó.
    No *novo = criarNo(c);

    //Si não temos nó ou string
    if(novo == NULL && str == NULL){
        //Se falhar um devemos liberar o outro(Todos dados reservados dinamicamente devem ser liberados)
        if(str != NULL) free(str);
        if(novo != NULL) free(novo);
        return;
    }else{
        //Si existe string e não existe lista, inserimos ao principio.
        if (lista->inicio == NULL) {
            inserirInicio(&(*lista), c);
        } else {
            //Si existir ambos(Lista e string.)... então recorremos a lista até o nó buscado(ou até o fim si não existir o nó).
            No* ptr = lista->inicio;

            while ( (strcmp(ptr->covid19.pais, str) != 0) && ptr->prox) {
                ptr = ptr->prox;
            }
            printf("%s", ptr->covid19.pais);
            getchar();
            //inserimos o nó
            novo->prox = ptr->prox;
            ptr->prox = novo;

            free(str); //ao terminar a string liberamos
        }
    }
}

//Função que busca um nó e o retorna
Covid19* buscar( char *str, Lista* lista){

    //Se não temos lista
    if( lista->inicio == NULL ){
        return NULL;
    }else{

        //Se temos lista caimos aqui e procedemos a buscar.
        No *ptr = lista->inicio;

        //Passamos por todos os nós até encontrar o nó buscado
           int posicao = 0;
        while ( (strcmp(ptr->covid19.pais, str) != 0) && ptr->prox) {
            ptr = ptr->prox;
            posicao++;
        }

        //Se encontrou retornamos o nó para ser imprimido
        if( strcmp(ptr->covid19.pais, str) == 0 ){
            return &ptr->covid19;
        }else{
            //Se não encontrou retornamos NULL para poder fazer comprovações.
            return NULL;
        }
    }
}

//Função que imprime um nó na tela
void imprimirNo(Covid19 *c){

    //Se não temos nó informamos e saimos, pois não há nada que imprimir
    if (c == NULL) {
        system("cls");
        puts("Nó não encontrado");
        return;
    } else {

        //Se o nó foi recebido corretamente no parâmetros então imprimimos
        printf (
            "País:....... %s\n"
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

//Elimina um nó ao principio da lista
void eliminaInicio(Lista* lista){
    //Si existe uma lista com pelomenos um nó ele será eliminado.
    if(lista->inicio != NULL){
        No *primeiroNo = lista->inicio;
        lista->inicio = lista->inicio->prox;
        //Eliminamos o nó inicial
        destruirNo(primeiroNo);
    }
}

//Elimina um nó no final da lista
void eliminaFinal(Lista* lista){

    //Se existe um ou mais nós na lista.
    if(lista->inicio){

        //Se existe mais de um elemento na lista.
        if (lista->inicio->prox) {
            //percorremos a lista até o penultimo nó.
            No* ptr = lista->inicio;
            while (ptr->prox->prox) {
                ptr = ptr->prox;
            }
            //Destruimos o ultimo
            No* no = ptr->prox;  //primeiro guardamos a posição do ultimo
            ptr->prox = NULL;   //fazemos o penultimo nó apontar a NULL(Penultimo passa a ser último)
            destruirNo (no);   //Destruimos o ultimo que guardamos(Anterior último)
        }else{

            //Se existe um único nó na lista destruimos esse nó
            No* ptr = lista->inicio; //primeiro guardamos a posição do ultimo
            lista->inicio = NULL;   //fazemos a lista apontar a NULL. A Lista fica vaazia já que só tinha um nó(Passo importante para reaproveitar a lista).
            destruirNo(ptr);       //Desttruimos o único nó que havia
        }
    }
}

//Libera a lista inteira
void destruirLista(Lista *lista){
    //Se não há lista informamos que não há nada que destruir.
    if(lista->inicio == NULL){
        puts("Não há dados para destruir");
        getchar();
        return;
    }else{

        //Se temos lista caimos aqui
        No *ptr = lista->inicio;

        //Se a lista conter um só nó o destruimos.
        if(lista->inicio->prox == NULL){
            lista->inicio = ptr->prox;
            destruirNo(ptr);
        }else{
            //Se tiver mais de um nó destruiremos a lista
            int nElementos = 0; //Contador de nós liberados
            while(lista->inicio != NULL){
                eliminaInicio(lista); //Eliminamos sempre o primeiro nó, fazendo o seguinte passar a ser o primeiro, já que posteriormente será destruido na sequencia.
                nElementos++; //Contando os nós liberados
            }
            //Informando quantos nós foram liberados
            printf("Eliminado/s %d elementos\n", nElementos);
        }
    }
}

//Função que procura um nó na lista e o elimina
void eliminarNo(char *str, Lista* lista){

    //Se não temos nenhum nó na lista
    if(lista->inicio == NULL){
        //informamos que não há nada que liberar
        puts("Não a dados na lista");
        system("pause");
        return;
    }else{

        //Se existe um ou mais nós na lista
        No *ptr = lista->inicio;

        //Se é o primeiro nó
       if ( strcmp(lista->inicio->covid19.pais , str) == 0 ){
            ptr = lista->inicio;
            lista->inicio = lista->inicio->prox;
            destruirNo(ptr); //destruimos o primeiro nó
            free(ptr);

        }else{
            //Se é um nó posterior ao primeiro nó que queremos destruir.
            int posicao = 0; //Variavel que anotará em que posição estava o nó

            //Percorremos a lista buscando um por um o nó
            No *anterior;
            while ( (strcmp (ptr->covid19.pais, str) != 0) && ptr->prox) {
                anterior = ptr;  //Sempre guardamos o nó atual como nó anterior para não perder a referença já que posteriormente necesitamos estabelecer  o prox do nó anterior como NULL já que passará a ser o último.
                ptr = ptr->prox;
                posicao++;
            }
            posicao++;

            //Informamos qual nó será eliminado da lista
            system("cls");
            printf("Vai proceder a Eliminação de %s da lista. Se encontra na posição %d da lista\n\nInfo:\n\n", ptr->covid19.pais, posicao);

            puts("Nó anterior");
            imprimirNo(&anterior->covid19); //nó anterior
            puts("Nó buscado");
            imprimirNo(&ptr->covid19);      //nó a eliminar

            if( ptr->prox != NULL ){
                puts("Nó seguinte");
                imprimirNo(&ptr->prox->covid19);      //nó seguinte(Se unirá ao nó pré anterior já que o anterior é o buscado e será eliminado)
            }else{
                puts("Nó seguinte\n(->NULL)\n\n");      //Se depois do nó buscado não há mais nós então esse é o ultimo nó da lista, e como será eliminado, o anterior passará a ser o ultimo, e seu próximo passará a ser NULL... neste caso só avisamos.
            }
            system("pause");
            system("cls");

            anterior->prox = ptr->prox;     //Unindo o prox nó do buscado ao anterior
            free(ptr);                      //Eliminando nó buscado
        }
    }
}

//Função que imprime um a um todos os nós da lista
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
    printf("Digite  o nome do País: "); scanf("%[^\n]%*c", c->pais);
    printf("Informe o número de casos: "); scanf("%d*c", &c->casos);
    printf("Informe o número de Recuperados: "); scanf("%d*c", &c->recuperados);
    printf("Informe o número de obtos: "); scanf("%d*c", &c->obitos);
    c->casos_ativos = 0;
    return c;
}

//Função que reserva uma string dinamicamente, lê um nome de um país e retorna a string(Tem que ser liberada a string posteriormente com free)
char* lerPais(){
    //Reserva uma string dinâmicamente de um tamanho de cem chars
    char* str = malloc(sizeof(char)*100);

    //Se não se reservou retornamos falso para poder fazer comprovaçoes posteriores
    if( str == NULL ){
        return NULL;
    }else{

        //Caso tenha sido reservado corretamente a string pedimos os dados e a retornamos.
        printf("Indique o País:");
        scanf("%[^\n]%*c", str);
        return str;
    }
}

//Função que calcula o numero total de todos os casos em cada um dos nós
void calcularTotal(Lista *lista){

    //Se não há lista informamos.
    if(lista->inicio == NULL){
        puts("Não ha dados para mostrar");
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
        printf("O número de casos é de %d em todo o mundo.\n", somatoria);
    }
}

//Função que calcula o numero total de todos os recuperados em cada um dos nós
void calcularRecuperados(Lista *lista){

    //Se não há lista informamos.
    if(lista->inicio == NULL){
        puts("Não ha dados para mostrar");
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
        printf("O número de recuperados é de %d em todo o mundo.\n", somatoria);
    }
}

//Função que calcula o numero total de todos os falecidos a causa do coronavirus em cada um dos paises(nós)
void calcularMortos(Lista *lista){

    //Se não há lista informamos.
    if(lista->inicio == NULL){
        puts("Não ha dados para mostrar");
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
        printf("O número de mortos em todo o mundo é de %d.\n", somatoria);
    }
}

//Calcula o numero de ativos de cada um dos nós(usando a função processarAtivos) e o envia para o arquivo "CasosAtivos.txt"
void calcularAtivos(Lista *lista){
    //Se a lista esta vazia não há nada que calcular
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
            //Se o arquivo se criou e temos uma lista, calculamos os ativos de cada nó da lista e enviamos para o arquivo.
            No* ptr = lista->inicio;

            processarAtivos(lista);//preenchendo o campo casos_ativos de cada nó

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

//Função que faz o processo de calculo do numero de casos ativos de todos os nós da lista.
void processarAtivos(Lista *lista){
    if(lista->inicio == NULL){
        puts("Lista vazia\n");
        return;
    }else{

        No* ptr = lista->inicio;
        int calculo = 0;

        //Para cada um dos nós da lista fazemos o calculo de casos ativos e salvamos na variavel membro chamada "casos_ativos"
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

//Função que cria uma cópia da lista original, de forma organizada de maior a menor e mostra ela pela tela.
void motraOrganizado(Lista* lista){ //Modo buscar

    //Se não temos lista retornamos
    if( lista->inicio == NULL ){
        return;
    }else{
        //Se há lista caimos aqui.

        /*  A estrategia é criar uma cópia da lista original de forma organizada, mostrar e destruir a
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

        /*  Comparamos o numero de casos_ativos do nó atual, com todos os outros casos_ativos dos
            outros nós da lista. Se o numero de casos_ativos do nó atual é maior que, o nó que foi
            comparado, invertemos as posiçoes e o que tenha menos casos ativos fica primeiro.
            Repetimos tudo isso para cada um dos nós

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

//}FIM Funções



