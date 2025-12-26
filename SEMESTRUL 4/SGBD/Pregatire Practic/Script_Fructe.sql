/*1)Creati un windows form master-detail care permite cautarea fructelor pentru un tip de fructe dat.
Formularul ar trebui sa contina cel putin urmatoarele componente:un grind(combobox sau list box) pentru afisarea tipurilor de fructe ,un grind pentru toate fructele tipului de fructe selectat si un buton pentru salvarea fructelor adaugate/sterse/modificate.
Modul in care adaugati/stergeti/modificati un fruct este la latitudinea voastra.
Un tip de fructe are un nume,cod,data avizare initiala(pt vanzare),un fruct are nume,cod,numar calorii.

2) Scrie-ti un sql care returneaza numele tipului pentru care numarul mediu de calorii al fructelor din acel tip este sub 50.

3)Scrie-ti un sql care returneaza numele tipului care are cele mai multe fructe.

4)Creati un index pentru una dintre interogariile de mai sus .Aratati ca indexul este folosit afisand si explicanda planul de executie pentru in
*/
CREATE DATABASE Practic_Fructe
GO 
USE Practic_Fructe
GO
CREATE TABLE Tipuri(
id_tip INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
data_avizare DATE);

CREATE TABLE Fructe(
id_fruct INT PRIMARY KEY IDENTITY,
nume VARCHAR(100),
numar_calorii INT ,
id_tip INT FOREIGN KEY REFERENCES Tipuri(id_tip));

insert into Tipuri(nume,data_avizare)values
('mar','2020-11-12'),
('para','2024-11-12'),
('portocale','2025-11-11'),
('banane','2025-10-10');
select * from tipuri;
select * from fructe;
insert into Fructe(nume,numar_calorii,id_tip) values
('iodaret',100,1),
('galbene',80,1),
('brussel',60,2),
('belgiene',120,2),
('corene',20,2),
('africane',86,3),
('baby',30,3),
('grecesti',20,4),
('mari',190,4);

select T.nume,T.data_avizare,avg(F.numar_calorii) as avg from Tipuri T 
inner join Fructe F on F.id_tip=T.id_tip
group by T.nume,T.data_avizare
having avg(F.numar_calorii)<70;

select top 1 T.nume from Tipuri T 
inner join Fructe F on F.id_fruct=T.id_tip
group by T.nume
order by COUNT(*) desc


select T.nume from Tipuri T 
inner join Fructe F on F.id_fruct=T.id_tip
where F.numar_calorii<80
ORDER by T.nume DESC;


create nonclustered index idx_nume ON Tipuri(nume,data_avizare);

drop index idx_nume on tipuri;