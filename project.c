/* iaed24 - ist1110274 - project */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAXPARQUES 20
#define TAMANHODATA 11
#define TAMANHOHORA 6
#define TAMANHOMATRIULA 9

//acho que a lista de parques pode ser simplesmente um vetor composto por struct do genero parque

typedef float TipoPreco;
typedef int TipoCapacidade;

typedef struct Precos {
    TipoPreco x;
    TipoPreco y;
    TipoPreco z;
} ConjuntoDePrecos;

typedef struct Parque {
    //informacao util
    char *nome;
    TipoCapacidade capacidade; 
    TipoCapacidade lugareslivres; 
    TipoPreco faturacao;
    struct Precos preco;

    //ponteiro para o proximo
    struct Parque *next;

} TipoParque;

typedef struct DataEHora {
    char data[TAMANHODATA];
    char hora[TAMANHOHORA];
} TipoData;

struct EntradasESaidas {
    char *nomeDoParque;
    struct DataEHora dataEHora;
    struct EntradasESaidas *next;
};

typedef struct Carro {
    //infromacao util
    char matricula[TAMANHOMATRIULA];
    struct EntradasESaidas *historico;

    //ponteiro para o proximo
    struct Carro *next;
} TipoCarro;

//a nossa base de dados sera do genero lista que armazena os parques e cada parque uma estrutura de dados com nome, capacidade, lugares livre, precos
TipoParque *todosOsParques;
TipoCarro *todosOsCarros;

//temos de ter sempre armazenada a ultima data usada
TipoData ultimaData;

//funcoes de 'p'
int invalidCapacity (TipoCapacidade capacidade);
int invalidCost (ConjuntoDePrecos preco);
int tooManyParks (TipoParque *todosOsParque);

void criaParque (char *nome, int capacidade, TipoPreco valorMinutos, TipoPreco valorHora, TipoPreco valorDiario);
void informacaoParques ();

//funcoes de 'e'
int noSuchParking (char *nomeDoParque);
int parkingIsFull (char *nomeDoParque);
int parValido (char primeiro, char segundo);
int invalidLicensePlate (char matricula[]);
int invalidDate (TipoData novaData);

void entraVeiculo (char *nomeDoParque, char matricula[], char data[], char hora[]);

//funcoes de 's'
int contasDeData (TipoData dataInicial, TipoData dataFinal);
TipoPreco faturacao(struct Precos precos, int totalMin);

void saiVeiculo (char *nomeDoParque, char matricula[], char data[], char hora[]);

//funcoes de 'v'

//funcoes de 'f'

//funcoes de 'r'
void removeParque (char *nomeParaRemover);

//funcoes auxiliares de main()
char* lerNome (char letra);

//-----------------------------------------------------------------------------------------------------------------------------------------------------------

int invalidCapacity (TipoCapacidade capacidade) {
    //capacidade menor ou igual a 0 e invalida    
    return (capacidade <= 0);
}

int invalidCost (ConjuntoDePrecos preco) {
    //precos negativos, ou entao que nao obdecam a x < y < z serao invalidos
    return (preco.x <= 0.0 || preco.y <= 0.0 || preco.z <= 0.0 || preco.x >= preco.y || preco.y >= preco.z);
}

int tooManyParks (TipoParque *todosOsParque) {
    TipoParque *atual = todosOsParque;
    int i = 0;

    //contar o numero de parques
    while (atual != NULL) {
        i++;
        atual = atual->next;
    }
    return (i >= MAXPARQUES);
}

void criaParque (char *nome, int capacidade, TipoPreco valorMinutos, TipoPreco valorHora, TipoPreco valorDiario) {
    ConjuntoDePrecos preco;
    preco.x = valorMinutos;
    preco.y = valorHora;
    preco.z = valorDiario;

    //se este parque passar todas as verificacoes entao sera adicionado a lista final
    if (todosOsParques != NULL) {
        if (!strcmp(todosOsParques->nome, nome)) {
            printf("%s: parking already exists.\n", nome);
        }
        TipoParque *last = todosOsParques;
        while (last->next != NULL) {
            if (!strcmp(last->nome, nome)) {
                printf("%s: parking already exists.\n", nome);

                return;
            }
            last = last->next;
        }
    } if (invalidCapacity(capacidade)) {
        printf("%d: invalid capacity.\n", capacidade);
        return;
    } else if (invalidCost(preco)) {
        printf("invalid cost.\n");
        return;
    } else if (tooManyParks(todosOsParques)) {
        printf("too many parks.\n");
        return;
    }

    TipoParque *novoParque = (TipoParque*) malloc (sizeof(TipoParque));
    
    novoParque->nome = strdup(nome);
    novoParque->capacidade = capacidade;
    novoParque->lugareslivres = capacidade;
    novoParque->faturacao = 0;
    novoParque->next = NULL;

    if (todosOsParques == NULL) {
        todosOsParques = (TipoParque*)malloc(sizeof(TipoParque*)); // Alocar memória para a lista de parques
        todosOsParques = novoParque;

    } else {
        TipoParque *last = todosOsParques;
        while (last->next != NULL) {
            last = last->next;
        }

        last->next = novoParque;
    }   
}

void informacaoParques () {
 
    if (todosOsParques != NULL) {
        TipoParque *atual = todosOsParques;

        while (atual != NULL) {
            printf("%s %d %d\n", atual->nome, atual->capacidade, atual->lugareslivres);
            atual = atual->next;
        }
    }
}


//----------------------------------------------------------------------------------------------------------------------------------------------------------
int noSuchParking (char *nomeDoParque) {
    TipoParque *atual = todosOsParques;

    while (atual != NULL) {
        if (!strcmp(atual->nome, nomeDoParque))
            return 0;
        atual = atual->next;
    }
    
    return 1;
}

int parkingIsFull (char *nomeDoParque) {
    TipoParque *atual = todosOsParques;
    //para chegar ao parque
    while (atual != NULL && strcmp(atual->nome, nomeDoParque)) {
        atual = atual->next;
    }

    return (atual->lugareslivres == 0);
}

int parValido (char primeiro, char segundo) {
    if (isdigit(primeiro) && isdigit(segundo)) {
        return 1;
    } else if (isupper(primeiro) && isupper(segundo)) {
        return 1;
    } else  
        return 0;
}

int invalidLicensePlate (char matricula[]) {
    //matricula e algo do genero AA-00-AA, comprimento = 8
    if (strlen(matricula) != 8)
        return 1;

    if (matricula[2] != '-' || matricula[5] != '-')
        return 1;    

    for (int i = 0; i < TAMANHOMATRIULA; i += 3) {
        if (!parValido(matricula[i], matricula[i + 1]))
            return 1;
        
    }    
    //se passar todos os testes
    return ((isupper(matricula[0]) && isupper(matricula[3]) && isupper(matricula[6])) || (isdigit(matricula[0] ) && isdigit(matricula[3]) && isdigit(matricula[6])));
}

int invalidDate (TipoData novaData) {
    //data dd-mm-aaaa   hora hh:mm
    //     0123456789        01234

    int ordemData[8] = {6, 7, 8, 9, 3, 4, 0, 1};
    int ordemHora[4] = {0, 1, 3, 4};
    int j, dia, mes;
    // hora, min;

    dia = (novaData.data[0] - '0')*10 + novaData.data[1] - '0';
    mes = (novaData.data[3] - '0')*10 + novaData.data[4] - '0';
    //hora = (novaData.hora[0] - '0')*10 + novaData.hora[1] - '0';
    //min = (novaData.hora[3] - '0')*10 + novaData.hora[4] - '0';

    if (mes < 1 || mes > 12 || dia < 1) { //mes entre 1 e 12, dia maior que 1, hora ate 24,  minutos ate 60 
        return 1;
    } if ((mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 ||mes == 10 ||mes == 12) && dia > 31) { //meses de 31 dias
        return 1;
    } if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && dia > 30) { //meses de 30 dias
        return 1;
    } if (mes == 2 && dia > 28) { //fevereiro 28 dias
        return 1;
    }

    for (int i = 0; i < 8; i++) {
        j = ordemData[i];
        if (novaData.data[j] > ultimaData.data[j]) {
            return 0;
        } if (novaData.data[j] < ultimaData.data[j]) {
            return 1;
        }
    }    

    for (int i = 0; i < 4; i++) {
        j = ordemHora[i];
        if (novaData.hora[j] > ultimaData.hora[j]) {
            return 0;
        } if (novaData.hora[j] < ultimaData.hora[j]) {
            return 1;
        }
    }    

    return 0;
}

void entraVeiculo (char *nomeDoParque, char matricula[], char data[], char hora[]) {
    TipoData novaData;
    strcpy(novaData.data, data);
    strcpy(novaData.hora, hora);

    if (noSuchParking(nomeDoParque)) {
        printf("%s: no such parking.\n", nomeDoParque);
    } else if (invalidLicensePlate(matricula)) {
        printf("%s: invalid licence plate.\n", matricula);
    } else if (invalidDate(novaData)) {
        printf("invalid date.\n");
    } else if (parkingIsFull(nomeDoParque)) {
        printf("%s: parking is full.\n", nomeDoParque);
    } else {
        //se for o primeiro carro a entrar
        if (todosOsCarros == NULL) {
            todosOsCarros = (TipoCarro*) malloc (sizeof(TipoCarro));
            struct EntradasESaidas *historico = (struct EntradasESaidas*) malloc (sizeof(struct EntradasESaidas)); 
            strcpy(todosOsCarros->matricula, matricula);

            historico->nomeDoParque = strdup(nomeDoParque);
            historico->dataEHora = novaData;
            historico->next = NULL;
            todosOsCarros->historico = historico;
            todosOsCarros->next = NULL;

        } else {
            TipoCarro *atual = todosOsCarros;
            while (atual->next != NULL && strcmp(atual->matricula, matricula)) {
                atual = atual->next;
            }

            //se for a primeira entrada do veiculo
            if (strcmp(atual->matricula, matricula)) {
                TipoCarro *esteVehiculo = (TipoCarro*) malloc (sizeof(TipoCarro));
                struct EntradasESaidas *historico = (struct EntradasESaidas*) malloc (sizeof(struct EntradasESaidas)); 
                esteVehiculo->historico = (struct EntradasESaidas*) malloc (sizeof(struct EntradasESaidas));

                historico->nomeDoParque = strdup(nomeDoParque);
                historico->dataEHora = novaData;
                historico->next = NULL;
                strcpy(esteVehiculo->matricula, matricula);
                esteVehiculo->historico = historico;
                esteVehiculo->next = NULL;
                atual->next = esteVehiculo;

            //se ja estiver na lista de veiculos
            } else {
                struct EntradasESaidas *pointer = atual->historico;
                int count = 0;
                //andar ate a ultima entrada/saida
                while (pointer != NULL) {
                    count += 1;
                    pointer = pointer->next;
                }
                //se o conjunto de entradas e saidas do tipo {entrada, saida, entrada, saida}
                // tiver um comprimento impar entao o veiculo ja esta num parque
                if ((count % 2) != 0) {
                    printf("%s: invalid vehicle entry.\n", matricula);
                    return;
                }

                pointer->nomeDoParque = strdup(nomeDoParque);
                pointer->dataEHora = novaData;
                pointer->next = NULL;
            }
        }

        TipoParque *nesteParque = todosOsParques;
        while (strcmp(nesteParque->nome, nomeDoParque)) {
            nesteParque = nesteParque->next;
        }
        nesteParque->lugareslivres -= 1;
        printf("%s %d\n", nesteParque->nome, nesteParque->lugareslivres);
        ultimaData = novaData;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------
int contasDeData (TipoData dataInicial, TipoData dataFinal) {
    int difAno, difMes, difDia, difHora, difMin;
    int totalMin;

    //calcular o total de minutos entre entrada e saida
    difAno = dataFinal.data[9]-dataInicial.data[9] + (dataFinal.data[8]-dataInicial.data[8])*10 + (dataFinal.data[7]-dataInicial.data[7])*100 + (dataFinal.data[6]-dataInicial.data[6])*1000;
    difMes = dataFinal.data[4]-dataInicial.data[4] + (dataFinal.data[3]-dataInicial.data[3])*10;
    difDia = dataFinal.data[1]-dataInicial.data[1] + (dataFinal.data[0]-dataInicial.data[0])*10;
    difHora = dataFinal.hora[1]-dataInicial.hora[1] + (dataFinal.hora[1]-dataInicial.hora[1])*10;
    difMin = dataFinal.hora[4]-dataInicial.hora[4] + (dataFinal.hora[3]-dataInicial.hora[3])*10;

    totalMin = difAno + difMes + difDia + difHora + difMin;

    return totalMin;
}

TipoPreco faturacao (struct Precos precos, int totalMin) {
    TipoPreco faturacao = 0, faturadoRestante;
    int dias, min15;
    
    dias = totalMin % (24*60);
    faturacao += precos.z * dias; //somar os dias completos

    min15 = (totalMin /(24*60)) /15;

    if (min15 < 5) {
        faturadoRestante = precos.x * min15;
    } else {
        faturadoRestante = precos.x * 4 + precos.y * (min15 - 4);
    }

    if (faturadoRestante > precos.z) {
        faturacao += precos.z;
    } else {
        faturacao += faturadoRestante;
    }

    return faturacao;
}

void saiVeiculo (char *nomeDoParque, char matricula[], char data[], char hora[]) {
    TipoData novaData;
    strcpy(novaData.data, data);
    strcpy(novaData.hora, hora);

    if (noSuchParking(nomeDoParque)) {
        printf("%s: no such parking.\n", nomeDoParque);
    } else if (invalidLicensePlate(matricula)) {
        printf("%s: invalid licence plate.\n", matricula);
    } else if (invalidDate(novaData)) {
        printf("invalid date.\n");
    } else {
        if (todosOsCarros == NULL) {
            printf("%s: invalid vehicle exit.", matricula);
        } else {
            TipoCarro *atual = todosOsCarros;
            TipoPreco rendimento;
            int tempo, count = 1;

            while (atual->next != NULL && strcmp(atual->matricula, matricula)) {    //ir ate ao ultimo veiculo
                atual = atual->next;
            }

            if (strcmp(atual->matricula, matricula)) {
                printf("%s: matriucla not found.", matricula);
                return;
            }

            struct EntradasESaidas *pointer = atual->historico;

            while (pointer->next != NULL) {     //andar ate a ultima entrada/saida
                count += 1;
                pointer = pointer->next;
            }

            //se tiver um comprimento par entao o veiculo nao esta num parque, ou se a entrada anterior tiver um nome de parque diferente
            if (((count % 2) == 0) || strcmp(pointer->nomeDoParque, nomeDoParque)) {
                printf("%s: invalid vehicle exit.\n", matricula);
                return;
            }
            //criar a saida para meter no historico
            struct EntradasESaidas *saida = (struct EntradasESaidas*) malloc (sizeof(struct EntradasESaidas));
            saida->nomeDoParque = strdup(nomeDoParque);
            saida->dataEHora = novaData;
            saida->next = NULL;
            pointer->next = saida; //colocar no historico

            TipoParque *parque = todosOsParques;
            while (strcmp(parque->nome, nomeDoParque)) {
                parque = parque->next;
            }

            tempo = contasDeData(pointer->dataEHora, saida->dataEHora);
            rendimento = faturacao(parque->preco, tempo);

            TipoParque *nesteParque = todosOsParques;
            while (strcmp(nesteParque->nome, nomeDoParque)) {
                nesteParque = nesteParque->next;
            }
            nesteParque->lugareslivres += 1;

            printf("%s %s %s %s %s %2f\n", matricula, pointer->dataEHora.data, pointer->dataEHora.hora, data, hora, rendimento);

            ultimaData = novaData;
        }
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------
void removeParque (char *nomeParaRemover) {
    
    TipoParque *atual = todosOsParques;
    TipoParque *anterior = NULL;

    while (atual != NULL && strcmp(atual->nome, nomeParaRemover) != 0) {
        anterior = atual;
        atual = atual->next;
    }

    //caso o parque exista
    if (atual != NULL) {

        //no caso de ser o primeiro da lista
        if (anterior == NULL) {
            todosOsParques = atual->next;
        } else {
            anterior->next = atual->next;
        }
        free(atual->nome);
        free(atual);

    //caso o parque nao exista
    } else {
        printf("%s: no such parking\n", nomeParaRemover);
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------------------------

char* lerNome (char letra) {
    char *nome = NULL;
    char c;
    int tamanho = 1;
    nome = (char*)malloc(3*sizeof(char));  // Aloca espaço inicial para o nome
    
    
    c = getchar();

    if (letra == '"') {
        nome[0] = c;
        c = getchar();
        while (c != '"') {
            nome[tamanho++] = c;
            nome = (char*) realloc(nome, (tamanho + 1) * sizeof(char)); // Realoca memória para acomodar mais caracteres
            c = getchar();
            
        }
    } else {
        nome[0] = letra;
        while (c != ' ' && c != '\n' && c != EOF) {
             // Realoca memória para acomodar mais caracteres
            nome[tamanho++] = c;
            nome = (char*) realloc(nome, (tamanho + 1) * sizeof(char));
            c = getchar();
        }
    }
    nome = (char*) realloc(nome, (tamanho+1)*sizeof(char));    
    nome[tamanho] = '\0'; //para fechar com caracter nulo

    return nome;
}



int main () {
    char c;
    c = getchar();

    //enquanto nao for dado o comando de terminar o programa ele corre
    while (c != 'q') {
        
        switch (c) {
            case 'p':
 
                while ((c = getchar()) == ' ');

                if (c == '\n') {
                    informacaoParques();

                } else {
                    char *nome = lerNome(c);
                    TipoCapacidade capacidade;
                    TipoPreco x, y, z;
                    
                    scanf("%d %lf %lf %lf", &capacidade, &x, &y, &z);
                                
                    criaParque(nome, capacidade, x, y, z);

                    free(nome);
                    //libertar a memoria
              
                }
                break;
    
            case 'e':
                if (1) {
                char matricula[TAMANHOMATRIULA], data[TAMANHODATA], hora[TAMANHOHORA];
                while ((c = getchar()) == ' ');

                char *nome = lerNome(c);
                
                scanf("%s %s %s", matricula, data, hora);
                                
                entraVeiculo(nome, matricula, data, hora);

                free(nome);

                }
                break;

            case 's':
                if (1) {
                char matricula[TAMANHOMATRIULA], data[TAMANHODATA], hora[TAMANHOHORA];
                while ((c = getchar()) == ' ');

                char *nome = lerNome(c);
                
                scanf("%s %s %s", matricula, data, hora);
                                
                saiVeiculo(nome, matricula, data, hora);

                free(nome);
                }
                break;

                break;

            case 'v':

                break;

            case 'f':

                break;

            case 'r':
                
                while ((c = getchar()) == ' ');
                
                char *nome = lerNome(c);
            
                removeParque(nome);

                free(nome);
                break;

            default:
                break;
        }

        c = getchar();

    }

    // Libertar memória alocada dinamicamente antes de sair
    TipoParque *atual = todosOsParques;
    while (atual != NULL) {
        TipoParque *proximo = atual->next;
        free(atual->nome);
        free(atual);
        atual = proximo;
    }

    return 0;
}