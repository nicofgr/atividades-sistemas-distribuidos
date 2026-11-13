
Exemplos de códigos para teste

curl -i -X POST http://localhost:3000/stars   -H "Content-Type: application/json"   -d '{
    "name": "Hello", 
    "mass": 5.0, 
    "surface_temperature": 5000.0, 
    "luminosity": 1.0, 
    "radius": 1.2
  }'

curl -i -X POST http://localhost:3000/observations   -H "Content-Type: application/json"   -d '{
    "telescope": "Hubble", 
    "date": 2010.5, 
    "starid": 1                   
  }'

curl -X GET http://localhost:3000/stars/2 -s -v | jq .
curl -X GET http://localhost:3000/observations -s -v | jq .
