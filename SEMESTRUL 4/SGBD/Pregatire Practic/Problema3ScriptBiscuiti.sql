CREATE DATABASE Practic_Biscuiti
GO 
USE Practic_Biscuiti 
GO

CREATE TABLE Producatori(
cod_p INT PRIMARY KEY IDENTITY,
nume_p VARCHAR(100),
website VARCHAR(100));

CREATE TABLE Biscuiti(
cod_b INT PRIMARY KEY IDENTITY,
nume_b VARCHAR(100),
nr_calorii INT,
pret INT,
cod_p INT FOREIGN KEY REFERENCES Producatori(cod_p) ON DELETE CASCADE ON UPDATE CASCADE);

CREATE TABLE Tari(
cod_t INT PRIMARY KEY IDENTITY,
nume_t VARCHAR(100));

CREATE TABLE Clienti(
cod_c INT PRIMARY KEY IDENTITY,
nume_c VARCHAR(100),
cod_t INT FOREIGN KEY REFERENCES Tari(cod_t) ON DELETE CASCADE ON UPDATE CASCADE);

CREATE TABLE Note(
cod_b INT FOREIGN KEY REFERENCES Biscuiti(cod_b),
cod_c INT FOREIGN KEY REFERENCES Clienti(cod_c),
nota INT,
CONSTRAINT pk PRIMARY KEY(cod_b,cod_c));

INSERT INTO Producatori(nume_p,website)VALUES
('bisco','biscoc.ro'),
('ulker','ulker.ro'),
('croco','croco.ro');
select * from Producatori
INSERT INTO Biscuiti(nume_b,nr_calorii,pret,cod_p)VALUES
('bisco',100,10,3),
('b1',100,10,1),
('b2',140,7,1),
('b3',99,8,1),
('b4',30,12,2),
('b5',78,8,2);
select * from Biscuiti;

CREATE NONCLUSTERED INDEX idx
ON Biscuiti(nr_calorii);

select cod_b from Biscuiti where nr_calorii<40;

-- Tari
INSERT INTO Tari(nume_t) VALUES
('Romania'), ('Germania'), ('Franta');

-- Clienti
INSERT INTO Clienti(nume_c, cod_t) VALUES
('Ana', 1), ('George', 2), ('Marie', 3), ('Luc', 1), ('Sara', 2);

-- Note
INSERT INTO Note(cod_b, cod_c, nota) VALUES (4,1,11),(7,3,10),(3,4,10),(7,4,6),
(1, 1, 9), (2, 1, 10), (3, 2, 6), (4, 3, 8), (5, 4, 7),
(1, 5, 5), (2, 2, 6), (3, 3, 8), (4, 4, 9), (5, 5, 10);

select * from Note;

----Afișează numele clienților din România, împreună cu numele biscuiților pe care i-au evaluat și nota acordată, ordonat descrescător după notă.

select C.nume_c,B.nume_b,N.nota from Note N
INNER JOIN Clienti C ON N.cod_c=C.cod_C 
INNER JOIN Biscuiti B ON B.cod_b=N.cod_b
INNER JOIN Tari T ON T.cod_t=C.cod_t
WHERE T.nume_t='Romania'
Order by N.nota DESC

-----Afișează pentru fiecare producător numele și media notelor primite pentru biscuiții săi, dar doar dacă au cel puțin 3 recenzii în total.

select P.nume_p,AVG(N.nota) AS media_notelor from Note N
INNER JOIN Biscuiti B on N.cod_b=B.cod_b
INNER JOIN Producatori P ON B.cod_p=P.cod_p
GROUP BY P.nume_p 
HAVING count(N.nota)>=3;

----Afișează numele și țara clienților care au acordat nota maximă pentru orice biscuite, dar doar pentru biscuiți care au mai puțin de 100 calorii.
select C.nume_c, T.nume_t from Clienti C
INNER JOIN Note N on N.cod_c=C.cod_c
INNER JOIN Biscuiti B ON B.cod_b=N.cod_b
INNER JOIN Tari T ON T.cod_t=C.cod_t
WHERE N.nota=10 and B.nr_calorii<100;

--nota maxima !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
select DISTINCT(C.nume_c), T.nume_t as nota from Clienti C
INNER JOIN Note N on N.cod_c=C.cod_c
INNER JOIN Biscuiti B ON B.cod_b=N.cod_b
INNER JOIN Tari T ON T.cod_t=C.cod_t
WHERE B.nr_calorii<100 and N.nota=(
select MAX(N2.nota) from Note N2 where N2.cod_b=N.cod_b
);


---Afișează numele clienților care au dat note mai mari decât media notelor pentru fiecare biscuite evaluat.
select DISTINCT(C.nume_c)from Clienti C 
INNER JOIN Note N on N.cod_c=C.cod_c
INNER JOIN Biscuiti B On B.cod_b=N.cod_b
where N.nota>(select AVG(N2.nota) from Note N2 where N2.cod_b=B.cod_b);