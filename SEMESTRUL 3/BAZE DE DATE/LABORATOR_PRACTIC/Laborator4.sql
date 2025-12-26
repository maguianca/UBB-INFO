USE MagazinDeBijuterii;
GO 
if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_Tables
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tables]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tables
GO
 
if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunTables_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunTables] DROP CONSTRAINT FK_TestRunTables_TestRuns
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_TestRuns]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_TestRuns
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestTables_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestTables] DROP CONSTRAINT FK_TestTables_Tests
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Tests]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Tests
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestRunViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestRunViews] DROP CONSTRAINT FK_TestRunViews_Views
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[FK_TestViews_Views]') and OBJECTPROPERTY(id, N'IsForeignKey') = 1)
ALTER TABLE [TestViews] DROP CONSTRAINT FK_TestViews_Views
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Tables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunTables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRunViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRunViews]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestRuns]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestRuns]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestTables]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestTables]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[TestViews]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [TestViews]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Tests]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Tests]
GO

if exists (select * from dbo.sysobjects where id = object_id(N'[Views]') and OBJECTPROPERTY(id, N'IsUserTable') = 1)
drop table [Views]
GO

CREATE TABLE [Tables] (
	[TableID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestRunTables] (
	[TestRunID] [int] NOT NULL ,
	[TableID] [int] NOT NULL ,
	[StartAt] [datetime] NOT NULL ,
	[EndAt] [datetime] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestRunViews] (
	[TestRunID] [int] NOT NULL ,
	[ViewID] [int] NOT NULL ,
	[StartAt] [datetime] NOT NULL ,
	[EndAt] [datetime] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestRuns] (
	[TestRunID] [int] IDENTITY (1, 1) NOT NULL ,
	[Description] [nvarchar] (2000) COLLATE SQL_Latin1_General_CP1_CI_AS NULL ,
	[StartAt] [datetime] NULL ,
	[EndAt] [datetime] NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestTables] (
	[TestID] [int] NOT NULL ,
	[TableID] [int] NOT NULL ,
	[NoOfRows] [int] NOT NULL ,
	[Position] [int] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [TestViews] (
	[TestID] [int] NOT NULL ,
	[ViewID] [int] NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [Tests] (
	[TestID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO

CREATE TABLE [Views] (
	[ViewID] [int] IDENTITY (1, 1) NOT NULL ,
	[Name] [nvarchar] (50) COLLATE SQL_Latin1_General_CP1_CI_AS NOT NULL 
) ON [PRIMARY]
GO

ALTER TABLE [Tables] WITH NOCHECK ADD 
	CONSTRAINT [PK_Tables] PRIMARY KEY  CLUSTERED 
	(
		[TableID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRunTables] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRunTables] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID],
		[TableID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRunViews] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRunViews] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID],
		[ViewID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRuns] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestRuns] PRIMARY KEY  CLUSTERED 
	(
		[TestRunID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestTables] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestTables] PRIMARY KEY  CLUSTERED 
	(
		[TestID],
		[TableID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestViews] WITH NOCHECK ADD 
	CONSTRAINT [PK_TestViews] PRIMARY KEY  CLUSTERED 
	(
		[TestID],
		[ViewID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [Tests] WITH NOCHECK ADD 
	CONSTRAINT [PK_Tests] PRIMARY KEY  CLUSTERED 
	(
		[TestID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [Views] WITH NOCHECK ADD 
	CONSTRAINT [PK_Views] PRIMARY KEY  CLUSTERED 
	(
		[ViewID]
	)  ON [PRIMARY] 
GO

ALTER TABLE [TestRunTables] ADD 
	CONSTRAINT [FK_TestRunTables_Tables] FOREIGN KEY 
	(
		[TableID]
	) REFERENCES [Tables] (
		[TableID]
	) ON DELETE CASCADE  ON UPDATE CASCADE ,
	CONSTRAINT [FK_TestRunTables_TestRuns] FOREIGN KEY 
	(
		[TestRunID]
	) REFERENCES [TestRuns] (
		[TestRunID]
	) ON DELETE CASCADE  ON UPDATE CASCADE 
GO

ALTER TABLE [TestRunViews] ADD 
	CONSTRAINT [FK_TestRunViews_TestRuns] FOREIGN KEY 
	(
		[TestRunID]
	) REFERENCES [TestRuns] (
		[TestRunID]
	) ON DELETE CASCADE  ON UPDATE CASCADE ,
	CONSTRAINT [FK_TestRunViews_Views] FOREIGN KEY 
	(
		[ViewID]
	) REFERENCES [Views] (
		[ViewID]
	) ON DELETE CASCADE  ON UPDATE CASCADE 
GO

ALTER TABLE [TestTables] ADD 
	CONSTRAINT [FK_TestTables_Tables] FOREIGN KEY 
	(
		[TableID]
	) REFERENCES [Tables] (
		[TableID]
	) ON DELETE CASCADE  ON UPDATE CASCADE ,
	CONSTRAINT [FK_TestTables_Tests] FOREIGN KEY 
	(
		[TestID]
	) REFERENCES [Tests] (
		[TestID]
	) ON DELETE CASCADE  ON UPDATE CASCADE 
GO

ALTER TABLE [TestViews] ADD 
	CONSTRAINT [FK_TestViews_Tests] FOREIGN KEY 
	(
		[TestID]
	) REFERENCES [Tests] (
		[TestID]
	),
	CONSTRAINT [FK_TestViews_Views] FOREIGN KEY 
	(
		[ViewID]
	) REFERENCES [Views] (
		[ViewID]
	)
GO
-----------------------------
INSERT INTO Tables( Name) VALUES
('Client'), ('Comanda'), ('BijuterieComanda'); 

SELECT * FROM Tables
----------------------------------------

CREATE VIEW ViewClient AS
SELECT id_client,nume,email
FROM Client;
GO

 
CREATE VIEW ViewComenziClienti AS
SELECT 
    c.id_comanda, 
    c.data, 
    c.status, 
    cl.nume AS client_nume, 
    cl.adresa AS client_adresa, 
    cl.telefon AS client_telefon, 
    cl.email AS client_email
FROM Comanda c
JOIN Client cl ON c.id_client = cl.id_client;
GO
----selectare client impreuna cu comanda
CREATE VIEW ViewRezumatComenzi AS
SELECT 
    bc.id_comanda,
    COUNT(bc.id_bij) AS numar_bijuterii, 
    SUM(bc.pret_bucata * bc.cantitate) AS total_valoare  
FROM BijuterieComanda bc
GROUP BY bc.id_comanda;
GO
------pretul final al unei comenzi ordonate dupa numar de comanda
CREATE VIEW ViewRezumatComenzi AS
SELECT 
    c.id_comanda,
    COUNT(bc.id_bij) AS numar_bijuterii,  -- numãrul total de bijuterii comandate
    SUM(bc.pret_bucata * bc.cantitate) AS total_valoare  -- valoarea totalã a comenzii
FROM Comanda c
JOIN BijuterieComanda bc ON c.id_comanda = bc.id_comanda
GROUP BY c.id_comanda;
GO


SELECT * FROM ViewClient;
SELECT * FROM ViewComenziClienti;
SELECT * FROM ViewRezumatComenzi;

SELECT * FROM Comanda;
SELECT * FROM Client;
SELECT * FROM BijuterieComanda;

----------------VIEW---------------------------------------
INSERT INTO Views VALUES ('ViewClient'), ('ViewComenziClienti'), ('ViewRezumatComenzi');
SELECT * FROM Views

-----------------TESTS------------------------------------
-- inserare in Tabela Tests

INSERT INTO Tests(Name) 
VALUES ('test')
GO


SELECT * FROM Tests


-----------------TestViews--------------
INSERT INTO TestViews VALUES(11,1),(11,2),(11,3);
SELECT * FROM TestViews;

-----------------TestTables-------------
INSERT INTO TestTables (TestID, TableID, NoOfRows, Position) 
VALUES (11, 1, 5000, 3),(11, 2, 5000, 2),(11,3,5000,1);

select * from TestTables;
-----------------Proceduri----------------------------
CREATE OR ALTER PROCEDURE InsertClient (@rows INT)
AS 
BEGIN
	DECLARE @id INT
	DECLARE @nume VARCHAR(300)
	DECLARE @adresa VARCHAR(300)
	DECLARE @i INT
	DECLARE @telefon VARCHAR(300)
	DECLARE @email VARCHAR(300)
	SET @i=1
	SET @nume='nume'
	SET @adresa='Strada'
	
	SET IDENTITY_INSERT Client ON;

	WHILE @i <=@rows
	BEGIN 
		SET @id=10000+@i
		SET @email=@nume+ '@'+CAST(@id AS VARCHAR(10))+'.com'
		SET @telefon = '072199' + CAST(FLOOR(RAND() * 10000) AS VARCHAR(4))
		INSERT INTO Client(id_client,nume,adresa,telefon,email) VALUES (@id,@nume,@adresa,@telefon,@email)
		SET @i=@i+1
	END
END
GO

/*
CREATE OR ALTER PROCEDURE DeleteClient(@rows INT)
AS
BEGIN
	DECLARE @i INT
	DECLARE @id INT 
	SET @id=10000
	SET @i=@rows
	WHILE @i>=0
	BEGIN
		SET @id=10000+@i
		DELETE FROM Client WHERE Client.id_client=@id
		SET @i=@i-1
	END
END
GO
*/
CREATE OR ALTER PROCEDURE DeleteClient
AS
BEGIN
	DELETE FROM Client 
END
GO

exec InsertClient 100
exec DeleteClient


SELECT * from Client

CREATE OR ALTER PROCEDURE InsertComanda (@rows INT)
AS 
BEGIN
	DECLARE @id INT
	DECLARE @status VARCHAR(300)
	DECLARE @data DATE 
	DECLARE @i INT
	DECLARE @id_client INT
	SET @i=1
	SET @status='expediat'
	SET @data=GETDATE()
	
	SET IDENTITY_INSERT Comanda ON;

	WHILE @i <=@rows
	BEGIN 
		SET @id=10000+@i
		SET @id_client=10000+@i
		INSERT INTO Comanda(id_comanda,data,status,id_client) VALUES (@id,@data,@status,@id_client)
		SET @i=@i+1
	END
END
GO

/*
CREATE OR ALTER PROCEDURE DeleteComanda(@rows INT)
AS
BEGIN
	DECLARE @i INT
	DECLARE @id INT 
	SET @id=10000
	SET @i=@rows
	WHILE @i>=0
	BEGIN
		SET @id=10000+@i
		DELETE FROM Comanda WHERE Comanda.id_comanda=@id
		SET @i=@i-1
	END
END
GO
*/
CREATE OR ALTER PROCEDURE DeleteComanda
AS
BEGIN
		DELETE FROM Comanda
END
GO

 exec InsertComanda 100
 exec DeleteComanda 
 SELECT * from Comanda

CREATE OR ALTER PROCEDURE InsertBijuterieComanda (@rows INT)
AS 
BEGIN
    DECLARE @id INT;
    DECLARE @id_bij VARCHAR(300);
    DECLARE @cantitate INT;
    DECLARE @pret_bucata FLOAT;
    DECLARE @i INT;

    SET @i = 1;
    SET @pret_bucata = 100;
    SET @cantitate = 1;
    SET @id_bij = 'Br30_006';
  
    WHILE @i <= @rows
    BEGIN 
        SET @id = 10000 + @i; 
        
        INSERT INTO BijuterieComanda (id_bij, id_comanda, cantitate, pret_bucata) 
        VALUES (@id_bij, @id, @cantitate, @pret_bucata);
        SET @i = @i + 1; 
    END
END;
GO


CREATE OR ALTER PROCEDURE DeleteBijuterieComanda
AS
BEGIN
	DELETE FROM BijuterieComanda 
END;
GO
exec InsertBijuterieComanda 100

exec DeleteBijuterieComanda 

select * from BijuterieComanda;
	

CREATE PROCEDURE Select_View @view_name varchar(30)
AS
BEGIN
	SET NOCOUNT ON;
	if @view_name = 'ViewClient'
	begin
		select * from ViewClient
	end

	if @view_name = 'ViewComenziClienti'
	begin
		select * from ViewComenziClienti
	end

	if @view_name = 'ViewRezumatComenzi'
	begin
		select * from ViewRezumatComenzi
	end
END;
GO

exec Select_View ViewClient

select* from Tests;
select* from TestTables;
select* from Tables;

------------------main------------------
CREATE OR ALTER PROCEDURE main (@testID INT)
AS
BEGIN
   DECLARE @testName VARCHAR(50)
   DECLARE @numeTabela NVARCHAR(50);
   DECLARE @NoOfRows INT;
   DECLARE @idTabel INT;
   DECLARE @procedura NVARCHAR(50);
   DECLARE @StartAt DATETIME;
   DECLARE @EndAt DATETIME;
   DECLARE @runID INT;
   DECLARE @sql NVARCHAR(MAX);
   DECLARE @numeView NVARCHAR(50);
   DECLARE @idView INT;

   ------stergere
   DECLARE cursor1 CURSOR FORWARD_ONLY FOR
		SELECT Tables.Name FROM TestTables 
		INNER JOIN Tables ON TestTables.TableID = Tables.TableID
		WHERE TestTables.TestID = @testID
		ORDER BY TestTables.Position;
	OPEN cursor1;

	FETCH NEXT FROM cursor1 INTO @numeTabela;
	WHILE @@FETCH_STATUS = 0
	BEGIN
		--SET @sql = N'DELETE FROM ' + QUOTENAME(@numeTabela);
        --EXEC sp_executesql @sql;
		SET @sql='Delete'+@numeTabela
		EXEC @sql
		FETCH NEXT FROM cursor1 INTO @numeTabela;
	END

	CLOSE cursor1;
	DEALLOCATE cursor1;

	SET @testName = (SELECT Name from Tests WHERE TestID = @testID);
	INSERT INTO TestRuns VALUES
	(@testName, GETDATE(), GETDATE());

	SELECT @runID = MAX(TestRunID)
	FROM TestRuns;

	----inserare-----

	
   DECLARE cursor2 CURSOR FORWARD_ONLY FOR
		SELECT Tables.TableID, Tables.Name, TestTables.NoOfRows FROM TestTables 
		INNER JOIN Tables ON TestTables.TableID = Tables.TableID
		WHERE TestTables.TestID = @testID
		ORDER BY TestTables.Position DESC;
	OPEN cursor2;

	FETCH NEXT FROM cursor2 INTO @idTabel, @numeTabela, @NoOfRows;
	WHILE @@FETCH_STATUS = 0
	BEGIN
		SET @procedura = N'Insert' + @numeTabela;
		SET @StartAt = GETDATE();
		EXEC @procedura @NoOfRows;
		SET @EndAt = GETDATE();
		INSERT INTO TestRunTables VALUES
		(@runID, @idTabel, @StartAt,@EndAt);
		FETCH NEXT FROM cursor2 INTO @idTabel, @numeTabela, @NoOfRows;
	END
	CLOSE cursor2;
	DEALLOCATE cursor2;

	-------views------------------
	DECLARE cursor3 CURSOR FORWARD_ONLY FOR
		SELECT TestViews.ViewID, Views.Name from TestViews
		INNER JOIN Views ON Views.ViewID = TestViews.ViewID
		WHERE TestViews.TestID = @testID;

	OPEN cursor3;
	FETCH NEXT FROM cursor3 INTO @idView, @numeView;
	WHILE @@FETCH_STATUS = 0
	BEGIN 
	  SET @sql = N'SELECT * FROM ' + QUOTENAME(@numeView);
	  SET @StartAt = GETDATE();
	  EXEC sp_executesql @sql;
	  SET @EndAt = GETDATE();
	  INSERT INTO TestRunViews VALUES
	  (@runID, @idView, @StartAt, @EndAt);
	  FETCH NEXT FROM cursor3 INTO @idView, @numeView;
	END;
		
	  CLOSE cursor3;
	  DEALLOCATE cursor3;

	  UPDATE TestRuns
	  SET EndAt = GETDATE()
	  WHERE TestRunID = @runID;
END;

select* from TestViews;
select* from Views;
select * from ViewClient;

EXEC main 11

SELECT * FROM TestRuns
SELECT * FROM TestRunTables
SELECT * FROM TestRunViews