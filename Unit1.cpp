//---------------------------------------------------------------------------
#pragma hdrstop
#include <stdlib.h>
#include <stdio.h>
#include <iostream.h>
#include <string.h>
#define TAILLE 200
#define NBLETTRESMAX 30
#pragma argsused
//---------------------------------------------------------------------------
struct noeudh
{
	char lettre[NBLETTRESMAX];
	int frequence, numero, fils, bit;
};

struct code
{
	char lettre, codechar[NBLETTRESMAX];
	int nbbits, codebit;

};

void triarbrhuffman(noeudh tab[NBLETTRESMAX][NBLETTRESMAX],int dernier, int Niveau)
{
	int indice = 0;

	for(indice=0;indice<dernier-Niveau;indice++)
	{
		int i, indiceMax=indice;
		for(i=indice+1;i<dernier-Niveau;i++)
		{
			if(tab[Niveau][indiceMax].frequence < tab[Niveau][i].frequence)
				indiceMax = i;
		}
		struct noeudh toto = tab[Niveau][indiceMax];
		tab[Niveau][indiceMax] = tab[Niveau][indice];
		tab[Niveau][indice] = toto;
	}

}

void affichecodes(code tc[NBLETTRESMAX],int NbLettreDifferentes)
{
        int i,j;
        for(i=0;i<NbLettreDifferentes;i++)
        {
                cout<<tc[i].lettre<<" - \t";
                for(j=0;j<strlen(tc[i].codechar);j++)
                        cout<<tc[i].codechar[strlen(tc[i].codechar)-1-j];

                cout<<"\t - code sur "<<tc[i].nbbits<<" bits : \t0x0"<<hex<<tc[i].codebit<<endl;
        }
        cout<<dec;
}

void affichearbre(noeudh tab[NBLETTRESMAX][NBLETTRESMAX],int NbLettreDifferentes, int NiveauEncours) //affiche les niveaux jusqu'au niveau en cours
{ int i,j;
for(i=0;i<=NiveauEncours;i++) //niveau
{ cout<<"---------------- Niveau "<<i<<" ----------------"<<endl;
for(j=0;j<NbLettreDifferentes;j++){cout<<tab[i][j].lettre;if(j!=NbLettreDifferentes-1)cout<<"\t";}cout<<endl;
for(j=0;j<NbLettreDifferentes;j++){cout<<tab[i][j].frequence;if(j!=NbLettreDifferentes-1)cout<<"\t";}cout<<endl;
for(j=0;j<NbLettreDifferentes;j++){cout<<tab[i][j].numero;if(j!=NbLettreDifferentes-1)cout<<"\t";}cout<<endl;
for(j=0;j<NbLettreDifferentes;j++){cout<<tab[i][j].fils;if(j!=NbLettreDifferentes-1)cout<<"\t";}cout<<endl;
for(j=0;j<NbLettreDifferentes;j++){cout<<tab[i][j].bit;if(j!=NbLettreDifferentes-1)cout<<"\t";}cout<<endl;
cout<<endl;
NbLettreDifferentes--;
}
}


int main(int argc, char* argv[])
{
	char tabfreq[256], une = '0', freq = '0', *tabchaine = NULL;
	size_t len = 0;
	int k = 0, i = 0, p = 0, t = 0, n = 0, j = 0, naa = 0, apa = 0, nombreAleatoire = 0, dernier = 0;
	struct noeudh tabhuffman[NBLETTRESMAX][NBLETTRESMAX];
	struct code tabcode[NBLETTRESMAX];

	//getline(&tabchaine, &len, stdin);
	tabchaine = "RIENNESERTDECOURIR";

	for(k=0; k<256; k++) tabfreq[k] = 0; //initialisation du tableau de fr�quence � 0 pour chaque case
	
	for(i=0; i<strlen(tabchaine); i++) //on r�cupere chaque caract�re de la chaine envoy�e
	{
		une = tabchaine[i];
		freq = tabfreq[une]++; 
	}

	for(p=0; p<256; p++)
	{
		if(tabfreq[p] != 0 && p != 10) 
		{	
			tabhuffman[0][dernier].fils = -1;
			tabhuffman[0][dernier].bit = -1;
			tabhuffman[0][dernier].numero = nombreAleatoire++; //numero arbitraire auto increment�
			tabhuffman[0][dernier].frequence = tabfreq[p];
			tabhuffman[0][dernier].lettre[0] = p;
			tabhuffman[0][dernier++].lettre[1] = '\0';
			triarbrhuffman(tabhuffman, dernier, 0);
		}
	}
	
	for(j=0;j<=dernier;j++) //initialisation de tabcode[]
	{
		char c[2] = "";
		tabcode[j].lettre = tabhuffman[0][j].lettre[0];
		tabcode[j].codechar[0] = 0;
		tabcode[j].nbbits = 0;
		tabcode[j].codebit = 0;

		/*if(tabhuffman[0][j].bit != -1)
		{
			c[0] = tabhuffman[0][j].bit+0x30;
			c[1] = 0;
			strcat(tabcode[j].codechar,c);
		}   */

	}
	
	for(apa=1;apa<=dernier-1;apa++) //cr�ation des niveaux >0
	{
		for(j=0;j<=dernier-apa;j++)
		{
			/* ----------------- CLONAGE ------------------ */
			tabhuffman[apa][j] = tabhuffman[apa-1][j];
			tabhuffman[apa][j].numero = tabhuffman[apa-1][j].numero+dernier;
			//tabhuffman[apa][dernier].fils = tabhuffman[apa-1][dernier].numero;
                        tabhuffman[apa-1][j].fils = tabhuffman[apa][j].numero;
		}
		
			/* ----------------- FUSION ------------------ */
			strcat(tabhuffman[apa][dernier-apa-1].lettre, tabhuffman[apa-1][dernier-apa].lettre);
			
			tabhuffman[apa][dernier-apa-1].frequence = tabhuffman[apa-1][dernier-apa-1].frequence + tabhuffman[apa-1][dernier-apa].frequence;

                        tabhuffman[apa-1][dernier-apa].fils = tabhuffman[apa-1][dernier-apa-1].fils;

			tabhuffman[apa-1][dernier-apa-1].bit = 0;
			tabhuffman[apa-1][dernier-apa].bit = 1;
			
			triarbrhuffman(tabhuffman, dernier, apa);

	}
	
	for(j=0;j<dernier;j++)
	{
		tabcode[j].nbbits = strlen(tabcode[j].codechar);
		for(k=0;k<tabcode[j].nbbits-1;k++)
		{
			tabcode[j].codebit = tabcode[j].codechar[k] - 0x30;
		}
	}
	char ch[2];
	for(j=0;j<dernier;j++)
	{
		int pere = j;
		for(apa=1;apa<=dernier;apa++)
		{
			for(p=0;p<dernier-apa;p++)
			{
				if(tabhuffman[apa][p].numero == tabhuffman[apa-1][pere].fils)
				{
					if(tabhuffman[apa][p].fils != -1)
					{
						if(tabhuffman[apa][p].bit != -1)
						{
                                                                ch[0] = tabhuffman[apa][p].bit+0x30;
                                                                ch[1] = 0;
                                                                strcat(tabcode[j].codechar, ch);
						}
						pere = p;
						p = dernier-apa;
					}
				}
			}
		}	
	}
	

	printf("\n\nNombre de caractere differents : %d\n\n", dernier);
	affichearbre(tabhuffman, dernier, dernier-1);
	affichecodes(tabcode, dernier);
	printf("\n\n");

        cin.get();
	return 0;
}
