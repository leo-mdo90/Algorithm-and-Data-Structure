//Plínio Santana de Brito 7696243
//Leonardo Moura de Oliveira 7696441
#include <stdio.h>
#include <stdlib.h>
#include <Math.h>
#define Infinity 1000;
/*
<<<LABEL>>>
O: posição do Dalton;
X: entrada da caverna;
V: caminho livre;
#: caminho ocupado;
W: caminho de grama alta.
*/

typedef struct no
{
    int X;
    int Y;
    char label;//LABEL
    int DisX;
    int DisO;
    int custoF;
    int ID;//Com quem está ligada
    struct no *prox;
} next;

typedef struct Grid
{
    int X;
    int Y;
    int CustP;
    int numPos;//Numero do nó
    char label;
    next *adj;
    struct Grid *prox;
} Grid;

typedef struct Lista
{
    next A;

} *Lista;

typedef struct ListaG
{
    Grid G;

} *ListaG;

Grid* cria_No(Grid *A)
{
    A = (Grid*)malloc(sizeof(Grid));
    A->adj = NULL;
    A->prox = NULL;

    return A;
}

void inserirNo(Grid *G, int i, char ch)
{
    Grid* aux;

    if(G->prox == NULL)
    {
        aux = cria_No(aux);
        aux->numPos = i;
        G->prox = aux;
        G->label = ch;
    }
    else
    {
        inserirNo(G->prox,i,ch);
    }
}

void imprimeNoCH(Grid* G)
{
    printf("%c", G->label);
}

void imprimeNo(Grid* G)
{
    printf("%d ", G->numPos);
}

char pesquisa(Grid *G, int y)
{
    Grid *aux;
    aux = G;
    while(aux->numPos != y)
    {
        aux = aux->prox;
    }

    return aux->label;
}

Grid* Search(Grid *G, int y)
{
    Grid *aux;
    aux = G;
    while(aux->numPos != y)
    {
        aux = aux->prox;
    }

    return aux;
}

next* cria_aresta(next *A, int y, int n,Grid *G)
{
    Grid *aux;
    aux = G;

    while(aux->numPos != y)
    {
        aux = aux->prox;
    }
    if(A == NULL)
    {
        if(aux->label != '#')
        {
            A = (next*)malloc(sizeof(next));
            A->ID = y;
            A->X = (int) (y/n)+1;
            aux->X = A->X;
            if((y%n)==0)
            {
                A->Y = n;
                aux->Y = n;
            }
            else
            {
                A->Y = (y%n);
                aux->Y = A->Y;
            }

            A->label = aux->label;
            A->prox = NULL;
        }
        else
            return NULL;
    }
    else
    {
        if(A->ID == y)
        {
            printf("Ja existe aresta %d!\n", y);
            return A;
        }
        else
        {
            A->prox = cria_aresta(A->prox,y,n,G);
        }
    }
    return A;

}

void inserirAresta(Grid *G , int y, int n,Grid *G1)
{

    if(G == NULL)
    {
        printf("Impossivel Tarefa\n");
        exit(1);//FLAG ERRO
    }

    if(G->numPos != y)
        inserirAresta(G->prox,y,n,G1);
    else
    {
        if((y>0) && (y<=n))
        {
            if((y%n)== 1)
            {
                G->adj = cria_aresta(G->adj,y+1,n,G1);
                G->adj = cria_aresta(G->adj,y+n,n,G1);
            }
            else if((y%n)== 0)
            {
                G->adj = cria_aresta(G->adj,y-1,n,G1);
                G->adj = cria_aresta(G->adj,y+n,n,G1);
            }
            else
            {
                G->adj = cria_aresta(G->adj,y+1,n,G1);
                G->adj = cria_aresta(G->adj,y-1,n,G1);
                G->adj = cria_aresta(G->adj,y+n,n,G1);
            }
        }

        else if((y>((n*n)-n)) && (y<=(n*n)))
        {
            if((y%n)== 1)
            {
                G->adj = cria_aresta(G->adj,y+1,n,G1);
                G->adj = cria_aresta(G->adj,y-n,n,G1);
            }
            else if((y%n)== 0)
            {
                G->adj = cria_aresta(G->adj,y-1,n,G1);
                G->adj = cria_aresta(G->adj,y-n,n,G1);
            }
            else
            {
                G->adj = cria_aresta(G->adj,y+1,n,G1);
                G->adj = cria_aresta(G->adj,y-1,n,G1);
                G->adj = cria_aresta(G->adj,y-n,n,G1);
            }
        }
        else
        {
            if((y%n)== 1)
            {
                G->adj = cria_aresta(G->adj,y+1,n,G1);
                G->adj = cria_aresta(G->adj,y+n,n,G1);
                G->adj = cria_aresta(G->adj,y-n,n,G1);
            }
            else if((y%n)== 0)
            {
                G->adj = cria_aresta(G->adj,y-1,n,G1);
                G->adj = cria_aresta(G->adj,y+n,n,G1);
                G->adj = cria_aresta(G->adj,y-n,n,G1);
            }
            else
            {
                G->adj = cria_aresta(G->adj,y+1,n,G1);
                G->adj = cria_aresta(G->adj,y-1,n,G1);
                G->adj = cria_aresta(G->adj,y+n,n,G1);
                G->adj = cria_aresta(G->adj,y-n,n,G1);
            }
        }
    }
}


int AStar(Grid *G,int PosX, int PosO)
{
    Lista *OpenList;
    ListaG *ClosedList;
    Grid  *aux;
    Grid  *ini;
    Grid  *fim;
    Grid  *percorre;
    Grid *Pai;
    fim = G;
    ini = G;
    percorre = G;
    int i,j,k,pos,iantes;
    int custoG = 0;
    int custo = 0;
    int sair = 0;

    Pai = cria_No(Pai);
    Pai->CustP = 0;

    i = 0;
    k = 0;
    iantes = 0;

    OpenList = ((Lista*)malloc(sizeof(G)));
    ClosedList = ((ListaG*)malloc(sizeof(ListaG)));

    while(ini->numPos!= PosO)
    {
        ini = ini->prox;
    }
    while(fim->numPos!= PosX)
    {
        fim = fim->prox;
    }

    do
    {

        aux = ini;
        i = iantes;

        while(aux->adj != NULL)
        {
            if(aux->adj->label == 'V')
            {
                custoG = Pai->CustP + 1;
            }
            else if(aux->adj->label == 'W')
            {
                custoG = Pai->CustP + 2;
            }
            else if(aux->adj->label == 'X')
            {
                custoG = Pai->CustP + 0;

            }
            int custoH = abs(fim->X - aux->adj->X) + abs(fim->Y - aux->adj->Y);
            aux->adj->custoF = custoH + custoG;
            OpenList[i] = aux->adj;
            OpenList = ((Lista*)realloc(OpenList,(i + 4)*sizeof(G)));
            aux->adj = aux->adj->prox;
            i++;
        }
        int minimo = Infinity;
        for(j=iantes; j<i; j++)
        {
            if(OpenList[j]->A.custoF <= minimo)
            {
                minimo = OpenList[j]->A.custoF;
                pos = j;
            }
        }
        if(OpenList[pos]->A.label == 'W')
            {
                Pai->CustP+= 2;
            }
        else if(OpenList[pos]->A.label == 'V')
            {
                Pai->CustP+= 1;
            }
        while(percorre->numPos != OpenList[pos]->A.ID)
        {
            percorre = percorre->prox;
        }
        ClosedList[k] = percorre;
        if(ClosedList[k]->G.label == 'V')
        {
            custo+=1;
        }
        else if(ClosedList[k]->G.label == 'W')
        {
            custo+=2;
        }
        ClosedList = ((ListaG*)realloc(ClosedList,(k + 2)*sizeof(ListaG)));
        ini = percorre;
        percorre = G;
        k++;
        iantes = i;
    }
    while(ini != fim);

    int c;
    aux = G;
    for(c=0; c<k; c++)
    {
        int x=0;
        while(x == 0)
        {
            if(ClosedList[c]->G.numPos == aux->numPos )
            {

                if(aux->label != 'X')
                    aux->label = '*';
                aux = G;
                x = 1;

            }
            else if(ClosedList[c]->G.numPos != aux->numPos)
            {
                aux = aux->prox;
            }
        }
    }
    return custo;

}

int main()
{
    FILE *pfile;
    FILE *pfile2;
    int n,j,i,posX,posO;
    char ch;

    Grid *G = NULL;
    Grid *aux;
    next *Naux;

    int *Cost;

    pfile2 = fopen("arquivo1.txt","w+");
    if(pfile2 == NULL)
    {
        return 5;//Flag de erro
    }
    pfile = fopen("arquivo.txt","r");
    if(pfile == NULL)
    {
        return 5;//Flag de erro
    }
    fscanf(pfile,"%d",&n);
    fscanf(pfile,"%c",&ch);

    for(j=1; j <= (n*n); j++)
    {
        do
        {
            fscanf(pfile,"%c",&ch);
        }
        while(ch == '\n');
        if(G == NULL)
        {
            G = cria_No(G);
            G->numPos = j;
            G->label = ch;
            if((n<999)&&(n>99))
                fseek(pfile,4,SEEK_SET);
            else if((n<99)&&(n>9))
                fseek(pfile,3,SEEK_SET);
            else if((n<9)&&(n>0))
                fseek(pfile,2,SEEK_SET);
        }
        else
            inserirNo(G,j,ch);
    }
    aux=G;
    while(aux->prox != NULL)
    {
        aux = aux->prox;
    }
    fseek(pfile,0,SEEK_END);
    fscanf(pfile,"%c",&ch);
    aux->label = ch;
    /* IMPRIMIR NOS
    j=1;
    aux=G;
    while(aux != NULL)
    {
        if((j%n)==1)
            printf("\n");
        imprimeNoCH(aux);
        imprimeNo(aux);
        aux = aux->prox;
        j++;
    }
    */

    i = n*n;
    j=1;
    while(j<=i)
    {
        inserirAresta(G,j,n,G);
        j++;
    }

/*ADJACENTES
    aux = G;
    do
    {
        Naux = aux->adj;
        while(Naux != NULL)
        {
            printf("%d%c<X%dY%d> ", Naux->ID,Naux->label,Naux->X,Naux->Y);
            Naux = Naux->prox;
        }
        printf("\n");
        aux = aux->prox;
    }
    while(aux != NULL);
*/
    aux=G;
    while(aux!=NULL)
    {
        if(aux->label == 'X')
        {
            posX = aux->numPos;
        }
        else if(aux->label == 'O')
        {
            posO = aux->numPos;
        }
        aux = aux->prox;
    }

    int custo = AStar(G,posX,posO);


//IMPRIMIR NO ARQUIVO

    fprintf(pfile2,"%d",custo);

    void imprimeNoCH(Grid* G, FILE *pfile)
    {
        fprintf(pfile2,"%c", G->label);
    }

    j=1;
    aux=G;
    while(aux != NULL)
    {

        if((j%n)==1)
        {
            fprintf(pfile2,"\n");
        }
        imprimeNoCH(aux,pfile2);
        aux = aux->prox;
        j++;
    }

    return 0;
}
