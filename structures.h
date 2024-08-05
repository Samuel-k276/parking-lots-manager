
#define TAMANHOMATRICULA 8
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
    float x;
    float y;
    float z;
} Precos;


typedef struct Parque* {
    char* nome;
    int capacidade;
    int lugareslivres;
    
    Precos precos;
    float faturacao;

    Parque next;

} Parque;

typedef struct Carro* {
    char matricula[TAMANHOMATRICULA];
    float faturacao;    
    

    
    Carro next;    
} Carro;
