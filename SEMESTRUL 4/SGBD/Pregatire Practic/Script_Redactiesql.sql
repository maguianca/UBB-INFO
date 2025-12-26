CREATE DATABASE Practic_Redactie
GO
Use Practic_Redactie

CREATE TABLE Tip(
id_tip INT PRIMARY KEY IDENTITY,
categorie VARCHAR(100),
redactor VARCHAR(100));

CREATE TABLE Articole(
id_articol INT PRIMARY KEY IDENTITY,
autor VARCHAR(100),
data_aparitie DATE,
numar_citiri INT,
id_tip INT FOREIGN KEY REFERENCES Tip(id_tip));

INSERT INTO Tip(categorie,redactor)VALUES
('cat1','Ana Morodan'),
('cat2','Andreea Raicu'),
('cat3','Alina Ceusan'),
('cat4','Dana Budeanu');
select * from Tip;
select * from Articole;
INSERT INTO Articole(autor,data_aparitie,numar_citiri,id_tip) VALUES
('Ana P','2025-10-11',1,3),
('miruna','2014-10-23',20,3),
('mircea','2023-03-04',10,3);
('dina','2024-03-04',10,3),
('georgi','2024-03-04',100,4),
('clems','2024-03-04',20,4);


----join 1
select T.categorie from Tip T 
inner join Articole A on A.id_tip=T.id_tip
group by T.categorie
having AVG(A.numar_citiri)<50;

--join2
select TOP 1 T.categorie from Tip T 
inner join Articole A on A.id_tip=T.id_tip
group by T.categorie
order by COUNT(*) DESC

CREATE NONCLUSTERED INDEX idx_categorie ON Tip(categorie);
