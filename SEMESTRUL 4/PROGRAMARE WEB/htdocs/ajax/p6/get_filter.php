<?php
header('Content-Type: application/json');
$databasePath = 'C:/Programare web/Tema6/componente';
$pdo = new PDO("sqlite:" . $databasePath);
$fields = ['producator', 'procesor', 'memorie', 'hdd', 'video'];
$result = [];

foreach ($fields as $field) {
    $stmt = $pdo->query("SELECT DISTINCT $field FROM notebookuri ORDER BY $field");
    $result[$field] = $stmt->fetchAll(PDO::FETCH_COLUMN);
}

echo json_encode($result);
