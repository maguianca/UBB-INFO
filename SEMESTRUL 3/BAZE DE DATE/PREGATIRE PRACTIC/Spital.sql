CREATE DATABASE Spital
GO 
USE Spital

CREATE TABLE Departamente(
id int primary key identity,
nume VARCHAR(100),
non_stop BIT
);

CREATE TABLE Doctor(
id int primary key identity,
nume VARCHAR(100),
data_nasterii DATETIME,
departament int foreign key references Departamente(id)
);
CREATE TABLE Pacient(
id int primary key identity,
nume VARCHAR(100),
data_nasterii DATETIME
);
Create Table DoctorPacient(
id_pacient int foreign key references Pacient(id),
id_doctor int foreign key references Doctor(id),
constraint pk_dp primary key(id_pacient,id_doctor)
);
CREATE TABLE Boala(
id int primary key identity,
denumire VARCHAR(100)
);
CREATE TABLE PacientBoala(
id_pacient int foreign key references Pacient(id),
id_boala int foreign key references Boala(id),
constraint pk_pb primary key(id_pacient,id_boala)
);
CREATE TABLE Tratament(
id int primary key identity,
descriere VARCHAR(100)
);
CREATE TABLE TratamenteBoala(
id_tratament int foreign key references Tratament(id),
id_boala int foreign key references Boala(id),
constraint pk_tb primary key(id_tratament,id_boala)
);


INSERT INTO Departamente (nume, non_stop) VALUES
('Cardiologie', 1),
('Neurologie', 0),
('Pediatrie', 1),
('Pediatrie oncologica',0),
('Ortopedie', 0);

INSERT INTO Doctor (nume, data_nasterii, departament) VALUES
('Dr. Popescu Ion', '1980-05-15', 1),
('Dr. Ionescu Maria', '1975-11-20', 2),
('Dr. Vasile Mihai', '1988-03-10', 3),
('Dr. Georgescu Andreea', '1990-07-05', 4),
('Dr.Iliuta Roxana','1987-10-19',5),
('Dr.Marian Dragos','1998-12-12',4),
('Dr.Ioana Radu','1999-11-11',3),
('Dr Ioana Mircea','1988-11-11',4),
('Dr.Georgescu Ruxandra','1970-05-05',3),
('Dr Mihaela Radulescu','1967-11-11',3);

select * from Doctor;
INSERT INTO Pacient (nume, data_nasterii) VALUES
('Ioana Sandu','1999-11-11'),
('Alexandru Pop', '1995-01-10'),
('Elena Marin', '1987-08-25'),
('Cristina Ionescu', '2005-12-14'),
('Mihai Enache', '1979-04-30');

INSERT INTO DoctorPacient (id_pacient, id_doctor) VALUES
(1, 1),
(2, 2),
(3, 3),
(4, 1),
(1, 4),
(2 ,5),
(3,6);


INSERT INTO Boala (denumire) VALUES
('Hipertensiune'),
('Migrena'),
('Gripa'),
('Fractura');

INSERT INTO PacientBoala (id_pacient, id_boala) VALUES
(1, 1),
(2, 2),
(3, 3),
(4, 4),
(1, 3),(2,3),(5,3),(2,1),(5,1),(4,1);

INSERT INTO Tratament (descriere) VALUES
('Medicament antihipertensiv'),
('Analgezice'),
('Antivirale'),
('Imobilizare ghips');

INSERT INTO TratamenteBoala (id_tratament, id_boala) VALUES
(3,1),
(1, 1),
(2, 2),
(3, 3),
(4, 4),
(2,3),
(2,4);

SELECT * from Departamente where nume LIKE '%pediatrie%';

SELECT COUNT(*) FROM
(
	SELECT id_boala
	FROM PacientBoala
	GROUP BY id_boala
	HAVING count(*) > 3
)t

CREATE OR ALTER FUNCTION cerinta2()
RETURNS INT
AS BEGIN
	DECLARE @nr INT
	Select @nr=COUNT(*) from  (select id_boala from PacientBoala group by id_boala having count(*)>3) t
	RETURN @nr
END;

select dbo. cerinta2();


CREATE OR ALTER VIEW cerinta3
AS 
SELECT 
	T.descriere,TB.id_tratament from Tratament T 
	INNER JOIN TratamenteBoala TB ON T.id=TB.id_tratament
	where T.Descriere LIKE 'A%'
	GROUP BY TB.id_tratament,T.descriere
	having Count(TB.id_tratament)>2;

select * from cerinta3;

CREATE OR ALTER VIEW cerinta4
AS	
SELECT 
	D.nume from Departamente D 
	Inner JOIN Doctor DR ON DR.departament=D.id
	where D.non_stop=1
	GROUp by DR.departament,D.nume
	having count(*)>=3;

select * from cerinta4;