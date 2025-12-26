CREATE DATABASE Seminar4
GO 
USE Seminar4

CREATE TABLE Sectiuni (
    cod_s INT PRIMARY KEY, 
    nume VARCHAR(100), 
    descriere VARCHAR(100)
);

CREATE TABLE Atractii (
    cod_a INT PRIMARY KEY, 
    nume VARCHAR(100), 
    descriere VARCHAR(100),
    varsta_min INT,
    cod_s INT,
    FOREIGN KEY(cod_s) REFERENCES Sectiuni(cod_s)
);

CREATE TABLE Categorii (
    cod_c INT PRIMARY KEY,
    nume VARCHAR(100)
);

CREATE TABLE Vizitatori (
    cod_v INT PRIMARY KEY,
    nume VARCHAR(100),
    email VARCHAR(200),
    cod_c INT,
    FOREIGN KEY(cod_c) REFERENCES Categorii(cod_c)
);

CREATE TABLE Note (
    cod_a INT,
    cod_v INT,
    PRIMARY KEY (cod_a, cod_v),
    FOREIGN KEY(cod_a) REFERENCES Atractii(cod_a),
    FOREIGN KEY(cod_v) REFERENCES Vizitatori(cod_v),
    nota INT
);
