## Tutoriais seguidos

[Creating a REST API in Rust](https://arshsharma.com/posts/rust-api/)
[Create a High-Performance REST API with Rust](https://www.rustfinity.com/blog/create-high-performance-rest-api-with-rust)
[ CRUD API in Rust Using Axum, SQLite, and sqlx ](https://dev.to/syeedmdtalha/crud-api-in-rust-using-axum-sqlite-and-sqlx-1eea)
[Build a Single-File Rust Web API with SQLite](https://hamy.xyz/blog/2026-03_rust-webapi-db)

## Exemplos de códigos para teste

``` bash
curl -i -X POST http://localhost:3000/stars   -H "Content-Type: application/json"   -d '{
    "name": "Hello", 
    "mass": 5.0, 
    "surface_temperature": 5000.0, 
    "luminosity": 1.0, 
    "radius": 1.2
  }'
```


``` bash
curl -i -X POST http://localhost:3000/observations   -H "Content-Type: application/json"   -d '{
    "telescope": "Hubble", 
    "date": 2010.5, 
    "starid": 1                   
  }'
```
``` bash
curl -X GET http://localhost:3000/stars/2 -s -v | jq .
```
```bash
curl -X GET http://localhost:3000/observations -s -v | jq .
```
