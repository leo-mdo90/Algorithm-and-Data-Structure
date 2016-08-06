//Plínio Santana de Brito 7696243
//Leonardo Moura de Oliveira 7696441
#include <stdio.h>
#include <stdlib.h>
#include <Math.h>
#define Infinity 1000;
/*
<<<LABEL>>>
O: Dalton's position;
X: Cave entrance;
V: free pass;
#: blocked pass;
W: High grass;
*/

typedef struct no
{
    int X;
    int Y;
    char label; //Label
    int DisX;
    int DisO;
    int custoF;
    int ID; //Linked with
    struct no *next;
} next;

typedef struct Grid
{
    int X;
    int Y;
    int CustP;
    int numPos; //Number of nodes
    char label;
    next *adj;
    struct Grid *next;
} Grid;

typedef struct List
{
    next A;

} *List;

typedef struct ListG
{
    Grid G;

} *ListG;

Grid* createNode(Grid *A)
{
    A = (Grid*)malloc(sizeof(Grid));
    A->adj = NULL;
    A->next = NULL;

    return A;
}

void insertNode(Grid *G, int i, char ch)
{
    Grid* aux;

    if(G->next == NULL)
    {
        aux = createNode(aux);
        aux->numPos = i;
        G->next = aux;
        G->label = ch;
    }
    else
    {
        insertNode(G->next,i,ch);
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

Grid* Search(Grid *G, int y)
{
    Grid *aux;
    aux = G;
    while(aux->numPos != y)
    {
        aux = aux->next;
    }

    return aux;
}

next* create_edge(next *A, int y, int n,Grid *G)
{
    Grid *aux;
    aux = G;

    while(aux->numPos != y)
    {
        aux = aux->next;
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
            A->next = NULL;
        }
        else
            return NULL;
    }
    else
    {
        if(A->ID == y)
        {
            printf("Edge already exist %d!\n", y);
            return A;
        }
        else
        {
            A->next = create_edge(A->next,y,n,G);
        }
    }
    return A;

}

void insertEdge(Grid *G , int y, int n,Grid *G1)
{

    if(G == NULL)
    {
        printf("Impossivel Task\n");
        exit(1);//FLAG ERRO
    }

    if(G->numPos != y)
        insertEdge(G->next,y,n,G1);
    else
    {
        if((y>0) && (y<=n))
        {
            if((y%n)== 1)
            {
                G->adj = create_edge(G->adj,y+1,n,G1);
                G->adj = create_edge(G->adj,y+n,n,G1);
            }
            else if((y%n)== 0)
            {
                G->adj = create_edge(G->adj,y-1,n,G1);
                G->adj = create_edge(G->adj,y+n,n,G1);
            }
            else
            {
                G->adj = create_edge(G->adj,y+1,n,G1);
                G->adj = create_edge(G->adj,y-1,n,G1);
                G->adj = create_edge(G->adj,y+n,n,G1);
            }
        }

        else if((y>((n*n)-n)) && (y<=(n*n)))
        {
            if((y%n)== 1)
            {
                G->adj = create_edge(G->adj,y+1,n,G1);
                G->adj = create_edge(G->adj,y-n,n,G1);
            }
            else if((y%n)== 0)
            {
                G->adj = create_edge(G->adj,y-1,n,G1);
                G->adj = create_edge(G->adj,y-n,n,G1);
            }
            else
            {
                G->adj = create_edge(G->adj,y+1,n,G1);
                G->adj = create_edge(G->adj,y-1,n,G1);
                G->adj = create_edge(G->adj,y-n,n,G1);
            }
        }
        else
        {
            if((y%n)== 1)
            {
                G->adj = create_edge(G->adj,y+1,n,G1);
                G->adj = create_edge(G->adj,y+n,n,G1);
                G->adj = create_edge(G->adj,y-n,n,G1);
            }
            else if((y%n)== 0)
            {
                G->adj = create_edge(G->adj,y-1,n,G1);
                G->adj = create_edge(G->adj,y+n,n,G1);
                G->adj = create_edge(G->adj,y-n,n,G1);
            }
            else
            {
                G->adj = create_edge(G->adj,y+1,n,G1);
                G->adj = create_edge(G->adj,y-1,n,G1);
                G->adj = create_edge(G->adj,y+n,n,G1);
                G->adj = create_edge(G->adj,y-n,n,G1);
            }
        }
    }
}


int AStar(Grid *G,int PosX, int PosO)
{
    List *OpenList;
    ListG *ClosedList;
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

    Pai = createNode(Pai);
    Pai->CustP = 0;

    i = 0;
    k = 0;
    iantes = 0;

    OpenList = ((List*)malloc(sizeof(G)));
    ClosedList = ((ListG*)malloc(sizeof(ListG)));

    while(ini->numPos!= PosO)
    {
        ini = ini->next;
    }
    while(fim->numPos!= PosX)
    {
        fim = fim->next;
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
            OpenList = ((List*)realloc(OpenList,(i + 4)*sizeof(G)));
            aux->adj = aux->adj->next;
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
            percorre = percorre->next;
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
        ClosedList = ((ListG*)realloc(ClosedList,(k + 2)*sizeof(ListG)));
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
                aux = aux->next;
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
            G = createNode(G);
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
            insertNode(G,j,ch);
    }
    aux=G;
    while(aux->next != NULL)
    {
        aux = aux->next;
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
        aux = aux->next;
        j++;
    }
    */

    i = n*n;
    j=1;
    while(j<=i)
    {
        insertEdge(G,j,n,G);
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
            Naux = Naux->next;
        }
        printf("\n");
        aux = aux->next;
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
        aux = aux->next;
    }

    int custo = AStar(G,posX,posO);


/*  Print on the archive */

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
        aux = aux->next;
        j++;
    }

    return 0;
}
