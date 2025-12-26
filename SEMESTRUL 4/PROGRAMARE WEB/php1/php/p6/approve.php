<?php
session_start();
if (!isset($_SESSION['admin_id'])) {
    header("Location: admin_login_app.php");
    exit;
}

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    if (!isset($_POST['csrf_token']) || !hash_equals($_SESSION['csrf_token'], $_POST['csrf_token'])) {
        die("Cerere neautorizata (CSRF).");
    }

    $id = (int)$_POST['id'];

    $conn = new mysqli("localhost", "root", "", "comentarii_app");
    if ($conn->connect_error) {
        die("Eroare conexiune la baza de date");
    }

    $stmt = $conn->prepare("UPDATE comentarii SET aprobat = 1 WHERE id = ?");
    $stmt->bind_param("i", $id);
    $stmt->execute();
}

header("Location: admin_panel.php");
exit;
