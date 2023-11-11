#ifndef IMAGEM_H
#define IMAGEM_H
// In�cio do c�digo fornecido pelo professor
// N�o adicione ou remova nada.

// Se estiver no Windows e n�o conseguir ver a imagem colorida, pode ser que seu terminal n�o suporte Ascii Escape Colors.
// Para habilit�-la, execute o comando abaixo no terminal com permiss�o de Administrador.
// Ap�s executado, o terminado deve ser fechado e aberto novamente para ter o suporte �s cores habilitado.
// Comando:
// reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 0x00000001 /f

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// Estrutura que representa uma imagem em Ascii
struct asciiImg_s
{
    uint8_t *bytes;
    int nBytes;
};

/// Tipo "Imagem ASCII"
typedef struct asciiImg_s asciiImg_t;

// Tamanho do buffer para cada linha da imagem
#define BUFFER_TAMANHO 50000

// Tamanho m�ximo da linha de comando
#define LINHA_COMANDO 10000

// Limiar inferior que considera o download com sucesso
#define LIMIAR_INFERIOR_TAMANHO_IMAGEM 500

// Nome do execut�vel da ferramenta de download e convers�o da imagem
#ifdef __unix__
#define FERRAMENTA_IMAGEM "./ascii-image-converter.bin"
#else
#define FERRAMENTA_IMAGEM "ascii-image-converter.exe"
#endif

// Nome do arquivo de sa�da tempor�rio da imagem
#define ARQUIVO_IMAGEM_TMP "ascii_art.txt"

/**
 *  \brief Fun��o que carrega uma imagem informada na URL.
 *
 *  \param [in] colorido Define se a imagem ser� colorida.
 *  \param [in] largura Define a largura da imagem gerada.
 *  \return Endere�o da estrutura com a imagem.
 *          Caso a imagem n�o tenha sido carregada corretamente, a fun��o
 *          retornar� NULL.
 */
asciiImg_t *insta_carregaImagem(char url[], bool colorido, int largura);

/**
 *  \brief Fun��o que imprime uma Imagem ASCII.
 *
 *  \param [in] img Endere�o da estrutura com os dados da imagem.
 */
void insta_imprimeImagem(asciiImg_t *img);

/**
 *  \brief Fun��o que libera a mem�ria alocada por uma imagem.
 *
 *  \param [in] img Endere�o da estrutura com os dados da imagem a ser liberada.
 */
void insta_liberaImagem(asciiImg_t *img);
// Fim do c�digo fornecido pelo professor
// ----------------------------------------------------------------------------------------------------------------------------


// N�mero de colunas da imagem
#define IMAGEM_NUM_COLUNAS_PADRAO 120

// Defini��o de imagem utilizada
#define IMAGEM_TER_COR_PADRAO false
typedef struct 
{
    unsigned int Quantidade;
    asciiImg_t** Imagens;
} S_ArrayImagens;

void Alocar_Imagem(S_ArrayImagens* array);
void Liberar_Imagens(S_ArrayImagens* array);
void Desaloca_Imagem(S_ArrayImagens* array);
void Remover_Imagem_DoArray(S_ArrayImagens* array, unsigned int posicao);

void Upload_Imagem(S_ArrayImagens* array);

void Salvar_Imagens_NoArquivo(const S_ArrayImagens* array, FILE* arquivo);
void Carregar_Imagens_DoArquivo(S_ArrayImagens* array, FILE* arquivo);
#endif