<?php
session_start();

if (!isset($_SESSION['user_id'])) {
    header("Location: login.php");
    exit;
}

if (!isset($_SESSION['csrf_token'])) {
    $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
}

$conn = new mysqli("localhost", "root", "", "poze");
if ($conn->connect_error) {
    die("Eroare conexiune DB");
}

$profil_id = isset($_GET['id']) ? (int)$_GET['id'] : $_SESSION['user_id'];

$stmt = $conn->prepare("SELECT username FROM utilizatori WHERE id = ?");
$stmt->bind_param("i", $profil_id);
$stmt->execute();
$stmt->bind_result($username);
$stmt->fetch();
$stmt->close();

echo "<h2>Profil: " . htmlspecialchars($username) . "</h2>";
echo "<p>Bun venit, " . htmlspecialchars($_SESSION['username']) . "!</p>";

$stmt = $conn->prepare("SELECT id, nume_fisier FROM poze WHERE utilizator_id = ?");
$stmt->bind_param("i", $profil_id);
$stmt->execute();
$rez = $stmt->get_result();

while ($row = $rez->fetch_assoc()) {
    $img = htmlspecialchars($row['nume_fisier']);
    echo "<div><img src='poze/{$img}' width='200'><br>";
    if ($profil_id === $_SESSION['user_id']) {
        $csrf = htmlspecialchars($_SESSION['csrf_token']);
        echo "<a href='delete.php?id={$row['id']}&csrf={$csrf}'>Șterge</a>";
    }
    echo "</div><hr>";
}

echo "<p><a href='upload.php'>Incarca poza</a> | <a href='logout.php'>Logout</a></p>";

echo "<h3>Vezi alte profiluri:</h3>";
$users = $conn->query("SELECT id, username FROM utilizatori WHERE id != " . $_SESSION['user_id']);
while ($u = $users->fetch_assoc()) {
    $uid = (int)$u['id'];
    $uname = htmlspecialchars($u['username']);
    echo "<a href='profil.php?id={$uid}'>{$uname}</a><br>";
}

$conn->close();
?>
