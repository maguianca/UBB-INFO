<?php
header('Content-Type: application/json');
$databasePath = 'C:/MPP/Java/TemaLab9/TemaLab7/Festival2025';
try {
    $pdo = new PDO("sqlite:" . $databasePath);
    $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $id = intval($_POST['id']);
    $username = $_POST['username'];
    $email = $_POST['email'];
    $password = $_POST['password'];

    $stmt = $pdo->prepare("UPDATE Angajat SET username = ?, email = ?, password = ? WHERE id = ?");
    $ok = $stmt->execute([$username, $email, $password, $id]);

    echo json_encode(['success' => $ok]);
} catch (PDOException $e) {
    echo json_encode(['error' => $e->getMessage()]);
}
?>
