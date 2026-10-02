#include <stdio.h>
#include "../shared/network.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>


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

        int connfd;

        connfd = create_client();
        connect_to_server(connfd, PORT);

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
                int message_size;
                char* message;

                u8 id; // TODO expand (only 256)
                switch(op){
                        case 'C':
                        case 'c':
                                puts("CRIAR");
                                scan_estrela(&data);

                                message_size = sizeof(op) + sizeof(data);
                                message = (char*)malloc(message_size);
                                memcpy(message, &op, sizeof(op));
                                memcpy(message+sizeof(op), &data, sizeof(data));

                                printf("%ld", sizeof(data));

                                send(connfd, message, message_size, 0);
                                free(message);
                                break;
                        case 'R':
                        case 'r':
                                puts("LER");
                                printf("Digite o ID desejado: ");
                                scanf("%hhu", &id);
                                message_size = sizeof(op) + sizeof(id);
                                message = (char*)malloc(message_size);
                                memcpy(message, &op, sizeof(op));
                                memcpy(message+sizeof(op), &id, sizeof(id));
                                send(connfd, message, message_size, 0);
                                free(message);
                                
                                u8 result;
                                read(connfd, &result, sizeof(result));
                                if(result == 1){
                                        printf("Dados encontrados\n");
                                        read(connfd, &data, sizeof(data));
                                        print_stardata(data);
                                }
                                if(result == 0)
                                        printf("Dados não encontrados\n");

                                break;
                        case 'U':
                        case 'u':
                                puts("ATUALIZAR");

                                printf("Digite o ID desejado: ");
                                scanf("%hhu", &id);

                                scan_estrela(&data); 

                                message_size = sizeof(op) + sizeof(id) + sizeof(data);

                                message = (char*)malloc(message_size);

                                memcpy(message, &op, sizeof(op));
                                memcpy(message+sizeof(op), &id, sizeof(id));
                                memcpy(message+sizeof(op)+sizeof(id), &data, sizeof(data));

                                send(connfd, message, message_size, 0);
                                free(message);
                                break;
                        case 'D':
                        case 'd':
                                puts("DELETAR");
                                printf("Digite o ID desejado: ");
                                scanf("%hhu", &id);
                                message_size = sizeof(op) + sizeof(id);
                                message = (char*)malloc(message_size);
                                memcpy(message, &op, sizeof(op));
                                memcpy(message+sizeof(op), &id, sizeof(id));
                                send(connfd, message, message_size, 0);
                                free(message);
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

        close(connfd);
        
        return 0;
}
