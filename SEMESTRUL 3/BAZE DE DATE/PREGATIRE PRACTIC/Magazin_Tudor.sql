CREATE DATABASE Magazin
GO 
USE Magazin
create table Locatii
(id int primary key identity,
strada varchar(100),
numar int,
cod_postal int
);
create table Magazine(
id int primary key identity,
denumire varchar(100),
an_deschidere int,
locatie int foreign key references Locatii(id)
);
create table Clienti(
id int primary key identity,
nume varchar(100),
prenume varchar(100),
gen varchar(100),
data_nasterii date
);
create table ProdusFavorit(
id int primary key identity,
denumire varchar(100),
pret int,
reducere int,
client int foreign key references Clienti(id)
);
create table Cumparaturi(
id_magazin int foreign key references Magazine(id),
id_clienti int foreign key references Clienti(id),
constraint pk_c primary key(id_magazin,id_clienti),
data DATETIME,
pret int
);

-- 1. Adăugăm date în tabela Locatii
INSERT INTO Locatii (strada, numar, cod_postal) 
VALUES 
('Strada Victoriei', 45, 300001),
('Bulevardul Unirii', 10, 300002),
('Calea Dorobanților', 18, 300003);

-- 2. Adăugăm date în tabela Magazine
INSERT INTO Magazine (denumire, an_deschidere, locatie) 
VALUES 
('Magazin Central', 2010, 1),
('Supermarket Unirea', 2015, 2),
('Boutique Dorobanți', 2018, 3);

-- 3. Adăugăm date în tabela Clienti
INSERT INTO Clienti (nume, prenume, gen, data_nasterii) 
VALUES 
('Popescu', 'Ion', 'Masculin', '1985-07-15'),
('Ionescu', 'Maria', 'Feminin', '1990-03-12'),
('Georgescu', 'Ana', 'Feminin', '1995-11-23'),
('Vasilescu', 'Andrei', 'Masculin', '1988-06-10');

-- 4. Adăugăm date în tabela ProdusFavorit
INSERT INTO ProdusFavorit (denumire, pret, reducere, client) 
VALUES 
('Laptop Asus', 3000, 10, 2),
('Telefon Apple', 8000, 15, 1),
('Ceas Rolex', 12000, 5, 1);
('Tableta iPad', 2500, 20, 4);

-- 5. Adăugăm date în tabela Cumparaturi
INSERT INTO Cumparaturi (id_magazin, id_clienti, data, pret) 
VALUES 
(1, 1, '2023-01-15 10:30:00', 2500),
(2, 2, '2023-02-20 15:45:00', 4000),
(3, 3, '2023-03-10 12:15:00', 3000),
(1, 4, '2023-04-05 14:00:00', 5000),
(2, 1, '2023-05-25 11:30:00', 1500);

create or alter view cerinta3
as
	select C.nume as Nume,C.prenume as Prenume,Count(*) as Nr 
	from Clienti C 
	inner join ProdusFavorit PF ON PF.client=C.id
	group by C.nume,C.prenume
	having Count(*)<=3 

select * from cerinta3;

