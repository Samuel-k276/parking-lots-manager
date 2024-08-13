
#define TAMANHOMATRICULA 8

typedef float TipoPrecos;
typedef struct Hora {
    int horas;
    int minutos;
} Hora;

typedef struct Data {
    int dia;
    int mes;
    int ano;
} Data;

typedef struct DataEHora {
    Data data;
    Hora hora;
} DataEHora;

typedef struct Precos {
    TipoPrecos x;
    TipoPrecos y;
    TipoPrecos z;
} Precos;


typedef struct Parque {
    char* nome;
    int capacidade;
    int lugareslivres;
    
    Precos precos;
    TipoPrecos faturacao;

    Parque* next;

} Parque;

typedef struct Carro {
    char matricula[TAMANHOMATRICULA];
    TipoPrecos faturacao;    
    

    
    Carro* next;    
} Carro;
