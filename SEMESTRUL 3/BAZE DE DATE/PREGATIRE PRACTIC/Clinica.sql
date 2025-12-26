CREATE DATABASE Clinica
GO 
USE Clinica
CREATE TABLE Pacienti(
id int primary key identity,
nume VARCHAR(100),
prenume VARCHAR(100),
adresa VARCHAR(100)
);
CREATE TABLE Specializare(
id int primary key identity,
denumire VARCHAR(100));

CREATE TABLE Diagnostice(
id int primary key identity,
denumire VARCHAR(100),
descriere VARCHAR(100)
);
CREATE TABLE Medici(
id int primary key identity,
nume VARCHAR(100),
prenume VARCHAR(100),
specializare int foreign key references Specializare(id)
);
CREATE TABLE ListaPacienti(
id_medici int foreign key references Medici(id),
id_pacient int foreign key references Pacienti(id),
constraint pk_lp primary key(id_medici,id_pacient),
diagnostic int foreign key references Diagnostice(id),
data DATETIME,
observatii VARCHAR(100),
constraint check_ora CHECK(
	DATEPART(MINUTE,data)=30 or DATEPART(MINUTE,data)=0)
);

INSERT INTO Pacienti (nume, prenume, adresa) VALUES
('Popescu', 'Ion', 'Strada X, Nr. 5'),
('Ionescu', 'Maria', 'Strada Y, Nr. 3'),
('Georgescu', 'Andrei', 'Strada Z, Nr. 10'),
('Vasilescu', 'Elena', 'Strada A, Nr. 1'),
('Mihaila', 'Alexandru', 'Strada B, Nr. 6'),
('Petrescu', 'Ioana', 'Strada C, Nr. 7'),
('Radu', 'Adriana', 'Strada D, Nr. 8'),
('Sandu', 'Mihai', 'Strada E, Nr. 9'),
('Constantin', 'Vlad', 'Strada F, Nr. 11'),
('Popa', 'Lucia', 'Strada G, Nr. 12');

INSERT INTO Specializare (denumire) VALUES
('Cardiologie'),
('Dermatologie');

INSERT INTO Diagnostice (denumire, descriere) VALUES
('Hipertensiune', 'Presiune arterială crescută'),
('Alergii', 'Reacții alergice la diverse substanțe'),
('Acnee', 'Afecțiune dermatologică cu leziuni cutanate'),
('Răceală', 'Infecție virală ușoară'),
('Diabet', 'Probleme cu nivelul zahărului în sânge');

INSERT INTO Medici (nume, prenume, specializare) VALUES
('Popa', 'Ioan', 1), 
('Vasilescu', 'Andrei', 2),
('Ionescu','Amalia',1),
('Mihaescu','Ioana',2),
('Marcelu','Maria',1);

INSERT INTO Pacienti (nume, prenume, adresa) VALUES
('Ionescu', 'Gabriel', 'Strada H, Nr. 13'),
('Munteanu', 'Sorin', 'Strada I, Nr. 14'),
('Dima', 'Stefan', 'Strada J, Nr. 15'),
('Nica', 'Ana', 'Strada K, Nr. 16'),
('Serban', 'Florin', 'Strada L, Nr. 17'),
('Lungu', 'Vasile', 'Strada M, Nr. 18'),
('Rusu', 'Maria', 'Strada N, Nr. 19'),
('Ilie', 'Ion', 'Strada O, Nr. 20'),
('Marin', 'Mihai', 'Strada P, Nr. 21'),
('Ciobanu', 'Andreea', 'Strada Q, Nr. 22'),
('Vlad', 'Ionela', 'Strada R, Nr. 23');


INSERT INTO ListaPacienti (id_medici, id_pacient, diagnostic, data, observatii) VALUES
(1, 1, 1, '2025-01-18 08:00:00', 'Consultatie cardiologie'),
(1, 2, 2, '2025-01-19 08:30:00', 'Consultatie hipertensiune'),
(1, 3, 1, '2025-01-12 09:00:00', 'Consultatie cardiologie'),
(1, 4, 3, '2025-01-11 09:30:00', 'Consultatie hipertensiune'),
(1, 5, 5, '2025-01-12 10:00:00', 'Consultatie diabet'),
(1, 6, 2, '2025-01-13 10:30:00', 'Consultatie alergii'),
(1, 7, 1, '2025-01-14 11:00:00', 'Consultatie cardiologie'),
(1, 8, 3, '2025-01-15 11:30:00', 'Consultatie hipertensiune'),
(1, 9, 4, '2025-01-18 12:00:00', 'Consultatie răceală'),
(1, 10, 5, '2025-01-18 12:30:00', 'Consultatie diabet'),

(2, 1, 3, '2025-01-18 13:00:00', 'Consultatie acnee'),
(2, 2, 4, '2025-01-20 13:30:00', 'Consultatie cosuri'),
(2, 3, 5, '2025-01-01 14:00:00', 'Consultatie diabet'),
(2, 4, 2, '2025-01-10 14:30:00', 'Consultatie alergii'),
(2, 6, 4, '2025-01-11 15:30:00', 'Consultatie răceală'),
(2, 7, 3, '2025-01-11 16:00:00', 'Consultatie acnee'),
(2, 8, 5, '2025-01-12 16:30:00', 'Consultatie psoriazis'),
(2, 9, 1, '2025-01-18 17:00:00', 'Consultatie acnee'),
(2, 10, 3, '2025-01-18 17:30:00', 'Consultatie acnee'),

(4, 1, 3, '2025-01-18 13:00:00', 'Consultatie acnee'),
(4, 2, 4, '2025-01-20 13:30:00', 'Consultatie cosuri'),
(4, 3, 5, '2025-01-01 14:00:00', 'Consultatie diabet'),
(4, 4, 2, '2025-01-10 14:30:00', 'Consultatie alergii'),

(1, 11, 1, '2025-01-19 08:00:00', 'Consultatie cardiologie'),
(1, 13, 2, '2025-01-19 08:30:00', 'Consultatie hipertensiune'),
(1, 14, 3, '2025-01-19 09:00:00', 'Consultatie alergii'),
(1, 16, 5, '2025-01-19 10:00:00', 'Consultatie diabet'),
(1, 17, 2, '2025-01-19 10:30:00', 'Consultatie hipertensiune'),
(1, 18, 4, '2025-01-19 11:00:00', 'Consultatie răceală'),
(1, 19, 3, '2025-01-19 11:30:00', 'Consultatie hipertensiune'),
(1, 15, 3, '2025-01-20 11:30:00', 'Consultatie raceala'),
(1, 20, 3, '2025-01-19 11:30:00', 'Consultatie afectiune inima'),
(1, 12, 1, '2025-01-19 08:00:00', 'Consultatie cardiologie'),
(1, 21, 2, '2025-01-19 08:30:00', 'Consultatie hipertensiune'),

(3, 4, 3, '2025-01-19 09:00:00', 'Consultatie alergii'),
(5, 5, 4, '2025-01-19 09:30:00', 'Consultatie răceală'),
(3, 6, 5, '2025-01-19 10:00:00', 'Consultatie diabet'),
(5, 7, 2, '2025-01-19 10:30:00', 'Consultatie hipertensiune'),
(3, 8, 4, '2025-01-19 11:00:00', 'Consultatie răceală'),
(5, 9, 3, '2025-01-19 11:30:00', 'Consultatie hipertensiune'),
(3, 11, 3, '2025-01-20 11:30:00', 'Consultatie raceala'),
(5, 19, 3, '2025-01-19 11:30:00', 'Consultatie afectiune inima');





CREATE Or ALTER PROceDURE cerinta2
@id_pacient int,
@id_medic int,
@id_diagnostic int,
@observatii VARCHAR(100),
@data_p DATETIME
AS
	IF EXISTS(select 1 from ListaPacienti where id_pacient=@id_pacient and id_medici=@id_medic)
	BEGIN
		UPDATE ListaPacienti 
		SET diagnostic=@id_diagnostic, observatii=@observatii, data=@data_p
		where id_pacient=@id_pacient and id_medici=@id_medic
	END
	ELSE 
	BEGIN
		INSERT INTO ListaPacienti(id_medici,id_pacient,diagnostic,observatii,data)
		VALUES(@id_medic,@id_pacient,@id_diagnostic,@observatii,@data_p);
	END;

exec cerinta2 12,3,2,'Are astm','2025-02-02 18:00';
select * from ListaPacienti
exec cerinta2 1,4,4,'Este ok dupa tratament','2025-02-02 18:00';

CREATE OR ALTER VIEW cerinta3
AS
SELECT 
	DR.nume,DR.prenume from Medici DR
	INNER JOIN ListaPacienti L on DR.id=L.id_medici
	group by DR.nume,DR.prenume
	having count(*)>20
select * from cerinta3;

CREATE OR ALTER FUNCTION cerinta4(@data DATETIME)
RETURNS TABLE AS
RETURN
SELECT
	DR.nume,DR.prenume from Medici DR
	INNER JOIN ListaPacienti L on DR.id=L.id_medici
	where L.data=@data
	group by DR.nume,DR.prenume
	having count(*)>=1

select * from dbo.cerinta4('2025-02-02 18:00');
/* sau daca in ziua respectiva macar 2 consultatii*/

CREATE OR ALTER FUNCTION cerinta5(@data DATE)
RETURNS TABLE AS
RETURN
SELECT
	DR.nume,DR.prenume from Medici DR
	INNER JOIN ListaPacienti L on DR.id=L.id_medici
	where CAST(L.data AS DATE)=@data
	group by DR.nume,DR.prenume
	having count(*)>1

select * from dbo.cerinta5('2025-01-18');



	
	

