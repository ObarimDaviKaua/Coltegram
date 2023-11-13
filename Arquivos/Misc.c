#include "Misc.h"
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

void Resolve_Fgets(char* texto)
{
    texto[strlen(texto) - 1] = '\0';
}

bool AcharParte_NaFrase(char* base, char* achar)
{
    unsigned int Tamanho_Base = strlen(base);
    unsigned int Tamanho_Achar = strlen(achar);
    unsigned int Letras_Coincidentes = 0;

    for(int i = 0; i < Tamanho_Base - Tamanho_Achar + 1; i++)
    {
        Letras_Coincidentes = 0;
        for(int j = 0; j < Tamanho_Achar; j++)
        {
            if(base[i+j] != achar[j])
                break;
            else Letras_Coincidentes++;
        }

        if(Letras_Coincidentes == Tamanho_Achar)
            return true;
    }

    return false;
}
bool Compara_Frases(char* frase1, char* frase2)
{
    unsigned int Tamanho1 = strlen(frase1);
    unsigned int Tamanho2 = strlen(frase2);

    for(int i = 0; i < Tamanho1 && i < Tamanho2; i++)
    {
        if(frase1[i] < frase2[i])
            return true;
        else if(frase1[i] > frase2[i])
            return false;
    }
    
    if(Tamanho1 < Tamanho2)
        return true;
    else return false;
}

void Alocar_ArrayId(S_ArrayId* array)
{
    (array->Quantidade)++;
    if(array->Quantidade == 1)
        array->Id = (unsigned int *) malloc(sizeof(unsigned int));
    else
        array->Id = (unsigned int *) realloc(array->Id, array->Quantidade * sizeof(unsigned int));

    if(array->Id == NULL)
        printf("ERRO: Alocagem de chave-usuario");    
    return;
}
void Alocar_ArrayId_ComValor(S_ArrayId* array, unsigned int novo_valor)
{
    Alocar_ArrayId(array);
    array->Id[array->Quantidade-1] = novo_valor;
    return;
}
void Desalocar_ArrayId(S_ArrayId* array)
{
    if(array->Quantidade == 0)
        return;

    (array->Quantidade)--;
    if(array->Quantidade == 0)
        Liberar_ArrayId(array);
    else
    {
        array->Id = (unsigned int *) realloc(array->Id, array->Quantidade * sizeof(unsigned int));
        if(array->Id == NULL)
            printf("ERRO: De-alocagem de chave-usuario");    
    }
    return;
}
void Remove_Posicao_ArrayId(S_ArrayId* array, int posicao)
{
    array->Id[posicao] = array->Id[array->Quantidade-1];
    Desalocar_ArrayId(array);
}
void Liberar_ArrayId(S_ArrayId* array)
{
    if(array->Id != NULL)
        free(array->Id);
    array->Id = NULL;
    array->Quantidade = 0;
    return;
}
void Remove_Id_DoArray(S_ArrayId* array, unsigned int valor)
{
    for(int i = 0; i < array->Quantidade; i++)
    {
        if(array->Id[i] == valor)
            Remove_Posicao_ArrayId(array, i);
    }
    return;
}
