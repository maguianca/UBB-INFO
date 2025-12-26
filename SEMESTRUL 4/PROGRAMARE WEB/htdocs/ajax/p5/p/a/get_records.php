<?php
header('Content-Type: application/json');

$databasePath = 'C:/MPP/Java/TemaLab9/TemaLab7/Festival2025';

try {
    $pdo = new PDO("sqlite:" . $databasePath);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $page = isset($_GET['page']) ? intval($_GET['page']) : 0;
    $limit = 3;
    $offset = $page * $limit;//de unde se incepe citirea

    $stmt = $pdo->prepare("SELECT username,email FROM Angajat LIMIT :limit OFFSET :offset");
    $stmt->bindValue(':limit', $limit, PDO::PARAM_INT);
    $stmt->bindValue(':offset', $offset, PDO::PARAM_INT);
    $stmt->execute();

    $results = $stmt->fetchAll(PDO::FETCH_ASSOC);

    echo json_encode($results);
} catch (PDOException $e) {
    echo json_encode(['error' => 'Eroare BD: ' . $e->getMessage()]);
}
?>
