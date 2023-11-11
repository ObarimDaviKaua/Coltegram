// In�cio do c�digo fornecido pelo professor
// N�o adicione ou remova nada.

// Se estiver no Windows e n�o conseguir ver a imagem colorida, pode ser que seu terminal n�o suporte Ascii Escape Colors.
// Para habilit�-la, execute o comando abaixo no terminal com permiss�o de Administrador.
// Ap�s executado, o terminado deve ser fechado e aberto novamente para ter o suporte �s cores habilitado.
// Comando:
// reg add HKEY_CURRENT_USER\Console /v VirtualTerminalLevel /t REG_DWORD /d 0x00000001 /f

#include "Imagem.h"
#include "Misc.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 *  \brief Fun��o que carrega uma imagem informada na URL.
 *
 *  \param [in] colorido Define se a imagem ser� colorida.
 *  \param [in] largura Define a largura da imagem gerada.
 *  \return Endere�o da estrutura com a imagem.
 *          Caso a imagem n�o tenha sido carregada corretamente, a fun��o
 *          retornar� NULL.
 */
asciiImg_t *insta_carregaImagem(char url[], bool colorido, int largura)
{
    FILE *arquivo;
    char buffer[BUFFER_TAMANHO];
    int nBytes, nBytesTotal = 0;
    char linhaComando[LINHA_COMANDO];

    asciiImg_t *img;
    // Aloca espa�o para uma imagem
    img = malloc(sizeof(asciiImg_t));
    if (img == NULL)
        return NULL;
    // Inicializa a estrutura
    img->bytes = NULL;
    img->nBytes = 0;
    // Monta a linha de comando
    (void)sprintf(linhaComando, "%s %s %s -W %d -c > %s", FERRAMENTA_IMAGEM, url, (colorido ? "-C" : ""), largura, ARQUIVO_IMAGEM_TMP);
    // Chama o programa para fazer o download da imagem
    (void)system(linhaComando);

    // Tenta abrir o arquivo recem criado
    arquivo = fopen(ARQUIVO_IMAGEM_TMP, "r");
    if (arquivo != NULL)
    {
        // Ignorar as 2 primeiras linhas do arquivo
        for (int i = 0; i < 2; i++)
        {
            fgets(buffer, BUFFER_TAMANHO, arquivo);
        }
        
        while (!feof(arquivo))
        {

            // Limpa a linha
            (void)memset(buffer, 0, sizeof(buffer));

            // Tenta ler uma linha
            if (fgets(buffer, BUFFER_TAMANHO, arquivo) == NULL)
                continue;

            // Descobre o n�mero de bytes da linha
            for (nBytes = 0; buffer[nBytes] != 0; nBytes++)
                ;

            // Aloca o espa�o
            img->bytes = realloc(img->bytes, sizeof(unsigned char) * (nBytesTotal + nBytes));

            // Copia para o espa�o alocado
            (void)memcpy(&(img->bytes[nBytesTotal]), buffer, nBytes);
            nBytesTotal += nBytes;
        }

        // Finaliza a imagem colocando o \0 final e o tamanho
        img->bytes = realloc(img->bytes, sizeof(unsigned char) * (nBytesTotal + 1));
        img->bytes[nBytesTotal++] = '\0';
        img->nBytes = nBytesTotal;

        // Fecha o arquivo
        fclose(arquivo);
    }
    // Verifica se a imagem � v�lida
    if (img->nBytes < LIMIAR_INFERIOR_TAMANHO_IMAGEM)
    {
        // Libera todo o espa�o alocado
        free(img->bytes);
        free(img);

        return NULL;
    }
    return img;
}

/**
 *  \brief Fun��o que imprime uma Imagem ASCII.
 *
 *  \param [in] img Endere�o da estrutura com os dados da imagem.
 */
void insta_imprimeImagem(asciiImg_t *img)
{
    printf("%s", img->bytes);
}

/**
 *  \brief Fun��o que libera a mem�ria alocada por uma imagem.
 *
 *  \param [in] img Endere�o da estrutura com os dados da imagem a ser liberada.
 */
void insta_liberaImagem(asciiImg_t *img)
{
    free(img->bytes);
    free(img);
}

// Fim do c�digo fornecido pelo professor
// ----------------------------------------------------------------------------------------------------------------------------

// N�mero de colunas da imagem
#define IMAGEM_NUM_COLUNAS_PADRAO 120

// Defini��o de imagem colorida
#define IMAGEM_COLORIDA true
// Defini��o de imagem preto/branco
#define IMAGEM_PRETO_BRANCO false
// Defini��o de imagem utilizada
#define IMAGEM_TER_COR_PADRAOIMAGEM_COLORIDA

void Alocar_Imagem(S_ArrayImagens* array)
{
    (array->Quantidade)++;
    if(array->Quantidade == 1)
        array->Imagens = (asciiImg_t **) malloc(sizeof(asciiImg_t* ));
    else
        array->Imagens = (asciiImg_t **) realloc(array->Imagens, array->Quantidade * sizeof(asciiImg_t *));

    if(array->Imagens == NULL)
        printf("ERRO: Alocagem de imagens");    
    return;
}
void Liberar_Imagens(S_ArrayImagens* array)
{
    for(int i = 0; i < array->Quantidade; i++)
    {
        insta_liberaImagem(array->Imagens[i]);
    }

    if(array->Imagens != NULL)
        free(array->Imagens);
    array->Imagens = NULL;
    array->Quantidade = 0;
    return;
}
void Desaloca_Imagem(S_ArrayImagens* array)
{
    if(array->Quantidade == 0)
        return;

    (array->Quantidade)--;
    if(array->Quantidade == 0)
        Liberar_Imagens(array);
    else
    {
        insta_liberaImagem(array->Imagens[array->Quantidade]);
        array->Imagens = (asciiImg_t **) realloc(array->Imagens, array->Quantidade * sizeof(asciiImg_t *));
        if(array->Imagens == NULL)
            printf("ERRO: De-alocagem de comentario");    
    }
    return;
}
void Remover_Imagem_DoArray(S_ArrayImagens* array, unsigned int posicao)
{
    if(array->Quantidade == 0 || posicao < 0 || posicao > array->Quantidade - 1)
        return;
    
    insta_liberaImagem(array->Imagens[posicao]);
    for(int i = posicao; i < array->Quantidade - 1; i++)
        array->Imagens[i] = array->Imagens[i + 1];
    
    (array->Quantidade)--;
    if(array->Quantidade == 0)
        Liberar_Imagens(array);
}

void Upload_Imagem(S_ArrayImagens* array)
{
    char Url[TEXTO_TAM];
    int ImagemColorida = true;
    int Resolucao_Horizontal = IMAGEM_NUM_COLUNAS_PADRAO;
    
    Alocar_Imagem(array);
    
    printf("Insira a URL da Imagem: ");
    fgets(Url, TEXTO_TAM, stdin);
    Resolve_Fgets(Url);

    printf("Modo de cor: \n");
    printf("[0] Preto & Branco \n");
    printf("[1] Colorido \n");
    scanf("%d", &ImagemColorida);
    getchar();

    printf("Resolucao horizontal (numero de colunas) da imagem: ");
    scanf("%d", &Resolucao_Horizontal);
    getchar();

    array->Imagens[array->Quantidade-1] = insta_carregaImagem(Url, (bool) ImagemColorida, Resolucao_Horizontal);
    printf(">>> INICIO DA IMAGEM <<< \n");
    insta_imprimeImagem(array->Imagens[array->Quantidade-1]);
    printf(">>> FIM DA IMAGEM <<< \n");
    
    printf(">>> Imagem carregada com sucesso! <<<\n");
}

void Salvar_Imagens_NoArquivo(const S_ArrayImagens* array, FILE* arquivo)
{
    for(int i = 0; i < array->Quantidade; i++)
    {
        fwrite(&array->Imagens[i]->nBytes, sizeof(int), 1, arquivo);
        fwrite(array->Imagens[i]->bytes, sizeof(uint8_t), array->Imagens[i]->nBytes, arquivo);
    }
}
void Carregar_Imagens_DoArquivo(S_ArrayImagens* array, FILE* arquivo)
{
    array->Imagens = (asciiImg_t **) malloc(array->Quantidade * sizeof(asciiImg_t*));
    for(int i = 0; i < array->Quantidade; i++)
    {
        array->Imagens[i] = (asciiImg_t *) malloc(sizeof(asciiImg_t));
        fread(&array->Imagens[i]->nBytes, sizeof(int), 1, arquivo);
        array->Imagens[i]->bytes = (uint8_t *) malloc(array->Imagens[i]->nBytes * sizeof(uint8_t));
        fread(array->Imagens[i]->bytes, sizeof(uint8_t), array->Imagens[i]->nBytes, arquivo);
    }
    if(array->Quantidade == 0)
        array->Imagens = NULL;
}