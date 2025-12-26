<?php
session_start();
if (!isset($_SESSION['csrf_token'])) {
    $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
}

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (!isset($_POST['csrf_token']) || $_POST['csrf_token'] !== $_SESSION['csrf_token']) {
        die("CSRF token invalid.");
    }

    $user = trim($_POST['username']);
    $pass = $_POST['password'];

    if ($user && $pass) {
        $hash = password_hash($pass, PASSWORD_DEFAULT);
        $conn = new mysqli("localhost", "root", "", "poze");
        if ($conn->connect_error) {
            die("Eroare conexiune DB");
        }

        $stmt = $conn->prepare("INSERT INTO utilizatori (username, parola) VALUES (?, ?)");
        $stmt->bind_param("ss", $user, $hash);
        if ($stmt->execute()) {
            echo "Cont creat pentru utilizatorul <strong>" . htmlspecialchars($user) . "</strong>. <a href='loginuser.php'>Autentificare</a>";
        } else {
            echo "Utilizatorul exista deja.";
        }

        $conn->close();
    }
}
?>

<form method="post">
    <h2>Inregistrare</h2>
    <input name="username" placeholder="Username" required><br>
    <input name="password" type="password" placeholder="Parola" required><br>
    <input type="hidden" name="csrf_token" value="<?= htmlspecialchars($_SESSION['csrf_token']) ?>">
    <input type="submit" value="Înregistrează-te">
</form>
