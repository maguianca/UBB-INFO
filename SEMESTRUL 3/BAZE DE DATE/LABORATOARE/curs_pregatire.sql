CREATE DATABASE CURS
GO 
USE CURS

CREATE TABLE R(
id int primary key identity,
A int,
B int,
C int
);
CREATE TABLE S(
id int primary key identity,
A int,
D int
);
insert into R(A,B,C)Values (1,2,3),(1,2,4),(3,3,5);
insert into S(A,D) values(1,4),(1,7),(3,8);
select * from R;
select * from S;

select distinct R.B from R left outer join S on R.B=S.A;
select distinct S.A from S right OUTER JOIN R on R.C=S.D;

select distinct B,A from R 
select A,B from R group by B,A

CREATE TABLE RR(
id int primary key identity,
A int,
B int
);
CREATE TABLE SS(
id int primary key identity,
B int,
C int
);
insert into RR(A,B)Values (1,10),(2,20),(3,10);
insert into SS(B,C) values(10,100),(10,200),(20,200);

SELECT RR.a FROM RR, SS WHERE RR.b = SS.B;
SELECT RR.a FROM RR WHERE RR.b IN (SELECT SS.b FROM SS);

CREATE TABLE G(
id int primary key identity,
A int,
B int
);
insert into G(A,B)Values (4,null),(1,10),(1,20),(1,20),(2,15),(2,15),(3,5);

SELECT a, MAX(b) FROM G GROUP BY a;
SELECT a, b FROM G r1 WHERE b >= ALL (SELECT b FROM G r2 WHERE r1.a = r2.a);


CREATE TABLE GG(
id int primary key identity,
A int,
B int
);
insert into GG(A,B)Values (null,3),(1,2),(3,null);
select * from GG
SELECT a 
FROM GG r1 
WHERE EXISTS (SELECT * FROM GG WHERE a = r1.b);

SELECT a 
FROM GG
WHERE b = ANY (SELECT a FROM GG);

select distinct a,b from GG
select a,b from GG group by a,b


CREATE TABLE A(
a int,
b int,
c int
);
CREATE TABLE B(
a int,
b int,
c int
);
insert into A(a,b,c) values(1,2,3),(2,3,4),(3,4,5);
insert into B(a,b,c) values(2,3,6),(3,4,7),(4,5,8);

SELECT DISTINCT a
FROM A
WHERE a NOT IN (SELECT a FROM B);

SELECT a
FROM A
WHERE NOT EXISTS (
    SELECT 1
    FROM B
    WHERE A.a = B.a AND A.b = B.b AND A.c = B.c
);


create table RRR(
A int,
B int,
C int
);
create table SSS(
A int,
D int
);
insert into RRR(A,B,C)values(1,2,3),(1,2,4),(3,3,5);
insert into SSS(A,D)values(1,4),(1,7),(3,8);
select * from RRR
select * from SSS
select RRR.A from RRR inner join SSS on RRR.A=SSS.A except select RRR.A from RRR
select RRR.A from RRR inner join SSS on RRR.A=SSS.A intersect select RRR.A from RRR

create table numbers(
num int
);
insert into numbers values(2),(null),(3),(1),(2),(1);

select avg(num) from numbers;
select count(num) from numbers;
select count(distinct num) from numbers;
select count(num)-max(num) from numbers