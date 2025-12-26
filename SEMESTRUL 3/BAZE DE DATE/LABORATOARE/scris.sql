CREATE DATABASE Scris
GO 
USE Scris

CREATE TABLE P(
CodP int primary key,
A int,
B int,
C varchar(10),
D varchar(10),
E int
);
insert into P(CodP,A,B,C,D,E)
VALUES(1,78,1,'c1','d1',7),
(2,35,4,'c1','d2',40),
(3,300,3,'c4','d2',7),
(4,560,8,'c2','d1',4),
(5,50,4,'c3','d3',5);

CREATE TABLE R(
CodR int primary key,
A int,
B varchar(10),
C int,
D int,
E varchar(10)
);
insert into R(CodR,A,B,C,D,E)
VALUES(1,7,'b1',12,50,'e1'),
(2,7,'b1',15,80,'e2'),
(3,6,'b2',18,20,'e2'),
(4,9,'b1',29,100,'e3'),
(5,10,'b2',34,150,'e1');

select A,B,COUNT(D)
from R 
GROUP BY A,B
HAVING COUNT(D)<>1

select B,E,SUM(C)
from R 
group by B,E
having sum(C) not in (10,30,15,40)


select D,C,SUM(B)
from P 
GROUP BY D,C
having SUM(B)>4

select E,D,SUM(A)
FROM P 
GROUP BY E,D
HAVING SUM(A) BETWEEN 200 AND 350;

create table RR(
A int,
B int,
C int,
primary key(A,B,C)
);

insert into RR(A,B,C)
values(1,1,1),(2,3,1),(3,3,5),(4,6,7),(5,7,6);
create table SS(
D int,
A int,
primary key(D,A)
);
insert into SS(D,A)
values(1,1),(2,2),(3,4),(4,2);

select R.B from RR R
left join SS S on R.A=S.A
group by R.B 
having count(S.D)>1

select B,C from RR 
where A not in(select A from SS)

select * from SS;

