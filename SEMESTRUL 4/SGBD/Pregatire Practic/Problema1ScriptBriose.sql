CREATE DATABASE Practic_Briose 
GO 
USE Practic_Briose
GO

CREATE TABLE Cofetarii(
cod_cofetarie INT PRIMARY KEY IDENTITY,
nume_cofetarie VARCHAR(200),
adresa VARCHAR(200),
website VARCHAR(200)
);

CREATE TABLE Briose(
cod_briosa INT PRIMARY KEY IDENTITY,
nume_briosa VARCHAR(200),
descriere VARCHAR(1000),
pret REAL,
cod_cofetarie INT FOREIGN KEY REFERENCES Cofetarii(cod_cofetarie) ON DELETE CASCADE 
ON UPDATE CASCADE);

CREATE TABLE Tari(
cod_tara INT PRIMARY KEY IDENTITY,
nume_tara VARCHAR(200)
);
CREATE TABLE Clienti(
cod_client INT PRIMARY KEY IDENTITY,
nume VARCHAR(200),
email VARCHAR(200),
data_nasterii DATE,
cod_tara INT FOREIGN KEY REFERENCES Tari(cod_tara) ON DELETE CASCADE ON UPDATE CASCADE
);

CREATE TABLE Note(
cod_briosa INT FOREIGN KEY REFERENCES Briose(cod_briosa),
cod_client INT FOREIGN KEY REFERENCES Clienti(cod_client),
nota INT 
);

INSERT INTO Cofetarii(nume_cofetarie,adresa, website) 
VALUES ('nadiniere','napoca','ndi.ro'),('Lemnul Verde','strada1','www.lemnul.ro'),
('Carpari','strada2','www.carpati.ro'),
('La Casa','strada3','www.lacasa.ro');

INSERT INTO Briose(nume_briosa,descriere,pret,cod_cofetarie)VALUES
('b1','aaa',12.3,1),
('b2','aaa',19,1),
('b3','aaa',21.3,1),
('b4','aaa',22.5,2),
('b5','aaa',19,2),
('b6','aaa',20,2),
('b7','aaa',21,3),
('b8','aaa',18.5,3),
('b9','aaa',16,3);

INSERT INTO Tari(nume_tara)VALUES('Romania'),('Ungaria'),('Spania');

INSERT INTO Clienti(nume,email,data_nasterii,cod_tara)VALUES
('Ana','ana@gmail','2000-01-02',1),
('Alona','alona@yahoo','2003-12-05',2),
('Ioana','ioana@yahoo','2000-11-11',3);


CREATE NONCLUSTERED INDEX idx_pret_briose
ON Briose(pret,descriere);

select cod_briosa from  Briose 
WHERE pret>20 and descriere LIKE 'a%'

-- Mai multe brioșe pentru testare
INSERT INTO Briose(nume_briosa,descriere,pret,cod_cofetarie) VALUES ('b','s',23,4),
('b10','cioco',10.5,1),
('b11','vanilie',15.3,1),
('b12','capsuni',25,2),
('b13','crema lamaie',19.5,2),
('b14','caramel',17.7,3),
('b15','fructe padure',22.9,3);
select * from Briose;
-- Mai mulți clienți
INSERT INTO Clienti(nume,email,data_nasterii,cod_tara) VALUES
('Mihai','mihai@gmail.com','1999-04-12',1),
('Laura','laura@yahoo.com','2002-08-22',2),
('Pedro','pedro@mail.es','2001-09-09',3);

select * from clienti;
-- Note date de clienți
INSERT INTO Note(cod_briosa,cod_client,nota) VALUES (17,7,8),(17,8,9);
(1,4,9), (2,5,8), (3,7,10),
(4,9,7), (5,8,6), (6,4,9),
(7,9,10), (8,8,7), (11,4,8),
(10,4,9), (11,5,10),
(13,8,7), (14,9,8), (15,7,9);

---Afișează numele cofetăriilor și media notelor acordate brioșelor lor, doar pentru cofetării care au primit cel puțin 3 evaluări. Ordonează descrescător după medie.

select C.nume_cofetarie, AVG(N.nota)as medie from Cofetarii C
INNER JOIN Briose B on B.cod_cofetarie=C.cod_cofetarie
INNER JOIN Note N on N.cod_briosa=B.cod_briosa
group by C.nume_cofetarie
having Count(N.nota)>=3
order by medie DESC


---Afișează numele clienților și numele brioșelor pentru care au dat notă și care au prețul mai mare decât media prețurilor tuturor brioșelor.

select C.nume, B.nume_briosa,B.pret from Clienti C
INNER JOIN Note N on N.cod_client=C.cod_client
INNER JOIN Briose B on B.cod_briosa=N.cod_briosa
where B.pret >(select AVG(B2.pret) from Briose B2)

----Afișează numele și email-ul clienților din România care au acordat nota maximă (per briosa) pentru cel puțin o brioșă.
select DISTINCT C.nume, C.email from Clienti C 
inner join Note N on N.cod_client=C.cod_client
inner join Tari T on C.cod_tara=T.cod_tara
inner  join Briose B on N.cod_briosa=B.cod_briosa
where T.nume_tara='Romania' and N.nota=(select MAX(N2.nota) from Note N2 where N2.cod_briosa=B.cod_briosa)

----Pentru fiecare țară, afișează numele celei mai apreciate brioșe (cu nota medie cea mai mare printre clienții din acea țară). Dacă sunt la egalitate, arată-le pe toate.

---Calculezi media notelor pentru fiecare brioșă și țară (de unde vine clientul).
---Compari acea medie cu cea mai mare medie din acea țară.
---Afișezi doar acele rânduri care ating media maximă pe țara respectivă.

SELECT T.nume_tara, B.nume_briosa, AVG(N.nota) AS media
FROM Note N
JOIN Clienti C ON N.cod_client = C.cod_client
JOIN Tari T ON C.cod_tara = T.cod_tara
JOIN Briose B ON N.cod_briosa = B.cod_briosa
GROUP BY T.nume_tara, B.nume_briosa
HAVING COUNT(*) > 0


WITH BrioseMedii AS (
  SELECT 
    T.nume_tara,
    B.nume_briosa,
    AVG(N.nota) AS media
  FROM Note N
  JOIN Clienti C ON N.cod_client = C.cod_client
  JOIN Tari T ON C.cod_tara = T.cod_tara
  JOIN Briose B ON N.cod_briosa = B.cod_briosa
  GROUP BY T.nume_tara, B.nume_briosa
)


SELECT BM1.nume_tara, BM1.nume_briosa, BM1.media
FROM BrioseMedii BM1
WHERE BM1.media = (
  SELECT MAX(BM2.media)
  FROM BrioseMedii BM2
  WHERE BM2.nume_tara = BM1.nume_tara
);




