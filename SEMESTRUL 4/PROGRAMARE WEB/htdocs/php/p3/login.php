<?php
session_start();
/*
if (isset($_SESSION['profesor_id'])) {
    header("Location: noteaza.php");
    exit;
}*/
if (!isset($_SESSION['csrf_token'])) {
    $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
}

$error = "";

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    if (!isset($_POST['csrf_token']) || $_POST['csrf_token'] !== $_SESSION['csrf_token']) {
        die("CSRF token invalid.");
    }

    $user = trim($_POST['username']);
    $pass = $_POST['password'];

    $conn = new mysqli("localhost", "root", "", "catalog");
    if ($conn->connect_error) {
        die("Eroare conexiune DB");
    }
    $stmt = $conn->prepare("SELECT id FROM profesori WHERE username = ? AND parola_hash = ?");
    $stmt->bind_param("ss", $user, $pass);
    $stmt->execute();
    $stmt->bind_result($id);

    if ($stmt->fetch()) {
        $_SESSION['profesor_id'] = $id;
        $_SESSION['username'] = $user;
        header("Location: noteaza.php");
        exit;
    } else {
        $error = "Date de autentificare invalide.";
    }

    $stmt->close();
    $conn->close();
}
?>

<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <title>Login Profesor</title>
</head>
<body>
<h2>Autentificare Profesor</h2>

<form method="post" action="">
    <?php if ($error): ?>
        <p style="color:red"><?= htmlspecialchars($error) ?></p>
    <?php endif; ?>

    <label>Username:</label><br>
    <input type="text" name="username" required><br>

    <label>Parola:</label><br>
    <input type="password" name="password" required><br><br>
    <input type="hidden" name="csrf_token" value="<?= htmlspecialchars($_SESSION['csrf_token']) ?>">

    <input type="submit" value="Autentificare">
</form>
</body>
</html>
