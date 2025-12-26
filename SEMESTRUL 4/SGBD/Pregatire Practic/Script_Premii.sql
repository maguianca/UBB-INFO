-- creati un windows form master-detail care permite cautarea premiilor pentru un tip de premii date. Form-ul ar trebui sa contina
-- cel putin urmatoarele componente: un grid(combobox sau list box) pentru afisarea tipurilor de premii, un grid pentru toate
-- premiile tipului de premii selectate si un buton pentru salvarea premiilor adaugate/ sterse/ modificate.
-- modul in care adaugati / stergeti/ modificati un premiu ramane la latitudinea voastra. un premiu are 
-- nume, sponsor, an, numele catigatorului, varsta. un tip de premiu are un nume si poate fi anual, poate avea un status(activ, inactiv- nu se mai acorda)
-- si un numar maxim de castigatori pe an( de exemplu intr-un an nu poate fi dat la mai mult de x persoane
--scrieti un sql care returneaza toate tipurile de premii pentru care exista minim 3 castigatori
--scrieti un sql care returneaza varsta medie a castigatorilor sub varsta de 18 ani
--creati un index si pentru una dintre interogarile de mai sus

create database Practic_Premii
go 
use Practic_Premii

create table Tip(
id_tip int primary key identity,
anual BIT,
status varchar(100),
numar int);

create table Premiu(
id_premiu int primary key identity,
nume varchar(100),
sponsor varchar(100),
an date,
nume_castigator varchar(100),
varsta int,
id_tip int foreign key references Tip(id_tip));

insert into Tip(nume,anual,status,numar)values('p1',1,'activ',100),('p2',0,'inactiv',2),('p3',1,'activ',5),('p4',0,'activ',10);
select * from tip;
insert into Premiu(nume,sponsor,an,nume_castigator,varsta,id_tip) values
('i1','a','2025-01-02','ana',18,6),
('i3','b','2024-12-13','ionel',21,6),
('i3','c','2024-12-12','gica',22,6),
('i5','c','2021-12-12','gica',22,6),
('i6','c','2025-09-08','ionel bolovan',22,5),
('i7','c','2024-04-05','maricia cocheta',22,7),
('i8','d','2025-11-11','ianos',22,8),
('i9','c','2024-12-12','familia',22,8);
--scrieti un sql care returneaza toate tipurile de premii pentru care exista minim 3 castigatori
--scrieti un sql care returneaza varsta medie a castigatorilor sub varsta de 18 ani
--creati un index si pentru una dintre interogarile de mai sus

select T.nume,T.anual,T.status,T.numar from Tip T 
inner join Premiu P on P.id_tip=T.id_tip
group by T.nume,T.anual,T.status,T.numar
having Count(*)>=3;


select AVG(P.varsta)as medie from Premiu P
where P.varsta<18;

drop index idx_Tip on Tip;
create nonclustered index idx_Tip on Tip(nume,anual,status,numar);

create nonclustered index idx_varsta on Premiu(varsta);
