<?php
session_start();

if (isset($_SESSION['user_id'])) {
    header("Location: profil.php");
    exit;
}
if (!isset($_SESSION['csrf_token'])) {
    $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
}

$error = "";

if ($_SERVER['REQUEST_METHOD'] === 'POST') {
    if (!isset($_POST['csrf_token']) || $_POST['csrf_token'] !== $_SESSION['csrf_token']) {
        die("<p style='color:red'>CSRF token invalid.</p>");
    }

    $user = trim($_POST['username']);
    $pass = $_POST['password'];

    $conn = new mysqli("localhost", "root", "", "poze");
    if ($conn->connect_error) {
        die("Eroare conexiune DB");
    }

    $stmt = $conn->prepare("SELECT id, parola FROM utilizatori WHERE username = ?");
    $stmt->bind_param("s", $user);
    $stmt->execute();
    $stmt->bind_result($id, $hash);

    if ($stmt->fetch() && password_verify($pass, $hash)) {
        $_SESSION['user_id'] = $id;
        $_SESSION['username'] = $user;
        header("Location: profil.php");
        exit;
    } else {
        $error = "Autentificare esuata.";
    }

    $stmt->close();
    $conn->close();
}
?>

<form method="post">
    <h2>Autentificare</h2>
    
    <?php if ($error): ?>
        <p style="color:red"><?= htmlspecialchars($error) ?></p>
    <?php endif; ?>
    <input name="username" placeholder="Username" required><br>
    <input name="password" type="password" placeholder="Parola" required><br>
    <input type="hidden" name="csrf_token" value="<?= htmlspecialchars($_SESSION['csrf_token']) ?>">

    <input type="submit" value="Autentificare">
</form>
