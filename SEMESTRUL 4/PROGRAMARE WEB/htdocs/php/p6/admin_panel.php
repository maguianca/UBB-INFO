<?php
session_start();
if (!isset($_SESSION['admin_id'])) {
    header("Location: admin_login.php");
    exit;
}
// CSRF token
if (!isset($_SESSION['csrf_token'])) {
    $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
}
$conn = new mysqli("localhost", "root", "", "comentarii_app");
if ($conn->connect_error) {
    die("Eroare conexiune la baza de date");
}
$rez = $conn->query("SELECT id, nume, mesaj, data_adaugare FROM comentarii WHERE aprobat = 0 ORDER BY data_adaugare ASC");

echo "<h2>Comentarii in asteptare:</h2>";

if ($rez->num_rows === 0) {
    echo "<p>Nu exista comentarii de aprobat.</p>";
} else {
    while ($c = $rez->fetch_assoc()) {
        $id = (int)$c['id'];
        $token = $_SESSION['csrf_token'];

        echo "<div>";
        echo "<strong>" . htmlspecialchars($c['nume']) . "</strong> (" . $c['data_adaugare'] . ")<br>";
        echo nl2br(htmlspecialchars($c['mesaj']));
        echo "<br>";
        echo "<form method='post' action='approve.php' style='margin-top:5px'>";
        echo "<input type='hidden' name='id' value='$id'>";
        echo "<input type='hidden' name='csrf_token' value='" . htmlspecialchars($token) . "'>";
        echo "<input type='submit' value='Aproba'>";
        echo "</form>";
        echo "</div><hr>";
    }
}

echo "<a href='logout_app.php'>Logout</a>";
