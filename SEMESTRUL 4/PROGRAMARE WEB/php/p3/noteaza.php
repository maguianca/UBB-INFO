<?php
session_start();
if (!isset($_SESSION['profesor_id'])) {
    header("Location: login.php");
    exit;
}
if (!isset($_SESSION['csrf_token'])) {
    $_SESSION['csrf_token'] = bin2hex(random_bytes(32));
}

$conn = new mysqli("localhost", "root", "", "catalog");
$studenti = $conn->query("SELECT id, nume FROM studenti");
$materii = $conn->query("SELECT id, denumire FROM materii");

if ($_SERVER["REQUEST_METHOD"] === "POST") {
    if (!isset($_POST['csrf_token']) || $_POST['csrf_token'] !== $_SESSION['csrf_token']) {
        die("<p style='color:red'>CSRF token invalid.</p>");
    }

    $sid = (int)$_POST['student_id'];
    $mid = (int)$_POST['materie_id'];
    $nota = (float)$_POST['nota'];
    $pid = $_SESSION['profesor_id'];

    if ($nota >= 1 && $nota <= 10) {
        $stmt = $conn->prepare("INSERT INTO note (student_id, materie_id, profesor_id, nota) VALUES (?, ?, ?, ?)");
        $stmt->bind_param("iiid", $sid, $mid, $pid, $nota);
        $stmt->execute();
        echo "<p style='color:green'>Nota a fost salvata.</p>";
    } else {
        echo "<p style='color:red'>Nota invalida (1 - 10).</p>";
    }
}
?>

<form method="post" action="noteaza.php">
    <h2>Completare note</h2>

    <label>Student:</label><br>
    <select name="student_id">
        <?php while ($s = $studenti->fetch_assoc()): ?>
            <option value="<?= $s['id'] ?>"><?= htmlspecialchars($s['nume']) ?></option>
        <?php endwhile; ?>
    </select><br><br>

    <label>Materie:</label><br>
    <select name="materie_id">
        <?php while ($m = $materii->fetch_assoc()): ?>
            <option value="<?= $m['id'] ?>"><?= htmlspecialchars($m['denumire']) ?></option>
        <?php endwhile; ?>
    </select><br><br>

    <label>Nota (1-10):</label><br>
    <input type="number" name="nota" step="0.01" min="1" max="10" required><br><br>
    <input type="hidden" name="csrf_token" value="<?= htmlspecialchars($_SESSION['csrf_token']) ?>">

    <input type="submit" value="Salveaza nota">
</form>
