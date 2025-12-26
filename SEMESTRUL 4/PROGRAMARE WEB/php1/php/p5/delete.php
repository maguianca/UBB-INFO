<?php
session_start();

if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit;
}
if (!isset($_GET['id'], $_GET['csrf']) || $_GET['csrf'] !== $_SESSION['csrf_token']) {
    die("<p style='color:red'>Cerere invalida (CSRF sau parametri lipsa).</p>");
}

$id = (int)$_GET['id'];
$conn = new mysqli("localhost", "root", "", "poze");
if ($conn->connect_error) {
    die("Eroare conexiune DB");
}

$stmt = $conn->prepare("SELECT nume_fisier FROM poze WHERE id = ? AND utilizator_id = ?");
$stmt->bind_param("ii", $id, $_SESSION['user_id']);
$stmt->execute();
$stmt->bind_result($fisier);

if ($stmt->fetch()) {
    $stmt->close();

    $cale = 'poze/' . basename($fisier);
    if (file_exists($cale)) {
        unlink($cale);
    }
    $stmt = $conn->prepare("DELETE FROM poze WHERE id = ?");
    $stmt->bind_param("i", $id);
    $stmt->execute();
}

$conn->close();
header("Location: profil.php");
exit;
