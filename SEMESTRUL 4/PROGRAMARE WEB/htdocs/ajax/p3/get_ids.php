<?php
header('Content-Type: application/json');
$databasePath = 'C:/xampp/htdocs/ajax/Festival2025';
try {
    $pdo = new PDO("sqlite:" . $databasePath);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
    $result = $pdo->query("SELECT id FROM Angajat");
    $ids = $result->fetchAll(PDO::FETCH_COLUMN);

    echo json_encode($ids);
} catch (PDOException $e) {
    echo json_encode(['error' => 'Eroare BD: ' . $e->getMessage()]);
}
?>
