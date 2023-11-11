#ifndef MISC_H
#define MISC_H

#include <stdbool.h>
#define NOME_TAM    (64) + 1
#define SENHA_TAM   (16) + 1
#define TEXTO_TAM   (256) + 1

#ifdef __unix__
#define Limpar_Tela() system("clear");
#else
#define Limpar_Tela() system("cls");
#endif

typedef enum
{
    Ordena_Id = 0,
    Ordena_Nome = 1,
    Ordena_Email = 2

} E_OrdenarPor;

typedef struct
{
    unsigned int Quantidade;
    unsigned int *Id;
} S_ArrayId;

void Alocar_ArrayId(S_ArrayId* array);
void Alocar_ArrayId_ComValor(S_ArrayId* array, unsigned int novo_valor);
void Remove_Posicao_ArrayId(S_ArrayId* array, int posicao);
void Remove_Id_DoArray(S_ArrayId* array, unsigned int valor);
void Desalocar_ArrayId(S_ArrayId* array);
void Liberar_ArrayId(S_ArrayId* array);

void Resolve_Fgets(char* texto);
bool AcharParte_NaFrase(char* base, char* achar);
bool Compara_Frases(char* frase1, char* frase2);

#endif