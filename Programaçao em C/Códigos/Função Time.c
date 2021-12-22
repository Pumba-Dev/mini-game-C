//  Sistema de Fila de Banco
//
//  Created by Erico Meneses Leão on 05/11/18.
//

#include <stdio.h>
#include <time.h>   //para manipular tempo

double tempo(time_t start){
    time_t now;
    time(&now); //pegando o tempo atual
    double dif = difftime(now,start);
    return dif;
}

int main()
{
    //Guardar o tempo do inicio do programa
    time_t start;
    
    //Guardando a hora local, no tipo time_t
    time(&start); //retorna a representação do número de segundos desde 00:00 de 01/01/1970
    
    
    //forçar a parada para esperar o tempo passar
    getchar();
    
    //chamo a função de tempo
    double dif = tempo(start);
    
    //Imprimindo tempo decorrido!
    printf("Tempo decorrido: %.0fs", dif);
    

    
    return 0;
}


