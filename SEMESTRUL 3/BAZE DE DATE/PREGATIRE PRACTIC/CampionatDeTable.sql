CREATE DATABASE CampionatTable
GO 
USE CampionatTable
create table Angajati(
id int primary key identity,
nume varchar(100),
nr_contact varchar(100)
);
Create table Masa(
id int primary key identity,
numar int,
culoare varchar(100)
);

create table Meci(
id int primary key identity,
data DATETIME,
masa int foreign key references Masa(id),
id_participant1 int foreign key references Angajati(id),
id_participant2 int foreign key references Angajati(id),
id_castigator int
);
create table Mutari(
id_mutare int primary key identity,
valoare_zar1 int check(1<=valoare_zar1 and valoare_zar1<=6),
valoare_zar2 int check(1<=valoare_zar2 and valoare_zar2<=6),
piesa_mutata_de_la varchar(100),
piesa_mutata_la varchar(100),
id_participant int foreign key references Angajati(id),
id_meci int foreign key references Meci(id)
);
create table MeciuriSpectator(
id_meci int foreign key references Meci(id),
id_angajat int foreign key references Angajati(id),
constraint pk_ms primary key(id_meci,id_angajat)
);
INSERT INTO Angajati (nume, nr_contact) VALUES
('Maria Ioana','CLF3215'),
('Bogdan Popescu', '0723456789'),
('Maria Ionescu', '0731234567'),
('Ion Vasile', '0755678901'),
('Elena Georgescu', '0765432109');

INSERT INTO Masa (numar, culoare) VALUES
(1, 'Rosie'),
(2, 'Albastra'),
(3, 'Verde');

INSERT INTO Meci (data, masa, id_participant1, id_participant2, id_castigator) VALUES
('2025-01-01 14:00:00', 1, 1, 2, 1),  -- Bogdan vs Maria, câștigător Bogdan
('2025-01-02 16:00:00', 2, 3, 4, 3);  -- Ion vs Elena, câștigător Ion
INSERT INTO Meci (data, masa, id_participant1, id_participant2, id_castigator) VALUES
('2024-01-03 14:00',3,5,1,5),
('2024-01-04 18:00',3,2,5,2);

INSERT INTO Mutari (valoare_zar1, valoare_zar2, piesa_mutata_de_la, piesa_mutata_la, id_participant, id_meci) VALUES
(5, 5, 'A1', 'B3', 1, 3),
(3, 2, 'C3', 'D4', 1, 3),
(4, 5, 'A2', 'B5', 5, 3),  
(6, 6, 'C6', 'D1', 5, 3),
(2,3,'A6','B1',3,4),
(2,2,'B1','B3',3,4),
(1,1,'A2','C4',5,4),
(2,2,'C4','C6',5,4);

(4, 5, 'A1', 'B3', 1, 1),  -- Mutare realizată de Bogdan în meciul 1
(6, 2, 'C3', 'D4', 2, 1),  -- Mutare realizată de Maria în meciul 1
(3, 6, 'D2', 'E5', 3, 2),  -- Mutare realizată de Ion în meciul 2
(1, 1, 'E6', 'F7', 4, 2);  -- Mutare realizată de Elena în meciul 2

INSERT INTO MeciuriSpectator (id_meci, id_angajat) VALUES
(1, 3),  -- Ion asistă la meciul 1
(1, 4),  -- Elena asistă la meciul 1
(2, 1),  -- Bogdan asistă la meciul 2
(2, 2);  -- Maria asistă la meciul 2

create or alter procedure cerinta2
@id_participant int 
as
begin
	declare @premiu_total int
	set @premiu_total=0
	declare @premiu int
	set @premiu=0
	select @premiu=100*COUNT(*)
	from Meci M where id_castigator=@id_participant;
	PRINT 'Puncte pt meciuri castigate: '+CAST(@premiu as VARCHAR(50));

	declare @puncte_spectator int
	select @puncte_spectator=10*COUNT(*)
	from MeciuriSpectator M where id_angajat=@id_participant;
	PRINT 'Puncte pt spectator: '+CAST(@puncte_spectator as VARCHAR(50));

	declare @puncte_minus int
	select @puncte_minus=10*COUNT(*)
	from MeciuriSpectator M where id_angajat<>@id_participant;
	PRINT 'Puncte minus: '+CAST(@puncte_minus as VARCHAR(50));

	SET @premiu_total=@premiu+@puncte_spectator-@puncte_minus;
	IF @premiu_total<0
		SET @premiu_total=0
	PRINT 'Puncte totale: '+CAST(@premiu_total AS varchar(50));
END;
exec cerinta2 3;

create or alter view cerinta3
as
select
	A.nume as Nume, A.nr_contact as NumarContract,Count(*) as NumarDuble 
	from Angajati A 
	INNER JOIN Mutari M ON M.id_participant=A.id
	where M.valoare_zar1=M.valoare_zar2 and A.nr_contact='CLF3215'
	group by A.nume,A.nr_contact;
select * from cerinta3;
