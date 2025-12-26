<?php
session_start();

if (empty($_SESSION['csrf_token'])) {
    $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
}

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    if (!isset($_POST['csrf_token']) || !hash_equals($_SESSION['csrf_token'], $_POST['csrf_token'])) {
        die("Cerere neautorizata (CSRF).");
    }

    $user = trim($_POST['username']);
    $pass = $_POST['password'];

    $conn = new mysqli("localhost", "root", "", "poze");
    if ($conn->connect_error) {
        die("Eroare conexiune la baza de date");
    }

    $stmt = $conn->prepare("SELECT id, parola FROM utilizatori WHERE username = ?");
    $stmt->bind_param("s", $user);
    $stmt->execute();
    $stmt->bind_result($id, $hash);

    if ($stmt->fetch()) {
        if (password_verify($pass, $hash)) {
            $_SESSION['admin_id'] = $id;
            header("Location: admin_panel.php");
            exit;
        } else {
            $err = "Parola incorecta.";
        }
    } else {
        $err = "Utilizator inexistent.";
    }

    $stmt->close();
    $conn->close();
}
?>

<!DOCTYPE html>
<html lang="ro">
<head>
    <meta charset="UTF-8">
    <title>Login admin</title>
</head>
<body>
    <form method="post">
        <h2>Login admin</h2>
        <?php if (!empty($err)) echo "<p style='color:red'>" . htmlspecialchars($err) . "</p>"; ?>
        <input name="username" placeholder="Username" required><br>
        <input type="password" name="password" placeholder="Parola" required><br>
        <!-- Token CSRF -->
        <input type="hidden" name="csrf_token" value="<?= htmlspecialchars($_SESSION['csrf_token']) ?>">
        <input type="submit" value="Login">
    </form>
</body>
</html>
