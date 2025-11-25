#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int convCharInt(char letra){
	switch(letra){
		case 'A':
		case 'a': return 0;
		break;
		case 'B':
		case 'b': return 1;
		break;
		case 'C':
		case 'c': return 2;
		break;
		case 'D':
		case 'd': return 3;
		break;
		case 'E':
		case 'e': return 4;
		break;
		case 'F':
		case 'f': return 5;
		break;
		case 'G':
		case 'g': return 6;
		break;
		case 'H':
		case 'h': return 7;
		break;
		case 'I':
		case 'i': return 8;
		break;
		case 'J':
		case 'j': return 9;
		break;
		case 'K':
		case 'k': return 10;
		break;
		case 'L':
		case 'l': return 11;
		break;
		case 'M':
		case 'm': return 12;
		break;
		case 'N':
		case 'n': return 13;
		break;
		case 'O':
		case 'o': return 14;
		break;
		case 'P':
		case 'p': return 15;
		break;
		case 'Q':
		case 'q': return 16;
		break;
		case 'R':
		case 'r': return 17;
		break;
		case 'S':
		case 's': return 18;
		break;
		case 'T':
		case 't': return 19;
		break;
		case 'U':
		case 'u': return 20;
		break;
		case 'V':
		case 'v': return 21;
		break;
		case 'W':
		case 'w': return 22;
		break;
		case 'X':
		case 'x': return 23;
		break;
		case 'Y':
		case 'y': return 24;
		break;
		case 'Z':
		case 'z': return 25;
		break;
		default: return -1;
		break;
	}
}

char convIntChar(int num){
	switch(num){
		case 0: return 'A';
		break;
		case 1: return 'B';
		break;
		case 2: return 'C';
		break;
		case 3: return 'D';
		break;
		case 4: return 'E';
		break;
		case 5: return 'F';
		break;
		case 6: return 'G';
		break;
		case 7: return 'H';
		break;
		case 8: return 'I';
		break;
		case 9: return 'J';
		break;
		case 10: return 'K';
		break;
		case 11: return 'L';
		break;
		case 12: return 'M';
		break;
		case 13: return 'N';
		break;
		case 14: return 'O';
		break;
		case 15: return 'P';
		break;
		case 16: return 'Q';
		break;
		case 17: return 'R';
		break;
		case 18: return 'S';
		break;
		case 19: return 'T';
		break;
		case 20: return 'U';
		break;
		case 21: return 'V';
		break;
		case 22: return 'W';
		break;
		case 23: return 'X';
		break;
		case 24: return 'Y';
		break;
		case 25: return 'Z';
		break;
	}
}


int main(){

	FILE *frase;
	FILE *fraseCifrada;

	frase = fopen("frase.txt","r");

	if (frase == NULL){
		printf("Error al intentar abrir 'frase.txt'\n");
		exit(1);
	}
	fraseCifrada = fopen("fraseCifrada.txt","w");

	char palabra[1000] = "";
	char cifrado[1000] = "";
	char seccion_cifrada[3];
	int i=0,j,rastro = 0;
	int x[3] = {0,0,0};
	int y[3] = {0,0,0};
	int a[3][3] = {{1,2,3},{0,4,5},{1,0,6}};

        fgets(palabra,sizeof(palabra), frase);

	do{
		//Sirve para crear la seccion a encriptar
		y[1] = 0;
		y[2] = 0;
		y[0] = 0;
		i = 0;

		while(i<3 && !(i == 0 && palabra[rastro] == '\0')){
			if(i>0 && palabra[rastro] == '\0'){
				for(j = i; j<3; j++){
					x[j] = convCharInt('x');
				}
				break;
			}

			if(convCharInt(palabra[rastro]) == -1){
				rastro++;
			}
			else{
				x[i] = convCharInt(palabra[rastro]);
				rastro++;
				i++;
			}
		}
		if (i == 0 && palabra[rastro] == '\0'){
			j = -1;
		}
		if(j != -1){
			//Realiza la multiplicacion de matrices
			for(i = 0; i < 3; i++){
				for(j = 0; j < 3; j++){
					y[i] += a[i][j]*x[j];
				}
			}

			//Genera el modulo del vector y
			for(i = 0; i < 3; i++){
				y[i] = y[i] % 26;
			}

			//Convierte los numeros en letras
			for(i = 0; i<3; i++){
				seccion_cifrada[i] = convIntChar(y[i]);
			}

			strncat(cifrado,seccion_cifrada,sizeof(seccion_cifrada));
		}
	}while(palabra[rastro] != '\0');

	fputs(cifrado, fraseCifrada);

	fclose(frase);
	fclose(fraseCifrada);

}
