
#define TAMANHOMATRICULA 8
typedef struct Precos {
    float x;
    float y;
    float z;
} Precos;


typedef struct Parque {
    char* nome;
    Precos precos;
    int capacidade;
    int lugareslivres;
    float faturacao;

    Parque* next;

} Parque;

typedef struct Carro {
    char matricula[TAMANHOMATRICULA];


    Carro* next;    
} Carro;