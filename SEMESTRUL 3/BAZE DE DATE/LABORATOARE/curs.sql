use MagazinDeBijuterii

Create View vw_ComandaClient with SCHEMABINDING AS 
SELECT Cl.nume, Cl.email,Com.data,Com.id_comanda  FROM dbo.Client Cl
Inner JOIN dbo.Comanda Com ON Com.id_client=Cl.id_client
GO

CREATE UNIQUE CLUSTERED INDEX IX_vw_ComandaClient
ON vw_ComandaClient(nume,email,id_comanda);
GO

select * from vw_ComandaClient WITH (NOEXPAND);
