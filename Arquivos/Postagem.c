#include "Postagem.h"
#include "Misc.h"
#include <stdlib.h>
#include <stdio.h>

unsigned int GerarId_Postagem(const S_ArrayPostagens* array)
{
    unsigned int ultimo_id = 0;
    for(int i = 0; i < array->Quantidade - 1; i++)
    {
        if(array->Postagens[i].Id > ultimo_id)
            ultimo_id = array->Postagens[i].Id;
    }
    return ultimo_id + 1;
}
void Alocar_Postagem(S_ArrayPostagens* array)
{
    (array->Quantidade)++;
    if(array->Quantidade == 1)
        array->Postagens = (S_Postagem *) malloc(sizeof(S_Postagem));
    else
        array->Postagens = (S_Postagem *) realloc(array->Postagens, array->Quantidade * sizeof(S_Postagem));

    if(array->Postagens == NULL)
        printf("ERRO: Alocagem de postagem");    
    return;
}
void Desalocar_Postagem(S_ArrayPostagens* array)
{
    if(array->Quantidade == 0)
        return;

    (array->Quantidade)--;
    if(array->Quantidade == 0)
        Liberar_Postagens_Profundo(array);
    else
    {
        array->Postagens = (S_Postagem *) realloc(array->Postagens, array->Quantidade * sizeof(S_Postagem));
        if(array->Postagens == NULL)
            printf("ERRO: De-alocagem de comentario");    
    }
    return;
}
void Liberar_Postagens(S_ArrayPostagens* array)
{
    if(array->Postagens != NULL)
        free(array->Postagens);
    array->Postagens = NULL;
    array->Quantidade = 0;
    return;
}
void Liberar_Postagens_Profundo(S_ArrayPostagens* array)
{
    for(int i = 0; i < array->Quantidade; i++)
    {
        Liberar_ArrayId(&array->Postagens[i].QuemCurtiu);
        Liberar_Comentarios(&array->Postagens[i].Comentarios);
        Liberar_Imagens(&array->Postagens[i].Imagens);
    }

    if(array->Postagens != NULL)
        free(array->Postagens);
    array->Postagens = NULL;
    array->Quantidade = 0;
    return;
}
void Adicionar_Postagem_NoArray(S_ArrayPostagens* array, const S_Postagem* postagem)
{
    Alocar_Postagem(array);
    array->Postagens[array->Quantidade-1] = *postagem;
    return;
}

S_Postagem* Achar_Postagem_PorId(const S_ArrayPostagens* array, unsigned int id_postagem)
{
    for(int i = 0; i < array->Quantidade; i++)
    {
        if(array->Postagens[i].Id == id_postagem)
            return &array->Postagens[i];
    }
    return NULL;
}
void Postar(S_ArrayPostagens* array, unsigned int id_autor)
{
    Alocar_Postagem(array);
    S_Postagem* NovaPostagem = &array->Postagens[array->Quantidade - 1];

    NovaPostagem->Id = GerarId_Postagem(array);
    NovaPostagem->Autor_Id = id_autor;
    NovaPostagem->Imagens = (S_ArrayImagens) {0, NULL};
    NovaPostagem->QuemCurtiu = (S_ArrayId) {0, NULL};
    NovaPostagem->Comentarios = (S_ArrayComentarios) {0, NULL};

    printf(">> Escreva uma descricao para seu postagem: ");
    fgets(NovaPostagem->Descrit, TEXTO_TAM, stdin);
    Resolve_Fgets(NovaPostagem->Descrit);
}
void VerPostagem(const S_Postagem* postagem, const S_ArrayUsuarios* array)
{
    S_Usuario* Autor = Achar_Usuario_PorId(array, postagem->Autor_Id);
    printf(">>> POSTAGEM %06u <<<\n", postagem->Id);
    printf("> Autor: %s [%06u]\n", Autor->Nome, Autor->Id);
    printf("> Imagens: %d\n", postagem->Imagens.Quantidade);
    printf("> Curtidas: %d \n\n", postagem->QuemCurtiu.Quantidade);
    

    for(int i = 0; i < postagem->Imagens.Quantidade; i++)
    {
        printf(">>> INICIO DA IMAGEM %u <<< \n", i);
        insta_imprimeImagem(postagem->Imagens.Imagens[i]);
        printf(">>> FIM DA IMAGEM %u <<< \n", i);
    }
    printf(">> Descricao do Autor <<\n");
    printf("> %s < \n\n", postagem->Descrit);
}
S_ArrayPostagens Achar_Postagens_DoUsuario(S_ArrayPostagens* array, unsigned int id_usuario)
{
    S_ArrayPostagens Saida = {0, NULL};
    for(int i = 0; i < array->Quantidade; i++)
    {
        if(array->Postagens[i].Autor_Id == id_usuario)
            Adicionar_Postagem_NoArray(&Saida, &array->Postagens[i]);
    }
    return Saida;
}

void Comentar(S_ArrayUsuarios* array, S_Postagem* postagem, unsigned int id_autor)
{
    Criar_Comentario(&postagem->Comentarios, postagem->Id, id_autor);
    S_Usuario* Usuario = Achar_Usuario_PorId(array, id_autor);
    Alocar_ArrayId_ComValor(&Usuario->PostagensComentadas, postagem->Id);
}
void Recomentar(S_Postagem* postagem, unsigned int id_autor)
{
    int id_comentario = -1;

    printf(">> ID do comentario a ser apagado: ");
    scanf("%d", &id_comentario);
    getchar();

    S_Comentario* Comentario = Achar_Comentario(&postagem->Comentarios, id_comentario);
    if(Comentario == NULL)
    {
        printf(">>>> Este Comentario nao existe! <<<<\n");
        return;
    }
    if(Verifica_Autoria(Comentario, id_autor) == false)
    {
        printf(">>>> Este Comentario pertence a outro usuario! <<<<\n");
        return;
    }

    Editar_Comentario(&postagem->Comentarios, Comentario);
    printf(">>> Postagem apagada! <<<\n");
}

void Descomentar(S_ArrayUsuarios* array, S_Postagem* postagem, unsigned int id_autor)
{
    int id_comentario = -1, posicao_comentario = -1;

    printf(">> ID do comentario a ser apagado: ");
    scanf("%d", &id_comentario);
    getchar();

    posicao_comentario = Achar_Posicao_DoComentario(&postagem->Comentarios, id_comentario);
    if(posicao_comentario < 0)
    {
        printf(">>>> Este Comentario nao existe! <<<<\n");
        return;
    }
    if(Verifica_Autoria(&postagem->Comentarios.Comentarios[posicao_comentario], id_autor) == false)
    {
        printf(">>>> Este Comentario pertence a outro usuario! <<<<\n");
        return;
    }
    S_Comentario* Comentario = &postagem->Comentarios.Comentarios[posicao_comentario];

    S_Usuario* Usuario = Achar_Usuario_PorId(array, Comentario->Perfil_Id);
    Remove_Id_DoArray(&Usuario->PostagensComentadas, Comentario->Id);

    Apagar_Comentario(&postagem->Comentarios, posicao_comentario);
    printf(">>> Postagem apagada! <<<\n");
}

void Curtir_Postagem(S_ArrayUsuarios* array, S_Postagem* postagem, unsigned int id_usuario)
{
    if(VerificarCurtida_Postagem(postagem, id_usuario) == true)
        return;

    Alocar_ArrayId_ComValor(&postagem->QuemCurtiu, id_usuario);
    
    S_Usuario* Usuario = Achar_Usuario_PorId(array, id_usuario);
    Alocar_ArrayId_ComValor(&Usuario->PostagensCurtidas, postagem->Id);

    printf("Postagem Curtida!\n");
}
void Descurtir_Postagem(S_ArrayUsuarios* array, S_Postagem* postagem, unsigned int id_usuario)
{
    if(VerificarCurtida_Postagem(postagem, id_usuario) != true)
        return;

    for(int i = 0; i < postagem->QuemCurtiu.Quantidade; i++)
    {
        if(postagem->QuemCurtiu.Id[i] == id_usuario)
        {
            postagem->QuemCurtiu.Id[i] = postagem->QuemCurtiu.Id[postagem->QuemCurtiu.Quantidade-1];
            Desalocar_ArrayId(&postagem->QuemCurtiu);
            
            S_Usuario* Usuario = Achar_Usuario_PorId(array, id_usuario);
            Remove_Id_DoArray(&Usuario->PostagensCurtidas, postagem->Id);
            
            printf("Postagem Descurtida!\n");
            return;
        }
    } 
}
void Mostrar_Curtidas(const S_ArrayUsuarios* array, const S_Postagem* postagem)
{
    S_ArrayUsuarios Encontrados = {0, NULL};
    S_Usuario* Buffer;
    for(int i = 0; i < postagem->QuemCurtiu.Quantidade; i++)
    {
        Buffer = Achar_Usuario_PorId(array, postagem->QuemCurtiu.Id[i]);
        Adicionar_Usuario_NoArray(&Encontrados, Buffer);
    }

    Mostrar_Usuarios(&Encontrados);
    Liberar_Usuarios(&Encontrados);
}

bool VerificarCurtida_Postagem(const S_Postagem* postagem, unsigned int id_usuario)
{
    for(int i = 0; i < postagem->QuemCurtiu.Quantidade; i++)
    {
        if(postagem->QuemCurtiu.Id[i] == id_usuario)
            return true;
    }
    return false;
}
void Editar_Post(S_ArrayPostagens* postagens, S_Postagem* postagem)
{
    int Escolha = 0;
    do
    {
        printf("[1] Alterar Descricao\n");
        printf("[2] Adicionar Imagens\n");
        printf("[3] Remover Imagem\n");
        printf("[0] Cancelar\n");
        
        printf(">> ");
        scanf("%d", &Escolha);
        getchar();

        switch (Escolha)
        {
            case 0:
                return;
            case 1:
                printf(">> Escreva uma descricao para seu postagem: ");
                fgets(postagem->Descrit, TEXTO_TAM, stdin);
                Resolve_Fgets(postagem->Descrit);
                printf(">> Descricao alterada com sucesso! <<\n");
                break;
            case 2:
                do
                {
                    Upload_Imagem(&postagem->Imagens);
                    printf(">> Adicionar outra imagem? <1 para sim, 0 para nao>: \n");
                
                    scanf("%d", &Escolha);
                    getchar();
                } while (Escolha != 0); 
                break;
            case 3:
                printf(">> Posicao da imagem: \n");
                scanf("%d", &Escolha);

                Remover_Imagem_DoArray(&postagem->Imagens, Escolha-1);
                break;
        }
    } while (1);
    
}
void Apagar_Post(S_ArrayPostagens* postagens, unsigned int post_id, S_ArrayUsuarios* usuarios)
{
    for(int i = 0; i < usuarios->Quantidade; i++)
    {
        S_Usuario* Usuario_Atual = &usuarios->Usuarios[i];
        int Posicao_Aux = Checar_Usuario_CurtiuPost(Usuario_Atual, post_id);
        if(Posicao_Aux >= 0)
            Remove_Posicao_ArrayId(&Usuario_Atual->PostagensCurtidas, Posicao_Aux);
        do
        {
            Posicao_Aux = Checar_Usuario_Comentou(Usuario_Atual, post_id);
            if(Posicao_Aux < 0) break;
            
            Remove_Posicao_ArrayId(&Usuario_Atual->PostagensComentadas, Posicao_Aux);
        } while (1);
    }

    for(int i = 0; i < postagens->Quantidade; i++)
    {
        if(postagens->Postagens[i].Id == post_id)
        {
            postagens->Postagens[i] = postagens->Postagens[postagens->Quantidade-1];
            Desalocar_Postagem(postagens);
            return;
        }
    }
}

void SalvarArquivo_Postagens(const S_ArrayPostagens* array, char* caminho_arquivo)
{
    FILE* Arquivo = fopen(caminho_arquivo, "wb");
    if(Arquivo == NULL)
    {
        printf("ERRO: Abertura de arquivo");
        return;
    }
    
    fwrite(&(array->Quantidade), sizeof(unsigned int), 1, Arquivo);
    fwrite(array->Postagens, sizeof(S_Postagem), array->Quantidade, Arquivo);
    for(int i = 0; i < array->Quantidade; i++)
    {

        Salvar_Imagens_NoArquivo(&array->Postagens[i].Imagens, Arquivo);

        fwrite(array->Postagens[i].QuemCurtiu.Id,
                sizeof(unsigned int),
                array->Postagens[i].QuemCurtiu.Quantidade,
                Arquivo);
        fwrite(array->Postagens[i].Comentarios.Comentarios,
                sizeof(S_Comentario),
                array->Postagens[i].Comentarios.Quantidade,
                Arquivo);
    }
    
    fclose(Arquivo);
    return;
}

void CarregarArquivo_Postagens(S_ArrayPostagens* array, char* caminho_arquivo)
{
    FILE* Arquivo = fopen(caminho_arquivo, "rb");

    if(Arquivo == NULL)
    {
        printf(">>> Arquivo de postagens (posts.bin) nao encontrado! <<\n");
        printf(">>> Um novo arquivo sera criado ao final do programa <<\n");
        return;
    }
    
    fread(&(array->Quantidade), sizeof(unsigned int), 1, Arquivo);
    array->Postagens = (S_Postagem*) malloc(array->Quantidade * sizeof(S_Postagem));
    fread(array->Postagens, sizeof(S_Postagem), array->Quantidade, Arquivo);
    for(int i = 0; i < array->Quantidade; i++)
    {
        Carregar_Imagens_DoArquivo(&array->Postagens[i].Imagens, Arquivo);
        
        S_ArrayId* QuemCurtiu = &array->Postagens[i].QuemCurtiu;
        QuemCurtiu->Id = (unsigned int *) malloc(QuemCurtiu->Quantidade * sizeof(unsigned int));
        fread(array->Postagens[i].QuemCurtiu.Id,
                sizeof(unsigned int),
                array->Postagens[i].QuemCurtiu.Quantidade,
                Arquivo);
        if(QuemCurtiu->Quantidade == 0)
            QuemCurtiu->Id = NULL;
        
        S_ArrayComentarios* Comentarios = &array->Postagens[i].Comentarios;
        Comentarios->Comentarios = (S_Comentario *) malloc(Comentarios->Quantidade * sizeof(S_Comentario));
        fread(array->Postagens[i].Comentarios.Comentarios,
                sizeof(S_Comentario),
                array->Postagens[i].Comentarios.Quantidade,
                Arquivo);
        if(Comentarios->Quantidade == 0)
            Comentarios->Comentarios = NULL;
        
    }
    
    fclose(Arquivo);
    return;
}
