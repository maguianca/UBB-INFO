GO
USE MagazinDeBijuterii;
INSERT INTO BorderouMarcare(id_borderou, pret_marcare)
VALUES ('B1', 2), ('B2', 2), ('B3', 2);
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
SELECT * from Bijuterie;
SELECT*from BijuterieComanda;
INSERT INTO BorderouMarcare(id_borderou, pret_marcare)
VALUES ('B4', 2), ('B5', 3), ('B6', 10),('B7',2),('B8',3),('B9',2),('B10',3);
INSERT INTO Bijuterie(id_bij,pret_bij,descriere_bij,gramaj_bij,id_borderou)
VALUES ('I30_001',150,'inel argint piatra',5,'B1'),
('I30_002',180,'inel argint',6.1,'B1'),
('I30_003',121,'inel argint piatra',4.2,'B1'),
('I30_004',155,'inel argint piatra',5.4,'B1'),
('I400_005',500,'inel aur',1.2,'B5');
INSERT INTO Bijuterie(id_bij,pret_bij,descriere_bij,gramaj_bij,id_borderou)
VALUES ('Br35_001',182,'bratara argint',182,'B2'),
('Br40_002',156,'bratara pietre semi',3.9,'B2'),
('Br430_003',4214,'bratara aur semi',9.8,'B6'),
('Br35_004',235,'bratara argint pietre',6.7,'B2'),
('Br40_005',90,'Bratara pietre argint',2.25,'B2'),
('Br30_006',125,'Bratara pietre semi',4.2,'B2');
INSERT INTO Bijuterie(id_bij,pret_bij,descriere_bij,gramaj_bij,id_borderou)
VALUES ('C35_001',290,'colier argint',8.5,'B4'),
('C35_002',100,'colier argint pietre',3,'B4'),
('C400_003',1600,'colier aur',4,'B4');

INSERT INTO Material(denumire,pret_bursa)
VALUES('argint 925',4.44),
('argint 925 rodiat',5.1),
('argint 925 rose',4.51),
('argint 925 placat cu aur',10.2),
('aur 14K',233),
('aur 14K rose',250),
('aur 14K alb',265),
('diamant alb briliant',4000),
('diamant alb oval',4000),
('maracasit',80),
('zirconiu alb',65),
('zirconiu rosu',65),
('zirconiu negru',65),
('zirconiu roz',65),
('zirconiu verde',65),
('zirconiu galben',65),
('moisanit',500),
('ametist',250),
('sultanit',170),
('topaz',220),
('smarald',460);
INSERT INTO Procent(id_bij,id_material,procent)
VALUES ('Br30_006',1,70),('Br30_006',11,10),('Br30_006',18,10),('Br30_006',19,10),
('Br35_001',1,100),('Br35_004',1,95),('Br35_004',11,5),('Br40_002',1,80),('Br40_002',17,10),('Br40_002',13,10),
('Br40_005',2,60),('Br40_005',3,20),('Br40_005',14,20),('C35_001',4,100),('C35_002',2,90),('C35_002',16,10),
('C400_003',6,50),('C400_003',7,50),('I30_001',2,90),('I30_001',12,10),('I30_002',3,100),('I30_003',1,90),('I30_003',20,10),
('I30_004',3,70),('I30_004',13,10),('I30_004',14,10),('I30_004',15,10),('I400_005',5,99),('I400_005',6,1),('Br430_003',5,80),
('Br430_003',18,20);
INSERT INTO Categorie(descriere)
VALUES ('Bratara argint'),('Colier argint'),('Colier aur'),('Inel argint'),('Inel aur');
INSERT INTO BijuterieCategorie(id_bij,id_categorie)
VALUES('Br30_006',1),('Br35_001',1),('Br35_004',1),('Br40_002',1),('Br40_005',1),
('C35_001',2),('C35_002',2),('C400_003',3),
('I30_001',4),('I30_002',4),('I30_003',4),('I30_004',4),('I400_005',5),('Br430_003',5);
INSERT INTO Magazin(nume,locatie,oras,nr_tel)
VALUES('Artemis','Iulius Mall','Cluj-Napoca','0359808123'),
('Artemis','Lotus Mall','Oradea','0359808124'),
('Artemis','Iulius Mall','Cluj-Napoca','0359808125'),
('Artemis','Vivo!','Floresti','0359808126'),
('Artemis','AFI Cotroceni','Bucuresti','0359808127');
INSERT INTO StocBijuterieMagazin(id_bij,id_magazin,cantitate)
VALUES ('Br30_006',1,10),('Br35_001',1,10),('Br35_004',1,10),('Br40_002',1,15),('Br40_005',1,15),('C35_001',1,7),('C35_002',1,8),
('C400_003',1,3),('I30_001',1,15),('I30_002',1,16),('I30_003',1,17),('I30_004',1,18),('I400_005',1,5),('Br430_003',1,4),
('Br30_006',2,7),('Br35_001',2,16),('Br35_004',2,13),('Br40_002',2,12),('Br40_005',2,15),('C35_001',2,7),('C35_002',2,8),
('C400_003',2,21),('I30_001',2,15),('I30_002',2,1),('I30_003',2,2),('I30_004',2,6),('I400_005',2,1),('Br430_003',2,2),
('Br30_006',3,4),('Br35_001',3,5),('Br35_004',3,10),('Br40_002',3,12),('Br40_005',3,11),('C35_001',3,9),('C35_002',3,8),
('C400_003',3,3),('I30_001',3,3),('I30_002',3,1),('I30_003',3,5),('I30_004',3,5),('I400_005',3,2),('Br430_003',3,1),
('Br30_006',4,10),('Br35_001',4,10),('Br35_004',4,10),('Br40_002',4,15),('Br40_005',4,15),('C35_001',4,7),('C35_002',4,8),
('C400_003',4,3),('I30_001',4,11),('I30_002',4,10),('I30_003',4,12),('I30_004',4,11),('I400_005',4,5),('Br430_003',4,4),
('Br30_006',5,2),('Br35_001',5,2),('Br35_004',5,2),('Br40_002',5,2),('Br40_005',5,2),('C35_001',5,2),('C35_002',5,2),
('C400_003',5,2),('I30_001',5,2),('I30_002',5,2),('I30_003',5,2),('I30_004',5,2),('I400_005',5,2),('Br430_003',5,2);
INSERT INTO Angajati(nume,post,id_magazin)
VALUES('Maria Ion','manager',1),
('Ioana Matei','vanzator',1),
('Camelia Dan','vanzator',1),
('Andrei Di','vanzator',2),
('Iris Ana','manager',2),
('Ema Tod','vanzator',3),
('Ionela M','vanzator',3),
('Paula Enache','manager',4),
('Ioana Mihalache','vanzator',4),
('Georgiana Soare','vanzator',5),
('Nicoleta M','manager',5);
INSERT INTO Client(nume,adresa,telefon,email)
VALUES('Ioana A','21 Decembrie nr.2,Cluj-Napoca','0721209988','ioanaana@gmail.com'),
('Camelia C','Aurel Vlaicu nr.198,Cluj-Napoca','0727769988','camelia12cornelia@yahoo.com'),
('Mircea P','Crinului 21,Oradea','0734209955','mirceapatrus67@outlook.com'),
('Emilia Z','Parcului 33A,Bucuresti','0712432288','emizoica@gmail.com'),
('Zoia R','Armatei Romane 2,Arad','0733214567','zoiaruca1221_@yahoo.com'),
('Andrei C','Facultatii 91A,Bucuresti','0712433432','andreicaraus@yahoo.com'),
('Razvan D','Titulescu 29D,Timisoara','0770987678','razvidan_9_@gmail.ro');
INSERT INTO Comanda(data,status,id_client)
VALUES('2024-8-20','finalizat',1),
('2024-8-26','finalizat',2),
('2024-9-2','finalizat',3),
('2024-9-11','in curs de expediere',2),
('2024-9-24','expediat',5),
('2024-10-3','finalizat',4),
('2024-10-17','in curs de expediere',6),
('2024-10-18','expediat',7),
('2024-10-22','in curs de expediere',3),
('2024-10-24','expediat',4),
('2024-10-25','in curs de procesare',5);
INSERT INTO BijuterieComanda(id_bij,id_comanda,cantitate,pret_bucata)
VALUES('Br30_006',1000,2,125),('Br35_001',1000,2,125),('Br40_002',1001,1,156),('C35_001',1002,1,285),('C35_002',1005,1,100),
('C400_003',1004,3,1600),('I30_001',1003,4,135),('I30_002',1004,1,180),('I30_003',1002,3,120),('I30_004',1002,1,155),
('I400_005',1005,1,500),('Br430_003',1006,2,4200),
('Br30_006',1001,1,125),('Br35_001',1006,2,182),('Br35_004',1006,1,235),('Br40_002',1007,1,150),('Br40_005',1009,2,90),
('C35_001',1008,1,290),('C35_002',1009,2,100),('C400_003',1010,1,1600);
INSERT INTO Categorie(descriere)
VALUES ('Lant argint'),('Lant aur'),('Pandantiv argint'),('Pandantiv aur');
INSERT INTO Angajati(nume,post,id_magazin)
VALUES
('Denisa P','vanzator',1),
('Cici C','paznic',1),
('Ion I','paznic',2),
('Iona Pop','vanzator',2);
UPDATE Magazin SET nume='Artemis',locatie='Central'
WHERE id_magazin=3;
INSERT INTO BijuterieComanda(id_bij,id_comanda,cantitate,pret_bucata)
VALUES('Br30_006',1009,4,125),('Br35_001',1005,5,125);
INSERT INTO Client(nume,adresa,telefon,email)
VALUES
('Emilia Z','Parcului 33A,Bucuresti','0712432288','emiliazoica@gmail.com');
