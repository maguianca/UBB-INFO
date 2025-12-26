CREATE DATABASE Strut
GO
USE Strut

CREATE TABLE Tara(
id int primary key identity,
nume varchar(100),
suprafata int
);

CREATE TABLE Posesor(
id int primary key identity,
nume varchar(100),
prenume varchar(100),
adresa varchar(100),
numar_telefon varchar(100),
id_tara int foreign key references Tara(id)
);
CREATE TABLE Struti(
id int primary key identity,
nume varchar(100),
data_nasterii DATE,
descriere varchar(100),
inaltime int,
greutate int,
id_posesor int foreign key references Posesor(id)
);
CREATE TABLE Competitie(
id int primary key identity,
nume varchar(100),
descriere varchar(100),
data_ora DATETIME,
locatie varchar(100)
);
CREATE TABLE StrutCompetitie(
id_strut int foreign key references Struti(id),
id_competitie int foreign key references Competitie(id),
constraint pk_sc primary key(id_strut,id_competitie),
pozitie int check(pozitie>0)
);

insert into Tara(nume,suprafata)values
('Australia',120000),
('Africa',130000),
('Sudan',81782),
('Korea',12333),
('Rusia',250000);

insert into Posesor(nume,prenume,adresa,numar_telefon,id_tara)
values('Juju','Julia','Habaha street','92783630',1),
('Mamam','Robert','Austra street','9287653',1),
('Doe','John','Liberty street','3242536',2),
('Haja','Ionn','African street','3242627',2),
('Jrav','Elsev','Iberican street','2553363',3),
('Mira','Miraj','M street','243536',3),
('Jshfdh','Xin','3736 Street','4233432',4),
('Xon','Xiv','63542 Street','72653637',4),
('Vladimir','Serej','6353 Street','0988988',5),
('Ruslana','Diana','238 Street','0963553',5);

select * from Posesor;

insert into Struti(nume,data_nasterii,descriere,inaltime,greutate,id_posesor)values
('Strut 1','2020-11-11','Strut Alb',190,80,1),
('Strut 2','2021-10-05','Strut Alb cu roz ',205,89,1),
('Strut 3','2023-12-11','Strut Alb',203,100,2),
('Strut 4','2021-03-04','Strut Negru',188,90,3),
('Strut 5','2022-08-09','Strut Gri',197,99,4),
('Strut 6','2020-04-04','Strut cu cioc rozaliu',201,80,5),
('Strut 7','2019-12-12','Strut cu cioc galben',200,89,5),
('Strut 8','2020-04-04','Strut cu pestrit',201,80,6),
('Strut 9','2019-12-13','StrutoCamila',210,99,7),
('Strut 10','2021-04-14','Strut cu cioc rozaliu',211,89,8),
('Strut 11','2023-12-12','Strut cu cioc galben si roz',201,89,9),
('Strut 12','2020-11-04','Strut negru',199,79,10);
select * from Struti;

insert into Competitie(nume,descriere,data_ora,locatie)values
('Competitie 1','competitie de primarava','2024-05-12 16:00:00','Memmingen'),
('Competitie 2','competitie de iarna','2024-12-12 20:00:00','Londra'),
('Competitie 3','competitie de toamna','2024-10-12 19:00:00','Berlin'),
('Competitie 4','competitie de vara','2024-06-18 20:30:00','Monaco'),
('Competitie 5','competitie strangere fonduri','2023-12-12 12:00:00','Paris'),
('Competitie 6','competitie pregatitoare','2025-01-12 15:00:00','Bruxel'),
('Competitie 7','competitie finala','2025-01-20 17:00:00','Dublin');

insert into StrutCompetitie(id_strut,id_competitie,pozitie)values
(1,1,3),
(2,1,2),
(3,1,4),
(4,1,1),
---------
(1,2,2),
(2,2,3),
(7,2,1),
(8,2,5),
(9,2,4),
---------
(10,3,1),
(11,3,2),
(12,3,3),
(9,3,4),
-------
(11,4,2),
(12,4,5),
(1,4,6),
(3,4,1),
(2,4,3),
-----------
(9,5,1),
(8,5,2),
(7,5,3),
(10,5,4),
-----------
(1,6,1),
(2,6,2),
(3,6,4),
(4,6,3),
---------
(11,7,1),
(12,7,2),
(9,7,3),
(6,7,4);

select * from StrutCompetitie;

select * from Tara;
select * from Posesor;
select * from Competitie;
select * from Struti;
select * from StrutCompetitie;

create or alter procedure cerinta2
@id_strut INT,
@id_competitie INT,
@pozitie INT
AS 
BEGIN 
	IF EXISTS(select 1 from StrutCompetitie where id_strut=@id_strut and id_competitie=@id_competitie)
		BEGIN
			UPDATE StrutCompetitie 
			SET pozitie=@pozitie
			WHERE id_strut=@id_strut and id_competitie=@id_competitie
			PRINT 'S-a modificat cu succes.'
		END
	ELSE 
		BEGIN 
			INSERT INTO StrutCompetitie(id_strut,id_competitie,pozitie)VALUES
			(@id_strut,@id_competitie,@pozitie)
			PRINT 'S-a introdus cu succes.'
		END
END;

exec cerinta2 5,6,1;
select * from StrutCompetitie;

exec cerinta2 5,6,5;
select * from StrutCompetitie;

exec cerinta2 6,6,1;

exec cerinta2 6,6,5;
exec cerinta2 1,7,6;

CREATE OR ALTER FUNCTION cerinta3()
RETURNS TABLE AS
RETURN 
SELECT 
	P.nume AS NumePosesor,P.prenume as PrenumePosesor,P.numar_telefon AS NumarTelefon,
	S.nume as NumeStrut,S.data_nasterii as DataNasteriiStrut
	from Struti S 
	INNER JOIN Posesor P ON S.id_posesor=P.id
	where S.id IN (SELECT S.id from Struti S INNER JOIN StrutCompetitie SC ON SC.id_strut=S.id where SC.pozitie=1)
	and S.id NOT IN(select S.id from Struti S inner join StrutCompetitie SC ON Sc.id_strut=S.id where SC.pozitie=2)

select * from cerinta3();