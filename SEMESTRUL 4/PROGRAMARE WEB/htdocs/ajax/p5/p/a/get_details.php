<?php
header('Content-Type: application/json');
$databasePath = 'C:/MPP/Java/TemaLab9/TemaLab7/Festival2025';
try {
    $pdo = new PDO("sqlite:" . $databasePath);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $id = intval($_GET['id']);
    $stmt = $pdo->prepare("SELECT username, email, password FROM Angajat WHERE id = ?");
    $stmt->execute([$id]);

    $data = $stmt->fetch(PDO::FETCH_ASSOC);
    echo json_encode($data);
} catch (PDOException $e) {
    echo json_encode(['error' => $e->getMessage()]);
}
?>
