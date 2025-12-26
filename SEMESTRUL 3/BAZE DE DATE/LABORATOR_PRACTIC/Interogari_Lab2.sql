GO
USE MagazinDeBijuterii;
SELECT * from BorderouMarcare;
SELECT* from Material;
SELECT* from Procent;
SELECT* from Categorie;
SELECT*from BijuterieCategorie;
SELECT*from Magazin;
SELECT*from Angajati;
SELECT *from StocBijuterieMagazin;
SELECT*from Client;
SELECT*from Comanda;
SELECT*from BijuterieComanda;
SELECT * from Bijuterie;
SELECT * from BorderouMarcare;
/* 1 selectez magazinele care nu au paznic dar au cel putin de 2 vanzatori   
   WHERE(4), GROUP BY(1), HAVING(1)
   2 tabele(1)
*/
SELECT id_magazin,nume, locatie FROM Magazin
WHERE id_magazin IN (SELECT id_magazin FROM Angajati WHERE post='vanzator' GROUP BY id_magazin HAVING COUNT(*)>=2 )
EXCEPT
SELECT id_magazin,nume, locatie FROM Magazin
WHERE id_magazin IN (SELECT id_magazin FROM Angajati WHERE post='paznic')

/* 2 selectarea categoriilor care nu au bijuterii agregate(categorii goale)
     WHERE(5), 
	 2 tabele(2)
*/
SELECT c.id_categorie, c.descriere
FROM Categorie c
LEFT JOIN BijuterieCategorie bc ON c.id_categorie = bc.id_categorie
WHERE bc.id_bij IS NULL;

/* 3 afiseaza clientii care au comenzi cu mai mult de 3 produse diferite
   HAVING(2),GROUP BY(2), DISTINCT(1) 
   3 TABELE (3)
   TABELE MANY-MANY(1)
*/
SELECT cl.id_client, cl.nume, cl.adresa, cl.telefon, cl.email
FROM Client cl
JOIN Comanda co ON cl.id_client = co.id_client
JOIN BijuterieComanda bc ON co.id_comanda = bc.id_comanda
GROUP BY cl.id_client, cl.nume, cl.adresa, cl.telefon, cl.email
HAVING COUNT(DISTINCT bc.id_bij) > 2;

/*4 afiseaza clientii care au comenzi cu cel putin de 15 de bucati de produse
  GROUP BY(3), HAVING(3),
  3 TABELE (4)
  TABELE MANY-MANY(2)
*/
SELECT cl.id_client, cl.nume, cl.adresa, cl.telefon, cl.email
FROM Client cl
JOIN Comanda co ON cl.id_client = co.id_client
JOIN BijuterieComanda bc ON co.id_comanda = bc.id_comanda
GROUP BY cl.id_client, cl.nume, cl.adresa, cl.telefon, cl.email
HAVING SUM(bc.cantitate) >= 15;

/*5 afiseaza clientii care au acelasi nume 
   WHERE(6),GROUP BY(4), 
*/
SELECT id_client, nume, adresa,telefon,email
FROM Client
WHERE nume IN (
    SELECT nume
    FROM Client
    GROUP BY nume
    HAVING COUNT(*) > 1
);
/*6.afiseaza numele posturilor din magazine diferite de vanzatori
	DISTINCT(2),WHERE(7)
*/
SELECT DISTINCT post FROM Angajati WHERE post!='vanzator';
/*7.Arata id_bij,descriere,gramaj unde pret_marcare>2 lei
    WHERE(8),
	2 tabele(5)
*/
SELECT b.id_bij, b.descriere_bij, b.gramaj_bij
FROM Bijuterie b
JOIN BorderouMarcare bm ON b.id_borderou = bm.id_borderou
WHERE bm.pret_marcare > 2;
/*8. selectarea borderouriloe care nu au bijuterii agregate(borderouri necompletate)
     WHERE(9),
	 2 tabele(6)
*/
SELECT c.id_borderou, c.pret_marcare
FROM BorderouMarcare c
LEFT JOIN Bijuterie bc ON c.id_borderou = bc.id_borderou
WHERE bc.id_borderou IS NULL;

/*9.Arata bijuteriile care sunt formate dintr-un singur material
  WHERE(10),
  2tabele(7)
*/
SELECT c.id_bij, c.descriere_bij
FROM Bijuterie c
LEFT JOIN Procent bc ON c.id_bij= bc.id_bij
WHERE bc.procent=100;
/*10.Arata magazinele care au un stoc mai mare de 130 de bucati
   GROUP BY(5),HAVING(4)
   2 tabele(8)
*/
SELECT m.id_magazin, m.nume, m.locatie, m.oras, SUM(s.cantitate) AS total_stoc
FROM Magazin m
JOIN StocBijuterieMagazin s ON m.id_magazin = s.id_magazin
GROUP BY m.id_magazin, m.nume, m.locatie, m.oras
HAVING SUM(s.cantitate) > 130;
