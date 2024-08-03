

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