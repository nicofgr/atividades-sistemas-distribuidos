struct star_data{
        int   id;
        char  nome[20];
        float massa;
        float temperatura;
        float luminosidade;
        float raio;
};
        
program CRUDPROG{
        version CRUDVERS{
                int       CREATE(star_data) = 1;
                star_data READ( int)   = 2;
                void      UPDATE(star_data) = 3;
                void      DELETE( int) = 4;
        }=1;
}=2233;
