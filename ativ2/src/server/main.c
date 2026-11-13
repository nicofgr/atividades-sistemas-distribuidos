#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <string.h>
#include "../shared/middle.h"
#include "../shared/constants.h"
#include "rpc/svc.h"


void insert(sqlite3* db, star_data data){
        char buffer[512];
        snprintf(buffer, 512,"INSERT INTO STARS (NAME, MASS, SURFACE_TEMPERATURE, LUMINOSITY, RADIUS)"\
                            "VALUES('%s', %f, %f, %f, %f);", data.nome, data.massa, data.temperatura, data.luminosidade, data.raio);
        int rc;
        char* zErrMsg = 0;

        rc = sqlite3_exec(db, buffer, NULL, 0, &zErrMsg);

        if( rc != SQLITE_OK ){
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
        } else {
                fprintf(stdout, "Records created successfully\n");
        }
}

int empty = TRUE;  //TODO: remove global var
static int callback(void *data, int argc, char **argv, char **azColName){
        empty = FALSE;
        int i;
        //fprintf(stderr, "%s: ", (const char*)data);
        
        for(i = 0; i<argc; i++)
                printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
        
        printf("\n");

        star_data* star = (star_data*)data;
        strcpy( star->nome, argv[1]);
        star->massa        = atoi(argv[2]);
        star->temperatura  = atoi(argv[3]);
        star->luminosidade = atoi(argv[4]);
        star->raio         = atoi(argv[5]);

        return 0;
}

u8 db_select(sqlite3* db, u8 id, star_data* data){
        char buffer[512];
        snprintf(buffer, 512,"SELECT * from STARS where ID=%hhu;", id);
        int rc;
        char* zErrMsg = 0;

        rc = sqlite3_exec(db, buffer, callback, data, &zErrMsg);

        if( rc != SQLITE_OK ){
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
        } else {
                fprintf(stdout, "Records read successfully\n");
        }

        if(empty == TRUE){
                return 0;
        }else{
                empty = TRUE;
                return 1;
        }
}

void update(sqlite3* db, u8 id, star_data data){
        char buffer[512];
        snprintf(buffer, 512,"UPDATE STARS "\
                             "SET "\
                             "  NAME = '%s', "\
                             "  MASS = %f, "\
                             "  SURFACE_TEMPERATURE = %f, "\
                             "  LUMINOSITY = %f, "\
                             "  RADIUS = %f "\
                             "WHERE ID = %hhu; " , data.nome, data.massa, data.temperatura, data.luminosidade, data.raio, id);

        printf("%s\n\n", buffer);
        int rc;
        char* zErrMsg = 0;

        rc = sqlite3_exec(db, buffer, NULL, 0, &zErrMsg);

        if( rc != SQLITE_OK ){
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
        } else {
                fprintf(stdout, "Records created successfully\n");
        }

}

void delete(sqlite3* db, u8 id){
        char buffer[512];
        snprintf(buffer, 512,"DELETE from STARS where ID=%hhu;", id);

        int rc;
        char* zErrMsg = 0;

        rc = sqlite3_exec(db, buffer, NULL, 0, &zErrMsg);

        if( rc != SQLITE_OK ){
                fprintf(stderr, "SQL error: %s\n", zErrMsg);
                sqlite3_free(zErrMsg);
        } else {
                fprintf(stdout, "Records deleted successfully\n");
        }
}


// ====== RPC STUFF ============================================================
//
int * create_1_svc(star_data* data, struct svc_req * req){
        static int status;

        sqlite3 *db;
        int rc;
        rc = sqlite3_open("data.db", &db);

        insert(db, *data);

        sqlite3_close(db);
        return &status;
}

star_data * read_1_svc(int* id, struct svc_req * req){
        static int status;

        sqlite3 *db;
        int rc;
        rc = sqlite3_open("data.db", &db);

        star_data data;
        db_select(db, *id, &data);

        sqlite3_close(db);
        return &data;
}

void * update_1_svc(star_data* data, struct svc_req * req){
        static int status;

        sqlite3 *db;
        int rc;
        rc = sqlite3_open("data.db", &db);

        update(db, data->id, *data);

        sqlite3_close(db);
        return &status;
}

void * delete_1_svc(int* id, struct svc_req * req){
        static int status;

        sqlite3 *db;
        int rc;
        rc = sqlite3_open("data.db", &db);

        delete(db, *id);

        sqlite3_close(db);
        return &status;
}
