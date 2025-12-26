<?php
session_start();

if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit;
}

if (!isset($_SESSION['csrf_token'])) {
    $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
}

if ($_SERVER['REQUEST_METHOD'] === 'POST' && isset($_FILES['poza'])) {
    if (!isset($_POST['csrf_token']) || $_POST['csrf_token'] !== $_SESSION['csrf_token']) {
        die("<p style='color:red'>Token CSRF invalid.</p>");
    }

    $file = $_FILES['poza'];
    $ext = strtolower(pathinfo($file['name'], PATHINFO_EXTENSION));
    $mime = mime_content_type($file['tmp_name']);
    $size = $file['size'];

    $allowed_ext = ['jpg', 'jpeg', 'png'];
    $allowed_mime = ['image/jpeg', 'image/png'];

    if (in_array($ext, $allowed_ext) && in_array($mime, $allowed_mime) && $size <= 2 * 1024 * 1024) {
        $nume_nou = uniqid() . '.' . $ext;
        move_uploaded_file($file['tmp_name'], 'poze/' . $nume_nou);

        $conn = new mysqli("localhost", "root", "", "poze");
        if ($conn->connect_error) {
            die("Eroare conexiune DB");
        }

        $stmt = $conn->prepare("INSERT INTO poze (utilizator_id, nume_fisier) VALUES (?, ?)");
        $stmt->bind_param("is", $_SESSION['user_id'], $nume_nou);
        $stmt->execute();
        echo "<p style='color:green'>Imagine incarcata cu succes.</p>";
        $stmt->close();
        $conn->close();
    } else {
        echo "<p style='color:red'>Fisier invalid (tip sau marime gresita).</p>";
    }
}
?>


<form method="post" enctype="multipart/form-data">
    <h2>Upload poza</h2>
    <input type="file" name="poza" required><br>
    <input type="hidden" name="csrf_token" value="<?= htmlspecialchars($_SESSION['csrf_token']) ?>">
    <input type="submit" value="Incarca">
</form>

<p><a href="profil.php">Inapoi la profil</a></p>
