#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include "../shared/middle.h"
#include "../shared/constants.h"

CLIENT *handle;

void print_stardata(const star_data data){
        printf("Nome: %s\n"
               "Massa %f\n"
               "Temperatura %f\n"
               "Luminosidade %f\n"
               "Raio %f\n", data.nome, data.massa, data.temperatura, data.luminosidade, data.raio);
}
void scan_estrela(star_data* data){
        printf(" Digite o nome da estrela: ");
        scanf("%s", data->nome);
        printf(" Digite a massa da estrela: ");
        scanf("%f", &data->massa);
        printf(" Digite a temperatura da estrela: ");
        scanf("%f", &data->temperatura);
        printf(" Digite a luminosidade da estrela: ");
        scanf("%f", &data->luminosidade);
        printf(" Digite o raio da estrela: ");
        scanf("%f", &data->raio);
}

int main(){

        handle = clnt_create("localhost", CRUDPROG, CRUDVERS, "tcp");

        if(handle == 0){
                fprintf(stderr, "[ERROR] Cant connect to remote program\n");
                exit(1);
        }

        int quit = FALSE;
        while(quit == FALSE){
                puts(" ╔═══════════════════╗\n"
                     " ║ Escolha uma opção ║\n"
                     " ╠═══════════════════╣\n"
                     " ║ C - Criar         ║\n"
                     " ║ R - leR           ║\n"
                     " ║ U - atUalizar     ║\n"
                     " ║ D - Deletar       ║\n"
                     " ║ q - sair          ║\n" 
                     " ╚═══════════════════╝");

                // TODO Arrumar a leitura pra ignorar strings
                u8 op;
                do{
                        op = getchar();
                }while(op == '\n');
                int temp;
                while((temp = getchar()) != '\n' && temp != EOF);

                star_data data;

                int id; // TODO expand (only 256)
                switch(op){
                        case 'C':
                        case 'c':
                                puts("CRIAR");
                                scan_estrela(&data);
                                data.id = 0;
                                int test;
                                test = *create_1(&data, handle);
                                printf("%d\n", test);
                                break;
                        case 'R':
                        case 'r':
                                puts("LER");
                                printf("Digite o ID desejado: ");
                                scanf("%d", &id);
                                data = *read_1(&id, handle);
                                print_stardata(data);
                                break;
                        case 'U':
                        case 'u':
                                puts("ATUALIZAR");
                                printf("Digite o ID desejado: ");
                                scanf("%d", &id);
                                scan_estrela(&data); 
                                data.id = id;
                                update_1(&data, handle); 
                                break;
                        case 'D':
                        case 'd':
                                puts("DELETAR");
                                printf("Digite o ID desejado: ");
                                scanf("%d", &id);
                                delete_1(&id, handle);
                                break;
                        case 'Q':
                        case 'q':
                                quit = TRUE;
                                break;
                        default: 
                                printf("Comando nao reconhecido %c\n", op);
                                break;
                }
        }

        
        return 0;
}
