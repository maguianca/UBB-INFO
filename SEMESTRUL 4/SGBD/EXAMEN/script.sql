create database Practic_Examen
go
use Practic_Examen;
go

create table Tip(
id_tip int primary key identity,
denumire varchar(100),
frecventa varchar(100),
categorie varchar(100),
statut varchar(100));

create table Eveniment(
id_eveniment int primary key identity,
titlu varchar(100),
organizator varchar(100),
data_eveniment DATE,
locatie varchar(100),
numar INT,
id_tip int foreign key references Tip(id_tip));

insert into Tip(denumire,frecventa,categorie,statut)values
('Tip1','anual','muzical','activ'),
('Tip2','lunar','muzical','activ'),
('Tip3','anual','teatral','inactiv'),
('Tip4','ocazional','expozitional','activ'),
('Tip5','anual','expozitional','inactiv');


----2
select T.denumire,T.id_tip, SUM(E.numar) as numar_participanti from Tip T
inner join Eveniment E on E.id_tip=T.id_tip
group by T.denumire,T.id_tip
having SUM(E.numar) >1000

---3
select TOP 1 E.titlu, E.data_eveniment from Eveniment E
inner join Tip T on T.id_tip=E.id_tip
where T.categorie='muzical'
order by E.data_eveniment DESC

select * from Eveniment;
select * from Tip;

---4

create nonclustered index idx_tip on Tip(categorie)

create nonclustered index idx_denumire on Tip(denumire,id_tip)


select * from Tip;

insert into Eveniment(titlu,organizator,data_eveniment,locatie,numar,id_tip)values
('Nunta','Geta Ungurean','2025-11-10','Palas',10,1),
('prezentare moda','Geta','2024-09-08','Expo',2000,4),
('Cei 10','Mr.Dan','2023-10-19','Teatru National',1000,3),
('Nunta','Mircea Bravo','2024-10-19','Teatru National',1000,3),
('Prezentare','Geta','2024-10-19','Expo',10000,5),
('Prezentare','Geta','2025-10-11','Expo',8000,5);

insert into Eveniment(titlu,organizator,data_eveniment,locatie,numar,id_tip)values
('Eveniment1','Geta','2025-04-10','Palas',10,2),
('Eveniment1','Geta','2025-03-12','Oradea',20,2),
('Eveniment1','Geta','2025-02-22','Cluj',30,1),
('Eveniment1','Geta','2025-05-12','Maramures',40,2),
('Eveniment1','Geta','2025-06-11','Bucuresti',55,1),
('Eveniment1','Geta','2025-07-08','Brasov',60,1);

select * from Eveniment;

