#ifndef SORTED_LIST_H
#define SORTED_LIST_H
#include<string.h>
#include<stdlib.h>

#include <stdio.h>

typedef struct ListNode {
    struct ListNode *urmator;
    struct ListNode *anterior;
    int prioritate;
    char *nume;
} ListNode;

typedef struct List {
    ListNode *primul;
    ListNode *ultimul;
} List;


int NumarActualGhisee = 0;
int NumarOameniTotal;

void deschide_ghisee(List ***ghisee, int N) {

	int i,j; //indici uilizati

	if(*ghisee == NULL && NumarActualGhisee == 0 ) // daca nu era niciun ghiseu deschis 
		{*ghisee = (List**)malloc (N * sizeof(List*)); 
		for ( i = 0 ; i < N ; i ++ )
			{ 
			((*ghisee)[i]) = (List*)malloc(sizeof(List));
			((*ghisee)[i])->primul = NULL;
			((*ghisee)[i])->ultimul = ((*ghisee)[i])->primul;	
			}
			NumarActualGhisee = N; 
		return;
		}

	

	if(*ghisee != NULL && NumarActualGhisee != N) //daca erau deja alocate alte ghisee
		{
			
		ListNode *first=NULL,*last=NULL; //pun toti oamenii din ghiseele anterioare intr-o lista
		first = (ListNode*)malloc(sizeof(ListNode));
		

		ListNode *g;
		i=0; g = ((*ghisee)[0])->primul;
		ListNode *node = (ListNode*)malloc(sizeof(ListNode));
			node->prioritate = g->prioritate;
			node->nume = g->nume;
			
			
			first = node;
				
		

		last = first;
		ListNode *w = first;
		
		
		int verif = 0;		
			

		for(i=0;i<NumarActualGhisee;i++) //facem lista
			{
			
			
			
			if(verif == 0) { g = ((*ghisee)[0])->primul->urmator; verif = 1; }
			else {g = ((*ghisee)[i])->primul;}

			while(g!=NULL)
			{ 
			ListNode *node = (ListNode*)malloc(sizeof(ListNode));
			node->prioritate = g->prioritate;
			node->nume = g->nume;
			
			
			w->urmator = node;
			node->anterior = w;
			node->urmator = NULL;
			
			w = w->urmator;
			g = g->urmator;	
		
			}
			

			}
		
			



		for(i=0;i<NumarActualGhisee;i++) //eliberam ghiseele anterioare
			{
			 ((*ghisee)[i])->primul = ((*ghisee)[i])->ultimul = NULL;		
			}
		
		for ( i = 0 ; i < NumarActualGhisee ; i ++ )
		{
		free((*ghisee)[i]) ; 	
		}
		free(*ghisee);

		*ghisee = (List**)malloc (N * sizeof(List*)); //facem alte ghisee
		for ( i = 0 ; i < N ; i ++ )
			{ 
			((*ghisee)[i]) = (List*)malloc(sizeof(List));
			((*ghisee)[i])->primul = NULL;
			((*ghisee)[i])->ultimul = ((*ghisee)[i])->primul;	
			}
			NumarActualGhisee = N; 

		


		ListNode *premier = NULL , *dernier = NULL; //creez o noua lista in care voi ordona elementele listei anterioare
		premier = (ListNode*)malloc(sizeof(ListNode));
		
		node = malloc(sizeof(ListNode));
		node->nume = first->nume;
		node->prioritate = first->prioritate;
		node->urmator = NULL;
		node->anterior = NULL;

		ListNode *pointer = first;
		pointer = pointer->urmator;

		premier = dernier = node;

		ListNode *index = premier;

		int checkifdone = 0;
		
		if( first == last ) { checkifdone = 1; }

		while( pointer != NULL )
			{ checkifdone = 0 ;
			ListNode *index = premier;
			node = malloc(sizeof(ListNode));
			node->nume = pointer->nume;
			node->prioritate = pointer->prioritate;
			node->urmator = NULL;
			node->anterior = NULL;
		
			if(checkifdone == 0 && index->prioritate < node->prioritate) //daca putem insera nodul inainte de primul element - caz cand prioritatea nodului este mai mare
				{
				index->anterior = node;
				node->anterior = NULL;
				node->urmator = index;
				premier = node;
				checkifdone = 1;	
				}
	
			if(checkifdone == 0 && index->prioritate == node->prioritate && (strcmp(node->nume,index->nume)<=0)) //daca putem insera nodul inainte de primul element - caz cand prioritatile sunt egale si se compara numele
				{
				index->anterior = node;
				node->anterior = NULL;
				node->urmator = index;
				premier = node;
				checkifdone = 1;
				}

			while(checkifdone == 0 && index!=NULL && index->prioritate > node->prioritate) //se merge mai departe pana se gaseste un element de prioritate mai mica sau egala sau pana se ajunge la NULL
				{index=index->urmator;}

			if(checkifdone == 0 && index == NULL) //daca se ajunge la NULL , inseram la sfarsit 
				{
				dernier->urmator = node;
				node->anterior = dernier;
				node->urmator = NULL;
				dernier = node;
				checkifdone = 1;
				}

			if(checkifdone == 0 && index->prioritate < node->prioritate) //daca se poate insera inainte de un element cu prioritatea mai mica 
				{
				node->anterior = index->anterior;
				node->urmator = index;
				index->anterior->urmator = node;
				index->anterior = node;
				checkifdone = 1;
				}
	
			int ok = 0;
			while(checkifdone == 0 && ok == 0) //daca inseram pe la mijloc sau la sfarsit 
			{
				if(checkifdone == 0 && ok == 0 && index->prioritate == node->prioritate && strcmp(index->nume,node->nume)>0) //daca prioritatile sunt egale si 
					{
					node->anterior = index->anterior;
					node->urmator = index;
					index->anterior->urmator = node;
					index->anterior = node;
					ok = 1;
					checkifdone = 1;
					}

				if(checkifdone == 0 && ok == 0 && index->prioritate < node->prioritate) //daca se poate insera inainte de un element cu prioritatea mai mica 
					{
					node->anterior = index->anterior;
					node->urmator = index;
					index->anterior->urmator = node;
					index->anterior = node;
					ok = 1;
					checkifdone = 1;
					}	
		
				index = index->urmator;

				if(checkifdone == 0 && index == NULL) //daca trebuie inserat la sfarsit
					{
					dernier->urmator = node;
					node->anterior = dernier;
					node->urmator = NULL;
					dernier = node;
					ok = 1;
					checkifdone = 1;
					}		


	
			}

			pointer = pointer->urmator;
			
			}

	

		
			ListNode *pointerInserare = premier; //pointam la lista ordonata (a 2-a)
	
			int indice = 0; // indicele ghiseului	
					

			while( pointerInserare != NULL ) //adaugam oamenii la ghisee pana cand se termina lista
				{
				
				ListNode *node = malloc(sizeof(ListNode)); //alocam un nod luat din lista ordonata
				node->nume = pointerInserare->nume;
				node->prioritate = pointerInserare->prioritate;
				node->urmator = NULL;
				node->anterior = NULL;

				int eraGol = 0;				

				if((*ghisee)[indice]->primul == NULL && (*ghisee)[indice]->ultimul == NULL) // daca ghiseul era gol
					{
					((*ghisee)[indice])->primul = node;
					((*ghisee)[indice])->ultimul = node;
					indice++;
					if(indice == N) {indice = 0;} //daca 
					eraGol = 1;
					}

				if( eraGol == 0 ) //daca ghiseul nu era gol
					{					
					ListNode *pointerGhiseu = ((*ghisee)[indice])->primul; //pointam la primul element al ghiseului respectiv

					while( pointerGhiseu->urmator != NULL ) { pointerGhiseu = pointerGhiseu->urmator; }

					if( pointerGhiseu->urmator == NULL )
						{
						pointerGhiseu->urmator = node;
						node->anterior = pointerGhiseu;
						(*ghisee)[indice]->ultimul = node;
						indice++;
						if(indice == N) {indice = 0;}		
						}					
					



					}	

				pointerInserare = pointerInserare->urmator;	
		
				}


		
		}

}

void inchide_ghisee(List ***ghisee) {

	int i;
	for ( i = 0 ; i < NumarActualGhisee ; i ++ )
		{
		free((*ghisee)[i]) ; 	
		}
	free(*ghisee);
	NumarActualGhisee = 0;
}

void adauga_persoana(List ***ghisee, char *nume, int prioritate, 
		int numar_ghiseu) {
	
	if(numar_ghiseu >= NumarActualGhisee) {return;} //daca nu exista ghiseul la care sa adaugam persoana

	ListNode *nod = malloc(sizeof(ListNode));
	nod->nume = nume;
	nod->prioritate = prioritate;
	nod->urmator = NULL;
	nod->anterior = NULL;


	if((*ghisee)[numar_ghiseu]->primul == NULL && (*ghisee)[numar_ghiseu]->ultimul == NULL) // daca lista era vida
		{
		((*ghisee)[numar_ghiseu])->primul = nod;
		((*ghisee)[numar_ghiseu])->ultimul = nod;
		return;
		}

	ListNode *g = ((*ghisee)[numar_ghiseu])->primul; // iau g pointer la primul element
	if(g->prioritate < prioritate) //daca putem insera nodul inainte de primul element - caz cand prioritatea nodului este mai mare
		{
		g->anterior = nod;
		nod->anterior = NULL;
		nod->urmator = g;
		((*ghisee)[numar_ghiseu])->primul = nod;
		return;	
		}
	
	if(g->prioritate == prioritate && (strcmp(nume,g->nume)<=0)) //daca putem insera nodul inainte de primul element - caz cand prioritatile sunt egale si se compara numele
		{
		g->anterior = nod;
		nod->anterior = NULL;
		nod->urmator = g;
		((*ghisee)[numar_ghiseu])->primul = nod;
		return;
		}

	while(g!=NULL && g->prioritate > prioritate) //se merge mai departe pana se gaseste un element de prioritate mai mica sau egala sau pana se ajunge la NULL
		{g=g->urmator;}

	if(g == NULL) //daca se ajunge la NULL , inseram la sfarsit 
		{
		((*ghisee)[numar_ghiseu])->ultimul->urmator = nod;
		nod->anterior = ((*ghisee)[numar_ghiseu])->ultimul;
		nod->urmator = NULL;
		((*ghisee)[numar_ghiseu])->ultimul = nod;
		return;
		}

	if(g->prioritate < prioritate) //daca se poate insera inainte de un element cu prioritatea mai mica 
		{
		nod->anterior = g->anterior;
		nod->urmator = g;
		g->anterior->urmator = nod;
		g->anterior = nod;
		return;
		}
	
	int ok = 0;
	while(ok == 0) //daca inseram  la mijloc sau la sfarsit 
		{
		if(ok == 0 && g->prioritate == prioritate && strcmp(g->nume,nume)>0) //daca prioritatile sunt egale si nodul se insereaza inainte
			{
			nod->anterior = g->anterior;
			nod->urmator = g;
			g->anterior->urmator = nod;
			g->anterior = nod;
			ok = 1;
			return;
			}

		if(ok == 0 && g->prioritate < prioritate) //daca se poate insera inainte de un element cu prioritatea mai mica 
			{
			nod->anterior = g->anterior;
			nod->urmator = g;
			g->anterior->urmator = nod;
			g->anterior = nod;
			ok = 1;
			return;
			}	
		
		g = g->urmator;

		if(g == NULL) //daca trebuie inserat la sfarsit
		{
		((*ghisee)[numar_ghiseu])->ultimul->urmator = nod;
		nod->anterior = ((*ghisee)[numar_ghiseu])->ultimul;
		nod->urmator = NULL;
		((*ghisee)[numar_ghiseu])->ultimul = nod;
		ok = 1;
		return;
		}		


	
		}



}

void sterge_persoana(List ***ghisee, char *nume, int prioritate, 
		int numar_ghiseu) {
	
	if(numar_ghiseu >= NumarActualGhisee) 
		{ return; }  //daca nu exista ghiseul de la care sa stergem persoana
	
	if((*ghisee)[numar_ghiseu]->primul == NULL && (*ghisee)[numar_ghiseu]->ultimul == NULL) // daca lista era vida
		{ return; }

	ListNode *g = ((*ghisee)[numar_ghiseu])->primul; //putem pointa la primul element

	if( ((*ghisee)[numar_ghiseu])->primul == ((*ghisee)[numar_ghiseu])->ultimul ) //daca ghiseul are un singur om
					{
			if(((*ghisee)[numar_ghiseu])->primul->nume == nume && ((*ghisee)[numar_ghiseu])->primul->prioritate == prioritate)
					{					
					((*ghisee)[numar_ghiseu])->primul = NULL;
					((*ghisee)[numar_ghiseu])->ultimul = NULL;
					g = NULL;
					free(g);
					return;
					}
					}
	while(g != NULL) //daca lista are mai mult de un om
		{	
		if(g->prioritate == prioritate && g->nume == nume)
		{
			if(g->anterior == NULL) //daca omul cautat este chiar primul 
				{
				g->urmator->anterior = NULL;
				((*ghisee)[numar_ghiseu])->primul = g->urmator;
				//g->urmator->anterior = NULL; 
				g = NULL;
				free(g);
				return;
				}

			if(g->urmator == NULL) //daca omul cautat este ultimul 
				{
				((*ghisee)[numar_ghiseu])->ultimul = g->anterior;
				g->anterior->urmator = NULL;
				g = NULL;
				free(g);
				return;
				}
			if(g->anterior != NULL && g->urmator != NULL) //daca elementul de sters este intre alte doua elemente
				{
				g->urmator->anterior = g->anterior;
				g->anterior->urmator = g->urmator;
				g = NULL;
				free(g);
				return;			
				}

		}
		g = g->urmator;

		}

	return;


}

void sterge_primii_oameni(List ***ghisee) {
	
	int i;

	if(NumarActualGhisee == 0) {return;}	

	for(i = 0 ; i < NumarActualGhisee ; i ++ ) //operatiile vor fi efectuate pentru toate ghiseele
		
		{    
		 
			if(((*ghisee)[i])->primul != NULL) //daca ghiseul i este alocat si are 1 element cel putin

				{ 

				ListNode *g = ((*ghisee)[i])->primul; //putem pointa la primul element 
				
				if( ((*ghisee)[i])->primul == ((*ghisee)[i])->ultimul ) //daca ghiseul are un singur om
					{
					((*ghisee)[i])->primul = NULL;
					((*ghisee)[i])->ultimul = NULL;
					g = NULL;
					free(g);
					
					}
				else if( ((*ghisee)[i])->primul != ((*ghisee)[i])->ultimul ){  //daca ghiseul are mai multi oameni
					((*ghisee)[i])->primul = g->urmator;
					g->urmator->anterior = NULL;
					g = NULL;
					free(g);
					
					}

				
				}

		}
	
		return;


}

int calculeaza_numar_oameni_ghiseu(List **ghisee, int numar_ghiseu) {
	
	int i ; 

	int NumarOameniGhiseu = 0;

	if(numar_ghiseu >= NumarActualGhisee) {return -1;} //daca nu exista ghiseul indicat 

	if(NumarActualGhisee == 0) {return 0;} //daca nu sunt alocate ghiseele


	

			

			if(((ghisee)[numar_ghiseu])->primul != NULL) //daca ghiseul i este alocat si are un element cel putin 

				{

				ListNode *g = ((ghisee)[numar_ghiseu])->primul; //putem pointa la primul element 
				
				while( g != NULL) //pana cand ajungem la NULL , crestem numarul oamenilor din ghiseu

					{
					 g = g->urmator;
					 NumarOameniGhiseu++;			
					 }			
			
				}

			
	return NumarOameniGhiseu;





}

int calculeaza_numar_total_oameni(List **ghisee) {
	
	int i;
	
	NumarOameniTotal = 0;

	if(*ghisee == NULL && NumarActualGhisee == 0) {return 0;} //daca nu sunt alocate ghiseele

	for(i = 0 ; i < NumarActualGhisee ; i ++ ) //operatiile vor fi efectuate pentru toate ghiseele
		
		{
		 
	

			if(((ghisee)[i])->primul != NULL) //daca ghiseul i este alocat si are 1 element cel putin

				{

				ListNode *g = ((ghisee)[i])->primul; //putem pointa la primul element 
				
				while( g != NULL) //pana cand ajungem la NULL , crestem numarul oamenilor

					{
					 g = g->urmator;
					 NumarOameniTotal++;			
					 }			
			
				}


		 }
	
	return NumarOameniTotal ; 


//	return -1;
}

int gaseste_pozitie_persoana (List **ghisee, char *nume, int prioritate, 
		int numar_ghiseu) {
	

		if(numar_ghiseu >= NumarActualGhisee) {return -1;} //daca nu exista ghiseul indicat
		
		if(((ghisee)[numar_ghiseu])->primul == NULL && ((ghisee)[numar_ghiseu])->ultimul == NULL) // daca lista era vida
			{ return -1; }

		int index = 0;
		
		ListNode *pointer = ((ghisee)[numar_ghiseu])->primul ; //pointam la primul element al listei

		if(((ghisee)[numar_ghiseu])->primul->prioritate == prioritate && ((ghisee)[numar_ghiseu])->primul->nume == nume)
			{ return 0; }

		int verificare = 0;
		while(pointer != NULL && verificare == 0)
			{ 
			if(pointer->nume == nume && pointer->prioritate == prioritate) //daca am gasit elementul , intoarcem pozitia
				{
				verificare = 1; 
				return index;
				}
			pointer = pointer->urmator;
			index++;

			}		

		return -1; //daca omul nu s-a gasit la rand
		

}

char* gaseste_persoana_din_fata(List **ghisee, char *nume, int prioritate, 
		int numar_ghiseu) {
	
		if(numar_ghiseu >= NumarActualGhisee) {return "Nu exista.";}  //daca nu exista ghiseul indicat
	
		if(((ghisee)[numar_ghiseu])->primul == NULL && ((ghisee)[numar_ghiseu])->ultimul == NULL) // daca lista era vida
			{ return "Nu exista."; }

		if(((ghisee)[numar_ghiseu])->primul->prioritate == prioritate && ((ghisee)[numar_ghiseu])->primul->nume == nume)
			{ return "Nu exista."; }
		
		ListNode *pointer = ((ghisee)[numar_ghiseu])->primul ; //pointam la primul element al listei

		int verificare = 0;
		while(pointer != NULL && verificare == 0)
			{ 
			
			if(pointer->nume == nume && pointer->prioritate == prioritate) //daca am gasit elementul , intoarcem numele
				{
				verificare = 1; 
				}

			if(verificare == 0)
				{				
				pointer = pointer->urmator;
				}


			}	

	
		if(pointer == NULL ) { return "Nu exista."; } //daca s-a ajuns la final fara sa se gaseasca elementul

		if(pointer->anterior != NULL )  //intoarcem numele celui din fata daca exista
			{ return pointer->anterior->nume; }


               return "Nu exista.";

}

void afiseaza_rand_ghiseu(FILE *f, List **ghisee, int numar_ghiseu) {
	

	if(numar_ghiseu >= NumarActualGhisee) {return;}  //daca nu exista ghiseul indicat

	if(*ghisee == NULL) { fprintf(f, "Ghiseul %d nu are nicio persoana in asteptare.\n", numar_ghiseu ); return; }	//daca ghiseele nu sunt alocate
	

	if( ((ghisee)[numar_ghiseu])->primul == NULL) { fprintf(f, "Ghiseul %d nu are nicio persoana in asteptare.\n", numar_ghiseu ); return; }	//daca ghiseul respectiv nu  este alocat


	ListNode *g = ((ghisee)[numar_ghiseu])->primul; //altfel, afisam oamenii


	while(g != NULL)
		{
		fprintf(f, "%s-%d;", g->nume,g->prioritate);
		g = g->urmator;
		}

		fprintf(f,"\n");

}

#endif
