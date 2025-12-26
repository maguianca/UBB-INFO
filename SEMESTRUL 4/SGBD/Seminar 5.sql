--Ex1.
--WORKLOAD UL APLICATIEI OPERATII


--CITIRE
/*
-> SELECT (Vizualizare) :
	-Bijuterie dupa categotie
	-Bijuterie dupa material
	-Comanda dupa client
	-Angajati dupa magazin 
	-Bijuterii din stoc magazin
	-Detalii bijuterie (gramaj, pret, matreial, id borderou, descriere)
	-Bijuteriile dintr-un borderou 
*/
---SCRIERE
/*
	INSERT (Adaugare):
		-Bijuterie 
		-Comanda noua
		-Adaugare produs in cos 
		-Client
		-Categorie
		-Angajat
		-Magazin 
		-Material
		-Alocare bijuterii in magazin
		-Adaugare bijuterii in borderou

	UPDATE:
		-Modificare stoc bijuterii magazin
		-Majorare/micsorare pret bijuterie
		-Modificare status comanda 
		-Actualizare date client
		-Actualizare date angajat
		-Modificare post Angajati 

	DELETE:
		-Elimina bijuterii din stoc  (daca cantitate e 0 sau bijuterii neconforme)
		-Stergere comanda
		-Stergere Angajati 
		-Stergere Magazin 
*/

--EX2 
/*
PROCENT

Operatii citire =  aprox(7/27) -> 25%

Operatii scriere= aprox(20/27)  -> 75%

*/

--EX3 
/*
SCRIERE 

Adaugare= aprox(10/20) ->50%

Actualizare= aprox(6/20) ->30%

Stergere= aprox(4/20) ->20%


*/

--EX4
/*
SELECT (citire):
			-Detalii bijuterie (gramaj, pret, material, id borderou, descriere)   (scanare bijuterie pentru clienti)
INSERT (adaugare):
			- Comanda noua (presupunem 10 de comenzi * nr magazin zilnice (clienti))
UPDATE (actualizare):
			- Modificare stoc bijuterii magazin   (presupunem 30 de produse vandute per magazin)
DELETE (stergere):
			- Eliminare bijuterii din stoc  (presupunem 2-3 produse pe luna neconforme (ex. pietre cazute))
*/

--EX5 
/*
TEHNICI DE OPTIMIZARE 
SELECT  - indecsi pe cele mai folosite coloane 

							SELECT (citire): -Detalii bijuterie (gramaj, pret, material, id borderou, descriere)   => Index pe pret/ material

INSERT  -procedura stocata (mai putine comenzi SQL) 
							INSERT (adaugare): - Comanda noua        => procedura stocata inserare_comanda 

UPDATE   -procedura stocata (mai putine comenzi SQL) 
							UPDATE (actualizare): - Modificare stoc bijuterii magazin   =>procedura stocata update_cantitate_stoc 

DELETE    - procedura stocata (mai putine comenzi SQL) 
							DELETE :- Eliminare bijuterii din stoc   => procedura stocata stergere bijuterie stoc magazin


*/