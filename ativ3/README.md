Instalar Rust:

```bash
curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs | sh
```

Para compilar e rodar o código:
``` bash
cargo run
```

## Exemplos de códigos para teste

Adicionar uma estrela à tabela stars:
``` bash
curl -i -X POST http://localhost:3000/stars   -H "Content-Type: application/json"   -d '{
    "name": "Beteugeuse", 
    "mass": 14.0, 
    "surface_temperature": 0.62, 
    "luminosity": 7500.0, 
    "radius": 800.0
  }'
```

``` bash
curl -i -X POST http://localhost:3000/stars   -H "Content-Type: application/json"   -d '{
    "name": "Sol", 
    "mass": 1.0, 
    "surface_temperature": 1.0, 
    "luminosity": 1.0, 
    "radius": 1.0
  }'
```

Adicionar uma observação à tabela observations:
``` bash
curl -i -X POST http://localhost:3000/observations   -H "Content-Type: application/json"   -d '{
    "telescope": "Hubble", 
    "date": "2005-11-11", 
    "starid": 1                   
  }'
```
Exemplo de erro, tipo inválido:
``` bash
curl -i -X POST http://localhost:3000/observations   -H "Content-Type: application/json"   -d '{
    "telescope": "Hubble", 
    "date": 2010.5, 
    "starid": 1                   
  }'
```

Mostrar estrela com id = 2:
``` bash
curl -X GET http://localhost:3000/stars/1 -s -v | jq .
```

Mostrar observações:
```bash
curl -X GET http://localhost:3000/observations -s -v | jq .
```

## Referências

* [Creating a REST API in Rust](https://arshsharma.com/posts/rust-api/)
* [Create a High-Performance REST API with Rust](https://www.rustfinity.com/blog/create-high-performance-rest-api-with-rust)
* [ CRUD API in Rust Using Axum, SQLite, and sqlx ](https://dev.to/syeedmdtalha/crud-api-in-rust-using-axum-sqlite-and-sqlx-1eea)
* [Build a Single-File Rust Web API with SQLite](https://hamy.xyz/blog/2026-03_rust-webapi-db)
